#pragma once

#include "GameTypes.h"
#include "NativeInvoker.h"

inline DWORD GetGameTimer() { return FiveXInvoke<DWORD>(0xA4EA0691); }
inline DWORD GetFrameCount() { return FiveXInvoke<DWORD>(0xB477A015); }
inline VOID DisplayOnscreenKeyboard(BOOL p0, const CHAR* windowTitle, const CHAR* p2, const CHAR* defaultText, const CHAR* defaultConcat1, const CHAR* defaultConcat2, const CHAR* defaultConcat3, INT maxInputLength) { FiveXNativeCallBuilder call(0xAD99F2CE); call.Push(p0).Push(windowTitle).Push(p2).Push(defaultText).Push(defaultConcat1).Push(defaultConcat2).Push(defaultConcat3).Push(maxInputLength).Invoke<VOID>(); }
inline INT UpdateOnscreenKeyboard() { return FiveXInvoke<INT>(0x23D0A1CE); }
inline const CHAR* GetOnscreenKeyboardResult() { return FiveXInvoke<const CHAR*>(0x44828FB3); }
inline VOID SetSuperJumpThisFrame(DWORD player) { FiveXInvoke<VOID>(0x86745EF3, player); }
inline DWORD PlayerId() { return FiveXInvoke<DWORD>(0x8AEA886C); }
inline DWORD PlayerPedId() { return FiveXInvoke<DWORD>(0xFA92E226); }
inline BOOL IsPlayerPlaying(DWORD player) { return FiveXInvoke<BOOL>(0xE15D777F, player); }
inline BOOL IsPedDeadOrDying(Ped ped, BOOL checkMeleeDeathFlags) { return FiveXInvoke<BOOL>(0xCBDB7739, ped, checkMeleeDeathFlags); }
inline BOOL GetIsLoadingScreenActive() { return FiveXInvoke<BOOL>(0x517B601B); }
inline BOOL GetNoLoadingScreen() { return FiveXInvoke<BOOL>(0x27512BA0); }
inline BOOL AreAllNavmeshRegionsLoaded() { return FiveXInvoke<BOOL>(0x34C4E789); }
inline VOID SetPlayerInvincible(DWORD player, BOOL enabled) { FiveXInvoke<VOID>(0xDFB9A2A2, player, enabled); }
inline VOID ClearPlayerWantedLevel(DWORD player) { FiveXInvoke<VOID>(0x54EA5BCC, player); }
inline BOOL DoesEntityExist(DWORD entity) { return FiveXInvoke<BOOL>(0x3AC90869, entity); }
inline Vector3 GetEntityCoords(DWORD entity, BOOL alive) { return FiveXInvoke<Vector3>(0x1647F1CB, entity, alive); }
inline BOOL HasCollisionLoadedAroundEntity(DWORD entity) { return FiveXInvoke<BOOL>(0x851687F9, entity); }
inline VOID SetEntityInvincible(DWORD entity, BOOL enabled) { FiveXInvoke<VOID>(0xC1213A21, entity, enabled); }
inline VOID SetEntityVisible(DWORD entity, BOOL visible) { FiveXInvoke<VOID>(0xD043E8E1, entity, visible); }
inline VOID SetEntityCoords(DWORD entity, FLOAT X, FLOAT Y, FLOAT Z, BOOL XAxes, BOOL YAxes, BOOL ZAxes, BOOL unk) { FiveXNativeCallBuilder call(0xDF70B41B); call.Push(entity).Push(X).Push(Y).Push(Z).Push(XAxes).Push(YAxes).Push(ZAxes).Push(unk).Invoke<VOID>(); }
inline VOID SetPedCanRagdoll(DWORD ped, BOOL enabled) { FiveXInvoke<VOID>(0xCF1384C4, ped, enabled); }
inline BOOL IsControlJustPressed(DWORD group, DWORD control) { return FiveXInvoke<BOOL>(0x4487F579, group, control); }
inline VOID DisableAllControlActions(INT group) { FiveXInvoke<VOID>(0x16753CF4, group); }
inline VOID DisableControlAction(INT group, INT control, BOOL disable) { FiveXInvoke<VOID>(0x3800C0DC, group, control, disable); }
inline VOID EnableControlAction(INT group, INT control) { FiveXInvoke<VOID>(0xD2753551, group, control); }
inline VOID RequestModel(DWORD model) { FiveXInvoke<VOID>(0xFFF1B500, model); }
inline BOOL HasModelLoaded(DWORD model) { return FiveXInvoke<BOOL>(0x62BFDB37, model); }
inline VOID SetModelAsNoLongerNeeded(DWORD model) { FiveXInvoke<VOID>(0xAE0F069E, model); }
inline VOID RequestCollisionAtCoord(FLOAT x, FLOAT y, FLOAT z) { FiveXInvoke<VOID>(0xCD9805E7, x, y, z); }
inline VOID RequestAnimDict(const CHAR* dictionary) { FiveXInvoke<VOID>(0xDCA96950, dictionary); }
inline BOOL HasAnimDictLoaded(const CHAR* dictionary) { return FiveXInvoke<BOOL>(0x05E6763C, dictionary); }
inline VOID RemoveAnimDict(const CHAR* dictionary) { FiveXInvoke<VOID>(0x0AE050B5, dictionary); }
inline VOID RequestClipSet(const CHAR* clipSet) { FiveXInvoke<VOID>(0x546C627A, clipSet); }
inline BOOL HasClipSetLoaded(const CHAR* clipSet) { return FiveXInvoke<BOOL>(0x230D5455, clipSet); }
inline VOID RemoveClipSet(const CHAR* clipSet) { FiveXInvoke<VOID>(0x1E21F7AA, clipSet); }
inline VOID RequestWeaponAsset(DWORD weapon, INT flags, BOOL p2) { FiveXInvoke<VOID>(0x65D139A5, weapon, flags, p2); }
inline BOOL HasWeaponAssetLoaded(DWORD weapon) { return FiveXInvoke<BOOL>(0x1891D5BB, weapon); }
inline VOID RemoveWeaponAsset(DWORD weapon) { FiveXInvoke<VOID>(0x2C0DFE3C, weapon); }
inline BOOL NetworkRequestControlOfEntity(DWORD entity) { return FiveXInvoke<BOOL>(0xA05FEBD7, entity); }
inline BOOL NetworkGetEntityIsNetworked(DWORD entity) { return FiveXInvoke<BOOL>(0xD7F934F4, entity); }
inline VOID NetworkRegisterEntityAsNetworked(DWORD entity) { FiveXInvoke<VOID>(0x31A630A4, entity); }
inline BOOL NetworkHasControlOfEntity(DWORD entity) { return FiveXInvoke<BOOL>(0x005FD797, entity); }
inline DWORD CreateVehicle(DWORD model, FLOAT x, FLOAT y, FLOAT z, FLOAT heading, BOOL networked, BOOL scriptHandle) { FiveXNativeCallBuilder call(0xDD75460A); return call.Push(model) .Push(x).Push(y).Push(z) .Push(heading).Push(networked).Push(scriptHandle) .Invoke<DWORD>(); }
inline INT AddRope(FLOAT x, FLOAT y, FLOAT z, FLOAT rotX, FLOAT rotY, FLOAT rotZ, FLOAT length, INT ropeType, FLOAT maxLength, FLOAT minLength, FLOAT windingSpeed, BOOL p11, BOOL p12, BOOL rigid, FLOAT p14, BOOL breakWhenShot, Any* unkPtr) { return FiveXInvoke<INT>(0xA592EC74, x, y, z, rotX, rotY, rotZ, length, ropeType, maxLength, minLength, windingSpeed, p11, p12, rigid, p14, breakWhenShot, unkPtr); }
inline VOID DeleteRope(INT* ropeId) { FiveXInvoke<VOID>(0x748D72AF, ropeId); }
inline VOID AttachEntitiesToRope(INT ropeId, Entity ent1, Entity ent2, FLOAT ent1_x, FLOAT ent1_y, FLOAT ent1_z, FLOAT ent2_x, FLOAT ent2_y, FLOAT ent2_z, FLOAT length, BOOL p10, BOOL p11, Any* p12, Any* p13) { FiveXInvoke<VOID>(0x7508668F, ropeId, ent1, ent2, ent1_x, ent1_y, ent1_z, ent2_x, ent2_y, ent2_z, length, p10, p11, p12, p13); }
inline VOID RopeLoadTextures() { FiveXInvoke<VOID>(0xBA97CE91); }
inline BOOL RopeAreTexturesLoaded() { return FiveXInvoke<BOOL>(0x5FDC1047); }
inline VOID RopeUnloadTextures() { FiveXInvoke<VOID>(0x584463E0); }
inline VOID RopeForceLength(INT ropeId, FLOAT length) { FiveXInvoke<VOID>(0xABF3130F, ropeId, length); }
inline VOID ActivatePhysics(Entity entity) { FiveXInvoke<VOID>(0x031711B8, entity); }
inline BOOL GetIsVehicleEngineRunning(Vehicle vehicle) { return FiveXInvoke<BOOL>(0x7DC6D022, vehicle); }
inline VOID RequestStreamedTextureDict(const CHAR* dictionary, BOOL p1) { FiveXInvoke<VOID>(0x4C9B035F, dictionary, p1); }
inline BOOL HasStreamedTextureDictLoaded(const CHAR* dictionary) { return FiveXInvoke<BOOL>(0x3F436EEF, dictionary); }
inline VOID DrawSprite(const CHAR* dictionary, const CHAR* texture, FLOAT x, FLOAT y, FLOAT width, FLOAT height, FLOAT rotation, INT red, INT green, INT blue, INT alpha) { FiveXNativeCallBuilder call(0x1FEC16B0); call.Push(dictionary).Push(texture).Push(x).Push(y).Push(width).Push(height).Push(rotation).Push(red).Push(green).Push(blue).Push(alpha).Invoke<VOID>(); }
inline VOID DrawMarker( INT type, FLOAT x, FLOAT y, FLOAT z, FLOAT dirX, FLOAT dirY, FLOAT dirZ, FLOAT rotX, FLOAT rotY, FLOAT rotZ, FLOAT scaleX, FLOAT scaleY, FLOAT scaleZ, INT red, INT green, INT blue, INT alpha, BOOL bobUpAndDown, BOOL faceCamera, INT p19, BOOL rotate, const CHAR* textureDict, const CHAR* textureName, BOOL drawOnEntities) { FiveXNativeCallBuilder call(0x48D84A02); call.Push(type) .Push(x).Push(y).Push(z) .Push(dirX).Push(dirY).Push(dirZ) .Push(rotX).Push(rotY).Push(rotZ) .Push(scaleX).Push(scaleY).Push(scaleZ) .Push(red).Push(green).Push(blue).Push(alpha) .Push(bobUpAndDown).Push(faceCamera) .Push(p19).Push(rotate) .Push(textureDict).Push(textureName) .Push(drawOnEntities) .Invoke<VOID>(); }
inline VOID DrawRect( FLOAT x, FLOAT y, FLOAT width, FLOAT height, INT red, INT green, INT blue, INT alpha) { FiveXNativeCallBuilder call(0xDD2BFC77); call.Push(x) .Push(y) .Push(width) .Push(height) .Push(red) .Push(green) .Push(blue) .Push(alpha) .Invoke<VOID>(); }
inline VOID SetTextEntryForWidth(const CHAR* type) { FiveXInvoke<VOID>(0x51E7A037, type); }
inline FLOAT GetTextScreenWidth(BOOL p0) { return FiveXInvoke<FLOAT>(0xD12A643A, p0); }
inline VOID SetTextFont(INT font) { FiveXInvoke<VOID>(0x80BC530D, font); }
inline VOID SetTextScale(FLOAT x, FLOAT y) { FiveXInvoke<VOID>(0xB6E15B23, x, y); }
inline VOID SetTextColour(INT red, INT green, INT blue, INT alpha) { FiveXInvoke<VOID>(0xE54DD2C8, red, green, blue, alpha); }
inline VOID SetTextCentre(BOOL centred) { FiveXInvoke<VOID>(0xE26D39A1, centred); }
inline VOID SetTextRightJustify(BOOL enabled) { FiveXInvoke<VOID>(0x45B60520, enabled); }
inline VOID SetTextWrap(FLOAT start, FLOAT end) { FiveXInvoke<VOID>(0x6F60AB54, start, end); }
inline VOID SetTextOutline() { FiveXInvoke<VOID>(0xC753412F); }
inline VOID SetTextEntry(const CHAR* type) { FiveXInvoke<VOID>(0x3E35563E, type); }
inline VOID AddTextComponentString(const CHAR* text) { FiveXInvoke<VOID>(0x27A244D8, text); }
inline VOID DrawText(FLOAT x, FLOAT y) { FiveXInvoke<VOID>(0x6F8350CE, x, y); }
inline VOID OnEnterSp() { FiveXInvoke<VOID>(0x8BF60FC3); } // 0x8BF60FC3
inline VOID OnEnterMp() { FiveXInvoke<VOID>(0xC65586A9); } // 0xC65586A9
inline VOID CellCamActivate(BOOL active, BOOL bGoFirstPerson) { FiveXInvoke<VOID>(0x234C1AE9, active, bGoFirstPerson); } // 0x234C1AE9
inline VOID CreateMobilePhone(int phoneType) { FiveXInvoke<VOID>(0x5BBC5E23, phoneType); } // 0x5BBC5E23
inline VOID GetStreetNameAtCoord(FLOAT x, FLOAT y, FLOAT z, Hash* streetName, Hash* crossingRoad) { FiveXInvoke<VOID>(0xDEBEEFCF, x, y, z, streetName, crossingRoad); } // 0xDEBEEFCF
inline BOOL GetWaterHeight(float x, float y, float z, float* outHeight) { return FiveXInvoke<BOOL>(0xD864E17C, x, y, z, outHeight); }
inline VOID TaskPause(Any p0, Any p1) { FiveXInvoke<VOID>(0x17A64668, p0, p1); } // 0x17A64668
inline VOID TaskStandStill(Any p0, Any p1) { FiveXInvoke<VOID>(0x6F80965D, p0, p1); } // 0x6F80965D
inline VOID TaskJump(Ped pedHandle, BOOL p1) { FiveXInvoke<VOID>(0x0356E3CE, pedHandle, p1); } // 0x0356E3CE
inline VOID TaskCower(Ped pedHandle, INT time) { FiveXInvoke<VOID>(0x9CF1C19B, pedHandle, time); } // 0x9CF1C19B
inline VOID TaskHandsUp(Ped pedHandle, INT time, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0x8DCC19C5, pedHandle, time, p2, p3, p4); } // 0x8DCC19C5
inline VOID TaskOpenVehicleDoor(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0x8EE06BF4, p0, p1, p2, p3, p4); } // 0x8EE06BF4
inline VOID TaskEnterVehicle(Ped pedHandle, Vehicle vehicleHandle, INT timeout, INT seat, FLOAT p4, Any p5, Any p6) { FiveXInvoke<VOID>(0xB8689B4E, pedHandle, vehicleHandle, timeout, seat, p4, p5, p6); } // 0xB8689B4E
inline VOID TaskLeaveVehicle(Ped pedHandle, Vehicle vehicleHandle, INT flags) { FiveXInvoke<VOID>(0x7B1141C6, pedHandle, vehicleHandle, flags); } // 0x7B1141C6
inline VOID TaskSkyDive(Any p0) { FiveXInvoke<VOID>(0xD3874AFA, p0); } // 0xD3874AFA
inline VOID TaskParachute(Any p0, Any p1) { FiveXInvoke<VOID>(0xEC3060A2, p0, p1); } // 0xEC3060A2
inline VOID TaskParachuteToTarget(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0xE0104D6C, p0, p1, p2, p3); } // 0xE0104D6C
inline VOID SetParachuteTaskTarget(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x6ED3AD81, p0, p1, p2, p3); } // 0x6ED3AD81
inline VOID SetParachuteTaskThrust(Any p0, Any p1) { FiveXInvoke<VOID>(0xD07C8AAA, p0, p1); } // 0xD07C8AAA
inline VOID TaskRappelFromHeli(Any p0, Any p1) { FiveXInvoke<VOID>(0x2C7ADB93, p0, p1); } // 0x2C7ADB93
inline VOID TaskVehicleDriveToCoord(Ped pedHandle, Vehicle vehicleHandle, FLOAT x, FLOAT y, FLOAT z, FLOAT speed, Any p6, Hash vehicleModel, INT drivingMode, Any p9, Any p10) { FiveXInvoke<VOID>(0xE4AC0387, pedHandle, vehicleHandle, x, y, z, speed, p6, vehicleModel, drivingMode, p9, p10); } // 0xE4AC0387
inline VOID TaskVehicleDriveToCoordLongrange(Ped driver, Vehicle vehicle, FLOAT x, FLOAT y, FLOAT z, FLOAT speed, INT driving_mode, INT stop_range) { FiveXInvoke<VOID>(0x1490182A, driver, vehicle, x, y, z, speed, driving_mode, stop_range); } // 0x1490182A
inline VOID TaskVehicleDriveWander(Ped driver, Vehicle vehicle, FLOAT unk1, Any unk2) { FiveXInvoke<VOID>(0x36EC0EB0, driver, vehicle, unk1, unk2); } // 0x36EC0EB0
inline VOID TaskFollowToOffsetOfEntity(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { FiveXInvoke<VOID>(0x2DF5A6AC, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x2DF5A6AC
inline VOID TaskGoStraightToCoord(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { FiveXInvoke<VOID>(0x80A9E7A7, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x80A9E7A7
inline VOID TaskGoStraightToCoordRelativeToEntity(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { FiveXInvoke<VOID>(0xD26CAC68, p0, p1, p2, p3, p4, p5, p6); } // 0xD26CAC68
inline VOID TaskAchieveHeading(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x0A0E9B42, p0, p1, p2); } // 0x0A0E9B42
inline VOID TaskFlushRoute() { FiveXInvoke<VOID>(0x34219154); } // 0x34219154
inline VOID TaskExtendRoute(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x43271F69, p0, p1, p2); } // 0x43271F69
inline VOID TaskFollowPointRoute(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xB837C816, p0, p1, p2); } // 0xB837C816
inline VOID TaskGoToEntity(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { FiveXInvoke<VOID>(0x374827C2, p0, p1, p2, p3, p4, p5, p6); } // 0x374827C2
inline VOID TaskSmartFleeCoord(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { FiveXInvoke<VOID>(0xB2E686FC, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xB2E686FC
inline VOID TaskSmartFleePed(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { FiveXInvoke<VOID>(0xE52EB560, p0, p1, p2, p3, p4, p5); } // 0xE52EB560
inline VOID TaskReactAndFleePed(Any p0, Any p1) { FiveXInvoke<VOID>(0x8A632BD8, p0, p1); } // 0x8A632BD8
inline VOID TaskShockingEventReact(Any p0, Any p1) { FiveXInvoke<VOID>(0x9BD00ACF, p0, p1); } // 0x9BD00ACF
inline VOID TaskWanderInArea(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { FiveXInvoke<VOID>(0xC6981FB9, p0, p1, p2, p3, p4, p5, p6); } // 0xC6981FB9
inline VOID TaskWanderStandard(Ped pedHandle, INT p1, INT p2) { FiveXInvoke<VOID>(0xAF59151A, pedHandle, p1, p2); } // 0xAF59151A
inline VOID TaskVehiclePark(Ped pedHandle, Vehicle vehicleHandle, FLOAT x, FLOAT y, FLOAT z, FLOAT heading, Any p6, Any p7, Any p8) { FiveXInvoke<VOID>(0x5C85FF90, pedHandle, vehicleHandle, x, y, z, heading, p6, p7, p8); } // 0x5C85FF90
inline VOID TaskStealthKill(Ped killer, Ped target, Hash killType, FLOAT p3, BOOL p4) { FiveXInvoke<VOID>(0x0D64C2FA, killer, target, killType, p3, p4); } // 0x0D64C2FA
inline VOID TaskPlantBomb(INT p0, FLOAT x, FLOAT y, FLOAT z, FLOAT degreeAngle) { FiveXInvoke<VOID>(0x33457535, p0, x, y, z, degreeAngle); } // 0x33457535
inline VOID TaskFollowNavMeshToCoord(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { FiveXInvoke<VOID>(0xFE4A10D9, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xFE4A10D9
inline VOID SetPedPathCanUseClimbovers(Ped ped, BOOL Toggle) { FiveXInvoke<VOID>(0xB7B7D442, ped, Toggle); } // 0xB7B7D442
inline VOID SetPedPathCanUseLadders(Ped ped, BOOL Toggle) { FiveXInvoke<VOID>(0x53A879EE, ped, Toggle); } // 0x53A879EE
inline VOID SetPedPathCanDropFromHeight(INT ped, BOOL Toggle) { FiveXInvoke<VOID>(0x394B7AC9, ped, Toggle); } // 0x394B7AC9
inline VOID SetPedPathsWidthPlant(Any p0, Any p1) { FiveXInvoke<VOID>(0x9C606EE3, p0, p1); } // 0x9C606EE3
inline VOID SetPedPathPreferToAvoidWater(Any p0, Any p1) { FiveXInvoke<VOID>(0x0EA39A29, p0, p1); } // 0x0EA39A29
inline VOID SetPedPathAvoidFire(Any p0, Any p1) { FiveXInvoke<VOID>(0xDCC5B934, p0, p1); } // 0xDCC5B934
inline Any GetNavmeshRouteDistanceRemaining(Any p0, Any p1, Any p2) { return FiveXInvoke<Any>(0xD9281778, p0, p1, p2); } // 0xD9281778
inline Any GetNavmeshRouteResult(Any p0) { return FiveXInvoke<Any>(0x96491602, p0); } // 0x96491602
inline VOID TaskGoToCoordAnyMeans(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { FiveXInvoke<VOID>(0xF91DF93B, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xF91DF93B
inline VOID TaskPlayAnim(Ped PedHandle, char* AnimSet, char* AnimationName, FLOAT Speed, FLOAT unk, INT Loop, INT LastAnimation, FLOAT PlaybackRate, BOOL xLock, BOOL yLock, BOOL zLock) { FiveXInvoke<VOID>(0x5AB552C6, PedHandle, AnimSet, AnimationName, Speed, unk, Loop, LastAnimation, PlaybackRate, xLock, yLock, zLock); } // 0x5AB552C6
inline VOID TaskPlayAnimAdvanced(Ped ped, char* animDict, char* animName, FLOAT posX, FLOAT posY, FLOAT posZ, FLOAT rotX, FLOAT rotY, FLOAT rotZ, FLOAT speed, FLOAT speedMultiplier, INT duration, Any flag, FLOAT animTime, Any p14, Any p15) { FiveXInvoke<VOID>(0x3DDEB0E6, ped, animDict, animName, posX, posY, posZ, rotX, rotY, rotZ, speed, speedMultiplier, duration, flag, animTime, p14, p15); } // 0x3DDEB0E6
inline VOID StopAnimTask(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x2B520A57, p0, p1, p2, p3); } // 0x2B520A57
inline VOID TaskScriptedAnimation(Ped ped, Any* p1, Any* p2, Any* p3, FLOAT p4, FLOAT p5) { FiveXInvoke<VOID>(0xFC2DCF47, ped, p1, p2, p3, p4, p5); } // 0xFC2DCF47
inline VOID PlayEntityScriptedAnim(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { FiveXInvoke<VOID>(0x02F72AE5, p0, p1, p2, p3, p4, p5); } // 0x02F72AE5
inline VOID StopAnimPlayback(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xE5F16398, p0, p1, p2); } // 0xE5F16398
inline VOID SetAnimWeight(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0x17229D98, p0, p1, p2, p3, p4); } // 0x17229D98
inline VOID SetAnimRate(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x6DB46584, p0, p1, p2, p3); } // 0x6DB46584
inline VOID SetAnimLooped(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x095D61A4, p0, p1, p2, p3); } // 0x095D61A4
inline VOID TaskVehiclePlayAnim(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x2B28F598, p0, p1, p2); } // 0x2B28F598
inline VOID TaskLookAtCoord(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { FiveXInvoke<VOID>(0x7B784DD8, p0, p1, p2, p3, p4, p5, p6); } // 0x7B784DD8
inline VOID TaskLookAtEntity(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0x991D6619, p0, p1, p2, p3, p4); } // 0x991D6619
inline VOID TaskClearLookAt(Any p0) { FiveXInvoke<VOID>(0x60EB4054, p0); } // 0x60EB4054
inline VOID OpenSequenceTask(Object* taskSequence) { FiveXInvoke<VOID>(0xABA6923E, taskSequence); } // 0xABA6923E
inline VOID CloseSequenceTask(Object taskSequence) { FiveXInvoke<VOID>(0x1A7CEBD0, taskSequence); } // 0x1A7CEBD0
inline VOID TaskPerformSequence(Ped ped, Object taskSequence) { FiveXInvoke<VOID>(0x4D9FBD11, ped, taskSequence); } // 0x4D9FBD11
inline VOID ClearSequenceTask(Object* taskSequence) { FiveXInvoke<VOID>(0x47ED03CE, taskSequence); } // 0x47ED03CE
inline VOID SetSequenceToRepeat(Any p0, Any p1) { FiveXInvoke<VOID>(0xCDDF1508, p0, p1); } // 0xCDDF1508
inline Any GetSequenceProgress(Any p0) { return FiveXInvoke<Any>(0xA3419909, p0); } // 0xA3419909
inline Any GetIsTaskActive(Any p0, Any p1) { return FiveXInvoke<Any>(0x86FDDF55, p0, p1); } // 0x86FDDF55
inline Any GetScriptTaskStatus(Any p0, Any p1) { return FiveXInvoke<Any>(0xB2477B23, p0, p1); } // 0xB2477B23
inline VOID TaskLeaveAnyVehicle(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xDBDD79FA, p0, p1, p2); } // 0xDBDD79FA
inline VOID TaskAimGunScripted(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x9D296BCD, p0, p1, p2, p3); } // 0x9D296BCD
inline VOID TaskAimGunScriptedWithTarget(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { FiveXInvoke<VOID>(0xFD517CE3, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xFD517CE3
inline VOID TaskAimGunAtEntity(Ped pedHandle, Entity entityHandle, INT duration, BOOL unknown) { FiveXInvoke<VOID>(0xBE32B3B6, pedHandle, entityHandle, duration, unknown); } // 0xBE32B3B6
inline VOID TaskTurnPedToFaceEntity(Ped pedHandle, Entity entityHandle, INT duration) { FiveXInvoke<VOID>(0x3C37C767, pedHandle, entityHandle, duration); } // 0x3C37C767
inline VOID TaskAimGunAtCoord(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { FiveXInvoke<VOID>(0xFBF44AD3, p0, p1, p2, p3, p4, p5, p6); } // 0xFBF44AD3
inline VOID TaskShootAtCoord(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { FiveXInvoke<VOID>(0x601C22E3, p0, p1, p2, p3, p4, p5); } // 0x601C22E3
inline VOID TaskShuffleToNextVehicleSeat(Any p0, Any p1) { FiveXInvoke<VOID>(0xBEAF8F67, p0, p1); } // 0xBEAF8F67
inline VOID ClearPedTasks(Ped pedHandle) { FiveXInvoke<VOID>(0xDE3316AB, pedHandle); } // 0xDE3316AB
inline VOID ClearPedSecondaryTask(Ped pedHandle) { FiveXInvoke<VOID>(0xA635F451, pedHandle); } // 0xA635F451
inline VOID TaskEveryoneLeaveVehicle(Any p0) { FiveXInvoke<VOID>(0xC1971F30, p0); } // 0xC1971F30
inline VOID TaskGotoEntityOffset(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { FiveXInvoke<VOID>(0x1A17A85E, p0, p1, p2, p3, p4, p5, p6); } // 0x1A17A85E
inline VOID TaskGotoEntityOffsetXy(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { FiveXInvoke<VOID>(0xBC1E3D0A, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xBC1E3D0A
inline VOID TaskTurnPedToFaceCoord(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0x30463D73, p0, p1, p2, p3, p4); } // 0x30463D73
inline VOID TaskVehicleTempAction(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x0679DFB8, p0, p1, p2, p3); } // 0x0679DFB8
inline VOID TaskVehicleMission(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { FiveXInvoke<VOID>(0x20609E56, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x20609E56
inline VOID TaskVehicleMissionPedTarget(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { FiveXInvoke<VOID>(0xC81C4677, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xC81C4677
inline VOID TaskVehicleMissionCoorsTarget(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { FiveXInvoke<VOID>(0x6719C109, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0x6719C109
inline VOID TaskVehicleEscort(Ped pedHandle, Vehicle vehicle, Vehicle targetVehicle, INT p3, FLOAT speed, Any p5, FLOAT minDistance, INT p7, FLOAT p8) { FiveXInvoke<VOID>(0x9FDCB250, pedHandle, vehicle, targetVehicle, p3, speed, p5, minDistance, p7, p8); } // 0x9FDCB250
inline VOID TaskVehicleChase(Ped pedHandle, Ped targetEntHandle) { FiveXInvoke<VOID>(0x55634798, pedHandle, targetEntHandle); } // 0x55634798
inline VOID TaskVehicleHeliProtect(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { FiveXInvoke<VOID>(0x0CB415EE, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x0CB415EE
inline VOID TaskHeliChase(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0xAC290A21, p0, p1, p2, p3, p4); } // 0xAC290A21
inline VOID TaskPlaneChase(Any p0, Any p1, FLOAT p2, FLOAT p3, FLOAT p4) { FiveXInvoke<VOID>(0x12FA1C28, p0, p1, p2, p3, p4); } // 0x12FA1C28
inline VOID TaskPlaneLand(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { FiveXInvoke<VOID>(0x5F7E23EA, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x5F7E23EA
inline VOID TaskHeliMission(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13, Any p14) { FiveXInvoke<VOID>(0x0C143E97, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14); } // 0x0C143E97
inline VOID TaskPlaneMission(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12) { FiveXInvoke<VOID>(0x1D007E65, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 0x1D007E65
inline VOID TaskBoatMission(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { FiveXInvoke<VOID>(0x5865B031, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0x5865B031
inline VOID TaskDriveBy(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { FiveXInvoke<VOID>(0x2B84D1C4, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x2B84D1C4
inline VOID SetDrivebyTaskTarget(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { FiveXInvoke<VOID>(0xDA6A6FC1, p0, p1, p2, p3, p4, p5); } // 0xDA6A6FC1
inline VOID TaskUseMobilePhone(Any p0, Any p1) { FiveXInvoke<VOID>(0x225A38C8, p0, p1); } // 0x225A38C8
inline VOID TaskUseMobilePhoneTimed(Any p0, Any p1) { FiveXInvoke<VOID>(0xC99C19F5, p0, p1); } // 0xC99C19F5
inline VOID TaskChatToPed(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { FiveXInvoke<VOID>(0xA2BE1821, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xA2BE1821
inline VOID AddFollowNavmeshToPhoneTask(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0x00D7303F, p0, p1, p2, p3, p4); } // 0x00D7303F
inline VOID TaskWarpPedIntoVehicle(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x65D4A35D, p0, p1, p2); } // 0x65D4A35D
inline VOID TaskShootAtEntity(INT p0, Entity Entity, Any p2, Any p3) { FiveXInvoke<VOID>(0xAC0631C9, p0, Entity, p2, p3); } // 0xAC0631C9
inline VOID TaskClimb(Any p0, Any p1) { FiveXInvoke<VOID>(0x90847790, p0, p1); } // 0x90847790
inline VOID TaskClimbLadder(Any p0, Any p1) { FiveXInvoke<VOID>(0x35BB4EE0, p0, p1); } // 0x35BB4EE0
inline VOID ClearPedTasksImmediately(Ped PedHandle) { FiveXInvoke<VOID>(0xBC045625, PedHandle); } // 0xBC045625
inline Any ClearPedTasksImmediately2(Ped PedHandle) { return FiveXInvoke<Any>(0xBC045625, PedHandle); } // 0xBC045625
inline VOID TaskPerformSequenceFromProgress(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0xFA60601B, p0, p1, p2, p3); } // 0xFA60601B
inline VOID SetNextDesiredMoveState(Any p0) { FiveXInvoke<VOID>(0x4E937D57, p0); } // 0x4E937D57
inline VOID SetPedDesiredMoveBlendRatio(Any p0, Any p1) { FiveXInvoke<VOID>(0xC65FC712, p0, p1); } // 0xC65FC712
inline Any GetPedDesiredMoveBlendRatio(Any p0) { return FiveXInvoke<Any>(0x5FEFAB72, p0); } // 0x5FEFAB72
inline VOID TaskGotoEntityAiming(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0xF1C493CF, p0, p1, p2, p3); } // 0xF1C493CF
inline VOID TaskSetDecisionMaker(Any p0, Any p1) { FiveXInvoke<VOID>(0x830AD50C, p0, p1); } // 0x830AD50C
inline VOID TaskSetSphereDefensiveArea(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0x9F3C5D6A, p0, p1, p2, p3, p4); } // 0x9F3C5D6A
inline VOID TaskClearDefensiveArea(Any p0) { FiveXInvoke<VOID>(0x7A05BF0D, p0); } // 0x7A05BF0D
inline VOID TaskPedSlideToCoord(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { FiveXInvoke<VOID>(0x225380EF, p0, p1, p2, p3, p4, p5); } // 0x225380EF
inline VOID TaskPedSlideToCoordHdgRate(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { FiveXInvoke<VOID>(0x38A995C1, p0, p1, p2, p3, p4, p5, p6); } // 0x38A995C1
inline Any AddCoverPoint(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return FiveXInvoke<Any>(0xA0AF0B98, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xA0AF0B98
inline VOID RemoveCoverPoint(Any p0) { FiveXInvoke<VOID>(0x0776888B, p0); } // 0x0776888B
inline BOOL IsCoverPointAtCoords(FLOAT x, FLOAT y, FLOAT z) { return FiveXInvoke<BOOL>(0x29F97A71, x, y, z); } // 0x29F97A71
inline VOID TaskCombatPed(Ped pedHandle, Player p1, Any p2, Any p3) { FiveXInvoke<VOID>(0xCB0D8932, pedHandle, p1, p2, p3); } // 0xCB0D8932
inline VOID TaskCombatPedTimed(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0xF5CA2A45, p0, p1, p2, p3); } // 0xF5CA2A45
inline VOID TaskSeekCoverFromPos(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { FiveXInvoke<VOID>(0x83F18EE9, p0, p1, p2, p3, p4, p5); } // 0x83F18EE9
inline VOID TaskSeekCoverFromPed(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0xC1EC907E, p0, p1, p2, p3); } // 0xC1EC907E
inline VOID TaskSeekCoverToCoverPoint(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { FiveXInvoke<VOID>(0x3D026B29, p0, p1, p2, p3, p4, p5, p6); } // 0x3D026B29
inline VOID TaskSeekCoverToCoords(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { FiveXInvoke<VOID>(0xFFFE754E, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xFFFE754E
inline VOID TaskPutPedDirectlyIntoCover(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { FiveXInvoke<VOID>(0xC9F00E68, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0xC9F00E68
inline VOID TaskExitCover(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0xC829FAC9, p0, p1, p2, p3, p4); } // 0xC829FAC9
inline VOID TaskPutPedDirectlyIntoMelee(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { FiveXInvoke<VOID>(0x79E1D27D, p0, p1, p2, p3, p4, p5); } // 0x79E1D27D
inline VOID TaskToggleDuck(Any p0, Any p1) { FiveXInvoke<VOID>(0x61CFBCBF, p0, p1); } // 0x61CFBCBF
inline VOID TaskGuardCurrentPosition(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x2FB099E9, p0, p1, p2, p3); } // 0x2FB099E9
inline VOID TaskGuardSphereDefensiveArea(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { FiveXInvoke<VOID>(0x86B76CB7, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0x86B76CB7
inline VOID TaskStandGuard(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { FiveXInvoke<VOID>(0xD130F636, p0, p1, p2, p3, p4, p5); } // 0xD130F636
inline VOID SetDriveTaskCruiseSpeed(Any p0, Any p1) { FiveXInvoke<VOID>(0x3CEC07B1, p0, p1); } // 0x3CEC07B1
inline VOID SetDriveTaskMaxCruiseSpeed(Any p0, Any p1) { FiveXInvoke<VOID>(0x7FDF6131, p0, p1); } // 0x7FDF6131
inline VOID SetDriveTaskDrivingStyle(Any DRIVER_PED, Any DRIVING_STYLE) { FiveXInvoke<VOID>(0x59C5FAD7, DRIVER_PED, DRIVING_STYLE); } // 0x59C5FAD7
inline VOID AddCoverBlockingArea(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { FiveXInvoke<VOID>(0x3536946F, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x3536946F
inline VOID RemoveAllCoverBlockingAreas() { FiveXInvoke<VOID>(0xCF9221A7); } // 0xCF9221A7
inline VOID TaskStartScenarioInPlace(Any p0, char* p1, Any p2, Any p3) { FiveXInvoke<VOID>(0xE50D6DDE, p0, p1, p2, p3); } // 0xE50D6DDE
inline VOID TaskStartScenarioAtPosition(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { FiveXInvoke<VOID>(0xAA2C4AC2, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xAA2C4AC2
inline VOID TaskUseNearestScenarioToCoord(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { FiveXInvoke<VOID>(0x9C50FBF0, p0, p1, p2, p3, p4, p5); } // 0x9C50FBF0
inline VOID TaskUseNearestScenarioToCoordWarp(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { FiveXInvoke<VOID>(0x1BE9D65C, p0, p1, p2, p3, p4, p5); } // 0x1BE9D65C
inline VOID TaskUseNearestScenarioChainToCoord(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { FiveXInvoke<VOID>(0xE32FFB22, p0, p1, p2, p3, p4, p5); } // 0xE32FFB22
inline VOID TaskUseNearestScenarioChainToCoordWarp(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { FiveXInvoke<VOID>(0xBAB4C0AE, p0, p1, p2, p3, p4, p5); } // 0xBAB4C0AE
inline BOOL DoesScenarioExistInArea(Any p0, Any p1, Any p2, Any p3, Any p4) { return FiveXInvoke<BOOL>(0xFA7F5047, p0, p1, p2, p3, p4); } // 0xFA7F5047
inline BOOL IsScenarioOccupied(Any p0, Any p1, Any p2, Any p3, Any p4) { return FiveXInvoke<BOOL>(0x697FC008, p0, p1, p2, p3, p4); } // 0x697FC008
inline BOOL DoesScenarioGroupExist(Any p0) { return FiveXInvoke<BOOL>(0x5F072EB9, p0); } // 0x5F072EB9
inline BOOL IsScenarioGroupEnabled(Any p0) { return FiveXInvoke<BOOL>(0x90991122, p0); } // 0x90991122
inline VOID SetScenarioGroupEnabled(Any p0, Any p1) { FiveXInvoke<VOID>(0x116997B1, p0, p1); } // 0x116997B1
inline VOID SetExclusiveScenarioGroup(Any p0) { FiveXInvoke<VOID>(0x59DB8F26, p0); } // 0x59DB8F26
inline VOID ResetExclusiveScenarioGroup() { FiveXInvoke<VOID>(0x17F9DFE8); } // 0x17F9DFE8
inline BOOL IsScenarioTypeEnabled(Any p0) { return FiveXInvoke<BOOL>(0xAE37E969, p0); } // 0xAE37E969
inline VOID SetScenarioTypeEnabled(Any p0, Any p1) { FiveXInvoke<VOID>(0xDB18E5DE, p0, p1); } // 0xDB18E5DE
inline BOOL IsPedActiveInScenario(Any p0) { return FiveXInvoke<BOOL>(0x05038F1A, p0); } // 0x05038F1A
inline VOID TaskCombatHatedTargetsInArea(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { FiveXInvoke<VOID>(0xDF099E18, p0, p1, p2, p3, p4, p5); } // 0xDF099E18
inline VOID TaskCombatHatedTargetsAroundPed(Player p0, FLOAT AreaToAttack, Any p2) { FiveXInvoke<VOID>(0x2E7064E4, p0, AreaToAttack, p2); } // 0x2E7064E4
inline VOID TaskCombatHatedTargetsAroundPedTimed(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0xF127AD6A, p0, p1, p2, p3); } // 0xF127AD6A
inline VOID TaskThrowProjectile(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0xF65C20A7, p0, p1, p2, p3); } // 0xF65C20A7
inline VOID TaskSwapWeapon(Any p0, Any p1) { FiveXInvoke<VOID>(0xDAF4F8FC, p0, p1); } // 0xDAF4F8FC
inline VOID TaskReloadWeapon(Any p0, Any p1) { FiveXInvoke<VOID>(0xCA6E91FD, p0, p1); } // 0xCA6E91FD
inline BOOL IsPedGettingUp(Any p0) { return FiveXInvoke<BOOL>(0x320813E6, p0); } // 0x320813E6
inline VOID TaskWrithe(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x0FDC54FC, p0, p1, p2, p3); } // 0x0FDC54FC
inline BOOL IsPedInWrithe(Any p0) { return FiveXInvoke<BOOL>(0x09E61921, p0); } // 0x09E61921
inline VOID OpenPatrolRoute(Any p0) { FiveXInvoke<VOID>(0xF33F83CA, p0); } // 0xF33F83CA
inline VOID ClosePatrolRoute() { FiveXInvoke<VOID>(0x67305E59); } // 0x67305E59
inline VOID AddPatrolRouteNode(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { FiveXInvoke<VOID>(0x21B48F10, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x21B48F10
inline VOID AddPatrolRouteLink(Any p0, Any p1) { FiveXInvoke<VOID>(0xD8761BB3, p0, p1); } // 0xD8761BB3
inline VOID CreatePatrolRoute() { FiveXInvoke<VOID>(0x0A6C7864); } // 0x0A6C7864
inline VOID DeletePatrolRoute(Any p0) { FiveXInvoke<VOID>(0x2A4E6706, p0); } // 0x2A4E6706
inline VOID TaskPatrol(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0xB92E5AF6, p0, p1, p2, p3, p4); } // 0xB92E5AF6
inline VOID TaskStayInCover(Any p0) { FiveXInvoke<VOID>(0xA27A9413, p0); } // 0xA27A9413
inline VOID AddVehicleSubtaskAttackPed(Any p0, Any p1) { FiveXInvoke<VOID>(0x80461113, p0, p1); } // 0x80461113
inline VOID TaskVehicleShootAtPed(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x59677BA0, p0, p1, p2); } // 0x59677BA0
inline VOID TaskVehicleAimAtPed(Any p0, Any p1) { FiveXInvoke<VOID>(0x920AE6DB, p0, p1); } // 0x920AE6DB
inline VOID TaskVehicleShootAtCoord(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0xA7AAA4D6, p0, p1, p2, p3, p4); } // 0xA7AAA4D6
inline VOID TaskVehicleAimAtCoord(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x010F47CE, p0, p1, p2, p3); } // 0x010F47CE
inline VOID TaskVehicleGotoNavmesh(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { FiveXInvoke<VOID>(0x55CF3BCD, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x55CF3BCD
inline VOID TaskGoToCoordWhileAimingAtCoord(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13, Any p14) { FiveXInvoke<VOID>(0x1552DC91, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14); } // 0x1552DC91
inline VOID TaskGoToCoordWhileAimingAtEntity(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13) { FiveXInvoke<VOID>(0x9BD52ABD, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); } // 0x9BD52ABD
inline VOID TaskGoToCoordAndAimAtHatedEntitiesNearCoord(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13, Any p14) { FiveXInvoke<VOID>(0x3F91358E, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14); } // 0x3F91358E
inline VOID TaskGoToEntityWhileAimingAtCoord(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { FiveXInvoke<VOID>(0xD896CD82, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0xD896CD82
inline VOID TaskGoToEntityWhileAimingAtEntity(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { FiveXInvoke<VOID>(0x68E36B7A, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x68E36B7A
inline VOID SetHighFallTask(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0xBBB26172, p0, p1, p2, p3); } // 0xBBB26172
inline VOID RequestWaypointRecording(Any p0) { FiveXInvoke<VOID>(0xAFABFB5D, p0); } // 0xAFABFB5D
inline VOID RemoveWaypointRecording(Any p0) { FiveXInvoke<VOID>(0x624530B0, p0); } // 0x624530B0
inline VOID TaskFollowWaypointRecording(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0xADF9904D, p0, p1, p2, p3, p4); } // 0xADF9904D
inline BOOL IsWaypointPlaybackGoingOnForPed(Any p0) { return FiveXInvoke<BOOL>(0x85B7725F, p0); } // 0x85B7725F
inline Any GetPedWaypointProgress(Any p0) { return FiveXInvoke<Any>(0x3595B104, p0); } // 0x3595B104
inline Any GetPedWaypointDistance(Any p0) { return FiveXInvoke<Any>(0x084B35B0, p0); } // 0x084B35B0
inline Any SetPedWaypointRouteOffset(Any p0, Any p1, Any p2, Any p3) { return FiveXInvoke<Any>(0xF867F747, p0, p1, p2, p3); } // 0xF867F747
inline Any WaypointPlaybackGetIsPaused(Any p0) { return FiveXInvoke<Any>(0xA6BB5717, p0); } // 0xA6BB5717
inline VOID WaypointPlaybackPause(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xFE39ECF8, p0, p1, p2); } // 0xFE39ECF8
inline VOID WaypointPlaybackResume(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x50F392EF, p0, p1, p2, p3); } // 0x50F392EF
inline VOID WaypointPlaybackOverrideSpeed(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x23E6BA96, p0, p1, p2); } // 0x23E6BA96
inline VOID WaypointPlaybackUseDefaultSpeed(Any p0) { FiveXInvoke<VOID>(0x1BBB2CAC, p0); } // 0x1BBB2CAC
inline VOID WaypointPlaybackStartAimingAtPed(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x75E60CF6, p0, p1, p2); } // 0x75E60CF6
inline VOID WaypointPlaybackStartAimingAtCoord(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0xF120A34E, p0, p1, p2, p3, p4); } // 0xF120A34E
inline VOID WaypointPlaybackStartShootingAtPed(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0xBD5F0EB8, p0, p1, p2, p3); } // 0xBD5F0EB8
inline VOID WaypointPlaybackStartShootingAtCoord(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { FiveXInvoke<VOID>(0xCDDB44D5, p0, p1, p2, p3, p4, p5); } // 0xCDDB44D5
inline VOID WaypointPlaybackStopAimingOrShooting(Any p0) { FiveXInvoke<VOID>(0x6D7CF40C, p0); } // 0x6D7CF40C
inline VOID AssistedMovementRequestRoute(char* route) { FiveXInvoke<VOID>(0x48262EDA, route); } // 0x48262EDA
inline VOID AssistedMovementRemoveRoute(Any p0) { FiveXInvoke<VOID>(0xB3CEC06F, p0); } // 0xB3CEC06F
inline VOID TaskVehicleFollowWaypointRecording(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { FiveXInvoke<VOID>(0x959818B6, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x959818B6
inline BOOL IsWaypointPlaybackGoingOnForVehicle(Any p0) { return FiveXInvoke<BOOL>(0x80DD15DB, p0); } // 0x80DD15DB
inline Any GetVehicleWaypointProgress(Any p0) { return FiveXInvoke<Any>(0xD3CCF64E, p0); } // 0xD3CCF64E
inline Any GetVehicleWaypointTargetPoint(Any p0) { return FiveXInvoke<Any>(0x81049608, p0); } // 0x81049608
inline VOID VehicleWaypointPlaybackPause(Any p0) { FiveXInvoke<VOID>(0x7C00B415, p0); } // 0x7C00B415
inline VOID VehicleWaypointPlaybackResume(Any p0) { FiveXInvoke<VOID>(0xBEB14C82, p0); } // 0xBEB14C82
inline VOID VehicleWaypointPlaybackUseDefaultSpeed(Any p0) { FiveXInvoke<VOID>(0x923C3AA4, p0); } // 0x923C3AA4
inline VOID VehicleWaypointPlaybackOverrideSpeed(Any p0, Any p1) { FiveXInvoke<VOID>(0xBE1E7BB4, p0, p1); } // 0xBE1E7BB4
inline VOID TaskSetBlockingOfNonTemporaryEvents(Any p0, Any p1) { FiveXInvoke<VOID>(0x1B54FB6B, p0, p1); } // 0x1B54FB6B
inline VOID TaskForceMotionState(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xCAD2EF77, p0, p1, p2); } // 0xCAD2EF77
inline BOOL IsPedStill(Any p0) { return FiveXInvoke<BOOL>(0x09E3418D, p0); } // 0x09E3418D
inline BOOL IsPedWalking(Any p0) { return FiveXInvoke<BOOL>(0x4B865C4A, p0); } // 0x4B865C4A
inline BOOL IsPedRunning(Any p0) { return FiveXInvoke<BOOL>(0xE9A5578F, p0); } // 0xE9A5578F
inline BOOL IsPedSprinting(Any p0) { return FiveXInvoke<BOOL>(0x4F3E0633, p0); } // 0x4F3E0633
inline BOOL IsPedStrafing(Any p0) { return FiveXInvoke<BOOL>(0xEFEED13C, p0); } // 0xEFEED13C
inline VOID TaskSynchronizedScene(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { FiveXInvoke<VOID>(0x4F217E7B, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x4F217E7B
inline VOID TaskArrestPed(Any p0, Any p1) { FiveXInvoke<VOID>(0xBC0F153D, p0, p1); } // 0xBC0F153D
inline BOOL IsPedRunningArrestTask(Any p0) { return FiveXInvoke<BOOL>(0x6942DB7A, p0); } // 0x6942DB7A
inline BOOL IsPedBeingArrested(Any p0) { return FiveXInvoke<BOOL>(0x5FF6C2ED, p0); } // 0x5FF6C2ED
inline VOID UncuffPed(Any p0) { FiveXInvoke<VOID>(0xA23A1D61, p0); } // 0xA23A1D61
inline BOOL IsPedCuffed(Any p0) { return FiveXInvoke<BOOL>(0x511CE741, p0); } // 0x511CE741
inline VOID PlayPedRingtone(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x1D530E47, p0, p1, p2); } // 0x1D530E47
inline BOOL IsPedRingtonePlaying(Any p0) { return FiveXInvoke<BOOL>(0xFE576EE4, p0); } // 0xFE576EE4
inline VOID StopPedRingtone(Ped p0) { FiveXInvoke<VOID>(0xFEEA107C, p0); } // 0xFEEA107C
inline BOOL IsMobilePhoneCallOngoing() { return FiveXInvoke<BOOL>(0x4ED1400A); } // 0x4ED1400A
inline VOID CreateNewScriptedConversation() { FiveXInvoke<VOID>(0xB2BC25F8); } // 0xB2BC25F8
inline VOID AddLineToConversation(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { FiveXInvoke<VOID>(0x96CD0513, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0x96CD0513
inline VOID AddPedToConversation(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xF8D5EB86, p0, p1, p2); } // 0xF8D5EB86
inline VOID SetMicrophonePosition(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { FiveXInvoke<VOID>(0xAD7BB191, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xAD7BB191
inline VOID StartScriptPhoneConversation(Any p0, Any p1) { FiveXInvoke<VOID>(0x38E42D07, p0, p1); } // 0x38E42D07
inline VOID PreloadScriptPhoneConversation(Any p0, Any p1) { FiveXInvoke<VOID>(0x9ACB213A, p0, p1); } // 0x9ACB213A
inline VOID StartScriptConversation(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0xE5DE7D9D, p0, p1, p2, p3); } // 0xE5DE7D9D
inline VOID PreloadScriptConversation(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0xDDF5C579, p0, p1, p2, p3); } // 0xDDF5C579
inline VOID StartPreloadedConversation() { FiveXInvoke<VOID>(0xA170261B); } // 0xA170261B
inline BOOL IsScriptedConversationOngoing() { return FiveXInvoke<BOOL>(0xCB8FD96F); } // 0xCB8FD96F
inline BOOL IsScriptedConversationLoaded() { return FiveXInvoke<BOOL>(0xE1870EA9); } // 0xE1870EA9
inline Any GetCurrentScriptedConversationLine() { return FiveXInvoke<Any>(0x9620E41F); } // 0x9620E41F
inline VOID PauseScriptedConversation(Any p0) { FiveXInvoke<VOID>(0xE2C9C6F8, p0); } // 0xE2C9C6F8
inline VOID RestartScriptedConversation() { FiveXInvoke<VOID>(0x6CB24B56); } // 0x6CB24B56
inline INT StopScriptedConversation(bool p0) { return FiveXInvoke<INT>(0xAB77DA7D, p0); } // 0xAB77DA7D
inline VOID SkipToNextScriptedConversationLine() { FiveXInvoke<VOID>(0x85C98304); } // 0x85C98304
inline VOID InterruptConversation(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xF3A67AF3, p0, p1, p2); } // 0xF3A67AF3
inline VOID RegisterScriptWithAudio(Any p0) { FiveXInvoke<VOID>(0xA6203643, p0); } // 0xA6203643
inline VOID UnregisterScriptWithAudio() { FiveXInvoke<VOID>(0x66728EFE); } // 0x66728EFE
inline Any RequestMissionAudioBank(Any p0, Any p1) { return FiveXInvoke<Any>(0x916E37CA, p0, p1); } // 0x916E37CA
inline Any RequestAmbientAudioBank(Any p0, Any p1) { return FiveXInvoke<Any>(0x23C88BC7, p0, p1); } // 0x23C88BC7
inline Any RequestScriptAudioBank(Any p0, Any p1) { return FiveXInvoke<Any>(0x21322887, p0, p1); } // 0x21322887
inline Any HintAmbientAudioBank(Any p0, Any p1) { return FiveXInvoke<Any>(0xF1850DDC, p0, p1); } // 0xF1850DDC
inline Any HintScriptAudioBank(Any p0, Any p1) { return FiveXInvoke<Any>(0x41FA0E51, p0, p1); } // 0x41FA0E51
inline VOID ReleaseMissionAudioBank() { FiveXInvoke<VOID>(0x8E8824C7); } // 0x8E8824C7
inline VOID ReleaseAmbientAudioBank() { FiveXInvoke<VOID>(0x8C938784); } // 0x8C938784
inline VOID ReleaseNamedScriptAudioBank(Any p0) { FiveXInvoke<VOID>(0x16707ABC, p0); } // 0x16707ABC
inline VOID ReleaseScriptAudioBank() { FiveXInvoke<VOID>(0x22F865E5); } // 0x22F865E5
inline Any GetSoundId() { return FiveXInvoke<Any>(0x6AE0AD56); } // 0x6AE0AD56
inline VOID ReleaseSoundId(Any p0) { FiveXInvoke<VOID>(0x9C080899, p0); } // 0x9C080899
inline VOID PlaySound(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0xB6E1917F, p0, p1, p2, p3, p4); } // 0xB6E1917F
inline VOID PlaySoundFrontend(INT p0, char* SoundFrom, char* SoundSet) { FiveXInvoke<VOID>(0x2E458F74, p0, SoundFrom, SoundSet); } // 0x2E458F74
inline VOID PlaySoundFromEntity(INT p0, char* p1, Entity entity, char* p3, Any p4, Any p5) { FiveXInvoke<VOID>(0x95AE00F8, p0, p1, entity, p3, p4, p5); } // 0x95AE00F8
inline VOID PlaySoundFromCoord(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { FiveXInvoke<VOID>(0xCAD3E2D5, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xCAD3E2D5
inline VOID StopSound(Any p0) { FiveXInvoke<VOID>(0xCD7F4030, p0); } // 0xCD7F4030
inline Any GetNetworkIdFromSoundId(Any p0) { return FiveXInvoke<Any>(0x2576F610, p0); } // 0x2576F610
inline VOID SetVariableOnSound(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x606EE5FA, p0, p1, p2); } // 0x606EE5FA
inline VOID SetVariableOnStream(Any p0, Any p1) { FiveXInvoke<VOID>(0xF67BB44C, p0, p1); } // 0xF67BB44C
inline VOID OverrideUnderwaterStream(Any p0, Any p1) { FiveXInvoke<VOID>(0x9A083B7E, p0, p1); } // 0x9A083B7E
inline BOOL HasSoundFinished(Any p0) { return FiveXInvoke<BOOL>(0xE85AEC2E, p0); } // 0xE85AEC2E
inline VOID PlayAmbientSpeech1(Ped pedHandle, char* speechName, char* speechParam) { FiveXInvoke<VOID>(0x5C57B85D, pedHandle, speechName, speechParam); } // 0x5C57B85D
inline VOID PlayAmbientSpeech2(Ped pedHandle, char* speechName, char* speechParam) { FiveXInvoke<VOID>(0x444180DB, pedHandle, speechName, speechParam); } // 0x444180DB
inline VOID OverrideTrevorRage(Any p0) { FiveXInvoke<VOID>(0x05B9B5CF, p0); } // 0x05B9B5CF
inline VOID ResetTrevorRage() { FiveXInvoke<VOID>(0xE80CF0D4); } // 0xE80CF0D4
inline VOID SetPlayerAngry(Any p0, Any p1) { FiveXInvoke<VOID>(0x782CA58D, p0, p1); } // 0x782CA58D
inline VOID PlayPain(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x874BD6CB, p0, p1, p2); } // 0x874BD6CB
inline VOID ReleaseWeaponAudio() { FiveXInvoke<VOID>(0x6096504C); } // 0x6096504C
inline VOID SetAmbientVoiceName(Any p0, char* p1) { FiveXInvoke<VOID>(0xBD2EA1A1, p0, p1); } // 0xBD2EA1A1
inline VOID StopCurrentPlayingAmbientSpeech(Any p0) { FiveXInvoke<VOID>(0xBB8E64BF, p0); } // 0xBB8E64BF
inline BOOL IsAmbientSpeechPlaying(Any p0) { return FiveXInvoke<BOOL>(0x1972E8AA, p0); } // 0x1972E8AA
inline BOOL IsScriptedSpeechPlaying(Any p0) { return FiveXInvoke<BOOL>(0x2C653904, p0); } // 0x2C653904
inline BOOL IsAnySpeechPlaying(Any p0) { return FiveXInvoke<BOOL>(0x2B74A6D6, p0); } // 0x2B74A6D6
inline BOOL IsPedInCurrentConversation(Any p0) { return FiveXInvoke<BOOL>(0x7B2F0743, p0); } // 0x7B2F0743
inline VOID SetPedIsDrunk(Any p0, Any p1) { FiveXInvoke<VOID>(0xD2EA77A3, p0, p1); } // 0xD2EA77A3
inline VOID SetAnimalMood(Any p0, Any p1) { FiveXInvoke<VOID>(0x3EA7C6CB, p0, p1); } // 0x3EA7C6CB
inline BOOL IsMobilePhoneRadioActive() { return FiveXInvoke<BOOL>(0x6E502A5B); } // 0x6E502A5B
inline VOID SetMobilePhoneRadioState(Any p0) { FiveXInvoke<VOID>(0xE1E0ED34, p0); } // 0xE1E0ED34
inline Any GetPlayerRadioStationIndex() { return FiveXInvoke<Any>(0x1C4946AC); } // 0x1C4946AC
inline Any GetPlayerRadioStationName() { return FiveXInvoke<Any>(0xD909C107); } // 0xD909C107
inline Any GetRadioStationName(INT radioStation) { return FiveXInvoke<Any>(0x3DF493BC, radioStation); } // 0x3DF493BC
inline Any GetPlayerRadioStationGenre() { return FiveXInvoke<Any>(0x872CF0EA); } // 0x872CF0EA
inline BOOL IsRadioRetuning() { return FiveXInvoke<BOOL>(0xCF29097B); } // 0xCF29097B
inline VOID SetRadioToStationName(char* radioStation) { FiveXInvoke<VOID>(0x7B36E35E, radioStation); } // 0x7B36E35E
inline VOID SetVehRadioStation(Object hVehicle, char* radioStation) { FiveXInvoke<VOID>(0xE391F55F, hVehicle, radioStation); } // 0xE391F55F
inline VOID SetEmitterRadioStation(Any p0, Any p1) { FiveXInvoke<VOID>(0x87431585, p0, p1); } // 0x87431585
inline VOID SetStaticEmitterEnabled(Any p0, Any p1) { FiveXInvoke<VOID>(0x91F72E92, p0, p1); } // 0x91F72E92
inline VOID SetRadioToStationIndex(Any p0) { FiveXInvoke<VOID>(0x1D82766D, p0); } // 0x1D82766D
inline VOID SetFrontendRadioActive(Any p0) { FiveXInvoke<VOID>(0xB1172075, p0); } // 0xB1172075
inline VOID UnlockMissionNewsStory(Any p0) { FiveXInvoke<VOID>(0xCCD9ABE4, p0); } // 0xCCD9ABE4
inline Any GetNumberOfPassengerVoiceVariations(Any p0) { return FiveXInvoke<Any>(0x27305D37, p0); } // 0x27305D37
inline Any GetAudibleMusicTrackTextId() { return FiveXInvoke<Any>(0xA2B88CA7); } // 0xA2B88CA7
inline VOID PlayEndCreditsMusic(Any p0) { FiveXInvoke<VOID>(0x8E88B3CC, p0); } // 0x8E88B3CC
inline VOID SkipRadioForward() { FiveXInvoke<VOID>(0x10D36630); } // 0x10D36630
inline VOID FreezeRadioStation(Any p0) { FiveXInvoke<VOID>(0x286BF543, p0); } // 0x286BF543
inline VOID UnfreezeRadioStation(Any p0) { FiveXInvoke<VOID>(0x4D46202C, p0); } // 0x4D46202C
inline VOID SetRadioAutoUnfreeze(Any p0) { FiveXInvoke<VOID>(0xA40196BF, p0); } // 0xA40196BF
inline VOID SetInitialPlayerStation(Any p0) { FiveXInvoke<VOID>(0x9B069233, p0); } // 0x9B069233
inline VOID SetUserRadioControlEnabled(Any p0) { FiveXInvoke<VOID>(0x52E054CE, p0); } // 0x52E054CE
inline VOID SetRadioTrack(Any p0, Any p1) { FiveXInvoke<VOID>(0x76E96212, p0, p1); } // 0x76E96212
inline VOID SetVehicleRadioLoud(Any p0, BOOL p1) { FiveXInvoke<VOID>(0x8D9EDD99, p0, p1); } // 0x8D9EDD99
inline VOID SetMobileRadioEnabledDuringGameplay(BOOL Toggle) { FiveXInvoke<VOID>(0x990085F0, Toggle); } // 0x990085F0
inline VOID SetVehicleRadioEnabled(Any p0, Any p1) { FiveXInvoke<VOID>(0x6F812CAB, p0, p1); } // 0x6F812CAB
inline Any FindRadioStationIndex(Any p0) { return FiveXInvoke<Any>(0xECA1512F, p0); } // 0xECA1512F
inline VOID SetAmbientZoneState(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x2849CAC9, p0, p1, p2); } // 0x2849CAC9
inline VOID ClearAmbientZoneState(Any p0, Any p1) { FiveXInvoke<VOID>(0xCDFF3C82, p0, p1); } // 0xCDFF3C82
inline VOID SetAmbientZoneListState(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xBF80B412, p0, p1, p2); } // 0xBF80B412
inline VOID ClearAmbientZoneListState(Any p0, Any p1) { FiveXInvoke<VOID>(0x38B9B8D4, p0, p1); } // 0x38B9B8D4
inline VOID SetAmbientZoneStatePersistent(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xC1FFB672, p0, p1, p2); } // 0xC1FFB672
inline VOID SetAmbientZoneListStatePersistent(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x5F5A2605, p0, p1, p2); } // 0x5F5A2605
inline BOOL IsAmbientZoneEnabled(Any p0) { return FiveXInvoke<BOOL>(0xBFABD872, p0); } // 0xBFABD872
inline VOID SetCutsceneAudioOverride(Any p0) { FiveXInvoke<VOID>(0xCE1332B7, p0); } // 0xCE1332B7
inline VOID GetPlayerHeadsetSoundAlternate(Any p0, Any p1) { FiveXInvoke<VOID>(0xD63CF33A, p0, p1); } // 0xD63CF33A
inline Any PlayPoliceReport(char* p0, FLOAT p1) { return FiveXInvoke<Any>(0x3F277B62, p0, p1); } // 0x3F277B62
inline VOID BlipSiren(Any p0) { FiveXInvoke<VOID>(0xC0EB6924, p0); } // 0xC0EB6924
inline VOID OverrideVehHorn(Vehicle p0, BOOL p1, INT p2) { FiveXInvoke<VOID>(0x2ACAB783, p0, p1, p2); } // 0x2ACAB783
inline BOOL IsHornActive(Any p0) { return FiveXInvoke<BOOL>(0x20E2BDD0, p0); } // 0x20E2BDD0
inline VOID SetAggressiveHorns(INT p0) { FiveXInvoke<VOID>(0x01D6EABE, p0); } // 0x01D6EABE
inline BOOL IsStreamPlaying() { return FiveXInvoke<BOOL>(0xF1F51A14); } // 0xF1F51A14
inline Any GetStreamPlayTime() { return FiveXInvoke<Any>(0xB4F0AD56); } // 0xB4F0AD56
inline Any LoadStream(Any p0, Any p1) { return FiveXInvoke<Any>(0x0D89599D, p0, p1); } // 0x0D89599D
inline Any LoadStreamWithStartOffset(Any p0, Any p1, Any p2) { return FiveXInvoke<Any>(0xE5B5745C, p0, p1, p2); } // 0xE5B5745C
inline VOID PlayStreamFromVehicle(Any p0) { FiveXInvoke<VOID>(0xF8E4BDA2, p0); } // 0xF8E4BDA2
inline VOID PlayStreamFromObject(Any p0) { FiveXInvoke<VOID>(0xC5266BF7, p0); } // 0xC5266BF7
inline VOID PlayStreamFrontend() { FiveXInvoke<VOID>(0x2C2A16BC); } // 0x2C2A16BC
inline VOID SpecialFrontendEqual(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x6FE5D865, p0, p1, p2); } // 0x6FE5D865
inline VOID StopStream() { FiveXInvoke<VOID>(0xD1E364DE); } // 0xD1E364DE
inline VOID StopPedSpeaking(Any p0, Any p1) { FiveXInvoke<VOID>(0xFF92B49D, p0, p1); } // 0xFF92B49D
inline VOID DisablePedPainAudio(Any p0, Any p1) { FiveXInvoke<VOID>(0x3B8E2D5F, p0, p1); } // 0x3B8E2D5F
inline BOOL IsAmbientSpeechDisabled(Any p0) { return FiveXInvoke<BOOL>(0x109D1F89, p0); } // 0x109D1F89
inline VOID SetSirenWithNoDriver(Any p0, Any p1) { FiveXInvoke<VOID>(0x77182D58, p0, p1); } // 0x77182D58
inline VOID SetHornEnabled(Any p0, Any p1) { FiveXInvoke<VOID>(0x6EB92D05, p0, p1); } // 0x6EB92D05
inline VOID SetAudioVehiclePriority(Any p0, Any p1) { FiveXInvoke<VOID>(0x271A9766, p0, p1); } // 0x271A9766
inline VOID UseSirenAsHorn(Any p0, Any p1) { FiveXInvoke<VOID>(0xC6BC16F3, p0, p1); } // 0xC6BC16F3
inline VOID ForceUseAudioGameObject(Vehicle vehicle, char* gameObjectName) { FiveXInvoke<VOID>(0x33B0B007, vehicle, gameObjectName); } // 0x33B0B007
inline VOID SetVehicleBoostActive(Vehicle vehicle, BOOL Toggle) { FiveXInvoke<VOID>(0x072F15F2, vehicle, Toggle); } // 0x072F15F2
inline VOID PlayVehicleDoorOpenSound(Any p0, Any p1) { FiveXInvoke<VOID>(0x84930330, p0, p1); } // 0x84930330
inline VOID PlayVehicleDoorCloseSound(Any p0, Any p1) { FiveXInvoke<VOID>(0xBA2CF407, p0, p1); } // 0xBA2CF407
inline BOOL IsGameInControlOfMusic() { return FiveXInvoke<BOOL>(0x7643170D); } // 0x7643170D
inline VOID SetGpsActive(Any p0) { FiveXInvoke<VOID>(0x0FC3379A, p0); } // 0x0FC3379A
inline VOID PlayMissionCompleteAudio(char* p0) { FiveXInvoke<VOID>(0x3033EA1D, p0); } // 0x3033EA1D
inline BOOL IsMissionCompletePlaying() { return FiveXInvoke<BOOL>(0x939982A1); } // 0x939982A1
inline Any StartAudioScene(Any p0) { return FiveXInvoke<Any>(0xE48D757B, p0); } // 0xE48D757B
inline VOID StopAudioScene(Any p0) { FiveXInvoke<VOID>(0xA08D8C58, p0); } // 0xA08D8C58
inline VOID StopAudioScenes() { FiveXInvoke<VOID>(0xF6C7342A); } // 0xF6C7342A
inline BOOL IsAudioSceneActive(Any p0) { return FiveXInvoke<BOOL>(0xACBED05C, p0); } // 0xACBED05C
inline VOID SetAudioSceneVariable(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x19BB3CE8, p0, p1, p2); } // 0x19BB3CE8
inline Any AudioIsScriptedMusicPlaying() { return FiveXInvoke<Any>(0x86E995D1); } // 0x86E995D1
inline Any PrepareMusicEvent(Any p0) { return FiveXInvoke<Any>(0x534A5C1C, p0); } // 0x534A5C1C
inline Any CancelMusicEvent(Any p0) { return FiveXInvoke<Any>(0x89FF942D, p0); } // 0x89FF942D
inline Any TriggerMusicEvent(Any p0) { return FiveXInvoke<Any>(0xB6094948, p0); } // 0xB6094948
inline Any GetMusicPlaytime() { return FiveXInvoke<Any>(0xD633C809); } // 0xD633C809
inline VOID ClearAllBrokenGlass() { FiveXInvoke<VOID>(0xE6B033BF); } // 0xE6B033BF
inline Any PrepareAlarm(Any p0) { return FiveXInvoke<Any>(0x084932E8, p0); } // 0x084932E8
inline VOID StartAlarm(Any p0, Any p1) { FiveXInvoke<VOID>(0x703F524B, p0, p1); } // 0x703F524B
inline VOID StopAlarm(Any p0, Any p1) { FiveXInvoke<VOID>(0xF987BE8C, p0, p1); } // 0xF987BE8C
inline VOID StopAllAlarms(Any p0) { FiveXInvoke<VOID>(0xC3CB9DC6, p0); } // 0xC3CB9DC6
inline BOOL IsAlarmPlaying(Any p0) { return FiveXInvoke<BOOL>(0x9D8E1D23, p0); } // 0x9D8E1D23
inline Any GetVehicleDefaultHorn(Any p0) { return FiveXInvoke<Any>(0xE84ABC19, p0); } // 0xE84ABC19
inline VOID ResetPedAudioFlags(Any p0) { FiveXInvoke<VOID>(0xDF720C86, p0); } // 0xDF720C86
inline VOID SetAudioFlag(Any p0, Any p1) { FiveXInvoke<VOID>(0x1C09C9E0, p0, p1); } // 0x1C09C9E0
inline Any PrepareSynchronizedAudioEvent(Any p0, Any p1) { return FiveXInvoke<Any>(0xE1D91FD0, p0, p1); } // 0xE1D91FD0
inline Any PrepareSynchronizedAudioEventForScene(Any p0, Any p1) { return FiveXInvoke<Any>(0x7652DD49, p0, p1); } // 0x7652DD49
inline Any PlaySynchronizedAudioEvent(Any p0) { return FiveXInvoke<Any>(0x507F3241, p0); } // 0x507F3241
inline Any StopSynchronizedAudioEvent(Any p0) { return FiveXInvoke<Any>(0xADEED2B4, p0); } // 0xADEED2B4
inline VOID RenderScriptCams(BOOL render, BOOL ease, INT easeTime, BOOL p3, BOOL p4) { FiveXInvoke<VOID>(0x74337969, render, ease, easeTime, p3, p4); } // 0x07E5B515DB0636FC 0x74337969
inline Any CreateCam(char* camName, BOOL p1) { return FiveXInvoke<Any>(0xE9BF2A7D, camName, p1); } // 0xE9BF2A7D
inline Cam CreateCamWithParams(char* camName, FLOAT posX, FLOAT posY, FLOAT posZ, FLOAT rotX, FLOAT rotY, FLOAT rotZ, FLOAT fov, INT p8, INT p9) { return FiveXInvoke<Any>(0x23B02F15, camName, posX, posY, posZ, rotX, rotY, rotZ, fov, p8, p9); } // 0x23B02F15
inline Cam CreateCamera(Hash camHash, BOOL p1) { return FiveXInvoke<Cam>(0x5D6739AE, camHash, p1); } // 0x5E3CF89C6BCCA67D 0x5D6739AE
inline Any CreateCameraWithParams(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return FiveXInvoke<Any>(0x0688BE9A, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x0688BE9A
inline VOID DestroyCam(Cam cam, BOOL destroy) { FiveXInvoke<VOID>(0xC39302BD, cam, destroy); } // 0x865908C81A2C22E9 0xC39302BD
inline VOID DestroyAllCams(Any p0) { FiveXInvoke<VOID>(0x10C151CE, p0); } // 0x10C151CE
inline BOOL DoesCamExist(Any p0) { return FiveXInvoke<BOOL>(0x1EF89DC0, p0); } // 0x1EF89DC0
inline VOID SetCamActiveV2(Cam cam, BOOL active) { FiveXInvoke<VOID>(0x064659C2, cam, active); } // 0x026FB97D0A425F84 0x064659C2
inline VOID SetCamActive(Cam cam, BOOL active) { FiveXInvoke<VOID>(0x064659C2, cam, active); } // 0x026FB97D0A425F84 0x064659C2
inline BOOL IsCamActive(Any p0) { return FiveXInvoke<BOOL>(0x4B58F177, p0); } // 0x4B58F177
inline BOOL IsCamRendering(INT p0) { return FiveXInvoke<BOOL>(0x6EC6B5B2, p0); } // 0x6EC6B5B2
inline Any GetRenderingCam() { return FiveXInvoke<Any>(0x0FCF4DF1); } // 0x0FCF4DF1
inline Vector3 GetCamCoord(Cam p0) { return FiveXInvoke<Vector3>(0x7C40F09C, p0); } // 0x7C40F09C
inline Vector3 GetCamRot(Any p0, Any p1) { return FiveXInvoke<Vector3>(0xDAC84C9F, p0, p1); } // 0xDAC84C9F
inline Any GetCamFov(ScrHandle Camera_handle) { return FiveXInvoke<Any>(0xD6E9FCF5, Camera_handle); } // 0xD6E9FCF5
inline Any GetCamNearClip(Cam cam) { return FiveXInvoke<Any>(0xCFCD35EE, cam); } // 0xCFCD35EE
inline Any GetCamFarClip(Any p0) { return FiveXInvoke<Any>(0x09F119B8, p0); } // 0x09F119B8
inline Any GetCamFarDof(Any p0) { return FiveXInvoke<Any>(0x98C5CCE9, p0); } // 0x98C5CCE9
inline VOID SetCamParams(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { FiveXInvoke<VOID>(0x2167CEBF, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0x2167CEBF
inline VOID SetCamCoordV2(Cam p0, FLOAT p1, FLOAT p2, FLOAT p3) { FiveXInvoke<VOID>(0x7A8053AF, p0, p1, p2, p3); } // 0x7A8053AF
inline VOID SetCamCoord(Cam p0, FLOAT p1, FLOAT p2, FLOAT p3) { FiveXInvoke<VOID>(0x7A8053AF, p0, p1, p2, p3); } // 0x7A8053AF
inline VOID SetCamRot(INT p0, FLOAT p1, FLOAT p2, FLOAT p3, Any p4) { FiveXInvoke<VOID>(0xEE38B3C1, p0, p1, p2, p3, p4); } // 0xEE38B3C1
inline VOID SetCamRotV2(INT p0, FLOAT p1, FLOAT p2, FLOAT p3) { FiveXInvoke<VOID>(0xEE38B3C1, p0, p1, p2, p3); } // 0xEE38B3C1
inline VOID SetCamFov(char* camName, FLOAT FovVaule) { FiveXInvoke<VOID>(0xD3D5D74F, camName, FovVaule); } // 0xD3D5D74F
inline VOID SetCamNearClip(Cam cam, FLOAT nearClip) { FiveXInvoke<VOID>(0x46DB13B1, cam, nearClip); } // 0xC7848EFCCC545182 0x46DB13B1
inline VOID SetCamFarClip(Any p0, Any p1) { FiveXInvoke<VOID>(0x0D23E381, p0, p1); } // 0x0D23E381
inline VOID SetCamNearDof(Any p0, Any p1) { FiveXInvoke<VOID>(0xF28254DF, p0, p1); } // 0xF28254DF
inline VOID SetCamFarDof(Any p0, Any p1) { FiveXInvoke<VOID>(0x58515E8E, p0, p1); } // 0x58515E8E
inline VOID SetCamDofStrength(Any p0, Any p1) { FiveXInvoke<VOID>(0x3CC4EB3F, p0, p1); } // 0x3CC4EB3F
inline VOID SetCamDofPlanes(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0xAD6C2B8F, p0, p1, p2, p3, p4); } // 0xAD6C2B8F
inline VOID SetCamMotionBlurStrength(Any p0, Any p1) { FiveXInvoke<VOID>(0xFD6E0D67, p0, p1); } // 0xFD6E0D67
inline VOID AttachCamToEntity(Cam p0, Entity p1, FLOAT p2, FLOAT p3, FLOAT p4, FLOAT p5) { FiveXInvoke<VOID>(0xAD7C45F6, p0, p1, p2, p3, p4, p5); } // 0xAD7C45F6
inline VOID AttachCamToPedBone(Cam cam, Ped ped, INT boneIndex, FLOAT x, FLOAT y, FLOAT z, BOOL heading) { FiveXInvoke<VOID>(0x506BB35C, cam, ped, boneIndex, x, y, z, heading); } // 0x61A3DBA14AB7F411 0x506BB35C
inline VOID DetachCam(char* camName) { FiveXInvoke<VOID>(0xF4FBF14A, camName); } // 0xF4FBF14A
inline VOID SetCamInheritRollVehicle(Any p0, Any p1) { FiveXInvoke<VOID>(0xE4BD5342, p0, p1); } // 0xE4BD5342
inline VOID PointCamAtCoord(Cam p0, FLOAT p1, FLOAT p2, FLOAT p3) { FiveXInvoke<VOID>(0x914BC21A, p0, p1, p2, p3); } // 0x914BC21A
inline VOID PointCamAtEntity(Cam p0, Entity p1, FLOAT p2, FLOAT p3, FLOAT p4, FLOAT p5) { FiveXInvoke<VOID>(0x7597A0F7, p0, p1, p2, p3, p4, p5); } // 0x7597A0F7
inline VOID PointCamAtPedBone(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { FiveXInvoke<VOID>(0x09F47049, p0, p1, p2, p3, p4, p5, p6); } // 0x09F47049
inline VOID StopCamPointing(INT p0) { FiveXInvoke<VOID>(0x5435F6A5, p0); } // 0x5435F6A5
inline VOID SetCamDebugName(Any p0, Any p1) { FiveXInvoke<VOID>(0x9B00DF3F, p0, p1); } // 0x9B00DF3F
inline VOID AddCamSplineNode(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { FiveXInvoke<VOID>(0xAD3C7EAA, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xAD3C7EAA
inline VOID SetCamSplinePhase(Any p0, Any p1) { FiveXInvoke<VOID>(0xF0AED233, p0, p1); } // 0xF0AED233
inline Any GetCamSplinePhase(Any p0) { return FiveXInvoke<Any>(0x39784DD9, p0); } // 0x39784DD9
inline Any GetCamSplineNodePhase(Any p0) { return FiveXInvoke<Any>(0x7B9522F6, p0); } // 0x7B9522F6
inline VOID SetCamSplineDuration(Any p0, Any p1) { FiveXInvoke<VOID>(0x3E91FC8A, p0, p1); } // 0x3E91FC8A
inline Any GetCamSplineNodeIndex(Any p0) { return FiveXInvoke<Any>(0xF8AEB6BD, p0); } // 0xF8AEB6BD
inline VOID OverrideCamSplineVelocity(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x326A17E2, p0, p1, p2, p3); } // 0x326A17E2
inline VOID OverrideCamSplineMotionBlur(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x633179E6, p0, p1, p2, p3); } // 0x633179E6
inline BOOL IsCamSplinePaused(Any p0) { return FiveXInvoke<BOOL>(0x60B34FF5, p0); } // 0x60B34FF5
inline VOID SetCamActiveWithInterp(INT camTo, INT camFrom, INT duration, Any unk0, Any unk1) { FiveXInvoke<VOID>(0x7983E7F0, camTo, camFrom, duration, unk0, unk1); } // 0x7983E7F0
inline BOOL IsCamInterpolating(Any p0) { return FiveXInvoke<BOOL>(0x7159CB5D, p0); } // 0x7159CB5D
inline VOID ShakeCam(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x1D4211B0, p0, p1, p2); } // 0x1D4211B0
inline VOID AnimatedShakeCam(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0xE1168767, p0, p1, p2, p3, p4); } // 0xE1168767
inline BOOL IsCamShaking(Any p0) { return FiveXInvoke<BOOL>(0x0961FD9B, p0); } // 0x0961FD9B
inline VOID SetCamShakeAmplitude(Any p0, Any p1) { FiveXInvoke<VOID>(0x60FF6382, p0, p1); } // 0x60FF6382
inline VOID StopCamShaking(Any p0, Any p1) { FiveXInvoke<VOID>(0x40D0EB87, p0, p1); } // 0x40D0EB87
inline Any PlayCamAnim(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { return FiveXInvoke<Any>(0xBCEFB87E, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0xBCEFB87E
inline BOOL IsCamPlayingAnim(Any p0, Any p1, Any p2) { return FiveXInvoke<BOOL>(0xB998CB49, p0, p1, p2); } // 0xB998CB49
inline VOID SetCamAnimCurrentPhase(Any p0, Any p1) { FiveXInvoke<VOID>(0x3CB1D17F, p0, p1); } // 0x3CB1D17F
inline Any GetCamAnimCurrentPhase(Any p0) { return FiveXInvoke<Any>(0x345F72D0, p0); } // 0x345F72D0
inline Any PlaySynchronizedCamAnim(Any p0, Any p1, Any p2, Any p3) { return FiveXInvoke<Any>(0x9458459E, p0, p1, p2, p3); } // 0x9458459E
inline BOOL IsScreenFadedOut() { return FiveXInvoke<BOOL>(0x9CAA05FA); } // 0x9CAA05FA
inline BOOL IsScreenFadedIn() { return FiveXInvoke<BOOL>(0x4F37276D); } // 0x4F37276D
inline BOOL IsScreenFadingOut() { return FiveXInvoke<BOOL>(0x79275A57); } // 0x79275A57
inline BOOL IsScreenFadingIn() { return FiveXInvoke<BOOL>(0xC7C82800); } // 0xC7C82800
inline VOID DoScreenFadeIn(INT ticks) { FiveXInvoke<VOID>(0x66C1BDEE, ticks); } // 0x66C1BDEE
inline VOID DoScreenFadeOut(INT ticks) { FiveXInvoke<VOID>(0x89D01805, ticks); } // 0x89D01805
inline VOID SetWidescreenBorders(INT p0, INT p1) { FiveXInvoke<VOID>(0x1A75DC9A, p0, p1); } // 0x1A75DC9A
inline Vector3 GetGameplayCamCoord() { return FiveXInvoke<Vector3>(0x9388CF79); } // 0x9388CF79
inline Vector3 GetGameplayCamRot(Any p0) { return FiveXInvoke<Vector3>(0x13A010B5, p0); } // 0x13A010B5
inline Vector3 GetGameplayCamRotV2(INT p0) { return FiveXInvoke<Vector3>(0x13A010B5, p0); } // 0x837765A25378F0BB 0x13A010B5
inline FLOAT* GetGameplayCamRotV3(INT p0) { return FiveXInvoke<FLOAT*>(0x13A010B5, p0); } // 0x837765A25378F0BB 0x13A010B5
inline Any GetGameplayCamFov() { return FiveXInvoke<Any>(0x4D6B3BFA); } // 0x4D6B3BFA
inline Any GetGameplayCamRelativeHeading() { return FiveXInvoke<Any>(0xCAF839C2); } // 0xCAF839C2
inline VOID SetGameplayCamRelativeHeading(FLOAT heading) { FiveXInvoke<VOID>(0x20C6217C, heading); } // 0x20C6217C
inline Any GetGameplayCamRelativePitch() { return FiveXInvoke<Any>(0xFC5A4946); } // 0xFC5A4946
inline VOID SetGameplayCamRelativePitch(FLOAT x, FLOAT Value2) { FiveXInvoke<VOID>(0x6381B963, x, Value2); } // 0x6381B963
inline VOID ShakeGameplayCam(Any p0, Any p1) { FiveXInvoke<VOID>(0xF2EFE660, p0, p1); } // 0xF2EFE660
inline BOOL IsGameplayCamShaking() { return FiveXInvoke<BOOL>(0x3457D681); } // 0x3457D681
inline VOID SetGameplayCamShakeAmplitude(Any p0) { FiveXInvoke<VOID>(0x9219D44A, p0); } // 0x9219D44A
inline VOID StopGameplayCamShaking(Any p0) { FiveXInvoke<VOID>(0xFD569E4E, p0); } // 0xFD569E4E
inline BOOL IsGameplayCamRendering() { return FiveXInvoke<BOOL>(0x0EF276DA); } // 0x0EF276DA
inline BOOL IsGameplayCamLookingBehind() { return FiveXInvoke<BOOL>(0x33C83F17); } // 0x33C83F17
inline BOOL IsSphereVisible(Any p0, Any p1, Any p2, Any p3) { return FiveXInvoke<BOOL>(0xDD1329E2, p0, p1, p2, p3); } // 0xDD1329E2
inline BOOL IsFollowPedCamActive() { return FiveXInvoke<BOOL>(0x9F9E856C); } // 0x9F9E856C
inline Any SetFollowPedCamCutsceneChat(Any p0, Any p1) { return FiveXInvoke<Any>(0x1425F6AC, p0, p1); } // 0x1425F6AC
inline VOID ClampGameplayCamYaw(FLOAT minimum, FLOAT maximum) { FiveXInvoke<VOID>(0x749909AC, minimum, maximum); } // 0x749909AC
inline VOID ClampGameplayCamPitch(FLOAT minimum, FLOAT maximum) { FiveXInvoke<VOID>(0xFA3A16E7, minimum, maximum); } // 0xFA3A16E7
inline VOID AnimateGameplayCamZoom(FLOAT p0, FLOAT _distance) { FiveXInvoke<VOID>(0x77340650, p0, _distance); } // 0x77340650
inline Any GetFollowPedCamZoomLevel() { return FiveXInvoke<Any>(0x57583DF1); } // 0x57583DF1
inline Any GetFollowPedCamViewMode() { return FiveXInvoke<Any>(0xA65FF946); } // 0xA65FF946
inline VOID SetFollowPedCamViewMode(Any p0) { FiveXInvoke<VOID>(0x495DBE8D, p0); } // 0x495DBE8D
inline BOOL IsFollowVehicleCamActive() { return FiveXInvoke<BOOL>(0x8DD49B77); } // 0x8DD49B77
inline Any GetFollowVehicleCamZoomLevel() { return FiveXInvoke<Any>(0x8CD67DE3); } // 0x8CD67DE3
inline VOID SetFollowVehicleCamZoomLevel(Any p0) { FiveXInvoke<VOID>(0x8F55EBBE, p0); } // 0x8F55EBBE
inline Any GetFollowVehicleCamViewMode() { return FiveXInvoke<Any>(0xA4B4DB03); } // 0xA4B4DB03
inline VOID SetFollowVehicleCamViewMode(Any p0) { FiveXInvoke<VOID>(0xC4FBBBD3, p0); } // 0xC4FBBBD3
inline BOOL IsAimCamActive() { return FiveXInvoke<BOOL>(0xC24B4F6F); } // 0xC24B4F6F
inline BOOL IsFirstPersonAimCamActive() { return FiveXInvoke<BOOL>(0xD6280468); } // 0xD6280468
inline VOID SetGameplayCoordHint(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { FiveXInvoke<VOID>(0xF27483C9, p0, p1, p2, p3, p4, p5, p6); } // 0xF27483C9
inline VOID SetGameplayPedHint(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { FiveXInvoke<VOID>(0x7C27343E, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x7C27343E
inline VOID SetGameplayVehicleHint(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { FiveXInvoke<VOID>(0x2C9A11D8, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x2C9A11D8
inline VOID SetGameplayEntityHint(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { FiveXInvoke<VOID>(0x66C32306, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x66C32306
inline BOOL IsGameplayHintActive() { return FiveXInvoke<BOOL>(0xAD8DA205); } // 0xAD8DA205
inline VOID StopGameplayHint(Any p0) { FiveXInvoke<VOID>(0x1BC28B7B, p0); } // 0x1BC28B7B
inline VOID SetGameplayHintFov(Any p0) { FiveXInvoke<VOID>(0x96FD173B, p0); } // 0x96FD173B
inline VOID GetIsMultiplayerBrief(Any p0) { FiveXInvoke<VOID>(0x2F0CE859, p0); } // 0x2F0CE859
inline VOID SetCinematicButtonActive(Any p0) { FiveXInvoke<VOID>(0x3FBC5D00, p0); } // 0x3FBC5D00
inline BOOL IsCinematicCamRendering() { return FiveXInvoke<BOOL>(0x80471AD9); } // 0x80471AD9
inline VOID ShakeCinematicCam(Any p0, Any p1) { FiveXInvoke<VOID>(0x61815F31, p0, p1); } // 0x61815F31
inline BOOL IsCinematicCamShaking() { return FiveXInvoke<BOOL>(0x8376D939); } // 0x8376D939
inline VOID SetCinematicCamShakeAmplitude(Any p0) { FiveXInvoke<VOID>(0x67510C4B, p0); } // 0x67510C4B
inline VOID StopCinematicCamShaking(Any p0) { FiveXInvoke<VOID>(0x71C12904, p0); } // 0x71C12904
inline VOID CreateCinematicShot(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0xAC494E35, p0, p1, p2, p3); } // 0xAC494E35
inline BOOL IsCinematicShotActive(Any p0) { return FiveXInvoke<BOOL>(0xA4049042, p0); } // 0xA4049042
inline VOID StopCinematicShot(Any p0) { FiveXInvoke<VOID>(0xD78358C5, p0); } // 0xD78358C5
inline VOID SetCinematicModeActive(Any p0) { FiveXInvoke<VOID>(0x2009E747, p0); } // 0x2009E747
inline VOID StopCutsceneCamShaking(Any p0) { FiveXInvoke<VOID>(0xF07D603D, p0); } // 0xF07D603D
inline VOID RemoveCutscene() { FiveXInvoke<VOID>(0x8052F533); } // 0x8052F533
inline VOID StopCutsceneImmediately() { FiveXInvoke<VOID>(0xF528A2AD); } // 0xF528A2AD
inline BOOL IsCutsceneActive() { return FiveXInvoke<BOOL>(0xCCE2FE9D); } // 0xCCE2FE9D
inline BOOL IsCutscenePlaying() { return FiveXInvoke<BOOL>(0xA3A78392); } // 0xA3A78392
inline BOOL IsControlEnabled(INT Index, INT Control) { return FiveXInvoke<BOOL>(0x9174AF84, Index, Control); } // 0x9174AF84
inline BOOL IsControlPressed(INT Index, INT Control) { return FiveXInvoke<BOOL>(0x517A4384, Index, Control); } // 0x517A4384
inline BOOL IsControlReleased(INT Index, INT Control) { return FiveXInvoke<BOOL>(0x1F91A06E, Index, Control); } // 0x1F91A06E
inline BOOL IsControlJustReleased(INT Index, INT Control) { return FiveXInvoke<BOOL>(0x2314444B, Index, Control); } // 0x2314444B
inline Any GetControlValue(Any p0, Any p1) { return FiveXInvoke<Any>(0xC526F3C6, p0, p1); } // 0xC526F3C6
inline Any GetControlNormal(Any p0, Any p1) { return FiveXInvoke<Any>(0x5DE226A5, p0, p1); } // 0x5DE226A5
inline BOOL IsDisabledControlPressed(INT Index, INT Control) { return FiveXInvoke<BOOL>(0x32A93544, Index, Control); } // 0x32A93544
inline BOOL IsDisabledControlJustPressed(INT Index, INT Control) { return FiveXInvoke<BOOL>(0xEE6ABD32, Index, Control); } // 0xEE6ABD32
inline BOOL IsDisabledControlJustReleased(INT Index, Any Control) { return FiveXInvoke<BOOL>(0xD6A679E1, Index, Control); } // 0xD6A679E1
inline Any GetDisabledControlNormal(Any p0, Any p1) { return FiveXInvoke<Any>(0x66FF4FAA, p0, p1); } // 0x66FF4FAA
inline VOID DisableControlAction2(INT controlGroup, INT control, BOOL disable) { FiveXInvoke<VOID>(0x3800C0DC, controlGroup, control, disable); } // 0xFE99B66D079CF6BC 0x3800C0DC
inline VOID SetPadShake(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x5D38BD2F, p0, p1, p2); } // 0x5D38BD2F
inline VOID StopPadShake(Any p0) { FiveXInvoke<VOID>(0x8F75657E, p0); } // 0x8F75657E
inline VOID SetControlShake(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xF63D817A, p0, p1, p2); } // 0xF63D817A
inline BOOL IsLookInverted() { return FiveXInvoke<BOOL>(0x313434B2); } // 0x313434B2
inline Any GetLocalPlayerAimState() { return FiveXInvoke<Any>(0x81802053); } // 0x81802053
inline VOID SetPlayerpadShakesWhenControllerDisabled(BOOL p0) { FiveXInvoke<VOID>(0xA86BD91F, p0); } // 0xA86BD91F
inline VOID SetInputExclusive(INT Index, INT Control) { FiveXInvoke<VOID>(0x4E8E29E6, Index, Control); } // 0x4E8E29E6
inline VOID EnableAllControlActions(INT Index) { FiveXInvoke<VOID>(0xFC2F119F, Index); } // 0xFC2F119F
inline INT GetWhatPedIsDoing(INT player) { return FiveXInvoke<int>(0xF8D7AF3B, player); }//0xF8D7AF3B
inline Any DecorSetTime(Any p0, char* p1, Any p2) { return FiveXInvoke<Any>(0xBBAEEF94, p0, p1, p2); } // 0xBBAEEF94
inline Any DecorSetBool(Any p0, char* p1, Any p2) { return FiveXInvoke<Any>(0x8E101F5C, p0, p1, p2); } // 0x8E101F5C
inline BOOL DecorSetInt(Any p0, char* p1, Any p2) { return FiveXInvoke<BOOL>(0xDB718B21, p0, p1, p2); } // 0xDB718B21
inline Any DecorGetBool(Any p0, char* p1) { return FiveXInvoke<Any>(0xDBCE51E0, p0, p1); } // 0xDBCE51E0
inline INT DecorGetInt(Entity entity, char* propertyName) { return FiveXInvoke<INT>(0xDDDE59B5, entity, propertyName); } // 0xDDDE59B5
inline INT DecorGetFloat(Entity entity, char* propertyName) { return FiveXInvoke<INT>(0x8DE5382F, entity, propertyName); } // 0x8DE5382F
inline BOOL DecorExistOn(Entity entity, char* propertyName) { return FiveXInvoke<BOOL>(0x74EF9C40, entity, propertyName); } // 0x74EF9C40
inline Any DecorRemove(Any p0, char* p1) { return FiveXInvoke<Any>(0xE0E2640B, p0, p1); } // 0xE0E2640B
inline VOID DecorRegister(Entity entity, char* propertyName, INT value) { FiveXInvoke<VOID>(0x68BD42A9, entity, propertyName, value); } // 0x68BD42A9
inline Any DecorIsRegisteredAsType(char* p0, Any p1) { return FiveXInvoke<Any>(0x7CF0971D, p0, p1); } // 0x7CF0971D
inline VOID DecorRegisterLock() { FiveXInvoke<VOID>(0x7F3F1C02); } // 0x7F3F1C02
inline VOID SetEntityCollision22(Entity entity, BOOL toggle) { FiveXInvoke<VOID>(0x139FD37D, entity, toggle); }
inline VOID AttachEntityToEntity2(Entity entity1, Entity entity2, INT boneIndex, FLOAT xPos, FLOAT yPos, FLOAT zPos, FLOAT xRot, FLOAT yRot, FLOAT zRot, BOOL p9, BOOL isRelative, BOOL collision, BOOL allowRotation, INT vertexIndex, BOOL fixedRot) { FiveXInvoke<VOID>(0xEC024237, entity1, entity2, boneIndex, xPos, yPos, zPos, xRot, yRot, zRot, p9, isRelative, collision, allowRotation, vertexIndex, fixedRot); } // 0xEC02423
inline VOID GetEntityCoords3(Entity entity, FLOAT* p1) { FiveXInvoke<VOID>(0x1647F1CB, entity, p1); } // 0x1647F1CB
inline Vector3 GetEntityRotation2(Entity entity, BOOL p1) { return FiveXInvoke<Vector3>(0x8FF45B04, entity, p1); } // 0x8FF45B04 0x8FF45B04
inline Vector3 SetEntityCoordsNew(Entity entity, FLOAT X, FLOAT Y, FLOAT Z, BOOL XAxes, BOOL YAxes, BOOL ZAxes, BOOL unk) { return FiveXInvoke<Vector3>(0xDF70B41B, entity, X, Y, Z, XAxes, YAxes, ZAxes, unk); } // 0xDF70B41B
inline Vector3 GetOffsetFromEntityInWorldCoords2(Entity Entity, FLOAT xCoord, FLOAT yCoord, FLOAT zCoord) { return FiveXInvoke<Vector3>(0xABCF043A, Entity, xCoord, yCoord, zCoord); } // 0xABCF043A
inline VOID GetOffsetFromEntityInWorldCoords3(INT Handle, FLOAT x, FLOAT y, FLOAT z, FLOAT* Out) { FiveXInvoke<VOID>(0xABCF043A, Handle, x, y, z, Out); }
inline BOOL DoesEntityHaveDrawable(Entity Entity) { return FiveXInvoke<BOOL>(0xA5B33300, Entity); } // 0xA5B33300
inline BOOL DoesEntityHavePhysics(Entity Entity) { return FiveXInvoke<BOOL>(0x9BCD2979, Entity); } // 0x9BCD2979
inline BOOL HasEntityAnimFinished(Any p0, Any p1, Any p2, Any p3) { return FiveXInvoke<BOOL>(0x1D9CAB92, p0, p1, p2, p3); } // 0x1D9CAB92
inline BOOL HasEntityBeenDamagedByAnyObject(Entity Entity) { return FiveXInvoke<BOOL>(0x6B74582E, Entity); } // 0x6B74582E
inline BOOL HasEntityBeenDamagedByAnyPed(Entity Entity) { return FiveXInvoke<BOOL>(0x53FD4A25, Entity); } // 0x53FD4A25
inline BOOL HasEntityBeenDamagedByAnyVehicle(Entity Entity) { return FiveXInvoke<BOOL>(0x878C2CE0, Entity); } // 0x878C2CE0
inline BOOL HasEntityBeenDamagedByEntity(Any p0, Any p1, Any p2) { return FiveXInvoke<BOOL>(0x07FC77E0, p0, p1, p2); } // 0x07FC77E0
inline BOOL HasEntityClearLosToEntity(Any p0, Any p1, Any p2) { return FiveXInvoke<BOOL>(0x53576FA7, p0, p1, p2); } // 0x53576FA7
inline BOOL HasEntityClearLosToEntityInFront(Any p0, Any p1) { return FiveXInvoke<BOOL>(0x210D87C8, p0, p1); } // 0x210D87C8
inline BOOL HasEntityCollidedWithAnything(Entity Entity) { return FiveXInvoke<BOOL>(0x662A2F41, Entity); } // 0x662A2F41
inline Any GetEntityAnimCurrentTime(Any p0, Any p1, Any p2) { return FiveXInvoke<Any>(0x83943F41, p0, p1, p2); } // 0x83943F41
inline Any GetEntityAnimTotalTime(Any p0, Any p1, Any p2) { return FiveXInvoke<Any>(0x433A9D18, p0, p1, p2); } // 0x433A9D18
inline Entity GetEntityAttachedTo(Entity Entity) { return FiveXInvoke<Any>(0xFE1589F9, Entity); } // 0xFE1589F9
inline Vector3 GetEntityCoords2(char* entity, BOOL unkBool) { return FiveXInvoke<Vector3>(0x1647F1CB, entity, unkBool); } // 0x1647F1CB
inline Vector3 GetEntityForwardVector(Entity entity) { return FiveXInvoke<Vector3>(0x84DCECBF, entity); } // 0x84DCECBF
inline Any GetEntityForwardX(Entity Entity) { return FiveXInvoke<Any>(0x49FAE914, Entity); } // 0x49FAE914
inline Any GetEntityForwardY(Entity Entity) { return FiveXInvoke<Any>(0x9E2F917C, Entity); } // 0x9E2F917C
inline FLOAT GetEntityHeading(Entity Entity) { return FiveXInvoke<float>(0x972CC383, Entity); } // 0x972CC383
inline Any GetEntityHealth(Entity Entity) { return FiveXInvoke<Any>(0x8E3222B7, Entity); } // 0x8E3222B7
inline Any GetEntityMaxHealth(Entity Entity) { return FiveXInvoke<Any>(0xC7AE6AA1, Entity); } // 0xC7AE6AA1
inline VOID SetEntityMaxHealth(Entity Entity, INT Toggle) { FiveXInvoke<VOID>(0x96F84DF8, Entity, Toggle); } // 0x96F84DF8
inline Any GetEntityHeight(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return FiveXInvoke<Any>(0xEE443481, p0, p1, p2, p3, p4, p5); } // 0xEE443481
inline Any GetEntityHeightAboveGround(Entity Entity) { return FiveXInvoke<Any>(0x57F56A4D, Entity); } // 0x57F56A4D
inline VOID GetEntityMatrix(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0xEB9EB001, p0, p1, p2, p3, p4); } // 0xEB9EB001
inline Hash GetEntityModel(Entity Entity) { return FiveXInvoke<Hash>(0xDAFCB3EC, Entity); } // 0xDAFCB3EC
inline Vector3 GetOffsetFromEntityGivenWorldCoords(Any p0, Any p1, Any p2, Any p3) { return FiveXInvoke<Vector3>(0x6477EC9E, p0, p1, p2, p3); } // 0x6477EC9E
inline Vector3 GetOffsetFromEntityInWorldCoords(Entity Entity, FLOAT xCoord, FLOAT yCoord, FLOAT zCoord) { return FiveXInvoke<Vector3>(0xABCF043A, Entity, xCoord, yCoord, zCoord); } // 0xABCF043A
inline Any GetEntityPitch(Entity Entity) { return FiveXInvoke<Any>(0xFCE6ECE5, Entity); } // 0xFCE6ECE5
inline VOID GetEntityQuaternion(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0x5154EC90, p0, p1, p2, p3, p4); } // 0x5154EC90
inline Any GetEntityRoll(Entity Entity) { return FiveXInvoke<Any>(0x36610842, Entity); } // 0x36610842
inline Vector3 GetEntityRotation(Entity Ent, INT Order) { return FiveXInvoke<Vector3>(0x8FF45B04, Ent, Order); } // 0x8FF45B04
inline Vector3 GetEntityRotationVelocity(Any p0) { return FiveXInvoke<Vector3>(0x9BF8A73F, p0); } // 0x9BF8A73F
inline Any GetEntityScript(Any p0, Any p1) { return FiveXInvoke<Any>(0xB7F70784, p0, p1); } // 0xB7F70784
inline FLOAT GetEntitySpeed(Entity entity) { return FiveXInvoke<float>(0x9E1E4798, entity); } // 0x9E1E4798
inline Vector3 GetEntitySpeedVector(Any p0, Any p1) { return FiveXInvoke<Vector3>(0x3ED2B997, p0, p1); } // 0x3ED2B997
inline Any GetEntityUprightValue(Any p0) { return FiveXInvoke<Any>(0xF4268190, p0); } // 0xF4268190
inline Vector3 GetEntityVelocity(Entity entity) { return FiveXInvoke<Vector3>(0xC14C9B6B, entity); } // 0xC14C9B6B
inline Vector3 GetWorldPositionOfEntityBone(Entity entity, INT boneIndex) { return FiveXInvoke<Vector3>(0x7C6339DF, entity, boneIndex); } // 0x7C6339DF
inline Any GetNearestPlayerToEntity(Entity Entity) { return FiveXInvoke<Any>(0xCE17FDEC, Entity); } // 0xCE17FDEC
inline INT GetEntityType(Entity Entity) { return FiveXInvoke<int>(0x0B1BD08D, Entity); } // 0x0B1BD08D
inline BOOL IsAnEntity(Entity Entity) { return FiveXInvoke<BOOL>(0xD4B9715A, Entity); } // 0xD4B9715A
inline BOOL IsEntityAPed(Entity Entity) { return FiveXInvoke<BOOL>(0x55D33EAB, Entity); } // 0x55D33EAB
inline BOOL IsEntityAMissionEntity(Entity Entity) { return FiveXInvoke<BOOL>(0x2632E124, Entity); } // 0x2632E124
inline BOOL IsEntityAVehicle(Entity Entity) { return FiveXInvoke<BOOL>(0xBE800B01, Entity); } // 0xBE800B01
inline BOOL IsEntityAnObject(Any p0) { return FiveXInvoke<BOOL>(0x3F52E561, p0); } // 0x3F52E561
inline BOOL IsEntityAtCoord(Entity entity, FLOAT x, FLOAT y, FLOAT z, FLOAT xSize, FLOAT ySize, FLOAT zSize, INT p7, INT p8, INT p9) { return FiveXInvoke<BOOL>(0xD749B606, entity, x, y, z, xSize, ySize, zSize, p7, p8, p9); } // 0xD749B606
inline BOOL IsEntityAtEntity(Entity entity1, Entity entity2, FLOAT xSize, FLOAT ySize, FLOAT zSize, INT p5, INT p6, INT p7) { return FiveXInvoke<BOOL>(0xDABDCB52, entity1, entity2, xSize, ySize, zSize, p5, p6, p7); } // 0xDABDCB52
inline BOOL IsEntityAttached(Any p0) { return FiveXInvoke<BOOL>(0xEC1479D5, p0); } // 0xEC1479D5
inline BOOL IsEntityAttachedToAnyObject(Any p0) { return FiveXInvoke<BOOL>(0x0B5DE340, p0); } // 0x0B5DE340
inline BOOL IsEntityAttachedToAnyPed(Any p0) { return FiveXInvoke<BOOL>(0x9D7A609C, p0); } // 0x9D7A609C
inline BOOL IsEntityAttachedToAnyVehicle(Any p0) { return FiveXInvoke<BOOL>(0xDE5C995E, p0); } // 0xDE5C995E
inline BOOL IsEntityAttachedToEntity(Entity from, Entity to) { return FiveXInvoke<BOOL>(0xB0ABFEA8, from, to); } // 0xB0ABFEA8
inline BOOL IsEntityDead(Entity entity) { return FiveXInvoke<BOOL>(0xB6F7CBAC, entity); } // 0xB6F7CBAC
inline BOOL IsEntityInAir(Entity entity) { return FiveXInvoke<BOOL>(0xA4157987, entity); } // 0xA4157987
inline BOOL IsEntityInAngledArea(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { return FiveXInvoke<BOOL>(0x883622FA, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0x883622FA
inline BOOL IsEntityInArea(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return FiveXInvoke<BOOL>(0x8C2DFA9D, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x8C2DFA9D
inline BOOL IsEntityInZone(Any p0, Any p1) { return FiveXInvoke<BOOL>(0x45C82B21, p0, p1); } // 0x45C82B21
inline BOOL IsEntityInWater(Entity entity) { return FiveXInvoke<BOOL>(0x4C3C2508, entity); } // 0x4C3C2508
inline BOOL IsEntityOnScreen(Any p0) { return FiveXInvoke<BOOL>(0xC1FEC5ED, p0); } // 0xC1FEC5ED
inline BOOL IsEntityPlayingAnim(Entity entity, char* animDict, char* animName, int taskFlag) { return FiveXInvoke<BOOL>(0x0D130D34, entity, animDict, animName, taskFlag); } // 0x0D130D34
inline BOOL IsEntityStatic(Any p0) { return FiveXInvoke<BOOL>(0x928E12E9, p0); } // 0x928E12E9
inline BOOL IsEntityTouchingEntity(Entity p0, Entity p1) { return FiveXInvoke<BOOL>(0x6B931477, p0, p1); } // 0x6B931477
inline BOOL IsEntityUpright(Any p0, Any p1) { return FiveXInvoke<BOOL>(0x3BCDF4E1, p0, p1); } // 0x3BCDF4E1
inline BOOL IsEntityUpsidedown(Any p0) { return FiveXInvoke<BOOL>(0x5ACAA48F, p0); } // 0x5ACAA48F
inline BOOL IsEntityVisible(Entity entity) { return FiveXInvoke<BOOL>(0x120B4ED5, entity); } // 0x120B4ED5
inline BOOL IsEntityInvisibleToScript(Any p0) { return FiveXInvoke<BOOL>(0x5D240E9D, p0); } // 0x5D240E9D
inline BOOL IsEntityOccluded(Any p0) { return FiveXInvoke<BOOL>(0x46BC5B40, p0); } // 0x46BC5B40
inline BOOL IsEntityWaitingForWorldCollision(Any p0) { return FiveXInvoke<BOOL>(0x00AB7A4A, p0); } // 0x00AB7A4A
inline VOID ApplyForceToEntity(Entity entity, BOOL p1, FLOAT Force_X, FLOAT Force_Y, FLOAT Force_Z, FLOAT Rot_X, FLOAT Rot_Y, FLOAT Rot_Z, BOOL p8, BOOL p9, BOOL p10, BOOL p11, INT p12, BOOL p13) { FiveXInvoke<VOID>(0xC1C0855A, entity, p1, Force_X, Force_Y, Force_Z, Rot_X, Rot_Y, Rot_Z, p8, p9, p10, p11, p12, p13); } // 0xC1C0855A
inline VOID AttachEntityToEntity(Entity entity1, Entity entity2, INT boneIndex, FLOAT xPos, FLOAT yPos, FLOAT zPos, FLOAT xRot, FLOAT yRot, FLOAT zRot, BOOL p9, BOOL isRelative, BOOL collision, BOOL allowRotation, INT vertexIndex, BOOL fixedRot) { FiveXInvoke<VOID>(0xEC024237, entity1, entity2, boneIndex, xPos, yPos, zPos, xRot, yRot, zRot, p9, isRelative, collision, allowRotation, vertexIndex, fixedRot); } // 0xEC024237
inline VOID AttachEntityToEntityPhysically(Entity entity1, Entity entity2, FLOAT unknown1, FLOAT unknown2, FLOAT x1, FLOAT y1, FLOAT z1, FLOAT x2, FLOAT y2, FLOAT z2, FLOAT rot_x, FLOAT rot_y, FLOAT rot_z, Any unknown3, Any unknown4, Any unknown5, Any unknown6, Any unknown7, Any unknown8) { FiveXInvoke<VOID>(0x0547417F, entity1, entity2, unknown1, unknown2, x1, y1, z1, x2, y2, z2, rot_x, rot_y, rot_z, unknown3, unknown4, unknown5, unknown6, unknown7, unknown8); } // 0x0547417F
inline Any GetEntityBoneIndexByName(Entity entity, char* boneName) { return FiveXInvoke<Any>(0xE4ECAC22, entity, boneName); } // 0xE4ECAC22
inline VOID ClearEntityLastDamageEntity(Entity entity) { FiveXInvoke<VOID>(0x2B83F43B, entity); } // 0x2B83F43B
inline VOID DeleteEntity(Entity* EntityHandle) { FiveXInvoke<VOID>(0xFAA3D236, EntityHandle); } // 0xFAA3D236
inline VOID DetachEntity(Entity p0, BOOL p1, BOOL p2) { FiveXInvoke<VOID>(0xC8EFCB41, p0, p1, p2); } // 0xC8EFCB41
inline VOID FreezeEntityPosition(Entity entity, BOOL Toggle) { FiveXInvoke<VOID>(0x65C16D57, entity, Toggle); } // 0x65C16D57
inline Any PlayEntityAnim(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return FiveXInvoke<Any>(0x878753D5, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x878753D5
inline Any PlaySynchronizedEntityAnim(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return FiveXInvoke<Any>(0x012760AA, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x012760AA
inline Any StopEntityAnim(Any p0, Any p1, Any p2, Any p3) { return FiveXInvoke<Any>(0xC4769830, p0, p1, p2, p3); } // 0xC4769830
inline Any StopSynchronizedEntityAnim(Any p0, Any p1, Any p2) { return FiveXInvoke<Any>(0xE27D2FC1, p0, p1, p2); } // 0xE27D2FC1
inline VOID SetEntityAnimCurrentTime(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x99D90735, p0, p1, p2, p3); } // 0x99D90735
inline VOID SetEntityAnimSpeed(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x3990C90A, p0, p1, p2, p3); } // 0x3990C90A
inline VOID SetEntityAsMissionEntity(Entity entityHandle, BOOL value, BOOL p2) { FiveXInvoke<VOID>(0x5D1F9E0F, entityHandle, value, p2); } // 0x5D1F9E0F
inline VOID SetEntityAsNoLongerNeeded(Entity* entityHandle) { FiveXInvoke<VOID>(0xADF2267C, entityHandle); } // 0xADF2267C
inline VOID SetPedAsNoLongerNeeded(Ped* pedHandle) { FiveXInvoke<VOID>(0x9A388380, pedHandle); } // 0x9A388380
inline VOID SetVehicleAsNoLongerNeeded(Vehicle* vehicleHandle) { FiveXInvoke<VOID>(0x9B0E10BE, vehicleHandle); } // 0x9B0E10BE
inline VOID SetObjectAsNoLongerNeeded(Object* objectHandle) { FiveXInvoke<VOID>(0x3F6B949F, objectHandle); } // 0x3F6B949F
inline VOID SetEntityCanBeDamaged(Entity Entity, BOOL Toggle) { FiveXInvoke<VOID>(0x60B6E744, Entity, Toggle); } // 0x60B6E744
inline VOID SetEntityCanBeDamagedByRelationshipGroup(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x34165B5D, p0, p1, p2); } // 0x34165B5D
inline VOID SetEntityCanBeTargetedWithoutLos(Any p0, Any p1) { FiveXInvoke<VOID>(0x3B13797C, p0, p1); } // 0x3B13797C
inline VOID SetEntityCollision(Entity entity, BOOL p1, BOOL p2) { FiveXInvoke<VOID>(0x139FD37D, entity, p1, p2); } // 0x139FD37D
inline VOID SetEntityCollision1(Entity entity, BOOL p1) { FiveXInvoke<VOID>(0x139FD37D, entity, p1); } // 0x139FD37D
inline VOID SetEntityCoords1(Entity entity, FLOAT X, FLOAT Y, FLOAT Z, FLOAT XAxes, FLOAT YAxes, FLOAT ZAxes, BOOL unk) { FiveXInvoke<VOID>(0xDF70B41B, entity, X, Y, Z, XAxes, YAxes, ZAxes, unk); } // 0xDF70B41B
inline VOID SetEntityCoords2(Entity entity, FLOAT X, FLOAT Y, FLOAT Z, BOOL XAxes, BOOL YAxes, BOOL ZAxes, BOOL unk) { FiveXInvoke<VOID>(0xDF70B41B, entity, X, Y, Z, XAxes, YAxes, ZAxes, unk); } // 0xDF70B41B
inline VOID SetEntityCoordsNoOffsetWaypoint(Any p0, FLOAT p1, FLOAT p2, FLOAT p3, BOOL p4, BOOL p5, BOOL p6) { FiveXInvoke<VOID>(0x4C83DE8D, p0, p1, p2, p3, p4, p5, p6); } // 0x4C83DE8D
inline VOID SetEntityCoordsNoOffset(Entity entity, FLOAT xCoord, FLOAT yCoord, FLOAT zCoord, BOOL p4, BOOL p5, BOOL p6) { FiveXInvoke<VOID>(0x4C83DE8D, entity, xCoord, yCoord, zCoord, p4, p5, p6); } // 0x4C83DE8D
inline VOID SetEntityDynamic(Entity entity, BOOL ToggleDynamics) { FiveXInvoke<VOID>(0x236F525B, entity, ToggleDynamics); } // 0x236F525B
inline VOID SetEntityHeading(Entity entity, FLOAT Heading) { FiveXInvoke<VOID>(0xE0FF064D, entity, Heading); } // 0xE0FF064D
inline VOID SetEntityHealth(Entity entity, INT Amount) { FiveXInvoke<VOID>(0xFBCD1831, entity, Amount); } // 0xFBCD1831
inline VOID SetEntityIsTargetPriority(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x9729EE32, p0, p1, p2); } // 0x9729EE32
inline VOID SetEntityLights(Any p0, Any p1) { FiveXInvoke<VOID>(0xE8FC85AF, p0, p1); } // 0xE8FC85AF
inline VOID SetEntityLoadCollisionFlag(Entity entity, BOOL Toggle) { FiveXInvoke<VOID>(0xC52F295B, entity, Toggle); } // 0xC52F295B
inline VOID SetEntityMaxSpeed(Any p0, Any p1) { FiveXInvoke<VOID>(0x46AFFED3, p0, p1); } // 0x46AFFED3
inline VOID SetEntityOnlyDamagedByPlayer(Any p0, Any p1) { FiveXInvoke<VOID>(0x4B707F50, p0, p1); } // 0x4B707F50
inline VOID SetEntityOnlyDamagedByRelationshipGroup(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x202237E2, p0, p1, p2); } // 0x202237E2
inline VOID SetEntityProofs(Entity Entity, BOOL bulletProof, BOOL fireProof, BOOL explosionProof, BOOL collisionProof, BOOL meleeProof, BOOL p6, BOOL p7, BOOL p8) { FiveXInvoke<VOID>(0x7E9EAB66, Entity, bulletProof, fireProof, explosionProof, collisionProof, meleeProof, p6, p7, p8); } // 0x7E9EAB66
inline VOID SetEntityQuaternion(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0x83B6046F, p0, p1, p2, p3, p4); } // 0x83B6046F
inline VOID SetEntityRecordsCollisions(Any p0, Any p1) { FiveXInvoke<VOID>(0x6B189A1A, p0, p1); } // 0x6B189A1A
inline VOID SetEntityRotation(Entity entity, FLOAT Pitch, FLOAT Roll, FLOAT Yaw, Any p4, Any p5) { FiveXInvoke<VOID>(0x0A345EFE, entity, Pitch, Roll, Yaw, p4, p5); } // 0x0A345EFE
inline VOID SetEntityRotationPandora(Entity entity, FLOAT Pitch, FLOAT Roll, FLOAT Yaw, INT p4, INT p5) { FiveXInvoke<VOID>(0x0A345EFE, entity, Pitch, Roll, Yaw, p4, p5); } // 0x0A345EFE
inline VOID SetEntityVelocity(Entity entity, FLOAT xVel, FLOAT yVel, FLOAT zVel) { FiveXInvoke<VOID>(0xFF5A1988, entity, xVel, yVel, zVel); } // 0xFF5A1988
inline VOID SetEntityHasGravity(Any p0, Any p1) { FiveXInvoke<VOID>(0xE2F262BF, p0, p1); } // 0xE2F262BF
inline VOID SetEntityLodDist(Entity entity, INT Distance) { FiveXInvoke<VOID>(0xD7ACC7AD, entity, Distance); } // 0xD7ACC7AD
inline VOID SetEntityAlpha(Entity entity, INT AlphaLVL, Any p2) { FiveXInvoke<VOID>(0xAE667CB0, entity, AlphaLVL, p2); } // 0xAE667CB0
inline Any GetEntityAlpha(Entity entity) { return FiveXInvoke<Any>(0x1560B017, entity); } // 0x1560B017
inline VOID ResetEntityAlpha(Entity entity) { FiveXInvoke<VOID>(0x8A30761C, entity); } // 0x8A30761C
inline VOID SetEntityRenderScorched(Entity entity, BOOL toggle) { FiveXInvoke<VOID>(0xAAC9317B, entity, toggle); } // 0xAAC9317B
inline VOID CreateModelSwap(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { FiveXInvoke<VOID>(0x0BC12F9E, p0, p1, p2, p3, p4, p5, p6); } // 0x0BC12F9E
inline VOID RemoveModelSwap(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { FiveXInvoke<VOID>(0xCE0AA8BC, p0, p1, p2, p3, p4, p5, p6); } // 0xCE0AA8BC
inline VOID CreateModelHide(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { FiveXInvoke<VOID>(0x7BD5CF2F, p0, p1, p2, p3, p4, p5); } // 0x7BD5CF2F
inline VOID RemoveModelHide(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { FiveXInvoke<VOID>(0x993DBC10, p0, p1, p2, p3, p4, p5); } // 0x993DBC10
inline VOID CreateForcedObject(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { FiveXInvoke<VOID>(0x335190A2, p0, p1, p2, p3, p4, p5); } // 0x335190A2
inline VOID RemoveForcedObject(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0xAED73ADD, p0, p1, p2, p3, p4); } // 0xAED73ADD
inline VOID SetEntityNoCollisionEntity(Entity ent1, Entity ent2, BOOL toogle) { FiveXInvoke<VOID>(0x1E11BFE9, ent1, ent2, toogle); } // 0x1E11BFE9
inline VOID SetEntityMotionBlur(Any p0, Any p1) { FiveXInvoke<VOID>(0xE90005B8, p0, p1); } // 0xE90005B8
inline Any StartScriptFire(FLOAT X, FLOAT Y, FLOAT Z, INT maxChildren, BOOL isGasFire) { return FiveXInvoke<Any>(0xE7529357, X, Y, Z, maxChildren, isGasFire); } // 0xE7529357 0xE7529357
inline VOID RemoveScriptFire(Any scriptHandle) { FiveXInvoke<VOID>(0x6B21FE26, scriptHandle); } // 0x6B21FE26 0x6B21FE26
inline Any StartEntityFire(Entity entity) { return FiveXInvoke<Any>(0x8928428E, entity); } // 0x8928428E 0x8928428E
inline VOID StopEntityFire(Entity Entity) { FiveXInvoke<VOID>(0xCE8C9066, Entity); } // 0xCE8C9066
inline BOOL IsEntityOnFire(Entity entity) { return FiveXInvoke<BOOL>(0x8C73E64F, entity); } // 0x8C73E64F 0x8C73E64F
inline INT GetNumberOfFiresInRange(FLOAT x, FLOAT y, FLOAT z, FLOAT radius) { return FiveXInvoke<int>(0x654D93B7, x, y, z, radius); } // 0x654D93B7 0x654D93B7
inline VOID StopFireInRange(FLOAT x, FLOAT y, FLOAT z, FLOAT range) { FiveXInvoke<VOID>(0x725C7205, x, y, z, range); } // 0x725C7205
inline BOOL GetClosestFirePos(Entity* fire, FLOAT x, FLOAT y, FLOAT z) { return FiveXInvoke<BOOL>(0xC4977B47, fire, x, y, z); } // 0xC4977B47 0xC4977B47
inline VOID AddExplosion(FLOAT x, FLOAT y, FLOAT z, INT explosionType, FLOAT damageScale, BOOL isAudible, BOOL isInvisible, FLOAT cameraShake) { FiveXInvoke<VOID>(0x10AF5258, x, y, z, explosionType, damageScale, isAudible, isInvisible, cameraShake); } // 0x10AF5258 0x10AF5258
inline VOID AddExplosions(Vector3* p1, INT ExplosionType, FLOAT ExplosionRadius, bool isAudible, bool isVisible, FLOAT CameraShake) { FiveXInvoke<VOID>(0x10AF5258, ExplosionType, ExplosionRadius, isAudible, isVisible, CameraShake); } // 0x10AF5258 0x10AF5258
inline VOID AddOwnedExplosion(Ped ped, FLOAT x, FLOAT y, FLOAT z, INT explosionType, FLOAT damageScale, BOOL isAudible, BOOL isInvisible, FLOAT cameraShake) { FiveXInvoke<VOID>(0x27EE0D67, ped, x, y, z, explosionType, damageScale, isAudible, isInvisible, cameraShake); } // 0x27EE0D67 0x27EE0D67
inline VOID AddSpecfxExplosion(FLOAT x, FLOAT y, FLOAT z, INT explosionType, Hash explosionFx, FLOAT damageScale, BOOL isAudible, BOOL isInvisible, FLOAT cameraShake) { FiveXInvoke<VOID>(0xCF358946, x, y, z, explosionType, explosionFx, damageScale, isAudible, isInvisible, cameraShake); } // 0xCF358946 0xCF358946
inline BOOL IsExplosionInArea(INT explosionType, FLOAT x1, FLOAT y1, FLOAT z1, FLOAT x2, FLOAT y2, FLOAT z2) { return FiveXInvoke<BOOL>(0xFB40075B, explosionType, x1, y1, z1, x2, y2, z2); } // 0xFB40075B 0xFB40075B
inline BOOL IsExplosionInSphere(INT explosionType, FLOAT x, FLOAT y, FLOAT z, FLOAT radius) { return FiveXInvoke<BOOL>(0xD455A7F3, explosionType, x, y, z, radius); } // 0xD455A7F3 0xD455A7F3
inline BOOL IsExplosionInAngledArea(INT explosionType, FLOAT x1, FLOAT y1, FLOAT z1, FLOAT x2, FLOAT y2, FLOAT z2, FLOAT angle) { return FiveXInvoke<BOOL>(0x0128FED9, explosionType, x1, y1, z1, x2, y2, z2, angle); } // 0x0128FED9 0x0128FED9
inline Entity GetPedInsideExplosionArea(INT explosionType, FLOAT x1, FLOAT y1, FLOAT z1, FLOAT x2, FLOAT y2, FLOAT z2, FLOAT radius) { return FiveXInvoke<Entity>(0xAEC0D176, explosionType, x1, y1, z1, x2, y2, z2, radius); } // 0xAEC0D176 0xAEC0D176
inline INT GetAllocatedStackSize() { return FiveXInvoke<int>(0x4E9CA30A); } // 0x4E9CA30A
inline BOOL SetAllocatedStackSize(INT StackSize) { return FiveXInvoke<BOOL>(0x11A178B8, StackSize); } // 0x11A178B8
inline VOID SetRandomSeed(Any p0) { FiveXInvoke<VOID>(0xDB3FEB5C, p0); } // 0xDB3FEB5C
inline VOID SetTimeScale(FLOAT Time) { FiveXInvoke<VOID>(0xA7F84694, Time); } // 0xA7F84694
inline VOID SetMissionFlag(Any p0) { FiveXInvoke<VOID>(0x57592D52, p0); } // 0x57592D52
inline Any GetMissionFlag() { return FiveXInvoke<Any>(0x95115F97); } // 0x95115F97
inline VOID SetRandomEventFlag(Any p0) { FiveXInvoke<VOID>(0xA77F31E8, p0); } // 0xA77F31E8
inline Any GetRandomEventFlag() { return FiveXInvoke<Any>(0x794CC92C); } // 0x794CC92C
inline Any GetPrevWeatherTypeHashName() { return FiveXInvoke<Any>(0xA8171E9E); } // 0xA8171E9E
inline Any GetNextWeatherTypeHashName() { return FiveXInvoke<Any>(0x353E8056); } // 0x353E8056
inline BOOL IsPrevWeatherType(char* p0) { return FiveXInvoke<BOOL>(0x250ADA61, p0); } // 0x250ADA61
inline BOOL IsNextWeatherType(char* p0) { return FiveXInvoke<BOOL>(0x99CB167F, p0); } // 0x99CB167F
inline VOID SetWeatherTypePersist(char* WeatherType) { FiveXInvoke<VOID>(0xC6C04C75, WeatherType); } // 0xC6C04C75
inline VOID SetWeatherTypeNowPersist(char* WeatherType) { FiveXInvoke<VOID>(0xC869FE97, WeatherType); } // 0xC869FE97
inline VOID SetWeatherTypeNow(char* WeatherType) { FiveXInvoke<VOID>(0x361E9EAC, WeatherType); } // 0x361E9EAC
inline VOID SetWeatherTypeOverTime(char* WeatherType, FLOAT Time) { FiveXInvoke<VOID>(0x386F0D25, WeatherType, Time); } // 0x386F0D25
inline VOID SetRandomWeatherType() { FiveXInvoke<VOID>(0xE7AA1BC9); } // 0xE7AA1BC9
inline VOID ClearWeatherTypePersist() { FiveXInvoke<VOID>(0x6AB757D8); } // 0x6AB757D8
inline VOID GetWeatherTypeTransition(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x9A5C1D56, p0, p1, p2); } // 0x9A5C1D56
inline VOID SetWeatherTypeTransition(Hash p0, Hash p1, FLOAT p2) { FiveXInvoke<VOID>(0x5CA74040, p0, p1, p2); } // 0x5CA74040
inline VOID SetOverrideWeather(char* WeatherType) { FiveXInvoke<VOID>(0xD9082BB5, WeatherType); } // 0xD9082BB5
inline VOID ClearOverrideWeather() { FiveXInvoke<VOID>(0x7740EA4E); } // 0x7740EA4E
inline VOID WaveIntensity(Any p0) { FiveXInvoke<VOID>(0xDA02F415, p0); } // 0xDA02F415
inline VOID SetWind(Any p0) { FiveXInvoke<VOID>(0xC6294698, p0); } // 0xC6294698
inline VOID SetWindSpeed(FLOAT Speed) { FiveXInvoke<VOID>(0x45705F94, Speed); } // 0x45705F94
inline Any GetWindSpeed() { return FiveXInvoke<Any>(0x098F0F3C); } // 0x098F0F3C
inline VOID SetWindDirection(Any p0) { FiveXInvoke<VOID>(0x381AEEE9, p0); } // 0x381AEEE9
inline Vector3 GetWindDirection() { return FiveXInvoke<Vector3>(0x89499A0D); } // 0x89499A0D
inline Any GetRainLevel() { return FiveXInvoke<Any>(0xC9F67F28); } // 0xC9F67F28
inline Any GetSnowLevel() { return FiveXInvoke<Any>(0x1B09184F); } // 0x1B09184F
inline VOID CreateLightningThunder() { FiveXInvoke<VOID>(0xDF38165E); } // 0xDF38165E
inline VOID LoadCloudHat(char* p0, BOOL p1) { FiveXInvoke<VOID>(0xED88FC61, p0, p1); } // 0xED88FC61
inline FLOAT GetFrameTime() { return FiveXInvoke<float>(0x96374262); } // 0x96374262
inline FLOAT GetRandomFloatInRange(FLOAT p0, FLOAT p1) { return FiveXInvoke<float>(0x0562C4D0, p0, p1); } // 0x0562C4D0
inline INT GetRandomIntInRange(INT StartRange, INT EndRange) { return FiveXInvoke<int>(0x4051115B, StartRange, EndRange); } // 0x4051115B
inline Any GetGroundZFor3dCoord(float x, float y, float z, float* groundZ) { return FiveXInvoke<Any>(0xA1BFD5E0, x, y, z, groundZ); } // 0xA1BFD5E0
inline bool GetGroundZFor3dCoord2(float x, float y, float z, float* groundZ) { return FiveXInvoke<bool>(0xA1BFD5E0, x, y, z, groundZ); } // 0xA1BFD5E0
inline Any Asin(Any p0) { return FiveXInvoke<Any>(0x998E5CAD, p0); } // 0x998E5CAD
inline Any Acos(Any p0) { return FiveXInvoke<Any>(0xF4038776, p0); } // 0xF4038776
inline FLOAT Tan(FLOAT p0) { return FiveXInvoke<float>(0xD320CE5E, p0); } // 0xD320CE5E
inline Any Atan(Any p0) { return FiveXInvoke<Any>(0x7A03CC8E, p0); } // 0x7A03CC8E
inline Any Atan2(Any p0, Any p1) { return FiveXInvoke<Any>(0x2508AC81, p0, p1); } // 0x2508AC8
inline Any GetDistanceBetweenCoords(FLOAT x1, FLOAT y1, FLOAT z1, FLOAT x2, FLOAT y2, FLOAT z2, BOOL unknown) { return FiveXInvoke<Any>(0xF698765E, x1, y1, z1, x2, y2, z2, unknown); } // 0xF698765E
inline Any GetAngleBetween2dVectors(Any p0, Any p1, Any p2, Any p3) { return FiveXInvoke<Any>(0xDBF75E58, p0, p1, p2, p3); } // 0xDBF75E58
inline Any GetHeadingFromVector2d(Any p0, Any p1) { return FiveXInvoke<Any>(0xD209D52B, p0, p1); } // 0xD209D52B
inline VOID SetBit(PINT var, INT bit) { FiveXInvoke<VOID>(0x4EFE7E6B, var, bit); } // 0x4EFE7E6B
inline VOID ClearBit(PINT var, INT bit) { FiveXInvoke<VOID>(0x8BC9E618, var, bit); } // 0x8BC9E618
inline INT GetHashKey(char* ToHash) { return FiveXInvoke<int>(0x98EFF6F1, ToHash); } // 0x98EFF6F1
inline BOOL IsAreaOccupied(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12) { return FiveXInvoke<BOOL>(0xC013972F, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 0xC013972F
inline BOOL IsPositionOccupied(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { return FiveXInvoke<BOOL>(0x452E8D9E, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0x452E8D9E
inline BOOL IsPointObscuredByAMissionEntity(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return FiveXInvoke<BOOL>(0xC161558D, p0, p1, p2, p3, p4, p5, p6); } // 0xC161558D
inline VOID ClearArea(FLOAT X, FLOAT Y, FLOAT Z, FLOAT radius, BOOL p4, BOOL ignoreCopCars, BOOL ignoreObjects, BOOL p7) { FiveXInvoke<VOID>(0x854E9AB8, X, Y, Z, radius, p4, ignoreCopCars, ignoreObjects, p7); } // 0x854E9AB8
inline VOID ClearAreaLeaveVehicleHealth(FLOAT x, FLOAT y, FLOAT z, FLOAT radius, BOOL p4, BOOL p5, BOOL p6, BOOL p7) { FiveXInvoke<VOID>(0x20E4FFD9, x, y, z, radius, p4, p5, p6, p7); } // 0x20E4FFD9
inline VOID ClearAreaOfVehicles(FLOAT x, FLOAT y, FLOAT z, FLOAT radius, BOOL p4, BOOL p5, BOOL p6, BOOL p7, BOOL p8) { FiveXInvoke<VOID>(0x63320F3C, x, y, z, radius, p4, p5, p6, p7, p8); } // 0x63320F3C
inline VOID ClearAngledAreaOfVehicles(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { FiveXInvoke<VOID>(0xF11A3018, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0xF11A3018
inline VOID ClearAreaOfObjects(FLOAT x, FLOAT y, FLOAT z, FLOAT radius, INT flags) { FiveXInvoke<VOID>(0xBB720FE7, x, y, z, radius, flags); } // 0xBB720FE7
inline VOID ClearAreaOfPeds(FLOAT XCoord, FLOAT YCoord, FLOAT zCoord, FLOAT Area, BOOL CreateNetEvent) { FiveXInvoke<VOID>(0x25BE7FA8, XCoord, YCoord, zCoord, Area, CreateNetEvent); } // 0x25BE7FA8
inline VOID ClearAreaOfCops(FLOAT x, FLOAT y, FLOAT z, FLOAT radius, BOOL createNetEvent) { FiveXInvoke<VOID>(0x95C53824, x, y, z, radius, createNetEvent); } // 0x95C53824
inline VOID ClearAreaOfProjectiles(FLOAT x, FLOAT y, FLOAT z, FLOAT radius, BOOL createNetEvent) { FiveXInvoke<VOID>(0x18DB5434, x, y, z, radius, createNetEvent); } // 0x18DB5434
inline VOID SetSaveMenuActive(Any p0) { FiveXInvoke<VOID>(0xF5CCF164, p0); } // 0xF5CCF164
inline VOID SetCreditsActive(Any p0) { FiveXInvoke<VOID>(0xEC2A0ECF, p0); } // 0xEC2A0ECF
inline VOID TerminateAllScriptsWithThisName(char* ScriptName) { FiveXInvoke<VOID>(0x9F861FD4, ScriptName); } // 0x9F861FD4
inline VOID NetworkSetScriptIsSafeForNetworkGame() { FiveXInvoke<VOID>(0x878486CE); } // 0x878486CE
inline Any AddHospitalRestart(Any p0, Any p1, Any p2, Any p3, Any p4) { return FiveXInvoke<Any>(0x4F3E3104, p0, p1, p2, p3, p4); } // 0x4F3E3104
inline VOID DisableHospitalRestart(Any p0, Any p1) { FiveXInvoke<VOID>(0x09F49C72, p0, p1); } // 0x09F49C72
inline Any AddPoliceRestart(Any p0, Any p1, Any p2, Any p3, Any p4) { return FiveXInvoke<Any>(0xE96C29FE, p0, p1, p2, p3, p4); } // 0xE96C29FE
inline VOID DisablePoliceRestart(Any p0, Any p1) { FiveXInvoke<VOID>(0x0A280324, p0, p1); } // 0x0A280324
inline VOID IgnoreNextRestart(Any p0) { FiveXInvoke<VOID>(0xDA13A4B6, p0); } // 0xDA13A4B6
inline VOID SetFadeInAfterDeathArrest(Any p0) { FiveXInvoke<VOID>(0xACDE6985, p0); } // 0xACDE6985
inline VOID SetFadeInAfterLoad(Any p0) { FiveXInvoke<VOID>(0x6E00EB0B, p0); } // 0x6E00EB0B
inline Any RegisterSaveHouse(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return FiveXInvoke<Any>(0x39C1849A, p0, p1, p2, p3, p4, p5, p6); } // 0x39C1849A
inline VOID SetSaveHouse(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xC3240BB4, p0, p1, p2); } // 0xC3240BB4
inline Any OverrideSaveHouse(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return FiveXInvoke<Any>(0x47436C12, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x47436C12
inline VOID DoAutoSave() { FiveXInvoke<VOID>(0x54C44B1A); } // 0x54C44B1A
inline BOOL IsAutoSaveInProgress() { return FiveXInvoke<BOOL>(0x36F75399); } // 0x36F75399
inline VOID BeginReplayStats(Any p0, Any p1) { FiveXInvoke<VOID>(0x17F4F44D, p0, p1); } // 0x17F4F44D
inline VOID EndReplayStats() { FiveXInvoke<VOID>(0xCB570185); } // 0xCB570185
inline VOID ClearReplayStats() { FiveXInvoke<VOID>(0xC47DFF02); } // 0xC47DFF02
inline BOOL IsMemoryCardInUse() { return FiveXInvoke<BOOL>(0x40CE4DFD); } // 0x40CE4DFD
inline VOID ShootSingleBulletBetweenCoords(FLOAT StartPositionX, FLOAT StartPositionY, FLOAT StartPositionZ, FLOAT HitPositionX, FLOAT HitPositionY, FLOAT HitPositionZ, Any p6, Any p7, Hash WeaponHash, Ped PedHandle, Any p10, Any p11, FLOAT Speed) { FiveXInvoke<VOID>(0xCB7415AC, StartPositionX, StartPositionY, StartPositionZ, HitPositionX, HitPositionY, HitPositionZ, p6, p7, WeaponHash, PedHandle, p10, p11, Speed); } // 0xCB7415AC
inline VOID GetModelDimensions(Entity Entity, FLOAT* Minimum, FLOAT* Maximum) { FiveXInvoke<VOID>(0x91ABB8E0, Entity, Minimum, Maximum); } // 0x91ABB8E0
inline VOID SetFakeWantedLevel(Any p0) { FiveXInvoke<VOID>(0x85B1C9FA, p0); } // 0x85B1C9FA
inline BOOL IsBitSet(INT var, INT bit) { return FiveXInvoke<BOOL>(0x902E26AC, var, bit); } // 0x902E26AC
inline VOID UsingMissionCreator(Any p0) { FiveXInvoke<VOID>(0x20AB0B6B, p0); } // 0x20AB0B6B
inline VOID SetMinigameInProgress(Any p0) { FiveXInvoke<VOID>(0x348B9046, p0); } // 0x348B9046
inline BOOL IsMinigameInProgress() { return FiveXInvoke<BOOL>(0x53A95E13); } // 0x53A95E13
inline BOOL IsThisAMinigameScript() { return FiveXInvoke<BOOL>(0x7605EF6F); } // 0x7605EF6F
inline BOOL IsSniperInverted() { return FiveXInvoke<BOOL>(0x5C3BF51B); } // 0x5C3BF51B
inline Any GetCurrentLanguage() { return FiveXInvoke<Any>(0x761BE00B); } // 0x761BE00B
inline Any GetProfileSetting(INT p0) { return FiveXInvoke<Any>(0xD374BEBC, p0); } // 0xD374BEBC
inline BOOL AreStringsEqual(char* string1, char* string2) { return FiveXInvoke<BOOL>(0x877C0BC5, string1, string2); } // 0x877C0BC5
inline Any CompareStrings(Any p0, Any p1, Any p2, Any p3) { return FiveXInvoke<Any>(0xFE25A58F, p0, p1, p2, p3); } // 0xFE25A58F
inline Any Absi(Any p0) { return FiveXInvoke<Any>(0xB44677C5, p0); } // 0xB44677C5
inline Any Absf(Any p0) { return FiveXInvoke<Any>(0xAF6F6E0B, p0); } // 0xAF6F6E0B
inline BOOL IsSniperBulletInArea(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return FiveXInvoke<BOOL>(0x0483715C, p0, p1, p2, p3, p4, p5); } // 0x0483715C
inline BOOL IsProjectileInArea(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return FiveXInvoke<BOOL>(0x78E1A557, p0, p1, p2, p3, p4, p5, p6); } // 0x78E1A557
inline BOOL IsProjectileTypeInArea(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return FiveXInvoke<BOOL>(0x2B73BCF6, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x2B73BCF6
inline BOOL GetCoordsOfProjectileTypeInArea(FLOAT x1, FLOAT y1, FLOAT z1, FLOAT x2, FLOAT y2, FLOAT z2, Hash projectileHash, Vector3* projectilePosition, BOOL ownedByPlayer) { return FiveXInvoke<BOOL>(0x1A40454B, x1, y1, z1, x2, y2, z2, projectileHash, projectilePosition, ownedByPlayer); }
inline BOOL IsProjectileTypeInAngledArea(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return FiveXInvoke<BOOL>(0xD1AE2681, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xD1AE2681
inline BOOL IsBulletInAngledArea(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return FiveXInvoke<BOOL>(0xE2DB58F7, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xE2DB58F7
inline BOOL IsBulletInArea(Any p0, Any p1, Any p2, Any p3, Any p4) { return FiveXInvoke<BOOL>(0xB54F46CA, p0, p1, p2, p3, p4); } // 0xB54F46CA
inline BOOL IsBulletInBox(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return FiveXInvoke<BOOL>(0xAB73ED26, p0, p1, p2, p3, p4, p5, p6); } // 0xAB73ED26
inline BOOL HasBulletImpactedInArea(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return FiveXInvoke<BOOL>(0x902BC7D9, p0, p1, p2, p3, p4, p5); } // 0x902BC7D9
inline BOOL HasBulletImpactedInBox(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return FiveXInvoke<BOOL>(0x2C2618CC, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x2C2618CC
inline BOOL IsOrbisVersion() { return FiveXInvoke<BOOL>(0x40282018); } // 0x40282018
inline BOOL IsDurangoVersion() { return FiveXInvoke<BOOL>(0x46FB06A5); } // 0x46FB06A5
inline BOOL IsXbox360Version() { return FiveXInvoke<BOOL>(0x24005CC8); } // 0x24005CC8
inline BOOL IsPs3Version() { return FiveXInvoke<BOOL>(0x4C0D5303); } // 0x4C0D5303
inline BOOL IsPcVersion() { return FiveXInvoke<BOOL>(0x4D5D9EE3); } // 0x4D5D9EE3
inline BOOL IsAussieVersion() { return FiveXInvoke<BOOL>(0x944BA1DC); } // 0x944BA1DC
inline BOOL IsStringNull(char* p0) { return FiveXInvoke<BOOL>(0x8E71E00F, p0); } // 0x8E71E00F
inline BOOL IsStringNullOrEmpty(char* string) { return FiveXInvoke<BOOL>(0x42E9F2CA, string); } // 0x42E9F2CA
inline BOOL StringToInt(char* string, PINT ToStore) { return FiveXInvoke<BOOL>(0x590A8160, string, ToStore); } // 0x590A8160
inline VOID SetBitsInRange(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x32094719, p0, p1, p2, p3); } // 0x32094719
inline Any GetBitsInRange(Any p0, Any p1, Any p2) { return FiveXInvoke<Any>(0xCA03A1E5, p0, p1, p2); } // 0xCA03A1E5
inline Any AddStuntJump(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13, Any p14, Any p15, Any p16) { return FiveXInvoke<Any>(0xB630E5FF, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16); } // 0xB630E5FF
inline Any AddStuntJumpAngled(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13, Any p14, Any p15, Any p16, Any p17, Any p18) { return FiveXInvoke<Any>(0xB9B7E777, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18); } // 0xB9B7E777
inline VOID DeleteStuntJump(Any p0) { FiveXInvoke<VOID>(0x840CB5DA, p0); } // 0x840CB5DA
inline VOID EnableStuntJumpSet(Any p0) { FiveXInvoke<VOID>(0x9D1E7785, p0); } // 0x9D1E7785
inline VOID DisableStuntJumpSet(Any p0) { FiveXInvoke<VOID>(0x644C9FA4, p0); } // 0x644C9FA4
inline BOOL IsStuntJumpInProgress() { return FiveXInvoke<BOOL>(0xF477D0B1); } // 0xF477D0B1
inline VOID CancelStuntJump() { FiveXInvoke<VOID>(0xF43D9821); } // 0xF43D9821
inline VOID SetGamePaused(BOOL Paused) { FiveXInvoke<VOID>(0x8230FF6C, Paused); } // 0x8230FF6C
inline VOID SetThisScriptCanBePaused(Any p0) { FiveXInvoke<VOID>(0xA0C3CE29, p0); } // 0xA0C3CE29
inline VOID SetThisScriptCanRemoveBlipsCreatedByAnyScript(Any p0) { FiveXInvoke<VOID>(0xD06F1720, p0); } // 0xD06F1720
inline VOID SetInstancePriorityMode(int p0) { FiveXInvoke<VOID>(0x721B2492, p0); } // 0x721B2492
inline BOOL IsFrontendFading() { return FiveXInvoke<BOOL>(0x8FF6232C); } // 0x8FF6232C
inline VOID PopulateNow() { FiveXInvoke<VOID>(0x72C20700); } // 0x72C20700
inline Any GetIndexOfCurrentLevel() { return FiveXInvoke<Any>(0x6F203C6E); } // 0x6F203C6E
inline VOID SetGravityLevel(Any p0) { FiveXInvoke<VOID>(0x2D833F4A, p0); } // 0x2D833F4A
inline VOID StartSaveData(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x881A694D, p0, p1, p2); } // 0x881A694D
inline VOID StopSaveData() { FiveXInvoke<VOID>(0x3B1C07C8); } // 0x3B1C07C8
inline VOID RegisterIntToSave(Any p0, Any p1) { FiveXInvoke<VOID>(0xB930956F, p0, p1); } // 0xB930956F
inline VOID RegisterFloatToSave(Any p0, Any p1) { FiveXInvoke<VOID>(0xDB06F7AD, p0, p1); } // 0xDB06F7AD
inline VOID RegisterBoolToSave(Any p0, Any p1) { FiveXInvoke<VOID>(0x5417E0E0, p0, p1); } // 0x5417E0E0
inline VOID RegisterTextLabelToSave(Any p0, Any p1) { FiveXInvoke<VOID>(0x284352C4, p0, p1); } // 0x284352C4
inline VOID StopSaveStruct() { FiveXInvoke<VOID>(0xC2624A28); } // 0xC2624A28
inline VOID StopSaveArray() { FiveXInvoke<VOID>(0x0CAD8217); } // 0x0CAD8217
inline Any CreateIncident(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return FiveXInvoke<Any>(0xFC5FF7B3, p0, p1, p2, p3, p4, p5, p6); } // 0xFC5FF7B3
inline Any CreateIncidentWithEntity(Any p0, Any p1, Any p2, Any p3, Any p4) { return FiveXInvoke<Any>(0xBBC35B03, p0, p1, p2, p3, p4); } // 0xBBC35B03
inline VOID DeleteIncident(Any p0) { FiveXInvoke<VOID>(0x212BD0DC, p0); } // 0x212BD0DC
inline BOOL IsIncidentValid(Any p0) { return FiveXInvoke<BOOL>(0x31FD0BA4, p0); } // 0x31FD0BA4
inline Any FindSpawnPointInDirection(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return FiveXInvoke<Any>(0x71AEFD77, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x71AEFD77
inline VOID EnableTennisMode(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x0BD3F9EC, p0, p1, p2); } // 0x0BD3F9EC
inline BOOL IsTennisMode(Any p0) { return FiveXInvoke<BOOL>(0x04A947BA, p0); } // 0x04A947BA
inline VOID ResetDispatchIdealSpawnDistance() { FiveXInvoke<VOID>(0xDA65ECAA); } // 0xDA65ECAA
inline VOID SetDispatchIdealSpawnDistance(Any p0) { FiveXInvoke<VOID>(0x6283BE32, p0); } // 0x6283BE32
inline VOID ResetDispatchTimeBetweenSpawnAttempts(Any p0) { FiveXInvoke<VOID>(0x1479E85A, p0); } // 0x1479E85A
inline VOID SetDispatchTimeBetweenSpawnAttempts(Any p0, Any p1) { FiveXInvoke<VOID>(0xABADB709, p0, p1); } // 0xABADB709
inline VOID SetDispatchTimeBetweenSpawnAttemptsMultiplier(Any p0, Any p1) { FiveXInvoke<VOID>(0x1C996BCD, p0, p1); } // 0x1C996BCD
inline VOID RemoveDispatchSpawnBlockingArea(Any p0) { FiveXInvoke<VOID>(0xA8D2FB92, p0); } // 0xA8D2FB92
inline VOID ResetDispatchSpawnBlockingAreas() { FiveXInvoke<VOID>(0x9A17F835); } // 0x9A17F835
inline VOID SetExplosiveAmmoThisFrame(Player player) { FiveXInvoke<VOID>(0x2EAFA1D1, player); } // 0x2EAFA1D1
inline VOID SetFireAmmoThisFrame(Player player) { FiveXInvoke<VOID>(0x7C18FC8A, player); } // 0x7C18FC8A
inline VOID SetExplosiveMeleeThisFrame(Player player) { FiveXInvoke<VOID>(0x96663D56, player); } // 0x96663D56
inline bool StartParticleFxNonLoopedAtCoord2(char* effectName, FLOAT x, FLOAT y, FLOAT z, FLOAT xRot, FLOAT yRot, FLOAT zRot, FLOAT scale, bool p8, bool p9, bool p10) { return FiveXInvoke<bool>(0xDD79D679, effectName, x, y, z, xRot, yRot, zRot, scale, p8, p9, p10); } // 0xDD79D679
inline VOID DrawMarker2(INT type, FLOAT posX, FLOAT posY, FLOAT posZ, FLOAT dirX, FLOAT dirY, FLOAT dirZ, FLOAT rotX, FLOAT rotY, FLOAT rotZ, FLOAT scaleX, FLOAT scaleY, FLOAT scaleZ, INT colorR, INT colorG, INT colorB, INT alpha, BOOL bobUpAndDown, BOOL faceCamera, INT p19, BOOL rotate, char* textureDict, char* textureName, BOOL drawOnEnts) { FiveXInvoke<VOID>(0x48D84A02, type, posX, posY, posZ, dirX, dirY, dirZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, colorR, colorG, colorB, alpha, bobUpAndDown, faceCamera, p19, rotate, textureDict, textureName, drawOnEnts); }
inline VOID Cartoongunfx(BOOL toggle) { FiveXInvoke<VOID>(0xC61C75E9, toggle); }
inline VOID Alienfx(Entity Entity, BOOL toggle) { FiveXInvoke<VOID>(0xCE8B8748, Entity, toggle); }
inline BOOL StartParticleFxNonLoopedOnPedBone2(char* effectName, Ped ped, FLOAT xOffset, FLOAT yOffset, FLOAT zOffset, FLOAT xRot, FLOAT yRot, FLOAT zRot, INT boneIndex, FLOAT scale, BOOL p10, BOOL p11, BOOL p12) { return FiveXInvoke<BOOL>(0x161780C1, effectName, ped, xOffset, yOffset, zOffset, xRot, yRot, zRot, boneIndex, scale, p10, p11, p12); } // 0x161780C1
inline VOID SetParticleFxNonLoopedColour(INT Red, INT Green, INT Blue) { FiveXInvoke<VOID>(0x7B689E20, Red, Green, Blue); } // 0x7B689E20
inline VOID SetPtfxAssetNextCall(char* p0) { FiveXInvoke<VOID>(0x9C720B61, p0); } // 0x9C720B61
inline VOID SetDebugLinesAndSpheresDrawingActive(BOOL enabled) { FiveXInvoke<VOID>(0x1418CA37, enabled); } // 0x1418CA37
inline VOID DrawDebugLine(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { FiveXInvoke<VOID>(0xABF783AB, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xABF783AB
inline VOID DrawDebugLineWithTwoColours(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13) { FiveXInvoke<VOID>(0xE8BFF632, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); } // 0xE8BFF632
inline VOID DrawDebugSphere(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { FiveXInvoke<VOID>(0x304D0EEF, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x304D0EEF
inline VOID DrawDebugBox(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { FiveXInvoke<VOID>(0x8524A848, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x8524A848
inline VOID DrawDebugText(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { FiveXInvoke<VOID>(0x269B006F, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x269B006F
inline VOID DrawDebugText2d(char* Text, FLOAT posX, FLOAT posY, FLOAT posZ, INT R, INT G, INT B, INT A) { FiveXInvoke<VOID>(0x528B973B, Text, posX, posY, posZ, R, G, B, A); } // 0x528B973B
inline VOID DrawLine(FLOAT posX1, FLOAT posY1, FLOAT posZ1, FLOAT posX2, FLOAT posY2, FLOAT posZ2, INT R, INT G, INT B, INT A) { FiveXInvoke<VOID>(0xB3426BCC, posX1, posY1, posZ1, posX2, posY2, posZ2, R, G, B, A); } // 0xB3426BCC
inline VOID DrawPoly(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12) { FiveXInvoke<VOID>(0xABD19253, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 0xABD19253
inline Any MeleeSeethroughSkipped() { return FiveXInvoke<Any>(0x65376C9B); } // 0x65376C9B
inline Any GetMaximumNumberOfPhotos() { return FiveXInvoke<Any>(0x727AA63F); } // 0x727AA63F
inline VOID DrawLightWithRange(FLOAT XCoord, FLOAT YCoord, FLOAT ZCoord, INT Red, INT Green, INT Blue, FLOAT Width, FLOAT Height) { FiveXInvoke<VOID>(0x6A396E9A, XCoord, YCoord, ZCoord, Red, Green, Blue, Width, Height); } // 0x6A396E9A
inline VOID DrawSpotLight(FLOAT x, FLOAT y, FLOAT z, FLOAT dir_x, FLOAT dir_y, FLOAT dir_z, INT r, INT g, INT b, FLOAT distance, FLOAT falloff, FLOAT p11, FLOAT radius, FLOAT p13) { FiveXInvoke<VOID>(0xBDBC410C, x, y, z, dir_x, dir_y, dir_z, r, g, b, distance, falloff, p11, radius, p13); } // 0xBDBC410C
inline Any CreateCheckpoint(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12) { return FiveXInvoke<Any>(0xF541B690, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 0xF541B690
inline VOID SetCheckpointCylinderHeight(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0xFF0F9B22, p0, p1, p2, p3); } // 0xFF0F9B22
inline VOID SetCheckpointRgba(Any p0, Any colorR, Any colorG, Any colorB, Any colorA) { FiveXInvoke<VOID>(0xEF9C8CB3, p0, colorR, colorG, colorB, colorA); } // 0xEF9C8CB3
inline VOID DeleteCheckpoint(Any p0) { FiveXInvoke<VOID>(0xB66CF3CA, p0); } // 0xB66CF3CA
inline VOID SetStreamedTextureDictAsNoLongerNeeded(char* Type) { FiveXInvoke<VOID>(0xF07DDA38, Type); } // 0xF07DDA38
inline VOID SetUiLayer(INT p0) { FiveXInvoke<VOID>(0xADF81D24, p0); } // 0xADF81D24
inline VOID ScreenDrawPositionBegin(INT x, INT y) { FiveXInvoke<VOID>(0x228A2598, x, y); } // 0x228A2598
inline VOID ScreenDrawPositionEnd() { FiveXInvoke<VOID>(0x3FE33BD6); } // 0x3FE33BD6
inline VOID ScreenDrawPositionRatio(FLOAT x, FLOAT y, FLOAT p2, FLOAT p3) { FiveXInvoke<VOID>(0x76C641E4, x, y, p2, p3); } // 0x76C641E4
inline Any AddEntityIcon(Entity entity, char* icon) { return FiveXInvoke<Any>(0xF3027D21, entity, icon); } // 0xF3027D21
inline VOID SetEntityIconVisibility(Entity entity, BOOL toggle) { FiveXInvoke<VOID>(0xD1D2FD52, entity, toggle); } // 0xD1D2FD52
inline VOID SetEntityIconColor(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0x6EE1E946, p0, p1, p2, p3, p4); } // 0x6EE1E946
inline VOID SetDrawOrigin(FLOAT p0, FLOAT p1, FLOAT p2, Any p3) { FiveXInvoke<VOID>(0xE10198D5, p0, p1, p2, p3); } // 0xE10198D5
inline VOID ClearDrawOrigin() { FiveXInvoke<VOID>(0xDD76B263); } // 0xDD76B263
inline VOID AttachTvAudioToEntity(Any p0) { FiveXInvoke<VOID>(0x784944DB, p0); } // 0x784944DB
inline VOID SetTvAudioFrontend(Any p0) { FiveXInvoke<VOID>(0x2E0DFA35, p0); } // 0x2E0DFA35
inline Any LoadMovieMeshSet(Any p0) { return FiveXInvoke<Any>(0x9627905C, p0); } // 0x9627905C
inline VOID ReleaseMovieMeshSet(Any p0) { FiveXInvoke<VOID>(0x4FA5501D, p0); } // 0x4FA5501D
inline VOID GetScreenResolution(PINT p0, PINT p1) { FiveXInvoke<VOID>(0x29F3572F, p0, p1); } // 0x29F3572F
inline VOID StartScreenEffect(char* effectName, int duration, BOOL looped) { FiveXInvoke<VOID>(0x1D980479, effectName, duration, looped); } // 0x1D980479
inline VOID StopScreenEffect(char* p0) { FiveXInvoke<VOID>(0x06BB5CDA, p0); } // 0x06BB5CDA
inline Any GetIsWidescreen() { return FiveXInvoke<Any>(0xEC717AEF); } // 0xEC717AEF
inline Any GetIsHidef() { return FiveXInvoke<Any>(0x1C340359); } // 0x1C340359
inline VOID SetNightvision(BOOL Toggle) { FiveXInvoke<VOID>(0xD1E5565F, Toggle); } // 0xD1E5565F
inline VOID SetNoiseoveride(Any p0) { FiveXInvoke<VOID>(0xD576F5DD, p0); } // 0xD576F5DD
inline VOID SetNoisinessoveride(Any p0) { FiveXInvoke<VOID>(0x046B62D9, p0); } // 0x046B62D9
inline BOOL World3dToScreen2d(FLOAT x3d, FLOAT y3d, FLOAT z3d, FLOAT* x2d, FLOAT* y2d) { return FiveXInvoke<BOOL>(0x1F950E4B, x3d, y3d, z3d, x2d, y2d); } // 0x1F950E4B 0x1F950E4B
inline Vector3 GetTextureResolution(char* p0, char* p1) { return FiveXInvoke<Vector3>(0x096DAA4D, p0, p1); } // 0x096DAA4D
inline VOID SetFlash(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0x7E55A1EE, p0, p1, p2, p3, p4); } // 0x7E55A1EE
inline Object CreateTrackedPoint() { return FiveXInvoke<Object>(0x3129C31A); } // 0x3129C31A
inline VOID SetTrackedPointInfo(Object poINT, Any x, Any y, Any z, FLOAT radius) { FiveXInvoke<VOID>(0x28689AA4, poINT, x, y, z, radius); } // 0x28689AA4
inline BOOL IsTrackedPointVisible(Any p0) { return FiveXInvoke<BOOL>(0x0BFC4F64, p0); } // 0x0BFC4F64
inline VOID DestroyTrackedPoint(Any p0) { FiveXInvoke<VOID>(0x14AC675F, p0); } // 0x14AC675F
inline VOID SetSeethrough(BOOL Toggle) { FiveXInvoke<VOID>(0x74D4995C, Toggle); } // 0x74D4995C
inline VOID SeethroughReset() { FiveXInvoke<VOID>(0x310E9B67); } // 0x310E9B67
inline BOOL IsParticleFxDelayedBlink() { return FiveXInvoke<BOOL>(0xEA432A94); } // 0xEA432A94
inline Any StartParticleFxNonLoopedAtCoord(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { return FiveXInvoke<Any>(0xDD79D679, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0xDD79D679
inline Any StartFwparticleFxNonLoopedAtCoord(char* FWType, FLOAT* xCoord, FLOAT* yCoord, FLOAT* zCoord, FLOAT unk, FLOAT unk2, FLOAT size, INT unk3, INT unk4, INT unk5, INT unk6) { return FiveXInvoke<Any>(0x633F8C48, FWType, xCoord, yCoord, zCoord, unk, unk2, size, unk3, unk4, unk5, unk6); } // 0x633F8C48
inline Any StartParticleFxNonLoopedOnPedBone(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12) { return FiveXInvoke<Any>(0x53DAEF4E, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 0x53DAEF4E
inline BOOL StartParticleFxNonLoopedOnEntity(char* effectName, Entity entity, FLOAT xOffset, FLOAT yOffset, FLOAT zOffset, FLOAT xRot, FLOAT yRot, FLOAT zRot, FLOAT scale, BOOL p9, BOOL p10, BOOL p11) { return FiveXInvoke<BOOL>(0x9604DAD4, effectName, entity, xOffset, yOffset, zOffset, xRot, yRot, zRot, scale, p9, p10, p11); } // 0x9604DAD4 0x9604DAD4
inline VOID SetParticleFxNonLoopedAlpha(Any p0) { FiveXInvoke<VOID>(0x497EAFF2, p0); } // 0x497EAFF2
inline Any StartParticleFxLoopedAtCoord(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { return FiveXInvoke<Any>(0xD348E3E6, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0xD348E3E6
inline Any StartParticleFxLoopedOnPedBone(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12) { return FiveXInvoke<Any>(0xF8FC196F, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 0xF8FC196F
inline Any StartParticleFxLoopedOnEntity(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { return FiveXInvoke<Any>(0x0D06FF62, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0x0D06FF62
inline VOID StopParticleFxLooped(Any p0, Any p1) { FiveXInvoke<VOID>(0xD245455B, p0, p1); } // 0xD245455B
inline VOID RemoveParticleFx(Any p0, Any p1) { FiveXInvoke<VOID>(0x6BA48C7E, p0, p1); } // 0x6BA48C7E
inline VOID RemoveParticleFxFromEntity(Entity p0) { FiveXInvoke<VOID>(0xCEDE52E9, p0); } // 0xCEDE52E9
inline VOID RemoveParticleFxInRange(FLOAT x, FLOAT y, FLOAT z, FLOAT range) { FiveXInvoke<VOID>(0x7EB8F275, x, y, z, range); } // 0x7EB8F275
inline BOOL DoesParticleFxLoopedExist(Any p0) { return FiveXInvoke<BOOL>(0xCBF91D2A, p0); } // 0xCBF91D2A
inline VOID SetParticleFxLoopedOffsets(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { FiveXInvoke<VOID>(0x641F7790, p0, p1, p2, p3, p4, p5, p6); } // 0x641F7790
inline VOID SetParticleFxLoopedEvolution(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x1CBC1373, p0, p1, p2); } // 0x1CBC1373
inline VOID SetParticleFxLoopedColour(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0x5219D530, p0, p1, p2, p3, p4); } // 0x5219D530
inline VOID SetParticleFxLoopedAlpha(Any p0, Any p1) { FiveXInvoke<VOID>(0x5ED49BE1, p0, p1); } // 0x5ED49BE1
inline VOID SetParticleFxLoopedScale(Any p0, Any p1) { FiveXInvoke<VOID>(0x099B8B49, p0, p1); } // 0x099B8B49
inline VOID SetParticleFxCamInsideVehicle(Any p0) { FiveXInvoke<VOID>(0x19EC0001, p0); } // 0x19EC0001
inline VOID SetParticleFxBloodScale(Any p0) { FiveXInvoke<VOID>(0x18136DE0, p0); } // 0x18136DE0
inline VOID SetCameraEndtime(Any p0) { FiveXInvoke<VOID>(0xC61C75E9, p0); } // 0xC61C75E9
inline VOID WashDecalsInRange(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0xDEECBC57, p0, p1, p2, p3, p4); } // 0xDEECBC57
inline VOID WashDecalsFromVehicle(Any p0, Any p1) { FiveXInvoke<VOID>(0x2929F11A, p0, p1); } // 0x2929F11A
inline VOID FadeDecalsInRange(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0xF81E884A, p0, p1, p2, p3, p4); } // 0xF81E884A
inline VOID RemoveDecalsInRange(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x06A619A0, p0, p1, p2, p3); } // 0x06A619A0
inline VOID RemoveDecalsFromObject(Any p0) { FiveXInvoke<VOID>(0x8B67DCA7, p0); } // 0x8B67DCA7
inline VOID RemoveDecalsFromObjectFacing(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0xF4999A55, p0, p1, p2, p3); } // 0xF4999A55
inline VOID RemoveDecalsFromVehicle(Any p0) { FiveXInvoke<VOID>(0x831D06CA, p0); } // 0x831D06CA
inline Any AddDecal(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13, Any p14, Any p15, Any p16, Any p17, Any p18, Any p19) { return FiveXInvoke<Any>(0xEAD0C412, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19); } // 0xEAD0C412
inline Any AddPetrolDecal(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return FiveXInvoke<Any>(0x1259DF42, p0, p1, p2, p3, p4, p5); } // 0x1259DF42
inline VOID SetCameraCameraForward() { FiveXInvoke<VOID>(0xCCCA6855); } // 0xCCCA6855
inline VOID RemoveDecal(Any p0) { FiveXInvoke<VOID>(0xA4363188, p0); } // 0xA4363188
inline BOOL IsDecalAlive(Any p0) { return FiveXInvoke<BOOL>(0xCDD4A61A, p0); } // 0xCDD4A61A
inline Any GetDecalWashLevel(Any p0) { return FiveXInvoke<Any>(0x054448EF, p0); } // 0x054448EF
inline VOID MoveVehicleDecals(Any p0, Any p1) { FiveXInvoke<VOID>(0xCE9E6CF2, p0, p1); } // 0xCE9E6CF2
inline VOID DisableVehicleDistantlights(Any p0) { FiveXInvoke<VOID>(0x7CFAE36F, p0); } // 0x7CFAE36F
inline VOID SetTimecycleModifier(char* CycleType) { FiveXInvoke<VOID>(0xA81F3638, CycleType); } // 0xA81F3638
inline VOID SetTimecycleModifierStrength(float strength) { FiveXInvoke<VOID>(0x458F4F45, strength); } // 0x458F4F45
inline VOID SetTransitionTimecycleModifier(Any p0, Any p1) { FiveXInvoke<VOID>(0xBB2BA72A, p0, p1); } // 0xBB2BA72A
inline VOID ClearTimecycleModifier() { FiveXInvoke<VOID>(0x8D8DF8EE); } // 0x8D8DF8EE
inline Any GetTimecycleModifierIndex() { return FiveXInvoke<Any>(0x594FEEC4); } // 0x594FEEC4
inline VOID PushTimecycleModifier() { FiveXInvoke<VOID>(0x7E082045); } // 0x7E082045
inline VOID PopTimecycleModifier() { FiveXInvoke<VOID>(0x79D7D235); } // 0x79D7D235
inline INT RequestScaleformMovie(char* scaleformName) { return FiveXInvoke<int>(0xC67E3DCB, scaleformName); } // 0xC67E3DCB
inline BOOL HasScaleformMovieLoaded(INT p0) { return FiveXInvoke<BOOL>(0xDDFB6448, p0); } // 0xDDFB6448
inline VOID SetScaleformMovieAsNoLongerNeeded(Any p0) { FiveXInvoke<VOID>(0x5FED3BA1, p0); } // 0x5FED3BA1
inline VOID DrawScaleformMovie(INT handle, FLOAT x, FLOAT y, FLOAT width, FLOAT height, INT r, INT g, INT b, INT a, INT unkb) { FiveXInvoke<VOID>(0x48DA6A58, handle, x, y, width, height, r, g, b, a, unkb); } // 0x48DA6A58
inline VOID DrawScaleformMovieFullscreen(INT scaleform, INT red, INT green, INT blue, INT alpha) { FiveXInvoke<VOID>(0x7B48E696, scaleform, red, green, blue, alpha); } // 0x7B48E696
inline VOID DrawScaleformMovie3d(INT scaleform, FLOAT posX, FLOAT posY, FLOAT posZ, FLOAT rotX, FLOAT rotY, FLOAT rotZ, FLOAT p7, FLOAT p8, FLOAT p9, FLOAT scaleX, FLOAT scaleY, FLOAT scaleZ, Any p13) { FiveXInvoke<VOID>(0xC4F63A89, scaleform, posX, posY, posZ, rotX, rotY, rotZ, p7, p8, p9, scaleX, scaleY, scaleZ, p13); }// 0x87D51D72255D4E78 0xC4F63A89
inline BOOL PushScaleformMovieFunctionFromHudComponent(INT hudComponent, char* functionName) { return FiveXInvoke<BOOL>(0x5D66CE1E, hudComponent, functionName); } // 0x5D66CE1E
inline BOOL BeginScaleformMovieMethod(INT scaleform, char* functionName) { return FiveXInvoke<BOOL>(0x215ABBE8, scaleform, functionName); } // 0x215ABBE8
inline VOID EndScaleformMovieMethod() { FiveXInvoke<VOID>(0x02DBF2D7); } // 0x02DBF2D7
inline Any SittingTv(Any p0) { return FiveXInvoke<Any>(0x516862EB, p0); } // 0x516862EB
inline VOID AddScaleformMovieMethodParameterInt(INT value) { FiveXInvoke<VOID>(0x716777CB, value); } // 0x716777CB
inline VOID PushScaleformMovieFunctionParameterFloat(FLOAT value) { FiveXInvoke<VOID>(0x9A01FFDA, value); } // 0x9A01FFDA
inline VOID BeginTextCommandScaleformString(char* p0) { FiveXInvoke<VOID>(0x3AC9CB55, p0); } // 0x3AC9CB55
inline VOID EndTextCommandScaleformString() { FiveXInvoke<VOID>(0x386CE0B8); } // 0x386CE0B8
inline VOID PushScaleformMovieFunctionParameterString(char* p0) { FiveXInvoke<VOID>(0x4DAAD55B, p0); } // 0x4DAAD55B
inline VOID SetTvChannel(Any p0) { FiveXInvoke<VOID>(0x41A8A627, p0); } // 0x41A8A627
inline Any GetTvChannel() { return FiveXInvoke<Any>(0x6B96145A); } // 0x6B96145A
inline VOID SetTvVolume(FLOAT p0) { FiveXInvoke<VOID>(0xF3504F4D, p0); } // 0xF3504F4D
inline Any GetTvVolume() { return FiveXInvoke<Any>(0x39555CF0); } // 0x39555CF0
inline VOID DrawTvChannel(FLOAT p0, FLOAT p1, FLOAT p2, FLOAT p3, FLOAT p4, Any p5, Any p6, Any p7, Any p8) { FiveXInvoke<VOID>(0x8129EF89, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x8129EF89
inline VOID EnableMovieSubtitles(Any p0) { FiveXInvoke<VOID>(0xC2DEBA3D, p0); } // 0xC2DEBA3D
inline INT NetworkSctvSlots(INT p0) { return FiveXInvoke<INT>(0x3C3E2AB6, p0); } //0x3C3E2AB6
inline Any NetworkIsFriendIndexOnline(INT p0) { return FiveXInvoke<Any>(0x94AE7172, p0); } // 0x94AE7172
inline VOID SetNetworkIdSyncToPlayer(INT netId, Player player, BOOL toggle) { FiveXInvoke<VOID>(0x4D15FDB1, netId, player, toggle); } // 0x4D15FDB1
inline VOID NetworkHandleFromPlayer1(Ped PedHandle, INT FreeMemPoINTer, INT p2) { FiveXInvoke<VOID>(0xD3498917, PedHandle, FreeMemPoINTer, p2); } // 0xD3498917
inline Any NetworkSendTextMessage1(char* Text, INT FreeMemPoINTer) { return FiveXInvoke<Any>(0xAFFEA720, Text, FreeMemPoINTer); } // 0xAFFEA720
inline BOOL NetworkAddFriend2(Any* p0, char* GamertagID) { return FiveXInvoke<BOOL>(0x20E5B3EE, p0, GamertagID); }
inline Any NetworkIsSignedIn() { return FiveXInvoke<Any>(0xADD0B40F); } // 0xADD0B40F
inline Any NetworkIsSignedOnline() { return FiveXInvoke<Any>(0x6E5BDCE2); } // 0x6E5BDCE2
inline Any NetworkIsCloudAvailable() { return FiveXInvoke<Any>(0xC7FF5AFC); } // 0xC7FF5AFC
inline Any NetworkIsHost() { return FiveXInvoke<Any>(0xE46AC10F); } // 0xE46AC10F
inline Any NetworkHaveOnlinePrivileges() { return FiveXInvoke<Any>(0xEF63BFDF); } // 0xEF63BFDF
inline VOID NetworkBail() { FiveXInvoke<VOID>(0x87D79A04); } // 0x87D79A04
inline Any NetworkCanEnterMultiplayer() { return FiveXInvoke<Any>(0x4A23B9C9); } // 0x4A23B9C9
inline Any NetworkSessionEnter(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return FiveXInvoke<Any>(0x543CD2BE, p0, p1, p2, p3, p4, p5); } // 0x543CD2BE
inline BOOL NetworkSessionCrewMatchmaking(INT p0, INT p1, INT p2, INT p3, bool p4) { return FiveXInvoke<BOOL>(0xD7624E6B, p0, p1, p2, p3, p4); } // 0xD7624E6B
inline Any NetworkSessionHost(Any p0, Any p1, Any p2) { return FiveXInvoke<Any>(0x6716460F, p0, p1, p2); } // 0x6716460F
inline Any NetworkSessionHostFriendsOnly(Any p0, Any p1) { return FiveXInvoke<Any>(0x26864403, p0, p1); } // 0x26864403
inline Any NetworkSessionEnd(Any p0, Any p1) { return FiveXInvoke<Any>(0xBCACBEA2, p0, p1); } // 0xBCACBEA2
inline VOID NetworkSessionKickPlayer(Player p0) { FiveXInvoke<VOID>(0x1E20138A, p0); } // 0x1E20138A
inline Any NetworkIsFindingGamers() { return FiveXInvoke<Any>(0xA6DAA79F); } // 0xA6DAA79F
inline Any NetworkGetNumFoundGamers() { return FiveXInvoke<Any>(0xF4B80C7E); } // 0xF4B80C7E
inline Any NetworkGetFoundGamer(Any p0, Any p1) { return FiveXInvoke<Any>(0xA08C9141, p0, p1); } // 0xA08C9141
inline VOID NetworkClearFoundGamers() { FiveXInvoke<VOID>(0x6AA9A154); } // 0x6AA9A154
inline VOID NetworkIsPlayerAnimationDrawingSynchronized() { FiveXInvoke<VOID>(0x3D6360B5); } // 0x3D6360B5
inline VOID NetworkSessionCancelInvite() { FiveXInvoke<VOID>(0x20317535); } // 0x20317535
inline Any NetworkHasPendingInvite() { return FiveXInvoke<Any>(0x0C207D6E); } // 0x0C207D6E
inline VOID NetworkSessionGetInviter(Any p0) { FiveXInvoke<VOID>(0xE9C6B3FD, p0); } // 0xE9C6B3FD
inline VOID NetworkSuppressInvite(Any p0) { FiveXInvoke<VOID>(0x323DC78C, p0); } // 0x323DC78C
inline VOID NetworkBlockInvites(Any p0) { FiveXInvoke<VOID>(0xD156FD1A, p0); } // 0xD156FD1A
inline VOID NetworkSessionHostSinglePlayer(Any p0) { FiveXInvoke<VOID>(0xF3B1CA85, p0); } // 0xF3B1CA85
inline VOID NetworkSessionLeaveSinglePlayer() { FiveXInvoke<VOID>(0xC692F86A); } // 0xC692F86A
inline Any NetworkIsGameInProgress() { return FiveXInvoke<Any>(0x09B88E3E); } // 0x09B88E3E
inline Any NetworkIsSessionActive() { return FiveXInvoke<Any>(0x715CB8C4); } // 0x715CB8C4
inline Any NetworkIsInSession() { return FiveXInvoke<Any>(0x4BC4105E); } // 0x4BC4105E
inline Any NetworkIsSessionStarted() { return FiveXInvoke<Any>(0x9D854A37); } // 0x9D854A37
inline Any NetworkIsSessionBusy() { return FiveXInvoke<Any>(0x8592152D); } // 0x8592152D
inline Any NetworkCanSessionEnd() { return FiveXInvoke<Any>(0xE1FCCDBA); } // 0xE1FCCDBA
inline VOID NetworkSessionVoiceHost() { FiveXInvoke<VOID>(0x345C2980); } // 0x345C2980
inline VOID NetworkSessionVoiceLeave() { FiveXInvoke<VOID>(0xE566C7DA); } // 0xE566C7DA
inline VOID NetworkSetKeepFocuspoint(Any p0, Any p1) { FiveXInvoke<VOID>(0x075321B5, p0, p1); } // 0x075321B5
inline Any NetworkSendTextMessage(char* Text, PINT FreeMemPoINTer) { return FiveXInvoke<Any>(0xAFFEA720, Text, FreeMemPoINTer); } // 0xAFFEA720
inline VOID NetworkSetActivitySpectator(Any p0) { FiveXInvoke<VOID>(0xFC9AD060, p0); } // 0xFC9AD060
inline Any NetworkIsActivitySpectator() { return FiveXInvoke<Any>(0xAF329720); } // 0xAF329720
inline VOID NetworkSetActivitySpectatorMax(Any p0) { FiveXInvoke<VOID>(0x74E0BC0A, p0); } // 0x74E0BC0A
inline Any NetworkGetActivityPlayerNum(Any p0) { return FiveXInvoke<Any>(0x31F951FD, p0); } // 0x31F951FD
inline Any NetworkIsActivitySpectatorFromHandle(Any p0) { return FiveXInvoke<Any>(0x58F1DF7D, p0); } // 0x58F1DF7D
inline Any NetworkHostTransition(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return FiveXInvoke<Any>(0x146764FB, p0, p1, p2, p3, p4, p5); } // 0x146764FB
inline VOID NetworkSetTransitionCreatorHandle(Any p0) { FiveXInvoke<VOID>(0x1DD01FE7, p0); } // 0x1DD01FE7
inline VOID NetworkClearTransitionCreatorHandle() { FiveXInvoke<VOID>(0x8BB336F7); } // 0x8BB336F7
inline Any NetworkInviteGamersToTransition(Any p0, Any p1) { return FiveXInvoke<Any>(0x5332E645, p0, p1); } // 0x5332E645
inline VOID NetworkSetGamerInvitedToTransition(Any p0) { FiveXInvoke<VOID>(0x17F1C69D, p0); } // 0x17F1C69D
inline Any NetworkLeaveTransition() { return FiveXInvoke<Any>(0x3A3599B7); } // 0x3A3599B7
inline Any NetworkLaunchTransition() { return FiveXInvoke<Any>(0xE3570BA2); } // 0xE3570BA2
inline Any NetworkDoTransitionToGame(Any p0, Any p1) { return FiveXInvoke<Any>(0x1B2114D2, p0, p1); } // 0x1B2114D2
inline Any NetworkDoTransitionToNewGame(Any p0, Any p1, Any p2) { return FiveXInvoke<Any>(0x58AFBE63, p0, p1, p2); } // 0x58AFBE63
inline Any NetworkDoTransitionToFreemode(Any p0, Any p1, Any p2, Any p3, Any p4) { return FiveXInvoke<Any>(0xC7CB8ADF, p0, p1, p2, p3, p4); } // 0xC7CB8ADF
inline Any NetworkDoTransitionToNewFreemode(Any p0, Any p1, Any p2, Any p3, Any p4) { return FiveXInvoke<Any>(0xAD13375E, p0, p1, p2, p3, p4); } // 0xAD13375E
inline Any NetworkIsTransitionToGame() { return FiveXInvoke<Any>(0x17146B2B); } // 0x17146B2B
inline Any NetworkGetTransitionMembers(Any p0, Any p1) { return FiveXInvoke<Any>(0x31F19263, p0, p1); } // 0x31F19263
inline Any NetworkSendTransitionGamerInstruction(Any p0, Any p1, Any p2, Any p3, Any p4) { return FiveXInvoke<Any>(0x468B0884, p0, p1, p2, p3, p4); } // 0x468B0884
inline Any NetworkMarkTransitionGamerAsFullyJoined(Any p0) { return FiveXInvoke<Any>(0x03383F57, p0); } // 0x03383F57
inline Any NetworkIsTransitionHost() { return FiveXInvoke<Any>(0x0C0900BC); } // 0x0C0900BC
inline Any NetworkIsTransitionHostFromHandle(Any p0) { return FiveXInvoke<Any>(0x0E2854C4, p0); } // 0x0E2854C4
inline Any NetworkGetTransitionHost(Any p0) { return FiveXInvoke<Any>(0x73098D40, p0); } // 0x73098D40
inline Any NetworkIsInTransition() { return FiveXInvoke<Any>(0xC3CDB626); } // 0xC3CDB626
inline Any NetworkIsTransitionStarted() { return FiveXInvoke<Any>(0x7917E111); } // 0x7917E111
inline Any NetworkIsTransitionBusy() { return FiveXInvoke<Any>(0xA357A2C6); } // 0xA357A2C6
inline Any NetworkHasPlayerStartedTransition(Any p0) { return FiveXInvoke<Any>(0x4ABD1E59, p0); } // 0x4ABD1E59
inline Any NetworkJoinTransition(Any p0) { return FiveXInvoke<Any>(0xB054EC4B, p0); } // 0xB054EC4B
inline Any NetworkIsActivitySession() { return FiveXInvoke<Any>(0x577DAA8A); } // 0x577DAA8A
inline Any NetworkAcceptPresenceInvite(Any p0) { return FiveXInvoke<Any>(0xE5DA4CED, p0); } // 0xE5DA4CED
inline Any NetworkGetPresenceInviteHandle(Any p0, Any p1) { return FiveXInvoke<Any>(0xB2451429, p0, p1); } // 0xB2451429
inline VOID NetworkRemoveTransitionInvite(Any p0) { FiveXInvoke<VOID>(0xFDE84CB7, p0); } // 0xFDE84CB7
inline Any NetworkInviteGamers(Any p0, Any p1, Any p2, Any p3) { return FiveXInvoke<Any>(0x52FB8074, p0, p1, p2, p3); } // 0x52FB8074
inline Any NetworkGetCurrentlySelectedGamerHandleFromInviteMenu(Any p0) { return FiveXInvoke<Any>(0x72BA00CE, p0); } // 0x72BA00CE
inline Any NetworkSetCurrentlySelectedGamerHandleFromInviteMenu(Any p0) { return FiveXInvoke<Any>(0xFD95899E, p0); } // 0xFD95899E
inline Any FilloutPmPlayerList(Any p0, Any p1, Any p2) { return FiveXInvoke<Any>(0xCE40F423, p0, p1, p2); } // 0xCE40F423
inline Any FilloutPmPlayerListWithNames(Any p0, Any p1, Any p2, Any p3) { return FiveXInvoke<Any>(0xB8DF604E, p0, p1, p2, p3); } // 0xB8DF604E
inline Any UsingNetworkWeapontype(Any p0) { return FiveXInvoke<Any>(0xF49C1533, p0); } // 0xF49C1533
inline Any NetworkIsInParty() { return FiveXInvoke<Any>(0xF9D7D67D); } // 0xF9D7D67D
inline Any NetworkIsPartyMember(Any p0) { return FiveXInvoke<Any>(0x1D0C929D, p0); } // 0x1D0C929D
inline Any NetworkPlayerIsCheater() { return FiveXInvoke<Any>(0xA51DC214); } // 0xA51DC214
inline VOID NetworkSetThisScriptIsNetworkScript(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x470810ED, p0, p1, p2); } // 0x470810ED
inline Any NetworkGetThisScriptIsNetworkScript() { return FiveXInvoke<Any>(0xD9BF6549); } // 0xD9BF6549
inline Any NetworkGetScriptStatus() { return FiveXInvoke<Any>(0x2BE9235A); } // 0x2BE9235A
inline VOID NetworkRegisterHostBroadcastVariables(Any p0, Any p1) { FiveXInvoke<VOID>(0xDAF3B0AE, p0, p1); } // 0xDAF3B0AE
inline VOID NetworkRegisterPlayerBroadcastVariables(Any p0, Any p1) { FiveXInvoke<VOID>(0xBE3D32B4, p0, p1); } // 0xBE3D32B4
inline Any NetworkGetPlayerIndex(Ped PedHandle) { return FiveXInvoke<Any>(0xBE1C1506, PedHandle); } // 0xBE1C1506
inline Any NetworkGetParticipantIndex(Any p0) { return FiveXInvoke<Any>(0xC4D91094, p0); } // 0xC4D91094
inline INT NetworkGetNumConnectedPlayers() { return FiveXInvoke<int>(0xF7952E62); } // 0xF7952E62
inline Any NetworkIsPlayerConnected(Any p0) { return FiveXInvoke<Any>(0x168EE2C2, p0); } // 0x168EE2C2
inline Any NetworkIsParticipantActive(Any p0) { return FiveXInvoke<Any>(0x4E2C348B, p0); } // 0x4E2C348B
inline Any NetworkIsPlayerActive(Any p0) { return FiveXInvoke<Any>(0x43657B17, p0); } // 0x43657B17
inline Any NetworkIsPlayerAParticipant(Any p0) { return FiveXInvoke<Any>(0xB08B6992, p0); } // 0xB08B6992
inline BOOL NetworkIsHostOfThisScript() { return FiveXInvoke<Any>(0x6970BA94); } // 0x6970BA94
inline Any NetworkGetHostOfThisScript() { return FiveXInvoke<Any>(0x89EA7B54); } // 0x89EA7B54
inline Any NetworkGetHostOfScript(char* p0, INT p1, Any p2) { return FiveXInvoke<Any>(0x9C95D0BB, p0, p1, p2); } // 0x9C95D0BB
inline VOID NetworkSetMissionFinished() { FiveXInvoke<VOID>(0x3083FAD7); } // 0x3083FAD7
inline Any NetworkIsScriptActive(Any p0, Any p1, Any p2, Any p3) { return FiveXInvoke<Any>(0x4A65250C, p0, p1, p2, p3); } // 0x4A65250C
inline Any ParticipantId() { return FiveXInvoke<Any>(0x9C35A221); } // 0x9C35A221
inline Any ParticipantIdToInt() { return FiveXInvoke<Any>(0x907498B0); } // 0x907498B0
inline Any NetworkGetDestroyerOfNetworkId(Any p0, Any p1) { return FiveXInvoke<Any>(0x4FCA6436, p0, p1); } // 0x4FCA6436
inline Any NetworkGetEntityKillerOfPlayer(Any p0, Any p1) { return FiveXInvoke<Any>(0xA7E7E04F, p0, p1); } // 0xA7E7E04F
inline VOID NetworkResurrectLocalPlayer(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { FiveXInvoke<VOID>(0xF1F9D4B4, p0, p1, p2, p3, p4, p5); } // 0xF1F9D4B4
inline VOID NetworkSetLocalPlayerInvincibleTime(Any p0) { FiveXInvoke<VOID>(0xFEA9B85C, p0); } // 0xFEA9B85C
inline Any NetworkIsLocalPlayerInvincible() { return FiveXInvoke<Any>(0x8DE13B36); } // 0x8DE13B36
inline Any NetworkGetNetworkIdFromEntity(Any p0) { return FiveXInvoke<Any>(0x9E35DAB6, p0); } // 0x9E35DAB6
inline Any NetworkGetEntityFromNetworkId(Any p0) { return FiveXInvoke<Any>(0x5B912C3F, p0); } // 0x5B912C3F
inline Any NetworkGetEntityIsLocal(Any p0) { return FiveXInvoke<Any>(0x813353ED, p0); } // 0x813353ED
inline Any NetworkDoesNetworkIdExist(Any p0) { return FiveXInvoke<Any>(0xB8D2C99E, p0); } // 0xB8D2C99E
inline Any NetworkDoesEntityExistWithNetworkId(Any p0) { return FiveXInvoke<Any>(0x1E2E3177, p0); } // 0x1E2E3177
inline Any NetworkRequestControlOfNetworkId(INT netID) { return FiveXInvoke<Any>(0x9262A60A, netID); } // 0x9262A60A
inline Any NetworkHasControlOfNetworkId(Entity entity) { return FiveXInvoke<Any>(0x92E77D21, entity); } // 0x92E77D21
inline Any NetworkRequestControlOfDoor(Any p0) { return FiveXInvoke<Any>(0xF60DAAF6, p0); } // 0xF60DAAF6
inline Any NetworkHasControlOfPickup(Any p0) { return FiveXInvoke<Any>(0xF7784FC8, p0); } // 0xF7784FC8
inline Any NetworkHasControlOfDoor(Any p0) { return FiveXInvoke<Any>(0x136326EC, p0); } // 0x136326EC
inline Any VehToNet(Vehicle vehicle) { return FiveXInvoke<Any>(0xF17634EB, vehicle); } // 0xF17634EB
inline Any PedToNet(Ped ped) { return FiveXInvoke<Any>(0x86A0B759, ped); } // 0x86A0B759
inline Any ObjToNet(Object object) { return FiveXInvoke<Any>(0x1E05F29F, object); } // 0x1E05F29F
inline Any NetToVeh(Any p0) { return FiveXInvoke<Any>(0x7E02FAEA, p0); } // 0x7E02FAEA
inline Ped NetToPed(INT p0) { return FiveXInvoke<Ped>(0x87717DD4, p0); } // 0x87717DD4
inline Any NetToObj(Any p0) { return FiveXInvoke<Any>(0x27AA14D8, p0); } // 0x27AA14D8
inline Any NetToEnt(Any p0) { return FiveXInvoke<Any>(0x5E149683, p0); } // 0x5E149683
inline VOID NetworkGetLocalHandle(Any p0, Any p1) { FiveXInvoke<VOID>(0x08023B16, p0, p1); } // 0x08023B16
inline VOID NetworkHandleFromUserId(char* userId, PINT networkHandle, INT bufferSize) { FiveXInvoke<VOID>(0x74C2C1B7, userId, networkHandle, bufferSize); } // 0x74C2C1B7
inline VOID NetworkHandleFromMemberId(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x9BFC9FE2, p0, p1, p2); } // 0x9BFC9FE2
inline VOID NetworkHandleFromPlayer(Ped PedHandle, PINT FreeMemPoINTer, INT p2) { FiveXInvoke<VOID>(0xD3498917, PedHandle, FreeMemPoINTer, p2); } // 0xD3498917
inline VOID NetworkHandleFromFriend(Player p0, INT* p1, INT p2) { FiveXInvoke<VOID>(0x3B0BB3A3, p0, p1, p2); } // 0x3B0BB3A3
inline Any NetworkGamertagFromHandleStart(Any p0) { return FiveXInvoke<Any>(0xEBA00C2A, p0); } // 0xEBA00C2A
inline Any NetworkGamertagFromHandlePending() { return FiveXInvoke<Any>(0xF000828E); } // 0xF000828E
inline Any NetworkGamertagFromHandleSucceeded() { return FiveXInvoke<Any>(0x89C2B5EA); } // 0x89C2B5EA
inline char* NetworkGetGamertagFromHandle(PINT p0) { return FiveXInvoke<char*>(0xA18A1B26, p0); } // 0xA18A1B26
inline Any NetworkAreHandlesTheSame(Any p0, Any p1) { return FiveXInvoke<Any>(0x45975AE3, p0, p1); } // 0x45975AE3
inline BOOL NetworkIsHandleValid(PINT p0, INT p1) { return FiveXInvoke<BOOL>(0xF0996C6E, p0, p1); } // 0xF0996C6E
inline Any NetworkGetPlayerFromGamerHandle(Any p0) { return FiveXInvoke<Any>(0x2E96EF1E, p0); } // 0x2E96EF1E
inline Any NetworkMemberIdFromGamerHandle(Any p0) { return FiveXInvoke<Any>(0x62EF0A63, p0); } // 0x62EF0A63
inline Any NetworkIsGamerInMySession(INT* p0) { return FiveXInvoke<Any>(0x59127716, p0); } // 0x59127716
inline VOID NetworkShowProfileUi(PINT p0) { FiveXInvoke<VOID>(0xF00A20B0, p0); } // 0xF00A20B0
inline Any NetworkGetGameRegion() { return FiveXInvoke<Any>(0xEE4D173E); } // 0xEE4D173E
inline Any NetworkPlayerGetName(Any p0) { return FiveXInvoke<Any>(0xCE48F260, p0); } // 0xCE48F260
inline BOOL NetworkPlayerIsRockstarDev(Player player) { return FiveXInvoke<BOOL>(0xF6659045, player); } // 0xF6659045
inline Any NetworkIsInactiveProfile(Any p0) { return FiveXInvoke<Any>(0x95481343, p0); } // 0x95481343
inline Any NetworkGetMaxFriends() { return FiveXInvoke<Any>(0x048171BC); } // 0x048171BC
inline INT NetworkGetFriendCount() { return FiveXInvoke<INT>(0xA396ACDE); } // 0xA396ACDE
inline char* NetworkGetFriendName(INT p0) { return FiveXInvoke<char*>(0x97420B6D, p0); } // 0x97420B6D
inline Any NetworkIsFriendOnline(Any p0) { return FiveXInvoke<Any>(0xE0A42430, p0); } // 0xE0A42430
inline Any NetworkIsFriendInSameTitle(char* p0) { return FiveXInvoke<Any>(0xC54365C2, p0); } // 0xC54365C2
inline Any NetworkIsFriendInMultiplayer(char* p0) { return FiveXInvoke<Any>(0x400BDDD9, p0); } // 0x400BDDD9
inline BOOL NetworkIsFriend(INT* networkHandle) { return FiveXInvoke<BOOL>(0x2DA4C282, networkHandle); } // 0x2DA4C282
inline Any NetworkIsPendingFriend(Any p0) { return FiveXInvoke<Any>(0x5C85FF81, p0); } // 0x5C85FF81
inline Any NetworkIsAddingFriend() { return FiveXInvoke<Any>(0xBB7EC8C4); } // 0xBB7EC8C4
inline Any NetworkAddFriend(INT* networkHandle, char* message) { return FiveXInvoke<Any>(0x20E5B3EE, networkHandle, message); } // 0x20E5B3EE
inline Any ClearPlayerBailedFromPlayericle(Any p0) { return FiveXInvoke<Any>(0x94AE7172, p0); } // 0x94AE7172
inline Any GetObjEntity(Any p0) { return FiveXInvoke<Any>(0xB802B671, p0); } // 0xB802B671
inline Any NetworkCanSetWaypoint() { return FiveXInvoke<Any>(0x009E68F3); } // 0x009E68F3
inline Any NetworkHasHeadset() { return FiveXInvoke<Any>(0xA7DC5657); } // 0xA7DC5657
inline Any VehicleNetAttachCharToCharPhysically() { return FiveXInvoke<Any>(0xAC00A5BE); } // 0xAC00A5BE
inline Any NetworkGamerHasHeadset(Any p0) { return FiveXInvoke<Any>(0xD036DA4A, p0); } // 0xD036DA4A
inline Any NetworkIsGamerTalking(Any p0) { return FiveXInvoke<Any>(0x99B58DBC, p0); } // 0x99B58DBC
inline Any NetworkCanCommunicateWithGamer(Any p0) { return FiveXInvoke<Any>(0xD05EB7F6, p0); } // 0xD05EB7F6
inline Any NetworkIsGamerMutedByMe(Any p0) { return FiveXInvoke<Any>(0x001B4046, p0); } // 0x001B4046
inline BOOL NetworkIsPlayerTalking(Player player) { return FiveXInvoke<Any>(0xDA9FD9DB, player); } // 0xDA9FD9DB
inline Any NetworkPlayerHasHeadset(Any p0) { return FiveXInvoke<Any>(0x451FB6B6, p0); } // 0x451FB6B6
inline Any NetworkIsPlayerMutedByMe(Any p0) { return FiveXInvoke<Any>(0x7A21050E, p0); } // 0x7A21050E
inline Any NetworkAmIMutedByPlayer(Any p0) { return FiveXInvoke<Any>(0xE128F2B0, p0); } // 0xE128F2B0
inline Any NetworkIsPlayerBlockedByMe(Any p0) { return FiveXInvoke<Any>(0xAE4F4560, p0); } // 0xAE4F4560
inline Any NetworkAmIBlockedByPlayer(Any p0) { return FiveXInvoke<Any>(0x953EF45E, p0); } // 0x953EF45E
inline Any NetworkGetPlayerLoudness(Any p0) { return FiveXInvoke<Any>(0xF2F67014, p0); } // 0xF2F67014
inline VOID NetworkSetTalkerProximity(Any p0) { FiveXInvoke<VOID>(0x67555C66, p0); } // 0x67555C66
inline Any NetworkGetTalkerProximity() { return FiveXInvoke<Any>(0x19991ADD); } // 0x19991ADD
inline VOID NetworkSetVoiceActive(Any p0) { FiveXInvoke<VOID>(0x8011247F, p0); } // 0x8011247F
inline VOID NetworkSetTeamOnlyChat(Any p0) { FiveXInvoke<VOID>(0x3813019A, p0); } // 0x3813019A
inline VOID NetworkSetOverrideSpectatorMode(Any p0) { FiveXInvoke<VOID>(0xA0FD42D3, p0); } // 0xA0FD42D3
inline VOID NetworkSetVoiceChannel(Any p0) { FiveXInvoke<VOID>(0x3974879F, p0); } // 0x3974879F
inline VOID IsNetworkVehicleBeenDamagedByAnyObject(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xF1E84832, p0, p1, p2); } // 0xF1E84832
inline VOID ShutdownAndLaunchSinglePlayerGame() { FiveXInvoke<VOID>(0x92B7351C); } // 0x92B7351C
inline VOID NetworkSetFriendlyFireOption(Any p0) { FiveXInvoke<VOID>(0x6BAF95FA, p0); } // 0x6BAF95FA
inline VOID NetworkSetRichPresence(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x932A6CED, p0, p1, p2, p3); } // 0x932A6CED
inline Any NetworkClanPlayerIsActive(Any p0) { return FiveXInvoke<Any>(0xAB8319A3, p0); } // 0xAB8319A3
inline Any NetworkClanPlayerGetDesc(Any p0, Any p1, Any p2) { return FiveXInvoke<Any>(0x6EE4A282, p0, p1, p2); } // 0x6EE4A282
inline Any NetworkClanDownloadMembership(Any p0) { return FiveXInvoke<Any>(0x8E8CB520, p0); } // 0x8E8CB520
inline Any NetworkClanDownloadMembershipPending(Any p0) { return FiveXInvoke<Any>(0x1FDB590F, p0); } // 0x1FDB590F
inline Any NetworkClanGetMembershipCount(Any p0) { return FiveXInvoke<Any>(0x25924010, p0); } // 0x25924010
inline Any NetworkClanGetMembershipValid(Any p0, Any p1) { return FiveXInvoke<Any>(0x48914F6A, p0, p1); } // 0x48914F6A
inline Any NetworkClanGetMembership(Any p0, Any p1, Any p2) { return FiveXInvoke<Any>(0xCDC4A590, p0, p1, p2); } // 0xCDC4A590
inline Any NetworkClanJoin(Any p0) { return FiveXInvoke<Any>(0x79C916C5, p0); } // 0x79C916C5
inline VOID SetNetworkIdCanMigrate(Any p0, Any p1) { FiveXInvoke<VOID>(0x47C8E5FF, p0, p1); } // 0x47C8E5FF
inline VOID SetNetworkIdExistsOnAllMachines(INT NetID, BOOL DoesExist) { FiveXInvoke<VOID>(0x68D486B2, NetID, DoesExist); } // 0x68D486B2
inline VOID NetworkSetEntityCanBlend(Any p0, Any p1) { FiveXInvoke<VOID>(0xDE8C0DB8, p0, p1); } // 0xDE8C0DB8
inline VOID SetNetworkIdVisibleInCutscene(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x199E75EF, p0, p1, p2); } // 0x199E75EF
inline VOID SetLocalPlayerVisibleInCutscene(Any p0, Any p1) { FiveXInvoke<VOID>(0x59F3479B, p0, p1); } // 0x59F3479B
inline VOID SetLocalPlayerInvisibleLocally(Any p0) { FiveXInvoke<VOID>(0x764F6222, p0); } // 0x764F6222
inline VOID SetLocalPlayerVisibleLocally(Any p0) { FiveXInvoke<VOID>(0x324B56DB, p0); } // 0x324B56DB
inline VOID SetPlayerInvisibleLocally(Any p0, Any p1) { FiveXInvoke<VOID>(0x18227209, p0, p1); } // 0x18227209
inline VOID SetPlayerVisibleLocally(Any p0, Any p1) { FiveXInvoke<VOID>(0xBA2BB4B4, p0, p1); } // 0xBA2BB4B4
inline VOID FadeOutLocalPlayer(Any p0) { FiveXInvoke<VOID>(0x8FA7CEBD, p0); } // 0x8FA7CEBD
inline VOID NetworkFadeOutEntity(Entity entity, BOOL normal, BOOL slow) { FiveXInvoke<VOID>(0x47EDEE56, entity, normal, slow); } // 0x47EDEE56
inline VOID NetworkFadeInEntity(Entity entity, BOOL state) { FiveXInvoke<VOID>(0x9B9FCD02, entity, state); } // 0x9B9FCD02
inline BOOL IsPlayerInCutscene(Any p0) { return FiveXInvoke<BOOL>(0xE0A619BD, p0); } // 0xE0A619BD
inline VOID SetEntityVisibleInCutscene(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xDBFB067B, p0, p1, p2); } // 0xDBFB067B
inline VOID SetEntityLocallyInvisible(Any p0) { FiveXInvoke<VOID>(0x51ADCC5F, p0); } // 0x51ADCC5F
inline VOID SetEntityLocallyVisible(Any p0) { FiveXInvoke<VOID>(0x235A57B3, p0); } // 0x235A57B3
inline BOOL IsDamageTrackerActiveOnNetworkId(Any p0) { return FiveXInvoke<BOOL>(0x597063BA, p0); } // 0x597063BA
inline VOID ActivateDamageTrackerOnNetworkId(Any p0, Any p1) { FiveXInvoke<VOID>(0x95D07BA5, p0, p1); } // 0x95D07BA5
inline BOOL IsSphereVisibleToAnotherMachine(Any p0, Any p1, Any p2, Any p3) { return FiveXInvoke<BOOL>(0x23C5274E, p0, p1, p2, p3); } // 0x23C5274E
inline BOOL IsSphereVisibleToPlayer(Any p0, Any p1, Any p2, Any p3, Any p4) { return FiveXInvoke<BOOL>(0xE9FCFB32, p0, p1, p2, p3, p4); } // 0xE9FCFB32
inline VOID ReserveNetworkMissionObjects(Any p0) { FiveXInvoke<VOID>(0x391DF4F3, p0); } // 0x391DF4F3
inline VOID ReserveNetworkMissionPeds(Any p0) { FiveXInvoke<VOID>(0x54998C37, p0); } // 0x54998C37
inline VOID ReserveNetworkMissionVehicles(Any p0) { FiveXInvoke<VOID>(0x5062875E, p0); } // 0x5062875E
inline BOOL CanRegisterMissionObjects(Any p0) { return FiveXInvoke<BOOL>(0x7F85DFDE, p0); } // 0x7F85DFDE
inline BOOL CanRegisterMissionPeds(Any p0) { return FiveXInvoke<BOOL>(0xCCAA5CE9, p0); } // 0xCCAA5CE9
inline BOOL CanRegisterMissionVehicles(Any p0) { return FiveXInvoke<BOOL>(0x818B6830, p0); } // 0x818B6830
inline BOOL CanRegisterMissionEntities(Any p0, Any p1, Any p2, Any p3) { return FiveXInvoke<BOOL>(0x83794008, p0, p1, p2, p3); } // 0x83794008
inline Any GetNumReservedMissionObjects(Any p0) { return FiveXInvoke<Any>(0x16A80CD6, p0); } // 0x16A80CD6
inline Any GetNumReservedMissionPeds(Any p0) { return FiveXInvoke<Any>(0x6C25975C, p0); } // 0x6C25975C
inline Any GetNumReservedMissionVehicles(Any p0) { return FiveXInvoke<Any>(0xA9A308F3, p0); } // 0xA9A308F3
inline Any GetNetworkTime() { return FiveXInvoke<Any>(0x998103C2); } // 0x998103C2
inline Any GetTimeOffset(Any p0, Any p1) { return FiveXInvoke<Any>(0x2E079AE6, p0, p1); } // 0x2E079AE6
inline Any GetTimeDifference(Any p0, Any p1) { return FiveXInvoke<Any>(0x5666A837, p0, p1); } // 0x5666A837
inline VOID NetworkSetInSpectatorMode(Any p0, Any p1) { FiveXInvoke<VOID>(0x5C4C8458, p0, p1); } // 0x5C4C8458
inline Any NetworkIsInSpectatorMode() { return FiveXInvoke<Any>(0x3EAD9DB8); } // 0x3EAD9DB8
inline VOID NetworkSetInMpCutscene(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x8434CB43, p0, p1, p2); } // 0x8434CB43
inline Any NetworkIsInMpCutscene() { return FiveXInvoke<Any>(0x4BB33316); } // 0x4BB33316
inline Any NetworkIsPlayerInMpCutscene(Any p0) { return FiveXInvoke<Any>(0x56F961E4, p0); } // 0x56F961E4
inline VOID SetNetworkVehicleRespotTimer(Any p0, Any p1) { FiveXInvoke<VOID>(0x2C30912D, p0, p1); } // 0x2C30912D
inline VOID UsePlayerColourInsteadOfTeamColour(Any p0) { FiveXInvoke<VOID>(0x4DD46DAE, p0); } // 0x4DD46DAE
inline INT NetworkCreateSynchronisedScene(FLOAT x, FLOAT y, FLOAT z, FLOAT xRot, FLOAT yRot, FLOAT zRot, INT p6, INT p7, INT p8, FLOAT p9, FLOAT p10, FLOAT p11) { return FiveXInvoke<int>(0xB06FE3FE, x, y, z, xRot, yRot, zRot, p6, p7, p8, p9, p10, p11); } // 0x4NTR4000
inline VOID NetworkAddPedToSynchronisedScene(Ped ped, INT netScene, char* animDictionary, char* animationName, FLOAT speed, FLOAT speedMultiplier, INT duration, INT flag, FLOAT playbackRate, INT p10, INT p11) { FiveXInvoke<VOID>(0xB386713E, ped, netScene, animDictionary, animationName, speed, speedMultiplier, duration, flag, playbackRate, p10, p11); } // 0xB386713E
inline VOID NetworkAddEntityToSynchronisedScene(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { FiveXInvoke<VOID>(0x10DD636C, p0, p1, p2, p3, p4, p5, p6); } // 0x10DD636C
inline VOID NetworkAttachSynchronisedSceneToEntity(Any netScene, Any entity, Any bone) { FiveXInvoke<VOID>(0x3FE5B222, netScene, entity, bone); } // 0x3FE5B222
inline VOID NetworkStartSynchronisedScene(Any p0) { FiveXInvoke<VOID>(0xA9DFDC40, p0); } // 0xA9DFDC40
inline VOID NetworkStopSynchronisedScene(Any p0) { FiveXInvoke<VOID>(0x97B1CDF6, p0); } // 0x97B1CDF6
inline VOID NetworkGetRespawnResult(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xDDFE9FBC, p0, p1, p2); } // 0xDDFE9FBC
inline VOID NetworkEndTutorialSession() { FiveXInvoke<VOID>(0xBA57E53E); } // 0xBA57E53E
inline Any NetworkIsInTutorialSession() { return FiveXInvoke<Any>(0x34DD7B28); } // 0x34DD7B28
inline VOID NetworkOverrideClockTime(INT Hours, INT Minutes, INT Seconds) { FiveXInvoke<VOID>(0xC077BCD6, Hours, Minutes, Seconds); } // 0xC077BCD6
inline Any NetworkAddEntityArea(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return FiveXInvoke<Any>(0x51030E5B, p0, p1, p2, p3, p4, p5); } // 0x51030E5B
inline Any NetworkRemoveEntityArea(Any p0) { return FiveXInvoke<Any>(0xEAB97F25, p0); } // 0xEAB97F25
inline Any NetworkDoesTunableExist(Any p0, Any p1) { return FiveXInvoke<Any>(0x9FCE9C9A, p0, p1); } // 0x9FCE9C9A
inline VOID NetworkResetBodyTracker() { FiveXInvoke<VOID>(0x3914463F); } // 0x3914463F
inline Any NetworkExplodeVehicle(Any p0, Any p1, Any p2, Any p3) { return FiveXInvoke<Any>(0x0E1B38AE, p0, p1, p2, p3); } // 0x0E1B38AE
inline VOID NetworkSetPropertyId(Any p0) { FiveXInvoke<VOID>(0x5A74E873, p0); } // 0x5A74E873
inline VOID SetStoreEnabled(Any p0) { FiveXInvoke<VOID>(0xC1F6443B, p0); } // 0xC1F6443B
inline Any SetBalanceAddMachine(Any p0, Any p1) { return FiveXInvoke<Any>(0xE123C7AC, p0, p1); } // 0xE123C7AC
inline Any SetBalanceAddMachines(Any p0, Any p1, Any p2) { return FiveXInvoke<Any>(0x22C33603, p0, p1, p2); } // 0x22C33603
inline Any TextureDownloadRequest(Any p0, Any p1, Any p2, Any p3) { return FiveXInvoke<Any>(0xAD546CC3, p0, p1, p2, p3); } // 0xAD546CC3
inline VOID TextureDownloadRelease(Any p0) { FiveXInvoke<VOID>(0xEE8D9E70, p0); } // 0xEE8D9E70
inline Any TextureDownloadGetName(Any p0) { return FiveXInvoke<Any>(0xA40EF65A, p0); } // 0xA40EF65A
inline VOID NetworkEarnFromRockstar2(INT p0) { FiveXInvoke<VOID>(0x5A3733CC, p0); } // 0x5A3733CC
inline Any NetworkCheckReceivePlayerCash(Any p0, Any p1, Any p2, Any p3, Any p4) { return FiveXInvoke<Any>(0xD6B69D67, p0, p1, p2, p3, p4); } // 0xD6B69D67
inline VOID NetworkGivePlayerJobshareCash(Any p0, Any p1) { FiveXInvoke<VOID>(0xC6047FDB, p0, p1); } // 0xC6047FDB
inline VOID NetworkReceivePlayerJobshareCash(Any p0, Any p1) { FiveXInvoke<VOID>(0x4ED71C1A, p0, p1); } // 0x4ED71C1A
inline VOID NetworkEarnFromBounty(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x127F2DAE, p0, p1, p2, p3); } // 0x127F2DAE
inline VOID NetworkBuyItem(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { FiveXInvoke<VOID>(0xA07B6368, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xA07B6368
inline VOID NetworkSpentBuyWantedlevel(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0xE7CB4F95, p0, p1, p2, p3); } // 0xE7CB4F95
inline VOID NetworkSpentPayVehicleInsurancePremium(INT amount, Hash vehicleModel, INT* networkHandle, BOOL notBankrupt, BOOL hasTheMoney) { FiveXInvoke<VOID>(0x4E665BB2, amount, vehicleModel, networkHandle, notBankrupt, hasTheMoney); } // 0x4E665BB2
inline VOID NetworkSpentCallPlayer(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x1A89B5FC, p0, p1, p2, p3); } // 0x1A89B5FC
inline VOID NetworkSpentBounty(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x3401FC96, p0, p1, p2); } // 0x3401FC96
inline VOID NetworkDeleteCharacter(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xA9F7E9C3, p0, p1, p2); } // 0xA9F7E9C3
inline VOID NetworkEarnFromPickup(INT amount) { FiveXInvoke<VOID>(0x70A0ED62, amount); } // 0x70A0ED62
inline VOID NetworkEarnFromBetting(Any p0, Any p1) { FiveXInvoke<VOID>(0xA0F7F07C, p0, p1); } // 0xA0F7F07C
inline VOID NetworkEarnFromJob(INT amount, CHAR* p1) { FiveXInvoke<VOID>(0x0B6997FC, amount, p1); } // 0x0B6997FC
inline VOID NetworkEarnFromHoldups(Any p0) { FiveXInvoke<VOID>(0xE6B90E9C, p0); } // 0xE6B90E9C
inline VOID NetworkEarnFromProperty(Any p0, Any p1) { FiveXInvoke<VOID>(0x9BE4F7E1, p0, p1); } // 0x9BE4F7E1
inline VOID NetworkEarnFromRockstar(INT p0) { FiveXInvoke<VOID>(0x5A3733CC, p0); } // 0x5A3733CC
inline VOID NetworkEarnFromVehicle(Any p0, Any p1) { FiveXInvoke<VOID>(0xF803589D, p0, p1); } // 0xF803589D
inline VOID NetworkSpentTaxi(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x1F3DB3E3, p0, p1, p2); } // 0x1F3DB3E3
inline VOID NetworkSpentBetting(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0xF8A07513, p0, p1, p2, p3, p4); } // 0xF8A07513
inline VOID NetworkBuyHealthcare(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x832150E5, p0, p1, p2); } // 0x832150E5
inline VOID NetworkBuyAirstrike(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x40470683, p0, p1, p2); } // 0x40470683
inline VOID NetworkSpentAmmoDrop(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x4B643076, p0, p1, p2); } // 0x4B643076
inline VOID NetworkBuyBounty(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0xCB89CBE0, p0, p1, p2, p3); } // 0xCB89CBE0
inline VOID NetworkBuyProperty(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x7D479AAB, p0, p1, p2, p3); } // 0x7D479AAB
inline VOID NetworkSpentHeliPickup(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x27EEBCAB, p0, p1, p2); } // 0x27EEBCAB
inline VOID NetworkSpentBoatPickup(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xB241CABD, p0, p1, p2); } // 0xB241CABD
inline VOID NetworkSpentCashDrop(Any p0, BOOL p1, BOOL p2) { FiveXInvoke<VOID>(0x87BD1D11, p0, p1, p2); } // 0x87BD1D11
inline VOID NetworkSpentCarwash(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0x8283E028, p0, p1, p2, p3, p4); } // 0x8283E028
inline VOID NetworkSpentCinema(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x1100CAF5, p0, p1, p2, p3); } // 0x1100CAF5
inline VOID NetworkSpentTelescope(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xAE7FF044, p0, p1, p2); } // 0xAE7FF044
inline VOID NetworkSpentHoldups(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x1B3803B1, p0, p1, p2); } // 0x1B3803B1
inline Any NetworkCanReceivePlayerCash(Any p0, Any p1, Any p2, Any p3) { return FiveXInvoke<Any>(0x41F5F10E, p0, p1, p2, p3); } // 0x41F5F10E
inline INT NetworkGetVcBankBalance() { return FiveXInvoke<INT>(0x16184FB5); } // 0x16184FB5
inline INT CrateObjectPandora(INT ModelHash, FLOAT X, FLOAT Y, FLOAT Z) { return FiveXInvoke<int>(0x2F7AA05C, ModelHash, X, Y, Z); }
inline Any CreateObject3(Hash ObjectHash, FLOAT XCoord, FLOAT YCoord, FLOAT ZCoord, INT p4, BOOL p5, BOOL dynamic) { return FiveXInvoke<Any>(0x2F7AA05C, ObjectHash, XCoord, YCoord, ZCoord, p4, p5, dynamic); } // 0x2F7AA05C
inline Pickup CreateAmbientPickup(Hash AmbientHash, FLOAT XCoord, FLOAT YCoord, FLOAT ZCoord, INT p4, INT amount, INT modelHash, BOOL p7, BOOL p8) { return FiveXInvoke<Pickup>(0x17B99CE7, AmbientHash, XCoord, YCoord, ZCoord, p4, amount, modelHash, p7, p8); } // 0x17B99CE7
inline Any CreateObject(Hash ObjectHash, FLOAT XCoord, FLOAT YCoord, FLOAT ZCoord, INT p4, BOOL p5, BOOL dynamic) { return FiveXInvoke<Any>(0x2F7AA05C, ObjectHash, XCoord, YCoord, ZCoord, p4, p5, dynamic); } // 0x2F7AA05C
inline INT CreateObject2(INT* ObjectHash, FLOAT XCoord, FLOAT YCoord, FLOAT ZCoord, INT p4, BOOL p5, BOOL dynamic) { return FiveXInvoke<int>(0x2F7AA05C, ObjectHash, XCoord, YCoord, ZCoord, p4, p5, dynamic); } // 0x2F7AA05C
inline Any CreateObjectNoOffset(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return FiveXInvoke<Any>(0x58040420, p0, p1, p2, p3, p4, p5, p6); } // 0x58040420
inline VOID DeleteObject(Object* Object) { FiveXInvoke<VOID>(0xD6EF9DA7, Object); } // 0xD6EF9DA7
inline Any PlaceObjectOnGroundProperly(Object Object) { return FiveXInvoke<Any>(0x8F95A20B, Object); } // 0x8F95A20B
inline Any SlideObject(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return FiveXInvoke<Any>(0x63BFA7A0, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x63BFA7A0
inline VOID SetObjectTargettable(Object object, BOOL targettable) { FiveXInvoke<VOID>(0x3F88CD86, object, targettable); } // 0x3F88CD86
inline Object GetClosestObjectOfType(FLOAT x, FLOAT y, FLOAT z, FLOAT p3, Hash type, BOOL p5, BOOL p6, BOOL p7) { return FiveXInvoke<Object>(0x45619B33, x, y, z, p3, type, p5, p6, p7); } // 0x45619B33
inline BOOL HasObjectBeenBroken(Any p0) { return FiveXInvoke<BOOL>(0xFE21F891, p0); } // 0xFE21F891
inline BOOL HasClosestObjectOfTypeBeenBroken(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return FiveXInvoke<BOOL>(0x6FC0353D, p0, p1, p2, p3, p4, p5); } // 0x6FC0353D
inline VOID SetStateOfClosestDoorOfType(Hash type, FLOAT x, FLOAT y, FLOAT z, BOOL locked, FLOAT heading, BOOL p6) { FiveXInvoke<VOID>(0x38C951A4, type, x, y, z, locked, heading, p6); } // 0x38C951A4
inline VOID GetStateOfClosestDoorOfType(Hash type, FLOAT x, FLOAT y, FLOAT z, BOOL locked, FLOAT* heading) { FiveXInvoke<VOID>(0x4B44A83D, type, x, y, z, locked, heading); } // 0x4B44A83D
inline VOID AddDoorToSystem(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { FiveXInvoke<VOID>(0x9D2D778D, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x9D2D778D
inline VOID RemoveDoorFromSystem(Object door) { FiveXInvoke<VOID>(0x00253286, door); } // 0x00253286
inline BOOL IsDoorClosed(Object door) { return FiveXInvoke<BOOL>(0x48659CD7, door); } // 0x48659CD7
inline BOOL IsGarageEmpty(Any p0, Any p1, Any p2) { return FiveXInvoke<BOOL>(0xA8B37DEA, p0, p1, p2); } // 0xA8B37DEA
inline BOOL DoesObjectOfTypeExistAtCoords(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return FiveXInvoke<BOOL>(0x23FF2BA4, p0, p1, p2, p3, p4, p5); } // 0x23FF2BA4
inline BOOL IsPointInAngledArea(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { return FiveXInvoke<BOOL>(0x73BCFFDC, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0x73BCFFDC
inline VOID SetObjectPhysicsParams(Object object, float weight, float p2, float p3, float p4, float p5, float gravity, float p7, float p8, float p9, float p10, float buoyancy) { FiveXInvoke<VOID>(0xE8D11C58, object, weight, p2, p3, p4, p5, gravity, p7, p8, p9, p10, buoyancy); } // 0xE8D11C58
inline Any GetObjectFragmentDamageHealth(Any p0, Any p1) { return FiveXInvoke<Any>(0xF0B330AD, p0, p1); } // 0xF0B330AD
inline VOID SetActivateObjectPhysicsAsSoonAsItIsUnfrozen(Any p0, Any p1) { FiveXInvoke<VOID>(0x3E263AE1, p0, p1); } // 0x3E263AE1
inline BOOL IsAnyObjectNearPoint(Any p0, Any p1, Any p2, Any p3, Any p4) { return FiveXInvoke<BOOL>(0xE9E46941, p0, p1, p2, p3, p4); } // 0xE9E46941
inline BOOL IsObjectNearPoint(Hash objectHash, float x, float y, float z, float range) { return FiveXInvoke<BOOL>(0x50A62C43, objectHash, x, y, z, range); } // 0x50A62C43
inline VOID TrackObjectVisibility(Any p0) { FiveXInvoke<VOID>(0x46D06B9A, p0); } // 0x46D06B9A
inline BOOL IsObjectVisible(Any p0) { return FiveXInvoke<BOOL>(0xF4FD8AE4, p0); } // 0xF4FD8AE4
inline Any CreatePickup(Hash typeHash, FLOAT posX, FLOAT posY, FLOAT posZ, INT p4, INT amount, BOOL p6, Hash customModelHash) { return FiveXInvoke<Any>(0x5E14DF68, typeHash, posX, posY, posZ, p4, amount, p6, customModelHash); } // 0x5E14DF68
inline Any CreatePickupRotate(Hash typeHash, FLOAT posX, FLOAT posY, FLOAT posZ, FLOAT rotX, FLOAT rotY, FLOAT rotZ, INT p7, INT amount, Any p9, Any p10, Hash customModelHash) { return FiveXInvoke<Any>(0xF015BFE2, typeHash, posX, posY, posZ, rotX, rotY, rotZ, p7, amount, p9, p10, customModelHash); } // 0xF015BFE2
inline Any CreateAmbientPickup2(Hash AmbientHash, FLOAT* XCoord, FLOAT* YCoord, FLOAT* ZCoord, INT p4, INT amount, INT modelHash, BOOL p7, BOOL p8) { return FiveXInvoke<Any>(0x17B99CE7, AmbientHash, XCoord, YCoord, ZCoord, p4, amount, modelHash, p7, p8); } // 0x17B99CE7
inline VOID CreateAmbientPickup3(INT Hash, FLOAT x, FLOAT y, FLOAT z, INT r4, INT value, INT modelHash, INT r8, INT r9) { FiveXInvoke<VOID>(0x17B99CE7, Hash, x, y, z, r4, value, modelHash, r8, r9); } // 0x8C886BE5
inline VOID CreatePortablePickup(INT Hash, FLOAT x, FLOAT y, FLOAT z, INT r4, INT value, INT modelHash, INT r8, INT r9) { FiveXInvoke<VOID>(0x8C886BE5, Hash, x, y, z, r4, value, modelHash, r8, r9); } // 0x8C886BE5
inline VOID AttachPortablePickupToPed(Any p0, Any p1) { FiveXInvoke<VOID>(0x184F6AB3, p0, p1); } // 0x184F6AB3
inline VOID DetachPortablePickupFromPed(Any p0) { FiveXInvoke<VOID>(0x1D094562, p0); } // 0x1D094562
inline Vector3 GetSafePickupCoords(Any X, Any Y, Any Z, Any p3, Any p4) { return FiveXInvoke<Vector3>(0x618B5F67, X, Y, Z, p3, p4); } // 0x618B5F67
inline Vector3 GetPickupCoords(Any p0) { return FiveXInvoke<Vector3>(0xC2E1E2C5, p0); } // 0xC2E1E2C5
inline VOID RemoveAllPickupsOfType(Any p0) { FiveXInvoke<VOID>(0x40062C53, p0); } // 0x40062C53
inline BOOL HasPickupBeenCollected(Any p0) { return FiveXInvoke<BOOL>(0x0BE5CCED, p0); } // 0x0BE5CCED
inline VOID RemovePickup(Any p0) { FiveXInvoke<VOID>(0x64A7A0E0, p0); } // 0x64A7A0E0
inline VOID CreateMoneyPickups(FLOAT* XCoord, FLOAT* YCoord, FLOAT* ZCoord, INT Vaule, Any p4, Any p5) { FiveXInvoke<VOID>(0x36C9A5EA, XCoord, YCoord, ZCoord, Vaule, p4, p5); } // 0x36C9A5EA
inline BOOL DoesPickupExist(Any p0) { return FiveXInvoke<BOOL>(0x9C6DA0B3, p0); } // 0x9C6DA0B3
inline BOOL DoesPickupObjectExist(Any p0) { return FiveXInvoke<BOOL>(0xE0B32108, p0); } // 0xE0B32108
inline VOID SetPickupRegenerationTime(Any p0, Any p1) { FiveXInvoke<VOID>(0xAB11267D, p0, p1); } // 0xAB11267D
inline VOID SetTeamPickupObject(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x77687DC5, p0, p1, p2); } // 0x77687DC5
inline VOID SetForceObjectThisFrame(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x3DA41C1A, p0, p1, p2, p3); } // 0x3DA41C1A
inline Ped CreatePed(INT type, Hash pedHash, FLOAT x, FLOAT y, FLOAT z, FLOAT heading, BOOL isNetwork, BOOL scriptHostPed) { return FiveXInvoke<Ped>(0x0389EF71, type, pedHash, x, y, z, heading, isNetwork, scriptHostPed); } // 0x0389EF71
inline VOID DeletePed(Ped* ped) { FiveXInvoke<VOID>(0x13EFB9A0, ped); } // 0x13EFB9A0
inline Ped ClonePed(Ped Priest, FLOAT Heading, BOOL networkhandle, BOOL createpedhandle) { return FiveXInvoke<Ped>(0x8C8A8D6E, Priest, Heading, networkhandle, createpedhandle); } // 0x8C8A8D6E
inline BOOL IsPedInVehicle(Ped pedHandle, Vehicle vehicleHandle, BOOL atGetIn) { return FiveXInvoke<BOOL>(0x7DA6BC83, pedHandle, vehicleHandle, atGetIn); } // 0x7DA6BC83
inline BOOL IsPedInModel(Ped ped, Hash vehicleModel) { return FiveXInvoke<BOOL>(0xA6438D4B, ped, vehicleModel); } // 0xA6438D4B
inline BOOL IsPedInAnyVehicle(Ped pedHandle, BOOL atGetIn) { return FiveXInvoke<BOOL>(0x3B0171EE, pedHandle, atGetIn); } // 0x3B0171EE
inline BOOL IsCopPedInArea3d(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return FiveXInvoke<BOOL>(0xB98DB96B, p0, p1, p2, p3, p4, p5); } // 0xB98DB96B
inline BOOL IsPedInjured(Ped ped) { return FiveXInvoke<BOOL>(0x2530A087, ped); } // 0x2530A087
inline BOOL IsPedHurt(Any p0) { return FiveXInvoke<BOOL>(0x69DFA0AF, p0); } // 0x69DFA0AF
inline BOOL IsPedFatallyInjured(Ped ped) { return FiveXInvoke<BOOL>(0xBADA0093, ped); } // 0xBADA0093
inline BOOL IsPedDead(Ped pedHandle, BOOL p1) { return FiveXInvoke<BOOL>(0xCBDB7739, pedHandle, p1); } // 0xCBDB7739
inline BOOL IsConversationPedDead(Any p0) { return FiveXInvoke<BOOL>(0x1FA39EFE, p0); } // 0x1FA39EFE
inline BOOL IsPedAimingFromCover(Player* p0) { return FiveXInvoke<BOOL>(0xDEBAB2AF, p0); } // 0xDEBAB2AF
inline BOOL IsPedReloading(Ped ped) { return FiveXInvoke<BOOL>(0x961E1745, ped); } // 0x961E1745
inline BOOL IsPedAPlayer(Ped ped) { return FiveXInvoke<BOOL>(0x404794CA, ped); } // 0x404794CA
inline Any CreatePedInsideVehicle(Vehicle vehicle, INT pedType, Hash modelHash, INT seat, Any p4, Any p5) { return FiveXInvoke<Any>(0x3000F092, vehicle, pedType, modelHash, seat, p4, p5); } // 0x3000F092
inline VOID SetPedDesiredHeading(Any p0, Any p1) { FiveXInvoke<VOID>(0x961458F9, p0, p1); } // 0x961458F9
inline BOOL IsPedFacingPed(Any p0, Any p1, Any p2) { return FiveXInvoke<BOOL>(0x0B775838, p0, p1, p2); } // 0x0B775838
inline BOOL IsPedInMeleeCombat(Ped ped) { return FiveXInvoke<BOOL>(0xFD7814A5, ped); } // 0xFD7814A5
inline BOOL IsPedStopped(Ped ped) { return FiveXInvoke<BOOL>(0xA0DC0B87, ped); } // 0xA0DC0B87
inline BOOL IsPedShootingInArea(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return FiveXInvoke<BOOL>(0x741BF04F, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x741BF04F
inline BOOL IsAnyPedShootingInArea(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return FiveXInvoke<BOOL>(0x91833867, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x91833867
inline BOOL IsPedShooting(Ped ped) { return FiveXInvoke<BOOL>(0xE7C3405E, ped); } // 0xE7C3405E
inline VOID SetPedAccuracy(Ped ped, INT accuracy) { FiveXInvoke<VOID>(0x6C17122E, ped, accuracy); } // 0x6C17122E
inline INT GetPedAccuracy(Ped p0) { return FiveXInvoke<INT>(0x0A2A0AA0, p0); } // 0x0A2A0AA0
inline BOOL IsPedModel(Ped pedHandle, Hash modelHash) { return FiveXInvoke<BOOL>(0x5F1DDFCB, pedHandle, modelHash); } // 0x5F1DDFCB
inline VOID ExplodePedHead(Ped ped, Hash WeaponHash) { FiveXInvoke<VOID>(0x05CC1380, ped, WeaponHash); } // 0x05CC1380
inline VOID RemovePedElegantly(Ped PedHandle) { FiveXInvoke<VOID>(0x4FFB8C6C, PedHandle); } // 0x4FFB8C6C
inline VOID AddArmourToPed(Ped PedHandle, INT Amount) { FiveXInvoke<VOID>(0xF686B26E, PedHandle, Amount); } // 0xF686B26E
inline VOID SetPedArmour(Ped ped, int amount) { FiveXInvoke<VOID>(0x4E3A0CC4, ped, amount); } // 0x4E3A0CC4
inline VOID SetPedIntoVehicle(Ped PedHandle, Vehicle VehicleHandle, INT SeatIndex) { FiveXInvoke<VOID>(0x07500C79, PedHandle, VehicleHandle, SeatIndex); } // 0x07500C79
inline BOOL CanCreateRandomPed(Any p0) { return FiveXInvoke<BOOL>(0xF9ABE88F, p0); } // 0xF9ABE88F
inline Ped CreateRandomPed(FLOAT X, FLOAT Y, FLOAT Z) { return FiveXInvoke<Ped>(0x5A949543, X, Y, Z); } // 0x5A949543
inline Ped CreateRandomPedAsDriver(Vehicle vehicleHandle, BOOL p1) { return FiveXInvoke<Ped>(0xB927CE9A, vehicleHandle, p1); } // 0xB927CE9A
inline BOOL CanCreateRandomDriver() { return FiveXInvoke<BOOL>(0x99861609); } // 0x99861609
inline VOID SetPedMoveAnimsBlendOut(Any p0) { FiveXInvoke<VOID>(0x20E01957, p0); } // 0x20E01957
inline VOID SetPedCanBeDraggedOut(Any p0, Any p1) { FiveXInvoke<VOID>(0xAA7F1131, p0, p1); } // 0xAA7F1131
inline BOOL IsPedMale(Any p0) { return FiveXInvoke<BOOL>(0x90950455, p0); } // 0x90950455
inline BOOL IsPedHuman(Any p0) { return FiveXInvoke<BOOL>(0x194BB7B0, p0); } // 0x194BB7B0
inline Vehicle GetVehiclePedIsIn(Ped pedHandle, BOOL getLastVehicle) { return FiveXInvoke<Vehicle>(0xAFE92319, pedHandle, getLastVehicle); } // 0xAFE92319
inline VOID ResetPedLastVehicle(Any p0) { FiveXInvoke<VOID>(0x5E3B5942, p0); } // 0x5E3B5942
inline VOID SetPedDensityMultiplierThisFrame(FLOAT multiplier) { FiveXInvoke<VOID>(0x039C82BB, multiplier); } // 0x039C82BB
inline VOID SetScenarioPedDensityMultiplierThisFrame(FLOAT interior, FLOAT exterior) { FiveXInvoke<VOID>(0x2909ABF0, interior, exterior); } // 0x2909ABF0
inline VOID SetPedNonCreationArea(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { FiveXInvoke<VOID>(0x7A97283F, p0, p1, p2, p3, p4, p5); } // 0x7A97283F
inline VOID ClearPedNonCreationArea() { FiveXInvoke<VOID>(0x6F7043A3); } // 0x6F7043A3
inline BOOL IsPedOnMount(Any p0) { return FiveXInvoke<BOOL>(0x43103006, p0); } // 0x43103006
inline Any GetMount(Any p0) { return FiveXInvoke<Any>(0xDD31EC4E, p0); } // 0xDD31EC4E
inline BOOL IsPedOnVehicle(Any p0) { return FiveXInvoke<BOOL>(0xA1AE7CC7, p0); } // 0xA1AE7CC7
inline BOOL IsPedOnSpecificVehicle(Ped ped, Vehicle specificVehicle) { return FiveXInvoke<BOOL>(0x63CB4603, ped, specificVehicle); } // 0x63CB4603
inline VOID SetPedMoney(Ped pedHandle, INT amount) { FiveXInvoke<VOID>(0x40D90BF2, pedHandle, amount); } // 0x40D90BF2
inline Any GetPedMoney(Ped pedHandle) { return FiveXInvoke<Any>(0xEB3C4C7E, pedHandle); } // 0xEB3C4C7E
inline VOID SetPedSuffersCriticalHits(Any p0, Any p1) { FiveXInvoke<VOID>(0x6F6FC7E6, p0, p1); } // 0x6F6FC7E6
inline BOOL IsPedSittingInVehicle(Any p0, Any p1) { return FiveXInvoke<BOOL>(0xDDDE26FA, p0, p1); } // 0xDDDE26FA
inline BOOL IsPedSittingInAnyVehicle(Ped Ped) { return FiveXInvoke<BOOL>(0x0EA9CA03, Ped); } // 0x0EA9CA03
inline BOOL IsPedOnFoot(Ped Ped) { return FiveXInvoke<BOOL>(0xC60D0785, Ped); } // 0xC60D0785
inline BOOL IsPedOnAnyBike(Any p0) { return FiveXInvoke<BOOL>(0x4D885B2E, p0); } // 0x4D885B2E
inline BOOL IsPedPlantingBomb(Any p0) { return FiveXInvoke<BOOL>(0x0EDAC574, p0); } // 0x0EDAC574
inline Vector3 GetDeadPedPickupCoords(Any p0, Any p1, Any p2) { return FiveXInvoke<Vector3>(0x129F9DC1, p0, p1, p2); } // 0x129F9DC1
inline BOOL IsPedInAnyBoat(Any p0) { return FiveXInvoke<BOOL>(0x1118A947, p0); } // 0x1118A947
inline BOOL IsPedInAnySub(Any p0) { return FiveXInvoke<BOOL>(0xE65F8059, p0); } // 0xE65F8059
inline BOOL IsPedInAnyHeli(Any p0) { return FiveXInvoke<BOOL>(0x7AB5523B, p0); } // 0x7AB5523B
inline BOOL IsPedInAnyPlane(Any p0) { return FiveXInvoke<BOOL>(0x51BBCE7E, p0); } // 0x51BBCE7E
inline BOOL IsPedInFlyingVehicle(Any p0) { return FiveXInvoke<BOOL>(0xCA072485, p0); } // 0xCA072485
inline VOID SetPedDiesInWater(Any p0, Any p1) { FiveXInvoke<VOID>(0x604C872B, p0, p1); } // 0x604C872B
inline VOID SetPedDiesInSinkingVehicle(Any p0, Any p1) { FiveXInvoke<VOID>(0x8D4D9ABB, p0, p1); } // 0x8D4D9ABB
inline INT GetPedArmour(Ped PedHandle) { return FiveXInvoke<INT>(0x2CE311A7, PedHandle); } // 0x2CE311A7
inline VOID SetPedStayInVehicleWhenJacked(Any p0, Any p1) { FiveXInvoke<VOID>(0xB014A09C, p0, p1); } // 0xB014A09C
inline VOID SetPedCanBeShotInVehicle(Any p0, Any p1) { FiveXInvoke<VOID>(0x5DB7B3A9, p0, p1); } // 0x5DB7B3A9
inline Any GetPedLastDamageBone(Any p0, Any p1) { return FiveXInvoke<Any>(0xAB933841, p0, p1); } // 0xAB933841
inline VOID ClearPedLastDamageBone(Any p0) { FiveXInvoke<VOID>(0x56CB715E, p0); } // 0x56CB715E
inline VOID SetAiWeaponDamageModifier(Any p0) { FiveXInvoke<VOID>(0x516E30EE, p0); } // 0x516E30EE
inline VOID ResetAiWeaponDamageModifier() { FiveXInvoke<VOID>(0x6E965420); } // 0x6E965420
inline VOID SetPedCanBeTargetted(Any p0, Any p1) { FiveXInvoke<VOID>(0x75C49F74, p0, p1); } // 0x75C49F74
inline VOID SetPedCanBeTargettedByTeam(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xB103A8E1, p0, p1, p2); } // 0xB103A8E1
inline VOID SetPedCanBeTargettedByPlayer(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xD050F490, p0, p1, p2); } // 0xD050F490
inline VOID SetTimeExclusiveDisplayTexture(Any p0, Any p1) { FiveXInvoke<VOID>(0x7F67671D, p0, p1); } // 0x7F67671D
inline BOOL IsPedInAnyPoliceVehicle(Any p0) { return FiveXInvoke<BOOL>(0x84FA790D, p0); } // 0x84FA790D
inline BOOL IsPedFalling(Ped PedHandle) { return FiveXInvoke<BOOL>(0xABF77334, PedHandle); } // 0xABF77334
inline BOOL IsPedJumping(Ped Ped) { return FiveXInvoke<BOOL>(0x07E5BC0E, Ped); } // 0x07E5BC0E
inline BOOL IsPedClimbing(Ped Ped) { return FiveXInvoke<BOOL>(0xBCE03D35, Ped); } // 0xBCE03D35
inline BOOL IsPedDiving(Any p0) { return FiveXInvoke<BOOL>(0x7BC5BF3C, p0); } // 0x7BC5BF3C
inline Any GetPedParachuteState(Any p0) { return FiveXInvoke<Any>(0x7D4BC475, p0); } // 0x7D4BC475
inline VOID SetPedParachuteTintIndex(Any p0, Any p1) { FiveXInvoke<VOID>(0x5AEFEC3A, p0, p1); } // 0x5AEFEC3A
inline VOID GetPedParachuteTintIndex(Any p0, Any p1) { FiveXInvoke<VOID>(0xE9E7FAC5, p0, p1); } // 0xE9E7FAC5
inline VOID SetPedDucking(Any p0, Any p1) { FiveXInvoke<VOID>(0xB90353D7, p0, p1); } // 0xB90353D7
inline BOOL IsPedDucking(Any p0) { return FiveXInvoke<BOOL>(0x9199C77D, p0); } // 0x9199C77D
inline BOOL IsPedInAnyTaxi(Any p0) { return FiveXInvoke<BOOL>(0x16FD386C, p0); } // 0x16FD386C
inline VOID SetPedIdRange(Any p0, Any p1) { FiveXInvoke<VOID>(0xEF3B4ED9, p0, p1); } // 0xEF3B4ED9
inline VOID SetPedSeeingRange(Any p0, Any p1) { FiveXInvoke<VOID>(0x4BD72FE8, p0, p1); } // 0x4BD72FE8
inline VOID SetPedHearingRange(Any p0, Any p1) { FiveXInvoke<VOID>(0xB32087E0, p0, p1); } // 0xB32087E0
inline VOID SetPedVisualFieldMinAngle(Any p0, Any p1) { FiveXInvoke<VOID>(0x72E2E18B, p0, p1); } // 0x72E2E18B
inline VOID SetPedVisualFieldMaxAngle(Any p0, Any p1) { FiveXInvoke<VOID>(0x0CEA0F9A, p0, p1); } // 0x0CEA0F9A
inline VOID SetPedVisualFieldMinElevationAngle(Any p0, Any p1) { FiveXInvoke<VOID>(0x5CC2F1B8, p0, p1); } // 0x5CC2F1B8
inline VOID SetPedVisualFieldMaxElevationAngle(Any p0, Any p1) { FiveXInvoke<VOID>(0x39D9102F, p0, p1); } // 0x39D9102F
inline VOID SetPedStealthMovement(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x67E28E1D, p0, p1, p2); } // 0x67E28E1D
inline Any GetPedStealthMovement(Any p0) { return FiveXInvoke<Any>(0x40321B83, p0); } // 0x40321B83
inline Any CreateGroup(INT Zombies) { return FiveXInvoke<Any>(0x8DC0368D, Zombies); } // 0x8DC0368D
inline VOID SetPedAsGroupLeader(Ped PedHandle, INT Zombies) { FiveXInvoke<VOID>(0x7265BEA2, PedHandle, Zombies); } // 0x7265BEA2
inline VOID SetPedAsGroupMember(Ped PedHandle, INT groupId) { FiveXInvoke<VOID>(0x0EE13F92, PedHandle, groupId); } // 0x0EE13F92
inline VOID RemoveGroup(INT Group) { FiveXInvoke<VOID>(0x48D72B88, Group); } // 0x48D72B88
inline VOID RemovePedFromGroup(Ped PedHandle) { FiveXInvoke<VOID>(0x82697713, PedHandle); } // 0x82697713
inline BOOL IsPedGroupMember(Ped PedHandle, INT Group) { return FiveXInvoke<BOOL>(0x876D5363, PedHandle, Group); } // 0x876D5363
inline VOID SetGroupSeparationRange(Any p0, Any p1) { FiveXInvoke<VOID>(0x7B820CD5, p0, p1); } // 0x7B820CD5
inline BOOL IsPedProne(Any p0) { return FiveXInvoke<BOOL>(0x02C2A6C3, p0); } // 0x02C2A6C3
inline BOOL IsPedInCombat(Any p0, Any p1) { return FiveXInvoke<BOOL>(0xFE027CB5, p0, p1); } // 0xFE027CB5
inline BOOL IsPedDoingDriveby(Any p0) { return FiveXInvoke<BOOL>(0xAC3CEB9C, p0); } // 0xAC3CEB9C
inline BOOL IsPedJacking(Any p0) { return FiveXInvoke<BOOL>(0x3B321816, p0); } // 0x3B321816
inline BOOL IsPedBeingJacked(Any p0) { return FiveXInvoke<BOOL>(0xD45D605C, p0); } // 0xD45D605C
inline BOOL IsPedBeingStunned(Any p0, Any p1) { return FiveXInvoke<BOOL>(0x0A66CE30, p0, p1); } // 0x0A66CE30
inline Any GetPedsJacker(Any p0) { return FiveXInvoke<Any>(0xDE1DBB59, p0); } // 0xDE1DBB59
inline Any GetJackTarget(Any p0) { return FiveXInvoke<Any>(0x1D196361, p0); } // 0x1D196361
inline BOOL IsPedFleeing(Any p0) { return FiveXInvoke<BOOL>(0x85D813C6, p0); } // 0x85D813C6
inline BOOL IsPedInCover(Any p0, Any p1) { return FiveXInvoke<BOOL>(0x972C5A8B, p0, p1); } // 0x972C5A8B
inline BOOL IsPedInCoverFacingLeft(Any p0) { return FiveXInvoke<BOOL>(0xB89DBB80, p0); } // 0xB89DBB80
inline BOOL IsPedGoingIntoCover(Any p0) { return FiveXInvoke<BOOL>(0xA3589628, p0); } // 0xA3589628
inline Any SetPedPinnedDown(Any p0, Any p1, Any p2) { return FiveXInvoke<Any>(0xCC78999D, p0, p1, p2); } // 0xCC78999D
inline Any GetPedCauseOfDeath(Any p0) { return FiveXInvoke<Any>(0x63458C27, p0); } // 0x63458C27
inline Any GetPedTimeOfDeath(Any p0) { return FiveXInvoke<Any>(0xDF6D5D54, p0); } // 0xDF6D5D54
inline VOID SetPedRelationshipGroupDefaultHash(Any p0, Any p1) { FiveXInvoke<VOID>(0x423B7BA2, p0, p1); } // 0x423B7BA2
inline VOID SetPedRelationshipGroupHash(Ped pedHandle, Any groupHandle) { FiveXInvoke<VOID>(0x79F8C18C, pedHandle, groupHandle); } // 0x79F8C18C
inline VOID SetRelationshipBetweenGroups(INT RelationStatus, Any Group1, Any Group2) { FiveXInvoke<VOID>(0xD4A215BA, RelationStatus, Group1, Group2); } // 0xD4A215BA
inline VOID ClearRelationshipBetweenGroups(INT RelationStatus, Any Group1, Any Group2) { FiveXInvoke<VOID>(0x994B8C2D, RelationStatus, Group1, Group2); } // 0x994B8C2D
inline Any AddRelationshipGroup(char* crewName, Any p1) { return FiveXInvoke<Any>(0x8B635546, crewName, p1); } // 0x8B635546
inline VOID RemoveRelationshipGroup(Any p0) { FiveXInvoke<VOID>(0x4A1DC59A, p0); } // 0x4A1DC59A
inline INT GetRelationshipBetweenPeds(Ped ped1, Ped ped2) { return FiveXInvoke<int>(0xE254C39C, ped1, ped2); } // 0xE254C39C
inline Any GetPedRelationshipGroupDefaultHash(Any p0) { return FiveXInvoke<Any>(0x714BD6E4, p0); } // 0x714BD6E4
inline Any GetPedRelationshipGroupHash(Player playerId) { return FiveXInvoke<Any>(0x354F283C, playerId); } // 0x354F283C
inline INT GetRelationshipBetweenGroups(Any p0, Any p1) { return FiveXInvoke<int>(0x4E372FE2, p0, p1); } // 0x4E372FE2
inline VOID SetPedCanBeTargetedWithoutLos(Any p0, Any p1) { FiveXInvoke<VOID>(0x7FDDC0A6, p0, p1); } // 0x7FDDC0A6
inline VOID SetPedToInformRespectedFriends(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xD78AC46C, p0, p1, p2); } // 0xD78AC46C
inline BOOL IsPedRespondingToEvent(Any p0, Any p1) { return FiveXInvoke<BOOL>(0x7A877554, p0, p1); } // 0x7A877554
inline VOID SetPedFiringPattern(Ped ped, Hash patternHash) { FiveXInvoke<VOID>(0xB4629D66, ped, patternHash); } // 0xB4629D66
inline VOID SetPedShootRate(Ped ped, INT shootRate) { FiveXInvoke<VOID>(0xFB301746, ped, shootRate); } // 0xFB301746
inline VOID SetCombatFloat(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xD8B7637C, p0, p1, p2); } // 0xD8B7637C
inline Any GetCombatFloat(Any p0, Any p1) { return FiveXInvoke<Any>(0x511D7EF8, p0, p1); } // 0x511D7EF8
inline VOID GetGroupSize(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xF7E1A691, p0, p1, p2); } // 0xF7E1A691
inline BOOL DoesGroupExist(INT Group) { return FiveXInvoke<BOOL>(0x935C978D, Group); } // 0x935C978D
inline INT GetPedGroupIndex(Ped pedHandle) { return FiveXInvoke<int>(0x134E0785, pedHandle); } // 0x134E0785
inline BOOL IsPedInGroup(Ped pedHandle) { return FiveXInvoke<BOOL>(0x836D9795, pedHandle); } // 0x836D9795
inline VOID SetGroupFormation(INT group, INT formationType) { FiveXInvoke<VOID>(0x08FAC739, group, formationType); } // 0x08FAC739
inline VOID SetGroupFormationSpacing(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0xB1E086FF, p0, p1, p2, p3); } // 0xB1E086FF
inline Vehicle GetVehiclePedIsUsing(Ped PedHandle) { return FiveXInvoke<Vehicle>(0x6DE3AADA, PedHandle); } // 0x6DE3AADA
inline Any SetExclusivePhoneRelationships(Any p0) { return FiveXInvoke<Any>(0x56E0C163, p0); } // 0x56E0C163
inline VOID SetPedGravity(Any p0, Any p1) { FiveXInvoke<VOID>(0x3CA16652, p0, p1); } // 0x3CA16652
inline VOID ApplyDamageToPed(Ped pedHandle, Any damageAmount, BOOL p2) { FiveXInvoke<VOID>(0x4DC27FCF, pedHandle, damageAmount, p2); } // 0x4DC27FCF
inline VOID SetPedAllowedToDuck(Any p0, Any p1) { FiveXInvoke<VOID>(0xC4D122F8, p0, p1); } // 0xC4D122F8
inline VOID SetPedNeverLeavesGroup(Ped PedHandle, INT Group) { FiveXInvoke<VOID>(0x0E038813, PedHandle, Group); } // 0x0E038813
inline Any GetPedType(Ped PedHandle) { return FiveXInvoke<Any>(0xB1460D43, PedHandle); } // 0xB1460D43
inline VOID SetPedAsCop(INT PedHandle, BOOL Toggle) { FiveXInvoke<VOID>(0x84E7DE9F, PedHandle, Toggle); } // 0x84E7DE9F
inline VOID SetPedMaxHealth(Any p0, Any p1) { FiveXInvoke<VOID>(0x5533F60B, p0, p1); } // 0x5533F60B
inline Any GetPedMaxHealth(Any p0) { return FiveXInvoke<Any>(0xA45B6C8D, p0); } // 0xA45B6C8D
inline VOID SetPedMaxTimeInWater(Any p0, Any p1) { FiveXInvoke<VOID>(0xFE0A106B, p0, p1); } // 0xFE0A106B
inline VOID SetPedMaxTimeUnderwater(Any p0, Any p1) { FiveXInvoke<VOID>(0x082EF240, p0, p1); } // 0x082EF240
inline VOID SetPedCanBeKnockedOffVehicle(Ped PedHandle, INT p1) { FiveXInvoke<VOID>(0x8A251612, PedHandle, p1); } // 0x8A251612
inline VOID KnockPedOffVehicle(Ped PedHandle) { FiveXInvoke<VOID>(0xACDD0674, PedHandle); } // 0xACDD0674
inline VOID SetPedCoordsNoGang(Ped ped, FLOAT XCoord, FLOAT YCoord, FLOAT ZCoord) { FiveXInvoke<VOID>(0x9561AD98, ped, XCoord, YCoord, ZCoord); } // 0x9561AD98
inline Any GetPedAsGroupMember(Any p0, Any p1) { return FiveXInvoke<Any>(0x9AA3CC8C, p0, p1); } // 0x9AA3CC8C
inline VOID SetPedKeepTask(Ped ped, BOOL Toggle) { FiveXInvoke<VOID>(0xA7EC79CE, ped, Toggle); } // 0xA7EC79CE
inline BOOL IsPedSwimming(Any p0) { return FiveXInvoke<BOOL>(0x7AB43DB8, p0); } // 0x7AB43DB8
inline BOOL IsPedSwimmingUnderWater(Any p0) { return FiveXInvoke<BOOL>(0x0E8D524F, p0); } // 0x0E8D524F
inline VOID SetPedCoordsKeepVehicle(Ped ped, FLOAT XCoord, FLOAT YCoord, FLOAT ZCoord) { FiveXInvoke<VOID>(0xD66AE1D3, ped, XCoord, YCoord, ZCoord); } // 0xD66AE1D3
inline VOID SetPedDiesInVehicle(Any p0, Any p1) { FiveXInvoke<VOID>(0x6FE1E440, p0, p1); } // 0x6FE1E440
inline VOID SetCreateRandomCops(Any p0) { FiveXInvoke<VOID>(0x23441648, p0); } // 0x23441648
inline BOOL CanCreateRandomCops() { return FiveXInvoke<BOOL>(0xAA73DAD9); } // 0xAA73DAD9
inline VOID SetPedAsEnemy(Ped pedHandle, BOOL p1) { FiveXInvoke<VOID>(0xAE620A1B, pedHandle, p1); } // 0xAE620A1B
inline VOID SetPedCanSmashGlass(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x149C60A8, p0, p1, p2); } // 0x149C60A8
inline BOOL IsPedInAnyTrain(Any p0) { return FiveXInvoke<BOOL>(0x759EF63A, p0); } // 0x759EF63A
inline BOOL IsPedGettingIntoAVehicle(INT playerID) { return FiveXInvoke<BOOL>(0x90E805AC, playerID); } // 0x90E805AC
inline BOOL IsPedTryingToEnterALockedVehicle(Any p0) { return FiveXInvoke<BOOL>(0x46828B4E, p0); } // 0x46828B4E
inline VOID SetEnableHandcuffs(Ped PedHandle, BOOL Toggle) { FiveXInvoke<VOID>(0xAC9BBA23, PedHandle, Toggle); } // 0xAC9BBA23
inline VOID SetEnableBoundAnkles(Any p0, Any p1) { FiveXInvoke<VOID>(0x9208D689, p0, p1); } // 0x9208D689
inline VOID SetCanAttackFriendly(Player p0, Ped p1, Any p2) { FiveXInvoke<VOID>(0x47C60963, p0, p1, p2); } // 0x47C60963
inline Any GetPedAlertness(Any p0) { return FiveXInvoke<Any>(0xF83E4DAF, p0); } // 0xF83E4DAF
inline VOID SetPedAlertness(Any p0, Any p1) { FiveXInvoke<VOID>(0x2C32D9AE, p0, p1); } // 0x2C32D9AE
inline VOID SetPedGetOutUpsideDownVehicle(Any p0, Any p1) { FiveXInvoke<VOID>(0x89AD49FF, p0, p1); } // 0x89AD49FF
inline VOID SetPedMovementClipset(Ped ped, char* clipSet, FLOAT blendSet) { FiveXInvoke<VOID>(0xA817CDEB, ped, clipSet, blendSet); } // 0xA817CDEB
inline VOID ResetPedMovementClipset(Ped ped, FLOAT blendSet) { FiveXInvoke<VOID>(0xB83CEE93, ped, blendSet); } // 0xB83CEE93
inline VOID SetPedStrafeClipset(Any p0, Any p1) { FiveXInvoke<VOID>(0x0BACF010, p0, p1); } // 0x0BACF010
inline VOID ResetPedStrafeClipset(Any p0) { FiveXInvoke<VOID>(0xF1967A12, p0); } // 0xF1967A12
inline VOID SetPedWeaponMovementClipset(Any p0, Any p1) { FiveXInvoke<VOID>(0xF8BE54DC, p0, p1); } // 0xF8BE54DC
inline VOID ResetPedWeaponMovementClipset(Any p0) { FiveXInvoke<VOID>(0xC60C9ACD, p0); } // 0xC60C9ACD
inline VOID SetPedInVehicleContext(Any p0, Any p1) { FiveXInvoke<VOID>(0x27F25C0E, p0, p1); } // 0x27F25C0E
inline VOID ResetPedInVehicleContext(Any p0) { FiveXInvoke<VOID>(0x3C94D88A, p0); } // 0x3C94D88A
inline VOID SetPedAlternateMovementAnim(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { FiveXInvoke<VOID>(0xBA84FD8C, p0, p1, p2, p3, p4, p5); } // 0xBA84FD8C
inline VOID ClearPedAlternateMovementAnim(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x7A7F5BC3, p0, p1, p2); } // 0x7A7F5BC3
inline VOID SetPedGestureGroup(Any p0, Any p1) { FiveXInvoke<VOID>(0x170DA109, p0, p1); } // 0x170DA109
inline INT GetPedDrawableVariation(Ped pedID, INT componentID) { return FiveXInvoke<int>(0x29850FE2, pedID, componentID); } // 0x29850FE2
inline INT GetNumberOfPedDrawableVariations(Ped pedID, INT componentID) { return FiveXInvoke<int>(0x9754C27D, pedID, componentID); } // 0x9754C27D
inline INT GetPedTextureVariation(Ped pedID, INT componentID) { return FiveXInvoke<int>(0xC0A8590A, pedID, componentID); } // 0xC0A8590A
inline INT GetNumberOfPedTextureVariations(Ped pedID, INT componentID, INT drawableID) { return FiveXInvoke<int>(0x83D9FBE7, pedID, componentID, drawableID); } // 0x83D9FBE7
inline INT GetNumberOfPedPropDrawableVariations(Ped ped, INT propId) { return FiveXInvoke<int>(0xC9780B95, ped, propId); } // 0xC9780B95
inline Any GetNumberOfPedPropTextureVariations(Ped ped, INT propId, INT drawableId) { return FiveXInvoke<Any>(0x4892B882, ped, propId, drawableId); } // 0x4892B882
inline Any RemoveNightvisionMelee(Any p0, Any p1, Any p2) { return FiveXInvoke<Any>(0x4892B882, p0, p1, p2); } // 0x4892B882
inline INT GetPedPaletteVariation(Any p0, Any p1) { return FiveXInvoke<int>(0xEF1BC082, p0, p1); } // 0xEF1BC082
inline BOOL IsPedComponentVariationValid(Any p0, Any p1, Any p2, Any p3) { return FiveXInvoke<BOOL>(0x952ABD9A, p0, p1, p2, p3); } // 0x952ABD9A
inline VOID SetPedComponentVariation(Ped PedHandle, INT componentID, INT drawableID, INT textureID, INT paletteID) { FiveXInvoke<VOID>(0xD4F7B05C, PedHandle, componentID, drawableID, textureID, paletteID); } // 0xD4F7B05C
inline VOID SetPedRandomComponentVariation(Ped pedHandle, BOOL p1) { FiveXInvoke<VOID>(0x4111BA46, pedHandle, p1); } // 0x4111BA46
inline VOID SetPedRandomProps(Ped PedHandle) { FiveXInvoke<VOID>(0xE3318E0E, PedHandle); } // 0xE3318E0E
inline VOID SetPedDefaultComponentVariation(Ped PedHandle) { FiveXInvoke<VOID>(0xC866A984, PedHandle); } // 0xC866A984
inline VOID SetPedBlendFromParents(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0x837BD370, p0, p1, p2, p3, p4); } // 0x837BD370
inline VOID SetPedHeadBlendData(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { FiveXInvoke<VOID>(0x60746B88, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0x60746B88
inline VOID UpdatePedHeadBlendData(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x5CB76219, p0, p1, p2, p3); } // 0x5CB76219
inline VOID SetPedHeadOverlay(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0xD28DBA90, p0, p1, p2, p3); } // 0xD28DBA90
inline BOOL HasPedHeadBlendFinished(Any p0) { return FiveXInvoke<BOOL>(0x2B1BD9C5, p0); } // 0x2B1BD9C5
inline Any GetPedPropIndex(Ped PedHandle, INT ComponentID) { return FiveXInvoke<Any>(0x746DDAC0, PedHandle, ComponentID); } // 0x746DDAC0
inline VOID SetPedPropIndex(Ped PedHandle, INT ComponentID, INT drawableID, INT TextureID, INT PaletteID) { FiveXInvoke<VOID>(0x0829F2E2, PedHandle, ComponentID, drawableID, TextureID, PaletteID); } // 0x0829F2E2
inline VOID KnockOffPedProp(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0x08D8B180, p0, p1, p2, p3, p4); } // 0x08D8B180
inline VOID ClearPedProp(Ped PedHandle, INT PropID) { FiveXInvoke<VOID>(0x2D23D743, PedHandle, PropID); } // 0x2D23D743
inline VOID ClearAllPedProps(Ped PedHandle) { FiveXInvoke<VOID>(0x81DF8B43, PedHandle); } // 0x81DF8B43
inline Any GetPedPropTextureIndex(Any p0, Any p1) { return FiveXInvoke<Any>(0x922A6653, p0, p1); } // 0x922A6653
inline VOID SetBlockingOfNonTemporaryEvents(Any p0, Any p1) { FiveXInvoke<VOID>(0xDFE34E4A, p0, p1); } // 0xDFE34E4A
inline VOID SetPedBoundsOrientation(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { FiveXInvoke<VOID>(0xCFA20D68, p0, p1, p2, p3, p4, p5); } // 0xCFA20D68
inline VOID RegisterTarget(Any p0, Any p1) { FiveXInvoke<VOID>(0x50A95442, p0, p1); } // 0x50A95442
inline VOID RegisterHatedTargetsAroundPed(Ped PedHandle, FLOAT AreaToAttack) { FiveXInvoke<VOID>(0x7F87559E, PedHandle, AreaToAttack); } // 0x7F87559E
inline Ped GetRandomPedAtCoord(FLOAT x, FLOAT y, FLOAT z, FLOAT xRadius, FLOAT yRadius, FLOAT zRadius, INT p6) { return FiveXInvoke<Ped>(0xDC8239EB, x, y, z, xRadius, yRadius, zRadius, p6); } // 0xDC8239EB
inline BOOL GetClosestPed(FLOAT x, FLOAT y, FLOAT z, FLOAT radius, BOOL p4, BOOL p5, Ped* outPed, BOOL p7, BOOL p8, INT pedType) { return FiveXInvoke<BOOL>(0x8F6C1F55, x, y, z, radius, p4, p5, outPed, p7, p8, pedType); } // 0x8F6C1F55
inline Ped GetClosestPed2(FLOAT x, FLOAT y, FLOAT z, FLOAT Radius, BOOL p4, BOOL p5, PINT handle, BOOL p7, BOOL p8, INT p9) { return FiveXInvoke<Ped>(0x8F6C1F55, x, y, z, Radius, p4, p5, handle, p7, p8, p9); } // 0x8F6C1F55
inline VOID SetScenarioPedsToBeReturnedByNextCommand(Any p0) { FiveXInvoke<VOID>(0x85615FD0, p0); } // 0x85615FD0
inline VOID SetDriverAbility(Any p0, Any p1) { FiveXInvoke<VOID>(0xAAD4012C, p0, p1); } // 0xAAD4012C
inline VOID SetDriverAggressiveness(Any p0, Any p1) { FiveXInvoke<VOID>(0x8B02A8FB, p0, p1); } // 0x8B02A8FB
inline BOOL CanPedRagdoll(Ped ped) { return FiveXInvoke<BOOL>(0xC0EFB7A3, ped); } // 0xC0EFB7A3
inline Any SetPedToRagdoll(Ped ped, INT Xforce, INT Yforce, INT Zforce, BOOL p4, BOOL p5, BOOL p6) { return FiveXInvoke<Any>(0x83CB5052, ped, Xforce, Yforce, Zforce, p4, p5, p6); } // 0x83CB5052
inline Any SetPedToRagdollWithFall(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13) { return FiveXInvoke<Any>(0xFA12E286, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); } // 0xFA12E286
inline VOID SetPedRagdollOnCollision(Ped PedHandle, BOOL Toggle) { FiveXInvoke<VOID>(0x2654A0F4, PedHandle, Toggle); } // 0x2654A0F4
inline BOOL IsPedRagdoll(Any p0) { return FiveXInvoke<BOOL>(0xC833BBE1, p0); } // 0xC833BBE1
inline BOOL IsPedRunningRagdollTask(Any p0) { return FiveXInvoke<BOOL>(0x44A153F2, p0); } // 0x44A153F2
inline VOID SetPedRagdollForceFall(Ped ped) { FiveXInvoke<VOID>(0x20A5BDE0, ped); } // 0x20A5BDE0
inline VOID ResetPedRagdollTimer(Any p0) { FiveXInvoke<VOID>(0xF2865370, p0); } // 0xF2865370
inline BOOL IsPedRunningMobilePhoneTask(Any p0) { return FiveXInvoke<BOOL>(0xFB2AFED1, p0); } // 0xFB2AFED1
inline VOID SetPedAngledDefensiveArea(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { FiveXInvoke<VOID>(0x3EFBDD9B, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x3EFBDD9B
inline VOID SetPedSphereDefensiveArea(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { FiveXInvoke<VOID>(0xBD96D8E8, p0, p1, p2, p3, p4, p5, p6); } // 0xBD96D8E8
inline VOID SetPedDefensiveAreaAttachedToPed(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { FiveXInvoke<VOID>(0x74BDA7CE, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0x74BDA7CE
inline VOID RemovePedDefensiveArea(Any p0, Any p1) { FiveXInvoke<VOID>(0x34AAAFA5, p0, p1); } // 0x34AAAFA5
inline Vector3 GetPedDefensiveAreaPosition(Any p0, Any p1) { return FiveXInvoke<Vector3>(0xCB65198D, p0, p1); } // 0xCB65198D
inline VOID ReviveInjuredPed(Any p0) { FiveXInvoke<VOID>(0x14D3E6E3, p0); } // 0x14D3E6E3
inline VOID ResurrectPed(Any p0) { FiveXInvoke<VOID>(0xA4B82097, p0); } // 0xA4B82097
inline VOID SetPedNameDebug(Any p0, Any p1) { FiveXInvoke<VOID>(0x20D6273E, p0, p1); } // 0x20D6273E
inline Vector3 GetPedExtractedDisplacement(Any p0, Any p1) { return FiveXInvoke<Vector3>(0x5231F901, p0, p1); } // 0x5231F901
inline VOID SetPedDiesWhenInjured(Ped ped, BOOL toggle) { FiveXInvoke<VOID>(0xE94E24D4, ped, toggle); } // 0xE94E24D4
inline VOID SetPedEnableWeaponBlocking(Ped ped, BOOL toggle) { FiveXInvoke<VOID>(0x4CAD1A4A, ped, toggle); } // 0x4CAD1A4A
inline VOID ResetPedVisibleDamage(Ped ped) { FiveXInvoke<VOID>(0xC4BC4841, ped); } // 0xC4BC4841
inline VOID ApplyPedBlood(Ped ped, INT i1, FLOAT f1, FLOAT f2, FLOAT f3, char* s1) { FiveXInvoke<VOID>(0x376CE3C0, ped, i1, f1, f2, f3, s1); } // 0x376CE3C0
inline VOID ApplyPedDamageDecal(Ped p0, INT p1, FLOAT p2, FLOAT p3, FLOAT p4, FLOAT p5, FLOAT p6, INT p7, BOOL p8, char* p9) { FiveXInvoke<VOID>(0x8A13A41F, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x8A13A41F
inline VOID ApplyPedDamagePack(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x208D0CB8, p0, p1, p2, p3); } // 0x208D0CB8
inline VOID ClearPedBloodDamage(Ped PedHandle) { FiveXInvoke<VOID>(0xF7ADC960, PedHandle); } // 0xF7ADC960
inline VOID ClearPedWetness(Ped ped) { FiveXInvoke<VOID>(0x629F15BD, ped); } // 0x629F15BD
inline VOID SetPedWetnessHeight(Ped ped, FLOAT height) { FiveXInvoke<VOID>(0x7B33289A, ped, height); } // 0x7B33289A
inline VOID SetPedWetnessEnabledThisFrame(Any p0) { FiveXInvoke<VOID>(0xBDE749F7, p0); } // 0xBDE749F7
inline VOID SetPedSweat(Ped ped, FLOAT sweat) { FiveXInvoke<VOID>(0x76A1DB9F, ped, sweat); } // 0x76A1DB9F
inline VOID SetPedDecoration(Ped ped, Hash ShirtType, Hash ShirtDecal) { FiveXInvoke<VOID>(0x70559AC7, ped, ShirtType, ShirtDecal); } // 0x70559AC7
inline VOID ClearPedDecorations(Ped PedHandle) { FiveXInvoke<VOID>(0xD4496BF3, PedHandle); } // 0xD4496BF3
inline BOOL WasPedSkeletonUpdated(Any p0) { return FiveXInvoke<BOOL>(0xF7E2FBAD, p0); } // 0xF7E2FBAD
inline Vector3 GetPedBoneCoords(Ped ped, INT i1, FLOAT f1, FLOAT f2, FLOAT f3) { return FiveXInvoke<Vector3>(0x4579CAB1, ped, i1, f1, f2, f3); } // 0x4579CAB1
inline VOID CreateNmMessage(Any p0, Any p1) { FiveXInvoke<VOID>(0x1CFBFD4B, p0, p1); } // 0x1CFBFD4B
inline VOID GivePedNmMessage(Any p0) { FiveXInvoke<VOID>(0x737C3689, p0); } // 0x737C3689
inline Any AddScenarioBlockingArea(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return FiveXInvoke<Any>(0xA38C0234, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xA38C0234
inline VOID RemoveScenarioBlockingAreas() { FiveXInvoke<VOID>(0x4DDF845F); } // 0x4DDF845F
inline VOID RemoveScenarioBlockingArea(Any p0, Any p1) { FiveXInvoke<VOID>(0x4483EF06, p0, p1); } // 0x4483EF06
inline VOID SetScenarioPedsSpawnInSphereArea(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0x80EAD297, p0, p1, p2, p3, p4); } // 0x80EAD297
inline BOOL IsPedUsingScenario(Any p0, Any p1) { return FiveXInvoke<BOOL>(0x0F65B0D4, p0, p1); } // 0x0F65B0D4
inline BOOL IsPedUsingAnyScenario(Any p0) { return FiveXInvoke<BOOL>(0x195EF5B7, p0); } // 0x195EF5B7
inline VOID PlayFacialAnim(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x1F6CCDDE, p0, p1, p2); } // 0x1F6CCDDE
inline VOID SetFacialIdleAnimOverride(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x9BA19C13, p0, p1, p2); } // 0x9BA19C13
inline VOID ClearFacialIdleAnimOverride(Any p0) { FiveXInvoke<VOID>(0x5244F4E2, p0); } // 0x5244F4E2
inline VOID SetPedCanPlayGestureAnims(Any p0, Any p1) { FiveXInvoke<VOID>(0xE131E3B3, p0, p1); } // 0xE131E3B3
inline VOID SetPedCanPlayVisemeAnims(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xA2FDAF27, p0, p1, p2); } // 0xA2FDAF27
inline VOID SetPedCanPlayAmbientAnims(Any p0, Any p1) { FiveXInvoke<VOID>(0xF8053081, p0, p1); } // 0xF8053081
inline VOID SetPedCanPlayAmbientBaseAnims(Any p0, Any p1) { FiveXInvoke<VOID>(0x5720A5DD, p0, p1); } // 0x5720A5DD
inline VOID SetPedCanHeadIk(Any p0, Any p1) { FiveXInvoke<VOID>(0xD3B04476, p0, p1); } // 0xD3B04476
inline VOID SetPedCanLegIk(Any p0, Any p1) { FiveXInvoke<VOID>(0x9955BC6F, p0, p1); } // 0x9955BC6F
inline VOID SetPedCanUseAutoConversationLookat(Any p0, Any p1) { FiveXInvoke<VOID>(0x584C5178, p0, p1); } // 0x584C5178
inline BOOL IsPedHeadtrackingPed(Any p0, Any p1) { return FiveXInvoke<BOOL>(0x2A5DF721, p0, p1); } // 0x2A5DF721
inline BOOL IsPedHeadtrackingEntity(Any p0, Any p1) { return FiveXInvoke<BOOL>(0x233C9ACF, p0, p1); } // 0x233C9ACF
inline VOID SetPedPrimaryLookat(Any p0, Any p1) { FiveXInvoke<VOID>(0x6DEF6F1C, p0, p1); } // 0x6DEF6F1C
inline VOID SetPedConfigFlag(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x9CFBE10D, p0, p1, p2); } // 0x9CFBE10D
inline VOID SetPedResetFlag(Ped ped, int flagId, BOOL doReset) { FiveXInvoke<VOID>(0xCFF6FF66, ped, flagId, doReset); } // 0xCFF6FF66
inline Any GetPedConfigFlag(Any p0, Any p1, Any p2) { return FiveXInvoke<Any>(0xABE98267, p0, p1, p2); } // 0xABE98267
inline Any GetPedResetFlag(Any p0, Any p1) { return FiveXInvoke<Any>(0x2FC10D11, p0, p1); } // 0x2FC10D11
inline VOID SetPedGroupMemberPassengerIndex(Any p0, Any p1) { FiveXInvoke<VOID>(0x2AB3670B, p0, p1); } // 0x2AB3670B
inline VOID SetPedCanEvasiveDive(Any p0, Any p1) { FiveXInvoke<VOID>(0x542FEB4D, p0, p1); } // 0x542FEB4D
inline BOOL IsPedEvasiveDiving(Any p0, Any p1) { return FiveXInvoke<BOOL>(0xD82829DC, p0, p1); } // 0xD82829DC
inline VOID SetPedShootsAtCoord(Ped ped, FLOAT x, FLOAT y, FLOAT z, BOOL toggle) { FiveXInvoke<VOID>(0xFD64EAE5, ped, x, y, z, toggle); } // 0xFD64EAE5
inline VOID SetPedModelIsSuppressed(Any p0, Any p1) { FiveXInvoke<VOID>(0x7820CA43, p0, p1); } // 0x7820CA43
inline VOID StopAnyPedModelBeingSuppressed() { FiveXInvoke<VOID>(0x5AD7DC55); } // 0x5AD7DC55
inline VOID SetPedCanBeTargetedWhenInjured(Any p0, Any p1) { FiveXInvoke<VOID>(0x6FD9A7CD, p0, p1); } // 0x6FD9A7CD
inline VOID SetPedGeneratesDeadBodyEvents(Ped ped, BOOL Toggle) { FiveXInvoke<VOID>(0xE9B97A2B, ped, Toggle); } // 0xE9B97A2B
inline VOID SetPedCanRagdollFromPlayerImpact(Any p0, Any p1) { FiveXInvoke<VOID>(0xE9BD733A, p0, p1); } // 0xE9BD733A
inline VOID GivePedHelmet(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x1862A461, p0, p1, p2, p3); } // 0x1862A461
inline VOID RemovePedHelmet(Any p0, Any p1) { FiveXInvoke<VOID>(0x2086B1F0, p0, p1); } // 0x2086B1F0
inline VOID SetPedHelmet(Any p0, Any p1) { FiveXInvoke<VOID>(0xED366E53, p0, p1); } // 0xED366E53
inline VOID SetPedHelmetFlag(Any p0, Any p1) { FiveXInvoke<VOID>(0x12677780, p0, p1); } // 0x12677780
inline VOID SetPedHelmetPropIndex(Any p0, Any p1) { FiveXInvoke<VOID>(0xA316D13F, p0, p1); } // 0xA316D13F
inline VOID SetPedHelmetTextureIndex(Any p0, Any p1) { FiveXInvoke<VOID>(0x5F6C3328, p0, p1); } // 0x5F6C3328
inline BOOL IsPedWearingHelmet(Ped PedHandle) { return FiveXInvoke<BOOL>(0x0D680D49, PedHandle); } // 0x0D680D49
inline VOID SetPedToLoadCover(Any p0, Any p1) { FiveXInvoke<VOID>(0xCF94BA97, p0, p1); } // 0xCF94BA97
inline VOID SetPedCanCowerInCover(Any p0, Any p1) { FiveXInvoke<VOID>(0x5194658B, p0, p1); } // 0x5194658B
inline VOID SetPedCanPeekInCover(Ped PedHandle, BOOL Toggle) { FiveXInvoke<VOID>(0xC1DAE216, PedHandle, Toggle); } // 0xC1DAE216
inline VOID SetPedPlaysHeadOnHornAnimWhenDiesInVehicle(Any p0, Any p1) { FiveXInvoke<VOID>(0x7C563CD2, p0, p1); } // 0x7C563CD2
inline VOID SetPedLegIkMode(Any p0, Any p1) { FiveXInvoke<VOID>(0xFDDB042E, p0, p1); } // 0xFDDB042E
inline VOID SetPedMotionBlur(Any p0, Any p1) { FiveXInvoke<VOID>(0xA211A128, p0, p1); } // 0xA211A128
inline VOID SetPedCanSwitchWeapon(INT PedID, BOOL CAN_SWITCH) { FiveXInvoke<VOID>(0xB5F8BA28, PedID, CAN_SWITCH); } // 0xB5F8BA28
inline VOID SetPedDiesInstantlyInWater(Ped PedHandle, BOOL Toggle) { FiveXInvoke<VOID>(0xFE2554FC, PedHandle, Toggle); } // 0xFE2554FC
inline VOID StopPedWeaponFiringWhenDropped(Any p0) { FiveXInvoke<VOID>(0x4AC3421E, p0); } // 0x4AC3421E
inline VOID SetScriptedAnimSeatOffset(Any p0, Any p1) { FiveXInvoke<VOID>(0x7CEFFA45, p0, p1); } // 0x7CEFFA45
inline VOID SetPedCombatMovement(Any p0, Any p1) { FiveXInvoke<VOID>(0x12E62F9E, p0, p1); } // 0x12E62F9E
inline Any GetPedCombatMovement(Any p0) { return FiveXInvoke<Any>(0xF3E7730E, p0); } // 0xF3E7730E
inline VOID SetPedCombatAbility(Ped ped, INT p1) { FiveXInvoke<VOID>(0x6C23D329, ped, p1); } // 0x6C23D329
inline VOID SetPedCombatRange(Ped ped, FLOAT range) { FiveXInvoke<VOID>(0x8818A959, ped, range); } // 0x8818A959
inline Any GetPedCombatRange(Any p0) { return FiveXInvoke<Any>(0x9B9B7163, p0); } // 0x9B9B7163
inline VOID SetPedCombatAttributes(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x81D64248, p0, p1, p2); } // 0x81D64248
inline VOID SetPedTargetLossResponse(Any p0, Any p1) { FiveXInvoke<VOID>(0xCFA613FF, p0, p1); } // 0xCFA613FF
inline BOOL IsPedPerformingStealthKill(Any p0) { return FiveXInvoke<BOOL>(0x9ADD7B21, p0); } // 0x9ADD7B21
inline BOOL IsPedBeingStealthKilled(Any p0) { return FiveXInvoke<BOOL>(0xD044C8AF, p0); } // 0xD044C8AF
inline BOOL WasPedKilledByStealth(Any p0) { return FiveXInvoke<BOOL>(0x2EA4B54E, p0); } // 0x2EA4B54E
inline BOOL WasPedKilledByTakedown(Any p0) { return FiveXInvoke<BOOL>(0xBDD3CE69, p0); } // 0xBDD3CE69
inline VOID SetPedFleeAttributes(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xA717A875, p0, p1, p2); } // 0xA717A875
inline VOID SetPedCowerHash(Any p0, Any p1) { FiveXInvoke<VOID>(0x16F30DF4, p0, p1); } // 0x16F30DF4
inline VOID SetPedSteersAroundPeds(Ped ped, BOOL DoesSteer) { FiveXInvoke<VOID>(0x797CAE4F, ped, DoesSteer); } // 0x797CAE4F
inline VOID SetPedSteersAroundObjects(Ped ped, BOOL DoesSteer) { FiveXInvoke<VOID>(0x3BD9B0A6, ped, DoesSteer); } // 0x3BD9B0A6
inline VOID SetPedSteersAroundVehicles(Ped ped, BOOL DoesSteer) { FiveXInvoke<VOID>(0x533C0651, ped, DoesSteer); } // 0x533C0651
inline BOOL IsAnyPedNearPoint(Any p0, Any p1, Any p2, Any p3) { return FiveXInvoke<BOOL>(0xFBD9B050, p0, p1, p2, p3); } // 0xFBD9B050
inline VOID ForcePedAiAndAnimationUpdate(Ped ped, BOOL p1, BOOL p2) { FiveXInvoke<VOID>(0x187B9070, ped, p1, p2); } // 0x187B9070
inline VOID GetPedFloodInvincibility(Any p0, Any p1) { FiveXInvoke<VOID>(0x31C31DAA, p0, p1); } // 0x31C31DAA
inline BOOL IsTrackedPedVisible(Any p0) { return FiveXInvoke<BOOL>(0x33248CC1, p0); } // 0x33248CC1
inline BOOL IsPedTracked(Any p0) { return FiveXInvoke<BOOL>(0x7EB613D9, p0); } // 0x7EB613D9
inline BOOL HasPedReceivedEvent(Any p0, Any p1) { return FiveXInvoke<BOOL>(0xECD73DB0, p0, p1); } // 0xECD73DB0
inline Any GetPedBoneIndex(Ped PedHandle, INT BoneIndex) { return FiveXInvoke<Any>(0x259C6BA2, PedHandle, BoneIndex); } // 0x259C6BA2
inline Any GetPedRagdollBoneIndex(Any p0, Any p1) { return FiveXInvoke<Any>(0x849F0716, p0, p1); } // 0x849F0716
inline VOID SetPedEnveffScale(Any p0, Any p1) { FiveXInvoke<VOID>(0xFC1CFC27, p0, p1); } // 0xFC1CFC27
inline Any GetPedEnveffScale(Any p0) { return FiveXInvoke<Any>(0xA3421E39, p0); } // 0xA3421E39
inline VOID SetEnablePedEnveffScale(Any p0, Any p1) { FiveXInvoke<VOID>(0xC70F4A84, p0, p1); } // 0xC70F4A84
inline Any CreateSynchronizedScene(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return FiveXInvoke<Any>(0xFFDDF8FA, p0, p1, p2, p3, p4, p5, p6); } // 0xFFDDF8FA
inline BOOL IsSynchronizedSceneRunning(Any p0) { return FiveXInvoke<BOOL>(0x57A282F1, p0); } // 0x57A282F1
inline VOID SetSynchronizedSceneOrigin(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { FiveXInvoke<VOID>(0x2EC2A0B2, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x2EC2A0B2
inline VOID SetSynchronizedScenePhase(Any p0, Any p1) { FiveXInvoke<VOID>(0xF5AB0D98, p0, p1); } // 0xF5AB0D98
inline Any GetSynchronizedScenePhase(Any p0) { return FiveXInvoke<Any>(0xB0B2C852, p0); } // 0xB0B2C852
inline VOID SetSynchronizedSceneRate(Any p0, Any p1) { FiveXInvoke<VOID>(0xF10112FD, p0, p1); } // 0xF10112FD
inline Any GetSynchronizedSceneRate(Any p0) { return FiveXInvoke<Any>(0x89365F0D, p0); } // 0x89365F0D
inline VOID SetSynchronizedSceneLooped(Any p0, Any p1) { FiveXInvoke<VOID>(0x32ED9F82, p0, p1); } // 0x32ED9F82
inline BOOL IsSynchronizedSceneLooped(Any p0) { return FiveXInvoke<BOOL>(0x47D87A84, p0); } // 0x47D87A84
inline VOID AttachSynchronizedSceneToEntity(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xE9BA6189, p0, p1, p2); } // 0xE9BA6189
inline VOID DetachSynchronizedScene(Any p0) { FiveXInvoke<VOID>(0x52A1CAB2, p0); } // 0x52A1CAB2
inline Any ForcePedMotionState(Any p0, Any p1, Any p2, Any p3, Any p4) { return FiveXInvoke<Any>(0x164DDEFF, p0, p1, p2, p3, p4); } // 0x164DDEFF
inline VOID SetPedMaxMoveBlendRatio(Any p0, Any p1) { FiveXInvoke<VOID>(0xEAD0269A, p0, p1); } // 0xEAD0269A
inline VOID SetPedMinMoveBlendRatio(Any p0, Any p1) { FiveXInvoke<VOID>(0x383EC364, p0, p1); } // 0x383EC364
inline VOID SetPedMoveRateOverride(Any p0, FLOAT p1) { FiveXInvoke<VOID>(0x900008C6, p0, p1); } // 0x900008C6
inline INT GetPedNearbyVehicles(Ped PedHandle, PINT sizeAndVehs) { return FiveXInvoke<int>(0xCB716F68, PedHandle, sizeAndVehs); } // 0xCB716F68
inline INT GetPedNearbyPeds(Ped PedHandle, PINT PToArray, INT p2) { return FiveXInvoke<int>(0x4D3325F4, PedHandle, PToArray, p2); } // 0x4D3325F4
inline BOOL IsPedUsingActionMode(Any p0) { return FiveXInvoke<BOOL>(0x5AE7EDA2, p0); } // 0x5AE7EDA2
inline VOID SetPedUsingActionMode(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x8802F696, p0, p1, p2, p3); } // 0x8802F696
inline VOID SetPedCapsule(Any p0, Any p1) { FiveXInvoke<VOID>(0xB153E1B9, p0, p1); } // 0xB153E1B9
inline Any RegisterPedheadshot(Any p0) { return FiveXInvoke<Any>(0xFFE2667B, p0); } // 0xFFE2667B
inline VOID UnregisterPedheadshot(Any p0) { FiveXInvoke<VOID>(0x0879AE45, p0); } // 0x0879AE45
inline BOOL IsPedheadshotValid(Any p0) { return FiveXInvoke<BOOL>(0x0B1080C4, p0); } // 0x0B1080C4
inline BOOL IsPedheadshotReady(Any p0) { return FiveXInvoke<BOOL>(0x761CD02E, p0); } // 0x761CD02E
inline Any GetPedheadshotTxdString(Any p0) { return FiveXInvoke<Any>(0x76D28E96, p0); } // 0x76D28E96
inline VOID SetPedheadshotCustomLighting(Any p0) { FiveXInvoke<VOID>(0xAB688DAB, p0); } // 0xAB688DAB
inline VOID SetPedheadshotCustomLight(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { FiveXInvoke<VOID>(0xF48A9155, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xF48A9155
inline VOID SetIkTarget(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { FiveXInvoke<VOID>(0x6FE5218C, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x6FE5218C
inline VOID RequestActionModeAsset(Any p0) { FiveXInvoke<VOID>(0x572BA553, p0); } // 0x572BA553
inline BOOL HasActionModeAssetLoaded(Any p0) { return FiveXInvoke<BOOL>(0xF7EB2BF1, p0); } // 0xF7EB2BF1
inline VOID RemoveActionModeAsset(Any p0) { FiveXInvoke<VOID>(0x3F480F92, p0); } // 0x3F480F92
inline VOID RequestStealthModeAsset(Any p0) { FiveXInvoke<VOID>(0x280A004A, p0); } // 0x280A004A
inline BOOL HasStealthModeAssetLoaded(Any p0) { return FiveXInvoke<BOOL>(0x39245667, p0); } // 0x39245667
inline VOID RemoveStealthModeAsset(Any p0) { FiveXInvoke<VOID>(0x8C0B243A, p0); } // 0x8C0B243A
inline VOID SetPedLodMultiplier(Any p0, Any p1) { FiveXInvoke<VOID>(0x1D2B5C70, p0, p1); } // 0x1D2B5C70
inline VOID SetPlayerMeleeWeaponDamageModifier(Player player, FLOAT modifier) { FiveXInvoke<VOID>(0x362E69AD, player, modifier); } // 0x362E69AD
inline BOOL GetEntityPlayerIsFreeAimingAt(Player player, Entity* entity) { return FiveXInvoke<BOOL>(0x8866D9D0, player, entity); } // 0x8866D9D0
inline Ped GetPlayerPed(Player player) { return FiveXInvoke<Ped>(0x6E31E993, player); } // 0x6E31E993
inline Ped GetPlayerPedScriptIndex(Player player) { return FiveXInvoke<Ped>(0x6AC64990, player); } // 0x6AC64990
inline VOID SetPlayerModel(Player player, Hash modelHash) { FiveXInvoke<VOID>(0x774A4C54, player, modelHash); } // 0x774A4C54
inline VOID ChangePlayerPed(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0xBE515485, p0, p1, p2, p3); } // 0xBE515485
inline VOID GetPlayerRgbColour(Player player, PINT Red, PINT Green, PINT Blue) { FiveXInvoke<VOID>(0x6EF43BBB, player, Red, Green, Blue); } // 0x6EF43BBB
inline INT GetNumberOfPlayers() { return FiveXInvoke<int>(0x4C1B8867); } // 0x4C1B8867
inline INT GetPlayerTeam(Player player) { return FiveXInvoke<int>(0x9873E404, player); } // 0x9873E404
inline VOID SetPlayerTeam(Player player, INT Team) { FiveXInvoke<VOID>(0x725ADCF2, player, Team); } // 0x725ADCF2
inline char* GetPlayerName(Player player) { return FiveXInvoke<char*>(0x406B4B20, player); } // 0x406B4B20 83B13AEB
inline FLOAT GetWantedLevelRadius(Player player) { return FiveXInvoke<float>(0x1CF7D7DA, player); } // 0x1CF7D7DA
inline Vector3 GetPlayerWantedCentrePosition(Player player) { return FiveXInvoke<Vector3>(0x821F2D2C, player); } // 0x821F2D2C
inline VOID SetPlayerWantedCentrePosition(Player player, FLOAT x, FLOAT y, FLOAT z) { FiveXInvoke<VOID>(0xF261633A, player, x, y, z); } // 0xF261633A
inline INT GetWantedLevelThreshold(INT wantedLevel) { return FiveXInvoke<int>(0xD9783F6B, wantedLevel); } // 0xD9783F6B
inline VOID SetPlayerWantedLevel(Player player, Hash wantedLevel, BOOL p2) { FiveXInvoke<VOID>(0xB7A0914B, player, wantedLevel, p2); } // 0xB7A0914B
inline VOID SetPlayerWantedLevelNoDrop(Player player, BOOL wantedLevel, Any p2) { FiveXInvoke<VOID>(0xED6F44F5, player, wantedLevel, p2); } // 0xED6F44F5
inline VOID SetPlayerWantedLevelNow(Player player, BOOL p1) { FiveXInvoke<VOID>(0xAF3AFD83, player, p1); } // 0xAF3AFD83
inline BOOL ArePlayerFlashingStarsAboutToDrop(Player player) { return FiveXInvoke<BOOL>(0xE13A71C7, player); } // 0xE13A71C7
inline BOOL ArePlayerStarsGreyedOut(Player player) { return FiveXInvoke<BOOL>(0x5E72AB72, player); } // 0x5E72AB72
inline VOID SetDispatchCopsForPlayer(Player player, BOOL Enable) { FiveXInvoke<VOID>(0x48A18913, player, Enable); } // 0x48A18913
inline BOOL IsPlayerWantedLevelGreater(Player player, INT wantedLevel) { return FiveXInvoke<BOOL>(0x589A2661, player, wantedLevel); } // 0x589A2661
inline BOOL IsPlayerDead(Player player) { return FiveXInvoke<BOOL>(0x140CA5A8, player); } // 0x140CA5A8
inline BOOL IsPlayerPressingHorn(Player player) { return FiveXInvoke<BOOL>(0xED1D1662, player); } // 0xED1D1662
inline VOID SetPlayerControl(Player playerId, BOOL Toggle, INT possiblyFlags) { FiveXInvoke<VOID>(0xD17AFCD8, playerId, Toggle, possiblyFlags); } // 0xD17AFCD8
inline INT GetPlayerWantedLevel(Player player) { return FiveXInvoke<int>(0xBDCDD163, player); } // 0xBDCDD163
inline VOID SetMaxWantedLevel(INT maxWantedLevel) { FiveXInvoke<VOID>(0x665A06F5, maxWantedLevel); } // 0x665A06F5
inline VOID SetPoliceRadarBlips(BOOL Toggle) { FiveXInvoke<VOID>(0x8E114B10, Toggle); } // 0x8E114B10
inline VOID SetPoliceIgnorePlayer(Player player, BOOL Toggle) { FiveXInvoke<VOID>(0xE6DE71B7, player, Toggle); } // 0xE6DE71B7
inline VOID SetEveryoneIgnorePlayer(Player player, BOOL Toggle) { FiveXInvoke<VOID>(0xC915285E, player, Toggle); } // 0xC915285E
inline VOID SetAllRandomPedsFlee(Player player, INT p1) { FiveXInvoke<VOID>(0x49EAE968, player, p1); } // 0x49EAE968
inline VOID SetAllRandomPedsFleeThisFrame(Player player) { FiveXInvoke<VOID>(0xBF974891, player); } // 0xBF974891
inline VOID SetIgnoreLowPriorityShockingEvents(INT playerIndex, BOOL p1) { FiveXInvoke<VOID>(0xA3D675ED, playerIndex, p1); } // 0xA3D675ED
inline VOID SetWantedLevelMultiplier(FLOAT Multiplier) { FiveXInvoke<VOID>(0x1359292F, Multiplier); } // 0x1359292F
inline VOID SetWantedLevelDifficulty(Player player, FLOAT difficulty) { FiveXInvoke<VOID>(0xB552626C, player, difficulty); } // 0xB552626C
inline VOID ResetWantedLevelDifficulty(Player player) { FiveXInvoke<VOID>(0xA64C378D, player); } // 0xA64C378D
inline VOID StartFiringAmnesty(Any p0) { FiveXInvoke<VOID>(0x5F8A22A6, p0); } // 0x5F8A22A6
inline VOID ReportCrime(Player player, INT p0, INT p1) { FiveXInvoke<VOID>(0xD8EB3A44, player, p0, p1); } // 0xD8EB3A44
inline BOOL CanPlayerStartMission(Any p0) { return FiveXInvoke<BOOL>(0x39E3CB3F, p0); } // 0x39E3CB3F
inline BOOL IsPlayerReadyForCutscene(Any p0) { return FiveXInvoke<BOOL>(0xBB77E9CD, p0); } // 0xBB77E9CD
inline BOOL IsPlayerTargettingEntity(Player Player, Entity Entity) { return FiveXInvoke<BOOL>(0xF3240B77, Player, Entity); } // 0xF3240B77
inline Any GetPlayerTargetEntity(Player player, Entity* entity) { return FiveXInvoke<Any>(0xF6AAA2D7, player, entity); } // 0xF6AAA2D7
inline BOOL IsPlayerFreeAiming(Player player) { return FiveXInvoke<BOOL>(0x1DEC67B7, player); } // 0x1DEC67B7
inline BOOL IsPlayerFreeAimingAtEntity(Player player, Entity entity) { return FiveXInvoke<BOOL>(0x7D80EEAA, player, entity); } // 0x7D80EEAA
inline BOOL GetAimedEntity(Player player, Entity* entity) { return FiveXInvoke<BOOL>(0x8866D9D0, player, entity); } // 0x8866D9D0
inline VOID SetPlayerLockonRangeOverride(Player player, FLOAT range) { FiveXInvoke<VOID>(0x74D42C03, player, range); } // 0x74D42C03
inline VOID SetPlayerCanDoDriveBy(Any p0, Any p1) { FiveXInvoke<VOID>(0xF4D99685, p0, p1); } // 0xF4D99685
inline VOID SetPlayerCanBeHassledByGangs(Any p0, Any p1) { FiveXInvoke<VOID>(0x71B305BB, p0, p1); } // 0x71B305BB
inline VOID SetPlayerCanUseCover(Any p0, Any p1) { FiveXInvoke<VOID>(0x13CAFAFA, p0, p1); } // 0x13CAFAFA
inline INT GetMaxWantedLevel() { return FiveXInvoke<int>(0x457F1E44); } // 0x457F1E44
inline BOOL IsPlayerTargettingAnything(Player player) { return FiveXInvoke<BOOL>(0x456DB50D, player); } // 0x456DB50D
inline VOID SetPlayerSprint(Any p0, Any p1) { FiveXInvoke<VOID>(0x7DD7900C, p0, p1); } // 0x7DD7900C
inline VOID ResetPlayerStamina(Any Player) { FiveXInvoke<VOID>(0xC0445A9C, Player); } // 0xC0445A9C
inline VOID RestorePlayerStamina(Any p0, Any p1) { FiveXInvoke<VOID>(0x62A93608, p0, p1); } // 0x62A93608
inline Any GetPlayerSprintTimeRemaining(Any p0) { return FiveXInvoke<Any>(0x40E80543, p0); } // 0x40E80543
inline Any GetPlayerUnderwaterTimeRemaining(Any p0) { return FiveXInvoke<Any>(0x1317125A, p0); } // 0x1317125A
inline INT GetPlayerGroup(Player Player) { return FiveXInvoke<int>(0xA5EDCDE8, Player); } // 0xA5EDCDE8
inline Any GetPlayerMaxArmour(Player Player) { return FiveXInvoke<Any>(0x02A50657, Player); } // 0x02A50657
inline BOOL IsPlayerControlOn(Player Player) { return FiveXInvoke<BOOL>(0x618857F2, Player); } // 0x618857F2
inline BOOL IsPlayerScriptControlOn(Any p0) { return FiveXInvoke<BOOL>(0x61B00A84, p0); } // 0x61B00A84
inline BOOL IsPlayerClimbing(Any p0) { return FiveXInvoke<BOOL>(0x4A9E9AE0, p0); } // 0x4A9E9AE0
inline BOOL IsPlayerBeingArrested(Any p0, Any p1) { return FiveXInvoke<BOOL>(0x7F6A60D3, p0, p1); } // 0x7F6A60D3
inline Any GetPlayersLastVehicle() { return FiveXInvoke<Any>(0xE2757AC1); } // 0xE2757AC1
inline Any GetPlayerIndex() { return FiveXInvoke<Any>(0x309BBDC1); } // 0x309BBDC1
inline Any IntToPlayerindex(Any p0) { return FiveXInvoke<Any>(0x98DD98F1, p0); } // 0x98DD98F1
inline Any GetTimeSincePlayerHitVehicle(Any p0) { return FiveXInvoke<Any>(0x6E9B8B9E, p0); } // 0x6E9B8B9E
inline Any GetTimeSincePlayerHitPed(Any p0) { return FiveXInvoke<Any>(0xB6209195, p0); } // 0xB6209195
inline Any GetTimeSincePlayerDroveOnPavement(Any p0) { return FiveXInvoke<Any>(0x8836E732, p0); } // 0x8836E732
inline FLOAT GetTimeSincePlayerDroveAgainstTraffic(FLOAT time) { return FiveXInvoke<float>(0x9F27D00E, time); } // 0x9F27D00E
inline BOOL IsPlayerFreeForAmbientTask(Any p0) { return FiveXInvoke<BOOL>(0x85C7E232, p0); } // 0x85C7E232
inline VOID ForceCleanup(Any p0) { FiveXInvoke<VOID>(0xFDAAEA2B, p0); } // 0xFDAAEA2B
inline VOID SetPlayerMayOnlyEnterThisVehicle(Any p0, Any p1) { FiveXInvoke<VOID>(0xA454DD29, p0, p1); } // 0xA454DD29
inline Any GiveAchievementToPlayer(INT achievement) { return FiveXInvoke<Any>(0x822BC992, achievement); } // 0x822BC992
inline BOOL HasAchievementBeenPassed(INT achievement) { return FiveXInvoke<BOOL>(0x136A5BE9, achievement); } // 0x136A5BE9
inline BOOL IsPlayerOnline() { return FiveXInvoke<BOOL>(0x9FAB6729); } // 0x9FAB6729
inline BOOL IsPlayerLoggingInNp() { return FiveXInvoke<BOOL>(0x8F72FAD0); } // 0x8F72FAD0
inline VOID DisplaySystemSigninUi(Any p0) { FiveXInvoke<VOID>(0x4264CED2, p0); } // 0x4264CED2
inline BOOL IsSystemUiBeingDisplayed() { return FiveXInvoke<BOOL>(0xE495B6DA); } // 0xE495B6DA
inline Any GetPlayerInvincible(Any p0) { return FiveXInvoke<Any>(0x680C90EE, p0); } // 0x680C90EE
inline VOID RemovePlayerHelmet(Player player, BOOL p2) { FiveXInvoke<VOID>(0x6255F3B4, player, p2); } // 0x6255F3B4
inline VOID GivePlayerRagdollControl(Player player, BOOL toggle) { FiveXInvoke<VOID>(0xC7B4D7AC, player, toggle); } // 0xC7B4D7AC
inline VOID SetPlayerLockon(Any p0, Any p1) { FiveXInvoke<VOID>(0x0B270E0F, p0, p1); } // 0x0B270E0F
inline VOID SetPlayerTargetingMode(INT targetmode) { FiveXInvoke<VOID>(0x61CAE253, targetmode); } // 0x61CAE253
inline VOID ClearPlayerHasDamagedAtLeastOnePed(Player player) { FiveXInvoke<VOID>(0x1D31CBBD, player); } // 0x1D31CBBD
inline BOOL HasPlayerDamagedAtLeastOnePed(Player player) { return FiveXInvoke<BOOL>(0x14F52453, player); } // 0x14F52453
inline VOID ClearPlayerHasDamagedAtLeastOneNonAnimalPed(Player player) { FiveXInvoke<VOID>(0x7E3BFBC5, player); } // 0x7E3BFBC5
inline Any HasPlayerDamagedAtLeastOneNonAnimalPed(Player player) { return FiveXInvoke<Any>(0xA3707DFC, player); } // 0xA3707DFC
inline VOID SetAirDragMultiplierForPlayersVehicle(Any p0, Any p1) { FiveXInvoke<VOID>(0xF20F72E5, p0, p1); } // 0xF20F72E5
inline VOID SetSwimMultiplierForPlayer(Player player, FLOAT multiplier) { FiveXInvoke<VOID>(0xB986FF47, player, multiplier); } // 0xB986FF47
inline VOID SetRunSprintMultiplierForPlayer(Player player, FLOAT multiplier) { FiveXInvoke<VOID>(0x825423C2, player, multiplier); } // 0x825423C2
inline Any GetTimeSinceLastArrest() { return FiveXInvoke<Any>(0x62824EF4); } // 0x62824EF4
inline Any GetTimeSinceLastDeath() { return FiveXInvoke<Any>(0x24BC5AC0); } // 0x24BC5AC0
inline VOID AssistedMovementCloseRoute() { FiveXInvoke<VOID>(0xF23277F3); } // 0xF23277F3
inline VOID AssistedMovementFlushRoute() { FiveXInvoke<VOID>(0xD04568B9); } // 0xD04568B9
inline VOID SetPlayerForcedAim(Player p0, BOOL p1) { FiveXInvoke<VOID>(0x94E42E2E, p0, p1); } // 0x94E42E2E
inline VOID SetPlayerForcedZoom(Any p0, Any p1) { FiveXInvoke<VOID>(0xB0C576CB, p0, p1); } // 0xB0C576CB
inline VOID DisablePlayerFiring(Player Player, BOOL Toggle) { FiveXInvoke<VOID>(0x30CB28CB, Player, Toggle); } // 0x30CB28CB
inline VOID SetPlayerMaxArmour(Player Player, BOOL Toggle) { FiveXInvoke<VOID>(0xC6C3C53B, Player, Toggle); } // 0xC6C3C53B
inline VOID SpecialAbilityDeactivate(Any p0) { FiveXInvoke<VOID>(0x80C2AB09, p0); } // 0x80C2AB09
inline VOID SpecialAbilityReset(Any p0) { FiveXInvoke<VOID>(0xA7D8BCD3, p0); } // 0xA7D8BCD3
inline VOID ResetSpecialAbilityControlsCinematic(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x8C7E68C1, p0, p1, p2); } // 0x8C7E68C1
inline VOID SpecialAbilityLock(Any p0) { FiveXInvoke<VOID>(0x1B7BB388, p0); } // 0x1B7BB388
inline VOID SpecialAbilityUnlock(Any p0) { FiveXInvoke<VOID>(0x1FDB2919, p0); } // 0x1FDB2919
inline BOOL IsSpecialAbilityUnlocked(Any p0) { return FiveXInvoke<BOOL>(0xC9C75E82, p0); } // 0xC9C75E82
inline BOOL IsSpecialAbilityActive(Any p0) { return FiveXInvoke<BOOL>(0x1B17E334, p0); } // 0x1B17E334
inline BOOL IsSpecialAbilityMeterFull(Any p0) { return FiveXInvoke<BOOL>(0x2E19D7F6, p0); } // 0x2E19D7F6
inline VOID EnableSpecialAbility(Any p0, Any p1) { FiveXInvoke<VOID>(0xC86C1B4E, p0, p1); } // 0xC86C1B4E
inline BOOL IsSpecialAbilityEnabled(Any p0) { return FiveXInvoke<BOOL>(0xC01238CC, p0); } // 0xC01238CC
inline VOID SetSpecialAbilityMultiplier(Any p0) { FiveXInvoke<VOID>(0xFF1BC556, p0); } // 0xFF1BC556
inline VOID StartPlayerTeleport(Player Player, FLOAT p1, FLOAT p2, FLOAT p3, FLOAT Heading, BOOL KeepVehicle, BOOL KeepVelocity, BOOL FadeInOut) { FiveXInvoke<VOID>(0xC552E06C, Player, p1, p2, p3, Heading, KeepVehicle, KeepVelocity, FadeInOut); } //0xC552E06C
inline VOID StopPlayerTeleport() { FiveXInvoke<VOID>(0x86AB8DBB); } // 0x86AB8DBB
inline BOOL IsPlayerTeleportActive() { return FiveXInvoke<BOOL>(0x3A11D118); } // 0x3A11D118
inline FLOAT GetPlayerCurrentStealthNoise(Vehicle* p0) { return FiveXInvoke<float>(0xC3B02362, p0); } // 0xC3B02362
inline VOID SetPlayerWeaponDamageModifier(Player player, FLOAT DamageAmount) { FiveXInvoke<VOID>(0xB02C2F39, player, DamageAmount); } // 0xB02C2F39
inline VOID SetPlayerVehicleDamageModifier(Player Player, FLOAT DamageAmount) { FiveXInvoke<VOID>(0x823ECA63, Player, DamageAmount); } // 0x823ECA63
inline VOID SetPlayerParachuteTintIndex(Any p0, Any p1) { FiveXInvoke<VOID>(0x8EA12EDB, p0, p1); } // 0x8EA12EDB
inline VOID GetPlayerParachuteTintIndex(Any p0, Any p1) { FiveXInvoke<VOID>(0x432B0509, p0, p1); } // 0x432B0509
inline VOID SetPlayerParachutePackTintIndex(Any p0, Any p1) { FiveXInvoke<VOID>(0xD79D5D1B, p0, p1); } // 0xD79D5D1B
inline VOID SetPlayerHasReserveParachute(Player player) { FiveXInvoke<VOID>(0xA3E4798E, player); } // 0xA3E4798E
inline VOID SetPlayerNoiseMultiplier(Player Player, FLOAT Multipliyer) { FiveXInvoke<VOID>(0x15786DD1, Player, Multipliyer); } // 0x15786DD1
inline VOID SimulatePlayerInputGait(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { FiveXInvoke<VOID>(0x0D77CC34, p0, p1, p2, p3, p4, p5); } // 0x0D77CC34
inline VOID ResetPlayerInputGait(Any p0) { FiveXInvoke<VOID>(0x4A701EE1, p0); } // 0x4A701EE1
inline VOID SetPlayerSimulateAiming(Any p0, Any p1) { FiveXInvoke<VOID>(0xF1E0CAFC, p0, p1); } // 0xF1E0CAFC
inline BOOL IsPlayerRidingTrain(Player Player) { return FiveXInvoke<BOOL>(0x9765E71D, Player); } // 0x9765E71D
inline VOID RequestScript(char* ScriptName) { FiveXInvoke<VOID>(0xE26B2666, ScriptName); } // 0xE26B2666
inline VOID SetScriptAsNoLongerNeeded(char* ScriptName) { FiveXInvoke<VOID>(0x6FCB7795, ScriptName); } // 0x6FCB7795
inline BOOL HasScriptLoaded(char* ScriptName) { return FiveXInvoke<BOOL>(0x5D67F751, ScriptName); } // 0x5D67F751
inline BOOL DoesScriptExist(char* ScriptName) { return FiveXInvoke<BOOL>(0xDEAB87AB, ScriptName); } // 0xDEAB87AB
inline VOID TerminateThread(INT ThreadID) { FiveXInvoke<VOID>(0x253FD520, ThreadID); } // 0x253FD520
inline BOOL IsThreadActive(INT ThreadID) { return FiveXInvoke<BOOL>(0x78D7A5A0, ThreadID); } // 0x78D7A5A0
inline char* GetThreadName(INT ThreadID) { return FiveXInvoke<char*>(0xBE7ACD89, ThreadID); } // 0xBE7ACD89
inline INT GetIdOfThisThread() { return FiveXInvoke<int>(0xDE524830); } // 0xDE524830
inline VOID TerminateThisThread() { FiveXInvoke<VOID>(0x3CD9CBB7); } // 0x3CD9CBB7
inline char* GetThisScriptName() { return FiveXInvoke<char*>(0xA40FD5D9); } // 0xA40FD5D9
inline Any GetNumberOfEvents(Any p0) { return FiveXInvoke<Any>(0xA3525D60, p0); } // 0xA3525D60
inline Any GetEventExists(Any p0, Any p1) { return FiveXInvoke<Any>(0xA1B447B5, p0, p1); } // 0xA1B447B5
inline Any GetEventAtIndex(Any p0, Any p1) { return FiveXInvoke<Any>(0xB49C1442, p0, p1); } // 0xB49C1442
inline Any GetEventData(INT p0, INT p1, INT* p2, INT p3) { return FiveXInvoke<Any>(0x4280F92F, p0, p1, p2, p3); } // 0x4280F92F
inline VOID TriggerScriptEvent(Any p0, PINT p1, Any p2, INT p3) { FiveXInvoke<VOID>(0x54763B35, p0, p1, p2, p3); } // 0x54763B35
inline VOID ShutdownLoadingScreen() { FiveXInvoke<VOID>(0xA2826D17); } // 0xA2826D17
inline VOID SetNoLoadingScreen(BOOL p0) { FiveXInvoke<VOID>(0xC8055034, p0); } // 0xC8055034
inline Any StatLoad(Any p0) { return FiveXInvoke<Any>(0x9E5629F4, p0); } // 0x9E5629F4
inline Any StatSave(INT p0, BOOL p1, INT p2) { return FiveXInvoke<Any>(0xE10A7CA4, p0, p1, p2); } // 0xE10A7CA4
inline Any StatLoadPending(Any p0) { return FiveXInvoke<Any>(0x4E9AC983, p0); } // 0x4E9AC983
inline Any StatSavePending() { return FiveXInvoke<Any>(0xC3FD3822); } // 0xC3FD3822
inline Any StatDeleteSlot(Any p0) { return FiveXInvoke<Any>(0x2F171B94, p0); } // 0x2F171B94
inline Any StatSetInt(Hash statName, INT value, BOOL save) { return FiveXInvoke<Any>(0xC9CC1C5C, statName, value, save); } // 0xC9CC1C5C
inline Any StatSetFloat(Hash statName, FLOAT value, BOOL save) { return FiveXInvoke<Any>(0x6CEA96F2, statName, value, save); } // 0x6CEA96F2
inline Any StatSetBool(Hash statName, BOOL value, BOOL save) { return FiveXInvoke<Any>(0x55D79DFB, statName, value, save); } // 0x55D79DFB
inline Any StatSetDate(Any p0, Any p1, Any p2, Any p3) { return FiveXInvoke<Any>(0x36BE807B, p0, p1, p2, p3); } // 0x36BE807B
inline Any StatSetString(Hash statName, char* value, BOOL save) { return FiveXInvoke<Any>(0xB1EF2E21, statName, value, save); } // 0xB1EF2E21
inline Any StatSetPos(Any p0, Any p1, Any p2, Any p3, Any p4) { return FiveXInvoke<Any>(0x1192C9A3, p0, p1, p2, p3, p4); } // 0x1192C9A3
inline Any StatSetMaskedInt(Any p0, Any p1, Any p2, Any p3, Any p4) { return FiveXInvoke<Any>(0x2CBAA739, p0, p1, p2, p3, p4); } // 0x2CBAA739
inline Any StatSetUserId(Hash playerName, char* value, BOOL save) { return FiveXInvoke<Any>(0xDBE78ED7, playerName, value, save); } // 0xDBE78ED7
inline BOOL StatGetInt(Hash statHash, PINT valuePoINTer, INT p2) { return FiveXInvoke<BOOL>(0x1C6FE43E, statHash, valuePoINTer, p2); } // 0x1C6FE43E
inline BOOL StatGetFloat(Hash statHash, FLOAT* valuePoINTer, Any p2) { return FiveXInvoke<BOOL>(0xFCBDA612, statHash, valuePoINTer, p2); } // 0xFCBDA612
inline BOOL StatGetBool(Hash statHash, PINT valuePoINTer, Any p2) { return FiveXInvoke<BOOL>(0x28A3DD2B, statHash, valuePoINTer, p2); } // 0x28A3DD2B
inline Any StatGetDate(Any p0, Any p1, Any p2, Any p3) { return FiveXInvoke<Any>(0xD762D16C, p0, p1, p2, p3); } // 0xD762D16C
inline Any StatGetString(Any p0, Any p1) { return FiveXInvoke<Any>(0x10CE4BDE, p0, p1); } // 0x10CE4BDE
inline Any StatGetPos(Any p0, Any p1, Any p2, Any p3, Any p4) { return FiveXInvoke<Any>(0xC846ECCE, p0, p1, p2, p3, p4); } // 0xC846ECCE
inline Any StatGetMaskedInt(Any p0, Any p1, Any p2, Any p3, Any p4) { return FiveXInvoke<Any>(0xE9D9B70F, p0, p1, p2, p3, p4); } // 0xE9D9B70F
inline char* StatGetUserId(char* p0) { return FiveXInvoke<char*>(0xE2E8B6BA, p0); } // 0xE2E8B6BA
inline VOID StatIncrement(Hash statName, INT Value) { FiveXInvoke<VOID>(0xDFC5F71E, statName, Value); } // 0xDFC5F71E
inline Any StatGetBoolMasked(Any p0, Any p1, Any p2) { return FiveXInvoke<Any>(0x6ACE1B7D, p0, p1, p2); } // 0x6ACE1B7D
inline Any StatSetBoolMasked(Any p0, Any p1, Any p2, Any p3) { return FiveXInvoke<Any>(0x7842C4D6, p0, p1, p2, p3); } // 0x7842C4D6
inline VOID PlaystatsNpcInvite(Any p0) { FiveXInvoke<VOID>(0x598C06F3, p0); } // 0x598C06F3
inline VOID PlaystatsAwardXp(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x8770017B, p0, p1, p2); } // 0x8770017B
inline VOID PlaystatsRankUp(Any p0) { FiveXInvoke<VOID>(0x56AFB9F5, p0); } // 0x56AFB9F5
inline VOID PlaystatsMissionStarted(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x3AAB699C, p0, p1, p2, p3); } // 0x3AAB699C
inline VOID PlaystatsMissionOver(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { FiveXInvoke<VOID>(0x5B90B5FF, p0, p1, p2, p3, p4, p5); } // 0x5B90B5FF
inline VOID PlaystatsMissionCheckpoint(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0xCDC52280, p0, p1, p2, p3); } // 0xCDC52280
inline VOID PlaystatsRaceCheckpoint(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0x580D5508, p0, p1, p2, p3, p4); } // 0x580D5508
inline VOID PlaystatsMatchStarted(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { FiveXInvoke<VOID>(0x2BDE85C1, p0, p1, p2, p3, p4, p5, p6); } // 0x2BDE85C1
inline VOID PlaystatsShopItem(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0xA4746384, p0, p1, p2, p3, p4); } // 0xA4746384
inline VOID PlaystatsFriendActivity(Any p0, Any p1) { FiveXInvoke<VOID>(0xD1FA1BDB, p0, p1); } // 0xD1FA1BDB
inline VOID PlaystatsOddjobDone(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xFE14A8EA, p0, p1, p2); } // 0xFE14A8EA
inline VOID PlaystatsPropChange(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x25740A1D, p0, p1, p2, p3); } // 0x25740A1D
inline VOID PlaystatsClothChange(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0x3AFF9E58, p0, p1, p2, p3, p4); } // 0x3AFF9E58
inline VOID PlaystatsCheatApplied(Any p0) { FiveXInvoke<VOID>(0x345166F3, p0); } // 0x345166F3
inline Any LeaderboardsGetNumberOfColumns(Any p0, Any p1) { return FiveXInvoke<Any>(0x0A56EE34, p0, p1); } // 0x0A56EE34
inline Any LeaderboardsGetColumnId(Any p0, Any p1, Any p2) { return FiveXInvoke<Any>(0x3821A334, p0, p1, p2); } // 0x3821A334
inline Any LeaderboardsGetColumnType(Any p0, Any p1, Any p2) { return FiveXInvoke<Any>(0x6F2820F4, p0, p1, p2); } // 0x6F2820F4
inline Any LeaderboardsReadClearAll() { return FiveXInvoke<Any>(0x233E058A); } // 0x233E058A
inline Any LeaderboardsReadClear(Any p0, Any p1, Any p2) { return FiveXInvoke<Any>(0x7090012F, p0, p1, p2); } // 0x7090012F
inline Any LeaderboardsReadPending(Any p0, Any p1, Any p2) { return FiveXInvoke<Any>(0xEEB8BF5C, p0, p1, p2); } // 0xEEB8BF5C
inline Any LeaderboardsReadSuccessful(Any p0, Any p1, Any p2) { return FiveXInvoke<Any>(0x3AC5B2F1, p0, p1, p2); } // 0x3AC5B2F1
inline Any Leaderboards2ReadFriendsByRow(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return FiveXInvoke<Any>(0xBD91B136, p0, p1, p2, p3, p4, p5); } // 0xBD91B136
inline Any Leaderboards2ReadByHandle(Any p0, Any p1) { return FiveXInvoke<Any>(0x6B553408, p0, p1); } // 0x6B553408
inline Any Leaderboards2ReadByRow(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return FiveXInvoke<Any>(0xCA931F34, p0, p1, p2, p3, p4, p5, p6); } // 0xCA931F34
inline Any Leaderboards2ReadByRank(Any p0, Any p1, Any p2) { return FiveXInvoke<Any>(0x1B03F59F, p0, p1, p2); } // 0x1B03F59F
inline Any Leaderboards2ReadByRadius(Any p0, Any p1, Any p2) { return FiveXInvoke<Any>(0xC5B7E685, p0, p1, p2); } // 0xC5B7E685
inline Any Leaderboards2ReadByScoreInt(Any p0, Any p1, Any p2) { return FiveXInvoke<Any>(0xAC020C18, p0, p1, p2); } // 0xAC020C18
inline Any Leaderboards2ReadByScoreFloat(Any p0, Any p1, Any p2) { return FiveXInvoke<Any>(0xC678B29F, p0, p1, p2); } // 0xC678B29F
inline Any Leaderboards2WriteData(Any p0) { return FiveXInvoke<Any>(0x5F9DF634, p0); } // 0x5F9DF634
inline Any LeaderboardsCacheDataRow(Any p0) { return FiveXInvoke<Any>(0x44F7D82B, p0); } // 0x44F7D82B
inline VOID LeaderboardsClearCacheData() { FiveXInvoke<VOID>(0x87F498C1); } // 0x87F498C1
inline Any LeaderboardsGetCacheExists(Any p0) { return FiveXInvoke<Any>(0xFC8A71F3, p0); } // 0xFC8A71F3
inline Any LeaderboardsGetCacheTime(Any p0) { return FiveXInvoke<Any>(0xEDF02302, p0); } // 0xEDF02302
inline Any LeaderboardsGetCacheDataRow(Any p0, Any p1, Any p2) { return FiveXInvoke<Any>(0xA11289EC, p0, p1, p2); } // 0xA11289EC
inline VOID RequestNamedPtfxAsset(char* fxName) { FiveXInvoke<VOID>(0xCFEA19A9, fxName); } // 0xCFEA19A9 0xCFEA19A9
inline VOID LoadAllObjectsNow() { FiveXInvoke<VOID>(0xC9DBDA90); } // 0xC9DBDA90
inline VOID LoadScene(float x, float y, float z) { FiveXInvoke<VOID>(0xB72403F5, x, y, z); } // 0xB72403F5
inline Any NetworkUpdateLoadScene() { return FiveXInvoke<Any>(0xC76E023C); } // 0xC76E023C
inline VOID NetworkStopLoadScene() { FiveXInvoke<VOID>(0x24857907); } // 0x24857907
inline BOOL IsNetworkLoadingScene() { return FiveXInvoke<BOOL>(0x6DCFC021); } // 0x6DCFC021
inline VOID SetInteriorActive(Any p0, Any p1) { FiveXInvoke<VOID>(0xE1013910, p0, p1); } // 0xE1013910
inline INT GetInteriorFromEntity(Entity entity) { return FiveXInvoke<INT>(0x5C644614, entity); } // 0x5C644614
inline BOOL IsModelInCdimage(Any p0) { return FiveXInvoke<BOOL>(0x1094782F, p0); } // 0x1094782F
inline BOOL IsModelValid(INT p0) { return FiveXInvoke<BOOL>(0xAF8F8E9D, p0); } // 0xAF8F8E9D
inline BOOL IsModelAVehicle(Any p0) { return FiveXInvoke<BOOL>(0xFFFC85D4, p0); } // 0xFFFC85D4
inline VOID RequestCollisionForModel(Hash vehicleHash) { FiveXInvoke<VOID>(0x3930C042, vehicleHash); } // 0x3930C042
inline BOOL HasCollisionForModelLoaded(Any p0) { return FiveXInvoke<BOOL>(0x41A094F8, p0); } // 0x41A094F8
inline VOID RequestAdditionalCollisionAtCoord(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xC2CC1DF2, p0, p1, p2); } // 0xC2CC1DF2
inline CHAR* DoesAnimDictExist(CHAR* p0) { return FiveXInvoke<char*>(0xCD31C872, p0); } // 0xCD31C872
inline VOID RequestAnimSet(char* p0) { FiveXInvoke<VOID>(0x2988B3FC, p0); } // 0x2988B3FC
inline BOOL HasAnimSetLoaded(char* p0) { return FiveXInvoke<BOOL>(0x4FFF397D, p0); } // 0x4FFF397D
inline VOID RemoveAnimSet(Any p0) { FiveXInvoke<VOID>(0xD04A817A, p0); } // 0xD04A817A
inline VOID RequestIpl(char* iplName) { FiveXInvoke<VOID>(0x3B70D1DB, iplName); } // 0x3B70D1DB
inline VOID RemoveIpl(char* iplName) { FiveXInvoke<VOID>(0xDF7CBD36, iplName); } // 0xDF7CBD36
inline BOOL IsIplActive(char* iplName) { return FiveXInvoke<BOOL>(0xB2C33714, iplName); } // 0xB2C33714
inline VOID SetStreaming(Any p0) { FiveXInvoke<VOID>(0x27EF6CB2, p0); } // 0x27EF6CB2
inline VOID SetGamePausesForStreaming(Any p0) { FiveXInvoke<VOID>(0x9211A28A, p0); } // 0x9211A28A
inline VOID SetReducePedModelBudget(Any p0) { FiveXInvoke<VOID>(0xAFCB2B86, p0); } // 0xAFCB2B86
inline VOID SetReduceVehicleModelBudget(Any p0) { FiveXInvoke<VOID>(0xCDB4FB7E, p0); } // 0xCDB4FB7E
inline VOID SetDitchPoliceModels(Any p0) { FiveXInvoke<VOID>(0x3EA7FCE4, p0); } // 0x3EA7FCE4
inline Any GetNumberOfStreamingRequests() { return FiveXInvoke<Any>(0xC2EE9A02); } // 0xC2EE9A02
inline VOID RequestPtfxAsset() { FiveXInvoke<VOID>(0x2C649263); } // 0x2C649263
inline BOOL HasPtfxAssetLoaded() { return FiveXInvoke<BOOL>(0x3EFF96BE); } // 0x3EFF96BE
inline VOID RemovePtfxAsset() { FiveXInvoke<VOID>(0xC10F178C); } // 0xC10F178C
inline VOID RequestDlcPtfxAsset(char* FX) { FiveXInvoke<VOID>(0xCFEA19A9, FX); } // 0xCFEA19A9
inline Any HasDlcPtfxLoaded(char* FX) { return FiveXInvoke<Any>(0x9ACC6446, FX); } // 0x9ACC6446
inline VOID RemoveDlcPtfxAsset(char* FX) { FiveXInvoke<VOID>(0xC44762A1, FX); } // 0xC44762A1
inline VOID SetVehiclePopulationBudget(Any p0) { FiveXInvoke<VOID>(0x1D56993C, p0); } // 0x1D56993C
inline VOID SetPedPopulationBudget(Any p0) { FiveXInvoke<VOID>(0xD2D026CD, p0); } // 0xD2D026CD
inline VOID ClearFocus() { FiveXInvoke<VOID>(0x34D91E7A); } // 0x34D91E7A
inline VOID SetFocusArea(float x, float y, float z, float offsetX, float offsetY, float offsetZ) { FiveXInvoke<VOID>(0x14680A60, x, y, z, offsetX, offsetY, offsetZ); } // 0x14680A60
inline VOID SetFocusEntity(Any p0) { FiveXInvoke<VOID>(0x18DB04AC, p0); } // 0x18DB04AC
inline BOOL IsEntityFocus(Any p0) { return FiveXInvoke<BOOL>(0xB456D707, p0); } // 0xB456D707
inline Any NewLoadSceneStart(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return FiveXInvoke<Any>(0xDF9C38B6, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xDF9C38B6
inline VOID NewLoadSceneStop() { FiveXInvoke<VOID>(0x7C05B1F6); } // 0x7C05B1F6
inline BOOL IsNewLoadSceneActive() { return FiveXInvoke<BOOL>(0xAD234B7F); } // 0xAD234B7F
inline BOOL IsNewLoadSceneLoaded() { return FiveXInvoke<BOOL>(0x3ECD839F); } // 0x3ECD839F
inline VOID StartPlayerSwitch(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x0829E975, p0, p1, p2, p3); } // 0x0829E975
inline VOID StopPlayerSwitch() { FiveXInvoke<VOID>(0x2832C010); } // 0x2832C010
inline Any StopPlayerRemainArcade() { return FiveXInvoke<Any>(0x56135ACC); } // 0x56135ACC
inline Any GetPlayerSwitchType() { return FiveXInvoke<Any>(0x280DC015); } // 0x280DC015
inline Any GetIdealPlayerSwitchType(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return FiveXInvoke<Any>(0xD5A450F1, p0, p1, p2, p3, p4, p5); } // 0xD5A450F1
inline Any GetPlayerSwitchState() { return FiveXInvoke<Any>(0x39A0E1F2); } // 0x39A0E1F2
inline Any GetPlayerShortSwitchState() { return FiveXInvoke<Any>(0x9B7BA38F); } // 0x9B7BA38F
inline Any SetPlayerInvertedUp() { return FiveXInvoke<Any>(0x569847E3); } // 0x569847E3
inline Any DestroyPlayerInPauseMenu() { return FiveXInvoke<Any>(0x90F64284); } // 0x90F64284
inline VOID OverrideLodscaleThisFrame(float scaling) { FiveXInvoke<VOID>(0xE5612C1A, scaling); } // 0xE5612C1A
inline VOID PrefetchSrl(Any p0) { FiveXInvoke<VOID>(0x37BE2FBB, p0); } // 0x37BE2FBB
inline BOOL IsSrlLoaded() { return FiveXInvoke<BOOL>(0x670FA2A6); } // 0x670FA2A6
inline VOID BeginSrl() { FiveXInvoke<VOID>(0x24F49427); } // 0x24F49427
inline VOID EndSrl() { FiveXInvoke<VOID>(0x1977C56A); } // 0x1977C56A
inline VOID SetSrlTime(Any p0) { FiveXInvoke<VOID>(0x30F8A487, p0); } // 0x30F8A487
inline VOID SetHdArea(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x80BAA035, p0, p1, p2, p3); } // 0x80BAA035
inline VOID ClearHdArea() { FiveXInvoke<VOID>(0x7CAC6FA0); } // 0x7CAC6FA0
inline VOID Wait(INT ms) { FiveXInvoke<VOID>(0x7715C03B, ms); } // 0x7715C03B
inline INT StartNewScript(char* ScriptName, INT StackSize) { return FiveXInvoke<int>(0x3F166D0E, ScriptName, StackSize); } // 0x3F166D0E
inline INT StartNewScriptWithArgs(char* ScriptName, Any Args, INT ArgCount, INT StackSize) { return FiveXInvoke<int>(0x4A2100E4, ScriptName, Args, ArgCount, StackSize); } // 0x4A2100E4
inline Any NullStartNewScript(INT p0, INT StackSize) { return FiveXInvoke<Any>(0x8D15BE5D, p0, StackSize); } // 0x8D15BE5D
inline Any NullStartNewScriptWithArgs(Any p0, Any p1, Any p2, Any p3) { return FiveXInvoke<Any>(0xE38A3AD4, p0, p1, p2, p3); } // 0xE38A3AD4
inline INT Timera() { return FiveXInvoke<int>(0x45C8C188); } // 0x45C8C188
inline INT Timerb() { return FiveXInvoke<int>(0x330A9C0C); } // 0x330A9C0C
inline VOID Settimera(INT TimerA) { FiveXInvoke<VOID>(0x35785333, TimerA); } // 0x35785333
inline VOID Settimerb(INT TimerB) { FiveXInvoke<VOID>(0x27C1B7C6, TimerB); } // 0x27C1B7C6
inline FLOAT Timestep() { return FiveXInvoke<float>(0x50597EE2); } // 0x50597EE2
inline FLOAT Sin(FLOAT p0) { return FiveXInvoke<float>(0xBF987F58, p0); } // 0xBF987F58
inline FLOAT Cos(FLOAT p0) { return FiveXInvoke<float>(0x00238FE9, p0); } // 0x00238FE9
inline FLOAT Sqrt(FLOAT p0) { return FiveXInvoke<float>(0x145C7701, p0); } // 0x145C7701
inline FLOAT Pow(FLOAT base, FLOAT exponent) { return FiveXInvoke<float>(0x85D134F8, base, exponent); } // 0x85D134F8
inline FLOAT Vmag(FLOAT p0, FLOAT p1, FLOAT p2) { return FiveXInvoke<float>(0x1FCF1ECD, p0, p1, p2); } // 0x1FCF1ECD
inline FLOAT Vmag2(FLOAT p0, FLOAT p1, FLOAT p2) { return FiveXInvoke<float>(0xE796E629, p0, p1, p2); } // 0xE796E629
inline FLOAT Vdist(Vector3 c1, Vector3 c2) { return FiveXInvoke<FLOAT>(0x3C08ECB7, c1.x, c1.y, c1.z, c2.x, c2.y, c2.z); } // 0x3C08ECB7
inline FLOAT Vdist2(FLOAT X1, FLOAT Y1, FLOAT Z1, FLOAT X2, FLOAT Y2, FLOAT Z2) { return FiveXInvoke<float>(0xC85DEF1F, X1, Y1, Z1, X2, Y2, Z2); } // 0xC85DEF1F
inline INT ShiftLeft(INT Value, INT BitShift) { return FiveXInvoke<int>(0x314CC6CD, Value, BitShift); } // 0x314CC6CD
inline INT ShiftRight(INT Value, INT BitShift) { return FiveXInvoke<int>(0x352633CA, Value, BitShift); } // 0x352633CA
inline INT Floor(FLOAT Value) { return FiveXInvoke<int>(0x32E9BE04, Value); } // 0x32E9BE04
inline INT Ceil(FLOAT Value) { return FiveXInvoke<int>(0xD536A1DF, Value); } // 0xD536A1DF
inline INT Round(FLOAT Value) { return FiveXInvoke<int>(0x323B0E24, Value); } // 0x323B0E24
inline FLOAT ToFloat(INT Value) { return FiveXInvoke<float>(0x67116627, Value); } // 0x67116627
inline VOID SetClockTime(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x26F6AF14, p0, p1, p2); } // 0x26F6AF14
inline VOID PauseClock(Any p0) { FiveXInvoke<VOID>(0xB02D6124, p0); } // 0xB02D6124
inline VOID AdvanceClockTimeTo(int hour, int minute, int second) { FiveXInvoke<VOID>(0x57B8DA7C, hour, minute, second); } // 0x57B8DA7C
inline VOID AddToClockTime(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xCC40D20D, p0, p1, p2); } // 0xCC40D20D
inline Any GetClockHours() { return FiveXInvoke<Any>(0x7EF8316F); } // 0x7EF8316F
inline Any GetClockMinutes() { return FiveXInvoke<Any>(0x94AAC486); } // 0x94AAC486
inline Any GetClockSeconds() { return FiveXInvoke<Any>(0x099C927E); } // 0x099C927E
inline VOID SetClockDate(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x96891C94, p0, p1, p2); } // 0x96891C94
inline Any GetClockDayOfWeek() { return FiveXInvoke<Any>(0x84E4A289); } // 0x84E4A289
inline Any GetClockDayOfMonth() { return FiveXInvoke<Any>(0xC7A5ACB7); } // 0xC7A5ACB7
inline Any GetClockMonth() { return FiveXInvoke<Any>(0x3C48A3D5); } // 0x3C48A3D5
inline Any GetClockYear() { return FiveXInvoke<Any>(0xB8BECF15); } // 0xB8BECF15
inline VOID GetPosixTime(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { FiveXInvoke<VOID>(0xE15A5281, p0, p1, p2, p3, p4, p5); } // 0xE15A5281
inline VOID GetLocalTime(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { FiveXInvoke<VOID>(0x124BCFA2, p0, p1, p2, p3, p4, p5); } // 0x124BCFA2
inline VOID BeginTextCommandWidth(char* p0) { FiveXInvoke<VOID>(0x51E7A037, p0); } // 0x51E7A037
inline FLOAT EndTextCommandGetWidth(BOOL p0) { return FiveXInvoke<FLOAT>(0xD12A643A, p0); } // 0xD12A643A
inline char* GetLabelText(char* labelName) { return FiveXInvoke<char*>(0x95C4B5AD, labelName); } // 0x95C4B5AD
inline INT DrawNotification2(INT time, BOOL p1) { return FiveXInvoke<int>(0x08F7AF78, time, p1); } // 0x08F7AF78
inline VOID SetNotificationTextEntry(char* p0) { FiveXInvoke<VOID>(0x574EE85C, p0); } // 0x574EE85C
inline VOID BeginTextCommandBusyspinnerOn(char* p0) { FiveXInvoke<VOID>(0xCB7C8994, p0); } // 0xCB7C8994
inline VOID EndTextCommandBusyspinnerOn(INT p0) { FiveXInvoke<VOID>(0x903F5EE4, p0); } // 0x903F5EE4
inline VOID BusyspinnerOff() { FiveXInvoke<VOID>(0x94119534); } // 0x94119534
inline bool BusyspinnerIsDisplaying() { return FiveXInvoke<bool>(0x3AF34DEF); } // 0x3AF34DEF
inline VOID PreloadBusyspinner() { FiveXInvoke<VOID>(0x71077FBD); } // 0x71077FBD
inline bool BusyspinnerIsOn() { return FiveXInvoke<bool>(0xB8B3A5D0); } // 0xB8B3A5D0
inline INT SetNotificationMessage(char* picName1, char* picName2, BOOL flash, INT iconType, char* sender, char* subject) { return FiveXInvoke<Any>(0xE7E3C98B, picName1, picName2, flash, iconType, sender, subject); } // 0xE7E3C98B
inline INT SetNotificationMessageClanTag(char* picName1, char* picName2, BOOL flash, INT iconType1, char* sender, char* subject, FLOAT duration, char* clanTag, INT iconType2) { return FiveXInvoke<int>(0xDEB491C8, picName1, picName2, flash, iconType1, sender, subject, duration, clanTag, iconType2); }
inline INT DrawNotification(BOOL blink, BOOL p1) { return FiveXInvoke<int>(0x08F7AF78, blink, p1); } // 0x08F7AF78
inline VOID BeginTextCommandPrint(char* p0) { FiveXInvoke<VOID>(0xF42C43C7, p0); } // 0xF42C43C7
inline VOID EndTextCommandPrint(INT duration, INT drawImmediately) { FiveXInvoke<VOID>(0x38F82261, duration, drawImmediately); } // 0x38F82261
inline VOID SetTextComponentFormat(char* inputtype) { FiveXInvoke<VOID>(0xB245FC10, inputtype); } // 0xB245FC10
inline VOID DisplayHelpTextFromStringLabel(Any p0, BOOL loop, BOOL beep, INT shape) { FiveXInvoke<VOID>(0xB59B530D, p0, loop, beep, shape); } // 0xB59B530D
inline VOID BeginTextCommandSetBlipName(char* textLabel) { FiveXInvoke<VOID>(0xF4C211F6, textLabel); } // 0xF4C211F6
inline VOID EndTextCommandSetBlipName(INT BLIP) { FiveXInvoke<VOID>(0xE8E59820, BLIP); } // 0xE8E59820
inline VOID AddTextComponentInteger(INT text) { FiveXInvoke<VOID>(0xFE272A57, text); } // 0xFE272A57
inline VOID AddTextComponentFloat(char* text, FLOAT DecimalPlaces) { FiveXInvoke<VOID>(0x24D78013, text, DecimalPlaces); } // 0x24D78013
inline VOID AddTextComponentSubstringPlayerName(char* text) { FiveXInvoke<VOID>(0x27A244D8, text); } // 0x27A244D8
inline VOID AddTextComponentString2(INT text) { FiveXInvoke<VOID>(0x27A244D8, text); } // 0x27A244D8
inline VOID AddTextComponentSubstringTime(Any p0, Any p1) { FiveXInvoke<VOID>(0x135B3CD0, p0, p1); } // 0x135B3CD0
inline VOID AddTextComponentString2(char* text) { FiveXInvoke<VOID>(0xC736999E, text); } // 0xC736999E
inline VOID AddTextComponentString3(char* text) { FiveXInvoke<VOID>(0x0829A799, text); } // 0x0829A799
inline VOID ClearPrints() { FiveXInvoke<VOID>(0x216CB1C5); } // 0x216CB1C5
inline VOID ClearBrief() { FiveXInvoke<VOID>(0x9F75A929); } // 0x9F75A929
inline VOID ClearAllHelpMessages() { FiveXInvoke<VOID>(0x9E5D9198); } // 0x9E5D9198
inline VOID ClearThisPrint(Any p0) { FiveXInvoke<VOID>(0x06878327, p0); } // 0x06878327
inline VOID ClearSmallPrints() { FiveXInvoke<VOID>(0xA869A238); } // 0xA869A238
inline BOOL DoesTextBlockExist(Any p0) { return FiveXInvoke<BOOL>(0x96F74838, p0); } // 0x96F74838
inline VOID RequestAdditionalText(Any p0, Any p1) { FiveXInvoke<VOID>(0x9FA9175B, p0, p1); } // 0x9FA9175B
inline BOOL HasAdditionalTextLoaded(Any p0) { return FiveXInvoke<BOOL>(0xB0E56045, p0); } // 0xB0E56045
inline VOID ClearAdditionalText(Any p0, Any p1) { FiveXInvoke<VOID>(0x518141E0, p0, p1); } // 0x518141E0
inline BOOL IsStreamingAdditionalText(Any p0) { return FiveXInvoke<BOOL>(0xF079E4EB, p0); } // 0xF079E4EB
inline BOOL HasThisAdditionalTextLoaded(Any p0, Any p1) { return FiveXInvoke<BOOL>(0x80A52040, p0, p1); } // 0x80A52040
inline BOOL IsMessageBeingDisplayed() { return FiveXInvoke<BOOL>(0x6A77FE8D); } // 0x6A77FE8D
inline BOOL DoesTextLabelExist(Any p0) { return FiveXInvoke<BOOL>(0x6ECAE560, p0); } // 0x6ECAE560
inline Any GetLengthOfStringWithThisTextLabel(Any p0) { return FiveXInvoke<Any>(0xA4CA7BE5, p0); } // 0xA4CA7BE5
inline INT GetLengthOfLiteralString(char* string) { return FiveXInvoke<int>(0x99379D55, string); } // 0x99379D55
inline char* GetStreetNameFromHashKey(Hash p0) { return FiveXInvoke<char*>(0x1E8E310C, p0); } // 0x1E8E310C
inline BOOL IsHudPreferenceSwitchedOn() { return FiveXInvoke<BOOL>(0xC3BC1B4F); } // 0xC3BC1B4F
inline BOOL IsRadarPreferenceSwitchedOn() { return FiveXInvoke<BOOL>(0x14AEAA28); } // 0x14AEAA28
inline BOOL IsSubtitlePreferenceSwitchedOn() { return FiveXInvoke<BOOL>(0x63BA19F5); } // 0x63BA19F5
inline VOID DisplayHud(BOOL Toggle) { FiveXInvoke<VOID>(0xD10E4E31, Toggle); } // 0xD10E4E31
inline VOID DisplayRadar(BOOL Toggle) { FiveXInvoke<VOID>(0x52816BD4, Toggle); } // 0x52816BD4
inline BOOL IsHudHidden() { return FiveXInvoke<BOOL>(0x40BADA1D); } // 0x40BADA1D
inline BOOL IsRadarHidden() { return FiveXInvoke<BOOL>(0x1AB3B954); } // 0x1AB3B954
inline VOID SetBlipRoute(Object blip, INT enabled) { FiveXInvoke<VOID>(0x3E160C90, blip, enabled); } // 0x3E160C90
inline VOID SetBlipRouteColour(Any p0, Any p1) { FiveXInvoke<VOID>(0xDDE7C65C, p0, p1); } // 0xDDE7C65C
inline VOID AddNextMessageToPreviousBriefs(Any p0) { FiveXInvoke<VOID>(0xB58B25BD, p0); } // 0xB58B25BD
inline VOID RespondingAsTemp(Any p0) { FiveXInvoke<VOID>(0xDCA3F423, p0); } // 0xDCA3F423
inline VOID SetRadarZoom(INT p0) { FiveXInvoke<VOID>(0x2A50D1A6, p0); } // 0x2A50D1A6
inline VOID GetHudColour(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0x63F66A0B, p0, p1, p2, p3, p4); } // 0x63F66A0B
inline VOID FlashAbilityBar(Any p0) { FiveXInvoke<VOID>(0x3648960D, p0); } // 0x3648960D
inline VOID SetAbilityBarValue(Any p0, Any p1) { FiveXInvoke<VOID>(0x24E53FD8, p0, p1); } // 0x24E53FD8
inline VOID FlashWantedDisplay(BOOL p0) { FiveXInvoke<VOID>(0x629F866B, p0); } // 0x629F866B
inline VOID SetTextJustification(INT justifyType) { FiveXInvoke<VOID>(0x68CDFA60, justifyType); } // 0x68CDFA60
inline VOID SetTextLeading(Any p0) { FiveXInvoke<VOID>(0x98CE21D4, p0); } // 0x98CE21D4
inline VOID SetTextProportional(Any p0) { FiveXInvoke<VOID>(0xF49D8A08, p0); } // 0xF49D8A08
inline VOID SetTextDropShadow() { FiveXInvoke<VOID>(0xE2A11511); } // 0xE2A11511
inline VOID SetTextEdge(Hash p0, INT p1, INT p2, INT p3, INT p4) { FiveXInvoke<VOID>(0x3F1A5DAB, p0, p1, p2, p3, p4); } // 0x3F1A5DAB
inline VOID SetTextRenderId(Any p0) { FiveXInvoke<VOID>(0xC5C3B7F3, p0); } // 0xC5C3B7F3
inline Any GetDefaultScriptRendertargetRenderId() { return FiveXInvoke<Any>(0x8188935F); } // 0x8188935F
inline Any RegisterNamedRendertarget(Any p0, Any p1) { return FiveXInvoke<Any>(0xFAE5D6F0, p0, p1); } // 0xFAE5D6F0
inline BOOL IsNamedRendertargetRegistered(Any p0) { return FiveXInvoke<BOOL>(0x284057F5, p0); } // 0x284057F5
inline Any ReleaseNamedRendertarget(Any p0) { return FiveXInvoke<Any>(0xD3F6C892, p0); } // 0xD3F6C892
inline VOID LinkNamedRendertarget(Any p0) { FiveXInvoke<VOID>(0x6844C4B9, p0); } // 0x6844C4B9
inline Any GetNamedRendertargetRenderId(Any p0) { return FiveXInvoke<Any>(0xF9D7A401, p0); } // 0xF9D7A401
inline BOOL IsNamedRendertargetLinked(Any p0) { return FiveXInvoke<BOOL>(0x8B52601F, p0); } // 0x8B52601F
inline VOID ClearHelp(INT Enable) { FiveXInvoke<VOID>(0xE6D85741, Enable); } // 0xE6D85741
inline BOOL IsHelpMessageOnScreen() { return FiveXInvoke<BOOL>(0x4B3C9CA9); } // 0x4B3C9CA9
inline BOOL IsHelpMessageBeingDisplayed() { return FiveXInvoke<BOOL>(0xA65F262A); } // 0xA65F262A
inline BOOL IsHelpMessageFadingOut() { return FiveXInvoke<BOOL>(0x3E50AE92); } // 0x3E50AE92
inline Any GetBlipInfoIdIterator() { return FiveXInvoke<Any>(0xB9827942); } // 0xB9827942
inline Any GetNumberOfActiveBlips() { return FiveXInvoke<Any>(0x144020FA); } // 0x144020FA
inline Any GetNextBlipInfoId(Any p0) { return FiveXInvoke<Any>(0x9356E92F, p0); } // 0x9356E92F
inline Any GetFirstBlipInfoId(Any p0) { return FiveXInvoke<Any>(0x64C0273D, p0); } // 0x64C0273D
inline Vector3 GetBlipInfoIdCoord(Any p0) { return FiveXInvoke<Vector3>(0xB7374A66, p0); } // 0xB7374A66
inline Any GetBlipInfoIdDisplay(Any p0) { return FiveXInvoke<Any>(0xD0FC19F4, p0); } // 0xD0FC19F4
inline Any GetBlipInfoIdType(Any p0) { return FiveXInvoke<Any>(0x501D7B4E, p0); } // 0x501D7B4E
inline Any GetBlipInfoIdEntityIndex(Any p0) { return FiveXInvoke<Any>(0xA068C40B, p0); } // 0xA068C40B
inline Any GetBlipInfoIdPickupIndex(Any p0) { return FiveXInvoke<Any>(0x86913D37, p0); } // 0x86913D37
inline Object GetBlipFromEntity(Entity entity) { return FiveXInvoke<Object>(0x005A2A47, entity); } // 0x005A2A47
inline Any AddBlipForRadius(FLOAT x, FLOAT y, FLOAT z, FLOAT r) { return FiveXInvoke<Any>(0x4626756C, x, y, z, r); } // 0x4626756C
inline Any AddBlipForEntity(Entity entity) { return FiveXInvoke<Any>(0x30822554, entity); } // 0x30822554
inline Any AddBlipForPickup(Any p0) { return FiveXInvoke<Any>(0x16693C3A, p0); } // 0x16693C3A
inline Any AddBlipForCoord(FLOAT x, FLOAT y, FLOAT z) { return FiveXInvoke<Any>(0xC6F43D0E, x, y, z); } // 0xC6F43D0E
inline VOID SetBlipCoords(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x680A34D4, p0, p1, p2, p3); } // 0x680A34D4
inline Vector3 GetBlipCoords(Any p0) { return FiveXInvoke<Vector3>(0xEF6FF47B, p0); } // 0xEF6FF47B
inline VOID SetBlipSprite(Object blip, INT spriteId) { FiveXInvoke<VOID>(0x8DBBB0B9, blip, spriteId); } // 0x8DBBB0B9
inline Any GetBlipSprite(Any p0) { return FiveXInvoke<Any>(0x72FF2E73, p0); } // 0x72FF2E73
inline VOID SetBlipNameFromTextFile(INT BlipID, char* blipname) { FiveXInvoke<VOID>(0xAC8A5461, BlipID, blipname); } // 0xAC8A5461
inline VOID SetBlipNameToPlayerName(Any p0, Any p1) { FiveXInvoke<VOID>(0x03A0B8F9, p0, p1); } // 0x03A0B8F9
inline VOID SetBlipAlpha(Blip blip, int alpha) { FiveXInvoke<VOID>(0xA791FCCD, blip, alpha); } // 0xA791FCCD
inline Any GetBlipAlpha(Any p0) { return FiveXInvoke<Any>(0x297AF6C8, p0); } // 0x297AF6C8
inline VOID SetBlipFade(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xA5999031, p0, p1, p2); } // 0xA5999031
inline VOID SetBlipRotation(Any p0, Any p1) { FiveXInvoke<VOID>(0x6B8F44FE, p0, p1); } // 0x6B8F44FE
inline VOID SetBlipFlashTimer(Any p0, Any p1) { FiveXInvoke<VOID>(0x8D5DF611, p0, p1); } // 0x8D5DF611
inline VOID SetBlipFlashInterval(Any p0, Any p1) { FiveXInvoke<VOID>(0xEAF67377, p0, p1); } // 0xEAF67377
inline VOID SetBlipColour(INT BlipID, INT Color) { FiveXInvoke<VOID>(0xBB3C5A41, BlipID, Color); } // 0xBB3C5A41
inline VOID SetBlipSecondaryColour(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0xC6384D32, p0, p1, p2, p3); } // 0xC6384D32
inline Any GetBlipColour(Any p0) { return FiveXInvoke<Any>(0xDD6A1E54, p0); } // 0xDD6A1E54
inline Any GetBlipHudColour(Any p0) { return FiveXInvoke<Any>(0xE88B4BC2, p0); } // 0xE88B4BC2
inline BOOL IsBlipShortRange(Any p0) { return FiveXInvoke<BOOL>(0x1226765A, p0); } // 0x1226765A
inline BOOL IsBlipOnMinimap(Any p0) { return FiveXInvoke<BOOL>(0x258CBA3A, p0); } // 0x258CBA3A
inline VOID SetBlipHighDetail(Any p0, Any p1) { FiveXInvoke<VOID>(0xD5842BFF, p0, p1); } // 0xD5842BFF
inline VOID SetBlipAsMissionCreatorBlip(Any p0, Any p1) { FiveXInvoke<VOID>(0x802FB686, p0, p1); } // 0x802FB686
inline BOOL IsMissionCreatorBlip(Any p0) { return FiveXInvoke<BOOL>(0x24ACC4E9, p0); } // 0x24ACC4E9
inline Any DisableBlipNameForVar() { return FiveXInvoke<Any>(0xFFD7476C); } // 0xFFD7476C
inline VOID SetBlipFlashes(Any p0, Any p1) { FiveXInvoke<VOID>(0xC0047F15, p0, p1); } // 0xC0047F15
inline VOID SetBlipFlashesAlternate(INT BlipID, BOOL p1) { FiveXInvoke<VOID>(0x1A81202B, BlipID, p1); } // 0x1A81202B
inline BOOL IsBlipFlashing(Any p0) { return FiveXInvoke<BOOL>(0x52E111D7, p0); } // 0x52E111D7
inline VOID SetBlipAsShortRange(Any p0, Any p1) { FiveXInvoke<VOID>(0x5C67725E, p0, p1); } // 0x5C67725E
inline VOID SetBlipScale(INT BlipID, FLOAT Scale) { FiveXInvoke<VOID>(0x1E6EC434, BlipID, Scale); } // 0x1E6EC434
inline VOID SetBlipPriority(Any p0, Any p1) { FiveXInvoke<VOID>(0xCE87DA6F, p0, p1); } // 0xCE87DA6F
inline VOID SetBlipDisplay(Object blip, Any p1) { FiveXInvoke<VOID>(0x2B521F91, blip, p1); } // 0x2B521F91
inline VOID SetBlipCategory(Any p0, Any p1) { FiveXInvoke<VOID>(0xEF72F533, p0, p1); } // 0xEF72F533
inline VOID RemoveBlip(INT* BlipID) { FiveXInvoke<VOID>(0xD8C3C1CD, BlipID); } // 0xD8C3C1CD
inline VOID SetBlipAsFriendly(INT BlipID, BOOL toggle) { FiveXInvoke<VOID>(0xF290CFD8, BlipID, toggle); } // 0xF290CFD8
inline VOID PulseBlip(Any p0) { FiveXInvoke<VOID>(0x44253855, p0); } // 0x44253855
inline VOID ShowNumberOnBlip(Any p0, Any p1) { FiveXInvoke<VOID>(0x7BFC66C6, p0, p1); } // 0x7BFC66C6
inline VOID HideNumberOnBlip(Any p0) { FiveXInvoke<VOID>(0x0B6D610D, p0); } // 0x0B6D610D
inline BOOL DoesBlipExist(Any p0) { return FiveXInvoke<BOOL>(0xAE92DD96, p0); } // 0xAE92DD96
inline VOID SetWaypointOff() { FiveXInvoke<VOID>(0xB3496E1B); } // 0xB3496E1B
inline VOID DeleteWaypoint() { FiveXInvoke<VOID>(0x62BABF2C); } // 0x62BABF2C
inline VOID RefreshWaypoint() { FiveXInvoke<VOID>(0xB395D753); } // 0xB395D753
inline BOOL IsWaypointActive() { return FiveXInvoke<BOOL>(0x5E4DF47B); } // 0x5E4DF47B
inline VOID SetNewWaypoint(float x, float y) { FiveXInvoke<VOID>(0x8444E1F0, x, y); } // 0x8444E1F0
inline VOID SetBlipBright(Any p0, Any p1) { FiveXInvoke<VOID>(0x72BEE6DF, p0, p1); } // 0x72BEE6DF
inline VOID SetBlipShowCone(Any p0, Any p1) { FiveXInvoke<VOID>(0xFF545AD8, p0, p1); } // 0xFF545AD8
inline Any SetMinimapComponent(INT componentID, BOOL toggle, INT hudColor) { return FiveXInvoke<Any>(0x419DCDC4, componentID, toggle, hudColor); } // 0x419DCDC4
inline Any GetMainPlayerBlipId() { return FiveXInvoke<Any>(0xAB93F020); } // 0xAB93F020
inline VOID HideLoadingOnFadeThisFrame() { FiveXInvoke<VOID>(0x35087963); } // 0x35087963
inline VOID SetRadarAsInteriorThisFrame(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0x6F2626E1, p0, p1, p2, p3, p4); } // 0x6F2626E1
inline VOID SetRadarAsExteriorThisFrame() { FiveXInvoke<VOID>(0x39ABB10E); } // 0x39ABB10E
inline VOID SetWidescreenFormat(Any p0) { FiveXInvoke<VOID>(0xF016E08F, p0); } // 0xF016E08F
inline VOID DisplayAreaName(Any p0) { FiveXInvoke<VOID>(0x489FDD41, p0); } // 0x489FDD41
inline VOID DisplayCash(Any p0) { FiveXInvoke<VOID>(0x0049DF83, p0); } // 0x0049DF83
inline VOID DisplayAmmoThisFrame(Any p0) { FiveXInvoke<VOID>(0x60693CEE, p0); } // 0x60693CEE
inline VOID DisplaySniperScopeThisFrame() { FiveXInvoke<VOID>(0xBC6C73CB); } // 0xBC6C73CB
inline VOID HideHudAndRadarThisFrame() { FiveXInvoke<VOID>(0xB75D4AD2); } // 0xB75D4AD2
inline VOID SetMultiplayerBankCash() { FiveXInvoke<VOID>(0x2C842D03); } // 0x2C842D03
inline VOID RemoveMultiplayerBankCash() { FiveXInvoke<VOID>(0x728B4EF4); } // 0x728B4EF4
inline VOID SetMultiplayerHudCash(Any p0, Any p1) { FiveXInvoke<VOID>(0xA8DB435E, p0, p1); } // 0xA8DB435E
inline VOID RemoveMultiplayerHudCash() { FiveXInvoke<VOID>(0x07BF4A7D); } // 0x07BF4A7D
inline VOID HideHelpTextThisFrame() { FiveXInvoke<VOID>(0xF3807BED); } // 0xF3807BED
inline VOID DisplayHelpTextThisFrame(Any p0, Any p1) { FiveXInvoke<VOID>(0x18E3360A, p0, p1); } // 0x18E3360A
inline VOID SetGpsFlags(Any p0, Any p1) { FiveXInvoke<VOID>(0x60539BAB, p0, p1); } // 0x60539BAB
inline VOID ClearGpsFlags() { FiveXInvoke<VOID>(0x056AFCE6); } // 0x056AFCE6
inline VOID ClearGpsRaceTrack() { FiveXInvoke<VOID>(0x40C59829); } // 0x40C59829
inline VOID ClearGpsPlayerWaypoint() { FiveXInvoke<VOID>(0x0B9C7FC2); } // 0x0B9C7FC2
inline VOID SetGpsFlashes(Any p0) { FiveXInvoke<VOID>(0xE991F733, p0); } // 0xE991F733
inline VOID FlashMinimapDisplay() { FiveXInvoke<VOID>(0xB8359952); } // 0xB8359952
inline VOID ToggleStealthRadar(Any p0) { FiveXInvoke<VOID>(0xC68D47C4, p0); } // 0xC68D47C4
inline VOID KeyHudColour(Any p0, Any p1) { FiveXInvoke<VOID>(0xD5BFCADB, p0, p1); } // 0xD5BFCADB
inline VOID SetMissionName(Any p0, Any p1) { FiveXInvoke<VOID>(0x68DCAE10, p0, p1); } // 0x68DCAE10
inline VOID SetMinimapBlockWaypoint(Any p0) { FiveXInvoke<VOID>(0xA41C3B62, p0); } // 0xA41C3B62
inline VOID SetMinimapInPrologue(BOOL p0) { FiveXInvoke<BOOL>(0x02F5F1D1, p0); } // 0x02F5F1D1
inline VOID SetMinimapHideFow(BOOL p0) { FiveXInvoke<BOOL>(0xD8D77733, p0); } // 0xD8D77733
inline VOID LockMinimapAngle(Any p0) { FiveXInvoke<VOID>(0xDEC733E4, p0); } // 0xDEC733E4
inline VOID UnlockMinimapAngle() { FiveXInvoke<VOID>(0x742043F9); } // 0x742043F9
inline VOID LockMinimapPosition(FLOAT p0, FLOAT p1) { FiveXInvoke<FLOAT>(0xB9632A91, p0, p1); } // 0xB9632A91
inline VOID UnlockMinimapPosition() { FiveXInvoke<VOID>(0x5E8E6F54); } // 0x5E8E6F54
inline VOID SetBigmapActive(BOOL p0, BOOL p1) { FiveXInvoke<BOOL>(0x08EB83D2, p0, p1); } // 0x08EB83D2
inline BOOL IsHudComponentActive(INT p0) { return FiveXInvoke<BOOL>(0x6214631F, p0); } // 0x6214631F
inline BOOL IsScriptedHudComponentActive(Any p0) { return FiveXInvoke<BOOL>(0x2B86F382, p0); } // 0x2B86F382
inline VOID HideScriptedHudComponentThisFrame(Any p0) { FiveXInvoke<VOID>(0x31ABA127, p0); } // 0x31ABA127
inline VOID HideHudComponentThisFrame(Any p0) { FiveXInvoke<VOID>(0xDB2D0762, p0); } // 0xDB2D0762
inline VOID ShowHudComponentThisFrame(Any p0) { FiveXInvoke<VOID>(0x95E1546E, p0); } // 0x95E1546E
inline VOID HideAreaAndVehicleNameThisFrame() { FiveXInvoke<VOID>(0x52746FE1); } // 0x52746FE1
inline VOID ResetReticuleValues() { FiveXInvoke<VOID>(0xBE27AA3F); } // 0xBE27AA3F
inline VOID ResetHudComponentValues(Any p0) { FiveXInvoke<VOID>(0xD15B46DA, p0); } // 0xD15B46DA
inline VOID SetHudComponentPosition(INT p0, FLOAT p1, FLOAT p2) { FiveXInvoke<VOID>(0x2F3A0D15, p0, p1, p2); } // 0x2F3A0D15
inline Vector3 GetHudComponentPosition(Any p0) { return FiveXInvoke<Vector3>(0x080DCED6, p0); } // 0x080DCED6
inline VOID ClearFloatingHelp(Any p0, Any p1) { FiveXInvoke<VOID>(0xB181F88F, p0, p1); } // 0xB181F88F
inline Any AddTrevorRandomModifier(Any p0) { return FiveXInvoke<Any>(0x63959059, p0); } // 0x63959059
inline Any GetCurrentWebsiteId() { return FiveXInvoke<Any>(0x42A55B14); } // 0x42A55B14
inline VOID SetWarningMessage(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { FiveXInvoke<VOID>(0xBE699BDE, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xBE699BDE
inline VOID SetDanceMappers(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { FiveXInvoke<VOID>(0x749929D3, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x749929D3
inline VOID ActivateFrontendMenu(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x01D83872, p0, p1, p2); } // 0x01D83872
inline VOID RestartFrontendMenu(Any p0, Any p1) { FiveXInvoke<VOID>(0xB07DAF98, p0, p1); } // 0xB07DAF98
inline VOID SetPauseMenuActive(Any p0) { FiveXInvoke<VOID>(0x1DCD878E, p0); } // 0x1DCD878E
inline VOID DisableFrontendThisFrame() { FiveXInvoke<VOID>(0xD86A029E); } // 0xD86A029E
inline VOID SetFrontendActive(Any p0) { FiveXInvoke<VOID>(0x81E1AD32, p0); } // 0x81E1AD32
inline BOOL IsPauseMenuActive() { return FiveXInvoke<BOOL>(0xD3600591); } // 0xD3600591
inline BOOL Ui3dSceneIsAvailable() { return FiveXInvoke<BOOL>(0xE40A0F1A); } // UI3DSCENE_IS_AVAILABLE
inline BOOL Ui3dScenePushPreset(const CHAR* presetName) { return FiveXInvoke<BOOL>(0x2E7D9B98, presetName); } // UI3DSCENE_PUSH_PRESET
inline BOOL Ui3dSceneAssignPedToSlot(const CHAR* presetName, Ped ped, INT slot, FLOAT x, FLOAT y, FLOAT z) { return FiveXInvoke<BOOL>(0x9A0E3BFE, presetName, ped, slot, x, y, z); } // UI3DSCENE_ASSIGN_PED_TO_SLOT
inline VOID Ui3dSceneClearPatchedData() { FiveXInvoke<VOID>(0x431AA036); } // UI3DSCENE_CLEAR_PATCHED_DATA
inline VOID Ui3dSceneMakePushedPresetPersistent(BOOL enabled) { FiveXInvoke<VOID>(0x24A7A7F6, enabled); } // UI3DSCENE_MAKE_PUSHED_PRESET_PERSISTENT
inline VOID SetPauseMenuPedLighting(BOOL state) { FiveXInvoke<VOID>(0x127310EB, state); } // SET_PAUSE_MENU_PED_LIGHTING
inline Any GetPauseMenuState() { return FiveXInvoke<Any>(0x92F50134); } // 0x92F50134
inline BOOL IsPauseMenuRestarting() { return FiveXInvoke<BOOL>(0x3C4CF4D9); } // 0x3C4CF4D9
inline VOID ObjectDecalToggle(Any p0) { FiveXInvoke<VOID>(0x0029046E, p0); } // 0x0029046E
inline VOID EnableDeathbloodSeethrough(Any p0) { FiveXInvoke<VOID>(0x15B24768, p0); } // 0x15B24768
inline Any SetUseridsUihidden(Any p0, Any p1) { return FiveXInvoke<Any>(0x4370999E, p0, p1); } // 0x4370999E
inline VOID ClearPedInPauseMenu() { FiveXInvoke<VOID>(0x28058ACF); } // 0x28058ACF
inline VOID GivePedToPauseMenu(Any p0, Any p1) { FiveXInvoke<VOID>(0x2AD2C9CE, p0, p1); } // 0x2AD2C9CE
inline BOOL DoesPedHaveAiBlip(Any p0) { return FiveXInvoke<BOOL>(0x3BE1257F, p0); } // 0x3BE1257F
inline VOID HideSpecialAbilityLockonOperation(Any p0, Any p1) { FiveXInvoke<VOID>(0x872C2CFB, p0, p1); } // 0x872C2CFB
inline INT GetVehicleModelValue(Hash vehicleModel) { return FiveXInvoke<int>(0x58FEFC3D, vehicleModel); } // 0x5873C14A52D74236 0x58FEFC3D b463
inline char* GetDisplayNameFromVehicleModel1(Hash p0) { return FiveXInvoke<char*>(0xEC86DF39, p0); } // 0xEC86DF39
inline Vehicle CreateVehicle2(Hash VehicleHash, FLOAT xCoord, FLOAT yCoord, FLOAT zCoord, FLOAT Heading, BOOL networkHandle, BOOL vehiclehandle) { return FiveXInvoke<Vehicle>(0xDD75460A, VehicleHash, xCoord, yCoord, zCoord, Heading, networkHandle, vehiclehandle); } // 0xDD75460A
inline VOID SetVehicleEngineTorqueMultiplier(Vehicle vehicle, FLOAT value) { FiveXInvoke<VOID>(0x642DA5AA, vehicle, value); } // 0x642DA5AA 0x642DA5AA
inline VOID SetVehicleEnginePowerMultiplier(Vehicle vehicle, FLOAT value) { FiveXInvoke<VOID>(0xE943B09C, vehicle, value); } // 0xE943B09C 0xE943B09C
inline VOID DeleteVehicle(DWORD* vehicle) { FiveXInvoke<VOID>(0x9803AF60, vehicle); } // 0x9803AF60
inline VOID SetVehicleAllowNoPassengersLockon(Any p0, Any p1) { FiveXInvoke<VOID>(0x8BAAC437, p0, p1); } // 0x8BAAC437
inline BOOL IsVehicleModel(Vehicle hash, BOOL toggle) { return FiveXInvoke<BOOL>(0x013B10B6, hash, toggle); } // 0x013B10B6
inline BOOL DoesScriptVehicleGeneratorExist(Any p0) { return FiveXInvoke<BOOL>(0xF6BDDA30, p0); } // 0xF6BDDA30
inline Any CreateScriptVehicleGenerator(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13, Any p14, Any p15, Any p16) { return FiveXInvoke<Any>(0x25A9A261, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16); } // 0x25A9A261
inline VOID DeleteScriptVehicleGenerator(Vehicle p0) { FiveXInvoke<VOID>(0xE4328E3F, p0); } // 0xE4328E3F
inline VOID SetScriptVehicleGenerator(Any p0, Any p1) { FiveXInvoke<VOID>(0x40D73747, p0, p1); } // 0x40D73747
inline VOID SetAllVehicleGeneratorsActiveInArea(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { FiveXInvoke<VOID>(0xB4E0E69A, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xB4E0E69A
inline VOID SetAllVehicleGeneratorsActive() { FiveXInvoke<VOID>(0xAB1FDD76); } // 0xAB1FDD76
inline VOID SetAllLowPriorityVehicleGeneratorsActive(Any p0) { FiveXInvoke<VOID>(0x87F767F2, p0); } // 0x87F767F2
inline BOOL SetVehicleOnGroundProperly(Vehicle vehicle) { return FiveXInvoke<BOOL>(0xE14FDBA6, vehicle); } // 0xE14FDBA6
inline Any SetAllVehiclesSpawn(Any p0, Any p1, Any p2, Any p3) { return FiveXInvoke<Any>(0xA0909ADB, p0, p1, p2, p3); } // 0xA0909ADB
inline BOOL IsVehicleStuckOnRoof(Vehicle Hash) { return FiveXInvoke<BOOL>(0x18D07C6C, Hash); } // 0x18D07C6C
inline VOID AddVehicleUpsidedownCheck(Any p0) { FiveXInvoke<VOID>(0x3A13D384, p0); } // 0x3A13D384
inline VOID RemoveVehicleUpsidedownCheck(Any p0) { FiveXInvoke<VOID>(0xF390BA1B, p0); } // 0xF390BA1B
inline BOOL IsVehicleStopped(Any p0) { return FiveXInvoke<BOOL>(0x655F072C, p0); } // 0x655F072C
inline INT GetVehicleNumberOfPassengers(Vehicle Vehicle) { return FiveXInvoke<int>(0x1EF20849, Vehicle); } // 0x1EF20849
inline INT GetVehicleMaxNumberOfPassengers(Vehicle Vehicle) { return FiveXInvoke<int>(0x0A2FC08C, Vehicle); } // 0x0A2FC08C
inline INT GetVehicleModelMaxNumberOfPassengers(Hash VehicleModel) { return FiveXInvoke<int>(0x838F7BF7, VehicleModel); } // 0x838F7BF7
inline VOID SetVehicleDensityMultiplierThisFrame(FLOAT multiplier) { FiveXInvoke<VOID>(0xF4187E51, multiplier); } // 0xF4187E51
inline VOID SetRandomVehicleDensityMultiplierThisFrame(FLOAT multiplier) { FiveXInvoke<VOID>(0x543F712B, multiplier); } // 0x543F712B
inline VOID SetParkedVehicleDensityMultiplierThisFrame(Any p0) { FiveXInvoke<VOID>(0xDD46CEBE, p0); } // 0xDD46CEBE
inline VOID SetFarDrawVehicles(Any p0) { FiveXInvoke<VOID>(0x9F019C49, p0); } // 0x9F019C49
inline VOID SetNumberOfParkedVehicles(INT value) { FiveXInvoke<VOID>(0x206A58E8, value); } // 0x206A58E8
inline VOID SetVehicleDoorsLocked(Vehicle hash, INT door) { FiveXInvoke<VOID>(0x4CDD35D0, hash, door); } // 0x4CDD35D0
inline VOID SetPedTargettableVehicleDestroy(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xD61D182D, p0, p1, p2); } // 0xD61D182D
inline VOID DisableVehicleImpactExplosionActivation(Any p0, Any p1) { FiveXInvoke<VOID>(0xC54156A9, p0, p1); } // 0xC54156A9
inline VOID SetVehicleDoorsLockedForPlayer(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x49829236, p0, p1, p2); } // 0x49829236
inline Any GetVehicleDoorsLockedForPlayer(Any p0, Any p1) { return FiveXInvoke<Any>(0x1DC50247, p0, p1); } // 0x1DC50247
inline VOID SetVehicleDoorsLockedForAllPlayers(Any p0, Any p1) { FiveXInvoke<VOID>(0x891BA8A4, p0, p1); } // 0x891BA8A4
inline VOID SetVehicleDoorsLockedForTeam(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x4F85E783, p0, p1, p2); } // 0x4F85E783
inline VOID ExplodeVehicle(Vehicle vehicle, BOOL b1, BOOL b2) { FiveXInvoke<VOID>(0xBEDEACEB, vehicle, b1, b2); } // 0xBEDEACEB
inline VOID SetVehicleOutOfControl(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x3764D734, p0, p1, p2); } // 0x3764D734
inline VOID SetVehicleTimedExplosion(Vehicle vehicle, Ped ped, BOOL toggle) { FiveXInvoke<VOID>(0xDB8CB8E2, vehicle, ped, toggle); } // 0xDB8CB8E2
inline VOID SetTaxiLights(Vehicle vehicle, BOOL state) { FiveXInvoke<VOID>(0x68639D85, vehicle, state); } // 0x68639D85
inline BOOL IsTaxiLightOn(Vehicle vehicle) { return FiveXInvoke<BOOL>(0x6FC4924A, vehicle); } // 0x6FC4924A
inline BOOL IsVehicleInGarageArea(Any p0, Any p1) { return FiveXInvoke<BOOL>(0xA90EC257, p0, p1); } // 0xA90EC257
inline VOID SetVehicleColours(Vehicle vehicle, int colorPrimary, int colorSecondary) { FiveXInvoke<VOID>(0x57F24253, vehicle, colorPrimary, colorSecondary); } // 0x57F24253
inline VOID SetVehicleFullbeam(Vehicle vehicle, BOOL state) { FiveXInvoke<VOID>(0x9C49CC15, vehicle, state); } // 0x9C49CC15
inline VOID SteerUnlockBias(Any p0, Any p1) { FiveXInvoke<VOID>(0xA59E3DCD, p0, p1); } // 0xA59E3DCD
inline VOID SetVehicleCustomPrimaryColour(Vehicle vehicle, INT r, INT g, INT b) { FiveXInvoke<VOID>(0x8DF9F9BC, vehicle, r, g, b); } // 0x8DF9F9BC
inline INT SetVehicleCustomPrimaryColour2(Vehicle vehicle, INT r, INT g, INT b) { return FiveXInvoke<int>(0x8DF9F9BC, vehicle, r, g, b); } // 0x8DF9F9BC
inline VOID GetVehicleCustomPrimaryColour(Vehicle vehicle, INT r, INT g, INT b) { FiveXInvoke<VOID>(0x1C2B9FEF, vehicle, r, g, b); } // 0x1C2B9FEF
inline VOID ClearVehicleCustomPrimaryColour(Vehicle vehicle) { FiveXInvoke<VOID>(0x51E1E33D, vehicle); } // 0x51E1E33D
inline BOOL GetIsVehiclePrimaryColourCustom(Vehicle vehicle) { return FiveXInvoke<BOOL>(0xD7EC8760, vehicle); } // 0xD7EC8760
inline VOID SetVehicleCustomSecondaryColour(Vehicle vehicle, INT r, INT g, INT b) { FiveXInvoke<VOID>(0x9D77259E, vehicle, r, g, b); } // 0x9D77259E
inline VOID GetVehicleCustomSecondaryColour(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x3FF247A2, p0, p1, p2, p3); } // 0x3FF247A2
inline VOID ClearVehicleCustomSecondaryColour(Vehicle vehicle) { FiveXInvoke<VOID>(0x7CE00B29, vehicle); } // 0x7CE00B29
inline BOOL GetIsVehicleSecondaryColourCustom(Vehicle vehicle) { return FiveXInvoke<BOOL>(0x288AD228, vehicle); } // 0x288AD228
inline VOID SetVehiclePaintFade(Vehicle p0, FLOAT p1) { FiveXInvoke<VOID>(0x8332730C, p0, p1); } // 0x8332730C
inline VOID SetCanResprayVehicle(Vehicle vehicle, BOOL state) { FiveXInvoke<VOID>(0x37677590, vehicle, state); } // 0x37677590
inline VOID SetBoatAnchor(Vehicle vehicle, BOOL p1) { FiveXInvoke<VOID>(0xA3906284, vehicle, p1); } // 0xA3906284
inline VOID SetVehicleSiren(Vehicle vehicle, BOOL siren) { FiveXInvoke<VOID>(0x4AC1EFC7, vehicle, siren); } // 0x4AC1EFC7
inline BOOL IsVehicleSirenOn(Vehicle vehicle) { return FiveXInvoke<BOOL>(0x25EB5873, vehicle); } // 0x25EB5873
inline VOID SetVehicleStrong(Vehicle vehicle, BOOL p0) { FiveXInvoke<VOID>(0xC758D19F, vehicle, p0); } // 0xC758D19F
inline VOID RemoveVehicleStuckCheck(Any p0) { FiveXInvoke<VOID>(0x81594917, p0); } // 0x81594917
inline VOID GetVehicleColours(Vehicle vehicle, int* colorPrimary, int* colorSecondary) { FiveXInvoke<VOID>(0x40D82D88, vehicle, colorPrimary, colorSecondary); } // 0x40D82D88
inline BOOL IsVehicleSeatFree(Vehicle vehicle, INT seatIndex) { return FiveXInvoke<BOOL>(0xDAF42B02, vehicle, seatIndex); } // 0xDAF42B02
inline Ped GetPedInVehicleSeat(Vehicle vehicle, INT index) { return FiveXInvoke<Ped>(0x388FDE9A, vehicle, index); } // 0x388FDE9A
inline Any GetVehicleLightsState(Any p0, Any p1, Any p2) { return FiveXInvoke<Any>(0x7C278621, p0, p1, p2); } // 0x7C278621
inline BOOL IsVehicleTyreBurst(Vehicle vehicle, INT wheelID, Any p2) { return FiveXInvoke<BOOL>(0x48C80210, vehicle, wheelID, p2); } // 0x48C80210
inline VOID SetVehicleForwardSpeed(Vehicle vehicle, FLOAT speed) { FiveXInvoke<VOID>(0x69880D14, vehicle, speed); } // 0x69880D14
inline Any SetPedEnabledBikeRingtone(Any p0, Any p1) { return FiveXInvoke<Any>(0x7FB25568, p0, p1); } // 0x7FB25568
inline VOID SetVehicleTyreBurst(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x89D28068, p0, p1, p2, p3); } // 0x89D28068
inline VOID SetVehicleDoorsShut(Vehicle vehicle, INT index) { FiveXInvoke<VOID>(0xBB1FF6E7, vehicle, index); } // 0xBB1FF6E7
inline VOID SetVehicleTyresCanBurst(Vehicle vehicle, BOOL value) { FiveXInvoke<VOID>(0xA198DB54, vehicle, value); } // 0xA198DB54
inline BOOL GetVehicleTyresCanBurst(Vehicle vehicle) { return FiveXInvoke<BOOL>(0x4D76CD2F, vehicle); } // 0x4D76CD2F
inline VOID SetVehicleWheelsCanBreak(Vehicle vehicle, BOOL enabled) { FiveXInvoke<VOID>(0x829ED654, vehicle, enabled); } // 0x829ED654
inline VOID SetVehicleDoorOpen(Vehicle vehicle, INT doorIndex, BOOL loose, BOOL openInstantly) { FiveXInvoke<VOID>(0xBB75D38B, vehicle, doorIndex, loose, openInstantly); } // 0xBB75D38B
inline VOID RemoveVehicleWindow(Vehicle vehicle, INT windowIndex) { FiveXInvoke<VOID>(0xBB8104A3, vehicle, windowIndex); } // 0xBB8104A3
inline VOID RollDownWindows(Vehicle vehicle) { FiveXInvoke<VOID>(0x51A16DC6, vehicle); } // 0x51A16DC6
inline VOID RollDownWindow(Vehicle vehicle, INT windowIndex) { FiveXInvoke<VOID>(0xF840134C, vehicle, windowIndex); } // 0xF840134C
inline VOID RollUpWindow(Vehicle vehicle, INT windowIndex) { FiveXInvoke<VOID>(0x83B7E06A, vehicle, windowIndex); } // 0x83B7E06A
inline VOID SmashVehicleWindow(Vehicle vehicle, INT index) { FiveXInvoke<VOID>(0xDDD9A8C2, vehicle, index); } // 0xDDD9A8C2
inline VOID FixVehicleWindow(Vehicle vehicle, INT index) { FiveXInvoke<VOID>(0x6B8E990D, vehicle, index); } // 0x6B8E990D
inline VOID DetachVehicleWindscreen(Vehicle vehicleHandle) { FiveXInvoke<VOID>(0xCC95C96B, vehicleHandle); } // 0xCC95C96B
inline VOID SetVehicleLights(Any p0, Any p1) { FiveXInvoke<VOID>(0xE8930226, p0, p1); } // 0xE8930226
inline VOID SetVehicleAlarm(Vehicle vehicle, BOOL state) { FiveXInvoke<VOID>(0x24877D84, vehicle, state); } // 0x24877D84
inline VOID StartVehicleAlarm(Vehicle vehicle) { FiveXInvoke<VOID>(0x5B451FF7, vehicle); } // 0x5B451FF7
inline BOOL IsVehicleAlarmActivated(Vehicle vehicle) { return FiveXInvoke<BOOL>(0xF2630A4C, vehicle); } // 0xF2630A4C
inline VOID SetVehicleInteriorlight(Vehicle vehicle, BOOL Toggle) { FiveXInvoke<VOID>(0x9AD1FE1E, vehicle, Toggle); } // 0x9AD1FE1E
inline VOID SetVehicleLightMultiplier(Vehicle vehicle, FLOAT multiplier) { FiveXInvoke<VOID>(0x48039D6A, vehicle, multiplier); } // 0x48039D6A
inline VOID AttachVehicleToTrailer(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x2133977F, p0, p1, p2); } // 0x2133977F
inline VOID DetachVehicleFromTrailer(Any p0) { FiveXInvoke<VOID>(0xB5DBF91D, p0); } // 0xB5DBF91D
inline BOOL IsVehicleAttachedToTrailer(Vehicle vehicle) { return FiveXInvoke<BOOL>(0xE142BBCC, vehicle); } // 0xE142BBCC
inline VOID SetVehicleTyreFixed(Vehicle vehicle, INT tyreIndex) { FiveXInvoke<VOID>(0xA42EFA6B, vehicle, tyreIndex); } // 0xA42EFA6B
inline VOID SetVehicleNumberPlateText(Vehicle vehicle, char* plateText) { FiveXInvoke<VOID>(0x400F9556, vehicle, plateText); } // 0x400F9556
inline char* GetVehicleNumberPlateText(Vehicle vehicle) { return FiveXInvoke<char*>(0xE8522D58, vehicle); } // 0xE8522D58
inline Any GetNumberOfVehicleNumberPlates() { return FiveXInvoke<Any>(0xD24BC1AE); } // 0xD24BC1AE
inline VOID SetVehicleNumberPlateTextIndex(Vehicle vehicle, INT PlateType) { FiveXInvoke<VOID>(0xA1A1890E, vehicle, PlateType); } // 0xA1A1890E
inline INT GetVehicleNumberPlateTextIndex(Vehicle vehicle) { return FiveXInvoke<int>(0x499747B6, vehicle); } // 0x499747B6
inline VOID SetRandomTrains(Any p0) { FiveXInvoke<VOID>(0xD461CA7F, p0); } // 0xD461CA7F
inline Any CreateMissionTrain(Any p0, Any p1, Any p2, Any p3, Any p4) { return FiveXInvoke<Any>(0xD4C2EAFD, p0, p1, p2, p3, p4); } // 0xD4C2EAFD
inline VOID SwitchTrainTrack(Any p0, Any p1) { FiveXInvoke<VOID>(0x68BFDD61, p0, p1); } // 0x68BFDD61
inline VOID DeleteAllTrains() { FiveXInvoke<VOID>(0x83DE7ABF); } // 0x83DE7ABF
inline VOID SetTrainSpeed(Any p0, Any p1) { FiveXInvoke<VOID>(0xDFC35E4D, p0, p1); } // 0xDFC35E4D
inline VOID SetTrainCruiseSpeed(Any p0, Any p1) { FiveXInvoke<VOID>(0xB507F51D, p0, p1); } // 0xB507F51D
inline VOID SetRandomBoats(Any p0) { FiveXInvoke<VOID>(0xB505BD89, p0); } // 0xB505BD89
inline VOID SetGarbageTrucks(Any p0) { FiveXInvoke<VOID>(0xD9ABB0FF, p0); } // 0xD9ABB0FF
inline BOOL DoesVehicleHaveStuckVehicleCheck(Any p0) { return FiveXInvoke<BOOL>(0x5D91D9AC, p0); } // 0x5D91D9AC
inline Any GetVehicleRecordingId(Any p0, Any p1) { return FiveXInvoke<Any>(0x328D601D, p0, p1); } // 0x328D601D
inline VOID RequestVehicleRecording(Any p0, Any p1) { FiveXInvoke<VOID>(0x91AFEFD9, p0, p1); } // 0x91AFEFD9
inline BOOL HasVehicleRecordingBeenLoaded(Any p0, Any p1) { return FiveXInvoke<BOOL>(0xF52CD7F5, p0, p1); } // 0xF52CD7F5
inline VOID RemoveVehicleRecording(Any p0, Any p1) { FiveXInvoke<VOID>(0xD3C05B00, p0, p1); } // 0xD3C05B00
inline Vector3 GetPositionOfVehicleRecordingAtTime(Any p0, Any p1, Any p2) { return FiveXInvoke<Vector3>(0x7178558D, p0, p1, p2); } // 0x7178558D
inline Vector3 GetRotationOfVehicleRecordingAtTime(Any p0, Any p1, Any p2) { return FiveXInvoke<Vector3>(0xD96DEC68, p0, p1, p2); } // 0xD96DEC68
inline Any GetTotalDurationOfVehicleRecordingId(Any p0) { return FiveXInvoke<Any>(0x7116785E, p0); } // 0x7116785E
inline Any GetTotalDurationOfVehicleRecording(Any p0, Any p1) { return FiveXInvoke<Any>(0x5B35EEB7, p0, p1); } // 0x5B35EEB7
inline Any GetPositionInRecording(Any p0) { return FiveXInvoke<Any>(0x7DCD644C, p0); } // 0x7DCD644C
inline Any GetTimePositionInRecording(Any p0) { return FiveXInvoke<Any>(0xF8C3E4A2, p0); } // 0xF8C3E4A2
inline VOID StartPlaybackRecordedVehicle(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0xCF614CA8, p0, p1, p2, p3); } // 0xCF614CA8
inline VOID StartPlaybackRecordedVehicleWithFlags(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { FiveXInvoke<VOID>(0x4E721AD2, p0, p1, p2, p3, p4, p5); } // 0x4E721AD2
inline VOID StopPlaybackRecordedVehicle(Any p0) { FiveXInvoke<VOID>(0xAE99C57C, p0); } // 0xAE99C57C
inline VOID PausePlaybackRecordedVehicle(Any p0) { FiveXInvoke<VOID>(0xCCF54912, p0); } // 0xCCF54912
inline VOID UnpausePlaybackRecordedVehicle(Any p0) { FiveXInvoke<VOID>(0x59060F75, p0); } // 0x59060F75
inline BOOL IsPlaybackGoingOnForVehicle(Any p0) { return FiveXInvoke<BOOL>(0x61F7650D, p0); } // 0x61F7650D
inline BOOL IsPlaybackUsingAiGoingOnForVehicle(Any p0) { return FiveXInvoke<BOOL>(0x63022C58, p0); } // 0x63022C58
inline Any GetCurrentPlaybackForVehicle(Any p0) { return FiveXInvoke<Any>(0xA3F44390, p0); } // 0xA3F44390
inline VOID SkipToEndAndStopPlaybackRecordedVehicle(Any p0) { FiveXInvoke<VOID>(0x8DEA18C8, p0); } // 0x8DEA18C8
inline VOID SetPlaybackSpeed(Any p0, FLOAT speed) { FiveXInvoke<VOID>(0x684E26E4, p0, speed); } // 0x684E26E4
inline VOID StartPlaybackRecordedVehicleUsingAi(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0x8DE8E24E, p0, p1, p2, p3, p4); } // 0x8DE8E24E
inline VOID SkipTimeInPlaybackRecordedVehicle(Any p0, Any p1) { FiveXInvoke<VOID>(0xCF3EFA4B, p0, p1); } // 0xCF3EFA4B
inline VOID SetPlaybackToUseAi(Any p0, Any p1) { FiveXInvoke<VOID>(0xB536CCD7, p0, p1); } // 0xB536CCD7
inline VOID SetPlaybackToUseAiTryToRevertBackLater(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x0C8ABAA4, p0, p1, p2, p3); } // 0x0C8ABAA4
inline VOID ExplodeVehicleInCutscene(Any p0, Any p1) { FiveXInvoke<VOID>(0xA85207B5, p0, p1); } // 0xA85207B5
inline VOID AddVehicleStuckCheckWithWarp(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { FiveXInvoke<VOID>(0xC8B789AD, p0, p1, p2, p3, p4, p5, p6); } // 0xC8B789AD
inline VOID SetVehicleModelIsSuppressed(Any p0, Any p1) { FiveXInvoke<VOID>(0x42A08C9B, p0, p1); } // 0x42A08C9B
inline Entity GetRandomVehicleInSphere(FLOAT p0, FLOAT p1, FLOAT p2, FLOAT p3, INT p4, INT p5) { return FiveXInvoke<Entity>(0x57216D03, p0, p1, p2, p3, p4, p5); } // 0x57216D03
inline Entity GetRandomVehicleFrontBumperInSphere(FLOAT p0, FLOAT p1, FLOAT p2, FLOAT p3, INT p4, INT p5, INT p6) { return FiveXInvoke<Entity>(0xDCADEB66, p0, p1, p2, p3, p4, p5, p6); } // 0xDCADEB66
inline Entity GetRandomVehicleBackBumperInSphere(FLOAT p0, FLOAT p1, FLOAT p2, FLOAT p3, INT p4, INT p5, INT p6) { return FiveXInvoke<Entity>(0xD6343F6B, p0, p1, p2, p3, p4, p5, p6); } // 0xD6343F6B
inline Vehicle GetClosestVehicle(FLOAT x, FLOAT y, FLOAT z, FLOAT radius, Hash hash, INT unk1) { return FiveXInvoke<Vehicle>(0xD7E26B2C, x, y, z, radius, hash, unk1); } // 0xD7E26B2C
inline Any GetTrainCarriage(Any p0, Any p1) { return FiveXInvoke<Any>(0x2544E7A6, p0, p1); } // 0x2544E7A6
inline VOID DeleteMissionTrain(Any p0) { FiveXInvoke<VOID>(0x86C9497D, p0); } // 0x86C9497D
inline VOID SetMissionTrainAsNoLongerNeeded(Any p0, Any p1) { FiveXInvoke<VOID>(0x19808560, p0, p1); } // 0x19808560
inline VOID SetMissionTrainCoords(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0xD6D70803, p0, p1, p2, p3); } // 0xD6D70803
inline BOOL IsThisModelABoat(Hash model) { return FiveXInvoke<BOOL>(0x10F6085C, model); } // 0x10F6085C
inline BOOL IsThisModelAPlane(Hash model) { return FiveXInvoke<BOOL>(0x3B3907BB, model); } // 0x3B3907BB
inline BOOL IsThisModelAHeli(Hash model) { return FiveXInvoke<BOOL>(0x8AF7F568, model); } // 0x8AF7F568
inline BOOL IsThisModelACar(Hash model) { return FiveXInvoke<BOOL>(0x60E4C22F, model); } // 0x60E4C22F
inline BOOL IsThisModelATrain(Hash model) { return FiveXInvoke<BOOL>(0xF87DCFFD, model); } // 0xF87DCFFD
inline BOOL IsThisModelABike(Hash model) { return FiveXInvoke<BOOL>(0x7E702CDD, model); } // 0x7E702CDD
inline BOOL IsThisModelABicycle(Hash model) { return FiveXInvoke<BOOL>(0x328E6FF5, model); } // 0x328E6FF5
inline BOOL IsThisModelAQuadbike(Hash model) { return FiveXInvoke<BOOL>(0xC1625277, model); } // 0xC1625277
inline VOID SetHeliBladesFullSpeed(Any p0) { FiveXInvoke<VOID>(0x033A9408, p0); } // 0x033A9408
inline VOID SetHeliBladesSpeed(Vehicle vehicle, FLOAT speed) { FiveXInvoke<VOID>(0x5C7D4EA9, vehicle, speed); } // 0x5C7D4EA9
inline VOID SetVehicleCanBeTargetted(Vehicle vehicle, BOOL state) { FiveXInvoke<VOID>(0x64B70B1D, vehicle, state); } // 0x64B70B1D
inline VOID SetVehicleCanBeVisiblyDamaged(Vehicle vehicle, BOOL state) { FiveXInvoke<VOID>(0xC5D94017, vehicle, state); } // 0xC5D9401
inline FLOAT GetVehicleDirtLevel(Vehicle vehicle) { return FiveXInvoke<float>(0xFD15C065, vehicle); } // 0xFD15C065
inline VOID SetVehicleDirtLevel(Vehicle Vehicle, FLOAT DirtLVL) { FiveXInvoke<VOID>(0x2B39128B, Vehicle, DirtLVL); } // 0x2B39128B
inline BOOL IsVehicleDoorFullyOpen(Vehicle vehicle, INT doorIndex) { return FiveXInvoke<BOOL>(0xC2385B6F, vehicle, doorIndex); } // 0xC2385B6F
inline VOID SetVehicleEngineOn(Vehicle veh, BOOL engineState, BOOL p3) { FiveXInvoke<VOID>(0x7FBC86F1, veh, engineState, p3); } // 0x7FBC86F1
inline VOID SetVehicleUndriveable(Vehicle vehicle, BOOL state) { FiveXInvoke<VOID>(0x48D02A4E, vehicle, state); } // 0x48D02A4E
inline VOID SetVehicleProvidesCover(Any p0, Any p1) { FiveXInvoke<VOID>(0xEFC01CA9, p0, p1); } // 0xEFC01CA9
inline VOID SetVehicleDoorControl(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x572DD360, p0, p1, p2, p3); } // 0x572DD360
inline VOID SetVehicleDoorLatched(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0x4EB7BBFC, p0, p1, p2, p3, p4); } // 0x4EB7BBFC
inline FLOAT GetVehicleDoorAngleRatio(Vehicle vehicle, INT doorIndex) { return FiveXInvoke<FLOAT>(0x0E399C26, vehicle, doorIndex); } // 0x0E399C26
inline VOID SetVehicleDoorShut(Vehicle vehicle, INT doorIndex, BOOL closeInstantly) { FiveXInvoke<VOID>(0x142606BD, vehicle, doorIndex, closeInstantly); } // 0x142606BD
inline VOID SetVehicleDoorBroken(Vehicle veh, INT doorIndex, BOOL unk) { FiveXInvoke<VOID>(0x8147FEA7, veh, doorIndex, unk); } // 0x8147FEA7
inline VOID SetVehicleCanBreak(Vehicle vehicle, BOOL Toggle) { FiveXInvoke<VOID>(0x90A810D1, vehicle, Toggle); } // 0x90A810D1
inline BOOL DoesVehicleHaveRoof(Vehicle vehicle) { return FiveXInvoke<BOOL>(0xDB817403, vehicle); } // 0xDB817403
inline BOOL IsBigVehicle(Vehicle vehicle) { return FiveXInvoke<BOOL>(0x9CDBA8DE, vehicle); } // 0x9CDBA8DE
inline Any GetNumberOfVehicleColours(Any p0) { return FiveXInvoke<Any>(0xF2442EE2, p0); } // 0xF2442EE2
inline VOID SetVehicleColourCombination(Vehicle vehicle, int colorCombination) { FiveXInvoke<VOID>(0xA557AEAD, vehicle, colorCombination); } // 0xA557AEAD
inline Any GetVehicleColourCombination(Vehicle vehicle) { return FiveXInvoke<Any>(0x77AC1B4C, vehicle); } // 0x77AC1B4C
inline VOID SetVehicleIsConsideredByPlayer(Any p0, Any p1) { FiveXInvoke<VOID>(0x14413319, p0, p1); } // 0x14413319
inline VOID GetRandomVehicleModelInMemory(BOOL b0, Hash* p1, PINT p2) { FiveXInvoke<VOID>(0xE2C45631, b0, p1, p2); } // 0xE2C45631
inline Any GetVehicleDoorLockStatus(Any p0) { return FiveXInvoke<Any>(0x0D72CEF2, p0); } // 0x0D72CEF2
inline BOOL IsVehicleDoorDamaged(Vehicle veh, INT doorID) { return FiveXInvoke<BOOL>(0x4999E3C3, veh, doorID); } // 0x4999E3C3
inline BOOL IsVehicleBumperBrokenOff(Any p0, Any p1) { return FiveXInvoke<BOOL>(0xAF25C027, p0, p1); } // 0xAF25C027
inline BOOL IsCopVehicleInArea3d(Any x1, Any x2, Any y1, Any y2, Any z1, Any z2) { return FiveXInvoke<BOOL>(0xFB16C6D1, x1, x2, y1, y2, z1, z2); } // 0xFB16C6D1
inline BOOL IsVehicleOnAllWheels(Vehicle vehicle) { return FiveXInvoke<BOOL>(0x10089F8E, vehicle); } // 0x10089F8E
inline Any GetVehicleLayoutHash(Any p0) { return FiveXInvoke<Any>(0xE0B35187, p0); } // 0xE0B35187
inline VOID SetRenderTrainAsDerailed(Any p0, Any p1) { FiveXInvoke<VOID>(0x899D9092, p0, p1); } // 0x899D9092
inline VOID SetVehicleExtraColours(Vehicle vehicle, int pearlescentColor, int wheelColor) { FiveXInvoke<VOID>(0x515DB2A0, vehicle, pearlescentColor, wheelColor); } // 0x515DB2A0
inline VOID GetVehicleExtraColours(Vehicle vehicle, int* pearlescentColor, int* wheelColor) { FiveXInvoke<VOID>(0x80E4659B, vehicle, pearlescentColor, wheelColor); } // 0x80E4659B
inline VOID StopAllGarageActivity() { FiveXInvoke<VOID>(0x17A0BCE5); } // 0x17A0BCE5
inline VOID SetVehicleFixed(Vehicle Vehicle) { FiveXInvoke<VOID>(0x17469AA1, Vehicle); } // 0x17469AA1
inline VOID SetVehicleDeformationFixed(Vehicle Vehicle) { FiveXInvoke<VOID>(0xDD2920C8, Vehicle); } // 0xDD2920C8
inline VOID SetDisableVehiclePetrolTankDamage(Vehicle p0, BOOL p1) { FiveXInvoke<VOID>(0xAD3E05F2, p0, p1); } // 0xAD3E05F2
inline VOID RemoveVehiclesFromGeneratorsInArea(Any x1, Any x2, Any y1, Any y2, Any z1, Any z2) { FiveXInvoke<VOID>(0x42CC15E0, x1, x2, y1, y2, z1, z2); } // 0x42CC15E0
inline VOID SetVehicleSteerBias(Any p0, Any p1) { FiveXInvoke<VOID>(0x7357C1EB, p0, p1); } // 0x7357C1EB
inline BOOL IsVehicleExtraTurnedOn(Vehicle vehicle, INT extraId) { return FiveXInvoke<BOOL>(0x042098B5, vehicle, extraId); } // 0x042098B5
inline VOID SetVehicleExtra(Vehicle vehicle, INT ExtraID, BOOL Toggle) { FiveXInvoke<VOID>(0x642D065C, vehicle, ExtraID, Toggle); } // 0x642D065C
inline BOOL DoesExtraExist(Vehicle vehicle, INT extraId) { return FiveXInvoke<BOOL>(0x409411CC, vehicle, extraId); } // 0x409411CC
inline VOID SetConvertibleRoof(Any p0, Any p1) { FiveXInvoke<VOID>(0xC87B6A51, p0, p1); } // 0xC87B6A51
inline VOID LowerConvertibleRoof(Any p0, Any p1) { FiveXInvoke<VOID>(0xC5F72EAE, p0, p1); } // 0xC5F72EAE
inline VOID RaiseConvertibleRoof(Any p0, Any p1) { FiveXInvoke<VOID>(0xA4E4CBA3, p0, p1); } // 0xA4E4CBA3
inline Any GetConvertibleRoofState(Any p0) { return FiveXInvoke<Any>(0x1B09714D, p0); } // 0x1B09714D
inline BOOL IsVehicleAConvertible(Any p0, Any p1) { return FiveXInvoke<BOOL>(0x6EF54490, p0, p1); } // 0x6EF54490
inline BOOL IsVehicleStoppedAtTrafficLights(Any p0) { return FiveXInvoke<BOOL>(0x69200FA4, p0); } // 0x69200FA4
inline VOID SetVehicleDamage(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { FiveXInvoke<VOID>(0x21B458B2, p0, p1, p2, p3, p4, p5, p6); } // 0x21B458B2
inline FLOAT GetVehicleEngineHealth(Vehicle vehicle) { return FiveXInvoke<float>(0x8880038A, vehicle); } // 0x8880038A
inline VOID SetVehicleEngineHealth(Vehicle vehicle, FLOAT health) { FiveXInvoke<VOID>(0x1B760FB5, vehicle, health); } // 0x1B760FB5
inline FLOAT GetVehiclePetrolTankHealth(Vehicle vehicle) { return FiveXInvoke<float>(0xE41595CE, vehicle); } // 0xE41595CE
inline VOID SetVehiclePetrolTankHealth(Vehicle vehicle, FLOAT health) { FiveXInvoke<VOID>(0x660A3692, vehicle, health); } // 0x660A3692
inline BOOL IsVehicleStuckTimerUp(Any p0, Any p1, Any p2) { return FiveXInvoke<BOOL>(0x2FCF58C1, p0, p1, p2); } // 0x2FCF58C1
inline VOID ResetVehicleStuckTimer(Any p0, Any p1) { FiveXInvoke<VOID>(0xEF2A6016, p0, p1); } // 0xEF2A6016
inline BOOL IsVehicleDriveable(Any p0, Any p1) { return FiveXInvoke<BOOL>(0x41A7267A, p0, p1); } // 0x41A7267A
inline VOID SetVehicleHasBeenOwnedByPlayer(Any p0, Any p1) { FiveXInvoke<VOID>(0xB4D3DBFB, p0, p1); } // 0xB4D3DBFB
inline VOID SetVehicleNeedsToBeHotwired(Any p0, Any p1) { FiveXInvoke<VOID>(0xD8260751, p0, p1); } // 0xD8260751
inline VOID StartVehicleHorn(Vehicle p0, INT p1, INT p2, BOOL p3) { FiveXInvoke<VOID>(0x0DF5ADB3, p0, p1, p2, p3); } // 0x0DF5ADB3
inline VOID SetVehicleHasStrongAxles(Any p0, Any p1) { FiveXInvoke<VOID>(0x0D1CBC65, p0, p1); } // 0x0D1CBC65
inline char* GetDisplayNameFromVehicleModel(Hash modelHash) { return FiveXInvoke<char*>(0xEC86DF39, modelHash); } // 0xEC86DF39
inline Vector3 GetVehicleDeformationAtPos(Any p0, Any p1, Any p2, Any p3) { return FiveXInvoke<Vector3>(0xABF02075, p0, p1, p2, p3); } // 0xABF02075
inline VOID SetVehicleLivery(Vehicle vehicle, INT LiveryIndex) { FiveXInvoke<VOID>(0x7AD87059, vehicle, LiveryIndex); } // 0x7AD87059
inline Any GetVehicleLivery(Any p0) { return FiveXInvoke<Any>(0xEC82A51D, p0); } // 0xEC82A51D
inline Any GetVehicleLiveryCount(Any p0) { return FiveXInvoke<Any>(0xFB0CA947, p0); } // 0xFB0CA947
inline BOOL IsVehicleWindowIntact(Any p0, Any p1) { return FiveXInvoke<BOOL>(0xAC4EF23D, p0, p1); } // 0xAC4EF23D
inline VOID ResetVehicleWheels(Any p0, Any p1) { FiveXInvoke<VOID>(0xD5FFE779, p0, p1); } // 0xD5FFE779
inline BOOL IsHeliPartBroken(Any p0, Any p1, Any p2, Any p3) { return FiveXInvoke<BOOL>(0xF4E4C439, p0, p1, p2, p3); } // 0xF4E4C439
inline BOOL WasCounterActivated(Any p0, Any p1) { return FiveXInvoke<BOOL>(0x2916D69B, p0, p1); } // 0x2916D69B
inline VOID SetVehicleNameDebug(Any p0, Any p1) { FiveXInvoke<VOID>(0xA712FF5C, p0, p1); } // 0xA712FF5C
inline VOID SetVehicleExplodesOnHighExplosionDamage(Any p0, Any p1) { FiveXInvoke<VOID>(0x38CC692B, p0, p1); } // 0x38CC692B
inline BOOL IsAnyVehicleNearPoint(Any p0, Any x, Any y, Any z) { return FiveXInvoke<BOOL>(0x2867A834, p0, x, y, z); } // 0x2867A834
inline VOID RequestVehicleHighDetailModel(Any p0) { FiveXInvoke<VOID>(0x9DA21956, p0); } // 0x9DA21956
inline VOID RemoveVehicleHighDetailModel(Any p0) { FiveXInvoke<VOID>(0x382BE070, p0); } // 0x382BE070
inline BOOL IsVehicleHighDetail(Any p0) { return FiveXInvoke<BOOL>(0x55D41928, p0); } // 0x55D41928
inline VOID RequestVehicleAsset(Hash VehicleHash, INT p1) { FiveXInvoke<VOID>(0x902B4F06, VehicleHash, p1); } // 0x902B4F06
inline BOOL HasVehicleAssetLoaded(Any p0) { return FiveXInvoke<BOOL>(0x8DAAC3CB, p0); } // 0x8DAAC3CB
inline VOID RemoveVehicleAsset(Any p0) { FiveXInvoke<VOID>(0x9620E9C6, p0); } // 0x9620E9C6
inline VOID AttachVehicleToTowTruck(Entity entity, Entity entity2, INT instant, FLOAT x, FLOAT y, FLOAT z) { FiveXInvoke<VOID>(0x8151571A, entity, entity2, instant, x, y, z); } // 0x8151571A
inline VOID DetachVehicleFromTowTruck(Any p0, Any p1) { FiveXInvoke<VOID>(0xC666CF33, p0, p1); } // 0xC666CF33
inline Any DetachVehicleFromAnyTowTruck(Any p0) { return FiveXInvoke<Any>(0x3BF93651, p0); } // 0x3BF93651
inline BOOL IsVehicleAttachedToTowTruck(Any p0, Any p1) { return FiveXInvoke<BOOL>(0x9699CFDC, p0, p1); } // 0x9699CFDC
inline Any GetEntityAttachedToTowTruck(Any p0) { return FiveXInvoke<Any>(0x11EC7844, p0); } // 0x11EC7844
inline Any SetVehicleAutomaticallyAttaches(Any p0, Any p1, Any p2) { return FiveXInvoke<Any>(0x4273A8D3, p0, p1, p2); } // 0x4273A8D3
inline VOID SetVehicleBurnout(Any p0, Any p1) { FiveXInvoke<VOID>(0x9B6EF0EA, p0, p1); } // 0x9B6EF0EA
inline BOOL IsVehicleInBurnout(Vehicle vehicle) { return FiveXInvoke<BOOL>(0x6632BC12, vehicle); } // 0x6632BC12
inline VOID SetVehicleReduceGrip(Vehicle Vehicle, BOOL Toggle) { FiveXInvoke<VOID>(0x90D3A0D9, Vehicle, Toggle); } // 0x90D3A0D9
inline VOID SetVehicleIndicatorLights(Vehicle vehicle, INT turnSignal, BOOL Toggle) { FiveXInvoke<VOID>(0xA6073B5D, vehicle, turnSignal, Toggle); } // 0xA6073B5D
inline VOID SetVehicleBrakeLights(Vehicle vehicle, BOOL Toggle) { FiveXInvoke<VOID>(0x6D9BA11E, vehicle, Toggle); } // 0x6D9BA11E
inline VOID SetVehicleHandbrake(Vehicle vehicle, BOOL Toggle) { FiveXInvoke<VOID>(0xBA729A25, vehicle, Toggle); } // 0xBA729A25
inline Any GetVehicleTrailerVehicle(Any p0, Any p1) { return FiveXInvoke<Any>(0xAE84D758, p0, p1); } // 0xAE84D758
inline VOID SetVehicleRudderBroken(Any p0, Any p1) { FiveXInvoke<VOID>(0x3FAC3CD4, p0, p1); } // 0x3FAC3CD4
inline Any GetVehicleMaxBraking(Any p0) { return FiveXInvoke<Any>(0x03B926F6, p0); } // 0x03B926F6
inline Any GetVehicleMaxTraction(Any p0) { return FiveXInvoke<Any>(0x7E5A1587, p0); } // 0x7E5A1587
inline Any GetVehicleAcceleration(Any p0) { return FiveXInvoke<Any>(0x00478321, p0); } // 0x00478321
inline FLOAT GetVehicleModelMaxSpeed(Hash p0) { return FiveXInvoke<float>(0x8F291C4A, p0); } // 0x8F291C4A
inline FLOAT GetVehicleModelMaxBraking(Hash p0) { return FiveXInvoke<float>(0x7EF02883, p0); } // 0x7EF02883
inline Any GetVehicleModelMaxBrakingMaxMods(Any p0) { return FiveXInvoke<Any>(0xF3A7293F, p0); } // 0xF3A7293F
inline FLOAT GetVehicleModelMaxTraction(Hash p0) { return FiveXInvoke<float>(0x7F985597, p0); } // 0x7F985597
inline FLOAT GetVehicleModelAcceleration(Hash p0) { return FiveXInvoke<float>(0x29CB3537, p0); } // 0x29CB3537
inline Any GetVehicleModelEstimatedAgility(Any p0) { return FiveXInvoke<Any>(0x37FBA7BC, p0); } // 0x37FBA7BC
inline Any GetVehicleClassMaxTraction(Any p0) { return FiveXInvoke<Any>(0x5B4FDC16, p0); } // 0x5B4FDC16
inline Any GetVehicleClassMaxAgility(Any p0) { return FiveXInvoke<Any>(0x45F2BD83, p0); } // 0x45F2BD83
inline Any GetVehicleClassMaxAcceleration(Any p0) { return FiveXInvoke<Any>(0x3E220A9B, p0); } // 0x3E220A9B
inline Any GetVehicleClassMaxBraking(Any p0) { return FiveXInvoke<Any>(0xD08CC1A5, p0); } // 0xD08CC1A5
inline BOOL IsVehicleSearchlightOn(Vehicle vehicle) { return FiveXInvoke<BOOL>(0xADAF3513, vehicle); } // 0xADAF3513
inline VOID SetVehicleSearchlight(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xE2C0DD8A, p0, p1, p2); } // 0xE2C0DD8A
inline BOOL CanShuffleSeat(Any p0, Any p1) { return FiveXInvoke<BOOL>(0xB3EB01ED, p0, p1); } // 0xB3EB01ED
inline Any GetNumModKits(Any p0) { return FiveXInvoke<Any>(0xE4903AA0, p0); } // 0xE4903AA0
inline VOID SetVehicleModKit(Vehicle vehicle, INT unknown) { FiveXInvoke<VOID>(0xB8132158, vehicle, unknown); } // 0xB8132158
inline Any GetVehicleModKit(Any p0) { return FiveXInvoke<Any>(0x9FE60927, p0); } // 0x9FE60927
inline Any GetVehicleModKitType(Any p0) { return FiveXInvoke<Any>(0xE5F76765, p0); } // 0xE5F76765
inline INT GetVehicleWheelType(Vehicle vehicle) { return FiveXInvoke<int>(0xDA58D7AE, vehicle); } // 0xDA58D7AE
inline VOID SetVehicleWheelType(Vehicle vehicle, INT WheelType) { FiveXInvoke<VOID>(0x64BDAAAD, vehicle, WheelType); } // 0x64BDAAAD
inline Any GetNumModColors(Any p0, Any p1) { return FiveXInvoke<Any>(0x73722CD9, p0, p1); } // 0x73722CD9
inline VOID SetVehicleModColor1(Vehicle vehicle, int paintType, int color, int pearlescentColor) { FiveXInvoke<VOID>(0xCBE9A54D, vehicle, paintType, color, pearlescentColor); } // 0xCBE9A54D
inline VOID SetVehicleModColor2(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0xC32613C2, p0, p1, p2); } // 0xC32613C2
inline VOID GetVehicleModColor1(Vehicle vehicle, int* paintType, int* color, int* pearlescentColor) { FiveXInvoke<VOID>(0xE625510A, vehicle, paintType, color, pearlescentColor); } // 0xE625510A
inline VOID GetVehicleModColor2(Vehicle vehicle, int* paintType, int* color) { FiveXInvoke<VOID>(0x9B76BB8E, vehicle, paintType, color); } // 0x9B76BB8E
inline VOID SetVehicleMod(Vehicle vehicle, INT ModType, INT ModIndex, BOOL Variation) { FiveXInvoke<VOID>(0xB52E5ED5, vehicle, ModType, ModIndex, Variation); } // 0xB52E5ED5
inline INT GetVehicleMod(Vehicle vehicle, INT Modtype) { return FiveXInvoke<int>(0xDC520069, vehicle, Modtype); } // 0xDC520069
inline BOOL GetVehicleModVariation(Vehicle vehicle, INT ModType) { return FiveXInvoke<BOOL>(0xC1B92003, vehicle, ModType); } // 0xC1B92003
inline INT GetNumVehicleMods(Vehicle vehicle, INT ModType) { return FiveXInvoke<int>(0x8A814FF9, vehicle, ModType); } // 0x8A814FF9
inline VOID RemoveVehicleMod(Any p0, Any p1) { FiveXInvoke<VOID>(0x9CC80A43, p0, p1); } // 0x9CC80A43
inline VOID ToggleVehicleMod(Vehicle vehicle, INT Mod, BOOL Toggle) { FiveXInvoke<VOID>(0xD095F811, vehicle, Mod, Toggle); } // 0xD095F811
inline BOOL IsToggleModOn(Vehicle vehicle, int modType) { return FiveXInvoke<BOOL>(0xF0E1689F, vehicle, modType); } // 0xF0E1689F
inline char* GetModTextLabel(Vehicle vehicle, INT ModType, INT ModValue) { return FiveXInvoke<char*>(0x0BA39CA7, vehicle, ModType, ModValue); } // 0x0BA39CA7
inline char* GetModSlotName(Vehicle vehicle, INT ModType) { return FiveXInvoke<char*>(0x5E113483, vehicle, ModType); } // 0x5E113483
inline Any GetLiveryName(Any p0, Any p1) { return FiveXInvoke<Any>(0xED80B5BE, p0, p1); } // 0xED80B5BE
inline Any GetVehicleModModifierValue(Any p0, Any p1, Any p2) { return FiveXInvoke<Any>(0x73AE5505, p0, p1, p2); } // 0x73AE5505
inline VOID PreloadVehicleMod(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x6EA5F4A8, p0, p1, p2); } // 0x6EA5F4A8
inline BOOL HasPreloadModsFinished(Any p0) { return FiveXInvoke<BOOL>(0xA8A0D246, p0); } // 0xA8A0D246
inline VOID ReleasePreloadMods(Any p0) { FiveXInvoke<VOID>(0xD442521F, p0); } // 0xD442521F
inline VOID SetVehicleTyreSmokeColor(Vehicle vehicle, INT r, INT g, INT b) { FiveXInvoke<VOID>(0x3EDEC0DB, vehicle, r, g, b); } // 0x3EDEC0DB
inline VOID GetVehicleTyreSmokeColor(Vehicle vehicle, INT R, INT G, INT B) { FiveXInvoke<VOID>(0x75280015, vehicle, R, G, B); } // 0x75280015
inline VOID SetVehicleWindowTint(Vehicle vehicle, INT TINT) { FiveXInvoke<VOID>(0x497C8787, vehicle, TINT); } // 0x497C8787
inline INT GetVehicleWindowTint(Vehicle vehicle) { return FiveXInvoke<int>(0x13D53892, vehicle); } // 0x13D53892
inline Any GetNumVehicleWindowTints() { return FiveXInvoke<Any>(0x625C7B66); } // 0x625C7B66
inline VOID GetVehicleColor(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x03BC8F1B, p0, p1, p2, p3); } // 0x03BC8F1B
inline Any GetVehicleCauseOfDestruction(Any p0) { return FiveXInvoke<Any>(0x7F8C20DD, p0); } // 0x7F8C20DD
inline VOID SetVehicleIsWanted(Vehicle p0, BOOL p1) { FiveXInvoke<VOID>(0xDAA388E8, p0, p1); } // 0xDAA388E8
inline VOID DisablePlaneAileron(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x7E84C45C, p0, p1, p2); } // 0x7E84C45C
inline VOID SetVehicleLodMultiplier(Any p0, Any p1) { FiveXInvoke<VOID>(0x569E5AE3, p0, p1); } // 0x569E5AE3
inline VOID SetVehicleShootAtTarget(Any p0, Any p1, Any p2, Any p3, Any p4) { FiveXInvoke<VOID>(0x2343FFDF, p0, p1, p2, p3, p4); } // 0x2343FFDF
inline Any GetVehiclePlateType(Vehicle vehicle) { return FiveXInvoke<Any>(0x65CA9286, vehicle); } // 0x65CA9286
inline VOID TrackVehicleVisibility(Any p0) { FiveXInvoke<VOID>(0x78122DC1, p0); } // 0x78122DC1
inline BOOL IsVehicleVisible(Any p0) { return FiveXInvoke<BOOL>(0x7E0D6056, p0); } // 0x7E0D6056
inline VOID SetVehicleGravity(Vehicle Vehicle, BOOL Toggle) { FiveXInvoke<VOID>(0x07B2A6DC, Vehicle, Toggle); } // 0x07B2A6DC
inline VOID SetVehicleEngineCanDegrade(Any p0, Any p1) { FiveXInvoke<VOID>(0x081DAC12, p0, p1); } // 0x081DAC12
inline BOOL IsVehicleStolen(Vehicle p0) { return FiveXInvoke<BOOL>(0x20B61DDE, p0); } // 0x20B61DDE
inline VOID SetVehicleIsStolen(Vehicle vehicle, BOOL isStolen) { FiveXInvoke<VOID>(0x70912E42, vehicle, isStolen); } // 0x70912E42
inline VOID DetachVehicleFromCargobob(Any p0, Any p1) { FiveXInvoke<VOID>(0x83D3D331, p0, p1); } // 0x83D3D331
inline Any DetachVehicleFromAnyCargobob(Any p0) { return FiveXInvoke<Any>(0x50E0EABE, p0); } // 0x50E0EABE
inline BOOL IsVehicleAttachedToCargobob(Any p0, Any p1) { return FiveXInvoke<BOOL>(0x5DEEC76C, p0, p1); } // 0x5DEEC76C
inline Any GetVehicleAttachedToCargobob(Any p0) { return FiveXInvoke<Any>(0x301A1D24, p0); } // 0x301A1D24
inline VOID AttachVehicleToCargobob(Entity entity, Entity entity2, INT instant, FLOAT X, FLOAT y, FLOAT z) { FiveXInvoke<VOID>(0x607DC9D5, entity, entity2, instant, X, y, z); } // 0x607DC9D5
inline VOID GetClosestVehicleTurningBloodspray(Any p0) { FiveXInvoke<VOID>(0xA8211EE9, p0); } // 0xA8211EE9
inline VOID GetVehicleHasBackRecursive(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x3A8AB081, p0, p1, p2, p3); } // 0x3A8AB081
inline BOOL DoesVehicleHaveWeapons(Vehicle vehicle) { return FiveXInvoke<BOOL>(0xB2E1E1FB, vehicle); } // 0xB2E1E1FB
inline VOID DisableVehicleWeapon(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0xA688B7D1, p0, p1, p2, p3); } // 0xA688B7D1
inline Any GetVehicleClass(Vehicle vehicle) { return FiveXInvoke<Any>(0xC025338E, vehicle); } // 0xC025338E
inline Any GetVehicleClassFromName(Any p0) { return FiveXInvoke<Any>(0xEA469980, p0); } // 0xEA469980
inline VOID SetPlayersLastVehicle(Vehicle vehicle) { FiveXInvoke<VOID>(0xDE86447D, vehicle); } // 0xDE86447D
inline VOID SetVehicleFrictionOverride(Any p0, Any p1) { FiveXInvoke<VOID>(0x32AFD42E, p0, p1); } // 0x32AFD42E
inline VOID SetVehicleMaxStrTrap(Any p0, Any p1) { FiveXInvoke<VOID>(0x670913A4, p0, p1); } // 0x670913A4
inline VOID GetVehicleDeformationGetTree(Any p0, Any p1) { FiveXInvoke<VOID>(0x98A10A86, p0, p1); } // 0x98A10A86
inline BOOL DoesVehicleExistWithDecorator(Any p0) { return FiveXInvoke<BOOL>(0x39E68EDD, p0); } // 0x39E68EDD
inline Entity GetCurrentPedWeaponEntityIndex(Ped ped) { return FiveXInvoke<Entity>(0x5D73CD20, ped); } // 0x3B390A939AF0B5FC 0x5D73CD20
inline VOID EnableLaserSightRendering(Any p0) { FiveXInvoke<VOID>(0xE3438955, p0); } // 0xE3438955
inline Any GetWeapontypeModel(Any p0) { return FiveXInvoke<Any>(0x44E1C269, p0); } // 0x44E1C269
inline Any GetWeapontypeSlot(Any p0) { return FiveXInvoke<Any>(0x2E3759AF, p0); } // 0x2E3759AF
inline Any GetWeapontypeGroup(Any p0) { return FiveXInvoke<Any>(0x5F2DE833, p0); } // 0x5F2DE833
inline VOID SetCurrentPedWeapon(Ped PedHandle, Hash WeaponHash, BOOL EquipNow) { FiveXInvoke<VOID>(0xB8278882, PedHandle, WeaponHash, EquipNow); } // 0xB8278882
inline Any GetCurrentPedWeapon(Ped ped, Hash* weapHash, BOOL p2) { return FiveXInvoke<Any>(0xB0237302, ped, weapHash, p2); } // 0xB0237302
inline Any GetBestPedWeapon(Any p0, Any p1) { return FiveXInvoke<Any>(0xB998D444, p0, p1); } // 0xB998D444
inline Any SetCurrentPedVehicleWeapon(Any p0, Any p1) { return FiveXInvoke<Any>(0x8E6F2AF1, p0, p1); } // 0x8E6F2AF1
inline Any GetCurrentPedVehicleWeapon(Any p0, Any p1) { return FiveXInvoke<Any>(0xF26C5D65, p0, p1); } // 0xF26C5D65
inline BOOL IsPedArmed(Any p0, Any p1) { return FiveXInvoke<BOOL>(0x0BFC892C, p0, p1); } // 0x0BFC892C
inline BOOL IsWeaponValid(Hash WeapHash) { return FiveXInvoke<BOOL>(0x38CA2954, WeapHash); } // 0x38CA2954
inline BOOL HasPedGotWeapon(Ped ped, Hash weaponHash, BOOL p2) { return FiveXInvoke<BOOL>(0x43D2FA82, ped, weaponHash, p2); } // 0x43D2FA82
inline Any GetPedWeapontypeInSlot(Any p0, Any p1) { return FiveXInvoke<Any>(0x9BC64E16, p0, p1); } // 0x9BC64E16
inline Any GetAmmoInPedWeapon(Any p0, Any p1) { return FiveXInvoke<Any>(0x0C755733, p0, p1); } // 0x0C755733
inline VOID AddAmmoToPed(Ped handle, Hash weaponHash, INT ammo) { FiveXInvoke<VOID>(0x7F0580C7, handle, weaponHash, ammo); } // 0x7F0580C7
inline VOID SetPedAmmo(Ped PedHandle, Hash WeaponHash, INT ammo) { FiveXInvoke<VOID>(0xBF90DF1A, PedHandle, WeaponHash, ammo); } // 0xBF90DF1A
inline VOID SetPedInfiniteAmmo(Ped Handle, BOOL Toggle, Hash WeaponHash) { FiveXInvoke<VOID>(0x9CB8D278, Handle, Toggle, WeaponHash); } // 0x9CB8D278
inline VOID SetPedInfiniteAmmoClip(Ped PedHandle, BOOL Toggle) { FiveXInvoke<VOID>(0x5A5E3B67, PedHandle, Toggle); } // 0x5A5E3B67
inline VOID GiveWeaponToPed(INT pedHandle, Hash weaponAssetHash, INT ammoCount, BOOL equipNow, BOOL isAmmoLoaded) { FiveXInvoke<VOID>(0xC4D88A85, pedHandle, weaponAssetHash, ammoCount, equipNow, isAmmoLoaded); } // 0xC4D88A85
inline VOID GiveDelayedWeaponToPed(Ped pedHandle, Hash weaponHash, INT time, BOOL p3) { FiveXInvoke<VOID>(0x5868D20D, pedHandle, weaponHash, time, p3); } // 0x5868D20D
inline VOID RemoveAllPedWeapons(Ped PedHandle, BOOL Toggle) { FiveXInvoke<VOID>(0xA44CE817, PedHandle, Toggle); } // 0xA44CE817
inline VOID RemoveWeaponFromPed(Ped Handle, Hash WeaponHash) { FiveXInvoke<VOID>(0x9C37F220, Handle, WeaponHash); } // 0x9C37F220
inline VOID HidePedWeaponForScriptedCutscene(Player PedHandle, BOOL Toggle) { FiveXInvoke<VOID>(0x00CFD6E9, PedHandle, Toggle); } // 0x00CFD6E9
inline VOID SetPedCurrentWeaponVisible(Any p0, Any p1, Any p2, Any p3) { FiveXInvoke<VOID>(0x00BECD77, p0, p1, p2, p3); } // 0x00BECD77
inline VOID SetPedDropsWeaponsWhenDead(Any p0, Any p1) { FiveXInvoke<VOID>(0x8A444056, p0, p1); } // 0x8A444056
inline BOOL HasPedBeenDamagedByWeapon(Any p0, Any p1, Any p2) { return FiveXInvoke<BOOL>(0xCDFBBCC6, p0, p1, p2); } // 0xCDFBBCC6
inline VOID ClearPedLastWeaponDamage(Ped PedHandle) { FiveXInvoke<VOID>(0x52C68832, PedHandle); } // 0x52C68832
inline BOOL HasEntityBeenDamagedByWeapon(Any p0, Any p1, Any p2) { return FiveXInvoke<BOOL>(0x6DAABB39, p0, p1, p2); } // 0x6DAABB39
inline VOID ClearEntityLastWeaponDamage(Any p0) { FiveXInvoke<VOID>(0xCEC2732B, p0); } // 0xCEC2732B
inline VOID SetPedDropsWeapon(Any p0) { FiveXInvoke<VOID>(0x3D3329FA, p0); } // 0x3D3329FA
inline VOID SetPedDropsInventoryWeapon(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { FiveXInvoke<VOID>(0x81FFB874, p0, p1, p2, p3, p4, p5); } // 0x81FFB874
inline Any GetMaxAmmoInClip(Ped ped, Hash WeapHash, BOOL p2) { return FiveXInvoke<Any>(0x6961E2A4, ped, WeapHash, p2); } // 0x6961E2A4
inline Any GetAmmoInClip(Ped Handle, Hash WeaponHash, PINT p2) { return FiveXInvoke<Any>(0x73C100C3, Handle, WeaponHash, p2); } // 0x73C100C3
inline Any SetAmmoInClip(Ped Handle, Hash WeaponHash, INT ammo) { return FiveXInvoke<Any>(0xA54B0B10, Handle, WeaponHash, ammo); } // 0xA54B0B10
inline Any GetMaxAmmo(Ped ped, Hash WeapHash, PINT ammo) { return FiveXInvoke<Any>(0x0B294796, ped, WeapHash, ammo); } // 0x0B294796
inline VOID SetPedAmmoByType(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x311C52BB, p0, p1, p2); } // 0x311C52BB
inline Any GetPedAmmoByType(Any p0, Any p1) { return FiveXInvoke<Any>(0x54077C4D, p0, p1); } // 0x54077C4D
inline VOID SetPedAmmoToDrop(Any p0, Any p1) { FiveXInvoke<VOID>(0x2386A307, p0, p1); } // 0x2386A307
inline BOOL GetPedLastWeaponImpactCoord(Ped Handle, FLOAT* Coords) { return FiveXInvoke<BOOL>(0x9B266079, Handle, Coords); } // 0x9B266079
inline BOOL GetPedLastWeaponImpactCoord2(Ped ped, Vector3* coord) { return FiveXInvoke<BOOL>(0x9B266079, ped, coord); } // 0x6C4D0409BA1A2BC2 0x9B266079
inline VOID SetPedGadget(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x8A256D0A, p0, p1, p2); } // 0x8A256D0A
inline Any GetSelectedPedWeapon(Any p0) { return FiveXInvoke<Any>(0xD240123E, p0); } // 0xD240123E
inline VOID ExplodeProjectiles(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x35A0B955, p0, p1, p2); } // 0x35A0B955
inline VOID RemoveAllProjectilesOfType(Any p0, Any p1) { FiveXInvoke<VOID>(0xA5F89919, p0, p1); } // 0xA5F89919
inline BOOL HasVehicleGotProjectileAttached(Any p0, Any p1, Any p2, Any p3) { return FiveXInvoke<BOOL>(0xA57E2E80, p0, p1, p2, p3); } // 0xA57E2E80
inline VOID GiveWeaponComponentToPed(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x3E1E286D, p0, p1, p2); } // 0x3E1E286D
inline VOID RemoveWeaponComponentFromPed(Any p0, Any p1, Any p2) { FiveXInvoke<VOID>(0x412AA00D, p0, p1, p2); } // 0x412AA00D
inline BOOL HasPedGotWeaponComponent(Any p0, Any p1, Any p2) { return FiveXInvoke<BOOL>(0xDC0FC145, p0, p1, p2); } // 0xDC0FC145
inline BOOL IsPedWeaponComponentActive(Any p0, Any p1, Any p2) { return FiveXInvoke<BOOL>(0x7565FB19, p0, p1, p2); } // 0x7565FB19
inline Any MakePedReload(Any p0) { return FiveXInvoke<Any>(0x515292C2, p0); } // 0x515292C2
inline Any CreateWeaponObject(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return FiveXInvoke<Any>(0x62F5987F, p0, p1, p2, p3, p4, p5, p6); } // 0x62F5987F
inline VOID GiveWeaponComponentToWeaponObject(Any p0, Any p1) { FiveXInvoke<VOID>(0xF7612A37, p0, p1); } // 0xF7612A37
inline VOID RemoveWeaponComponentFromWeaponObject(Any p0, Any p1) { FiveXInvoke<VOID>(0xA6E7ED3C, p0, p1); } // 0xA6E7ED3C
inline BOOL HasWeaponGotWeaponComponent(Any p0, Any p1) { return FiveXInvoke<BOOL>(0x1D368510, p0, p1); } // 0x1D368510
inline VOID GiveWeaponObjectToPed(Any p0, Any p1) { FiveXInvoke<VOID>(0x639AF3EF, p0, p1); } // 0x639AF3EF
inline Any GetWeaponObjectFromPed(Any p0) { return FiveXInvoke<Any>(0xDF939A38, p0); } // 0xDF939A38
inline VOID SetPedWeaponTintIndex(Ped PedHandle, Hash WeaponHash, INT ColorIndex) { FiveXInvoke<VOID>(0xEB2A7B23, PedHandle, WeaponHash, ColorIndex); } // 0xEB2A7B23
inline Any GetPedWeaponTintIndex(Any p0, Any p1) { return FiveXInvoke<Any>(0x3F9C90A7, p0, p1); } // 0x3F9C90A7
inline VOID SetWeaponObjectTintIndex(Any p0, Any p1) { FiveXInvoke<VOID>(0x44ACC1DA, p0, p1); } // 0x44ACC1DA
inline Any GetWeaponObjectTintIndex(Any p0) { return FiveXInvoke<Any>(0xD91D9576, p0); } // 0xD91D9576
inline Any GetWeaponTintCount(Any p0) { return FiveXInvoke<Any>(0x99E4EAAB, p0); } // 0x99E4EAAB
inline Any GetWeaponHudStats(INT Hash, INT* Out) { return FiveXInvoke<Any>(0xA9AD3D98, Hash, Out); } // 0xA9AD3D98
inline Any GetWeaponComponentHudStats(Any p0, Any p1) { return FiveXInvoke<Any>(0xBB5498F4, p0, p1); } // 0xBB5498F4
inline Any GetWeaponClipSize(Any p0) { return FiveXInvoke<Any>(0x8D515E66, p0); } // 0x8D515E66
inline Any SetWeaponSmokegrenadeAssigned(Any p0) { return FiveXInvoke<Any>(0x76876154, p0); } // 0x76876154
inline VOID SetWeaponAnimationOverride(Any p0, Any p1) { FiveXInvoke<VOID>(0xA5DF7484, p0, p1); } // 0xA5DF7484
inline Any GetWeaponDamageType(Any p0) { return FiveXInvoke<Any>(0x013AFC13, p0); } // 0x013AFC13
inline VOID BreakObjectFragmentChild(Entity p0, INT p1, BOOL p2) { FiveXInvoke<VOID>(0x1E82C2AE, p0, p1, p2); }
inline VOID AttachEntityBoneToEntityBoneYForwad(Entity entity1, Entity entity2, INT boneIndex, FLOAT xPos, FLOAT yPos, FLOAT zPos, FLOAT xRot, FLOAT yRot, FLOAT zRot, BOOL p9, BOOL isRelative, BOOL collision, BOOL allowRotation, INT vertexIndex, BOOL fixedRot) { FiveXInvoke<VOID>(0xEC024237, entity1, entity2, boneIndex, xPos, yPos, zPos, xRot, yRot, zRot, p9, isRelative, collision, allowRotation, vertexIndex, fixedRot); } // 0xEC02423
inline Ped TestCreatePed(
    DWORD hash,
    INT type,
    Hash model,
    FLOAT x,
    FLOAT y,
    FLOAT z,
    FLOAT heading,
    BOOL networked,
    BOOL scriptHost
) {
    FiveXNativeContext ctx;
    FiveXNativeReset(&ctx);

    FiveXNativePush(&ctx, type);
    FiveXNativePush(&ctx, model);
    FiveXNativePush(&ctx, x);
    FiveXNativePush(&ctx, y);
    FiveXNativePush(&ctx, z);
    FiveXNativePush(&ctx, heading);
    FiveXNativePush(&ctx, networked);
    FiveXNativePush(&ctx, scriptHost);

    DbgPrint(
        "[BEFORE] ret=%08X storage0=%08X argc=%d\n",
        ctx.ReturnValue,
        ctx.Storage[0],
        ctx.ArgumentCount
    );

    BOOL called = FiveXNativeCall(hash, &ctx);

    DbgPrint(
        "[AFTER] called=%d ret=%08X storage0=%08X storage1=%08X\n",
        called,
        ctx.ReturnValue,
        ctx.Storage[0],
        ctx.Storage[1]
    );

    return *(Ped*)ctx.ReturnValue;
}
