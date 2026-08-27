#pragma once

#include "../../FiveXKernel.h"

namespace Notify {
	BOOL Error(const CHAR* format, ...);
	BOOL Success(const CHAR* format, ...);
	BOOL Default(const CHAR* format, ...);
}
