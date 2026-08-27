#pragma once

#include "../FiveXKernel.h"

namespace Helpers {
    inline BOOL HasElapsed(DWORD now, DWORD deadline) { return (LONG)(now - deadline) >= 0; }
    inline BOOL HasElapsed(DWORD deadline) { return HasElapsed(GetTickCount(), deadline); }
}
