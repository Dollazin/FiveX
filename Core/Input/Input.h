#pragma once

#include "../../FiveXKernel.h"

BOOL FiveXInputInitialize();
VOID FiveXInputUpdate();
VOID FiveXInputShutdown();
BOOL FiveXInputConnected();
BOOL FiveXInputHeld(WORD buttons);
BOOL FiveXInputPressed(WORD buttons);
BOOL FiveXInputPressedOrRepeated(WORD button, DWORD initialDelay, DWORD repeatDelay);
BOOL FiveXInputAnyHeld(WORD buttons);
