#include "NativeLoop.h"
#include "HookEngine.h"
#include "LoopScheduler.h"
#include "CoreNatives.h"
#include "Lifecycle.h"

static FiveXHook g_hook;
static DWORD(*g_original)(DWORD,DWORD,DWORD,PVOID);
static DWORD g_frame;
static DWORD Hook(DWORD a,DWORD b,DWORD c,PVOID d) {
    FiveXCallbackEnter();
    DWORD current=GetFrameCount();
    if(current!=g_frame) { g_frame=current; FiveXLoopTick(); }
    DWORD result = g_original ? g_original(a,b,c,d) : 0;
    FiveXCallbackLeave();
    return result;
}
BOOL FiveXNativeLoopInitialize() { FiveXHookReset(&g_hook); g_frame=0xFFFFFFFF; FiveXLoopPrepare(); return FiveXHookInstall(&g_hook,0x83525E00,(PVOID)Hook,(PVOID*)&g_original); }
BOOL FiveXNativeLoopShutdown() { FiveXLoopRequestStop(); return FiveXHookRemove(&g_hook); }
