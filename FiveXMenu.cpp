#include "FiveXMenu.h"
#include "Runtime/Lua/LuaRuntime.h"
#include "Core/Input/Input.h"
#include "GameNatives.h"
#include <stdio.h>

#define FIVEX_MENU_VISIBLE_RESOURCES 8

static BOOL g_open;
static INT g_selected;

static VOID Text(const CHAR* value, FLOAT x, FLOAT y, FLOAT scale, BOOL rightAligned = FALSE) {
	SetTextFont(0);
	SetTextScale(0.0f, scale);
	SetTextColour(255, 255, 255, 255);
	SetTextCentre(FALSE);
	SetTextRightJustify(rightAligned);
	SetTextWrap(0.0f, rightAligned ? x : 1.0f);
	SetTextEntry("STRING");
	AddTextComponentString(value);
	DrawText(x, y);
}

static const CHAR* ResourceAction(const FiveXLuaResourceInfo* resource) {
	if (!resource)
		return "";
	if (resource->State == FiveXLuaResourceStarted)
		return "A: STOP RESOURCE";
	return "A: START RESOURCE";
}

BOOL FiveXMenuInitialize() {
	g_open = FALSE;
	g_selected = 0;
	return TRUE;
}

VOID FiveXMenuShutdown() {
	g_open = FALSE;
}

VOID FiveXMenuTick() {
	const WORD openButtons = XINPUT_GAMEPAD_RIGHT_SHOULDER | XINPUT_GAMEPAD_X;
	if (FiveXInputPressed(openButtons))
		g_open = !g_open;
	if (!g_open)
		return;

	// Menu input is read directly through XInput, so all GTA control groups can
	// be disabled without preventing the user from navigating or closing FiveX.
	DisableAllControlActions(0);
	DisableAllControlActions(1);
	DisableAllControlActions(2);

	const INT count = FiveXLuaResourceCount();
	if (g_selected > count)
		g_selected = count;

	DrawRect(0.5f, 0.465f, 0.46f, 0.385f, 8, 8, 12, 210);
	DrawRect(0.5f, 0.25f, 0.46f, 0.05f, 18, 18, 24, 245);
	Text("FIVEX | LUA RESOURCES", 0.285f, 0.235f, 0.42f);

	CHAR line[160];
	sprintf_s(line, sizeof(line), "DETECTED RESOURCES: %d", count);
	Text(line, 0.715f, 0.239f, 0.28f, TRUE);

	sprintf_s(line, sizeof(line), "%c Refresh Resouces",
		g_selected == 0 ? '>' : ' ');
	if (g_selected == 0)
		DrawRect(0.5f, 0.300f, 0.46f, 0.035f, 55, 80, 120, 210);
	Text(line, 0.285f, 0.287f, 0.31f);

	INT firstResource = 0;
	if (g_selected > FIVEX_MENU_VISIBLE_RESOURCES)
		firstResource = g_selected - FIVEX_MENU_VISIBLE_RESOURCES;
	INT lastResource = firstResource + FIVEX_MENU_VISIBLE_RESOURCES;
	if (lastResource > count)
		lastResource = count;

	if (!count) {
		Text("NO RESOURCES FOUND", 0.285f, 0.325f, 0.30f);
	}
	else {
		for (INT index = firstResource; index < lastResource; ++index) {
			const FiveXLuaResourceInfo* resource = FiveXLuaResourceGet(index);
			if (!resource)
				continue;
			const BOOL selected = g_selected == index + 1;
			const FLOAT y = 0.325f + (index - firstResource) * 0.032f;
			if (selected)
				DrawRect(0.5f, y + 0.013f, 0.46f, 0.031f, 55, 80, 120, 210);
			sprintf_s(line, sizeof(line), "%c %s  [%s]",
				selected ? '>' : ' ', resource->Name,
				FiveXLuaResourceStateText(index));
			Text(line, 0.285f, y, 0.30f);
		}
	}

	const FLOAT footerY = 0.635f;
	DrawRect(0.5f, footerY + 0.013f, 0.46f, 0.035f, 10, 10, 14, 220);
	if (g_selected == 0)
		Text("A: REFRESH RESOURCE FOLDERS", 0.285f, footerY, 0.29f);
	else
		Text(ResourceAction(FiveXLuaResourceGet(g_selected - 1)),
			0.285f, footerY, 0.29f);

	if (FiveXInputPressedOrRepeated(XINPUT_GAMEPAD_DPAD_UP, 350, 70))
		g_selected = g_selected > 0 ? g_selected - 1 : count;
	if (FiveXInputPressedOrRepeated(XINPUT_GAMEPAD_DPAD_DOWN, 350, 70))
		g_selected = g_selected < count ? g_selected + 1 : 0;
	if (FiveXInputPressed(XINPUT_GAMEPAD_A)) {
		if (!g_selected) {
			FiveXLuaResourceRefresh();
			if (g_selected > FiveXLuaResourceCount())
				g_selected = FiveXLuaResourceCount();
		}
		else {
			const FiveXLuaResourceInfo* resource = FiveXLuaResourceGet(g_selected - 1);
			if (resource) {
				if (resource->State == FiveXLuaResourceStarted)
					FiveXLuaResourceStop(resource->Name);
				else
					FiveXLuaResourceStart(resource->Name);
			}
		}
	}
}
