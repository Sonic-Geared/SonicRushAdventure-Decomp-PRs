#ifndef RUSH_EFFECT_RING_SPARKLE_H
#define RUSH_EFFECT_RING_SPARKLE_H

#include <stage/effectTask.h>

// --------------------
// STRUCTS
// --------------------

typedef struct EffectRingSparkle_
{
    StageTask objWork;
    
    OBS_ACTION2D_BAC_WORK ani;
} EffectRingSparkle;

// --------------------
// FUNCTIONS
// --------------------

EffectRingSparkle *EffectRingSparkle__Create(fx32 x, fx32 y, fx32 velX, fx32 velY, fx32 accX, fx32 accY);
void EffectRingSparkle__Destructor(Task *task);

#endif // RUSH_EFFECT_RING_SPARKLE_H