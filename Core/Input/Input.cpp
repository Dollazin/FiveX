#include "Input.h"
#include "../Global.h"

struct FiveXInputRepeatSlot {
	WORD Button;
	DWORD NextAt;
};

static WORD g_currentButtons;
static WORD g_previousButtons;
static BOOL g_connected;
static FiveXInputRepeatSlot g_repeatSlots[8];

BOOL FiveXInputInitialize() {
	g_currentButtons = 0;
	g_previousButtons = 0;
	g_connected = FALSE;
	ZeroMemory(g_repeatSlots, sizeof(g_repeatSlots));
	return TRUE;
}

VOID FiveXInputUpdate() {
	g_previousButtons = g_currentButtons;
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(state));
	if (XInputGetState(0, &state) != ERROR_SUCCESS) {
		g_currentButtons = 0;
		g_connected = FALSE;
		ZeroMemory(g_repeatSlots, sizeof(g_repeatSlots));
		return;
	}
	g_currentButtons = state.Gamepad.wButtons;
	g_connected = TRUE;
}

VOID FiveXInputShutdown() {
	g_currentButtons = 0;
	g_previousButtons = 0;
	g_connected = FALSE;
	ZeroMemory(g_repeatSlots, sizeof(g_repeatSlots));
}

BOOL FiveXInputConnected() { return g_connected; }

BOOL FiveXInputHeld(WORD buttons) {
	return g_connected && (g_currentButtons & buttons) == buttons;
}

BOOL FiveXInputPressed(WORD buttons) {
	return g_connected && (g_currentButtons & buttons) == buttons &&
		(g_previousButtons & buttons) != buttons;
}

BOOL FiveXInputAnyHeld(WORD buttons) {
	return g_connected && (g_currentButtons & buttons) != 0;
}

BOOL FiveXInputPressedOrRepeated(WORD button, DWORD initialDelay, DWORD repeatDelay) {
	FiveXInputRepeatSlot* slot = NULL;
	for (DWORD index = 0; index < ARRAYSIZE(g_repeatSlots); ++index) {
		if (g_repeatSlots[index].Button == button) {
			slot = &g_repeatSlots[index];
			break;
		}
		if (!slot && g_repeatSlots[index].Button == 0)
			slot = &g_repeatSlots[index];
	}
	if (!slot)
		return FiveXInputPressed(button);
	if (!FiveXInputHeld(button)) {
		slot->Button = button;
		slot->NextAt = 0;
		return FALSE;
	}
	const DWORD now = GetTickCount();
	if (FiveXInputPressed(button)) {
		slot->Button = button;
		slot->NextAt = now + initialDelay;
		return TRUE;
	}
	if (slot->NextAt && Helpers::HasElapsed(now, slot->NextAt)) {
		slot->NextAt = now + repeatDelay;
		return TRUE;
	}
	return FALSE;
}
