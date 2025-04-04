#ifndef RUSH_EFFECT_HOVER_CRYSTAL_SPARKLE_H
#define RUSH_EFFECT_HOVER_CRYSTAL_SPARKLE_H

#include <stage/effectTask.h>

// --------------------
// CONSTANTS
// --------------------

#define EFFECT_HOVERCRYSTALSPARKLE_PARTICLE_COUNT 32

// --------------------
// STRUCTS
// --------------------

struct EffectHoverCrystalParticle
{
    Vec2Fx32 position;
    Vec2Fx32 velocity;
    Vec2Fx32 acceleration;
    u16 timer;
};

typedef struct EffectHoverCrystalSparkle_
{
    StageTask objWork;

    OBS_ACTION2D_BAC_WORK ani;
    s16 listCount;
    s16 listStartSlot;
    struct EffectHoverCrystalParticle list[EFFECT_HOVERCRYSTALSPARKLE_PARTICLE_COUNT];
} EffectHoverCrystalSparkle;

// --------------------
// FUNCTIONS
// --------------------

EffectHoverCrystalSparkle *EffectHoverCrystalSparkle__Create(fx32 x, fx32 y, fx32 velX, fx32 velY, fx32 accX, fx32 accY);
void EffectHoverCrystalSparkle__Destructor(Task *task);
void EffectHoverCrystalSparkle__State_202CFB8(EffectHoverCrystalSparkle *work);
void EffectHoverCrystalSparkle__Draw(void);

#endif // RUSH_EFFECT_HOVER_CRYSTAL_SPARKLE_H