#ifndef RUSH2_GHOST_H
#define RUSH2_GHOST_H

#include <stage/gameObject.h>

// --------------------
// ENUMS
// --------------------

enum GhostVisibilityMode_
{
    GHOST_VISIBILITY_OPAQUE,
    GHOST_VISIBILITY_TRANSPARENT,
    GHOST_VISIBILITY_FLASHING,
    GHOST_VISIBILITY_INVISIBLE,
};
typedef u8 GhostVisibilityMode;

// --------------------
// STRUCTS
// --------------------

typedef struct EnemyGhost_
{
    GameObjectTask gameWork;
    OBS_RECT_WORK collider;
    Vec2Fx32 targetPos;
    fx32 velocityStore;
    fx32 xMin;
    fx32 field_3B4;
    fx32 xMax;
    fx32 field_3BC;
    u16 angle;
    GhostVisibilityMode visibilityMode;
    u32 visibilityTimer;
    OBS_ACTION2D_BAC_WORK aniMachine;
    u32 machineDisplayFlag;
} EnemyGhost;

typedef struct EnemyGhostBomb_
{
    GameObjectTask gameWork;
} EnemyGhostBomb;

// --------------------
// FUNCTIONS
// --------------------

EnemyGhost *CreateGhost(MapObject *mapObject, fx32 x, fx32 y, fx32 type);
EnemyGhostBomb *CreateGhostBomb(MapObject *mapObject, fx32 x, fx32 y, fx32 type);

#endif // RUSH2_GHOST_H