#include "HookEngine.h"
#include "Core/Global.h"

static VOID __declspec(naked) FiveXGlpr() {
	__asm {
		std r14, -0x98(sp)
		std r15, -0x90(sp)
		std r16, -0x88(sp)
		std r17, -0x80(sp)
		std r18, -0x78(sp)
		std r19, -0x70(sp)
		std r20, -0x68(sp)
		std r21, -0x60(sp)
		std r22, -0x58(sp)
		std r23, -0x50(sp)
		std r24, -0x48(sp)
		std r25, -0x40(sp)
		std r26, -0x38(sp)
		std r27, -0x30(sp)
		std r28, -0x28(sp)
		std r29, -0x20(sp)
		std r30, -0x18(sp)
		std r31, -0x10(sp)
		stw r12, -0x8(sp)
		blr
	}
}

static VOID FlushCode(PVOID address, DWORD size) {
	BYTE* first = (BYTE*)address;
	FIVEX_DCACHE_FLUSH(first);
	if (size > 0x20)
		FIVEX_DCACHE_FLUSH(first + size - 1);
	FIVEX_SYNC();
	FIVEX_ISYNC();
}

static VOID PatchAbsoluteJump(DWORD* address, DWORD destination, BOOL linked) {
	DWORD high = (destination >> 16) & 0xFFFF;
	if (destination & 0x8000)
		++high;

	address[0] = 0x3D600000 | high;
	address[1] = 0x396B0000 | (destination & 0xFFFF);
	address[2] = 0x7D6903A6;
	address[3] = 0x4E800420 | (linked ? 1 : 0);
}

static BOOL IsAbsoluteJump(const DWORD* address) {
	return address &&
		(address[0] & 0xFFFF0000) == 0x3D600000 &&
		(address[1] & 0xFFFF0000) == 0x396B0000 &&
		address[2] == 0x7D6903A6 &&
		(address[3] & 0xFFFFFFFE) == 0x4E800420;
}

static DWORD AbsoluteJumpDestination(const DWORD* address) {
	if (!IsAbsoluteJump(address))
		return 0;
	const DWORD high = address[0] & 0xFFFF;
	const SHORT low = (SHORT)(address[1] & 0xFFFF);
	return (high << 16) + (LONG)low;
}

static BOOL InstructionsMatch(const DWORD* first, const DWORD* second) {
	if (!first || !second)
		return FALSE;
	for (DWORD index = 0; index < 4; ++index) {
		if (first[index] != second[index])
			return FALSE;
	}
	return TRUE;
}

static BOOL NeedsUnsupportedRelocation(DWORD instruction) {
	const DWORD opcode = instruction & 0xFC000000;
	const BOOL absoluteAddress = (instruction & 2) != 0;

	// Relative conditional branches cannot be copied to the trampoline unchanged.
	if (opcode == 0x40000000 && !absoluteAddress)
		return TRUE;

	// Relative BL is handled below only when it targets the known GLPR helper.
	// A relative branch without link cannot safely be copied either.
	if (opcode == 0x48000000 && !absoluteAddress && (instruction & 1) == 0)
		return TRUE;

	return FALSE;
}

static DWORD RelinkGlpr(DWORD branchOffset, DWORD* stubInstruction, DWORD* originalInstruction) {
	if (branchOffset & 0x02000000)
		branchOffset |= 0xFC000000;

	DWORD originalTargetInstruction = originalInstruction[branchOffset / 4];
	DWORD* glpr = (DWORD*)FiveXGlpr;

	for (DWORD index = 0; index < 20; ++index) {
		if (originalTargetInstruction == glpr[index]) {
			DWORD newOffset = (DWORD)&glpr[index] - (DWORD)stubInstruction;
			return 0x48000001 | (newOffset & 0x03FFFFFC);
		}
	}

	return 0;
}

VOID FiveXHookReset(FiveXHook* hook) {
	if (!hook)
		return;

	hook->Address = 0;
	hook->Installed = FALSE;
	for (DWORD index = 0; index < 4; ++index)
		hook->Original[index] = 0;
	for (DWORD index = 0; index < 4; ++index)
		hook->Patched[index] = 0;
	for (DWORD index = 0; index < 8; ++index)
		hook->Trampoline[index] = 0x60000000;
	hook->Trampoline[7] = 0x4E800020;
}

BOOL FiveXHookInstall(FiveXHook* hook, DWORD address, PVOID replacement, PVOID* original) {
	if (!hook || !replacement || !original || address < 0x80000000 ||
		address >= 0xE0000000 || (address & 3) || hook->Installed)
		return FALSE;

	DWORD* target = (DWORD*)address;
	if (IsAbsoluteJump(target)) {
		const DWORD previousDestination = AbsoluteJumpDestination(target);
		if (!previousDestination ||
			!MmIsAddressValid((PVOID)previousDestination)) {
			DbgPrint("[FiveX] Existing detour at 0x%08X has an invalid destination.\n", address);
			return FALSE;
		}
		if (previousDestination == (DWORD)replacement) {
			DbgPrint("[FiveX] Hook is already applied at 0x%08X; refusing duplicate ownership.\n", address);
			return FALSE;
		}

		hook->Address = address;
		for (DWORD index = 0; index < 4; ++index)
			hook->Original[index] = target[index];
		if (!InstructionsMatch(target, hook->Original)) {
			DbgPrint("[FiveX] Existing detour changed during hook installation at 0x%08X.\n", address);
			FiveXHookReset(hook);
			return FALSE;
		}

		PatchAbsoluteJump(target, (DWORD)replacement, FALSE);
		for (DWORD index = 0; index < 4; ++index)
			hook->Patched[index] = target[index];
		FlushCode(target, 0x10);

		*original = (PVOID)previousDestination;
		hook->Installed = TRUE;
		DbgPrint("[FiveX] Hook chained after existing detour at 0x%08X -> 0x%08X.\n",
			address, previousDestination);
		return TRUE;
	}
	hook->Address = address;
	for (DWORD index = 0; index < 4; ++index)
		hook->Original[index] = target[index];

	DWORD returnAddress = address + 0x10;
	DWORD returnHigh = (returnAddress >> 16) & 0xFFFF;
	if (returnAddress & 0x8000)
		++returnHigh;

	hook->Trampoline[0] = 0x3D600000 | returnHigh;
	hook->Trampoline[1] = 0x396B0000 | (returnAddress & 0xFFFF);
	hook->Trampoline[2] = 0x7D6903A6;

	for (DWORD index = 0; index < 4; ++index) {
		DWORD instruction = target[index];
		if (NeedsUnsupportedRelocation(instruction)) {
			DbgPrint("[FiveX] Unsupported relative branch in hook prologue at 0x%08X.\n", address + index * 4);
			FiveXHookReset(hook);
			return FALSE;
		}
		if ((instruction & 0x48000003) == 0x48000001) {
			hook->Trampoline[index + 3] = RelinkGlpr(
				instruction & ~0x48000003,
				&hook->Trampoline[index + 3],
				&target[index]);
			if (hook->Trampoline[index + 3] == 0) {
				FiveXHookReset(hook);
				return FALSE;
			}
		}
		else {
			hook->Trampoline[index + 3] = instruction;
		}
	}
	hook->Trampoline[7] = 0x4E800420;
	FlushCode(hook->Trampoline, sizeof(hook->Trampoline));

	if (!InstructionsMatch(target, hook->Original)) {
		DbgPrint("[FiveX] Hook target changed during installation at 0x%08X.\n", address);
		FiveXHookReset(hook);
		return FALSE;
	}
	PatchAbsoluteJump(target, (DWORD)replacement, FALSE);
	for (DWORD index = 0; index < 4; ++index)
		hook->Patched[index] = target[index];
	FlushCode(target, 0x10);

	*original = hook->Trampoline;
	hook->Installed = TRUE;
	return TRUE;
}

BOOL FiveXHookRemove(FiveXHook* hook) {
	if (!hook || !hook->Installed || hook->Address < 0x80000000)
		return TRUE;

	DWORD* target = (DWORD*)hook->Address;
	BOOL stillOwned = TRUE;
	BOOL alreadyRestored = TRUE;
	for (DWORD index = 0; index < 4; ++index) {
		if (target[index] != hook->Patched[index])
			stillOwned = FALSE;
		if (target[index] != hook->Original[index])
			alreadyRestored = FALSE;
	}
	if (!stillOwned) {
		if (alreadyRestored) {
			hook->Installed = FALSE;
			return TRUE;
		}
		DbgPrint("[FiveX] Hook ownership changed at 0x%08X; original bytes were not restored.\n", hook->Address);
		return FALSE;
	}
	for (DWORD index = 0; index < 4; ++index)
		target[index] = hook->Original[index];
	FlushCode(target, 0x10);
	hook->Installed = FALSE;
	return TRUE;
}
