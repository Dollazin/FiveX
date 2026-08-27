#pragma once

#include "FiveXKernel.h"

struct FiveXNativeRegistration {
	FiveXNativeRegistration* Previous;
	DWORD Handlers[7];
	DWORD Count;
	DWORD Hashes[7];
};

struct FiveXNativeContext {
	DWORD* ReturnValue;
	DWORD ArgumentCount;
	DWORD* Arguments;
	DWORD ReadCount;
	DWORD Storage[32];
};

inline VOID FiveXNativeReset(FiveXNativeContext* context) {
	context->ReturnValue = context->Storage;
	context->ArgumentCount = 0;
	context->Arguments = context->Storage;
	context->ReadCount = 0;
	for (DWORD index = 0; index < 32; ++index)
		context->Storage[index] = 0;
}

template <typename T>
inline BOOL FiveXNativePush(FiveXNativeContext* context, T value) {
	typedef CHAR FiveXNativeArgumentMustFitDword[(sizeof(T) <= sizeof(DWORD)) ? 1 : -1];
	(void)sizeof(FiveXNativeArgumentMustFitDword);

	if (!context || context->ArgumentCount >= 32)
		return FALSE;

	*(T*)&context->Arguments[context->ArgumentCount] = value;
	++context->ArgumentCount;
	return TRUE;
}

inline BOOL FiveXNativeCall(DWORD hash, FiveXNativeContext* context);

template <typename T>
inline T FiveXNativeResult(FiveXNativeContext* context);

class FiveXNativeCallBuilder {
public:
	explicit FiveXNativeCallBuilder(DWORD hash) : Hash(hash), Valid(TRUE) {
		FiveXNativeReset(&Context);
	}

	template <typename T>
	FiveXNativeCallBuilder& Push(T value) {
		if (!FiveXNativePush(&Context, value))
			Valid = FALSE;
		return *this;
	}

	template <typename R>
	R Invoke() {
		if (Valid)
			FiveXNativeCall(Hash, &Context);
		return FiveXNativeResult<R>(&Context);
	}

private:
	DWORD Hash;
	BOOL Valid;
	FiveXNativeContext Context;
};

inline BOOL FiveXNativeCall(DWORD hash, FiveXNativeContext* context) {
	FiveXNativeRegistration** table = (FiveXNativeRegistration**)0x83DDCD08;
	FiveXNativeRegistration* registration = table[hash & 0xFF];

	while (registration) {
		DWORD count = registration->Count;
		if (count > 7)
			count = 7;

		for (DWORD index = 0; index < count; ++index) {
			if (registration->Hashes[index] == hash && registration->Handlers[index]) {
				((VOID(*)(FiveXNativeContext*))registration->Handlers[index])(context);
				return TRUE;
			}
		}
		registration = registration->Previous;
	}

	return FALSE;
}

template <typename T>
inline T FiveXNativeResult(FiveXNativeContext* context) {
	return *(T*)context->ReturnValue;
}

template <>
inline VOID FiveXNativeResult<VOID>(FiveXNativeContext*) {
}

template <typename R>
inline R FiveXInvoke(DWORD hash) {
	FiveXNativeContext context;
	FiveXNativeReset(&context);
	FiveXNativeCall(hash, &context);
	return FiveXNativeResult<R>(&context);
}

template <typename R, typename P1>
inline R FiveXInvoke(DWORD hash, P1 p1) {
	FiveXNativeContext context;
	FiveXNativeReset(&context);
	FiveXNativePush(&context, p1);
	FiveXNativeCall(hash, &context);
	return FiveXNativeResult<R>(&context);
}

template <typename R, typename P1, typename P2>
inline R FiveXInvoke(DWORD hash, P1 p1, P2 p2) {
	FiveXNativeContext context;
	FiveXNativeReset(&context);
	FiveXNativePush(&context, p1);
	FiveXNativePush(&context, p2);
	FiveXNativeCall(hash, &context);
	return FiveXNativeResult<R>(&context);
}

template <typename R, typename P1, typename P2, typename P3>
inline R FiveXInvoke(DWORD hash, P1 p1, P2 p2, P3 p3) {
	FiveXNativeContext context;
	FiveXNativeReset(&context);
	FiveXNativePush(&context, p1);
	FiveXNativePush(&context, p2);
	FiveXNativePush(&context, p3);
	FiveXNativeCall(hash, &context);
	return FiveXNativeResult<R>(&context);
}

template <typename R, typename P1, typename P2, typename P3, typename P4>
inline R FiveXInvoke(DWORD hash, P1 p1, P2 p2, P3 p3, P4 p4) {
	FiveXNativeContext context;
	FiveXNativeReset(&context);
	FiveXNativePush(&context, p1);
	FiveXNativePush(&context, p2);
	FiveXNativePush(&context, p3);
	FiveXNativePush(&context, p4);
	FiveXNativeCall(hash, &context);
	return FiveXNativeResult<R>(&context);
}

template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
inline R FiveXInvoke(DWORD hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) {
	FiveXNativeContext context;
	FiveXNativeReset(&context);
	FiveXNativePush(&context, p1);
	FiveXNativePush(&context, p2);
	FiveXNativePush(&context, p3);
	FiveXNativePush(&context, p4);
	FiveXNativePush(&context, p5);
	FiveXNativeCall(hash, &context);
	return FiveXNativeResult<R>(&context);
}

template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
inline R FiveXInvoke(DWORD hash, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) {
	FiveXNativeContext context;
	FiveXNativeReset(&context);
	FiveXNativePush(&context, p1);
	FiveXNativePush(&context, p2);
	FiveXNativePush(&context, p3);
	FiveXNativePush(&context, p4);
	FiveXNativePush(&context, p5);
	FiveXNativePush(&context, p6);
	FiveXNativeCall(hash, &context);
	return FiveXNativeResult<R>(&context);
}

#include "NativeInvokerExtended.inl"
