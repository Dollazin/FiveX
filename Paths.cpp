#include "Core/Storage/Paths.h"
#include <stdio.h>
#include <string.h>

static const CHAR g_root[] = "Hdd:\\FiveX";
static const CHAR g_resources[] = "Hdd:\\FiveX\\Resources";
static const CHAR g_logs[] = "Hdd:\\FiveX\\Logs";

static FIVEX_ANSI_STRING MakeAnsiString(const CHAR* value) {
    FIVEX_ANSI_STRING result;
    result.Length = (USHORT)strlen(value);
    result.MaximumLength = result.Length + 1;
    result.Buffer = const_cast<PCHAR>(value);
    return result;
}

BOOL FiveXPathsInitialize() {
    const HRESULT mountResult = FiveXMountHddPath();
    if (FAILED(mountResult)) {
        DbgPrint("[FiveX] Hdd mount failed: result=0x%08X.\n", mountResult);
        return FALSE;
    }

    const CHAR* directories[] = { g_root, g_resources, g_logs };
    for (DWORD index = 0; index < ARRAYSIZE(directories); ++index) {
        const FiveXFileResult result = FiveXEnsureDirectory(directories[index]);
        DbgPrint("[FiveX] Storage directory[%lu] result=%d path=%s\n",
            index, result, directories[index]);
        if (result != FiveXFileOk)
            return FALSE;
    }
    return TRUE;
}

HRESULT FiveXMountHddPath() {
    CHAR linkPath[FIVEX_MAX_PATH];
    const CHAR* format = KeGetCurrentProcessType() == 2
        ? "\\System??\\%s"
        : "\\??\\%s";
    sprintf_s(linkPath, sizeof(linkPath), format, "Hdd:");

    FIVEX_ANSI_STRING deviceName = MakeAnsiString("\\Device\\Harddisk0\\Partition1");
    FIVEX_ANSI_STRING linkName = MakeAnsiString(linkPath);
    ObDeleteSymbolicLink(&linkName);
    const HRESULT result = ObCreateSymbolicLink(&linkName, &deviceName);
    DbgPrint("[FiveX] Hdd mount result=%ld link=%s\n", result, linkPath);
    return result;
}
const CHAR* FiveXPathRoot() { return g_root; }
const CHAR* FiveXPathResources() { return g_resources; }
const CHAR* FiveXPathLogs() { return g_logs; }
const CHAR* FiveXPathConfig() { return g_root; }
const CHAR* FiveXPathData() { return g_root; }
const CHAR* FiveXPathLists() { return g_root; }
const CHAR* FiveXPathThemes() { return g_root; }
const CHAR* FiveXPathRpfs() { return g_root; }
const CHAR* FiveXPathOutfits() { return g_root; }
const CHAR* FiveXPathTeleports() { return g_root; }
const CHAR* FiveXPathRecentPlayers() { return g_root; }
const CHAR* FiveXPathLanguages() { return g_root; }
FiveXFileResult FiveXPathBuild(CHAR* out, DWORD size, const CHAR* base, const CHAR* relative) {
    if (!out || !size || !base || !relative || sprintf_s(out, size, "%s\\%s", base, relative) < 0) return FiveXFilePathTooLong;
    return FiveXFileOk;
}
