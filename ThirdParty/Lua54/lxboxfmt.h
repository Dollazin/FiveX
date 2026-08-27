#ifndef lxboxfmt_h
#define lxboxfmt_h

#include <stddef.h>

#if defined(__cplusplus)
extern "C" {
#endif

int fivex_lua_number2str(char* buffer, size_t size, double value);
int fivex_lua_formatnumber(char* buffer, size_t size, const char* format, double value);

#if defined(__cplusplus)
}
#endif

#endif
