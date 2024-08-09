#ifndef RUSH2_EFFECT_GOAL_JEWEL_H
#define RUSH2_EFFECT_GOAL_JEWEL_H

#include <stage/effectTask.h>

// --------------------
// STRUCTS
// --------------------

typedef struct EffectGoalJewel_
{
    EffectTask objWork;
    
    OBS_ACTION2D_BAC_WORK ani;
} EffectGoalJewel;

// --------------------
// FUNCTIONS
// --------------------

EffectGoalJewel *EffectGoalJewel__Create(u32 type, fx32 x, fx32 y, fx32 velX, fx32 velY);

#endif // RUSH2_EFFECT_GOAL_JEWEL_H