#include "FiveXKernel.h"
#include "NativeLoop.h"

#define FIVEX_WORKER_STACK_SIZE (64 * 1024)
#define FIVEX_EX_CREATE_FLAG_SYSTEM 0x2
#define FIVEX_GTA_TITLE_ID 0x545408A7
#define FIVEX_SCRIPT_DISPATCHER_ADDRESS 0x83525E00
#define FIVEX_TITLE_STABILITY_MS 1500

// The RGH plugin loader cannot run the full Xbox DLL CRT bootstrap safely.
// Initialize only the multithread runtime after the XAPI heap is ready. This
// creates the CRT lock table up front and prevents _mtinitlocknum from trying
// to initialize lock 10 through _lock(10), which recurses indefinitely.
extern "C" INT __cdecl _mtinit();

static HANDLE g_module;
static volatile LONG g_stop;
static volatile LONG g_callbacks;
typedef DWORD(__cdecl* FiveXGetCurrentTitleId)();
static FiveXGetCurrentTitleId g_getCurrentTitleId;
static DWORD g_gtaCandidateSince;
static DWORD g_lastTitleId;
static const DWORD g_guardBypasses[] = { 0x82D5C960, 0x82CE583C, 0x82D1E060, 0x82D1E084, 0x82D1E0AC, 0x82D1E0BC };
static VOID Patch(DWORD address, DWORD value) { if (MmIsAddressValid((PVOID)address)) { *(volatile DWORD*)address=value; FIVEX_DCACHE_FLUSH((PVOID)address); FIVEX_SYNC(); FIVEX_ISYNC(); } }
static VOID ApplyCompatibility() {
    // Same GTA TU compatibility fixes retained from FiveX: entity-create guards
    // and the 1024-entry script-guid pool constructor limit.
    for (DWORD i=0;i<ARRAYSIZE(g_guardBypasses);++i) Patch(g_guardBypasses[i],0x60000000);
    Patch(0x835326D0,0x38600400);
}
extern "C" VOID FiveXCallbackEnter() { InterlockedIncrement(&g_callbacks); }
extern "C" VOID FiveXCallbackLeave() { InterlockedDecrement(&g_callbacks); }
extern "C" BOOL FiveXCallbacksAllowed() { return g_stop == 0; }
extern "C" VOID FiveXRequestUnload() { /* FiveX has no in-game self-unload. */ }

static BOOL TryGetCurrentTitleId(DWORD* titleId) {
    if (!titleId) return FALSE;
    *titleId = 0;
    if (!g_getCurrentTitleId) {
        HANDLE xam = NULL;
        PVOID procedure = NULL;
        if (XexGetModuleHandle((PCHAR)"xam.xex", &xam) != 0 || !xam) return FALSE;
        if (XexGetProcedureAddress(xam, 0x1CF, &procedure) != 0 || !procedure) return FALSE;
        g_getCurrentTitleId = (FiveXGetCurrentTitleId)procedure;
    }
    *titleId = g_getCurrentTitleId();
    return TRUE;
}

static BOOL IsGtaReady() {
    DWORD titleId = 0;
    if (!TryGetCurrentTitleId(&titleId) || titleId != FIVEX_GTA_TITLE_ID) {
        g_gtaCandidateSince = 0;
        if (titleId != g_lastTitleId) {
            DbgPrint("[FiveX] Waiting for GTA V. Current Title ID=0x%08X.\n", titleId);
            g_lastTitleId = titleId;
        }
        return FALSE;
    }
    if (titleId != g_lastTitleId) {
        DbgPrint("[FiveX] GTA V detected. Title ID=0x%08X. Waiting for script dispatcher.\n", titleId);
        g_lastTitleId = titleId;
    }
    if (!MmIsAddressValid((PVOID)FIVEX_SCRIPT_DISPATCHER_ADDRESS) ||
        !MmIsAddressValid((PVOID)(FIVEX_SCRIPT_DISPATCHER_ADDRESS + 0x0F))) {
        g_gtaCandidateSince = 0;
        return FALSE;
    }
    const DWORD now = GetTickCount();
    if (!g_gtaCandidateSince) {
        g_gtaCandidateSince = now;
        return FALSE;
    }
    return (DWORD)(now - g_gtaCandidateSince) >= FIVEX_TITLE_STABILITY_MS;
}

static VOID Worker(VOID*) {
    while (!g_stop && !IsGtaReady()) Sleep(25);
    if (!g_stop) {
        ApplyCompatibility();
        if (FiveXNativeLoopInitialize()) while (!g_stop) Sleep(100);
    }
    FiveXNativeLoopShutdown();
    ExTerminateThread(0);
}
extern "C" BOOL WINAPI FiveXEntry(HANDLE module, DWORD reason, LPVOID) {
    if(reason==DLL_PROCESS_ATTACH) {
        g_module=module;
        g_stop=0;
        g_callbacks=0;
        g_getCurrentTitleId=NULL;
        g_gtaCandidateSince=0;
        g_lastTitleId=0xFFFFFFFF;
        if (!XapiInitHeap() || !_mtinit()) return FALSE;
        HANDLE thread=NULL;
        DWORD threadId=0;
        DWORD status=ExCreateThread(&thread,FIVEX_WORKER_STACK_SIZE,&threadId,
            (PVOID)XapiThreadStartup,(LPTHREAD_START_ROUTINE)Worker,NULL,
            FIVEX_EX_CREATE_FLAG_SYSTEM);
        if(status!=0 || !thread) return FALSE;
        if(ResumeThread(thread)==(DWORD)-1) { CloseHandle(thread); return FALSE; }
        CloseHandle(thread);
    }
    if(reason==DLL_PROCESS_DETACH) { g_stop=1; MemoryBarrier(); }
    return TRUE;
}
