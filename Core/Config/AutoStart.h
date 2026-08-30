#pragma once

#include "../../FiveXKernel.h"

BOOL FiveXAutoStartInitialize();
BOOL FiveXAutoStartContains(const CHAR* resourceName);
BOOL FiveXAutoStartSet(const CHAR* resourceName, BOOL enabled);
const CHAR* FiveXAutoStartPath();
