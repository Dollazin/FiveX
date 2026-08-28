#include "LuaRuntime.h"
#include "../../Core/Global.h"
#include "../../Core/Storage/FileIO.h"
#include "../../Core/Storage/Paths.h"
#include "../../Core/Config/NumberFormat.h"
#include "../../Core/UI/Notification.h"
#include "../../GameNatives.h"

extern "C" {
#include "../../ThirdParty/Lua54/lua.h"
#include "../../ThirdParty/Lua54/lauxlib.h"
#include "../../ThirdParty/Lua54/lualib.h"
}

#include <math.h>
#include <float.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIVEX_LUA_MAX_RESOURCES 16
#define FIVEX_LUA_MAX_SCRIPTS 32
#define FIVEX_LUA_MAX_DEPENDENCIES 12
#define FIVEX_LUA_MAX_THREADS 64
#define FIVEX_LUA_MAX_HANDLERS 64
#define FIVEX_LUA_MAX_EXPORTS 32
#define FIVEX_LUA_MAX_OWNED_ENTITIES 128
#define FIVEX_LUA_MAX_PENDING_ACTIONS 16
#define FIVEX_LUA_MAX_FILE_SIZE (2 * 1024 * 1024)
#define FIVEX_LUA_MEMORY_LIMIT (8 * 1024 * 1024)
#define FIVEX_LUA_INSTRUCTION_BUDGET 2000000
#define FIVEX_LUA_HOOK_STEP 1000
#define FIVEX_LUA_VECTOR3_METATABLE "FiveX.vector3"
#define FIVEX_LUA_NATIVE_TEXT_LIMIT 4096

struct FiveXLuaAllocator {
	SIZE_T Used;
	SIZE_T Limit;
};

struct FiveXLuaThread {
	lua_State* State;
	INT Reference;
	INT ArgumentCount;
	INT InstructionBudget;
	DWORD WakeAt;
	BOOL Active;
};

struct FiveXLuaHandler {
	CHAR Name[64];
	INT Reference;
};

struct FiveXLuaExport {
	CHAR Name[64];
	INT Reference;
};

struct FiveXLuaVector3 {
	FLOAT X;
	FLOAT Y;
	FLOAT Z;
};

enum FiveXLuaNativeArgumentType {
	FiveXLuaNativeArgumentNone = 0,
	FiveXLuaNativeArgumentInteger,
	FiveXLuaNativeArgumentFloat,
	FiveXLuaNativeArgumentBoolean,
	FiveXLuaNativeArgumentString,
	FiveXLuaNativeArgumentPointerInInteger,
	FiveXLuaNativeArgumentPointerNull,
	FiveXLuaNativeArgumentPointerOutInteger,
	FiveXLuaNativeArgumentPointerOutFloat,
	FiveXLuaNativeArgumentPointerOutBoolean,
	FiveXLuaNativeArgumentPointerOutVector3
};

enum FiveXLuaNativeReturnType {
	FiveXLuaNativeReturnVoid = 0,
	FiveXLuaNativeReturnInteger,
	FiveXLuaNativeReturnFloat,
	FiveXLuaNativeReturnBoolean,
	FiveXLuaNativeReturnString,
	FiveXLuaNativeReturnVector3
};

struct FiveXLuaNativeEntry {
	const CHAR* Name;
	DWORD Hash;
	FiveXLuaNativeReturnType ReturnType;
	BYTE NativeArgumentCount;
	BYTE LuaArgumentCount;
	FiveXLuaNativeArgumentType Arguments[24];
};

union FiveXLuaNativePointerStorage {
	DWORD Integer;
	FLOAT Float;
	BOOL Boolean;
	Vector3 Vector;
};

static const FiveXLuaNativeEntry g_luaNativeCatalog[] = {
#include "LuaNativeCatalog.inl"
};

struct FiveXLuaResource {
	FiveXLuaResourceInfo Info;
	CHAR Root[FIVEX_MAX_PATH];
	CHAR Scripts[FIVEX_LUA_MAX_SCRIPTS][FIVEX_MAX_PATH];
	CHAR Dependencies[FIVEX_LUA_MAX_DEPENDENCIES][64];
	INT DependencyCount;
	FiveXLuaAllocator Allocator;
	lua_State* State;
	FiveXLuaThread Threads[FIVEX_LUA_MAX_THREADS];
	FiveXLuaHandler Handlers[FIVEX_LUA_MAX_HANDLERS];
	INT HandlerCount;
	FiveXLuaExport Exports[FIVEX_LUA_MAX_EXPORTS];
	INT ExportCount;
	Entity OwnedEntities[FIVEX_LUA_MAX_OWNED_ENTITIES];
	INT OwnedEntityCount;
	BOOL Catalogued;
	BOOL FoundDuringRefresh;
};

enum FiveXLuaPendingActionType {
	FiveXLuaPendingStart = 1,
	FiveXLuaPendingStop,
	FiveXLuaPendingRestart
};

struct FiveXLuaPendingAction {
	CHAR Name[64];
	FiveXLuaPendingActionType Type;
};

static FiveXLuaResource g_resources[FIVEX_LUA_MAX_RESOURCES];
static INT g_resourceCount;
static BOOL g_initialized;
static BOOL g_ticking;
static FiveXLuaPendingAction g_pendingActions[FIVEX_LUA_MAX_PENDING_ACTIONS];
static INT g_pendingActionCount;
static FiveXLuaResource* g_manifestResource;

static VOID CopyText(CHAR* output, SIZE_T outputSize, const CHAR* value) {
	if (!output || !outputSize)
		return;
	if (!value)
		value = "";
	strncpy_s(output, outputSize, value, _TRUNCATE);
}

static BOOL IsFiniteNativeNumber(lua_Number value) {
	return value == value && value <= (lua_Number)FLT_MAX && value >= (lua_Number)-FLT_MAX;
}

static DWORD CheckNativeDword(lua_State* state, INT index, const CHAR* nativeName) {
	const lua_Integer value = luaL_checkinteger(state, index);
	if (value < (lua_Integer)(-2147483647 - 1) ||
		(value >= 0 && (lua_Unsigned)value > (lua_Unsigned)0xFFFFFFFFu))
		luaL_error(state, "%s argument %d does not fit a 32-bit Xbox value",
			nativeName ? nativeName : "native", index);
	return (DWORD)value;
}

static const CHAR* CheckNativeString(lua_State* state, INT index, const CHAR* nativeName) {
	size_t length = 0;
	const CHAR* value = luaL_checklstring(state, index, &length);
	if (length > FIVEX_LUA_NATIVE_TEXT_LIMIT || strlen(value) != length)
		luaL_error(state, "%s argument %d contains an invalid or oversized string",
			nativeName ? nativeName : "native", index);
	return value;
}

static BOOL IsSafeResourceName(const CHAR* name) {
	if (!name || !name[0] || strlen(name) >= 64)
		return FALSE;
	for (const CHAR* position = name; *position; ++position) {
		const CHAR value = *position;
		if (!((value >= 'a' && value <= 'z') ||
			  (value >= 'A' && value <= 'Z') ||
			  (value >= '0' && value <= '9') ||
			  value == '_' || value == '-' || value == '.'))
			return FALSE;
	}
	return TRUE;
}

static FiveXLuaResource* FindResource(const CHAR* name) {
	if (!name)
		return NULL;
	for (INT index = 0; index < g_resourceCount; ++index) {
		if (g_resources[index].Catalogued &&
			_stricmp(g_resources[index].Info.Name, name) == 0)
			return &g_resources[index];
	}
	return NULL;
}

static FiveXLuaResource* AllocateResourceSlot() {
	for (INT index = 0; index < g_resourceCount; ++index) {
		if (!g_resources[index].Catalogued)
			return &g_resources[index];
	}
	if (g_resourceCount >= FIVEX_LUA_MAX_RESOURCES)
		return NULL;
	return &g_resources[g_resourceCount++];
}

static FiveXLuaResource* ResourceFromLua(lua_State* state) {
	return (FiveXLuaResource*)lua_touserdata(state, lua_upvalueindex(1));
}

static VOID* LuaAllocate(VOID* userData, VOID* pointer, size_t oldSize, size_t newSize) {
	FiveXLuaAllocator* allocator = (FiveXLuaAllocator*)userData;
	if (!allocator)
		return NULL;
	// Lua uses oldSize as a type tag for fresh allocations.
	if (!pointer)
		oldSize = 0;
	if (!newSize) {
		if (pointer) {
			free(pointer);
			allocator->Used = allocator->Used >= oldSize ? allocator->Used - oldSize : 0;
		}
		return NULL;
	}
	SIZE_T nextUsed = allocator->Used >= oldSize
		? allocator->Used - oldSize + newSize
		: newSize;
	if (nextUsed > allocator->Limit)
		return NULL;
	VOID* resized = realloc(pointer, newSize);
	if (!resized)
		return NULL;
	allocator->Used = nextUsed;
	return resized;
}

static BOOL ReadFileAllocated(const CHAR* path, CHAR** data, DWORD* size) {
	if (data)
		*data = NULL;
	if (size)
		*size = 0;
	if (!path || !data || !size)
		return FALSE;

	FiveXFileReader reader;
	if (FiveXFileOpenRead(path, &reader) != FiveXFileOk)
		return FALSE;
	DWORD length = GetFileSize(reader.Handle, NULL);
	if (length == INVALID_FILE_SIZE || !length || length > FIVEX_LUA_MAX_FILE_SIZE) {
		FiveXFileCloseRead(&reader);
		return FALSE;
	}
	CHAR* buffer = (CHAR*)malloc(length + 1);
	if (!buffer) {
		FiveXFileCloseRead(&reader);
		return FALSE;
	}
	DWORD total = 0;
	while (total < length) {
		DWORD read = 0;
		if (FiveXFileRead(&reader, buffer + total, length - total, &read) != FiveXFileOk || !read) {
			free(buffer);
			FiveXFileCloseRead(&reader);
			return FALSE;
		}
		total += read;
	}
	FiveXFileCloseRead(&reader);
	buffer[length] = '\0';
	*data = buffer;
	*size = length;
	return TRUE;
}

static BOOL HasWildcard(const CHAR* path) {
	return path && (strchr(path, '*') != NULL || strchr(path, '?') != NULL);
}

static BOOL IsSafeRelativePath(const CHAR* path) {
	if (!path || !path[0] || strstr(path, "..") || strchr(path, ':'))
		return FALSE;
	return strlen(path) < FIVEX_MAX_PATH;
}

static BOOL AddManifestScript(const CHAR* script) {
	if (!g_manifestResource || !script || !script[0])
		return FALSE;
	if (g_manifestResource->Info.ScriptCount >= FIVEX_LUA_MAX_SCRIPTS) {
		DbgPrint("[FiveX][Lua] Too many scripts in resource %s.\n", g_manifestResource->Info.Name);
		return FALSE;
	}
	if (HasWildcard(script)) {
		DbgPrint("[FiveX][Lua] Wildcards are not supported yet: %s/%s\n",
			g_manifestResource->Info.Name, script);
		return FALSE;
	}
	if (script[0] == '@') {
		const CHAR* slash = strchr(script + 1, '/');
		if (!slash)
			slash = strchr(script + 1, '\\');
		if (!slash || slash == script + 1)
			return FALSE;
		CHAR resourceName[64];
		SIZE_T resourceLength = (SIZE_T)(slash - (script + 1));
		if (resourceLength >= sizeof(resourceName))
			return FALSE;
		memcpy(resourceName, script + 1, resourceLength);
		resourceName[resourceLength] = '\0';
		FiveXLuaResource* source = FindResource(resourceName);
		if (!source || !IsSafeRelativePath(slash + 1))
			return FALSE;
		const INT scriptIndex = g_manifestResource->Info.ScriptCount;
		if (FiveXPathBuild(g_manifestResource->Scripts[scriptIndex],
			FIVEX_MAX_PATH, source->Root, slash + 1) != FiveXFileOk)
			return FALSE;
		++g_manifestResource->Info.ScriptCount;
		return TRUE;
	}
	if (!IsSafeRelativePath(script))
		return FALSE;
	const INT scriptIndex = g_manifestResource->Info.ScriptCount;
	if (FiveXPathBuild(g_manifestResource->Scripts[scriptIndex],
		FIVEX_MAX_PATH, g_manifestResource->Root, script) != FiveXFileOk)
		return FALSE;
	++g_manifestResource->Info.ScriptCount;
	return TRUE;
}

static BOOL AddManifestDependency(const CHAR* dependency) {
	if (!g_manifestResource || !IsSafeResourceName(dependency))
		return FALSE;
	for (INT index = 0; index < g_manifestResource->DependencyCount; ++index) {
		if (_stricmp(g_manifestResource->Dependencies[index], dependency) == 0)
			return TRUE;
	}
	if (g_manifestResource->DependencyCount >= FIVEX_LUA_MAX_DEPENDENCIES)
		return FALSE;
	CopyText(g_manifestResource->Dependencies[g_manifestResource->DependencyCount++],
		64, dependency);
	return TRUE;
}

static INT ManifestAddScript(lua_State* state) {
	if (!AddManifestScript(luaL_checkstring(state, 1)))
		return luaL_error(state, "invalid client script entry");
	return 0;
}

static INT ManifestAddScripts(lua_State* state) {
	luaL_checktype(state, 1, LUA_TTABLE);
	lua_Integer count = (lua_Integer)lua_rawlen(state, 1);
	for (lua_Integer index = 1; index <= count; ++index) {
		lua_rawgeti(state, 1, index);
		const CHAR* script = lua_tostring(state, -1);
		if (!script || !AddManifestScript(script)) {
			lua_pop(state, 1);
			return luaL_error(state, "invalid client script entry at index %d", (INT)index);
		}
		lua_pop(state, 1);
	}
	return 0;
}

static INT ManifestAddDependency(lua_State* state) {
	if (!AddManifestDependency(luaL_checkstring(state, 1)))
		return luaL_error(state, "invalid dependency entry");
	return 0;
}

static INT ManifestAddDependencies(lua_State* state) {
	luaL_checktype(state, 1, LUA_TTABLE);
	lua_Integer count = (lua_Integer)lua_rawlen(state, 1);
	for (lua_Integer index = 1; index <= count; ++index) {
		lua_rawgeti(state, 1, index);
		const CHAR* dependency = lua_tostring(state, -1);
		if (!dependency || !AddManifestDependency(dependency)) {
			lua_pop(state, 1);
			return luaL_error(state, "invalid dependency entry at index %d", (INT)index);
		}
		lua_pop(state, 1);
	}
	return 0;
}

static INT ManifestIgnore(lua_State*) {
	return 0;
}

static VOID RegisterManifestFunction(lua_State* state, const CHAR* name, lua_CFunction function) {
	lua_pushcfunction(state, function);
	lua_setglobal(state, name);
}

static BOOL ParseManifest(FiveXLuaResource* resource) {
	if (!resource)
		return FALSE;
	resource->Info.ScriptCount = 0;
	resource->DependencyCount = 0;

	CHAR manifestPath[FIVEX_MAX_PATH];
	if (FiveXPathBuild(manifestPath, sizeof(manifestPath), resource->Root, "fxmanifest.lua") != FiveXFileOk)
		return FALSE;
	CHAR* source = NULL;
	DWORD sourceSize = 0;
	if (!ReadFileAllocated(manifestPath, &source, &sourceSize))
		return FALSE;

	lua_State* state = luaL_newstate();
	if (!state) {
		free(source);
		return FALSE;
	}
	RegisterManifestFunction(state, "client_script", ManifestAddScript);
	RegisterManifestFunction(state, "client_scripts", ManifestAddScripts);
	RegisterManifestFunction(state, "shared_script", ManifestAddScript);
	RegisterManifestFunction(state, "shared_scripts", ManifestAddScripts);
	RegisterManifestFunction(state, "dependency", ManifestAddDependency);
	RegisterManifestFunction(state, "dependencies", ManifestAddDependencies);
	const CHAR* ignored[] = {
		"fx_version", "game", "games", "lua54", "author", "description",
		"version", "repository", "server_script", "server_scripts", "file",
		"files", "ui_page", "data_file", "escrow_ignore", "provide",
		"use_experimental_fxv2_oal"
	};
	for (DWORD index = 0; index < ARRAYSIZE(ignored); ++index)
		RegisterManifestFunction(state, ignored[index], ManifestIgnore);

	g_manifestResource = resource;
	INT status = luaL_loadbufferx(state, source, sourceSize, manifestPath, "t");
	if (status == LUA_OK)
		status = lua_pcall(state, 0, 0, 0);
	if (status != LUA_OK) {
		DbgPrint("[FiveX][Lua] Manifest error %s: %s\n", resource->Info.Name,
			lua_tostring(state, -1) ? lua_tostring(state, -1) : "unknown");
	}
	g_manifestResource = NULL;
	lua_close(state);
	free(source);
	return status == LUA_OK && resource->Info.ScriptCount > 0;
}

static FiveXLuaVector3* CheckVector3(lua_State* state, INT index) {
	return (FiveXLuaVector3*)luaL_checkudata(state, index, FIVEX_LUA_VECTOR3_METATABLE);
}

static FiveXLuaVector3* TestVector3(lua_State* state, INT index) {
	return (FiveXLuaVector3*)luaL_testudata(state, index, FIVEX_LUA_VECTOR3_METATABLE);
}

static VOID PushVector3(lua_State* state, FLOAT x, FLOAT y, FLOAT z) {
	FiveXLuaVector3* vector = (FiveXLuaVector3*)lua_newuserdatauv(state, sizeof(FiveXLuaVector3), 0);
	vector->X = x;
	vector->Y = y;
	vector->Z = z;
	luaL_getmetatable(state, FIVEX_LUA_VECTOR3_METATABLE);
	lua_setmetatable(state, -2);
}

static INT LuaVector3New(lua_State* state) {
	PushVector3(state,
		(FLOAT)luaL_optnumber(state, 1, 0.0),
		(FLOAT)luaL_optnumber(state, 2, 0.0),
		(FLOAT)luaL_optnumber(state, 3, 0.0));
	return 1;
}

static INT LuaVector3Index(lua_State* state) {
	FiveXLuaVector3* vector = CheckVector3(state, 1);
	if (lua_type(state, 2) == LUA_TNUMBER) {
		INT index = (INT)lua_tointeger(state, 2);
		if (index == 1) lua_pushnumber(state, vector->X);
		else if (index == 2) lua_pushnumber(state, vector->Y);
		else if (index == 3) lua_pushnumber(state, vector->Z);
		else lua_pushnil(state);
		return 1;
	}
	const CHAR* key = luaL_checkstring(state, 2);
	if (_stricmp(key, "x") == 0) lua_pushnumber(state, vector->X);
	else if (_stricmp(key, "y") == 0) lua_pushnumber(state, vector->Y);
	else if (_stricmp(key, "z") == 0) lua_pushnumber(state, vector->Z);
	else lua_pushnil(state);
	return 1;
}

static INT LuaVector3ToString(lua_State* state) {
	FiveXLuaVector3* vector = CheckVector3(state, 1);
	CHAR x[32];
	CHAR y[32];
	CHAR z[32];
	CHAR text[96];
	FiveXFormatFloat(x, sizeof(x), vector->X, 4);
	FiveXFormatFloat(y, sizeof(y), vector->Y, 4);
	FiveXFormatFloat(z, sizeof(z), vector->Z, 4);
	sprintf_s(text, sizeof(text), "vector3(%s, %s, %s)", x, y, z);
	lua_pushstring(state, text);
	return 1;
}

static INT LuaVector3Length(lua_State* state) {
	FiveXLuaVector3* vector = CheckVector3(state, 1);
	lua_pushnumber(state, sqrt(vector->X * vector->X + vector->Y * vector->Y + vector->Z * vector->Z));
	return 1;
}

static INT LuaVector3Operation(lua_State* state, CHAR operation) {
	FiveXLuaVector3* first = CheckVector3(state, 1);
	FiveXLuaVector3* second = TestVector3(state, 2);
	FLOAT x;
	FLOAT y;
	FLOAT z;
	if (second) {
		x = second->X; y = second->Y; z = second->Z;
	}
	else {
		FLOAT scalar = (FLOAT)luaL_checknumber(state, 2);
		x = scalar; y = scalar; z = scalar;
	}
	if (operation == '+') PushVector3(state, first->X + x, first->Y + y, first->Z + z);
	else if (operation == '-') PushVector3(state, first->X - x, first->Y - y, first->Z - z);
	else if (operation == '*') PushVector3(state, first->X * x, first->Y * y, first->Z * z);
	else PushVector3(state, first->X / x, first->Y / y, first->Z / z);
	return 1;
}

static INT LuaVector3Add(lua_State* state) { return LuaVector3Operation(state, '+'); }
static INT LuaVector3Sub(lua_State* state) { return LuaVector3Operation(state, '-'); }
static INT LuaVector3Mul(lua_State* state) { return LuaVector3Operation(state, '*'); }
static INT LuaVector3Div(lua_State* state) { return LuaVector3Operation(state, '/'); }

static INT LuaType(lua_State* state) {
	if (TestVector3(state, 1)) {
		lua_pushliteral(state, "vector3");
		return 1;
	}
	luaL_checkany(state, 1);
	lua_pushstring(state, luaL_typename(state, 1));
	return 1;
}

static VOID RegisterVector3(lua_State* state) {
	luaL_newmetatable(state, FIVEX_LUA_VECTOR3_METATABLE);
	lua_pushcfunction(state, LuaVector3Index); lua_setfield(state, -2, "__index");
	lua_pushcfunction(state, LuaVector3ToString); lua_setfield(state, -2, "__tostring");
	lua_pushcfunction(state, LuaVector3Length); lua_setfield(state, -2, "__len");
	lua_pushcfunction(state, LuaVector3Add); lua_setfield(state, -2, "__add");
	lua_pushcfunction(state, LuaVector3Sub); lua_setfield(state, -2, "__sub");
	lua_pushcfunction(state, LuaVector3Mul); lua_setfield(state, -2, "__mul");
	lua_pushcfunction(state, LuaVector3Div); lua_setfield(state, -2, "__div");
	lua_pop(state, 1);
	lua_pushcfunction(state, LuaVector3New); lua_setglobal(state, "vector3");
	lua_pushcfunction(state, LuaVector3New); lua_setglobal(state, "vec3");
	lua_pushcfunction(state, LuaType); lua_setglobal(state, "type");
}

static INT LuaPrint(lua_State* state) {
	const INT count = lua_gettop(state);
	CHAR message[256];
	message[0] = 0;
	for (INT index = 1; index <= count; ++index) {
		size_t length = 0;
		const CHAR* value = luaL_tolstring(state, index, &length);
		if (index > 1)
			strncat_s(message, sizeof(message), " ", _TRUNCATE);
		strncat_s(message, sizeof(message), value ? value : "nil", _TRUNCATE);
		lua_pop(state, 1);
	}
	Notify::Default("%s", message);
	return 0;
}

static FiveXLuaThread* AllocateThread(FiveXLuaResource* resource) {
	if (!resource)
		return NULL;
	for (INT index = 0; index < FIVEX_LUA_MAX_THREADS; ++index) {
		if (!resource->Threads[index].Active) {
			ZeroMemory(&resource->Threads[index], sizeof(resource->Threads[index]));
			resource->Threads[index].Active = TRUE;
			resource->Threads[index].Reference = LUA_NOREF;
			resource->Threads[index].InstructionBudget = FIVEX_LUA_INSTRUCTION_BUDGET;
			resource->Threads[index].WakeAt = GetTickCount();
			return &resource->Threads[index];
		}
	}
	return NULL;
}

static VOID ReleaseThread(FiveXLuaResource* resource, FiveXLuaThread* thread) {
	if (!resource || !thread)
		return;
	if (thread->Reference != LUA_NOREF && resource->State)
		luaL_unref(resource->State, LUA_REGISTRYINDEX, thread->Reference);
	ZeroMemory(thread, sizeof(*thread));
	thread->Reference = LUA_NOREF;
}

static INT LuaCreateThread(lua_State* state) {
	FiveXLuaResource* resource = ResourceFromLua(state);
	luaL_checktype(state, 1, LUA_TFUNCTION);
	FiveXLuaThread* slot = AllocateThread(resource);
	if (!slot)
		return luaL_error(state, "resource thread limit reached");
	lua_State* threadState = lua_newthread(state);
	slot->State = threadState;
	slot->Reference = luaL_ref(state, LUA_REGISTRYINDEX);
	lua_pushvalue(state, 1);
	lua_xmove(state, threadState, 1);
	return 0;
}

static INT LuaWait(lua_State* state) {
	if (!lua_isyieldable(state))
		return luaL_error(state, "Wait cannot be used from this context");
	INT milliseconds = (INT)luaL_optinteger(state, 1, 0);
	if (milliseconds < 0)
		milliseconds = 0;
	lua_pushinteger(state, milliseconds);
	return lua_yield(state, 1);
}

static INT LuaGetCurrentResourceName(lua_State* state) {
	FiveXLuaResource* resource = ResourceFromLua(state);
	lua_pushstring(state, resource ? resource->Info.Name : "");
	return 1;
}

static const CHAR* ResourceStateName(const FiveXLuaResource* resource) {
	if (!resource)
		return "missing";
	switch (resource->Info.State) {
	case FiveXLuaResourceStarting: return "starting";
	case FiveXLuaResourceStarted: return "started";
	case FiveXLuaResourceFailed: return "failed";
	default: return "stopped";
	}
}

static INT LuaGetResourceState(lua_State* state) {
	const CHAR* name = luaL_checkstring(state, 1);
	lua_pushstring(state, ResourceStateName(FindResource(name)));
	return 1;
}

static BOOL QueueAction(const CHAR* name, FiveXLuaPendingActionType type) {
	if (!IsSafeResourceName(name) || g_pendingActionCount >= FIVEX_LUA_MAX_PENDING_ACTIONS)
		return FALSE;
	CopyText(g_pendingActions[g_pendingActionCount].Name,
		sizeof(g_pendingActions[g_pendingActionCount].Name), name);
	g_pendingActions[g_pendingActionCount].Type = type;
	++g_pendingActionCount;
	return TRUE;
}

static INT LuaStartResource(lua_State* state) {
	lua_pushboolean(state, QueueAction(luaL_checkstring(state, 1), FiveXLuaPendingStart));
	return 1;
}

static INT LuaStopResource(lua_State* state) {
	lua_pushboolean(state, QueueAction(luaL_checkstring(state, 1), FiveXLuaPendingStop));
	return 1;
}

static INT LuaRestartResource(lua_State* state) {
	lua_pushboolean(state, QueueAction(luaL_checkstring(state, 1), FiveXLuaPendingRestart));
	return 1;
}

static FiveXLuaHandler* FindHandlerSlot(FiveXLuaResource* resource, const CHAR* eventName) {
	if (!resource || !eventName || resource->HandlerCount >= FIVEX_LUA_MAX_HANDLERS)
		return NULL;
	FiveXLuaHandler* handler = &resource->Handlers[resource->HandlerCount++];
	ZeroMemory(handler, sizeof(*handler));
	CopyText(handler->Name, sizeof(handler->Name), eventName);
	return handler;
}

static INT LuaAddEventHandler(lua_State* state) {
	FiveXLuaResource* resource = ResourceFromLua(state);
	const CHAR* eventName = luaL_checkstring(state, 1);
	luaL_checktype(state, 2, LUA_TFUNCTION);
	FiveXLuaHandler* handler = FindHandlerSlot(resource, eventName);
	if (!handler)
		return luaL_error(state, "resource event handler limit reached");
	lua_pushvalue(state, 2);
	handler->Reference = luaL_ref(state, LUA_REGISTRYINDEX);
	lua_pushinteger(state, handler->Reference);
	return 1;
}

static BOOL CopyLuaValue(lua_State* from, lua_State* to, INT index, INT depth) {
	if (depth > 4) {
		lua_pushnil(to);
		return FALSE;
	}
	index = lua_absindex(from, index);
	switch (lua_type(from, index)) {
	case LUA_TNIL: lua_pushnil(to); return TRUE;
	case LUA_TBOOLEAN: lua_pushboolean(to, lua_toboolean(from, index)); return TRUE;
	case LUA_TNUMBER:
		if (lua_isinteger(from, index)) lua_pushinteger(to, lua_tointeger(from, index));
		else lua_pushnumber(to, lua_tonumber(from, index));
		return TRUE;
	case LUA_TSTRING: {
		size_t length = 0;
		const CHAR* value = lua_tolstring(from, index, &length);
		lua_pushlstring(to, value, length);
		return TRUE;
	}
	case LUA_TUSERDATA: {
		FiveXLuaVector3* vector = TestVector3(from, index);
		if (vector) {
			PushVector3(to, vector->X, vector->Y, vector->Z);
			return TRUE;
		}
		break;
	}
	case LUA_TTABLE:
		lua_newtable(to);
		lua_pushnil(from);
		while (lua_next(from, index) != 0) {
			const BOOL keyCopied = CopyLuaValue(from, to, -2, depth + 1);
			CopyLuaValue(from, to, -1, depth + 1);
			if (keyCopied)
				lua_settable(to, -3);
			else
				lua_pop(to, 2);
			lua_pop(from, 1);
		}
		return TRUE;
	default:
		break;
	}
	lua_pushnil(to);
	return FALSE;
}

static BOOL QueueHandlerCall(FiveXLuaResource* target, INT handlerReference,
	lua_State* source, INT firstArgument, INT argumentCount) {
	if (!target || !target->State || target->Info.State != FiveXLuaResourceStarted)
		return FALSE;
	FiveXLuaThread* slot = AllocateThread(target);
	if (!slot)
		return FALSE;
	lua_State* threadState = lua_newthread(target->State);
	slot->State = threadState;
	slot->Reference = luaL_ref(target->State, LUA_REGISTRYINDEX);
	lua_rawgeti(target->State, LUA_REGISTRYINDEX, handlerReference);
	lua_xmove(target->State, threadState, 1);
	for (INT index = 0; index < argumentCount; ++index)
		CopyLuaValue(source, threadState, firstArgument + index, 0);
	slot->ArgumentCount = argumentCount;
	return TRUE;
}

static INT DispatchEvent(lua_State* source, const CHAR* eventName,
	INT firstArgument, INT argumentCount, FiveXLuaResource* onlyResource) {
	INT queued = 0;
	for (INT resourceIndex = 0; resourceIndex < g_resourceCount; ++resourceIndex) {
		FiveXLuaResource* target = &g_resources[resourceIndex];
		if (onlyResource && target != onlyResource)
			continue;
		if (target->Info.State != FiveXLuaResourceStarted)
			continue;
		for (INT handlerIndex = 0; handlerIndex < target->HandlerCount; ++handlerIndex) {
			FiveXLuaHandler* handler = &target->Handlers[handlerIndex];
			if (_stricmp(handler->Name, eventName) == 0 &&
				QueueHandlerCall(target, handler->Reference, source, firstArgument, argumentCount))
				++queued;
		}
	}
	return queued;
}

static INT LuaTriggerEvent(lua_State* state) {
	const CHAR* eventName = luaL_checkstring(state, 1);
	DispatchEvent(state, eventName, 2, lua_gettop(state) - 1, NULL);
	return 0;
}

static INT LuaRegisterNetEvent(lua_State*) {
	return 0;
}

static FiveXLuaExport* FindExport(FiveXLuaResource* resource, const CHAR* name) {
	if (!resource || !name)
		return NULL;
	for (INT index = 0; index < resource->ExportCount; ++index) {
		if (_stricmp(resource->Exports[index].Name, name) == 0)
			return &resource->Exports[index];
	}
	return NULL;
}

static INT LuaRegisterExport(lua_State* state) {
	FiveXLuaResource* resource = ResourceFromLua(state);
	INT offset = lua_istable(state, 1) ? 1 : 0;
	const CHAR* name = luaL_checkstring(state, 1 + offset);
	luaL_checktype(state, 2 + offset, LUA_TFUNCTION);
	FiveXLuaExport* entry = FindExport(resource, name);
	if (!entry) {
		if (!resource || resource->ExportCount >= FIVEX_LUA_MAX_EXPORTS)
			return luaL_error(state, "resource export limit reached");
		entry = &resource->Exports[resource->ExportCount++];
		ZeroMemory(entry, sizeof(*entry));
		CopyText(entry->Name, sizeof(entry->Name), name);
	}
	else if (entry->Reference != LUA_NOREF) {
		luaL_unref(state, LUA_REGISTRYINDEX, entry->Reference);
	}
	lua_pushvalue(state, 2 + offset);
	entry->Reference = luaL_ref(state, LUA_REGISTRYINDEX);
	return 0;
}

static INT LuaCallExport(lua_State* state) {
	const CHAR* resourceName = lua_tostring(state, lua_upvalueindex(2));
	const CHAR* exportName = lua_tostring(state, lua_upvalueindex(3));
	FiveXLuaResource* target = FindResource(resourceName);
	FiveXLuaExport* entry = FindExport(target, exportName);
	if (!target || target->Info.State != FiveXLuaResourceStarted || !entry)
		return luaL_error(state, "export %s:%s is unavailable", resourceName, exportName);
	INT firstArgument = lua_istable(state, 1) ? 2 : 1;
	INT argumentCount = lua_gettop(state) - firstArgument + 1;
	INT targetBase = lua_gettop(target->State);
	lua_rawgeti(target->State, LUA_REGISTRYINDEX, entry->Reference);
	for (INT index = 0; index < argumentCount; ++index)
		CopyLuaValue(state, target->State, firstArgument + index, 0);
	INT status = lua_pcall(target->State, argumentCount, LUA_MULTRET, 0);
	if (status != LUA_OK) {
		const CHAR* error = lua_tostring(target->State, -1);
		CHAR message[256];
		sprintf_s(message, sizeof(message), "export %s:%s failed: %s",
			resourceName, exportName, error ? error : "unknown");
		lua_settop(target->State, targetBase);
		return luaL_error(state, "%s", message);
	}
	INT resultCount = lua_gettop(target->State) - targetBase;
	if (resultCount > 8)
		resultCount = 8;
	for (INT index = 0; index < resultCount; ++index)
		CopyLuaValue(target->State, state, targetBase + 1 + index, 0);
	lua_settop(target->State, targetBase);
	return resultCount;
}

static INT LuaExportProxyIndex(lua_State* state) {
	FiveXLuaResource* caller = ResourceFromLua(state);
	const CHAR* targetName = lua_tostring(state, lua_upvalueindex(2));
	const CHAR* exportName = luaL_checkstring(state, 2);
	lua_pushlightuserdata(state, caller);
	lua_pushstring(state, targetName);
	lua_pushstring(state, exportName);
	lua_pushcclosure(state, LuaCallExport, 3);
	return 1;
}

static INT LuaExportsIndex(lua_State* state) {
	FiveXLuaResource* caller = ResourceFromLua(state);
	const CHAR* targetName = luaL_checkstring(state, 2);
	lua_newtable(state);
	lua_newtable(state);
	lua_pushlightuserdata(state, caller);
	lua_pushstring(state, targetName);
	lua_pushcclosure(state, LuaExportProxyIndex, 2);
	lua_setfield(state, -2, "__index");
	lua_setmetatable(state, -2);
	return 1;
}

static VOID RegisterExports(lua_State* state, FiveXLuaResource* resource) {
	lua_newtable(state);
	lua_newtable(state);
	lua_pushlightuserdata(state, resource);
	lua_pushcclosure(state, LuaRegisterExport, 1);
	lua_setfield(state, -2, "__call");
	lua_pushlightuserdata(state, resource);
	lua_pushcclosure(state, LuaExportsIndex, 1);
	lua_setfield(state, -2, "__index");
	lua_setmetatable(state, -2);
	lua_setglobal(state, "exports");
}

static INT PushNativeResult(lua_State* state, FiveXNativeContext* context,
	FiveXLuaNativeReturnType returnType) {
	switch (returnType) {
	case FiveXLuaNativeReturnVoid:
		return 0;
	case FiveXLuaNativeReturnInteger:
		lua_pushinteger(state, (lua_Integer)FiveXNativeResult<DWORD>(context));
		return 1;
	case FiveXLuaNativeReturnFloat:
		lua_pushnumber(state, (lua_Number)FiveXNativeResult<FLOAT>(context));
		return 1;
	case FiveXLuaNativeReturnBoolean:
		lua_pushboolean(state, FiveXNativeResult<BOOL>(context));
		return 1;
	case FiveXLuaNativeReturnString: {
		const CHAR* value = FiveXNativeResult<const CHAR*>(context);
		if (!value) {
			lua_pushnil(state);
			return 1;
		}
		BOOL valid = TRUE;
		SIZE_T length = 0;
		while (valid && length <= FIVEX_LUA_NATIVE_TEXT_LIMIT) {
			const CHAR* current = value + length;
			if (!MmIsAddressValid((PVOID)current)) {
				valid = FALSE;
				break;
			}
			if (!*current)
				break;
			++length;
		}
		if (valid && length <= FIVEX_LUA_NATIVE_TEXT_LIMIT)
			lua_pushlstring(state, value, length);
		else {
			DbgPrint("[FiveX][LuaNative] Rejected invalid native string result pointer=%p.\n", value);
			lua_pushnil(state);
		}
		return 1;
	}
	case FiveXLuaNativeReturnVector3: {
		Vector3 value = FiveXNativeResult<Vector3>(context);
		PushVector3(state, value.x, value.y, value.z);
		return 1;
	}
	default:
		return luaL_error(state, "unsupported native return type");
	}
}

static BOOL IsCatalogOutputPointer(FiveXLuaNativeArgumentType type) {
	return type == FiveXLuaNativeArgumentPointerOutInteger ||
		type == FiveXLuaNativeArgumentPointerOutFloat ||
		type == FiveXLuaNativeArgumentPointerOutBoolean ||
		type == FiveXLuaNativeArgumentPointerOutVector3;
}

static BOOL IsNullableCatalogString(DWORD hash, INT nativeArgumentIndex) {
	// DrawMarker(textureDict, textureName) explicitly accepts NULL for both
	// optional texture arguments on the Xbox build.
	return hash == 0x48D84A02 &&
		(nativeArgumentIndex == 21 || nativeArgumentIndex == 22);
}

static VOID ValidateCatalogSpecialCases(lua_State* state,
	const FiveXLuaNativeEntry* entry) {
	if (!entry)
		return;
	if (entry->Hash == 0x48D84A02) {
		const BOOL dictionaryNull = lua_isnil(state, 22);
		const BOOL textureNull = lua_isnil(state, 23);
		if (dictionaryNull != textureNull)
			luaL_error(state, "DrawMarker arguments 22 and 23 must both be nil or valid strings");
		if (!dictionaryNull) {
			const CHAR* dictionary = CheckNativeString(state, 22, entry->Name);
			const CHAR* texture = CheckNativeString(state, 23, entry->Name);
			if (!dictionary[0] || !texture[0])
				luaL_error(state, "DrawMarker optional textures must use nil, nil instead of empty strings");
		}
	}
}

static BOOL ValidatePointerInputHandle(lua_State* state,
	const FiveXLuaNativeEntry* entry, INT luaIndex, DWORD value) {
	if (!entry)
		return FALSE;
	if (entry->Hash == 0xD8C3C1CD) {
		if (!value || !DoesBlipExist((Blip)value))
			luaL_error(state, "%s argument %d is not a valid blip",
				entry->Name, luaIndex);
	}
	else if (entry->Hash == 0xFAA3D236 || entry->Hash == 0xD6EF9DA7 ||
		entry->Hash == 0x13EFB9A0 || entry->Hash == 0x9803AF60) {
		if (!value || !DoesEntityExist((Entity)value))
			luaL_error(state, "%s argument %d is not a valid entity",
				entry->Name, luaIndex);
	}
	return TRUE;
}

static BOOL PushCatalogArgument(lua_State* state, FiveXNativeContext* context,
	INT* luaIndex, const FiveXLuaNativeEntry* entry, INT nativeArgumentIndex,
	FiveXLuaNativeArgumentType type,
	FiveXLuaNativePointerStorage* storage) {
	if (!luaIndex || !entry || !storage)
		return FALSE;
	switch (type) {
	case FiveXLuaNativeArgumentInteger: {
		BOOL pushed = FiveXNativePush(context,
			CheckNativeDword(state, *luaIndex, entry->Name));
		++(*luaIndex);
		return pushed;
	}
	case FiveXLuaNativeArgumentFloat: {
		const lua_Number value = luaL_checknumber(state, *luaIndex);
		if (!IsFiniteNativeNumber(value))
			luaL_error(state, "%s argument %d must be a finite Xbox float",
				entry->Name, *luaIndex);
		BOOL pushed = FiveXNativePush(context, (FLOAT)value);
		++(*luaIndex);
		return pushed;
	}
	case FiveXLuaNativeArgumentBoolean:
		luaL_checktype(state, *luaIndex, LUA_TBOOLEAN);
		if (!FiveXNativePush(context, (BOOL)lua_toboolean(state, *luaIndex)))
			return FALSE;
		++(*luaIndex);
		return TRUE;
	case FiveXLuaNativeArgumentString: {
		BOOL pushed = FALSE;
		if (lua_isnil(state, *luaIndex) &&
			IsNullableCatalogString(entry->Hash, nativeArgumentIndex))
			pushed = FiveXNativePush(context, (DWORD)0);
		else
			pushed = FiveXNativePush(context,
				CheckNativeString(state, *luaIndex, entry->Name));
		++(*luaIndex);
		return pushed;
	}
	case FiveXLuaNativeArgumentPointerInInteger:
		storage->Integer = CheckNativeDword(state, *luaIndex, entry->Name);
		ValidatePointerInputHandle(state, entry, *luaIndex, storage->Integer);
		++(*luaIndex);
		return FiveXNativePush(context, &storage->Integer);
	case FiveXLuaNativeArgumentPointerNull:
		return FiveXNativePush(context, (DWORD)0);
	case FiveXLuaNativeArgumentPointerOutInteger:
		storage->Integer = 0;
		return FiveXNativePush(context, &storage->Integer);
	case FiveXLuaNativeArgumentPointerOutFloat:
		storage->Float = 0.0f;
		return FiveXNativePush(context, &storage->Float);
	case FiveXLuaNativeArgumentPointerOutBoolean:
		storage->Boolean = FALSE;
		return FiveXNativePush(context, &storage->Boolean);
	case FiveXLuaNativeArgumentPointerOutVector3:
		storage->Vector.x = 0.0f;
		storage->Vector.y = 0.0f;
		storage->Vector.z = 0.0f;
		return FiveXNativePush(context, &storage->Vector);
	default:
		return FALSE;
	}
}

static INT PushCatalogPointerResult(lua_State* state,
	FiveXLuaNativeArgumentType type,
	const FiveXLuaNativePointerStorage* storage) {
	if (!storage)
		return 0;
	switch (type) {
	case FiveXLuaNativeArgumentPointerOutInteger:
		lua_pushinteger(state, (lua_Integer)storage->Integer);
		return 1;
	case FiveXLuaNativeArgumentPointerOutFloat:
		lua_pushnumber(state, (lua_Number)storage->Float);
		return 1;
	case FiveXLuaNativeArgumentPointerOutBoolean:
		lua_pushboolean(state, storage->Boolean);
		return 1;
	case FiveXLuaNativeArgumentPointerOutVector3:
		PushVector3(state, storage->Vector.x, storage->Vector.y, storage->Vector.z);
		return 1;
	default:
		return 0;
	}
}

static INT LuaInvokeCatalogNative(lua_State* state) {
	const FiveXLuaNativeEntry* entry = (const FiveXLuaNativeEntry*)
		lua_touserdata(state, lua_upvalueindex(2));
	if (!entry)
		return luaL_error(state, "native metadata unavailable");
	if (lua_gettop(state) != entry->LuaArgumentCount)
		return luaL_error(state, "%s expects %d arguments, received %d",
			entry->Name, (INT)entry->LuaArgumentCount, lua_gettop(state));
	ValidateCatalogSpecialCases(state, entry);

	FiveXNativeContext context;
	FiveXNativeReset(&context);
	FiveXLuaNativePointerStorage pointerStorage[24];
	ZeroMemory(pointerStorage, sizeof(pointerStorage));
	INT luaIndex = 1;
	for (INT index = 0; index < entry->NativeArgumentCount; ++index) {
		if (!PushCatalogArgument(state, &context, &luaIndex, entry, index,
			entry->Arguments[index], &pointerStorage[index]))
			return luaL_error(state, "%s has an invalid argument at index %d",
				entry->Name, index + 1);
	}
	if (!FiveXNativeCall(entry->Hash, &context)) {
		return luaL_error(state, "native %s (0x%08X) is unavailable", entry->Name, entry->Hash);
	}
	INT resultCount = PushNativeResult(state, &context, entry->ReturnType);
	for (INT index = 0; index < entry->NativeArgumentCount; ++index) {
		if (IsCatalogOutputPointer(entry->Arguments[index]))
			resultCount += PushCatalogPointerResult(state,
				entry->Arguments[index], &pointerStorage[index]);
	}
	return resultCount;
}

static BOOL ParseNativeReturnType(const CHAR* value, FiveXLuaNativeReturnType* result) {
	if (!value || !result)
		return FALSE;
	if (_stricmp(value, "void") == 0) *result = FiveXLuaNativeReturnVoid;
	else if (_stricmp(value, "int") == 0 || _stricmp(value, "integer") == 0 ||
		_stricmp(value, "hash") == 0 || _stricmp(value, "entity") == 0)
		*result = FiveXLuaNativeReturnInteger;
	else if (_stricmp(value, "float") == 0) *result = FiveXLuaNativeReturnFloat;
	else if (_stricmp(value, "bool") == 0 || _stricmp(value, "boolean") == 0)
		*result = FiveXLuaNativeReturnBoolean;
	else if (_stricmp(value, "string") == 0) *result = FiveXLuaNativeReturnString;
	else if (_stricmp(value, "vector3") == 0) *result = FiveXLuaNativeReturnVector3;
	else return FALSE;
	return TRUE;
}

static const FiveXLuaNativeEntry* NativeEntryFromHash(DWORD hash) {
	for (DWORD index = 0; index < ARRAYSIZE(g_luaNativeCatalog); ++index) {
		if (g_luaNativeCatalog[index].Hash == hash)
			return &g_luaNativeCatalog[index];
	}
	return NULL;
}

static VOID ValidateDirectKnownNative(lua_State* state, DWORD hash,
	FiveXLuaNativeReturnType returnType, const FiveXNativeContext* context) {
	const FiveXLuaNativeEntry* entry = NativeEntryFromHash(hash);
	if (!entry || !context)
		return;
	if (returnType != entry->ReturnType)
		luaL_error(state,
			"InvokeNative %s return type does not match the safe catalog; use '%s'",
			entry->Name,
			entry->ReturnType == FiveXLuaNativeReturnVoid ? "void" :
			entry->ReturnType == FiveXLuaNativeReturnInteger ? "int" :
			entry->ReturnType == FiveXLuaNativeReturnFloat ? "float" :
			entry->ReturnType == FiveXLuaNativeReturnBoolean ? "bool" :
			entry->ReturnType == FiveXLuaNativeReturnString ? "string" : "vector3");
	for (INT index = 0; index < entry->NativeArgumentCount; ++index) {
		if (entry->Arguments[index] == FiveXLuaNativeArgumentPointerInInteger ||
			entry->Arguments[index] == FiveXLuaNativeArgumentPointerNull ||
			IsCatalogOutputPointer(entry->Arguments[index]))
			luaL_error(state,
				"InvokeNative cannot safely call pointer native %s; use the named Lua binding",
				entry->Name);
	}
	if (context->ArgumentCount != entry->NativeArgumentCount)
		luaL_error(state, "InvokeNative %s expects %d native arguments, received %lu",
			entry->Name, (INT)entry->NativeArgumentCount, context->ArgumentCount);
	if (hash == 0x48D84A02) {
		const BOOL dictionaryNull = lua_isnil(state, 24);
		const BOOL textureNull = lua_isnil(state, 25);
		if (dictionaryNull != textureNull)
			luaL_error(state, "InvokeNative DrawMarker texture arguments must both be nil or valid strings");
		if (!dictionaryNull) {
			const CHAR* dictionary = CheckNativeString(state, 24, "DrawMarker");
			const CHAR* texture = CheckNativeString(state, 25, "DrawMarker");
			if (!dictionary[0] || !texture[0])
				luaL_error(state, "InvokeNative DrawMarker must use nil, nil instead of empty texture strings");
		}
	}
}

static INT LuaInvokeNative(lua_State* state) {
	lua_Integer hashValue = luaL_checkinteger(state, 1);
	if (hashValue < 0 || (lua_Unsigned)hashValue > (lua_Unsigned)0xFFFFFFFFu)
		return luaL_error(state, "InvokeNative requires a 32-bit Xbox native hash");

	FiveXLuaNativeReturnType returnType;
	const CHAR* returnName = luaL_checkstring(state, 2);
	if (!ParseNativeReturnType(returnName, &returnType))
		return luaL_error(state, "invalid return type '%s'", returnName);
	const DWORD hash = (DWORD)hashValue;

	FiveXNativeContext context;
	FiveXNativeReset(&context);
	for (INT index = 3; index <= lua_gettop(state); ++index) {
		BOOL pushed = FALSE;
		switch (lua_type(state, index)) {
		case LUA_TNIL:
			pushed = FiveXNativePush(&context, (DWORD)0);
			break;
		case LUA_TBOOLEAN:
			pushed = FiveXNativePush(&context, (BOOL)lua_toboolean(state, index));
			break;
		case LUA_TNUMBER:
			if (lua_isinteger(state, index))
				pushed = FiveXNativePush(&context,
					CheckNativeDword(state, index, "InvokeNative"));
			else {
				const lua_Number value = lua_tonumber(state, index);
				if (!IsFiniteNativeNumber(value))
					return luaL_error(state,
						"InvokeNative argument %d must be a finite Xbox float", index - 2);
				pushed = FiveXNativePush(&context, (FLOAT)value);
			}
			break;
		case LUA_TSTRING:
			pushed = FiveXNativePush(&context,
				CheckNativeString(state, index, "InvokeNative"));
			break;
		case LUA_TUSERDATA: {
			FiveXLuaVector3* vector = TestVector3(state, index);
			if (vector) {
				if (!IsFiniteNativeNumber(vector->X) ||
					!IsFiniteNativeNumber(vector->Y) ||
					!IsFiniteNativeNumber(vector->Z))
					return luaL_error(state,
						"InvokeNative vector argument %d must contain finite values", index - 2);
				pushed = FiveXNativePush(&context, vector->X) &&
					FiveXNativePush(&context, vector->Y) &&
					FiveXNativePush(&context, vector->Z);
			}
			break;
		}
		default:
			break;
		}
		if (!pushed)
			return luaL_error(state, "unsupported native argument at index %d", index - 2);
	}

	ValidateDirectKnownNative(state, hash, returnType, &context);
	if (!FiveXNativeCall(hash, &context)) {
		return luaL_error(state, "native hash 0x%08X is unavailable", hash);
	}
	const INT resultCount = PushNativeResult(state, &context, returnType);
	return resultCount;
}

static VOID RegisterNativeCatalog(lua_State* state, FiveXLuaResource* resource) {
	for (DWORD index = 0; index < ARRAYSIZE(g_luaNativeCatalog); ++index) {
		lua_pushlightuserdata(state, resource);
		lua_pushlightuserdata(state, (VOID*)&g_luaNativeCatalog[index]);
		lua_pushcclosure(state, LuaInvokeCatalogNative, 2);
		lua_setglobal(state, g_luaNativeCatalog[index].Name);
	}
}

static Entity CheckExistingEntity(lua_State* state, INT index, const CHAR* nativeName) {
	const Entity entity = (Entity)CheckNativeDword(state, index, nativeName);
	if (!entity || !DoesEntityExist(entity))
		luaL_error(state, "%s argument %d is not an existing entity", nativeName, index);
	return entity;
}

static FLOAT CheckNativeFloat(lua_State* state, INT index, const CHAR* nativeName) {
	const lua_Number value = luaL_checknumber(state, index);
	if (!IsFiniteNativeNumber(value))
		luaL_error(state, "%s argument %d must be a finite Xbox float", nativeName, index);
	return (FLOAT)value;
}

static VOID RequireLuaArgumentCount(lua_State* state, const CHAR* nativeName,
	INT minimum, INT maximum) {
	const INT received = lua_gettop(state);
	if (received < minimum || received > maximum) {
		if (minimum == maximum)
			luaL_error(state, "%s expects %d arguments, received %d",
				nativeName, minimum, received);
		else
			luaL_error(state, "%s expects %d to %d arguments, received %d",
				nativeName, minimum, maximum, received);
	}
}

static BOOL CheckNativeBoolean(lua_State* state, INT index, const CHAR* nativeName) {
	if (!lua_isboolean(state, index))
		luaL_error(state, "%s argument %d must be boolean", nativeName, index);
	return lua_toboolean(state, index) ? TRUE : FALSE;
}

static INT LuaGetGameTimer(lua_State* state) { RequireLuaArgumentCount(state, "GetGameTimer", 0, 0); lua_pushinteger(state, GetGameTimer()); return 1; }
static INT LuaPlayerId(lua_State* state) { RequireLuaArgumentCount(state, "PlayerId", 0, 0); lua_pushinteger(state, PlayerId()); return 1; }
static INT LuaPlayerPedId(lua_State* state) { RequireLuaArgumentCount(state, "PlayerPedId", 0, 0); lua_pushinteger(state, PlayerPedId()); return 1; }
static INT LuaDoesEntityExist(lua_State* state) {
	RequireLuaArgumentCount(state, "DoesEntityExist", 1, 1);
	lua_pushboolean(state, DoesEntityExist((Entity)CheckNativeDword(state, 1, "DoesEntityExist")));
	return 1;
}
static INT LuaGetEntityHeading(lua_State* state) {
	RequireLuaArgumentCount(state, "GetEntityHeading", 1, 1);
	const Entity entity = CheckExistingEntity(state, 1, "GetEntityHeading");
	lua_pushnumber(state, GetEntityHeading(entity));
	return 1;
}
static INT LuaGetEntityCoords(lua_State* state) {
	RequireLuaArgumentCount(state, "GetEntityCoords", 1, 2);
	const Entity entity = CheckExistingEntity(state, 1, "GetEntityCoords");
	const BOOL alive = lua_gettop(state) >= 2 ?
		CheckNativeBoolean(state, 2, "GetEntityCoords") : FALSE;
	Vector3 value = GetEntityCoords(entity, alive);
	PushVector3(state, value.x, value.y, value.z);
	return 1;
}
static INT LuaGetFirstBlipInfoId(lua_State* state) {
	RequireLuaArgumentCount(state, "GetFirstBlipInfoId", 1, 1);
	lua_pushinteger(state, (lua_Integer)GetFirstBlipInfoId((Any)
		CheckNativeDword(state, 1, "GetFirstBlipInfoId")));
	return 1;
}
static INT LuaDoesBlipExist(lua_State* state) {
	RequireLuaArgumentCount(state, "DoesBlipExist", 1, 1);
	lua_pushboolean(state, DoesBlipExist((Any)
		CheckNativeDword(state, 1, "DoesBlipExist")));
	return 1;
}
static INT LuaGetBlipInfoIdCoord(lua_State* state) {
	RequireLuaArgumentCount(state, "GetBlipInfoIdCoord", 1, 1);
	const DWORD blip = CheckNativeDword(state, 1, "GetBlipInfoIdCoord");
	if (!blip || !DoesBlipExist((Any)blip))
		return luaL_error(state, "GetBlipInfoIdCoord argument 1 is not a valid blip");
	Vector3 value = GetBlipInfoIdCoord((Any)blip);
	PushVector3(state, value.x, value.y, value.z);
	return 1;
}
static INT LuaGetGroundZFor3dCoord(lua_State* state) {
	RequireLuaArgumentCount(state, "GetGroundZFor3dCoord", 3, 3);
	FLOAT groundZ = 0.0f;
	const FLOAT x = CheckNativeFloat(state, 1, "GetGroundZFor3dCoord");
	const FLOAT y = CheckNativeFloat(state, 2, "GetGroundZFor3dCoord");
	const FLOAT z = CheckNativeFloat(state, 3, "GetGroundZFor3dCoord");
	BOOL found = GetGroundZFor3dCoord2(
		x, y, z, &groundZ);
	lua_pushboolean(state, found);
	lua_pushnumber(state, groundZ);
	return 2;
}
static INT LuaSetEntityCoords(lua_State* state) {
	RequireLuaArgumentCount(state, "SetEntityCoords", 4, 4);
	const Entity entity = CheckExistingEntity(state, 1, "SetEntityCoords");
	const FLOAT x = CheckNativeFloat(state, 2, "SetEntityCoords");
	const FLOAT y = CheckNativeFloat(state, 3, "SetEntityCoords");
	const FLOAT z = CheckNativeFloat(state, 4, "SetEntityCoords");
	SetEntityCoords(entity, x, y, z, FALSE, FALSE, FALSE, FALSE);
	return 0;
}
static INT LuaGetHashKey(lua_State* state) {
	RequireLuaArgumentCount(state, "GetHashKey", 1, 1);
	const CHAR* text = CheckNativeString(state, 1, "GetHashKey");
	lua_pushinteger(state, GetHashKey((CHAR*)text));
	return 1;
}
static INT LuaRequestModel(lua_State* state) {
	RequireLuaArgumentCount(state, "RequestModel", 1, 1);
	const DWORD model = CheckNativeDword(state, 1, "RequestModel");
	if (!model || !IsModelInCdimage(model))
		return luaL_error(state, "RequestModel argument 1 is not a valid model hash");
	RequestModel(model);
	return 0;
}
static INT LuaHasModelLoaded(lua_State* state) {
	RequireLuaArgumentCount(state, "HasModelLoaded", 1, 1);
	lua_pushboolean(state, HasModelLoaded(CheckNativeDword(state, 1, "HasModelLoaded")));
	return 1;
}
static INT LuaSetModelAsNoLongerNeeded(lua_State* state) {
	RequireLuaArgumentCount(state, "SetModelAsNoLongerNeeded", 1, 1);
	SetModelAsNoLongerNeeded(CheckNativeDword(state, 1, "SetModelAsNoLongerNeeded"));
	return 0;
}
static INT LuaCreateVehicle(lua_State* state) {
	RequireLuaArgumentCount(state, "CreateVehicle", 7, 7);
	FiveXLuaResource* resource = ResourceFromLua(state);
	const DWORD model = CheckNativeDword(state, 1, "CreateVehicle");
	if (!model || !IsModelInCdimage(model) || !HasModelLoaded(model))
		return luaL_error(state, "CreateVehicle requires a valid, loaded model");
	const FLOAT x = CheckNativeFloat(state, 2, "CreateVehicle");
	const FLOAT y = CheckNativeFloat(state, 3, "CreateVehicle");
	const FLOAT z = CheckNativeFloat(state, 4, "CreateVehicle");
	const FLOAT heading = CheckNativeFloat(state, 5, "CreateVehicle");
	Entity vehicle = (Entity)CreateVehicle(model, x, y, z, heading,
		CheckNativeBoolean(state, 6, "CreateVehicle"),
		CheckNativeBoolean(state, 7, "CreateVehicle"));
	if (resource && vehicle && resource->OwnedEntityCount < FIVEX_LUA_MAX_OWNED_ENTITIES)
		resource->OwnedEntities[resource->OwnedEntityCount++] = vehicle;
	lua_pushinteger(state, vehicle);
	return 1;
}
static INT LuaDeleteEntity(lua_State* state) {
	RequireLuaArgumentCount(state, "DeleteEntity", 1, 1);
	Entity entity = CheckExistingEntity(state, 1, "DeleteEntity");
	DeleteEntity(&entity);
	return 0;
}
static INT LuaSetVehicleEngineOn(lua_State* state) {
	RequireLuaArgumentCount(state, "SetVehicleEngineOn", 3, 3);
	const Vehicle vehicle = (Vehicle)CheckExistingEntity(state, 1, "SetVehicleEngineOn");
	SetVehicleEngineOn(vehicle,
		CheckNativeBoolean(state, 2, "SetVehicleEngineOn"),
		CheckNativeBoolean(state, 3, "SetVehicleEngineOn"));
	return 0;
}
static INT LuaIsControlJustPressed(lua_State* state) {
	RequireLuaArgumentCount(state, "IsControlJustPressed", 2, 2);
	const DWORD group = CheckNativeDword(state, 1, "IsControlJustPressed");
	const DWORD control = CheckNativeDword(state, 2, "IsControlJustPressed");
	if (group > 2 || control > 400)
		return luaL_error(state, "IsControlJustPressed received an invalid input group/control");
	lua_pushboolean(state, IsControlJustPressed(group, control));
	return 1;
}

static VOID RegisterResourceFunction(lua_State* state, FiveXLuaResource* resource,
	const CHAR* name, lua_CFunction function) {
	lua_pushlightuserdata(state, resource);
	lua_pushcclosure(state, function, 1);
	lua_setglobal(state, name);
}

static VOID OpenResourceLibraries(lua_State* state) {
	const luaL_Reg libraries[] = {
		{ LUA_GNAME, luaopen_base },
		{ LUA_TABLIBNAME, luaopen_table },
		{ LUA_STRLIBNAME, luaopen_string },
		{ LUA_MATHLIBNAME, luaopen_math },
		{ LUA_COLIBNAME, luaopen_coroutine },
		{ LUA_UTF8LIBNAME, luaopen_utf8 },
		{ NULL, NULL }
	};
	for (const luaL_Reg* library = libraries; library->func; ++library) {
		luaL_requiref(state, library->name, library->func, 1);
		lua_pop(state, 1);
	}
	lua_pushnil(state); lua_setglobal(state, "dofile");
	lua_pushnil(state); lua_setglobal(state, "loadfile");
}

static VOID RegisterResourceApi(FiveXLuaResource* resource) {
	lua_State* state = resource->State;
	RegisterVector3(state);
	RegisterNativeCatalog(state, resource);
	lua_pushcfunction(state, LuaPrint); lua_setglobal(state, "print");
	RegisterResourceFunction(state, resource, "CreateThread", LuaCreateThread);
	RegisterResourceFunction(state, resource, "Wait", LuaWait);
	RegisterResourceFunction(state, resource, "GetCurrentResourceName", LuaGetCurrentResourceName);
	RegisterResourceFunction(state, resource, "GetResourceState", LuaGetResourceState);
	RegisterResourceFunction(state, resource, "StartResource", LuaStartResource);
	RegisterResourceFunction(state, resource, "StopResource", LuaStopResource);
	RegisterResourceFunction(state, resource, "RestartResource", LuaRestartResource);
	RegisterResourceFunction(state, resource, "AddEventHandler", LuaAddEventHandler);
	RegisterResourceFunction(state, resource, "TriggerEvent", LuaTriggerEvent);
	RegisterResourceFunction(state, resource, "RegisterNetEvent", LuaRegisterNetEvent);
	RegisterResourceFunction(state, resource, "InvokeNative", LuaInvokeNative);
	RegisterResourceFunction(state, resource, "GetGameTimer", LuaGetGameTimer);
	RegisterResourceFunction(state, resource, "PlayerId", LuaPlayerId);
	RegisterResourceFunction(state, resource, "PlayerPedId", LuaPlayerPedId);
	RegisterResourceFunction(state, resource, "DoesEntityExist", LuaDoesEntityExist);
	RegisterResourceFunction(state, resource, "GetEntityCoords", LuaGetEntityCoords);
	RegisterResourceFunction(state, resource, "GetFirstBlipInfoId", LuaGetFirstBlipInfoId);
	RegisterResourceFunction(state, resource, "DoesBlipExist", LuaDoesBlipExist);
	RegisterResourceFunction(state, resource, "GetBlipInfoIdCoord", LuaGetBlipInfoIdCoord);
	RegisterResourceFunction(state, resource, "GetGroundZFor_3dCoord", LuaGetGroundZFor3dCoord);
	RegisterResourceFunction(state, resource, "GetGroundZFor3dCoord", LuaGetGroundZFor3dCoord);
	RegisterResourceFunction(state, resource, "SetEntityCoords", LuaSetEntityCoords);
	RegisterResourceFunction(state, resource, "GetEntityHeading", LuaGetEntityHeading);
	RegisterResourceFunction(state, resource, "GetHashKey", LuaGetHashKey);
	RegisterResourceFunction(state, resource, "RequestModel", LuaRequestModel);
	RegisterResourceFunction(state, resource, "HasModelLoaded", LuaHasModelLoaded);
	RegisterResourceFunction(state, resource, "SetModelAsNoLongerNeeded", LuaSetModelAsNoLongerNeeded);
	RegisterResourceFunction(state, resource, "CreateVehicle", LuaCreateVehicle);
	RegisterResourceFunction(state, resource, "DeleteEntity", LuaDeleteEntity);
	RegisterResourceFunction(state, resource, "SetVehicleEngineOn", LuaSetVehicleEngineOn);
	RegisterResourceFunction(state, resource, "IsControlJustPressed", LuaIsControlJustPressed);
	RegisterExports(state, resource);

	const CHAR* timeoutHelper =
		"function SetTimeout(milliseconds, callback) "
		"assert(type(callback) == 'function', 'callback must be a function') "
		"CreateThread(function() Wait(milliseconds or 0) callback() end) end";
	if (luaL_loadstring(state, timeoutHelper) != LUA_OK || lua_pcall(state, 0, 0, 0) != LUA_OK) {
		DbgPrint("[FiveX][Lua] SetTimeout helper error in %s: %s\n",
			resource->Info.Name, lua_tostring(state, -1) ? lua_tostring(state, -1) : "unknown");
		lua_pop(state, 1);
	}

	lua_newtable(state);
	RegisterResourceFunction(state, resource, "__fivex_create_thread", LuaCreateThread);
	lua_getglobal(state, "__fivex_create_thread"); lua_setfield(state, -2, "CreateThread");
	RegisterResourceFunction(state, resource, "__fivex_wait", LuaWait);
	lua_getglobal(state, "__fivex_wait"); lua_setfield(state, -2, "Wait");
	lua_getglobal(state, "SetTimeout"); lua_setfield(state, -2, "SetTimeout");
	lua_getglobal(state, "InvokeNative"); lua_setfield(state, -2, "InvokeNative");
	lua_getglobal(state, "print"); lua_setfield(state, -2, "Trace");
	lua_setglobal(state, "Citizen");
	lua_pushnil(state); lua_setglobal(state, "__fivex_create_thread");
	lua_pushnil(state); lua_setglobal(state, "__fivex_wait");
}

static VOID InstructionHook(lua_State* state, lua_Debug*) {
	for (INT resourceIndex = 0; resourceIndex < g_resourceCount; ++resourceIndex) {
		FiveXLuaResource* resource = &g_resources[resourceIndex];
		for (INT threadIndex = 0; threadIndex < FIVEX_LUA_MAX_THREADS; ++threadIndex) {
			FiveXLuaThread* thread = &resource->Threads[threadIndex];
			if (thread->Active && thread->State == state) {
				thread->InstructionBudget -= FIVEX_LUA_HOOK_STEP;
				if (thread->InstructionBudget <= 0)
					luaL_error(state, "instruction budget exceeded");
				return;
			}
		}
	}
}

static BOOL LoadScriptThread(FiveXLuaResource* resource, const CHAR* path) {
	CHAR* source = NULL;
	DWORD size = 0;
	if (!ReadFileAllocated(path, &source, &size)) {
		DbgPrint("[FiveX][Lua] Unable to read script: %s\n", path);
		return FALSE;
	}
	FiveXLuaThread* slot = AllocateThread(resource);
	if (!slot) {
		free(source);
		return FALSE;
	}
	lua_State* threadState = lua_newthread(resource->State);
	slot->State = threadState;
	slot->Reference = luaL_ref(resource->State, LUA_REGISTRYINDEX);
	INT status = luaL_loadbufferx(threadState, source, size, path, "t");
	free(source);
	if (status != LUA_OK) {
		DbgPrint("[FiveX][Lua] Compile error %s: %s\n", path,
			lua_tostring(threadState, -1) ? lua_tostring(threadState, -1) : "unknown");
		ReleaseThread(resource, slot);
		return FALSE;
	}
	return TRUE;
}

static VOID ResumeResourceThreads(FiveXLuaResource* resource) {
	if (!resource || !resource->State || resource->Info.State != FiveXLuaResourceStarted)
		return;
	DWORD now = GetTickCount();
	INT activeCount = 0;
	for (INT index = 0; index < FIVEX_LUA_MAX_THREADS; ++index) {
		FiveXLuaThread* thread = &resource->Threads[index];
		if (!thread->Active)
			continue;
		++activeCount;
		if (!Helpers::HasElapsed(now, thread->WakeAt))
			continue;
		thread->InstructionBudget = FIVEX_LUA_INSTRUCTION_BUDGET;
		lua_sethook(thread->State, InstructionHook, LUA_MASKCOUNT, FIVEX_LUA_HOOK_STEP);
		INT resultCount = 0;
		INT argumentCount = thread->ArgumentCount;
		thread->ArgumentCount = 0;
		INT status = lua_resume(thread->State, NULL, argumentCount, &resultCount);
		if (status == LUA_YIELD) {
			INT wait = 0;
			if (resultCount > 0 && lua_isnumber(thread->State, -1))
				wait = (INT)lua_tointeger(thread->State, -1);
			lua_settop(thread->State, 0);
			thread->WakeAt = now + (wait < 0 ? 0 : wait);
		}
		else if (status == LUA_OK) {
			ReleaseThread(resource, thread);
			--activeCount;
		}
		else {
			const CHAR* error = lua_tostring(thread->State, -1);
			DbgPrint("[FiveX][Lua][%s] Runtime error: %s\n",
				resource->Info.Name, error ? error : "unknown");
			Notify::Error("Lua error in %s", resource->Info.Name);
			ReleaseThread(resource, thread);
			--activeCount;
		}
	}
	resource->Info.ThreadCount = activeCount;
	resource->Info.MemoryUsed = resource->Allocator.Used;
	lua_gc(resource->State, LUA_GCSTEP, 16);
}

static BOOL StartResourceInternal(FiveXLuaResource* resource, INT depth) {
	if (!resource || depth > FIVEX_LUA_MAX_DEPENDENCIES)
		return FALSE;
	if (resource->Info.State == FiveXLuaResourceStarted)
		return TRUE;
	if (resource->Info.State == FiveXLuaResourceStarting) {
		DbgPrint("[FiveX][Lua] Circular dependency involving %s.\n", resource->Info.Name);
		return FALSE;
	}
	resource->Info.State = FiveXLuaResourceStarting;
	ZeroMemory(resource->Threads, sizeof(resource->Threads));
	resource->HandlerCount = 0;
	resource->ExportCount = 0;
	resource->OwnedEntityCount = 0;
	if (!ParseManifest(resource)) {
		resource->Info.State = FiveXLuaResourceFailed;
		DbgPrint("[FiveX][Lua] Invalid or empty manifest: %s\n", resource->Info.Name);
		return FALSE;
	}
	for (INT index = 0; index < resource->DependencyCount; ++index) {
		FiveXLuaResource* dependency = FindResource(resource->Dependencies[index]);
		if (!dependency || !StartResourceInternal(dependency, depth + 1)) {
			resource->Info.State = FiveXLuaResourceFailed;
			DbgPrint("[FiveX][Lua] Dependency unavailable: %s -> %s\n",
				resource->Info.Name, resource->Dependencies[index]);
			return FALSE;
		}
	}

	resource->Allocator.Used = 0;
	resource->Allocator.Limit = FIVEX_LUA_MEMORY_LIMIT;
	resource->Info.MemoryLimit = resource->Allocator.Limit;
	resource->State = lua_newstate(LuaAllocate, &resource->Allocator);
	if (!resource->State) {
		resource->Info.State = FiveXLuaResourceFailed;
		return FALSE;
	}
	OpenResourceLibraries(resource->State);
	RegisterResourceApi(resource);
	resource->Info.State = FiveXLuaResourceStarted;
	for (INT index = 0; index < resource->Info.ScriptCount; ++index) {
		if (!LoadScriptThread(resource, resource->Scripts[index])) {
			resource->Info.State = FiveXLuaResourceFailed;
			break;
		}
	}
	if (resource->Info.State == FiveXLuaResourceFailed) {
		lua_close(resource->State);
		resource->State = NULL;
		resource->Allocator.Used = 0;
		ZeroMemory(resource->Threads, sizeof(resource->Threads));
		resource->HandlerCount = 0;
		resource->ExportCount = 0;
		resource->OwnedEntityCount = 0;
		return FALSE;
	}

	// First resume loads top-level declarations before onResourceStart.
	ResumeResourceThreads(resource);
	lua_pushstring(resource->State, resource->Info.Name);
	DispatchEvent(resource->State, "onResourceStart", -1, 1, resource);
	lua_pop(resource->State, 1);
	ResumeResourceThreads(resource);
	DbgPrint("[FiveX][Lua] Resource started: %s scripts=%d\n",
		resource->Info.Name, resource->Info.ScriptCount);
	Notify::Success("Lua resource started: %s", resource->Info.Name);
	return TRUE;
}

static VOID CleanupOwnedEntities(FiveXLuaResource* resource) {
	if (!resource)
		return;
	for (INT index = 0; index < resource->OwnedEntityCount; ++index) {
		Entity entity = resource->OwnedEntities[index];
		if (entity && DoesEntityExist(entity))
			DeleteEntity(&entity);
	}
	resource->OwnedEntityCount = 0;
}

static BOOL StopResourceInternal(FiveXLuaResource* resource) {
	if (!resource)
		return FALSE;
	if (resource->Info.State != FiveXLuaResourceStarted &&
		resource->Info.State != FiveXLuaResourceFailed)
		return TRUE;

	// Dependents stop first so they cannot retain calls into a closed state.
	for (INT resourceIndex = 0; resourceIndex < g_resourceCount; ++resourceIndex) {
		FiveXLuaResource* dependent = &g_resources[resourceIndex];
		if (dependent == resource || dependent->Info.State != FiveXLuaResourceStarted)
			continue;
		for (INT dependencyIndex = 0; dependencyIndex < dependent->DependencyCount; ++dependencyIndex) {
			if (_stricmp(dependent->Dependencies[dependencyIndex], resource->Info.Name) == 0) {
				StopResourceInternal(dependent);
				break;
			}
		}
	}

	if (resource->State && resource->Info.State == FiveXLuaResourceStarted) {
		lua_pushstring(resource->State, resource->Info.Name);
		DispatchEvent(resource->State, "onResourceStop", -1, 1, resource);
		lua_pop(resource->State, 1);
		ResumeResourceThreads(resource);
	}
	CleanupOwnedEntities(resource);
	if (resource->State)
		lua_close(resource->State);
	resource->State = NULL;
	resource->Allocator.Used = 0;
	resource->Info.MemoryUsed = 0;
	resource->Info.ThreadCount = 0;
	resource->HandlerCount = 0;
	resource->ExportCount = 0;
	ZeroMemory(resource->Threads, sizeof(resource->Threads));
	resource->Info.State = FiveXLuaResourceStopped;
	DbgPrint("[FiveX][Lua] Resource stopped: %s\n", resource->Info.Name);
	return TRUE;
}

static BOOL DiscoverResource(const CHAR* fileName, DWORD attributes, PVOID context) {
	if ((attributes & FILE_ATTRIBUTE_DIRECTORY) == 0 || !IsSafeResourceName(fileName))
		return TRUE;
	FiveXLuaResource* resource = FindResource(fileName);
	if (!resource) {
		resource = AllocateResourceSlot();
		if (!resource)
			return FALSE;
		ZeroMemory(resource, sizeof(*resource));
		resource->Catalogued = TRUE;
		CopyText(resource->Info.Name, sizeof(resource->Info.Name), fileName);
		resource->Info.State = FiveXLuaResourceStopped;
		resource->Info.MemoryLimit = FIVEX_LUA_MEMORY_LIMIT;
		const CHAR* root = context ? (const CHAR*)context : FiveXPathResources();
		if (FiveXPathBuild(resource->Root, sizeof(resource->Root), root, fileName) != FiveXFileOk) {
			ZeroMemory(resource, sizeof(*resource));
			while (g_resourceCount > 0 && !g_resources[g_resourceCount - 1].Catalogued)
				--g_resourceCount;
			return TRUE;
		}
	}
	resource->FoundDuringRefresh = TRUE;
	return TRUE;
}

VOID FiveXLuaResourceRefresh() {
	if (!g_initialized)
		return;
	for (INT index = 0; index < g_resourceCount; ++index) {
		if (g_resources[index].Catalogued)
			g_resources[index].FoundDuringRefresh = FALSE;
	}
	const CHAR* roots[] = { FiveXPathResources(), "Usb0:\\FiveX\\Resources", "Usb1:\\FiveX\\Resources" };
	DWORD count = 0;
	for (DWORD rootIndex = 0; rootIndex < ARRAYSIZE(roots); ++rootIndex) {
		// Missing storage devices and absent optional resource folders are
		// normal. Skip them before enumeration so they do not pollute the log.
		if (!FiveXDirectoryExists(roots[rootIndex]))
			continue;
		CHAR pattern[FIVEX_MAX_PATH];
		if (FiveXPathBuild(pattern, sizeof(pattern), roots[rootIndex], "*") == FiveXFileOk)
			FiveXFileEnumerate(pattern, DiscoverResource, (PVOID)roots[rootIndex], &count);
	}
	for (INT index = 0; index < g_resourceCount; ++index) {
		FiveXLuaResource* resource = &g_resources[index];
		if (!resource->Catalogued || resource->FoundDuringRefresh)
			continue;
		StopResourceInternal(resource);
		DbgPrint("[FiveX][Lua] Resource removed from catalog: %s\n",
			resource->Info.Name);
		ZeroMemory(resource, sizeof(*resource));
	}
	while (g_resourceCount > 0 && !g_resources[g_resourceCount - 1].Catalogued)
		--g_resourceCount;
	DbgPrint("[FiveX][Lua] Resource scan complete. Discovered=%d\n",
		FiveXLuaResourceCount());
}

BOOL FiveXLuaRuntimeInitialize() {
	if (g_initialized)
		return TRUE;
	ZeroMemory(g_resources, sizeof(g_resources));
	g_resourceCount = 0;
	g_pendingActionCount = 0;
	g_ticking = FALSE;
	g_initialized = TRUE;
	FiveXEnsureDirectory(FiveXPathResources());
	FiveXLuaResourceRefresh();
	DbgPrint("[FiveX][Lua] Runtime initialized. Version=%s\n", LUA_RELEASE);
	return TRUE;
}

static VOID ProcessPendingActions() {
	FiveXLuaPendingAction pending[FIVEX_LUA_MAX_PENDING_ACTIONS];
	INT count = g_pendingActionCount;
	if (count > FIVEX_LUA_MAX_PENDING_ACTIONS)
		count = FIVEX_LUA_MAX_PENDING_ACTIONS;
	memcpy(pending, g_pendingActions, sizeof(FiveXLuaPendingAction) * count);
	g_pendingActionCount = 0;
	for (INT index = 0; index < count; ++index) {
		if (pending[index].Type == FiveXLuaPendingStart)
			FiveXLuaResourceStart(pending[index].Name);
		else if (pending[index].Type == FiveXLuaPendingStop)
			FiveXLuaResourceStop(pending[index].Name);
		else
			FiveXLuaResourceRestart(pending[index].Name);
	}
}

VOID FiveXLuaRuntimeTick() {
	if (!g_initialized)
		return;
	ProcessPendingActions();
	g_ticking = TRUE;
	for (INT index = 0; index < g_resourceCount; ++index)
		ResumeResourceThreads(&g_resources[index]);
	g_ticking = FALSE;
	ProcessPendingActions();
}

VOID FiveXLuaRuntimeShutdown() {
	if (!g_initialized)
		return;
	FiveXLuaResourceStopAll();
	g_resourceCount = 0;
	g_pendingActionCount = 0;
	g_initialized = FALSE;
	DbgPrint("[FiveX][Lua] Runtime shutdown completed.\n");
}

INT FiveXLuaResourceCount() {
	INT count = 0;
	for (INT index = 0; index < g_resourceCount; ++index) {
		if (g_resources[index].Catalogued)
			++count;
	}
	return count;
}

const FiveXLuaResourceInfo* FiveXLuaResourceGet(INT index) {
	if (index < 0)
		return NULL;
	INT visibleIndex = 0;
	for (INT slot = 0; slot < g_resourceCount; ++slot) {
		if (!g_resources[slot].Catalogued)
			continue;
		if (visibleIndex++ == index)
			return &g_resources[slot].Info;
	}
	return NULL;
}

const CHAR* FiveXLuaResourceStateText(INT index) {
	const FiveXLuaResourceInfo* resource = FiveXLuaResourceGet(index);
	if (!resource)
		return "~o~INVALID";
	switch (resource->State) {
	case FiveXLuaResourceStarted: return "~g~STARTED";
	case FiveXLuaResourceStarting: return "~y~STARTING";
	case FiveXLuaResourceFailed: return "~o~FAILED";
	default: return "~r~STOPPED";
	}
}

BOOL FiveXLuaResourceStart(const CHAR* name) {
	if (g_ticking)
		return QueueAction(name, FiveXLuaPendingStart);
	FiveXLuaResource* resource = FindResource(name);
	return StartResourceInternal(resource, 0);
}

BOOL FiveXLuaResourceStop(const CHAR* name) {
	if (g_ticking)
		return QueueAction(name, FiveXLuaPendingStop);
	return StopResourceInternal(FindResource(name));
}

BOOL FiveXLuaResourceRestart(const CHAR* name) {
	if (g_ticking)
		return QueueAction(name, FiveXLuaPendingRestart);
	FiveXLuaResource* resource = FindResource(name);
	if (!resource)
		return FALSE;
	StopResourceInternal(resource);
	return StartResourceInternal(resource, 0);
}

VOID FiveXLuaResourceStopAll() {
	for (INT index = g_resourceCount - 1; index >= 0; --index)
		StopResourceInternal(&g_resources[index]);
}
