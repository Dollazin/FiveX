/* Xbox 360 CRT floating-point printf replacement used by embedded Lua. */
#include "lxboxfmt.h"

#include <math.h>
#include <string.h>

typedef unsigned __int64 FiveXLuaUnsigned64;

static int append_char(char* output, size_t size, int position, char value) {
  if ((size_t)(position + 1) >= size)
    return position;
  output[position++] = value;
  output[position] = '\0';
  return position;
}

static int append_text(char* output, size_t size, int position, const char* value) {
  while (value && *value && (size_t)(position + 1) < size)
    output[position++] = *value++;
  if (size)
    output[position < (int)size ? position : (int)size - 1] = '\0';
  return position;
}

static int append_unsigned(char* output, size_t size, int position,
                           FiveXLuaUnsigned64 value, int minimumDigits) {
  char reversed[32];
  int count = 0;
  do {
    reversed[count++] = (char)('0' + (value % 10));
    value /= 10;
  } while (value && count < (int)sizeof(reversed));
  while (count < minimumDigits && count < (int)sizeof(reversed))
    reversed[count++] = '0';
  while (count > 0)
    position = append_char(output, size, position, reversed[--count]);
  return position;
}

static FiveXLuaUnsigned64 decimal_multiplier(int precision) {
  FiveXLuaUnsigned64 result = 1;
  while (precision-- > 0)
    result *= 10;
  return result;
}

static int normalize_number(double* value) {
  int exponent = 0;
  if (*value == 0.0)
    return 0;
  while (*value >= 10.0) {
    *value /= 10.0;
    ++exponent;
  }
  while (*value < 1.0) {
    *value *= 10.0;
    --exponent;
  }
  return exponent;
}

static int format_fixed_absolute(char* output, size_t size, double value,
                                 int precision) {
  FiveXLuaUnsigned64 multiplier;
  FiveXLuaUnsigned64 scaled;
  FiveXLuaUnsigned64 whole;
  FiveXLuaUnsigned64 fraction;
  int position = 0;
  if (precision < 0) precision = 0;
  if (precision > 14) precision = 14;
  multiplier = decimal_multiplier(precision);
  if (value > (9.0e18 / (double)multiplier))
    return -1;
  scaled = (FiveXLuaUnsigned64)(value * (double)multiplier + 0.5);
  whole = scaled / multiplier;
  fraction = scaled % multiplier;
  output[0] = '\0';
  position = append_unsigned(output, size, position, whole, 1);
  if (precision > 0) {
    position = append_char(output, size, position, '.');
    position = append_unsigned(output, size, position, fraction, precision);
  }
  return position;
}

static int format_scientific_absolute(char* output, size_t size, double value,
                                      int precision, int upper) {
  char mantissa[96];
  int exponent;
  int mantissaLength;
  int position = 0;
  if (precision < 0) precision = 6;
  if (precision > 14) precision = 14;
  exponent = normalize_number(&value);
  mantissaLength = format_fixed_absolute(mantissa, sizeof(mantissa), value, precision);
  if (mantissaLength < 0)
    return 0;
  if (mantissa[0] == '1' && mantissa[1] == '0' &&
      (mantissa[2] == '.' || mantissa[2] == '\0')) {
	value = 1.0;
    ++exponent;
    mantissaLength = format_fixed_absolute(mantissa, sizeof(mantissa), value, precision);
  }
  output[0] = '\0';
  position = append_text(output, size, position, mantissa);
  position = append_char(output, size, position, upper ? 'E' : 'e');
  position = append_char(output, size, position, exponent < 0 ? '-' : '+');
  if (exponent < 0) exponent = -exponent;
  position = append_unsigned(output, size, position,
                             (FiveXLuaUnsigned64)exponent, 2);
  return position;
}

static void trim_fraction(char* value) {
  char* exponent = strchr(value, 'e');
  char* upperExponent = strchr(value, 'E');
  char* decimal = strchr(value, '.');
  char* end;
  char* suffix;
  if (!exponent || (upperExponent && upperExponent < exponent))
    exponent = upperExponent;
  if (!decimal || (exponent && decimal > exponent))
    return;
  suffix = exponent;
  end = suffix ? suffix - 1 : value + strlen(value) - 1;
  while (end >= value && *end == '0')
    --end;
  if (end >= value && *end == '.')
    --end;
  if (suffix)
    memmove(end + 1, suffix, strlen(suffix) + 1);
  else
    end[1] = '\0';
}

static int format_general_absolute(char* output, size_t size, double value,
                                   int precision, int upper, int alternate) {
  double normalized;
  int exponent;
  int decimals;
  int length;
  if (precision <= 0) precision = 1;
  if (precision > 14) precision = 14;
  if (value == 0.0) {
    output[0] = '0'; output[1] = '\0';
    return 1;
  }
  normalized = value;
  exponent = normalize_number(&normalized);
  if (exponent < -4 || exponent >= precision)
    length = format_scientific_absolute(output, size, value, precision - 1, upper);
  else {
    decimals = precision - exponent - 1;
    if (decimals < 0) decimals = 0;
    length = format_fixed_absolute(output, size, value, decimals);
    if (length < 0)
      length = format_scientific_absolute(output, size, value, precision - 1, upper);
  }
  if (!alternate)
    trim_fraction(output);
  return (int)strlen(output);
}

static int copy_special(char* output, size_t size, double value, int upper) {
  const char* text;
  if (value != value)
    text = upper ? "NAN" : "nan";
  else if (value < 0.0)
    text = upper ? "-INF" : "-inf";
  else
    text = upper ? "INF" : "inf";
  output[0] = '\0';
  return append_text(output, size, 0, text);
}

int fivex_lua_formatnumber(char* buffer, size_t size,
                             const char* format, double value) {
  char raw[256];
  char specifier = 'g';
  int precision = -1;
  int width = 0;
  int left = 0;
  int zero = 0;
  int plus = 0;
  int space = 0;
  int alternate = 0;
  int negative;
  int upper;
  int rawLength;
  int prefixLength = 0;
  int padding;
  int position = 0;
  const char* cursor;
  if (!buffer || !size)
    return 0;
  buffer[0] = '\0';
  cursor = format ? format : "%g";
  if (*cursor == '%') ++cursor;
  while (*cursor == '-' || *cursor == '+' || *cursor == ' ' ||
         *cursor == '#' || *cursor == '0') {
    if (*cursor == '-') left = 1;
    else if (*cursor == '+') plus = 1;
    else if (*cursor == ' ') space = 1;
    else if (*cursor == '#') alternate = 1;
    else if (*cursor == '0') zero = 1;
    ++cursor;
  }
  while (*cursor >= '0' && *cursor <= '9') {
    width = width * 10 + (*cursor++ - '0');
    if (width > 200) width = 200;
  }
  if (*cursor == '.') {
    precision = 0;
    ++cursor;
    while (*cursor >= '0' && *cursor <= '9') {
      precision = precision * 10 + (*cursor++ - '0');
      if (precision > 14) precision = 14;
    }
  }
  while (*cursor && strchr("aAeEfFgG", *cursor) == NULL)
    ++cursor;
  if (*cursor) specifier = *cursor;
  upper = (specifier == 'A' || specifier == 'E' || specifier == 'F' || specifier == 'G');
  if (value != value || value == HUGE_VAL || value == -HUGE_VAL) {
    rawLength = copy_special(raw, sizeof(raw), value, upper);
    negative = raw[0] == '-';
  }
  else {
    double absoluteValue;
    negative = value < 0.0;
    absoluteValue = negative ? -value : value;
    if (specifier == 'f' || specifier == 'F') {
      if (precision < 0) precision = 6;
      rawLength = format_fixed_absolute(raw, sizeof(raw), absoluteValue, precision);
      if (rawLength < 0)
        rawLength = format_scientific_absolute(raw, sizeof(raw), absoluteValue,
                                               precision, upper);
    }
    else if (specifier == 'e' || specifier == 'E') {
      rawLength = format_scientific_absolute(raw, sizeof(raw), absoluteValue,
                                             precision < 0 ? 6 : precision, upper);
    }
    else {
      rawLength = format_general_absolute(raw, sizeof(raw), absoluteValue,
                                          precision < 0 ? 14 : precision,
                                          upper, alternate);
    }
  }
  if (!negative && plus) prefixLength = 1;
  else if (!negative && space) prefixLength = 1;
  else if (negative && raw[0] != '-') prefixLength = 1;
  padding = width - rawLength - prefixLength;
  if (padding < 0) padding = 0;
  if (!left && !zero)
    while (padding-- > 0) position = append_char(buffer, size, position, ' ');
  if (negative && raw[0] != '-') position = append_char(buffer, size, position, '-');
  else if (!negative && plus) position = append_char(buffer, size, position, '+');
  else if (!negative && space) position = append_char(buffer, size, position, ' ');
  if (!left && zero)
    while (padding-- > 0) position = append_char(buffer, size, position, '0');
  position = append_text(buffer, size, position, raw);
  if (left)
    while (padding-- > 0) position = append_char(buffer, size, position, ' ');
  return position;
}

int fivex_lua_number2str(char* buffer, size_t size, double value) {
  return fivex_lua_formatnumber(buffer, size, "%.14g", value);
}
