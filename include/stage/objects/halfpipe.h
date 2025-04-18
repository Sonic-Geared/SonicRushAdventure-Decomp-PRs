#ifndef RUSH_HALFPIPE_H
#define RUSH_HALFPIPE_H

#include <stage/gameObject.h>

// --------------------
// STRUCTS
// --------------------

typedef struct Halfpipe_
{
    GameObjectTask gameWork;
} Halfpipe;

// --------------------
// FUNCTIONS
// --------------------

Halfpipe *CreateHalfpipe(MapObject *mapObject, fx32 x, fx32 y, fx32 type);

#endif // RUSH_HALFPIPE_H
