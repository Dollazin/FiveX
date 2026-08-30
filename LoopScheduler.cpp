#include "LoopScheduler.h"
#include "Core/Global.h"
#include "Lifecycle.h"
#include "FiveXRuntime.h"
#include "CoreNatives.h"

struct FiveXLoopSlot {
	FiveXLoopEntry Entry;
	const CHAR* Name;
	LPVOID Fiber;
	DWORD WakeAt;
	BOOL Active;
	BOOL Completed;
};

static FiveXLoopSlot g_loops[FIVEX_MAX_LOOPS];
static LPVOID g_mainFiber;
static FiveXLoopSlot* g_currentLoop;
static DWORD g_ownerThreadId;
static DWORD g_registeredLoopCount;
static volatile LONG g_prepared;
static volatile LONG g_started;
static volatile LONG g_stopRequested;
static volatile LONG g_stopped;
static volatile LONG g_restartAfterCleanup;
static DWORD g_readinessProbeAt;
static DWORD g_readinessStableSince;
static BOOL g_readinessCombined;
static BOOL g_ownsThreadConversion;

static VOID UpdateGameReadiness() {
	const DWORD now = GetTickCount();
	if (g_readinessProbeAt && (LONG)(now - g_readinessProbeAt) < 0)
		return;
	g_readinessProbeAt = now + 500;

	const BOOL loadingScreenActive = GetIsLoadingScreenActive();
	const BOOL noLoadingScreen = GetNoLoadingScreen();
	const BOOL busySpinnerOn = BusyspinnerIsOn();
	const BOOL networkLoadingScene = IsNetworkLoadingScene();
	const BOOL screenFadedIn = IsScreenFadedIn();
	const Player player = (Player)PlayerId();
	const BOOL playerPlaying = IsPlayerPlaying(player);
	const Ped ped = (Ped)PlayerPedId();
	const BOOL pedExists = ped && DoesEntityExist(ped);
	const BOOL pedAlive = pedExists && !IsPedDeadOrDying(ped, TRUE);
	const BOOL navmeshLoaded = AreAllNavmeshRegionsLoaded();
	const BOOL combinedReady = !loadingScreenActive && !busySpinnerOn && !networkLoadingScene && screenFadedIn && playerPlaying && pedExists && pedAlive && navmeshLoaded;

	(void)noLoadingScreen;
	if (combinedReady != g_readinessCombined) {
		g_readinessCombined = combinedReady;
		DbgPrint("[FiveX][ReadyCheck] COMBINED_READY=%d\n", combinedReady);
	}
	if (!combinedReady) {
		g_readinessStableSince = 0;
		return;
	}
	if (!g_readinessStableSince) {
		g_readinessStableSince = now;
		DbgPrint("[FiveX][ReadyCheck] Game signals ready; starting 5-second stability timer.\n");
	}
}

static BOOL GameReadinessUnlocked() {
	UpdateGameReadiness();
	if (!g_readinessCombined || !g_readinessStableSince)
		return FALSE;
	if ((DWORD)(GetTickCount() - g_readinessStableSince) < 5000)
		return FALSE;
	DbgPrint("[FiveX][ReadyCheck] Game remained ready for 5 seconds. Runtime may initialize.\n");
	return TRUE;
}

static VOID WINAPI LoopFiber(LPVOID parameter) {
	FiveXLoopSlot* loop = (FiveXLoopSlot*)parameter;
	if (loop && loop->Entry)
		loop->Entry();

	if (loop) {
		loop->Completed = TRUE;
		loop->Active = FALSE;
	}

	for (;;)
		SwitchToFiber(g_mainFiber);
}

static BOOL CleanupOnOwnerThread() {
	FiveXRuntimeShutdown();
	const BOOL restart = g_restartAfterCleanup && FiveXCallbacksAllowed();

	for (DWORD index = 0; index < FIVEX_MAX_LOOPS; ++index) {
		if (g_loops[index].Fiber) {
			DeleteFiber(g_loops[index].Fiber);
			g_loops[index].Fiber = NULL;
		}
		g_loops[index].Entry = NULL;
		g_loops[index].Name = NULL;
		g_loops[index].WakeAt = 0;
		g_loops[index].Active = FALSE;
		g_loops[index].Completed = FALSE;
	}

	g_currentLoop = NULL;
	g_registeredLoopCount = 0;
	g_started = 0;
	if (g_ownsThreadConversion)
		ConvertFiberToThread();
	g_mainFiber = NULL;
	g_ownerThreadId = 0;
	g_ownsThreadConversion = FALSE;
	g_restartAfterCleanup = 0;
	if (restart) {
		FiveXLoopPrepare();
		DbgPrint("[FiveX] Loop scheduler reset after a partial startup failure.\n");
		return TRUE;
	}
	g_stopped = 1;
	MemoryBarrier();
	DbgPrint("[FiveX] Loop scheduler stopped.\n");
	return TRUE;
}

VOID FiveXLoopPrepare() {
	for (DWORD index = 0; index < FIVEX_MAX_LOOPS; ++index) {
		g_loops[index].Entry = NULL;
		g_loops[index].Name = NULL;
		g_loops[index].Fiber = NULL;
		g_loops[index].WakeAt = 0;
		g_loops[index].Active = FALSE;
		g_loops[index].Completed = FALSE;
	}

	g_mainFiber = NULL;
	g_currentLoop = NULL;
	g_ownerThreadId = 0;
	g_registeredLoopCount = 0;
	g_ownsThreadConversion = FALSE;
	g_started = 0;
	g_stopRequested = 0;
	g_stopped = 0;
	g_restartAfterCleanup = 0;
	g_readinessProbeAt = 0;
	g_readinessStableSince = 0;
	g_readinessCombined = FALSE;
	g_prepared = 1;
	MemoryBarrier();
}

BOOL FiveXRegisterLoop(FiveXLoopEntry entry, const CHAR* name) {
	if (!entry || g_started)
		return FALSE;

	for (DWORD index = 0; index < FIVEX_MAX_LOOPS; ++index) {
		if (!g_loops[index].Entry) {
			g_loops[index].Entry = entry;
			g_loops[index].Name = name;
			g_loops[index].Active = TRUE;
			++g_registeredLoopCount;
			return TRUE;
		}
	}

	DbgPrint("[FiveX] Loop registration failed: limit=%u.\n", FIVEX_MAX_LOOPS);
	return FALSE;
}

static BOOL StartOnCurrentThread() {
	g_ownerThreadId = GetCurrentThreadId();
	g_mainFiber = ConvertThreadToFiber(NULL);
	g_ownsThreadConversion = g_mainFiber != NULL;
	if (!g_mainFiber)
		g_mainFiber = GetCurrentFiber();
	if (!g_mainFiber)
		return FALSE;

	if (!FiveXRuntimeInitialize()) {
		FiveXRuntimeShutdown();
		if (g_ownsThreadConversion)
			ConvertFiberToThread();
		g_mainFiber = NULL;
		g_ownerThreadId = 0;
		g_ownsThreadConversion = FALSE;
		return FALSE;
	}

	FiveXRegisterLoops();
	g_started = 1;
	for (DWORD index = 0; index < FIVEX_MAX_LOOPS; ++index) {
		if (g_loops[index].Entry) {
			g_loops[index].Fiber = CreateFiber(FIVEX_LOOP_STACK_SIZE, LoopFiber, &g_loops[index]);
			if (!g_loops[index].Fiber) {
				g_restartAfterCleanup = 1;
				g_stopRequested = 1;
				CleanupOnOwnerThread();
				return FALSE;
			}
			DbgPrint("[FiveX] Loop initialized: %s\n",
				g_loops[index].Name ? g_loops[index].Name : "unnamed");
		}
	}

	DbgPrint("[FiveX] Loop scheduler started. Registered=%u\n", g_registeredLoopCount);
	return TRUE;
}

VOID FiveXLoopTick() {
	if (!g_prepared)
		return;

	if (!g_started) {
		if (g_stopRequested) {
			g_stopped = 1;
			return;
		}
		if (!GameReadinessUnlocked())
			return;
		if (!StartOnCurrentThread())
			return;
	}

	if (GetCurrentThreadId() != g_ownerThreadId)
		return;

	if (g_stopRequested) {
		CleanupOnOwnerThread();
		return;
	}

	DWORD now = GetTickCount();
	for (DWORD index = 0; index < FIVEX_MAX_LOOPS && !g_stopRequested; ++index) {
		FiveXLoopSlot* loop = &g_loops[index];
		if (loop->Active && loop->Fiber && Helpers::HasElapsed(now, loop->WakeAt)) {
			g_currentLoop = loop;
			SwitchToFiber(loop->Fiber);
			g_currentLoop = NULL;
		}
	}

	if (g_stopRequested)
		CleanupOnOwnerThread();
}

VOID FiveXWait(DWORD milliseconds) {
	if (!g_currentLoop || !g_mainFiber)
		return;

	g_currentLoop->WakeAt = GetTickCount() + milliseconds;
	SwitchToFiber(g_mainFiber);
}

VOID FiveXLoopRequestStop() {
	g_stopRequested = 1;
	MemoryBarrier();
	if (!g_started)
		g_stopped = 1;
}

BOOL FiveXLoopsAreStopped() {
	return g_stopped != 0;
}

BOOL FiveXCanWait() {
	return g_currentLoop != NULL &&
		g_mainFiber != NULL &&
		g_ownerThreadId != 0 &&
		GetCurrentThreadId() == g_ownerThreadId;
}

BOOL FiveXStopWasRequested() {
	return g_stopRequested != 0;
}
