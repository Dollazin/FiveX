#pragma once

#include "../../FiveXKernel.h"

#define FIVEX_MAX_PATH 260

enum FiveXFileResult {
	FiveXFileOk = 0,
	FiveXFileInvalidArgument,
	FiveXFileNotFound,
	FiveXFileOpenFailed,
	FiveXFileReadFailed,
	FiveXFileWriteFailed,
	FiveXFileDeleteFailed,
	FiveXFileReplaceFailed,
	FiveXFileEnumerateFailed,
	FiveXFileBufferTooSmall,
	FiveXFilePathTooLong
};

struct FiveXFileReader {
	HANDLE Handle;
};

struct FiveXFileWriter {
	HANDLE Handle;
};

typedef BOOL(*FiveXFileEnumerateCallback)(const CHAR* fileName, DWORD attributes, PVOID context);

BOOL FiveXFileInitialize();
VOID FiveXFileShutdown();
BOOL FiveXFileExists(const CHAR* path);
BOOL FiveXDirectoryExists(const CHAR* path);
FiveXFileResult FiveXEnsureDirectory(const CHAR* path);
FiveXFileResult FiveXEnsureDirectoryTree(const CHAR* path);
FiveXFileResult FiveXFileOpenRead(const CHAR* path, FiveXFileReader* reader);
FiveXFileResult FiveXFileRead(FiveXFileReader* reader, PVOID buffer, DWORD capacity, DWORD* bytesRead);
VOID FiveXFileCloseRead(FiveXFileReader* reader);
FiveXFileResult FiveXFileOpenWrite(const CHAR* path, BOOL append, FiveXFileWriter* writer);
FiveXFileResult FiveXFileWrite(FiveXFileWriter* writer, const VOID* data, DWORD size);
VOID FiveXFileCloseWrite(FiveXFileWriter* writer);
FiveXFileResult FiveXFileReadAll(const CHAR* path, PVOID buffer, DWORD capacity, DWORD* size);
FiveXFileResult FiveXFileWriteAll(const CHAR* path, const VOID* data, DWORD size);
FiveXFileResult FiveXFileAppend(const CHAR* path, const VOID* data, DWORD size);
FiveXFileResult FiveXFileDelete(const CHAR* path);
FiveXFileResult FiveXFileReplace(const CHAR* temporaryPath, const CHAR* destinationPath);
FiveXFileResult FiveXFileEnumerate(const CHAR* searchPattern, FiveXFileEnumerateCallback callback, PVOID context, DWORD* count);
