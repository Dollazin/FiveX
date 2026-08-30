#include "FiveXRuntime.h"
#include "Runtime/Lua/LuaRuntime.h"
#include "Core/Storage/FileIO.h"
#include "Core/Storage/Paths.h"
#include "Core/Config/AutoStart.h"
#include "Core/UI/Notification.h"
#include "Core/Input/Input.h"
#include "FiveXMenu.h"
#include "LoopScheduler.h"

static VOID FiveXLoop() {
	for (;;) {
		FiveXInputUpdate();
		FiveXMenuTick();
		FiveXLuaRuntimeTick();
		FiveXWait(0);
	}
}
BOOL FiveXRuntimeInitialize() {
	if (!FiveXFileInitialize() || !FiveXPathsInitialize())
		return FALSE;
	// Auto-start persistence is optional. A missing, damaged or temporarily
	// unavailable INI must never prevent the runtime itself from loading.
	if (!FiveXAutoStartInitialize())
		DbgPrint("[FiveX][AutoStart] Initialization failed; runtime will continue.\n");
	return FiveXInputInitialize() && FiveXLuaRuntimeInitialize() && FiveXMenuInitialize();
}
VOID FiveXRuntimeShutdown() { FiveXLuaResourceStopAll(); FiveXMenuShutdown(); FiveXLuaRuntimeShutdown(); FiveXInputShutdown(); FiveXFileShutdown(); }
VOID FiveXRegisterLoops() { FiveXRegisterLoop(FiveXLoop, "fivex"); }
