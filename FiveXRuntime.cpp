#include "FiveXRuntime.h"
#include "Runtime/Lua/LuaRuntime.h"
#include "Core/Storage/FileIO.h"
#include "Core/Storage/Paths.h"
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
BOOL FiveXRuntimeInitialize() { return FiveXFileInitialize() && FiveXPathsInitialize() && FiveXInputInitialize() && FiveXLuaRuntimeInitialize() && FiveXMenuInitialize(); }
VOID FiveXRuntimeShutdown() { FiveXLuaResourceStopAll(); FiveXMenuShutdown(); FiveXLuaRuntimeShutdown(); FiveXInputShutdown(); FiveXFileShutdown(); }
VOID FiveXRegisterLoops() { FiveXRegisterLoop(FiveXLoop, "fivex"); }
