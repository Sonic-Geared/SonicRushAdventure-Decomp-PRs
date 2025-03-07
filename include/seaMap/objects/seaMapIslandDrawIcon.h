#ifndef RUSH_SEAMAPISLANDDRAWICON_H
#define RUSH_SEAMAPISLANDDRAWICON_H

#include <seaMap/seaMapEventManager.h>
#include <game/util/spriteButton.h>
#include <game/input/touchField.h>

// --------------------
// ENUMS
// --------------------

// --------------------
// STRUCTS
// --------------------

struct SeaMapIslandDrawIcon_
{
    SeaMapObject objWork;
    SpriteButtonAnimator aniDrawIcon;
};

// --------------------
// FUNCTIONS
// --------------------

NOT_DECOMPILED BOOL SeaMapIslandDrawIcon__CanDrawFrom(CHEVObject *mapObject);
NOT_DECOMPILED BOOL SeaMapIslandDrawIcon__IsActive(SeaMapIslandDrawIcon *work);
NOT_DECOMPILED BOOL SeaMapIslandDrawIcon__IsEnabled(CHEVObject *mapObject);
NOT_DECOMPILED SeaMapObject *SeaMapIslandDrawIcon__Create(CHEVObjectType *objectType, CHEVObject *mapObject);
NOT_DECOMPILED void SeaMapIslandDrawIcon__Main(void);
NOT_DECOMPILED void SeaMapIslandDrawIcon__Destructor(Task *task);
NOT_DECOMPILED void SeaMapIslandDrawIcon__TouchAreaCallback(TouchAreaResponse *response, TouchArea *area, void *userData);
NOT_DECOMPILED void SeaMapIslandDrawIcon__RectCheck1(Vec2Fx16 *pos, HitboxRect *rect);
NOT_DECOMPILED void SeaMapIslandDrawIcon__RectCheck2(Vec2Fx16 *pos, HitboxRect *rect);
NOT_DECOMPILED void SeaMapIslandDrawIcon__CreateSparkles(CHEVObject *mapObject);

#endif // RUSH_SEAMAPISLANDDRAWICON_H