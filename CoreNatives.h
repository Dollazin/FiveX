#pragma once

// Typed wrappers used only by the FiveX C++ core. Lua resources use the
// metadata-driven catalog and do not depend on this header.

#include "GameTypes.h"
#include "NativeInvoker.h"

inline DWORD GetGameTimer() { return FiveXInvoke<DWORD>(0xA4EA0691); }
inline DWORD GetFrameCount() { return FiveXInvoke<DWORD>(0xB477A015); }
inline DWORD PlayerId() { return FiveXInvoke<DWORD>(0x8AEA886C); }
inline DWORD PlayerPedId() { return FiveXInvoke<DWORD>(0xFA92E226); }
inline BOOL IsPlayerPlaying(DWORD player) { return FiveXInvoke<BOOL>(0xE15D777F, player); }
inline BOOL IsPedDeadOrDying(Ped ped, BOOL checkMeleeDeathFlags) { return FiveXInvoke<BOOL>(0xCBDB7739, ped, checkMeleeDeathFlags); }
inline BOOL GetIsLoadingScreenActive() { return FiveXInvoke<BOOL>(0x517B601B); }
inline BOOL GetNoLoadingScreen() { return FiveXInvoke<BOOL>(0x27512BA0); }
inline BOOL AreAllNavmeshRegionsLoaded() { return FiveXInvoke<BOOL>(0x34C4E789); }
inline BOOL DoesEntityExist(DWORD entity) { return FiveXInvoke<BOOL>(0x3AC90869, entity); }
inline Vector3 GetEntityCoords(DWORD entity, BOOL alive) { return FiveXInvoke<Vector3>(0x1647F1CB, entity, alive); }
inline VOID SetEntityCoords(DWORD entity, FLOAT x, FLOAT y, FLOAT z, BOOL xAxes, BOOL yAxes, BOOL zAxes, BOOL unknown) {
	FiveXNativeCallBuilder call(0xDF70B41B);
	call.Push(entity).Push(x).Push(y).Push(z).Push(xAxes).Push(yAxes).Push(zAxes).Push(unknown).Invoke<VOID>();
}
inline BOOL IsControlJustPressed(DWORD group, DWORD control) { return FiveXInvoke<BOOL>(0x4487F579, group, control); }
inline VOID DisableAllControlActions(INT group) { FiveXInvoke<VOID>(0x16753CF4, group); }
inline VOID RequestModel(DWORD model) { FiveXInvoke<VOID>(0xFFF1B500, model); }
inline BOOL HasModelLoaded(DWORD model) { return FiveXInvoke<BOOL>(0x62BFDB37, model); }
inline VOID SetModelAsNoLongerNeeded(DWORD model) { FiveXInvoke<VOID>(0xAE0F069E, model); }
inline DWORD CreateVehicle(DWORD model, FLOAT x, FLOAT y, FLOAT z, FLOAT heading, BOOL networked, BOOL scriptHandle) {
	FiveXNativeCallBuilder call(0xDD75460A);
	return call.Push(model).Push(x).Push(y).Push(z).Push(heading).Push(networked).Push(scriptHandle).Invoke<DWORD>();
}
inline VOID DrawMarker(INT type, FLOAT x, FLOAT y, FLOAT z, FLOAT dirX, FLOAT dirY, FLOAT dirZ,
	FLOAT rotX, FLOAT rotY, FLOAT rotZ, FLOAT scaleX, FLOAT scaleY, FLOAT scaleZ,
	INT red, INT green, INT blue, INT alpha, BOOL bobUpAndDown, BOOL faceCamera,
	INT p19, BOOL rotate, const CHAR* textureDict, const CHAR* textureName, BOOL drawOnEntities) {
	FiveXNativeCallBuilder call(0x48D84A02);
	call.Push(type).Push(x).Push(y).Push(z)
		.Push(dirX).Push(dirY).Push(dirZ)
		.Push(rotX).Push(rotY).Push(rotZ)
		.Push(scaleX).Push(scaleY).Push(scaleZ)
		.Push(red).Push(green).Push(blue).Push(alpha)
		.Push(bobUpAndDown).Push(faceCamera).Push(p19).Push(rotate)
		.Push(textureDict).Push(textureName).Push(drawOnEntities).Invoke<VOID>();
}
inline VOID DrawRect(FLOAT x, FLOAT y, FLOAT width, FLOAT height, INT red, INT green, INT blue, INT alpha) {
	FiveXNativeCallBuilder call(0xDD2BFC77);
	call.Push(x).Push(y).Push(width).Push(height).Push(red).Push(green).Push(blue).Push(alpha).Invoke<VOID>();
}
inline VOID SetTextFont(INT font) { FiveXInvoke<VOID>(0x80BC530D, font); }
inline VOID SetTextScale(FLOAT x, FLOAT y) { FiveXInvoke<VOID>(0xB6E15B23, x, y); }
inline VOID SetTextColour(INT red, INT green, INT blue, INT alpha) { FiveXInvoke<VOID>(0xE54DD2C8, red, green, blue, alpha); }
inline VOID SetTextCentre(BOOL centred) { FiveXInvoke<VOID>(0xE26D39A1, centred); }
inline VOID SetTextRightJustify(BOOL enabled) { FiveXInvoke<VOID>(0x45B60520, enabled); }
inline VOID SetTextWrap(FLOAT start, FLOAT end) { FiveXInvoke<VOID>(0x6F60AB54, start, end); }
inline VOID SetTextDropShadow() { FiveXInvoke<VOID>(0xE2A11511); }
inline VOID SetTextEntry(const CHAR* type) { FiveXInvoke<VOID>(0x3E35563E, type); }
inline VOID AddTextComponentString(const CHAR* text) { FiveXInvoke<VOID>(0x27A244D8, text); }
inline VOID DrawText(FLOAT x, FLOAT y) { FiveXInvoke<VOID>(0x6F8350CE, x, y); }
inline BOOL IsScreenFadedIn() { return FiveXInvoke<BOOL>(0x4F37276D); }
inline FLOAT GetEntityHeading(Entity entity) { return FiveXInvoke<FLOAT>(0x972CC383, entity); }
inline VOID DeleteEntity(Entity* entity) { FiveXInvoke<VOID>(0xFAA3D236, entity); }
inline BOOL GetGroundZFor3dCoord2(FLOAT x, FLOAT y, FLOAT z, FLOAT* groundZ) { return FiveXInvoke<BOOL>(0xA1BFD5E0, x, y, z, groundZ); }
inline INT GetHashKey(CHAR* text) { return FiveXInvoke<INT>(0x98EFF6F1, text); }
inline BOOL IsNetworkLoadingScene() { return FiveXInvoke<BOOL>(0x6DCFC021); }
inline BOOL IsModelInCdimage(Any model) { return FiveXInvoke<BOOL>(0x1094782F, model); }
inline VOID SetNotificationTextEntry(CHAR* type) { FiveXInvoke<VOID>(0x574EE85C, type); }
inline BOOL BusyspinnerIsOn() { return FiveXInvoke<BOOL>(0xB8B3A5D0); }
inline INT DrawNotification(BOOL blink, BOOL showInBrief) { return FiveXInvoke<INT>(0x08F7AF78, blink, showInBrief); }
inline Any GetFirstBlipInfoId(Any sprite) { return FiveXInvoke<Any>(0x64C0273D, sprite); }
inline Vector3 GetBlipInfoIdCoord(Any blip) { return FiveXInvoke<Vector3>(0xB7374A66, blip); }
inline BOOL DoesBlipExist(Any blip) { return FiveXInvoke<BOOL>(0xAE92DD96, blip); }
inline VOID SetVehicleEngineOn(Vehicle vehicle, BOOL engineState, BOOL instantly) {
	FiveXInvoke<VOID>(0x7FBC86F1, vehicle, engineState, instantly);
}
