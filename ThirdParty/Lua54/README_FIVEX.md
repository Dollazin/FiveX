# Lua runtime provenance

FiveX embeds upstream Lua 5.4.8 as the Xbox-compatible core for its
FiveM-compatible client resource runtime.

FiveM currently tracks the citizenfx/lua branch luaglm-548, which is based
on Lua 5.4.8 and adds CfxLua/GLM extensions. Those GLM extensions require a
modern C++ toolchain that is not available in the Xbox 360 XDK 2010 compiler.
FiveX therefore uses the matching upstream 5.4.8 core and supplies its own
Xbox-compatible vector3, scheduler, events, exports, and resource lifecycle.

Upstream source:

- https://www.lua.org/ftp/lua-5.4.8.tar.gz
- SHA-256: 4f18ddae154e793e46eeab727c59ef1c0c0c2b744e7b94219710d76f530629ae

FiveM runtime reference:

- https://github.com/citizenfx/fivem
- https://github.com/citizenfx/lua/tree/luaglm-548

Lua's license is included in lua.h.
