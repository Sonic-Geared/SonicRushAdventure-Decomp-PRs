#ifndef RUSH2_SEAMAPISLANDICON_H
#define RUSH2_SEAMAPISLANDICON_H

#include <seaMap/seaMapEventManager.h>
#include <seaMap/seaMapUnknown204A9E4.h>

// --------------------
// ENUMS
// --------------------

// --------------------
// STRUCTS
// --------------------

typedef struct SeaMapIslandIcon_
{
    SeaMapObject objWork;
    s32 field_10;
    SeaMapUnknown204A9E4Object *objectUnknown;
} SeaMapIslandIcon;

// --------------------
// FUNCTIONS
// --------------------

NOT_DECOMPILED SeaMapObject *SeaMapIslandIcon__Create(CHEVObjectType *objectType, CHEVObject *mapObject);
NOT_DECOMPILED void SeaMapIslandIcon__Destructor2(Task *task);
NOT_DECOMPILED void SeaMapIslandIcon__Main1(void);
NOT_DECOMPILED void SeaMapIslandIcon__Main2(void);
NOT_DECOMPILED void SeaMapIslandIcon__Destructor1(Task *task);
NOT_DECOMPILED void SeaMapIslandIcon__Func_2048824(CHEVObject *mapObject);
NOT_DECOMPILED BOOL SeaMapIslandIcon__ViewCheck(CHEVObject *mapObject, fx32 x, fx32 y, BOOL flag);

#endif // RUSH2_SEAMAPISLANDICON_H