#include "Notification.h"
#include "../../GameNatives.h"
#include <stdarg.h>
#include <stdio.h>

static BOOL ShowV(const CHAR* format, va_list args) {
    CHAR text[256];
    vsnprintf(text, sizeof(text), format, args);
    SetNotificationTextEntry("STRING");
    AddTextComponentString(text);
    DrawNotification(FALSE, FALSE);
    return TRUE;
}
BOOL Notify::Error(const CHAR* f, ...) { va_list a; va_start(a,f); BOOL r=ShowV(f,a); va_end(a); return r; }
BOOL Notify::Success(const CHAR* f, ...) { va_list a; va_start(a,f); BOOL r=ShowV(f,a); va_end(a); return r; }
BOOL Notify::Default(const CHAR* f, ...) { va_list a; va_start(a,f); BOOL r=ShowV(f,a); va_end(a); return r; }
