#pragma once

#include "FileIO.h"

BOOL FiveXPathsInitialize();
HRESULT FiveXMountHddPath();
const CHAR* FiveXPathRoot();
const CHAR* FiveXPathConfig();
const CHAR* FiveXPathData();
const CHAR* FiveXPathLists();
const CHAR* FiveXPathLogs();
const CHAR* FiveXPathThemes();
const CHAR* FiveXPathRpfs();
const CHAR* FiveXPathOutfits();
const CHAR* FiveXPathTeleports();
const CHAR* FiveXPathRecentPlayers();
const CHAR* FiveXPathLanguages();
const CHAR* FiveXPathResources();
FiveXFileResult FiveXPathBuild(CHAR* output, DWORD outputSize, const CHAR* basePath, const CHAR* relativePath);
