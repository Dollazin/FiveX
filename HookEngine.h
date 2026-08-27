#pragma once

#include "FiveXKernel.h"

struct FiveXHook {
	DWORD Address;
	DWORD Original[4];
	DWORD Patched[4];
	DWORD Trampoline[8];
	BOOL Installed;
};

VOID FiveXHookReset(FiveXHook* hook);
BOOL FiveXHookInstall(FiveXHook* hook, DWORD address, PVOID replacement, PVOID* original);
BOOL FiveXHookRemove(FiveXHook* hook);
