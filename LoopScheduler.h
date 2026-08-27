#pragma once

#include "FiveXKernel.h"

#ifndef FIVEX_MAX_LOOPS
#define FIVEX_MAX_LOOPS 32
#endif

#ifndef FIVEX_LOOP_STACK_SIZE
#define FIVEX_LOOP_STACK_SIZE (64 * 1024)
#endif

typedef VOID(*FiveXLoopEntry)();

VOID FiveXLoopPrepare();
BOOL FiveXRegisterLoop(FiveXLoopEntry entry, const CHAR* name);
VOID FiveXLoopTick();
VOID FiveXLoopRequestStop();
BOOL FiveXLoopsAreStopped();
BOOL FiveXCanWait();
BOOL FiveXStopWasRequested();
VOID FiveXWait(DWORD milliseconds);

// Cooperative yield. Use only from a function registered with FiveXRegisterLoop.
inline VOID Wait(DWORD milliseconds) {
	FiveXWait(milliseconds);
}
