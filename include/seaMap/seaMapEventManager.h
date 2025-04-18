#ifndef RUSH_SEAMAPEVENTMANAGER_H
#define RUSH_SEAMAPEVENTMANAGER_H

#include <global.h>
#include <game/system/task.h>
#include <game/graphics/sprite.h>
#include <game/stage/mapSys.h>

// --------------------
// TYPES
// --------------------

typedef struct CHEVObject_ CHEVObject;
typedef struct CHEVObjectType_ CHEVObjectType;

typedef struct SeaMapObject_ SeaMapObject;

typedef SeaMapObject *(*SeaMapObjCreateFunc)(CHEVObjectType *objectType, CHEVObject *mapObject);
typedef BOOL (*SeaMapObjViewCheck)(CHEVObject *mapObject, fx32 x, fx32 y, BOOL flag);

typedef struct SeaMapIslandDrawIcon_ SeaMapIslandDrawIcon;

// --------------------
// ENUMS
// --------------------

enum SeaMapObjectIDs
{
    SEAMAPOBJECT_ISLAND_DRAW_ICON,
    SEAMAPOBJECT_UNUSED,
    SEAMAPOBJECT_ISLAND_ICON_1,
    SEAMAPOBJECT_ISLAND_ICON_2,
    SEAMAPOBJECT_JOHNNY_ICON,
    SEAMAPOBJECT_UNKNOWN,
    SEAMAPOBJECT_CORAL_CAVE_ICON,
    SEAMAPOBJECT_SKY_BABYLON_ICON,
    SEAMAPOBJECT_TARGET_FLAG_ICON,
    SEAMAPOBJECT_BOAT_ICON,
    SEAMAPOBJECT_STYLUS_PROMPT,
    SEAMAPOBJECT_DS_POPUP,
    SEAMAPOBJECT_SPARKLES_1,
    SEAMAPOBJECT_SPARKLES_2,

    SEAMAPOBJECT_COUNT,
};

// --------------------
// STRUCTS
// --------------------

struct CHEVObject_
{
    u16 type;
    Vec2Fx16 position;
    u8 flags1;
    u8 flags2;
    HitboxRect box;
    s16 unlockID;
};

struct CHEVObjectType_
{
    u16 animID;
    u16 palette;
    u8 viewBounds[2];
    SeaMapObjCreateFunc createFunc;
    SeaMapObjViewCheck viewCheck;
};

struct SeaMapObject_
{
    Task *task;
    CHEVObjectType *objectType;
    CHEVObject *mapObject;
    Vec2Fx16 position;
};

typedef struct CHEV_
{
    u16 count;
    CHEVObject entries[1];
} CHEV;

typedef struct SeaMapVoyageVisibleIsland_
{
    CHEVObject *object;
    u32 radius;
} SeaMapVoyageVisibleIsland;

typedef struct SeaMapEventManager_
{
    s32 lastTouchedIconType;
    SeaMapIslandDrawIcon *lastTouchedIcon;
    CHEVObject objectList[16];
    AnimatorSprite aniJohnny;
    AnimatorSprite aniJohnnyDefeated;
    AnimatorSprite aniTargetFlag;
    Task *dsPopup;
    Task *coralCaveIcon;
    Task *skyBabylonIcon;
} SeaMapEventManager;

// --------------------
// VARIABLES
// --------------------

extern Task *SeaMapEventManager__Singleton;

extern CHEVObjectType SeaMapEventManager__ObjectList[SEAMAPOBJECT_COUNT];

// --------------------
// FUNCTIONS
// --------------------

NOT_DECOMPILED BOOL SeaMapEventManager__CheckFeatureUnlocked(u32 id);
NOT_DECOMPILED void SeaMapEventManager__Create(void);
NOT_DECOMPILED void SeaMapEventManager__Destroy(void);
NOT_DECOMPILED SeaMapObject *SeaMapEventManager__CreateObject(s32 type, s16 x, s16 y, u8 flags, HitboxRect *box, s16 unlockID);
NOT_DECOMPILED SeaMapEventManager *SeaMapEventManager__GetWork2(void);
NOT_DECOMPILED void SeaMapEventManager__Func_2046A78(void);
NOT_DECOMPILED void SeaMapEventManager__Func_2046A94(void *a1);
NOT_DECOMPILED CHEVObject *SeaMapEventManager__GetObjectFromID(u32 id);
NOT_DECOMPILED void SeaMapEventManager__FindVisibleIslands(fx32 shipX, fx32 shipY, fx32 distanceThreshold, SeaMapVoyageVisibleIsland *islandList, u16 *islandCount);
NOT_DECOMPILED u32 SeaMapEventManager__GetObjectType(CHEVObject *obj);
NOT_DECOMPILED BOOL SeaMapEventManager__ObjectIsActive(CHEVObject *obj);
NOT_DECOMPILED u32 SeaMapEventManager__Func_2046CE8(u32 id);
NOT_DECOMPILED u32 SeaMapEventManager__Func_2046EEC(u32 id);
NOT_DECOMPILED void SeaMapEventManager__SetBoatFlipX(SeaMapObject *boat, BOOL enabled);
NOT_DECOMPILED SeaMapObject *SeaMapEventManager__CreateStylusIcon(fx32 startX, fx32 startY, fx32 endX, fx32 endY, s16 speed);
NOT_DECOMPILED void SeaMapEventManager__DestroyStylusIcon(SeaMapObject *work);
NOT_DECOMPILED void SeaMapEventManager__CreateDSPopup(void);
NOT_DECOMPILED void SeaMapEventManager__DestroyDSPopup(void);
NOT_DECOMPILED SeaMapObject *SeaMapEventManager__UnlockCoralCave(void);
NOT_DECOMPILED SeaMapObject *SeaMapEventManager__UnlockSkyBabylon(void);
NOT_DECOMPILED void SeaMapEventManager__Func_20471B8(AnimatorSprite *animator, SpriteFrameCallback callback, void *userData);
NOT_DECOMPILED BOOL SeaMapEventManager__IslandEnabled(u32 id);
NOT_DECOMPILED SeaMapEventManager *SeaMapEventManager__GetWork(void);
NOT_DECOMPILED void SeaMapEventManager__SpawnObjects1(void);
NOT_DECOMPILED void SeaMapEventManager__SpawnObjects2(void);
NOT_DECOMPILED void SeaMapEventManager__Func_20473C0(Task *task);
NOT_DECOMPILED void SeaMapEventManager__InitMapObject(SeaMapObject *work, Task *task, CHEVObjectType *objectType, CHEVObject *mapObject);
NOT_DECOMPILED void SeaMapEventManager__DestroyObject(SeaMapObject *work);
NOT_DECOMPILED BOOL SeaMapEventManager__ObjectInBounds(Vec2Fx16 *objPos, u8 *a2);
NOT_DECOMPILED void SeaMapEventManager__Func_20474FC(Vec2Fx16 *a1, Vec2Fx16 *a2);
NOT_DECOMPILED void SeaMapEventManager__SetObjectAsActive(SeaMapObject *work);
NOT_DECOMPILED void SeaMapEventManager__SetObjectAsInactive(SeaMapObject *work);
NOT_DECOMPILED BOOL SeaMapEventManager__Func_204756C(CHEVObject *object);
NOT_DECOMPILED void SeaMapEventManager__GetViewRect2(HitboxRect *rect, fx32 x, fx32 y, s32 *right, s32 *bottom, s32 *left, s32 *top);
NOT_DECOMPILED void SeaMapEventManager__GetViewRect(HitboxRect *rect, fx32 x, fx32 y, ViewRect *viewRect);
NOT_DECOMPILED BOOL SeaMapEventManager__PointInViewRect2(s32 left, s32 top, s32 right, s32 bottom, fx32 x, fx32 y);
NOT_DECOMPILED BOOL SeaMapEventManager__PointInViewRect(s32 left, s32 top, s32 right, s32 bottom, fx32 x, fx32 y);
NOT_DECOMPILED BOOL SeaMapEventManager__ViewRectCheck(CHEVObject *object, fx32 x, fx32 y);
NOT_DECOMPILED BOOL SeaMapEventManager__ViewRectCheck2(CHEVObject *mapObject, fx32 x, fx32 y);

#endif // RUSH_SEAMAPEVENTMANAGER_H