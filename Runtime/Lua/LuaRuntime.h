#pragma once

#include "../../FiveXKernel.h"

enum FiveXLuaResourceState {
	FiveXLuaResourceStopped = 0,
	FiveXLuaResourceStarting,
	FiveXLuaResourceStarted,
	FiveXLuaResourceFailed
};

struct FiveXLuaResourceInfo {
	CHAR Name[64];
	FiveXLuaResourceState State;
	INT ScriptCount;
	INT ThreadCount;
	SIZE_T MemoryUsed;
	SIZE_T MemoryLimit;
};

BOOL FiveXLuaRuntimeInitialize();
VOID FiveXLuaRuntimeTick();
VOID FiveXLuaRuntimeShutdown();

VOID FiveXLuaResourceRefresh();
INT FiveXLuaResourceCount();
const FiveXLuaResourceInfo* FiveXLuaResourceGet(INT index);
const CHAR* FiveXLuaResourceStateText(INT index);
BOOL FiveXLuaResourceStart(const CHAR* name);
BOOL FiveXLuaResourceStop(const CHAR* name);
BOOL FiveXLuaResourceRestart(const CHAR* name);
VOID FiveXLuaResourceStopAll();
