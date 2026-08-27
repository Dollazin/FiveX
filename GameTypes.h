#pragma once

#include "FiveXKernel.h"

// POD-only game types. Keep these free of constructors and dynamic state so
// they remain safe across repeated module load/unload/reload cycles.
struct Vector3 {
	FLOAT x;
	FLOAT y;
	FLOAT z;
};

// GTA V script-domain aliases used by the complete Xbox 360 native catalog.
// They intentionally remain 32-bit POD values, matching the native ABI.
typedef INT Any;
typedef INT Hash;
typedef INT Entity;
typedef INT Player;
typedef INT FireId;
typedef INT Ped;
typedef INT Vehicle;
typedef INT Cam;
typedef INT Group;
typedef INT Train;
typedef INT Pickup;
typedef INT Object;
typedef INT Weapon;
typedef INT Blip;
typedef INT Bone;
typedef INT Texture;
typedef INT TextureDict;
typedef INT Camera;
typedef INT TaskSequence;
typedef INT ColourIndex;
typedef INT ScrHandle;
