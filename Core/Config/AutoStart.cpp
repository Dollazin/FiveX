#include "AutoStart.h"
#include "../Storage/FileIO.h"
#include "../Storage/Paths.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIVEX_AUTOSTART_MAX_RESOURCES 64
#define FIVEX_AUTOSTART_NAME_SIZE 64
#define FIVEX_AUTOSTART_FILE_CAPACITY 8192

static CHAR (*g_autoStartNames)[FIVEX_AUTOSTART_NAME_SIZE];
static INT g_autoStartCount;
static CHAR g_autoStartPath[FIVEX_MAX_PATH];

static BOOL EnsureNameStorage() {
	if (g_autoStartNames)
		return TRUE;
	g_autoStartNames = (CHAR (*)[FIVEX_AUTOSTART_NAME_SIZE])malloc(
		FIVEX_AUTOSTART_MAX_RESOURCES * FIVEX_AUTOSTART_NAME_SIZE);
	if (!g_autoStartNames)
		return FALSE;
	ZeroMemory(g_autoStartNames,
		FIVEX_AUTOSTART_MAX_RESOURCES * FIVEX_AUTOSTART_NAME_SIZE);
	return TRUE;
}

static BOOL IsSafeResourceName(const CHAR* name) {
	if (!name || !name[0] || strlen(name) >= FIVEX_AUTOSTART_NAME_SIZE)
		return FALSE;
	for (const CHAR* position = name; *position; ++position) {
		const CHAR value = *position;
		if (!((value >= 'a' && value <= 'z') ||
			  (value >= 'A' && value <= 'Z') ||
			  (value >= '0' && value <= '9') ||
			  value == '_' || value == '-' || value == '.'))
			return FALSE;
	}
	return TRUE;
}

static CHAR* Trim(CHAR* value) {
	if (!value)
		return value;
	while (*value == ' ' || *value == '\t')
		++value;
	CHAR* end = value + strlen(value);
	while (end > value &&
		(end[-1] == ' ' || end[-1] == '\t' || end[-1] == '\r'))
		--end;
	*end = '\0';
	return value;
}

static INT FindName(const CHAR* resourceName) {
	if (!resourceName || !g_autoStartNames)
		return -1;
	for (INT index = 0; index < g_autoStartCount; ++index) {
		if (_stricmp(g_autoStartNames[index], resourceName) == 0)
			return index;
	}
	return -1;
}

static BOOL Save() {
	CHAR* output = (CHAR*)malloc(FIVEX_AUTOSTART_FILE_CAPACITY);
	if (!output)
		return FALSE;
	INT used = sprintf_s(output, FIVEX_AUTOSTART_FILE_CAPACITY,
		"; FiveX resource auto-start\r\n[AutoStart]\r\n");
	if (used < 0) {
		free(output);
		return FALSE;
	}

	for (INT index = 0; index < g_autoStartCount; ++index) {
		const INT written = sprintf_s(
			output + used,
			FIVEX_AUTOSTART_FILE_CAPACITY - used,
			"%s=1\r\n",
			g_autoStartNames[index]);
		if (written < 0) {
			free(output);
			return FALSE;
		}
		used += written;
	}

	const FiveXFileResult result = FiveXFileWriteAll(
		g_autoStartPath, output, (DWORD)used);
	free(output);
	if (result != FiveXFileOk) {
		DbgPrint("[FiveX][AutoStart] Unable to save %s result=%d\n",
			g_autoStartPath, result);
		return FALSE;
	}
	return TRUE;
}

BOOL FiveXAutoStartInitialize() {
	if (!EnsureNameStorage())
		return FALSE;
	ZeroMemory(g_autoStartNames,
		FIVEX_AUTOSTART_MAX_RESOURCES * FIVEX_AUTOSTART_NAME_SIZE);
	g_autoStartCount = 0;
	if (FiveXPathBuild(g_autoStartPath, sizeof(g_autoStartPath),
		FiveXPathConfig(), "FiveX.ini") != FiveXFileOk)
		return FALSE;

	CHAR* input = (CHAR*)malloc(FIVEX_AUTOSTART_FILE_CAPACITY);
	if (!input)
		return FALSE;
	DWORD size = 0;
	const FiveXFileResult result = FiveXFileReadAll(
		g_autoStartPath, input, FIVEX_AUTOSTART_FILE_CAPACITY - 1, &size);
	if (result == FiveXFileNotFound) {
		free(input);
		DbgPrint("[FiveX][AutoStart] Creating %s\n", g_autoStartPath);
		if (!Save())
			DbgPrint("[FiveX][AutoStart] Continuing without persistence.\n");
		return TRUE;
	}
	if (result != FiveXFileOk) {
		free(input);
		DbgPrint("[FiveX][AutoStart] Unable to read %s result=%d\n",
			g_autoStartPath, result);
		DbgPrint("[FiveX][AutoStart] Continuing with an empty auto-start list.\n");
		return TRUE;
	}
	input[size] = '\0';

	BOOL inAutoStartSection = FALSE;
	CHAR* cursor = input;
	while (*cursor) {
		CHAR* line = cursor;
		while (*cursor && *cursor != '\n')
			++cursor;
		if (*cursor)
			*cursor++ = '\0';
		line = Trim(line);
		if (!line[0] || line[0] == ';' || line[0] == '#')
			continue;
		if (line[0] == '[') {
			CHAR* end = strchr(line, ']');
			if (end)
				*end = '\0';
			inAutoStartSection = end && _stricmp(Trim(line + 1), "AutoStart") == 0;
			continue;
		}
		if (!inAutoStartSection)
			continue;
		CHAR* equals = strchr(line, '=');
		if (!equals)
			continue;
		*equals = '\0';
		CHAR* name = Trim(line);
		CHAR* enabled = Trim(equals + 1);
		const BOOL active = strcmp(enabled, "1") == 0 ||
			_stricmp(enabled, "true") == 0 ||
			_stricmp(enabled, "yes") == 0 ||
			_stricmp(enabled, "on") == 0;
		if (active && IsSafeResourceName(name) && FindName(name) < 0 &&
			g_autoStartCount < FIVEX_AUTOSTART_MAX_RESOURCES) {
			strncpy_s(g_autoStartNames[g_autoStartCount],
				sizeof(g_autoStartNames[g_autoStartCount]), name, _TRUNCATE);
			++g_autoStartCount;
		}
	}

	DbgPrint("[FiveX][AutoStart] Loaded=%d path=%s\n",
		g_autoStartCount, g_autoStartPath);
	free(input);
	return TRUE;
}

BOOL FiveXAutoStartContains(const CHAR* resourceName) {
	return FindName(resourceName) >= 0;
}

BOOL FiveXAutoStartSet(const CHAR* resourceName, BOOL enabled) {
	if (!IsSafeResourceName(resourceName))
		return FALSE;
	if (!g_autoStartNames && !EnsureNameStorage())
		return FALSE;
	const INT existing = FindName(resourceName);
	if (enabled) {
		if (existing >= 0)
			return TRUE;
		if (g_autoStartCount >= FIVEX_AUTOSTART_MAX_RESOURCES)
			return FALSE;
		strncpy_s(g_autoStartNames[g_autoStartCount],
			sizeof(g_autoStartNames[g_autoStartCount]), resourceName, _TRUNCATE);
		++g_autoStartCount;
		if (Save())
			return TRUE;
		--g_autoStartCount;
		g_autoStartNames[g_autoStartCount][0] = '\0';
		return FALSE;
	}

	if (existing < 0)
		return TRUE;
	CHAR removed[FIVEX_AUTOSTART_NAME_SIZE];
	strncpy_s(removed, sizeof(removed), g_autoStartNames[existing], _TRUNCATE);
	for (INT index = existing; index + 1 < g_autoStartCount; ++index)
		memcpy(g_autoStartNames[index], g_autoStartNames[index + 1],
			sizeof(g_autoStartNames[index]));
	--g_autoStartCount;
	ZeroMemory(g_autoStartNames[g_autoStartCount],
		sizeof(g_autoStartNames[g_autoStartCount]));
	if (Save())
		return TRUE;
	for (INT index = g_autoStartCount; index > existing; --index)
		memcpy(g_autoStartNames[index], g_autoStartNames[index - 1],
			sizeof(g_autoStartNames[index]));
	strncpy_s(g_autoStartNames[existing], sizeof(g_autoStartNames[existing]),
		removed, _TRUNCATE);
	++g_autoStartCount;
	return FALSE;
}

const CHAR* FiveXAutoStartPath() {
	return g_autoStartPath;
}
