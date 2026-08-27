#pragma once

#include <xtl.h>

#define FIVEX_DCACHE_FLUSH(address) __dcbst(0, address)
#define FIVEX_SYNC() __sync()
#define FIVEX_ISYNC() __emit(0x4C00012C)

typedef LONG NTSTATUS;

typedef struct _FIVEX_ANSI_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PCHAR Buffer;
} FIVEX_ANSI_STRING, *PFIVEX_ANSI_STRING;

extern "C" {
	NTSYSAPI VOID NTAPI DbgPrint(const CHAR* format, ...);
	NTSYSAPI BOOL NTAPI MmIsAddressValid(PVOID address);
	NTSYSAPI UCHAR NTAPI KeGetCurrentProcessType(VOID);
	NTSYSAPI HRESULT NTAPI ObCreateSymbolicLink(
		PFIVEX_ANSI_STRING symbolicLinkName,
		PFIVEX_ANSI_STRING deviceName);
	NTSYSAPI HRESULT NTAPI ObDeleteSymbolicLink(
		PFIVEX_ANSI_STRING symbolicLinkName);
	NTSYSAPI DWORD NTAPI ExCreateThread(
		PHANDLE handle,
		DWORD stackSize,
		LPDWORD threadId,
		PVOID apiThreadStartup,
		LPTHREAD_START_ROUTINE startAddress,
		LPVOID parameter,
		DWORD creationFlags);
	NTSYSAPI VOID NTAPI ExTerminateThread(DWORD exitCode);
	NTSYSAPI NTSTATUS NTAPI XexGetModuleHandle(
		PCHAR moduleName,
		PHANDLE moduleHandle);
	NTSYSAPI NTSTATUS NTAPI XexGetProcedureAddress(
		HANDLE moduleHandle,
		DWORD ordinal,
		PVOID* procedureAddress);
	VOID XapiThreadStartup(
		VOID(__cdecl* startRoutine)(VOID*),
		PVOID startContext,
		DWORD exitCode);
	BOOL XapiInitHeap();
}
