#include "NumberFormat.h"
#include <stdio.h>

static DWORD DecimalMultiplier(INT decimals) {
	static const DWORD multipliers[] = { 1, 10, 100, 1000, 10000, 100000, 1000000 };
	return multipliers[decimals];
}

BOOL FiveXFormatFloat(CHAR* output, DWORD outputSize, FLOAT value, INT decimals) {
	if (!output || !outputSize)
		return FALSE;
	if (decimals < 0)
		decimals = 0;
	if (decimals > 6)
		decimals = 6;
	BOOL negative = value < 0.0f;
	FLOAT absoluteValue = negative ? -value : value;
	DWORD multiplier = DecimalMultiplier(decimals);
	DWORD scaledValue = (DWORD)((absoluteValue * multiplier) + 0.5f);
	DWORD wholeValue = scaledValue / multiplier;
	DWORD decimalValue = scaledValue % multiplier;
	INT written = decimals == 0
		? sprintf_s(output, outputSize, "%s%u", negative ? "-" : "", wholeValue)
		: sprintf_s(output, outputSize, "%s%u.%0*u", negative ? "-" : "", wholeValue, decimals, decimalValue);
	if (written <= 0 || (DWORD)written >= outputSize) {
		output[0] = '\0';
		return FALSE;
	}
	return TRUE;
}
