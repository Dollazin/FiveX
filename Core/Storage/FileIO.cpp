#include "FileIO.h"
#include "../Global.h"
#include <string.h>

static volatile LONG g_fileInitialized;

static VOID ResetReader(FiveXFileReader* reader) {
	if (reader)
		reader->Handle = INVALID_HANDLE_VALUE;
}

static VOID ResetWriter(FiveXFileWriter* writer) {
	if (writer)
		writer->Handle = INVALID_HANDLE_VALUE;
}

BOOL FiveXFileInitialize() {
	InterlockedExchange(&g_fileInitialized, 1);
	return TRUE;
}

VOID FiveXFileShutdown() {
	// File handles are operation-owned and never retained by this module.
	InterlockedExchange(&g_fileInitialized, 0);
}

BOOL FiveXFileExists(const CHAR* path) {
	if (!path || !path[0])
		return FALSE;
	DWORD attributes = GetFileAttributes(path);
	return attributes != (DWORD)-1 && (attributes & FILE_ATTRIBUTE_DIRECTORY) == 0;
}

BOOL FiveXDirectoryExists(const CHAR* path) {
	if (!path || !path[0])
		return FALSE;
	DWORD attributes = GetFileAttributes(path);
	return attributes != (DWORD)-1 && (attributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
}

FiveXFileResult FiveXEnsureDirectory(const CHAR* path) {
	if (!path || !path[0])
		return FiveXFileInvalidArgument;
	if (FiveXDirectoryExists(path))
		return FiveXFileOk;
	if (CreateDirectory(path, NULL)) {
		DbgPrint("[FiveX] Directory created: %s\n", path);
		return FiveXFileOk;
	}
	const DWORD error = GetLastError();
	if (FiveXDirectoryExists(path))
		return FiveXFileOk;
	DbgPrint("[FiveX] Directory create failed: %s Error=%lu\n", path, error);
	return FiveXFileWriteFailed;
}

FiveXFileResult FiveXEnsureDirectoryTree(const CHAR* path) {
	if (!path || !path[0])
		return FiveXFileInvalidArgument;
	DWORD length = (DWORD)strlen(path);
	if (length >= FIVEX_MAX_PATH)
		return FiveXFilePathTooLong;

	CHAR current[FIVEX_MAX_PATH];
	strncpy_s(current, sizeof(current), path, _TRUNCATE);
	for (DWORD index = 0; index < length; ++index) {
		// Skip the separator immediately after an Xbox mount name (for example Hdd:\\).
		if ((current[index] == '\\' || current[index] == '/') && index > 4) {
			CHAR separator = current[index];
			current[index] = '\0';
			FiveXFileResult result = FiveXEnsureDirectory(current);
			current[index] = separator;
			if (result != FiveXFileOk)
				return result;
		}
	}
	return FiveXEnsureDirectory(current);
}

FiveXFileResult FiveXFileOpenRead(const CHAR* path, FiveXFileReader* reader) {
	if (!path || !path[0] || !reader)
		return FiveXFileInvalidArgument;
	ResetReader(reader);
	reader->Handle = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (reader->Handle == INVALID_HANDLE_VALUE)
		return FiveXFileExists(path) ? FiveXFileOpenFailed : FiveXFileNotFound;
	return FiveXFileOk;
}

FiveXFileResult FiveXFileRead(FiveXFileReader* reader, PVOID buffer, DWORD capacity, DWORD* bytesRead) {
	if (bytesRead)
		*bytesRead = 0;
	if (!reader || reader->Handle == INVALID_HANDLE_VALUE || !buffer || !capacity)
		return FiveXFileInvalidArgument;
	DWORD read = 0;
	if (!ReadFile(reader->Handle, buffer, capacity, &read, NULL))
		return FiveXFileReadFailed;
	if (bytesRead)
		*bytesRead = read;
	return FiveXFileOk;
}

VOID FiveXFileCloseRead(FiveXFileReader* reader) {
	if (reader && reader->Handle != INVALID_HANDLE_VALUE)
		CloseHandle(reader->Handle);
	ResetReader(reader);
}

FiveXFileResult FiveXFileOpenWrite(const CHAR* path, BOOL append, FiveXFileWriter* writer) {
	if (!path || !path[0] || !writer)
		return FiveXFileInvalidArgument;
	ResetWriter(writer);
	writer->Handle = CreateFile(path, GENERIC_WRITE, FILE_SHARE_READ, NULL, append ? OPEN_ALWAYS : CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (writer->Handle == INVALID_HANDLE_VALUE)
		return FiveXFileOpenFailed;
	if (append && SetFilePointer(writer->Handle, 0, NULL, FILE_END) == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR) {
		FiveXFileCloseWrite(writer);
		return FiveXFileOpenFailed;
	}
	return FiveXFileOk;
}

FiveXFileResult FiveXFileWrite(FiveXFileWriter* writer, const VOID* data, DWORD size) {
	if (!writer || writer->Handle == INVALID_HANDLE_VALUE || (!data && size))
		return FiveXFileInvalidArgument;
	if (!size)
		return FiveXFileOk;
	DWORD written = 0;
	if (!WriteFile(writer->Handle, data, size, &written, NULL) || written != size)
		return FiveXFileWriteFailed;
	return FiveXFileOk;
}

VOID FiveXFileCloseWrite(FiveXFileWriter* writer) {
	if (writer && writer->Handle != INVALID_HANDLE_VALUE)
		CloseHandle(writer->Handle);
	ResetWriter(writer);
}

FiveXFileResult FiveXFileReadAll(const CHAR* path, PVOID buffer, DWORD capacity, DWORD* size) {
	if (size)
		*size = 0;
	if (!buffer || !capacity)
		return FiveXFileInvalidArgument;
	FiveXFileReader reader;
	FiveXFileResult result = FiveXFileOpenRead(path, &reader);
	if (result != FiveXFileOk)
		return result;
	DWORD fileSize = GetFileSize(reader.Handle, NULL);
	if (fileSize == INVALID_FILE_SIZE && GetLastError() != NO_ERROR) {
		FiveXFileCloseRead(&reader);
		return FiveXFileReadFailed;
	}
	if (fileSize > capacity) {
		FiveXFileCloseRead(&reader);
		return FiveXFileBufferTooSmall;
	}
	DWORD read = 0;
	result = fileSize ? FiveXFileRead(&reader, buffer, fileSize, &read) : FiveXFileOk;
	FiveXFileCloseRead(&reader);
	if (result == FiveXFileOk && size)
		*size = read;
	return result;
}

FiveXFileResult FiveXFileWriteAll(const CHAR* path, const VOID* data, DWORD size) {
	FiveXFileWriter writer;
	FiveXFileResult result = FiveXFileOpenWrite(path, FALSE, &writer);
	if (result != FiveXFileOk)
		return result;
	result = FiveXFileWrite(&writer, data, size);
	FiveXFileCloseWrite(&writer);
	return result;
}

FiveXFileResult FiveXFileAppend(const CHAR* path, const VOID* data, DWORD size) {
	FiveXFileWriter writer;
	FiveXFileResult result = FiveXFileOpenWrite(path, TRUE, &writer);
	if (result != FiveXFileOk)
		return result;
	result = FiveXFileWrite(&writer, data, size);
	FiveXFileCloseWrite(&writer);
	return result;
}

FiveXFileResult FiveXFileDelete(const CHAR* path) {
	if (!path || !path[0])
		return FiveXFileInvalidArgument;
	if (!FiveXFileExists(path))
		return FiveXFileNotFound;
	return DeleteFile(path) ? FiveXFileOk : FiveXFileDeleteFailed;
}

FiveXFileResult FiveXFileReplace(const CHAR* temporaryPath, const CHAR* destinationPath) {
	if (!temporaryPath || !temporaryPath[0] || !destinationPath || !destinationPath[0])
		return FiveXFileInvalidArgument;
	if (!FiveXFileExists(temporaryPath))
		return FiveXFileNotFound;
	if (MoveFileExA(temporaryPath, destinationPath,
		MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH))
		return FiveXFileOk;
	DbgPrint("[FiveX] Atomic file replace failed: %s -> %s Error=%lu\n",
		temporaryPath, destinationPath, GetLastError());
	return FiveXFileReplaceFailed;
}

FiveXFileResult FiveXFileEnumerate(const CHAR* searchPattern, FiveXFileEnumerateCallback callback, PVOID context, DWORD* count) {
	if (count)
		*count = 0;
	if (!searchPattern || !searchPattern[0] || !callback)
		return FiveXFileInvalidArgument;

	const CHAR* separator = strrchr(searchPattern, '\\');
	if (!separator)
		separator = strrchr(searchPattern, '/');
	if (separator) {
		const DWORD directoryLength = (DWORD)(separator - searchPattern);
		if (!directoryLength || directoryLength >= FIVEX_MAX_PATH)
			return FiveXFileInvalidArgument;
		CHAR directory[FIVEX_MAX_PATH];
		memcpy(directory, searchPattern, directoryLength);
		directory[directoryLength] = '\0';
		if (!FiveXDirectoryExists(directory)) {
			DbgPrint("[FiveX] Enumeration skipped; directory unavailable: %s\n", directory);
			return FiveXFileNotFound;
		}
	}

	WIN32_FIND_DATAA data;
	ZeroMemory(&data, sizeof(data));
	HANDLE findHandle = FindFirstFileA(searchPattern, &data);
	if (!findHandle || findHandle == INVALID_HANDLE_VALUE) {
		DbgPrint("[FiveX] FindFirstFile failed safely: %s Error=%lu\n", searchPattern, GetLastError());
		return FiveXFileNotFound;
	}
	DWORD found = 0;
	BOOL keepGoing = TRUE;
	do {
		if (strcmp(data.cFileName, ".") != 0 && strcmp(data.cFileName, "..") != 0) {
			++found;
			keepGoing = callback(data.cFileName, data.dwFileAttributes, context);
		}
	}
	while (keepGoing && FindNextFileA(findHandle, &data));
	DWORD error = GetLastError();
	if (findHandle && findHandle != INVALID_HANDLE_VALUE)
		FindClose(findHandle);
	if (count)
		*count = found;
	if (!keepGoing)
		return FiveXFileOk;
	return error == ERROR_NO_MORE_FILES ? FiveXFileOk : FiveXFileEnumerateFailed;
}
