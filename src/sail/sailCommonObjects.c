#include <sail/sailCommonObjects.h>
#include <game/object/obj.h>
#include <game/object/objectManager.h>
#include <game/graphics/screenShake.h>
#include <sail/sailAudio.h>
#include <game/math/unknown2066510.h>
#include <sail/sailPlayer.h>

// --------------------
// TEMP
// --------------------

NOT_DECOMPILED void EffectSailHit__Create(VecFx32 *position);
NOT_DECOMPILED void EffectSailBomb__Create(VecFx32 *position);
NOT_DECOMPILED void EffectUnknown2161544__Create(StageTask *parent, VecFx32 *position);
NOT_DECOMPILED void EffectSailWater06__Create(VecFx32 *position);
NOT_DECOMPILED void EffectSailGuard__Create(VecFx32 *position);
NOT_DECOMPILED void EffectSailUnknown21625C8__Create(VecFx32 *position);

// --------------------
// VARIABLES
// --------------------

static const s16 _0218BC64[] = { 0x80, 0x100, 0x80, 0x20, -0x80, -0x100, -0x80, -0x20 };

NOT_DECOMPILED const char *aSbLandBac;
NOT_DECOMPILED const char *aSbMineBac_0;
NOT_DECOMPILED const char *aSbBomberBac;
NOT_DECOMPILED const char *aSbCloudBac_0;
NOT_DECOMPILED const char *aSbBuoyNsbmd_0;
NOT_DECOMPILED const char *aSbBuoyNsbca;
NOT_DECOMPILED const char *aSbSeagullBac;
NOT_DECOMPILED const char *aSbSeagullNsbmd_0;
NOT_DECOMPILED const char *aSbStoneNsbmd_0;

// --------------------
// FUNCTIONS
// --------------------

void SailObject__InitCommon(StageTask *work)
{
    Animator3D *aniModel = NULL;

    if (work->obj_3d != NULL || work->obj_3des != NULL)
    {
        if (work->obj_3d != NULL)
            aniModel = &work->obj_3d->ani.work;
        else
            aniModel = &work->obj_3des->ani.work;

        aniModel->scale.x = FLOAT_TO_FX32(0.125);
        aniModel->scale.y = FLOAT_TO_FX32(0.125);
        aniModel->scale.z = FLOAT_TO_FX32(0.125);
        work->displayFlag |= DISPLAY_FLAG_DISABLE_ROTATION;

        SetTaskOutFunc(work, SailObject__Draw_Default);
    }

    if (work->obj_2dIn3d != NULL)
    {
        work->scale.x = FLOAT_TO_FX32(0.03125);
        work->scale.y = FLOAT_TO_FX32(0.03125);
        work->scale.z = FLOAT_TO_FX32(0.03125);
        work->displayFlag |= DISPLAY_FLAG_DISABLE_ROTATION;
    }

    if ((work->userFlag & SAILOBJECT_FLAG_10000000) == 0)
    {
        switch (SailManager__GetShipType())
        {
            case SHIP_JET:
                if ((work->userFlag & SAILOBJECT_FLAG_40000000) != 0)
                {
                    fx32 scale        = MultiplyFX(FLOAT_TO_FX32(0.1796875), aniModel->scale.x);
                    aniModel->scale.x = scale;
                    aniModel->scale.y = scale;
                    aniModel->scale.z = scale;
                }
                break;

            case SHIP_BOAT:
                if ((work->userFlag & SAILOBJECT_FLAG_20000000) == 0 && (work->userFlag & SAILOBJECT_FLAG_40000000) == 0 && (work->userFlag & SAILOBJECT_FLAG_80000000) == 0)
                {
                    if (aniModel != NULL)
                    {
                        fx32 scale = MultiplyFX(FLOAT_TO_FX32(4.0), aniModel->scale.x);

                        aniModel->scale.x = scale;
                        aniModel->scale.y = scale;
                        aniModel->scale.z = scale;
                    }
                    else if (work->obj_2dIn3d != NULL)
                    {
                        fx32 scale = MultiplyFX(FLOAT_TO_FX32(4.0), work->scale.x);

                        work->scale.x = scale;
                        work->scale.y = scale;
                        work->scale.z = scale;
                    }
                }
                break;

            case SHIP_SUBMARINE:
                if ((work->userFlag & SAILOBJECT_FLAG_20000000) == 0 && (work->userFlag & SAILOBJECT_FLAG_40000000) == 0 && (work->userFlag & SAILOBJECT_FLAG_80000000) == 0)
                {
                    if (aniModel != NULL)
                    {
                        fx32 scale = MultiplyFX(FLOAT_TO_FX32(4.0), aniModel->scale.x);

                        aniModel->scale.x = scale;
                        aniModel->scale.y = scale;
                        aniModel->scale.z = scale;
                    }
                    else if (work->obj_2dIn3d != NULL)
                    {
                        fx32 scale = MultiplyFX(FLOAT_TO_FX32(4.0), work->scale.x);

                        work->scale.x = scale;
                        work->scale.y = scale;
                        work->scale.z = scale;
                    }
                }
                break;

            case SHIP_HOVER:
                if ((work->userFlag & SAILOBJECT_FLAG_40000000) != 0)
                {
                    fx32 scale        = MultiplyFX(FLOAT_TO_FX32(0.1796875), aniModel->scale.x);
                    aniModel->scale.x = scale;
                    aniModel->scale.y = scale;
                    aniModel->scale.z = scale;
                }
                break;
        }
    }

    SailObject__SetAnimSpeed(work, FLOAT_TO_FX32(1.0));

    SetTaskInFunc(work, SailObject__In_Default);

    if (work->objType == SAILSTAGE_OBJ_TYPE_OBJECT)
        SetTaskLastFunc(work, SailObject__Last_Default);

    if (work->objType == SAILSTAGE_OBJ_TYPE_OBJECT)
    {
        SailObject *worker = GetStageTaskWorker(work, SailObject);
        worker->player     = SailManager__GetWork()->sailPlayer;
        worker->field_124  = FLOAT_TO_FX32(1.0);

        SetTaskViewCheckFunc(work, SailObject__ViewCheck_Default);
        work->flag &= ~STAGE_TASK_FLAG_DISABLE_VIEWCHECK_EVENT;
        work->userFlag |= SAILOBJECT_FLAG_40;
        SetTaskDestructorEvent(work->taskRef, SailObject__Destructor);
    }

    SailObject__SetLightColors(work, 0);

    work->flag |= STAGE_TASK_FLAG_DISABLE_SHAKE;
}

void SailObject__InitFromMapObject(StageTask *work, SailEventManagerObject *mapObject)
{
    SailObject *worker               = GetStageTaskWorker(work, SailObject);
    SailVoyageManager *voyageManager = SailManager__GetWork()->voyageManager;

    if (mapObject != NULL)
    {
        work->position    = mapObject->position;
        worker->objectRef = NULL;

        if ((mapObject->flags & SAILMAPOBJECT_FLAG_20000000) == 0)
        {
            mapObject->objTask   = work;
            worker->objectRadius = mapObject->unknown;
            worker->segmentID    = mapObject->segmentID;
            worker->objectAngle  = mapObject->angle;

            s32 segmentPos = FX_Div(worker->objectRadius.z & 0x7FFFF, SailVoyageManager__GetSegmentSize(&voyageManager->segmentList[mapObject->segmentID]));
            SailVoyageManager__Func_2158888(&voyageManager->segmentList[mapObject->segmentID], segmentPos, &worker->field_1C.x, &worker->field_1C.z);
            worker->objectRef = mapObject;
        }
    }
}

void SailObject__SetAnimSpeed(StageTask *work, fx32 speed)
{
    if (work->obj_3d != NULL)
    {
        work->obj_3d->ani.speedMultiplier = MultiplyFX(speed, FLOAT_TO_FX32(2.0));
    }

    if (work->obj_2d != NULL)
    {
        work->obj_2d->ani.work.animAdvance = MultiplyFX(speed, FLOAT_TO_FX32(2.0));
    }

    if (work->obj_2dIn3d != NULL)
    {
        work->obj_2dIn3d->ani.animatorSprite.animAdvance = MultiplyFX(speed, FLOAT_TO_FX32(2.0));
    }
}

void SailObject__HandleParentFollow(StageTask *work)
{
    StageTask *parent = work->parentObj;

    work->dir.y = parent->dir.y;

    VecFx32 offset;
    MtxFx33 mtx;
    MTX_RotY33(&mtx, SinFX(work->dir.y), CosFX(work->dir.y));
    MTX_MultVec33(&work->parentOffset, &mtx, &offset);

    work->position.x = parent->position.x + offset.x;
    work->position.y = parent->position.y + offset.y;
    work->position.z = parent->position.z + offset.z;

    work->displayFlag &= ~DISPLAY_FLAG_NO_DRAW;
    work->displayFlag |= parent->displayFlag & DISPLAY_FLAG_NO_DRAW;
}

void SailObject__ApplyRotation(StageTask *work)
{
    Animator3D *animator;

    if (work->obj_3d != NULL)
    {
        animator = &work->obj_3d->ani.work;
    }
    else if (work->obj_3des != NULL)
    {
        animator = &work->obj_3des->ani.work;
    }
    else if (work->obj_2dIn3d != NULL)
    {
        animator = &work->obj_2dIn3d->ani.work;
    }
    else
    {
        return;
    }

    MtxFx33 mtx;
    MTX_Identity33(&animator->rotation);

    if (work->dir.x != FLOAT_DEG_TO_IDX(0.0))
    {
        MTX_RotX33(&mtx, SinFX((s32)work->dir.x), CosFX((s32)work->dir.x));
        MTX_Concat33(&animator->rotation, &mtx, &animator->rotation);
    }

    if (work->dir.z != FLOAT_DEG_TO_IDX(0.0))
    {
        MTX_RotZ33(&mtx, SinFX((s32)work->dir.z), CosFX((s32)work->dir.z));
        MTX_Concat33(&animator->rotation, &mtx, &animator->rotation);
    }

    if (work->dir.y != FLOAT_DEG_TO_IDX(0.0))
    {
        MTX_RotY33(&mtx, SinFX((s32)work->dir.y), CosFX((s32)work->dir.y));
        MTX_Concat33(&animator->rotation, &mtx, &animator->rotation);
    }
}

void SailObject__SetSpriteColor(StageTask *work, GXRgb color)
{
    if (work->obj_2dIn3d != NULL)
        work->obj_2dIn3d->ani.color = color;
}

void SailObject__In_Default(void)
{
    StageTask *work = TaskGetWorkCurrent(StageTask);

    if ((work->userFlag & SAILOBJECT_FLAG_1) == 0)
    {
        VEC_Subtract(&work->position, SailVoyageManager__GetVoyageVelocity(), &work->position);
    }

    if ((work->flag & STAGE_TASK_FLAG_DISABLE_SHAKE) != 0)
        SailObject__ShakeScreen(work, FX32_TO_WHOLE(work->shakeTimer));

    if ((work->userFlag & SAILOBJECT_FLAG_40) != 0)
    {
        SailObject *worker = GetStageTaskWorker(work, SailObject);
        if (worker == NULL)
            return;

        if (worker->player != NULL && (worker->player->flag & STAGE_TASK_FLAG_DESTROYED) != 0)
            worker->player = NULL;

        if (worker->collidedObj != NULL && (worker->collidedObj->flag & STAGE_TASK_FLAG_DESTROYED) != 0)
            worker->collidedObj = NULL;

        if (worker->targetHUD != NULL && (worker->targetHUD->flag & STAGE_TASK_FLAG_DESTROYED) != 0)
            worker->targetHUD = NULL;
    }

    if (work->objType == SAILSTAGE_OBJ_TYPE_OBJECT)
    {
        SailManager *manager             = SailManager__GetWork();
        SailObject *worker               = GetStageTaskWorker(work, SailObject);
        SailVoyageManager *voyageManager = manager->voyageManager;

        if (worker == NULL)
            return;

        worker->objectRadius.z += voyageManager->field_74;

        // in the submarine, distant objects should appear darker than closer ones.
        if (SailManager__GetShipType() == SHIP_SUBMARINE)
        {
            fx32 x   = MATH_ABS(work->position.x);
            fx32 z   = MATH_ABS(work->position.z);
            fx32 pos = MT_MATH_MAX(x, z);

            fx32 distance = FLOAT_TO_FX32(1.0);
            if (pos > FLOAT_TO_FX32(96.0))
            {
                distance = FLOAT_TO_FX32(0.0);
            }
            else if (pos > FLOAT_TO_FX32(80.0))
            {
                distance = (FLOAT_TO_FX32(16.0) - (u32)(pos - FLOAT_TO_FX32(80.0)));
                distance >>= 4;
            }

            if (distance < FLOAT_TO_FX32(0.3125))
                distance = FLOAT_TO_FX32(0.3125);

            if (work->obj_3d != NULL)
            {
                u16 color1 = MultiplyFX(GX_COLOR_FROM_888(0xF8), distance);
                u16 color2 = MultiplyFX(GX_COLOR_FROM_888(0x88), distance);
                u16 color3 = MultiplyFX(GX_COLOR_FROM_888(0x40), distance);

                worker->lightColor[0] = GX_RGB(color1, color1, color1);
                worker->lightColor[1] = GX_RGB(color2, color2, color2);
                worker->lightColor[2] = GX_RGB(color3, color3, color3);
            }
        }
    }
}

void SailObject__Draw_Default(void)
{
    StageTask *work    = TaskGetWorkCurrent(StageTask);
    SailObject *object = GetStageTaskWorker(work, SailObject);

    switch (work->objType)
    {
        case SAILSTAGE_OBJ_TYPE_PLAYER: {
            SailPlayer *player = (SailPlayer *)object;

            NNS_G3dGlbLightColor(GX_LIGHTID_0, SailObject__ApplyFogBrightness(player->lightColor[0]));
            NNS_G3dGlbLightColor(GX_LIGHTID_1, SailObject__ApplyFogBrightness(player->lightColor[1]));
            NNS_G3dGlbLightColor(GX_LIGHTID_2, SailObject__ApplyFogBrightness(player->lightColor[2]));
        }
        break;

        case SAILSTAGE_OBJ_TYPE_OBJECT:
            NNS_G3dGlbLightColor(GX_LIGHTID_0, SailObject__ApplyFogBrightness(object->lightColor[0]));
            NNS_G3dGlbLightColor(GX_LIGHTID_1, SailObject__ApplyFogBrightness(object->lightColor[1]));
            NNS_G3dGlbLightColor(GX_LIGHTID_2, SailObject__ApplyFogBrightness(object->lightColor[2]));
            break;

        case SAILSTAGE_OBJ_TYPE_EFFECT:
            if ((work->userFlag & SAILOBJECT_FLAG_400000) == 0)
                break;

            NNS_G3dGlbLightColor(GX_LIGHTID_0, SailObject__ApplyFogBrightness(object->lightColor[0]));
            NNS_G3dGlbLightColor(GX_LIGHTID_1, SailObject__ApplyFogBrightness(object->lightColor[1]));
            NNS_G3dGlbLightColor(GX_LIGHTID_2, SailObject__ApplyFogBrightness(object->lightColor[2]));
            break;
    }

    StageTask__Draw(work);
}

GXRgb SailObject__ApplyFogBrightness(GXRgb color)
{
    SailManager *manager = SailManager__GetWork();

    s32 r = MultiplyFX((color >> GX_RGB_R_SHIFT) & 0x1F, manager->skyBrightness.x);
    s32 g = MultiplyFX((color >> GX_RGB_G_SHIFT) & 0x1F, manager->skyBrightness.y);
    s32 b = MultiplyFX((color >> GX_RGB_B_SHIFT) & 0x1F, manager->skyBrightness.z);

    return GX_RGB(r, g, b);
}

void SailObject__SetLightColors(StageTask *work, s32 type)
{
    GXRgb *lightColor0;
    GXRgb *lightColor1;
    GXRgb *lightColor2;

    SailObject *object = GetStageTaskWorker(work, SailObject);

    switch (work->objType)
    {
        case SAILSTAGE_OBJ_TYPE_PLAYER: {
            SailPlayer *player = (SailPlayer *)object;
            lightColor0        = &player->lightColor[0];
            lightColor1        = &player->lightColor[1];
            lightColor2        = &player->lightColor[2];
        }
        break;

        case SAILSTAGE_OBJ_TYPE_EFFECT:
            if ((work->userFlag & SAILOBJECT_FLAG_400000) == 0)
                return;

        case SAILSTAGE_OBJ_TYPE_OBJECT:

            lightColor0 = &object->lightColor[0];
            lightColor1 = &object->lightColor[1];
            lightColor2 = &object->lightColor[2];

            if ((work->userFlag & SAILOBJECT_FLAG_8000) != 0 && type == 0)
                type = 5;
            break;

        default:
            return;
    }

    switch (type)
    {
        default:
            *lightColor0 = GX_RGB_888(0xF8, 0xF8, 0xF8);
            *lightColor1 = GX_RGB_888(0x88, 0x88, 0x88);
            *lightColor2 = GX_RGB_888(0x40, 0x40, 0x40);
            break;

        case 1:
            *lightColor0 = GX_RGB_888(0xF8, 0x00, 0x00);
            *lightColor1 = GX_RGB_888(0xF8, 0x00, 0x00);
            *lightColor2 = GX_RGB_888(0xF8, 0x00, 0x00);
            break;

        case 2:
            *lightColor0 = GX_RGB_888(0x00, 0x00, 0xF8);
            *lightColor1 = GX_RGB_888(0x00, 0x00, 0xF8);
            *lightColor2 = GX_RGB_888(0x00, 0x00, 0xF8);
            break;

        case 3:
            *lightColor0 = GX_RGB_888(0xF8, 0xF8, 0x00);
            *lightColor1 = GX_RGB_888(0xF8, 0xF8, 0x00);
            *lightColor2 = GX_RGB_888(0xF8, 0xF8, 0x00);
            break;

        case 4:
            *lightColor0 = GX_RGB_888(0x20, 0x20, 0x20);
            *lightColor1 = GX_RGB_888(0x20, 0x20, 0x20);
            *lightColor2 = GX_RGB_888(0x20, 0x20, 0x20);
            break;

        case 5:
            *lightColor0 = GX_RGB_888(0x50, 0x50, 0xF8);
            *lightColor1 = GX_RGB_888(0x30, 0x30, 0x88);
            *lightColor2 = GX_RGB_888(0x10, 0x10, 0x40);
            break;
    }
}

void SailObject__Last_Default(void)
{
    StageTask *work    = TaskGetWorkCurrent(StageTask);
    SailObject *worker = GetStageTaskWorker(work, SailObject);

    if (worker->field_130 != 0)
        worker->field_130--;

    if (worker->blinkTimer != 0)
    {
        worker->blinkTimer--;
        if ((worker->blinkTimer & 2) != 0)
            SailObject__SetLightColors(work, 1);
        else
            SailObject__SetLightColors(work, 0);
    }

    worker->collidedObj = NULL;
}

void SailObject__DoColliderUnknown(StageTask *work, SailColliderWorkHitCheck *collider)
{
    UNUSED(work);
    UNUSED(collider);

    // Does..... nothing?
}

BOOL SailObject__ColliderCheckActive_Default(OBS_RECT_WORK *rect1, OBS_RECT_WORK *rect2)
{
    SailColliderWork *collider1;
    SailColliderWork *collider2;

    SailColliderWorkHitCheck *hitCheck1_1 = NULL;
    SailColliderWorkHitCheck *hitCheck2_1 = NULL;
    SailColliderWorkHitCheck *hitCheck1_2 = NULL;
    SailColliderWorkHitCheck *hitCheck2_2 = NULL;

    collider1 = rect1->userData;
    collider2 = rect2->userData;

    s32 type = collider1->type;

    switch (collider1->type)
    {
        case 1:
            hitCheck1_1 = &collider1->hitCheck;
            break;

        case 2:
            hitCheck1_2 = &collider1->hitCheck;
            break;

        default:
            return FALSE;
    }

    switch (collider2->type)
    {
        case 1:
            hitCheck2_1 = &collider2->hitCheck;
            break;

        case 2:
            hitCheck2_2 = &collider2->hitCheck;
            break;

        default:
            return FALSE;
    }

    if (hitCheck1_1 != NULL && hitCheck2_1 != NULL)
        return SailObject__CheckHitboxEnabled_Type1(hitCheck1_1, hitCheck2_1, type);

    if (hitCheck1_1 != NULL && hitCheck2_2 != NULL)
        return SailObject__CheckHitboxEnabled_Type2(hitCheck1_1, hitCheck2_2, type);

    if (hitCheck2_1 != NULL && hitCheck1_2 != NULL)
        return SailObject__CheckHitboxEnabled_Type2(hitCheck2_1, hitCheck1_2, type);

    // ???
    BOOL value = FALSE;
    if (hitCheck1_2 != NULL)
    {
        value = FALSE;
    }

    return value;
}

BOOL SailObject__CheckHitboxEnabled_Type1(SailColliderWorkHitCheck *collider1, SailColliderWorkHitCheck *collider2, fx32 a3)
{
    fx32 distanceX;
    fx32 distanceZ;

    distanceZ = (collider1->field_0.z - collider2->field_0.z);
    distanceX = (collider1->field_0.x - collider2->field_0.x);

    if (distanceX < 0)
        distanceX = -distanceX;
    if (distanceZ < 0)
        distanceZ = -distanceZ;

    fx32 value;
    if (distanceX > distanceZ)
    {
        value = MultiplyFX(FLOAT_TO_FX32(0.96045), distanceX);
        value += MultiplyFX(FLOAT_TO_FX32(0.397706), distanceZ);
    }
    else
    {
        value = MultiplyFX(FLOAT_TO_FX32(0.96045), distanceZ);
        value += MultiplyFX(FLOAT_TO_FX32(0.397706), distanceX);
    }

    if (value > FLOAT_TO_FX32(256.0))
        return FALSE;

    VecFx32 dest;
    VEC_Subtract(&collider1->field_0, &collider2->field_0, &dest);
    fx32 dot = VEC_DotProduct(&dest, &dest);

    fx32 unknownX2 = collider2->field_24.x;
    fx32 unknownX1 = collider1->field_24.x;

    if ((dot - MultiplyFX(unknownX1 + unknownX2, unknownX1 + unknownX2)) > 0)
        return FALSE;

    if (collider1->field_24.y != 0 || collider2->field_24.y != 0)
    {
        s32 unknownY1 = collider1->field_24.y;
        s32 unknownY2 = collider2->field_24.y;

        s32 distanceY = collider1->field_0.y - collider2->field_0.y;

        if (unknownY1 == 0)
            unknownY1 = collider1->field_24.x;

        if (unknownY2 != 0)
            unknownY1 += unknownY2;
        else
            unknownY1 += unknownX2;

        s32 value2 = MultiplyFX(distanceY, distanceY) - MultiplyFX(unknownY1, unknownY1);
        if (value2 > 0)
            return FALSE;
    }

    if (collider1->field_24.z != 0 || collider2->field_24.z != 0)
    {
        u16 angle = FX_Atan2Idx(collider2->field_0.x - collider1->field_0.x, collider2->field_0.z - collider1->field_0.z);

        if (collider1->field_24.z != 0)
        {
            unknownX1 -= MATH_ABS(MultiplyFX(unknownX1 - collider1->field_24.z, SinFX((s32)(u16)(angle - collider1->angle))));
        }

        if (collider2->field_24.z != 0)
        {
            unknownX2 -= MATH_ABS(MultiplyFX(unknownX2 - collider2->field_24.z, SinFX((s32)(u16)(angle - collider2->angle))));
        }

        if (dot - MultiplyFX(unknownX1 + unknownX2, unknownX1 + unknownX2) > 0)
            return FALSE;
    }

    VEC_Add(&collider1->field_0, &collider2->field_0, &collider1->type1.field_38);
    collider1->type1.field_38.x >>= 1;
    collider1->type1.field_38.y >>= 1;
    collider1->type1.field_38.z >>= 1;
    collider1->type1.field_38.y = -collider1->type1.field_38.y;

    collider2->type1.field_38 = collider1->type1.field_38;

    return TRUE;
}

BOOL SailObject__CheckHitboxEnabled_Type2(SailColliderWorkHitCheck *collider1, SailColliderWorkHitCheck *collider2, fx32 a3)
{
    s32 range = collider1->field_24.x + collider2->type2.field_48;

    VecFx32 position2;
    VecFx32 position1;
    VEC_Subtract(&collider2->field_C, &collider2->field_0, &position2);
    VEC_Subtract(&collider1->field_0, &collider2->field_0, &position1);

    s32 dot1 = VEC_DotProduct(&position1, &position2);
    if (dot1 < 0)
        return 0;

    s32 dot2 = VEC_DotProduct(&position2, &position2);
    if (dot1 > dot2)
        return 0;

    fx32 step = FX_Div(dot1, dot2);
    VecFx32 localPos;
    localPos.x = position1.x - MultiplyFX(step, position2.x);
    localPos.y = position1.y - MultiplyFX(step, position2.y);
    localPos.z = position1.z - MultiplyFX(step, position2.z);

    if (VEC_DotProduct(&localPos, &localPos) > MultiplyFX(range, range))
        return FALSE;

    VEC_Subtract(&collider1->field_0, &localPos, &collider2->type2.field_5C);
    collider2->type2.field_5C.y = -collider2->type2.field_5C.y;
    collider1->type1.field_38   = collider2->type2.field_5C;

    return TRUE;
}

void SailObject__SetupHitbox(StageTask *work, SailColliderWork *sailCollider, s32 id)
{
    StageTask__InitCollider(work, NULL, id, STAGE_TASK_COLLIDER_FLAGS_NONE);

    OBS_RECT_WORK *collider = StageTask__GetCollider(work, id);
    collider->onDefend      = NULL;
    collider->flag          = OBS_RECT_WORK_FLAG_80000 | OBS_RECT_WORK_FLAG_IS_ACTIVE;
    collider->userData      = sailCollider;
    ObjRect__SetCheckActive(collider, SailObject__ColliderCheckActive_Default);

    switch (id)
    {
        case 0:
        case 3:
        default:
            collider->hitPower = 0;
            collider->defPower = 10;
            collider->hitFlag |= 1;
            collider->hitFlag &= ~2;
            collider->defFlag &= ~1;
            break;

        case 1:
        case 2:
            collider->hitPower = 10;
            collider->defPower = 100;
            break;
    }

    switch (work->objType)
    {
        case SAILSTAGE_OBJ_TYPE_PLAYER:
        case SAILSTAGE_OBJ_TYPE_EFFECT:
            // Does not match with the macro, has to be manually written out.
            // ObjRect__SetGroupFlags(collider, 1, 2);
            collider->groupFlags = 1;
            collider->groupFlags |= 2 << 8;
            collider->flag |= OBS_RECT_WORK_FLAG_20;
            break;

        case SAILSTAGE_OBJ_TYPE_OBJECT:
        default:
            ObjRect__SetGroupFlags(collider, 2, 1);
            sailCollider->atkPower = FLOAT_TO_FX32(64.0);

            if (id == 0 || id == 3)
            {
                collider->hitPower = 10;
                collider->defPower = 5;
                ObjRect__SetOnDefend(collider, SailObject__OnDefend_Default);
                collider->flag |= OBS_RECT_WORK_FLAG_20;
            }
            break;
    }

    sailCollider->stageTask = work;
}

void SailObject__Func_21658A4(StageTask *work, s32 id)
{
    if (work->objType == SAILSTAGE_OBJ_TYPE_OBJECT)
    {
        OBS_RECT_WORK *collider = StageTask__GetCollider(work, id);
        collider->groupFlags |= 2 << 8;
        collider->hitPower = 8;
    }
}

void SailObject__Func_21658D0(StageTask *work, s32 id, s32 a3, VecFx32 *a4)
{
    OBS_RECT_WORK *obsCollider = StageTask__GetCollider(work, id);

    SailColliderWork *collider = obsCollider->userData;
    collider->type             = 1;

    collider->hitCheck.field_0 = work->position;

    collider->hitCheck.field_24.x = a3;
    collider->hitCheck.field_34   = &work->position;

    if (a4 != NULL)
    {
        collider->hitCheck.field_C = *a4;
    }

    VecFx32 position;
    SailObject__Func_2165A9C(work, &position);
    collider->hitCheck.field_C.x += position.x;
    collider->hitCheck.field_C.y -= position.y;
    collider->hitCheck.field_C.z += position.z;
}

void SailObject__Func_2165960(StageTask *work, s32 id, s32 a3, VecFx32 *a4, VecFx32 *a5, VecFx32 *a6)
{
    OBS_RECT_WORK *obsCollider = StageTask__GetCollider(work, id);

    SailColliderWork *collider = obsCollider->userData;
    collider->type             = 2;

    collider->hitCheck.field_18 = *a4;
    collider->hitCheck.field_24 = *a5;

    collider->hitCheck.type2.field_48 = a3;

    VEC_Subtract(a5, a4, &collider->hitCheck.type2.field_50);
    VEC_Normalize(&collider->hitCheck.type2.field_50, &collider->hitCheck.type2.field_50);
    collider->hitCheck.type2.field_4C = &work->position;

    if (a6 != NULL)
    {
        collider->hitCheck.type2.field_3C = *a6;
    }

    VecFx32 position;
    SailObject__Func_2165A9C(work, &position);
    collider->hitCheck.type2.field_3C.x += position.x;
    collider->hitCheck.type2.field_3C.y -= position.y;
    collider->hitCheck.type2.field_3C.z += position.z;
}

void SailObject__ShakeScreen(StageTask *work, s32 timer)
{
    u16 shipType = SailManager__GetShipType();

    if (timer != 0)
    {
        fx32 shakeX = FX32_FROM_WHOLE(StageTask__shakeOffsetTable[timer & 0xF]);
        fx32 shakeY = FX32_FROM_WHOLE(StageTask__shakeOffsetTable[(timer + 1) & 0xF]);

        work->offset.x += shakeX >> shipShiftUnknown[shipType];
        work->offset.y += shakeY >> shipShiftUnknown[shipType];
        if ((work->flag & STAGE_TASK_FLAG_20000) == 0)
            work->offset.z += shakeX >> shipShiftUnknown[shipType];
    }
}

void SailObject__Func_2165A9C(StageTask *work, VecFx32 *position)
{
    switch (work->objType)
    {
        case SAILSTAGE_OBJ_TYPE_PLAYER: {
            SailPlayer *player = GetStageTaskWorker(work, SailPlayer);

            *position = player->field_4;
        }
        break;

        case SAILSTAGE_OBJ_TYPE_OBJECT: {
            SailObject *object = GetStageTaskWorker(work, SailObject);

            *position = object->field_4;
        }
        break;

        // case SAILSTAGE_OBJ_TYPE_EFFECT:
        default:
            position->x = 0;
            position->y = 0;
            position->z = 0;
            break;
    }
}

void SailObject__Func_2165AF4(StageTask *work, VecFx32 *position)
{
    switch (work->objType)
    {
        case SAILSTAGE_OBJ_TYPE_PLAYER: {
            SailPlayer *player = GetStageTaskWorker(work, SailPlayer);

            player->field_4 = *position;
        }
        break;

        case SAILSTAGE_OBJ_TYPE_OBJECT: {
            SailObject *object = GetStageTaskWorker(work, SailObject);

            object->field_4 = *position;
        }
        break;
    }
}

NONMATCH_FUNC StageTask *SailLanding__Create(SailEventManagerObject *mapObject)
{
    // should match when 'aSbLandBac' is decompiled
#ifdef NON_MATCHING
    StageTask *work;
    SailObject *worker;

    SailManager *manager = SailManager__GetWork();

    work = CreateStageTaskSimpleEx(TASK_PRIORITY_UPDATE_LIST_START + 0xB10, TASK_GROUP(1));
    StageTask__SetType(work, SAILSTAGE_OBJ_TYPE_OBJECT);

    worker = StageTask__AllocateWorker(work, sizeof(SailObject));
    UNUSED(worker);

    ObjObjectAction3dBACLoad(work, NULL, "/sb_land.bac", OBJ_DATA_GFX_AUTO, OBJ_DATA_GFX_AUTO, GetObjectFileWork(OBJDATAWORK_18), SailManager__GetArchive());
    SailObject__InitCommon(work);
    SailObject__InitFromMapObject(work, mapObject);

    work->userTimer                             = mapObject->objectValue14;
    work->obj_2dIn3d->ani.polygonAttr.polygonID = 0x30;
    work->obj_2dIn3d->ani.polygonAttr.enableFog = FALSE;
    work->obj_2dIn3d->ani.work.matrixOpIDs[0]   = MATRIX_OP_SET_CAMERA_ROT_33;
    work->obj_2dIn3d->ani.work.matrixOpIDs[1]   = MATRIX_OP_FLUSH_P_CAMERA3D;

    if (SailManager__GetShipType() == SHIP_SUBMARINE)
        work->position.y = -FLOAT_TO_FX32(2.0);
    else
        work->position.y = -FLOAT_TO_FX32(0.40625);

    if (work->userTimer != manager->field_4)
    {
        SetTaskState(work, SailLanding__State_216A46C);
        SetTaskOutFunc(work, SailLanding__Draw_216A6A4);

        work->flag |= STAGE_TASK_FLAG_DISABLE_VIEWCHECK_EVENT;
        if (SailManager__GetShipType() == SHIP_BOAT)
            work->position.y = -FLOAT_TO_FX32(0.125);
    }
    else
    {
        SetTaskOutFunc(work, SailLanding__Draw_216A4E8);

        if (SailManager__GetShipType() == SHIP_SUBMARINE)
            SailSubFish__CreateUnknown2(work);
        else
            SailSeagull__CreateUnknown2(work);
    }

    return work;
#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0xc
	mov r7, r0
	bl SailManager__GetWork
	mov r5, r0
	mov r0, #0xb10
	mov r1, #1
	bl CreateStageTaskEx_
	mov r4, r0
	mov r1, #1
	bl StageTask__SetType
	mov r0, r4
	mov r1, #0x1a0
	bl StageTask__AllocateWorker
	mov r0, #0x12
	bl GetObjectFileWork
	mov r6, r0
	bl SailManager__GetArchive
	ldr r3, =0x0000FFFF
	ldr r2, =aSbLandBac
	stmia sp, {r3, r6}
	str r0, [sp, #8]
	mov r1, #0
	mov r0, r4
	bl ObjObjectAction3dBACLoad
	mov r0, r4
	bl SailObject__InitCommon
	mov r0, r4
	mov r1, r7
	bl SailObject__InitFromMapObject
	ldr r0, [r7, #0x38]
	mov r2, #0x1d
	str r0, [r4, #0x2c]
	ldr r3, [r4, #0x134]
	mov r1, #7
	ldr r0, [r3, #0xf4]
	bic r0, r0, #0x3f000000
	orr r0, r0, #0x30000000
	str r0, [r3, #0xf4]
	ldr r3, [r4, #0x134]
	ldr r0, [r3, #0xf4]
	bic r0, r0, #0x8000
	str r0, [r3, #0xf4]
	ldr r0, [r4, #0x134]
	strb r2, [r0, #0xa]
	ldr r0, [r4, #0x134]
	strb r1, [r0, #0xb]
	bl SailManager__GetShipType
	cmp r0, #3
	moveq r0, #0x2000
	movne r0, #0x680
	rsb r0, r0, #0
	str r0, [r4, #0x48]
	ldr r1, [r4, #0x2c]
	ldr r0, [r5, #4]
	cmp r1, r0
	beq _02165C50
	ldr r1, =SailLanding__State_216A46C
	ldr r0, =SailLanding__Draw_216A6A4
	str r1, [r4, #0xf4]
	str r0, [r4, #0xfc]
	ldr r0, [r4, #0x18]
	orr r0, r0, #0x10
	str r0, [r4, #0x18]
	bl SailManager__GetShipType
	cmp r0, #1
	bne _02165C74
	mov r0, #0x200
	rsb r0, r0, #0
	str r0, [r4, #0x48]
	b _02165C74
_02165C50:
	ldr r0, =SailLanding__Draw_216A4E8
	str r0, [r4, #0xfc]
	bl SailManager__GetShipType
	cmp r0, #3
	mov r0, r4
	bne _02165C70
	bl SailSubFish__CreateUnknown2
	b _02165C74
_02165C70:
	bl SailSeagull__CreateUnknown2
_02165C74:
	mov r0, r4
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}

// clang-format on
#endif
}

NONMATCH_FUNC StageTask *SailJetMine__Create(SailEventManagerObject *mapObject)
{
    // should match when 'aSbMineBac_0' is decompiled
#ifdef NON_MATCHING
    StageTask *work;
    SailObject *worker;

    SailManager *manager = SailManager__GetWork();

    work = CreateStageTaskSimple();
    StageTask__SetType(work, SAILSTAGE_OBJ_TYPE_OBJECT);

    worker = StageTask__AllocateWorker(work, sizeof(SailObject));

    ObjObjectAction3dBACLoad(work, 0, "sb_mine.bac", OBJ_DATA_GFX_NONE, OBJ_DATA_GFX_NONE, GetObjectDataWork(OBJDATAWORK_2), SailManager__GetArchive());
    ObjObjectActionAllocTexture(work, OBJ_DATA_GFX_NONE, OBJ_DATA_GFX_NONE, GetObjectTextureRef(OBJDATAWORK_54));
    work->obj_2dIn3d->ani.animatorSprite.flags |= ANIMATOR_FLAG_DISABLE_PALETTES | ANIMATOR_FLAG_DISABLE_SPRITE_PARTS;
    SailObject__InitCommon(work);
    SailObject__InitFromMapObject(work, mapObject);

    work->position.y -= FLOAT_TO_FX32(1.0);
    worker->dword118 = 300;

    if (SailManager__GetShipType() == SHIP_HOVER)
    {
        worker->field_120 = FLOAT_TO_FX32(1.5);
        worker->health    = FLOAT_TO_FX32(1.5);
    }
    work->obj_2dIn3d->ani.polygonAttr.enableFog = FALSE;
    work->obj_2dIn3d->ani.work.matrixOpIDs[0]   = MATRIX_OP_SET_CAMERA_ROT_43;
    work->obj_2dIn3d->ani.work.matrixOpIDs[1]   = MATRIX_OP_FLUSH_P_CAMERA3D;

    work->userFlag |= SAILOBJECT_FLAG_40000 | SAILOBJECT_FLAG_2;
    worker->field_124 = FLOAT_TO_FX32(0.75);
    SailObject__SetupHitbox(work, &worker->collider[0], 0);
    SailObject__Func_21658D0(work, 0, 0x600, 0);

    if ((manager->flags & 0x1000) != 0)
        worker->collider[0].atkPower >>= 1;

    if (SailManager__GetShipType() == SHIP_HOVER)
        worker->collider[0].hitCheck.field_24.x = 2304;

    if (SailManager__GetShipType() == SHIP_BOAT)
    {
        worker->collider[0].hitCheck.field_24.x = FLOAT_TO_FX32(2.0);
        work->userFlag |= SAILOBJECT_FLAG_20000;
    }

    StageTask__InitSeqPlayer(work);

    SetTaskState(work, SailMine__State_216A4E8);

    return work;
#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, r7, r8, lr}
	sub sp, sp, #0xc
	mov r7, r0
	bl SailManager__GetWork
	mov r6, r0
	bl CreateStageTask_
	mov r4, r0
	mov r1, #1
	bl StageTask__SetType
	mov r0, r4
	mov r1, #0x1a0
	bl StageTask__AllocateWorker
	mov r5, r0
	mov r0, #2
	bl GetObjectFileWork
	mov r8, r0
	bl SailManager__GetArchive
	mov r1, #0
	stmia sp, {r1, r8}
	str r0, [sp, #8]
	ldr r2, =aSbMineBac_0
	mov r0, r4
	mov r3, r1
	bl ObjObjectAction3dBACLoad
	mov r0, #0x36
	bl GetObjectFileWork
	mov r1, #0
	mov r3, r0
	mov r0, r4
	mov r2, r1
	bl ObjObjectActionAllocTexture
	ldr r2, [r4, #0x134]
	mov r0, r4
	ldr r1, [r2, #0xcc]
	orr r1, r1, #0x18
	str r1, [r2, #0xcc]
	bl SailObject__InitCommon
	mov r1, r7
	mov r0, r4
	bl SailObject__InitFromMapObject
	ldr r1, [r4, #0x48]
	mov r0, #0x12c
	sub r1, r1, #0x1000
	str r1, [r4, #0x48]
	str r0, [r5, #0x118]
	bl SailManager__GetShipType
	cmp r0, #2
	moveq r0, #0x1800
	streq r0, [r5, #0x120]
	streq r0, [r5, #0x11c]
	ldr r1, [r4, #0x134]
	mov r2, #0x1c
	ldr r0, [r1, #0xf4]
	mov r3, #7
	bic r0, r0, #0x8000
	str r0, [r1, #0xf4]
	ldr r1, [r4, #0x134]
	mov r0, r4
	strb r2, [r1, #0xa]
	ldr r2, [r4, #0x134]
	add r1, r5, #0x28
	strb r3, [r2, #0xb]
	ldr r2, [r4, #0x24]
	mov r3, #0xc00
	orr r2, r2, #2
	orr r2, r2, #0x40000
	str r2, [r4, #0x24]
	mov r2, #0
	str r3, [r5, #0x124]
	bl SailObject__SetupHitbox
	mov r1, #0
	mov r0, r4
	mov r3, r1
	mov r2, #0x600
	bl SailObject__Func_21658D0
	ldr r0, [r6, #0x24]
	tst r0, #0x1000
	ldrne r0, [r5, #0x98]
	movne r0, r0, asr #1
	strne r0, [r5, #0x98]
	bl SailManager__GetShipType
	cmp r0, #2
	moveq r0, #0x900
	streq r0, [r5, #0x50]
	bl SailManager__GetShipType
	cmp r0, #1
	bne _02165E04
	mov r0, #0x2000
	str r0, [r5, #0x50]
	ldr r0, [r4, #0x24]
	orr r0, r0, #0x20000
	str r0, [r4, #0x24]
_02165E04:
	mov r0, r4
	bl StageTask__InitSeqPlayer
	ldr r1, =SailMine__State_216A4E8
	mov r0, r4
	str r1, [r4, #0xf4]
	add sp, sp, #0xc
	ldmia sp!, {r3, r4, r5, r6, r7, r8, pc}

// clang-format on
#endif
}

NONMATCH_FUNC StageTask *SailJetBomber__Create(SailEventManagerObject *mapObject)
{
    // should match when 'aSbBomberBac' is decompiled
#ifdef NON_MATCHING
    StageTask *work;
    SailObject *worker;

    work = CreateStageTaskSimple();
    StageTask__SetType(work, SAILSTAGE_OBJ_TYPE_OBJECT);

    worker = StageTask__AllocateWorker(work, sizeof(SailObject));

    ObjObjectAction3dBACLoad(work, NULL, "sb_bomber.bac", OBJ_DATA_GFX_AUTO, OBJ_DATA_GFX_AUTO, GetObjectFileWork(OBJDATAWORK_103), SailManager__GetArchive());
    SailObject__InitCommon(work);
    SailObject__InitFromMapObject(work, mapObject);
    work->position.y -= FLOAT_TO_FX32(1.0);
    if (SailManager__GetShipType() == SHIP_HOVER)
    {
        worker->field_120 = FLOAT_TO_FX32(1.5);
        worker->health    = FLOAT_TO_FX32(1.5);
    }
    worker->dword118                            = 300;
    work->obj_2dIn3d->ani.polygonAttr.enableFog = FALSE;
    work->obj_2dIn3d->ani.work.matrixOpIDs[0]   = MATRIX_OP_SET_CAMERA_ROT_43;
    work->obj_2dIn3d->ani.work.matrixOpIDs[1]   = MATRIX_OP_FLUSH_P_CAMERA3D;
    work->userFlag |= SAILOBJECT_FLAG_2;

    SailObject__SetupHitbox(work, &worker->collider[0], 0);
    SailObject__Func_21658D0(work, 0, 0x600, 0);

    StageTask__InitSeqPlayer(work);
    SailJetBomber__Action_Init(work);

    return work;
#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0xc
	mov r7, r0
	bl CreateStageTask_
	mov r4, r0
	mov r1, #1
	bl StageTask__SetType
	mov r0, r4
	mov r1, #0x1a0
	bl StageTask__AllocateWorker
	mov r5, r0
	mov r0, #0x67
	bl GetObjectFileWork
	mov r6, r0
	bl SailManager__GetArchive
	ldr r3, =0x0000FFFF
	ldr r2, =aSbBomberBac
	stmia sp, {r3, r6}
	str r0, [sp, #8]
	mov r1, #0
	mov r0, r4
	bl ObjObjectAction3dBACLoad
	mov r0, r4
	bl SailObject__InitCommon
	mov r1, r7
	mov r0, r4
	bl SailObject__InitFromMapObject
	ldr r0, [r4, #0x48]
	sub r0, r0, #0x1000
	str r0, [r4, #0x48]
	bl SailManager__GetShipType
	cmp r0, #2
	moveq r0, #0x1800
	streq r0, [r5, #0x120]
	streq r0, [r5, #0x11c]
	mov r0, #0x12c
	str r0, [r5, #0x118]
	ldr r1, [r4, #0x134]
	mov r2, #0x1c
	ldr r0, [r1, #0xf4]
	mov r3, #7
	bic r0, r0, #0x8000
	str r0, [r1, #0xf4]
	ldr r1, [r4, #0x134]
	mov r0, r4
	strb r2, [r1, #0xa]
	ldr r2, [r4, #0x134]
	add r1, r5, #0x28
	strb r3, [r2, #0xb]
	ldr r3, [r4, #0x24]
	mov r2, #0
	orr r3, r3, #2
	str r3, [r4, #0x24]
	bl SailObject__SetupHitbox
	mov r1, #0
	mov r0, r4
	mov r3, r1
	mov r2, #0x600
	bl SailObject__Func_21658D0
	mov r0, r4
	bl StageTask__InitSeqPlayer
	mov r0, r4
	bl SailJetBomber__Action_Init
	mov r0, r4
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailJetBoatCloud__CreateUnknown(void)
{
    // https://decomp.me/scratch/ARkA2 -> 70.15%
#ifdef NON_MATCHING
    VecFx32 position;
    SailEventManagerObject object = { 0 };

    object.type = SAILMAPOBJECT_37;

    for (u16 i = 0; i < 16; i++)
    {
        fx32 viewRange = -0x4F000 - ObjDispRandRepeat(FLOAT_TO_FX32(8.0));
        u16 angle      = ObjDispRandRepeat(0x20000) + 0x800;

        position.x = MultiplyFX(viewRange, SinFX((s32)angle));
        position.y = -FLOAT_TO_FX32(7.0) - ObjDispRandRepeat(0x8000);
        position.z = MultiplyFX(viewRange, CosFX((s32)angle));

        object.viewRange = viewRange;
        object.angle     = angle;
        object.position  = position;

        object.flags |= SAILMAPOBJECT_FLAG_20000000;
        SailEventManager__CreateObject2(&object);
    }
#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
	sub sp, sp, #0x4c
	mov r9, #0
	add r2, sp, #0
	mov r0, r9
	mov r1, r9
	stmia r2!, {r0, r1}
	stmia r2!, {r0, r1}
	stmia r2!, {r0, r1}
	stmia r2!, {r0, r1}
	stmia r2!, {r0, r1}
	stmia r2!, {r0, r1}
	stmia r2!, {r0, r1}
	stmia r2, {r0, r1}
	mov r0, #0x25
	strh r0, [sp, #0x30]
	mov r4, #0x4f000
	ldr r0, =0x0001FFFF
	rsb r4, r4, #0
	ldr r11, =FX_SinCosTable_
	ldr r5, =0x00196225
	ldr r6, =0x3C6EF35F
	mov r10, r9
	sub r7, r0, #0x18000
	add r8, r4, #0x48000
_02165F9C:
	ldr r0, =_obj_disp_rand
	ldr r0, [r0, #0]
	mla r2, r0, r5, r6
	mov r0, r2, lsr #0x10
	mov r1, r0, lsl #0x10
	ldr r0, =0x0001FFFF
	and r0, r0, r1, lsr #16
	mla r1, r2, r5, r6
	mov r2, r1, lsr #0x10
	mov r2, r2, lsl #0x10
	mov r2, r2, lsr #0x10
	and r2, r2, r4, lsr #19
	add r2, r2, #0x800
	add r2, r9, r2
	mov r2, r2, lsl #0x10
	mov r9, r2, lsr #0x10
	mla r2, r1, r5, r6
	ldr r1, =_obj_disp_rand
	sub r0, r4, r0
	str r2, [r1]
	mov r1, r2, lsr #0x10
	mov r1, r1, lsl #0x10
	and r1, r7, r1, lsr #16
	sub r1, r8, r1
	str r1, [sp, #0x44]
	mov r1, r9, lsl #0x10
	mov r1, r1, lsr #0x10
	mov r1, r1, asr #4
	mov r3, r1, lsl #1
	mov r1, r3, lsl #1
	ldrsh r2, [r11, r1]
	add r1, r11, r3, lsl #1
	ldrsh r1, [r1, #2]
	smull ip, r3, r0, r2
	smull r2, r1, r0, r1
	str r0, [sp, #0x28]
	mov r0, #0x800
	adds r0, ip, r0
	adc r3, r3, #0
	mov r0, r0, lsr #0xc
	orr r0, r0, r3, lsl #20
	str r0, [sp, #0x40]
	mov r0, #0x800
	mov ip, #0
	adds r2, r2, r0
	mov r0, ip
	adc r0, r1, r0
	mov r1, r2, lsr #0xc
	orr r1, r1, r0, lsl #20
	strh r9, [sp, #0x2e]
	add r0, sp, #0x40
	str r1, [sp, #0x48]
	add r3, sp, #0x1c
	ldmia r0, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	ldr r1, [sp, #0x34]
	add r0, sp, #0
	orr r1, r1, #0x20000000
	str r1, [sp, #0x34]
	bl SailEventManager__CreateObject2
	add r0, r10, #1
	mov r0, r0, lsl #0x10
	mov r10, r0, lsr #0x10
	cmp r10, #0x10
	blo _02165F9C
	add sp, sp, #0x4c
	ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}

// clang-format on
#endif
}

NONMATCH_FUNC StageTask *SailJetBoatCloud__Create(SailEventManagerObject *mapObject)
{
    // should match when 'aSbCloudBac_0' is decompiled
#ifdef NON_MATCHING
    StageTask *work;
    SailObject *worker;

    work = CreateStageTaskSimpleEx(TASK_PRIORITY_UPDATE_LIST_START + 0x1060, TASK_GROUP(1));
    StageTask__SetType(work, SAILSTAGE_OBJ_TYPE_OBJECT);

    worker = StageTask__AllocateWorker(work, sizeof(SailObject));

    ObjObjectAction3dBACLoad(work, NULL, "sb_cloud.bac", OBJ_DATA_GFX_NONE, OBJ_DATA_GFX_NONE, GetObjectFileWork(OBJDATAWORK_23), SailManager__GetArchive());

    u16 anim = ObjDispRandRepeat(4);
    if (anim > 2)
        anim = 0;
    Animator2D__SetAnimation(&work->obj_2dIn3d->ani.animatorSprite, anim);

    ObjObjectActionAllocTexture(work, OBJ_DATA_GFX_NONE, OBJ_DATA_GFX_NONE, GetObjectFileWork(2 * anim + OBJDATAWORK_56));
    work->obj_2dIn3d->ani.animatorSprite.flags |= ANIMATOR_FLAG_DISABLE_PALETTES | ANIMATOR_FLAG_DISABLE_SPRITE_PARTS;

    SailObject__InitCommon(work);
    SailObject__InitFromMapObject(work, mapObject);
    worker->field_138.x = mapObject->angle;
    worker->field_138.y = mapObject->viewRange;

    work->obj_2dIn3d->ani.polygonAttr.enableFog = FALSE;
    work->obj_2dIn3d->ani.work.matrixOpIDs[0]   = MATRIX_OP_SET_CAMERA_ROT_33;
    work->obj_2dIn3d->ani.work.matrixOpIDs[1]   = MATRIX_OP_FLUSH_P_CAMERA3D;

    fx32 scale    = ObjDispRandRepeat(0x8000) + FLOAT_TO_FX32(7.0);
    scale         = MultiplyFX(scale, FLOAT_TO_FX32(0.03125));
    work->scale.x = scale;
    work->scale.y = scale;
    work->scale.z = scale;

    if (ObjDispRandRepeat(2) != 0)
        work->scale.y = -work->scale.y;

    if (ObjDispRandRepeat(2) != 0)
        work->scale.x = -work->scale.x;

    work->flag |= STAGE_TASK_FLAG_DISABLE_VIEWCHECK_EVENT;
    work->userFlag |= SAILOBJECT_FLAG_1;

    SetTaskState(work, SailJetBoatCloud__State_216AA38);

    return work;
#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0xc
	mov r6, r0
	ldr r0, =0x00001060
	mov r1, #1
	bl CreateStageTaskEx_
	mov r4, r0
	mov r1, #1
	bl StageTask__SetType
	mov r0, r4
	mov r1, #0x1a0
	bl StageTask__AllocateWorker
	mov r5, r0
	mov r0, #0x17
	bl GetObjectFileWork
	mov r7, r0
	bl SailManager__GetArchive
	mov r1, #0
	stmia sp, {r1, r7}
	str r0, [sp, #8]
	ldr r2, =aSbCloudBac_0
	mov r0, r4
	mov r3, r1
	bl ObjObjectAction3dBACLoad
	ldr r2, =_obj_disp_rand
	ldr r0, =0x00196225
	ldr r3, [r2, #0]
	ldr r1, =0x3C6EF35F
	mla r0, r3, r0, r1
	str r0, [r2]
	mov r0, r0, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	and r7, r0, #3
	ldr r2, [r4, #0x134]
	cmp r7, #2
	ldr r0, [r2, #0x90]
	movhi r7, #0
	cmp r0, #1
	beq _02166170
	cmp r0, #2
	beq _02166180
	cmp r0, #3
	beq _02166190
	b _0216619C
_02166170:
	mov r1, r7
	add r0, r2, #0x90
	bl AnimatorSprite__SetAnimation
	b _0216619C
_02166180:
	mov r1, r7
	add r0, r2, #0x90
	bl AnimatorSpriteDS__SetAnimation
	b _0216619C
_02166190:
	mov r1, r7
	add r0, r2, #0x90
	bl AnimatorSpriteDS__SetAnimation2
_0216619C:
	mov r0, r7, lsl #1
	add r0, r0, #0x38
	bl GetObjectFileWork
	mov r1, #0
	mov r3, r0
	mov r0, r4
	mov r2, r1
	bl ObjObjectActionAllocTexture
	ldr r2, [r4, #0x134]
	mov r0, r4
	ldr r1, [r2, #0xcc]
	orr r1, r1, #0x18
	str r1, [r2, #0xcc]
	bl SailObject__InitCommon
	mov r0, r4
	mov r1, r6
	bl SailObject__InitFromMapObject
	ldrh r0, [r6, #0x2e]
	mov r2, #0x1d
	mov ip, #7
	str r0, [r5, #0x138]
	ldr r0, [r6, #0x28]
	ldr r6, =_obj_disp_rand
	str r0, [r5, #0x13c]
	ldr r1, [r4, #0x134]
	ldr r3, =0x00196225
	ldr r0, [r1, #0xf4]
	ldr r5, =0x3C6EF35F
	bic r0, r0, #0x8000
	str r0, [r1, #0xf4]
	ldr r0, [r4, #0x134]
	ldr r1, =0x00007FFF
	strb r2, [r0, #0xa]
	ldr r0, [r4, #0x134]
	mov r2, #0x800
	strb ip, [r0, #0xb]
	ldr r0, [r6, #0]
	mla ip, r0, r3, r5
	mov r0, ip, lsr #0x10
	mov r0, r0, lsl #0x10
	and r0, r1, r0, lsr #16
	add r1, r0, #0x7000
	adds r0, r2, r1, lsl #7
	mov r2, r0, lsr #0xc
	mov r0, r1, asr #0x1f
	mov r0, r0, lsl #7
	orr r0, r0, r1, lsr #25
	adc r0, r0, #0
	str ip, [r6]
	orr r2, r2, r0, lsl #20
	str r2, [r4, #0x38]
	str r2, [r4, #0x3c]
	str r2, [r4, #0x40]
	ldr r0, [r6, #0]
	ldr r2, =_obj_disp_rand
	mla r1, r0, r3, r5
	mov r0, r1, lsr #0x10
	mov r0, r0, lsl #0x10
	str r1, [r6]
	mov r0, r0, lsr #0x10
	tst r0, #1
	ldrne r0, [r4, #0x3c]
	ldr r1, =0x3C6EF35F
	rsbne r0, r0, #0
	strne r0, [r4, #0x3c]
	ldr r0, =0x00196225
	ldr r3, [r2, #0]
	mla r1, r3, r0, r1
	mov r0, r1, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	str r1, [r2]
	tst r0, #1
	ldrne r0, [r4, #0x38]
	ldr r1, =SailJetBoatCloud__State_216AA38
	rsbne r0, r0, #0
	strne r0, [r4, #0x38]
	ldr r0, [r4, #0x18]
	orr r0, r0, #0x10
	str r0, [r4, #0x18]
	ldr r2, [r4, #0x24]
	mov r0, r4
	orr r2, r2, #1
	str r2, [r4, #0x24]
	str r1, [r4, #0xf4]
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}

// clang-format on
#endif
}

NONMATCH_FUNC StageTask *SailCloud__Create(s32 type)
{
    // should match when 'aSbCloudBac_0' is decompiled
#ifdef NON_MATCHING
    StageTask *work;
    SailObject *worker;

    work = CreateStageTaskSimple();
    StageTask__SetType(work, SAILSTAGE_OBJ_TYPE_OBJECT);

    worker = StageTask__AllocateWorker(work, sizeof(SailObject));

    ObjObjectAction3dBACLoad(work, NULL, "sb_cloud.bac", OBJ_DATA_GFX_NONE, OBJ_DATA_GFX_NONE, GetObjectFileWork(OBJDATAWORK_23), SailManager__GetArchive());

    u16 anim = ObjDispRandRepeat(2);
    Animator2D__SetAnimation(&work->obj_2dIn3d->ani.animatorSprite, anim);

    ObjObjectActionAllocTexture(work, OBJ_DATA_GFX_NONE, OBJ_DATA_GFX_NONE, GetObjectFileWork(2 * anim + OBJDATAWORK_56));
    work->obj_2dIn3d->ani.animatorSprite.flags |= DISPLAY_FLAG_PAUSED | DISPLAY_FLAG_DID_FINISH;

    SailObject__InitCommon(work);
    work->obj_2dIn3d->ani.work.matrixOpIDs[0] = MATRIX_OP_SET_CAMERA_ROT_33;
    work->obj_2dIn3d->ani.work.matrixOpIDs[1] = MATRIX_OP_FLUSH_P_CAMERA3D;
    work->userWork                            = ObjDispRandRepeat(0x40) + 32;
    work->userTimer                           = 0;

    if (type != 0)
    {
        worker->field_138.y = ObjDispRandRepeat(FLOAT_TO_FX32(2.0)) + FLOAT_TO_FX32(16.0);
        worker->field_138.x = (u16)ObjDispRandRange(-FLOAT_TO_FX32(1.0), FLOAT_TO_FX32(1.0));
        work->position.y    = ObjDispRandRepeat(FLOAT_TO_FX32(1.0)) - FLOAT_TO_FX32(2.0);

        fx32 scale    = MultiplyFX(ObjDispRandRepeat(FLOAT_TO_FX32(1.0)) + FLOAT_TO_FX32(8.0), FLOAT_TO_FX32(0.03125));
        work->scale.x = scale;
        work->scale.y = scale;
        work->scale.z = scale;

        if (SailManager__GetShipType() == SHIP_BOAT)
        {
            worker->field_138.y *= 4;
            worker->field_138.x *= 4;
            work->position.y *= 4;

            work->scale.z = work->scale.y = work->scale.x = 4 * work->scale.x;
        }
    }
    else
    {
        work->displayFlag |= DISPLAY_FLAG_USE_DEFAULT_CAMERA_CONFIG;
        work->position.x = FLOAT_TO_FX32(128.0);
        work->position.y = FLOAT_TO_FX32(96.0);

        work->position.x += FX32_FROM_WHOLE(ObjDispRandRange(-64, 64));
        work->position.y += FX32_FROM_WHOLE(ObjDispRandRange(-64, 64));
        work->position.z = -880;

        fx32 scale    = ObjDispRandRepeat(FLOAT_TO_FX32(4.0)) + FLOAT_TO_FX32(6.0);
        work->scale.x = scale;
        work->scale.y = scale;
        work->scale.z = scale;

        work->velocity.x = ObjDispRandRange(-FLOAT_TO_FX32(1.0), FLOAT_TO_FX32(1.0));
        work->velocity.y = ObjDispRandRange(-FLOAT_TO_FX32(1.0), FLOAT_TO_FX32(1.0));
        work->velocity.z = 8;
    }

    if (ObjDispRandRepeat(2) != 0)
        work->scale.y = -work->scale.y;

    if (ObjDispRandRepeat(2) != 0)
        work->scale.x = -work->scale.x;

    work->flag |= STAGE_TASK_FLAG_DISABLE_VIEWCHECK_EVENT;
    work->userFlag |= SAILOBJECT_FLAG_1;

    SetTaskState(work, SailCloud__State_216AF60);

    return work;
#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0xc
	mov r6, r0
	bl CreateStageTask_
	mov r4, r0
	mov r1, #1
	bl StageTask__SetType
	mov r0, r4
	mov r1, #0x1a0
	bl StageTask__AllocateWorker
	mov r5, r0
	mov r0, #0x17
	bl GetObjectFileWork
	mov r7, r0
	bl SailManager__GetArchive
	mov r1, #0
	stmia sp, {r1, r7}
	str r0, [sp, #8]
	ldr r2, =aSbCloudBac_0
	mov r0, r4
	mov r3, r1
	bl ObjObjectAction3dBACLoad
	ldr r2, =_obj_disp_rand
	ldr r0, =0x00196225
	ldr r3, [r2, #0]
	ldr r1, =0x3C6EF35F
	mla r0, r3, r0, r1
	str r0, [r2]
	mov r0, r0, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	ldr r2, [r4, #0x134]
	and r7, r0, #1
	ldr r0, [r2, #0x90]
	cmp r0, #1
	beq _021663B8
	cmp r0, #2
	beq _021663C8
	cmp r0, #3
	beq _021663D8
	b _021663E4
_021663B8:
	mov r1, r7
	add r0, r2, #0x90
	bl AnimatorSprite__SetAnimation
	b _021663E4
_021663C8:
	mov r1, r7
	add r0, r2, #0x90
	bl AnimatorSpriteDS__SetAnimation
	b _021663E4
_021663D8:
	mov r1, r7
	add r0, r2, #0x90
	bl AnimatorSpriteDS__SetAnimation2
_021663E4:
	mov r0, r7, lsl #1
	add r0, r0, #0x38
	bl GetObjectFileWork
	mov r1, #0
	mov r3, r0
	mov r0, r4
	mov r2, r1
	bl ObjObjectActionAllocTexture
	ldr r2, [r4, #0x134]
	mov r0, r4
	ldr r1, [r2, #0xcc]
	orr r1, r1, #0x18
	str r1, [r2, #0xcc]
	bl SailObject__InitCommon
	ldr r0, [r4, #0x134]
	mov r1, #0x1d
	strb r1, [r0, #0xa]
	ldr r0, [r4, #0x134]
	mov r1, #7
	ldr r2, =_obj_disp_rand
	strb r1, [r0, #0xb]
	ldr r3, [r2, #0]
	ldr r0, =0x00196225
	ldr r1, =0x3C6EF35F
	mov ip, #0
	mla r7, r3, r0, r1
	mov r3, r7, lsr #0x10
	str r7, [r2]
	mov r3, r3, lsl #0x10
	mov r3, r3, lsr #0x10
	and r3, r3, #0x3f
	add r3, r3, #0x20
	str r3, [r4, #0x28]
	str ip, [r4, #0x2c]
	cmp r6, #0
	beq _02166580
	ldr r3, [r2, #0]
	ldr r6, =0x00001FFF
	mla r7, r3, r0, r1
	mov r3, r7, lsr #0x10
	mov r3, r3, lsl #0x10
	and r3, r6, r3, lsr #16
	str r7, [r2]
	add r3, r3, #0x10000
	str r3, [r5, #0x13c]
	ldr lr, [r2]
	sub r7, r6, #1
	mla r3, lr, r0, r1
	mov lr, r3, lsr #0x10
	mov lr, lr, lsl #0x10
	and lr, r7, lr, lsr #16
	sub r7, r6, #0x1000
	sub r7, r7, lr
	mov r7, r7, lsl #0x10
	str r3, [r2]
	mov r3, r7, lsr #0x10
	str r3, [r5, #0x138]
	ldr r3, [r2, #0]
	sub r7, r6, #0x1000
	mla lr, r3, r0, r1
	mov r3, lr, lsr #0x10
	mov r3, r3, lsl #0x10
	and r3, r7, r3, lsr #16
	str lr, [r2]
	sub r3, r3, #0x2000
	str r3, [r4, #0x48]
	ldr r7, [r2, #0]
	sub r3, r6, #0x1000
	mla r0, r7, r0, r1
	mov r1, r0, lsr #0x10
	mov r1, r1, lsl #0x10
	and r1, r3, r1, lsr #16
	add r3, r1, #0x8000
	mov r1, r3, asr #0x1f
	mov r6, r1, lsl #7
	mov r1, #0x800
	adds r7, r1, r3, lsl #7
	orr r6, r6, r3, lsr #25
	adc r1, r6, ip
	mov r3, r7, lsr #0xc
	str r0, [r2]
	orr r3, r3, r1, lsl #20
	str r3, [r4, #0x38]
	str r3, [r4, #0x3c]
	str r3, [r4, #0x40]
	bl SailManager__GetShipType
	cmp r0, #1
	bne _02166674
	ldr r0, [r5, #0x13c]
	mov r0, r0, lsl #2
	str r0, [r5, #0x13c]
	ldr r0, [r5, #0x138]
	mov r0, r0, lsl #2
	str r0, [r5, #0x138]
	ldr r0, [r4, #0x48]
	mov r0, r0, lsl #2
	str r0, [r4, #0x48]
	ldr r0, [r4, #0x38]
	mov r0, r0, lsl #2
	str r0, [r4, #0x38]
	str r0, [r4, #0x3c]
	str r0, [r4, #0x40]
	b _02166674
_02166580:
	ldr r5, [r4, #0x20]
	mov r3, #0x80000
	orr r5, r5, #0x20000
	str r5, [r4, #0x20]
	str r3, [r4, #0x44]
	mov r3, #0x60000
	str r3, [r4, #0x48]
	ldr r3, [r2, #0]
	sub r6, ip, #0x370
	mla r5, r3, r0, r1
	mov r3, r5, lsr #0x10
	mov r3, r3, lsl #0x10
	str r5, [r2]
	mov r3, r3, lsr #0x10
	and r3, r3, #0x7e
	ldr r5, [r4, #0x44]
	rsb r3, r3, #0x3f
	add r3, r5, r3, lsl #12
	str r3, [r4, #0x44]
	ldr r3, [r2, #0]
	ldr r5, =0x00003FFF
	mla r7, r3, r0, r1
	mov r3, r7, lsr #0x10
	mov r3, r3, lsl #0x10
	str r7, [r2]
	mov r3, r3, lsr #0x10
	and r3, r3, #0x7e
	ldr r7, [r4, #0x48]
	rsb r3, r3, #0x3f
	add r3, r7, r3, lsl #12
	str r3, [r4, #0x48]
	str r6, [r4, #0x4c]
	ldr r3, [r2, #0]
	ldr r6, =0x00001FFE
	mla r7, r3, r0, r1
	mov r3, r7, lsr #0x10
	mov r3, r3, lsl #0x10
	and r3, r5, r3, lsr #16
	str r7, [r2]
	add r3, r3, #0x6000
	str r3, [r4, #0x38]
	str r3, [r4, #0x3c]
	str r3, [r4, #0x40]
	ldr r3, [r2, #0]
	mov r5, #8
	mla r7, r3, r0, r1
	mov r3, r7, lsr #0x10
	mov r3, r3, lsl #0x10
	and r3, r6, r3, lsr #16
	str r7, [r2]
	rsb r3, r3, r6, lsr #1
	str r3, [r4, #0x98]
	ldr r3, [r2, #0]
	mla r1, r3, r0, r1
	mov r0, r1, lsr #0x10
	mov r0, r0, lsl #0x10
	and r0, r6, r0, lsr #16
	str r1, [r2]
	rsb r0, r0, r6, lsr #1
	str r0, [r4, #0x9c]
	str r5, [r4, #0xa0]
_02166674:
	ldr r2, =_obj_disp_rand
	ldr r0, =0x00196225
	ldr r3, [r2, #0]
	ldr r1, =0x3C6EF35F
	mla r1, r3, r0, r1
	mov r0, r1, lsr #0x10
	str r1, [r2]
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	tst r0, #1
	ldrne r0, [r4, #0x3c]
	ldr r2, =_obj_disp_rand
	rsbne r0, r0, #0
	strne r0, [r4, #0x3c]
	ldr r0, =0x00196225
	ldr r3, [r2, #0]
	ldr r1, =0x3C6EF35F
	mla r1, r3, r0, r1
	mov r0, r1, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	str r1, [r2]
	tst r0, #1
	ldrne r0, [r4, #0x38]
	ldr r1, =SailCloud__State_216AF60
	rsbne r0, r0, #0
	strne r0, [r4, #0x38]
	ldr r0, [r4, #0x18]
	orr r0, r0, #0x10
	str r0, [r4, #0x18]
	ldr r2, [r4, #0x24]
	mov r0, r4
	orr r2, r2, #1
	str r2, [r4, #0x24]
	str r1, [r4, #0xf4]
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}

// clang-format on
#endif
}

void SailObject__Func_2166728(StageTask *work)
{
    SailObject *worker = GetStageTaskWorker(work, SailObject);

    VecFx32 position = worker->player->position;

    StageTask *player = worker->player;
    switch (player->objType)
    {
        case SAILSTAGE_OBJ_TYPE_PLAYER: {
            SailPlayer *playerWorker = GetStageTaskWorker(player, SailPlayer);
            VEC_Subtract(&player->position, &playerWorker->field_4, &position);
        }
        break;

        case SAILSTAGE_OBJ_TYPE_EFFECT:
        case SAILSTAGE_OBJ_TYPE_OBJECT: {
            if ((work->userFlag & SAILOBJECT_FLAG_40) == 0)
                break;

            SailObject *playerWorker = GetStageTaskWorker(player, SailObject);
            VEC_Subtract(&player->position, &playerWorker->field_4, &position);
        }
        break;
    }

    worker->field_10 = position;
}

void SailObject__Func_21667BC(StageTask *work)
{
    SailObject *worker = GetStageTaskWorker(work, SailObject);

    VecFx32 position = worker->player->position;

    StageTask *player = worker->player;
    switch (player->objType)
    {
        case SAILSTAGE_OBJ_TYPE_PLAYER: {
            SailPlayer *playerWorker = GetStageTaskWorker(player, SailPlayer);
            VEC_Subtract(&player->position, &playerWorker->field_4, &position);
        }
        break;

        case SAILSTAGE_OBJ_TYPE_OBJECT: {
            SailObject *playerWorker = GetStageTaskWorker(player, SailObject);
            VEC_Subtract(&player->position, &playerWorker->field_4, &position);
        }
        break;
    }

    worker->field_10.y = position.y;
}

void SailObject__Func_2166834(StageTask *work)
{
    SailObject *worker = GetStageTaskWorker(work, SailObject);

    VecFx32 position = work->position;
    VEC_Subtract(&work->position, &worker->field_4, &position);

    VecFx32 unknown = worker->field_10;

    SailObject__Func_216688C(work, &position, &unknown);
}

void SailObject__Func_216688C(StageTask *work, VecFx32 *a2, VecFx32 *a3)
{
    MtxFx43 mtx;

    OBS_ACTION3D_NN_WORK *animator = work->obj_3d;

    VecFx32 unknown2 = { FLOAT_TO_FX32(0.0), FLOAT_TO_FX32(1.0), FLOAT_TO_FX32(0.0) };

    VecFx32 translation = *a2;
    VecFx32 unknown1    = *a3;

    translation.y = -translation.y;
    unknown1.y    = -unknown1.y;

    Unknown2066510__Func_2066A4C(&translation, &unknown1, &unknown2, &mtx);
    MTX_Copy43To33(&mtx, &animator->ani.work.rotation);
}

NONMATCH_FUNC void SailObject__Func_216690C(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0xc
	mov r6, r1
	ldr r4, [r0, #0x124]
	bl SailManager__GetWork
	ldr r5, [r0, #0x98]
	add r1, sp, #0
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	str r0, [r1, #8]
	add r1, r4, #0x100
	ldrh r3, [r1, #0x6c]
	ldr r2, [r4, #0x178]
	ldr r0, [r4, #0x134]
	ldr r5, [r5, #0xc0]
	sub r2, r2, r0
	mov r0, #0x28
	str r2, [r4, #0x178]
	mla r5, r3, r0, r5
	ldrh r0, [r1, #0x6c]
	cmp r0, r2, asr #19
	ble _02166984
	ldrh r0, [r5, #2]
	strh r0, [r1, #0x6e]
	ldrh r0, [r1, #0x6c]
	cmp r0, #0
	subne r0, r0, #1
	strneh r0, [r1, #0x6c]
	subne r5, r5, #0x28
_02166984:
	add r0, r4, #0x100
	ldrh r1, [r0, #0x6c]
	ldr r2, [r4, #0x178]
	cmp r1, r2, asr #19
	bge _021669AC
	add r1, r1, #1
	strh r1, [r0, #0x6c]
	add r5, r5, #0x28
	ldrh r1, [r5, #2]
	strh r1, [r0, #0x6e]
_021669AC:
	mov r0, r5
	bl SailVoyageManager__GetSegmentSize
	ldr r3, [r4, #0x178]
	ldr r2, =0x0007FFFF
	mov r1, r0
	and r0, r3, r2
	bl FX_Div
	mov r7, r0
	mov r0, r5
	mov r1, r7
	bl SailVoyageManager__GetAngleForSegmentPos
	add r1, r4, #0x100
	cmp r6, #0
	strh r0, [r1, #0x6e]
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4, r5, r6, r7, pc}
	add r2, sp, #0
	add r3, sp, #8
	mov r0, r5
	mov r1, r7
	bl SailVoyageManager__Func_2158888
	add r0, sp, #0
	mov r2, r6
	add r1, r4, #0x1c
	bl VEC_Subtract
	add r0, sp, #0
	add r3, r4, #0x1c
	ldmia r0, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__Func_2166A2C(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	mov r4, r0
	ldr r5, [r4, #0x124]
	bl SailManager__GetWork
	ldr r7, [r0, #0x98]
	ldr r0, [r5, #0x178]
	ldr r1, [r4, #8]
	ldr r2, [r7, #0xc0]
	mov r8, r0, asr #0x13
	mov r0, #0x28
	mla r6, r8, r0, r2
	cmp r1, #0
	bne _02166A70
	add r0, r5, #0x170
	add r1, r5, #0x17c
	mov r2, r0
	bl VEC_Add
_02166A70:
	ldr r0, [r4, #0x24]
	tst r0, #1
	beq _02166A98
	ldr r1, [r7, #0x44]
	ldr r0, [r7, #0x48]
	ldr r2, [r5, #0x178]
	sub r0, r1, r0
	add r0, r2, r0
	str r0, [r5, #0x178]
	b _02166AB8
_02166A98:
	bl SailManager__GetShipType
	cmp r0, #1
	bne _02166AB8
	ldr r0, [r4, #8]
	cmp r0, #0
	ldrne r0, [r5, #0x178]
	addne r0, r0, #0x800
	strne r0, [r5, #0x178]
_02166AB8:
	ldr r0, [r5, #0x178]
	cmp r8, r0, asr #19
	ble _02166ADC
	ldrh r1, [r6, #2]
	cmp r8, #0
	add r0, r5, #0x100
	strh r1, [r0, #0x6e]
	subne r8, r8, #1
	subne r6, r6, #0x28
_02166ADC:
	ldr r0, [r5, #0x178]
	cmp r8, r0, asr #19
	bge _02166AF8
	add r6, r6, #0x28
	ldrh r1, [r6, #2]
	add r0, r5, #0x100
	strh r1, [r0, #0x6e]
_02166AF8:
	mov r0, r6
	bl SailVoyageManager__GetSegmentSize
	ldr r3, [r5, #0x178]
	ldr r2, =0x0007FFFF
	mov r1, r0
	and r0, r3, r2
	bl FX_Div
	mov r8, r0
	mov r0, r6
	mov r1, r8
	bl SailVoyageManager__GetAngleForSegmentPos
	add r2, r5, #0x100
	strh r0, [r2, #0x6e]
	mov r1, r8
	mov r0, r6
	add r2, r4, #0x44
	add r3, r4, #0x4c
	bl SailVoyageManager__Func_2158888
	add r6, r5, #0x100
	ldrh r2, [r6, #0x6e]
	ldr lr, =FX_SinCosTable_
	mov r1, r7
	rsb r2, r2, #0
	mov r2, r2, lsl #0x10
	mov r2, r2, lsr #0x10
	mov r2, r2, lsl #0x10
	mov r2, r2, lsr #0x10
	mov r2, r2, asr #4
	mov r2, r2, lsl #1
	add r2, r2, #1
	mov r2, r2, lsl #1
	ldrsh r7, [lr, r2]
	ldr r3, [r5, #0x170]
	ldr ip, [r4, #0x44]
	smull r8, r7, r3, r7
	adds r8, r8, #0x800
	adc r3, r7, #0
	mov r7, r8, lsr #0xc
	orr r7, r7, r3, lsl #20
	add r3, ip, r7
	str r3, [r4, #0x44]
	ldrh r6, [r6, #0x6e]
	ldr r3, [r5, #0x170]
	ldr ip, [r4, #0x4c]
	rsb r6, r6, #0
	mov r6, r6, lsl #0x10
	mov r6, r6, lsr #0x10
	mov r6, r6, lsl #0x10
	mov r6, r6, lsr #0x10
	mov r6, r6, asr #4
	mov r6, r6, lsl #2
	ldrsh r6, [lr, r6]
	add r0, r4, #0x44
	mov r2, r0
	smull r7, r6, r3, r6
	adds r7, r7, #0x800
	adc r3, r6, #0
	mov r6, r7, lsr #0xc
	orr r6, r6, r3, lsl #20
	add r3, ip, r6
	str r3, [r4, #0x4c]
	ldr r3, [r5, #0x174]
	str r3, [r4, #0x48]
	bl VEC_Subtract
	ldmia sp!, {r4, r5, r6, r7, r8, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__Func_2166C04(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	ldr r5, [r0, #0x124]
	mov r4, r1
	bl SailManager__GetWork
	ldr r2, [r5, #0x178]
	mov r1, #0x28
	mov r2, r2, asr #0x13
	ldr r6, [r0, #0x98]
	mul r7, r2, r1
	ldr r8, [r6, #0xc0]
	add r0, r8, r7
	bl SailVoyageManager__GetSegmentSize
	mov r1, r0
	ldr r2, [r5, #0x178]
	ldr r0, =0x0007FFFF
	and r0, r2, r0
	bl FX_Div
	mov r1, r0
	add r0, r8, r7
	mov r2, r4
	add r3, r4, #8
	bl SailVoyageManager__Func_2158888
	mov r1, r6
	ldr ip, [r4]
	ldr r3, [r5, #0x170]
	add r6, r5, #0x100
	ldrh r2, [r6, #0x6e]
	ldr lr, =FX_SinCosTable_
	mov r0, r4
	rsb r2, r2, #0
	mov r2, r2, lsl #0x10
	mov r2, r2, lsr #0x10
	mov r2, r2, lsl #0x10
	mov r2, r2, lsr #0x10
	mov r2, r2, asr #4
	mov r2, r2, lsl #1
	add r2, r2, #1
	mov r2, r2, lsl #1
	ldrsh r7, [lr, r2]
	mov r2, r4
	smull r8, r7, r3, r7
	adds r8, r8, #0x800
	adc r3, r7, #0
	mov r7, r8, lsr #0xc
	orr r7, r7, r3, lsl #20
	add r3, ip, r7
	str r3, [r4]
	ldr r3, [r5, #0x170]
	ldrh r5, [r6, #0x6e]
	ldr ip, [r4, #8]
	rsb r5, r5, #0
	mov r5, r5, lsl #0x10
	mov r5, r5, lsr #0x10
	mov r5, r5, lsl #0x10
	mov r5, r5, lsr #0x10
	mov r5, r5, asr #4
	mov r5, r5, lsl #2
	ldrsh r5, [lr, r5]
	smull r6, r5, r3, r5
	adds r6, r6, #0x800
	adc r3, r5, #0
	mov r5, r6, lsr #0xc
	orr r5, r5, r3, lsl #20
	add r3, ip, r5
	str r3, [r4, #8]
	bl VEC_Subtract
	ldmia sp!, {r4, r5, r6, r7, r8, pc}

// clang-format on
#endif
}

void SailObject__Func_2166D18(StageTask *work)
{
    work->velocity.y += _0218BC64[(work->userTimer >> 2) & 0x7];
    work->userTimer++;
}

void SailObject__Func_2166D50(StageTask *work)
{
    work->velocity.y = -_0218BC64[(work->userTimer >> 2) & 0x7] >> 2;
    work->userTimer++;
}

void SailObject__Func_2166D88(void)
{
    OBS_RECT_WORK *rect;
    SailColliderWork *collider;
    SailColliderWorkHitCheck *hitCheck;
    s16 i;

    for (i = 0; TRUE; i++)
    {
        rect = ObjRect__RegistGetNext(15, i);
        if (rect == NULL)
            break;

        if ((rect->flag & OBS_RECT_WORK_FLAG_800) == 0 && (rect->flag & OBS_RECT_WORK_FLAG_80000) != 0)
        {
            collider = rect->userData;

            VecFx32 position;
            MtxFx33 mtx;
            switch (collider->type)
            {
                case 1: {
                    hitCheck = &collider->hitCheck;

                    if (hitCheck->field_C.x != 0 || hitCheck->field_C.z != 0 || hitCheck->field_24.z)
                    {
                        if (rect->parent != NULL)
                            hitCheck->angle = rect->parent->dir.y;
                    }

                    hitCheck->field_0   = *hitCheck->field_34;
                    hitCheck->field_0.y = -hitCheck->field_0.y;

                    position = hitCheck->field_C;

                    if (hitCheck->angle != 0)
                    {
                        if (hitCheck->field_C.x != 0 || hitCheck->field_C.z != 0)
                        {
                            MTX_RotY33(&mtx, SinFX((s32)hitCheck->angle), CosFX((s32)hitCheck->angle));
                            MTX_MultVec33(&position, &mtx, &position);
                        }
                    }

                    VEC_Subtract(&hitCheck->field_0, &position, &hitCheck->field_0);
                }
                break;

                case 2: {
                    hitCheck = &collider->hitCheck;

                    position   = *collider->hitCheck.type2.field_4C;
                    position.y = -position.y;

                    VEC_Subtract(&position, &hitCheck->type2.field_3C, &position);
                    VEC_Add(&hitCheck->field_18, &position, &hitCheck->field_0);
                    VEC_Add(&hitCheck->field_24, &position, &hitCheck->field_C);
                }
                break;
            }
        }
    }
}

NONMATCH_FUNC StageTask *SailBuoy__Create(StageTask *parent)
{
    // should match when 'aSbBuoyNsbmd_0' & 'aSbBuoyNsbca' are decompiled
#ifdef NON_MATCHING
    StageTask *work;
    SailObject *worker;

    work = CreateStageTaskSimple();
    StageTask__SetType(work, SAILSTAGE_OBJ_TYPE_OBJECT);

    worker = StageTask__AllocateWorker(work, sizeof(SailObject));

    ObjAction3dNNModelLoad(work, NULL, "sb_buoy.nsbmd", 0, GetObjectFileWork(OBJDATAWORK_28), SailManager__GetArchive());
    if (SailManager__GetShipType() != SHIP_SUBMARINE)
    {
        ObjAction3dNNMotionLoad(work, NULL, "sb_buoy.nsbca", GetObjectFileWork(OBJDATAWORK_29), SailManager__GetArchive());
        AnimatorMDL__SetAnimation(&work->obj_3d->ani, 0, work->obj_3d->resources[B3D_RESOURCE_JOINT_ANIM], 0, NULL);
        SailObject__SetAnimSpeed(work, FLOAT_TO_FX32(2.0));
        work->displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;
    }

    NNS_G3dMdlSetMdlEmi(work->obj_3d->ani.renderObj.resMdl, 1, GX_RGB_888(0x00, 0x00, 0x00));
    NNS_G3dMdlSetMdlLightEnableFlag(work->obj_3d->ani.renderObj.resMdl, 1, GX_LIGHTID_0);

    SailObject__InitCommon(work);
    SailObject__InitFromMapObject(work, mapObject);

    work->userWork = mapObject->viewRange;
    work->flag |= STAGE_TASK_FLAG_NO_OBJ_COLLISION;
    work->userFlag |= SAILOBJECT_FLAG_80000;

    fx32 scale;
    if (SailManager__GetShipType() != SHIP_BOAT)
    {
        scale = MultiplyFX(FLOAT_TO_FX32(0.5), work->scale.x);
    }
    else
    {
        scale = MultiplyFX(FLOAT_TO_FX32(0.25), work->scale.x);
        SailObject__SetupHitbox(work, &worker->collider[0], 0);
        SailObject__SetupHitbox(work, &worker->collider[1], 3);
        SailObject__Func_21658A4(work, 0);

        VecFx32 a4;
        a4.x = FLOAT_TO_FX32(0.0);
        a4.y = -FLOAT_TO_FX32(1.5);
        a4.z = FLOAT_TO_FX32(0.0);
        SailObject__Func_21658D0(work, 0, FLOAT_TO_FX32(1.75), &a4);

        a4.x = FLOAT_TO_FX32(0.0);
        a4.y = -FLOAT_TO_FX32(4.625);
        a4.z = FLOAT_TO_FX32(0.0);
        SailObject__Func_21658D0(work, 3, FLOAT_TO_FX32(1.5), &a4);

        work->flag &= ~STAGE_TASK_FLAG_NO_OBJ_COLLISION;
        worker->field_120 = FLOAT_TO_FX32(150.0);
        worker->health    = FLOAT_TO_FX32(150.0);
        worker->dword118  = 1500;
        work->userFlag |= SAILOBJECT_FLAG_2000000;
        work->userFlag |= SAILOBJECT_FLAG_40000;
    }

    work->scale.x = scale;
    work->scale.y = scale;
    work->scale.z = scale;

    StageTask__InitSeqPlayer(work);
    SailBuoy__SetupObject(work);

    return work;
#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0x14
	mov r6, r0
	bl CreateStageTask_
	mov r4, r0
	mov r1, #1
	bl StageTask__SetType
	mov r0, r4
	mov r1, #0x1a0
	bl StageTask__AllocateWorker
	mov r5, r0
	mov r0, #0x1c
	bl GetObjectFileWork
	mov r7, r0
	bl SailManager__GetArchive
	str r7, [sp]
	str r0, [sp, #4]
	mov r0, r4
	mov r1, #0
	ldr r2, =aSbBuoyNsbmd_0
	mov r3, r1
	bl ObjAction3dNNModelLoad
	bl SailManager__GetShipType
	cmp r0, #3
	beq _02166FCC
	mov r0, #0x1d
	bl GetObjectFileWork
	mov r7, r0
	bl SailManager__GetArchive
	str r0, [sp]
	ldr r2, =aSbBuoyNsbca
	mov r0, r4
	mov r3, r7
	mov r1, #0
	bl ObjAction3dNNMotionLoad
	ldr r0, [r4, #0x12c]
	mov r1, #0
	str r1, [sp]
	ldr r2, [r0, #0x148]
	mov r3, r1
	bl AnimatorMDL__SetAnimation
	mov r0, r4
	mov r1, #0x2000
	bl SailObject__SetAnimSpeed
	ldr r0, [r4, #0x20]
	orr r0, r0, #4
	str r0, [r4, #0x20]
_02166FCC:
	ldr r0, [r4, #0x12c]
	mov r1, #1
	ldr r0, [r0, #0x94]
	mov r2, #0
	bl NNS_G3dMdlSetMdlEmi
	ldr r0, [r4, #0x12c]
	mov r1, #1
	ldr r0, [r0, #0x94]
	mov r2, #0
	bl NNS_G3dMdlSetMdlLightEnableFlag
	mov r0, r4
	bl SailObject__InitCommon
	mov r0, r4
	mov r1, r6
	bl SailObject__InitFromMapObject
	ldr r0, [r6, #0x28]
	str r0, [r4, #0x28]
	ldr r0, [r4, #0x18]
	orr r0, r0, #2
	str r0, [r4, #0x18]
	ldr r0, [r4, #0x24]
	orr r0, r0, #0x80000
	str r0, [r4, #0x24]
	bl SailManager__GetShipType
	ldr r2, [r4, #0x38]
	cmp r0, #1
	mov r0, #0x800
	mov r1, r2, asr #0x1f
	beq _0216705C
	mov r1, r1, lsl #0xb
	adds r3, r0, r2, lsl #11
	orr r1, r1, r2, lsr #21
	adc r0, r1, #0
	mov r6, r3, lsr #0xc
	orr r6, r6, r0, lsl #20
	b _02167118
_0216705C:
	mov r1, r1, lsl #0xa
	adds r6, r0, r2, lsl #10
	orr r1, r1, r2, lsr #22
	adc r3, r1, #0
	mov r6, r6, lsr #0xc
	mov r0, r4
	add r1, r5, #0x28
	mov r2, #0
	orr r6, r6, r3, lsl #20
	bl SailObject__SetupHitbox
	mov r0, r4
	add r1, r5, #0xa0
	mov r2, #3
	bl SailObject__SetupHitbox
	mov r0, r4
	mov r1, #0
	bl SailObject__Func_21658A4
	mov r1, #0
	sub r0, r1, #0x1800
	str r0, [sp, #0xc]
	mov r0, r4
	mov r2, #0x1c00
	add r3, sp, #8
	str r1, [sp, #8]
	str r1, [sp, #0x10]
	bl SailObject__Func_21658D0
	mov r0, #0
	str r0, [sp, #8]
	str r0, [sp, #0x10]
	sub r0, r0, #0x4a00
	str r0, [sp, #0xc]
	mov r0, r4
	mov r1, #3
	mov r2, #0x1800
	add r3, sp, #8
	bl SailObject__Func_21658D0
	ldr r1, [r4, #0x18]
	mov r0, #0x96000
	bic r1, r1, #2
	str r1, [r4, #0x18]
	str r0, [r5, #0x120]
	str r0, [r5, #0x11c]
	ldr r0, =0x000005DC
	str r0, [r5, #0x118]
	ldr r0, [r4, #0x24]
	orr r0, r0, #0x2040000
	str r0, [r4, #0x24]
_02167118:
	str r6, [r4, #0x38]
	str r6, [r4, #0x3c]
	mov r0, r4
	str r6, [r4, #0x40]
	bl StageTask__InitSeqPlayer
	mov r0, r4
	bl SailBuoy__SetupObject
	mov r0, r4
	add sp, sp, #0x14
	ldmia sp!, {r4, r5, r6, r7, pc}

// clang-format on
#endif
}

NONMATCH_FUNC StageTask *SailBuoy__CreateFromSegment(SailVoyageSegment *voyageSegment)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0xc
	mov r6, r0
	bl SailManager__GetWork
	ldr r4, [r0, #0xa0]
	add r1, sp, #0
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	str r0, [r1, #8]
	bl SailManager__GetShipType
	mov r1, r0, lsl #0x10
	mov r2, #0
	mov r0, r6
	str r2, [sp, #4]
	mov r5, r1, lsr #0x10
	bl SailVoyageManager__GetSegmentSize
	mov r7, r0
	mov r0, r6
	bl SailVoyageManager__GetSegmentSize
	ldr r1, [r6, #0x24]
	cmp r5, #0
	add r1, r1, r7
	sub r0, r1, r0, asr #4
	str r0, [sp, #8]
	beq _021671C0
	cmp r5, #1
	beq _021671DC
	cmp r5, #2
_021671C0:
	ldr r0, =0x0218B9AC
	mov r1, r5, lsl #1
	ldrh r1, [r0, r1]
	mov r0, #0x5c
	mul r0, r1, r0
	str r0, [sp]
	b _02167228
_021671DC:
	ldrsh r7, [r6, #0xa]
	mov r0, #0xb
	mov r1, #0
	cmp r7, #0
	rsblt r7, r7, #0
	umull r3, r2, r7, r0
	mla r2, r7, r1, r2
	mov r1, r7, asr #0x1f
	mla r2, r1, r0, r2
	adds r3, r3, #0x800
	ldr r0, =0x0218B9AC
	mov r1, r5, lsl #1
	adc r2, r2, #0
	mov r3, r3, lsr #0xc
	ldrh r0, [r0, r1]
	orr r3, r3, r2, lsl #20
	add r1, r3, #0x10
	mul r0, r1, r0
	str r0, [sp]
_02167228:
	ldrsh r0, [r6, #0xa]
	cmp r0, #0
	ldrgt r0, [sp]
	rsbgt r0, r0, #0
	strgt r0, [sp]
	ldrsh r0, [r6, #0xa]
	cmp r0, #0
	bne _0216727C
	ldr r2, =_obj_disp_rand
	ldr r0, =0x00196225
	ldr r3, [r2, #0]
	ldr r1, =0x3C6EF35F
	mla r1, r3, r0, r1
	mov r0, r1, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	tst r0, #1
	ldrne r0, [sp]
	str r1, [r2]
	rsbne r0, r0, #0
	strne r0, [sp]
_0216727C:
	add r1, sp, #0
	mov r0, #0x1f
	bl SailEventManager__CreateObject
	ldrh r2, [r6, #0x30]
	mov r1, r0
	cmp r2, #3
	blo _021672A4
	cmp r2, #5
	movls r0, #1
	strls r0, [r1, #0x28]
_021672A4:
	mov r0, r4
	bl NNS_FndAppendListObject
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}

// clang-format on
#endif
}

NONMATCH_FUNC StageTask *SailBuoy__CreateFromSegment2(SailVoyageSegment *voyageSegment)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #0xc
	mov r5, r0
	bl SailManager__GetWork
	ldr r4, [r0, #0xa0]
	add r2, sp, #0
	mov r1, #0
	str r1, [r2, #4]
	mov r0, r5
	str r1, [r2]
	str r1, [r2, #8]
	str r1, [sp, #4]
	bl SailVoyageManager__GetSegmentSize
	ldr r1, [r5, #0x24]
	add r0, r1, r0
	str r0, [sp, #8]
	bl SailManager__GetShipType
	ldr r1, =0x0218B9AC
	mov r0, r0, lsl #1
	ldrh r1, [r1, r0]
	mov r0, #0x5c
	mul r0, r1, r0
	str r0, [sp]
	bl SailManager__GetShipType
	cmp r0, #1
	beq _02167338
	cmp r0, #3
	beq _02167358
	b _02167390
_02167338:
	bl SailManager__GetShipType
	ldr r1, =0x0218B9AC
	mov r0, r0, lsl #1
	ldrh r1, [r1, r0]
	mov r0, #0xa
	mul r0, r1, r0
	str r0, [sp]
	b _02167390
_02167358:
	bl SailManager__GetShipType
	mov r2, r0, lsl #1
	ldr r0, =0x0218B9AC
	mov r1, #0x3c
	ldrh r3, [r0, r2]
	mov r2, #0x400
	mov r0, r5
	mul r1, r3, r1
	str r1, [sp]
	str r2, [sp, #4]
	bl SailVoyageManager__GetSegmentSize
	ldr r1, [sp, #8]
	add r0, r1, r0, asr #2
	str r0, [sp, #8]
_02167390:
	add r1, sp, #0
	mov r0, #0x1f
	bl SailEventManager__CreateObject
	mov r1, r0
	mov r2, #2
	mov r0, r4
	str r2, [r1, #0x28]
	bl NNS_FndAppendListObject
	ldr r0, [sp]
	add r1, sp, #0
	rsb r2, r0, #0
	mov r0, #0x1f
	str r2, [sp]
	bl SailEventManager__CreateObject
	mov r1, r0
	mov r2, #2
	mov r0, r4
	str r2, [r1, #0x28]
	bl NNS_FndAppendListObject
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC StageTask *SailSeagull__Create(SailEventManagerObject *mapObject)
{
    // should match when 'aSbSeagullBac' is decompiled
#ifdef NON_MATCHING
    StageTask *work;
    SailObject *worker;

    work = CreateStageTaskSimple();
    StageTask__SetType(work, SAILSTAGE_OBJ_TYPE_OBJECT);

    worker = StageTask__AllocateWorker(work, sizeof(SailObject));
    UNUSED(worker);

    ObjObjectAction3dBACLoad(work, NULL, "sb_seagull.bac", OBJ_DATA_GFX_AUTO, OBJ_DATA_GFX_AUTO, GetObjectFileWork(OBJDATAWORK_30), SailManager__GetArchive());
    work->obj_2dIn3d->ani.work.matrixOpIDs[0] = MATRIX_OP_SET_CAMERA_ROT_33;
    work->obj_2dIn3d->ani.work.matrixOpIDs[1] = MATRIX_OP_FLUSH_P_CAMERA3D;
    work->displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;

    SailObject__InitCommon(work);
    SailObject__InitFromMapObject(work, mapObject);
    work->flag |= STAGE_TASK_FLAG_NO_OBJ_COLLISION;

    SailSeagull__SetupObject(work);

    return work;
#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, lr}
	sub sp, sp, #0xc
	mov r5, r0
	bl CreateStageTask_
	mov r4, r0
	mov r1, #1
	bl StageTask__SetType
	mov r0, r4
	mov r1, #0x1a0
	bl StageTask__AllocateWorker
	mov r0, #0x1e
	bl GetObjectFileWork
	mov r6, r0
	bl SailManager__GetArchive
	ldr r3, =0x0000FFFF
	ldr r2, =aSbSeagullBac
	stmia sp, {r3, r6}
	str r0, [sp, #8]
	mov r1, #0
	mov r0, r4
	bl ObjObjectAction3dBACLoad
	ldr r0, [r4, #0x134]
	mov r1, #0x1d
	strb r1, [r0, #0xa]
	ldr r1, [r4, #0x134]
	mov r2, #7
	strb r2, [r1, #0xb]
	ldr r1, [r4, #0x20]
	mov r0, r4
	orr r1, r1, #4
	str r1, [r4, #0x20]
	bl SailObject__InitCommon
	mov r1, r5
	mov r0, r4
	bl SailObject__InitFromMapObject
	ldr r1, [r4, #0x18]
	mov r0, r4
	orr r1, r1, #2
	str r1, [r4, #0x18]
	bl SailSeagull__SetupObject
	mov r0, r4
	add sp, sp, #0xc
	ldmia sp!, {r3, r4, r5, r6, pc}

// clang-format on
#endif
}

NONMATCH_FUNC StageTask *SailSeagull2__Create(SailEventManagerObject *mapObject)
{
    // should match when 'aSbSeagullNsbmd_0' is decompiled
#ifdef NON_MATCHING
    StageTask *work;
    SailObject *worker;

    work = CreateStageTaskSimple();
    StageTask__SetType(work, SAILSTAGE_OBJ_TYPE_OBJECT);

    worker = StageTask__AllocateWorker(work, sizeof(SailObject));
    UNUSED(worker);

    ObjAction3dNNModelLoad(work, NULL, "sb_seagull.nsbmd", 0, GetObjectFileWork(OBJDATAWORK_31), SailManager__GetArchive());
    SailObject__InitCommon(work);
    SailObject__InitFromMapObject(work, mapObject);
    work->flag |= STAGE_TASK_FLAG_NO_OBJ_COLLISION;

    SailSeagull2__SetupObject(work);

    return work;
#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #8
	mov r6, r0
	bl CreateStageTask_
	mov r5, r0
	mov r1, #1
	bl StageTask__SetType
	mov r0, r5
	mov r1, #0x1a0
	bl StageTask__AllocateWorker
	mov r0, #0x1f
	bl GetObjectFileWork
	mov r4, r0
	bl SailManager__GetArchive
	str r4, [sp]
	str r0, [sp, #4]
	mov r0, r5
	mov r1, #0
	ldr r2, =aSbSeagullNsbmd_0
	mov r3, r1
	bl ObjAction3dNNModelLoad
	mov r0, r5
	bl SailObject__InitCommon
	mov r1, r6
	mov r0, r5
	bl SailObject__InitFromMapObject
	ldr r1, [r5, #0x18]
	mov r0, r5
	orr r1, r1, #2
	str r1, [r5, #0x18]
	bl SailSeagull2__SetupObject
	mov r0, r5
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, pc}

// clang-format on
#endif
}

NONMATCH_FUNC StageTask *SailSeagull3__Create(StageTask *parent)
{
    // should match when 'aSbSeagullNsbmd_0' is decompiled
#ifdef NON_MATCHING
    StageTask *work;
    SailObject *worker;

    work = CreateStageTaskSimple();
    StageTask__SetType(work, SAILSTAGE_OBJ_TYPE_OBJECT);

    worker = StageTask__AllocateWorker(work, sizeof(SailObject));
    UNUSED(worker);

    ObjAction3dNNModelLoad(work, NULL, "sb_seagull.nsbmd", 0, GetObjectFileWork(OBJDATAWORK_31), SailManager__GetArchive());
    SailObject__InitCommon(work);
    StageTask__SetParent(work, parent, 0);

    work->flag |= STAGE_TASK_FLAG_DISABLE_VIEWCHECK_EVENT | STAGE_TASK_FLAG_NO_OBJ_COLLISION;
    work->moveFlag |= STAGE_TASK_MOVE_FLAG_DISABLE_MOVE_EVENT;

    OBS_ACTION3D_NN_WORK *animator = work->obj_3d;
    fx32 scale                     = animator->ani.work.scale.x;
    scale                          = MultiplyFX(0x200, 0x1200 + ObjDispRandRepeat(0x200));
    animator->ani.work.scale.z = animator->ani.work.scale.y = animator->ani.work.scale.x = scale;

    SailSeagull3__State_216BF2C(work);

    return work;
#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #8
	mov r6, r0
	bl CreateStageTask_
	mov r4, r0
	mov r1, #1
	bl StageTask__SetType
	mov r0, r4
	mov r1, #0x1a0
	bl StageTask__AllocateWorker
	mov r0, #0x1f
	bl GetObjectFileWork
	mov r5, r0
	bl SailManager__GetArchive
	str r5, [sp]
	mov r1, #0
	str r0, [sp, #4]
	ldr r2, =aSbSeagullNsbmd_0
	mov r0, r4
	mov r3, r1
	bl ObjAction3dNNModelLoad
	mov r0, r4
	bl SailObject__InitCommon
	mov r1, r6
	mov r0, r4
	mov r2, #0
	bl StageTask__SetParent
	ldr r0, [r4, #0x18]
	ldr ip, =_obj_disp_rand
	orr r0, r0, #0x12
	str r0, [r4, #0x18]
	ldr r0, [r4, #0x1c]
	ldr r1, =0x00196225
	orr r0, r0, #0x2000
	str r0, [r4, #0x1c]
	ldr lr, [ip]
	ldr r2, =0x3C6EF35F
	ldr r0, [r4, #0x12c]
	mla r1, lr, r1, r2
	str r1, [ip]
	mov r1, r1, lsr #0x10
	ldr r3, =0x000001FF
	mov r1, r1, lsl #0x10
	and r1, r3, r1, lsr #16
	add r2, r1, #0x1200
	mov r1, r2, asr #0x1f
	mov r3, r1, lsl #9
	mov r1, #0x800
	orr r3, r3, r2, lsr #23
	adds r2, r1, r2, lsl #9
	adc r1, r3, #0
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #20
	str r2, [r0, #0x18]
	str r2, [r0, #0x1c]
	str r2, [r0, #0x20]
	mov r0, r4
	bl SailSeagull3__State_216BF2C
	mov r0, r4
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, pc}

// clang-format on
#endif
}

NONMATCH_FUNC StageTask *SailSeagull__CreateFromSegment(SailVoyageSegment *voyageSegment)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0xc
	mov r5, r0
	bl SailManager__GetWork
	ldr r4, [r0, #0xa0]
	add r1, sp, #0
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	str r0, [r1, #8]
	bl SailManager__GetShipType
	ldr r1, [r5, #0x24]
	mov r0, r0, lsl #0x10
	str r1, [sp, #8]
	movs lr, r0, lsr #0x10
	beq _0216767C
	cmp lr, #1
	beq _021676EC
	cmp lr, #2
_0216767C:
	ldr r6, =_obj_disp_rand
	ldr r0, =0x00196225
	ldr r3, [r6, #0]
	ldr r2, =0x3C6EF35F
	ldr r1, =0x0218B9AC
	mla r5, r3, r0, r2
	mla r0, r5, r0, r2
	mov r2, r0, lsr #0x10
	mov r3, r5, lsr #0x10
	mov r5, r2, lsl #0x10
	mov r2, lr, lsl #1
	ldr r7, =0x0218B9B4
	mov r3, r3, lsl #0x10
	mov r5, r5, lsr #0x10
	mov ip, r3, lsr #0x10
	and r3, r5, #0x1f
	and r5, ip, #0x7e
	add r3, r3, #0x50
	ldrh ip, [r1, r2]
	rsb r5, r5, #0x3f
	ldrh r2, [r7, r2]
	rsb r1, r3, #0
	mul r3, ip, r5
	mul r1, r2, r1
	str r3, [sp]
	str r0, [r6]
	str r1, [sp, #4]
	b _02167800
_021676EC:
	ldrsh r6, [r5, #0xa]
	mov r3, #0xb
	mov r2, #0
	cmp r6, #0
	rsblt r6, r6, #0
	umull r7, r1, r6, r3
	mla r1, r6, r2, r1
	mov r6, r6, asr #0x1f
	mla r1, r6, r3, r1
	adds r2, r7, #0x800
	ldr r0, =_obj_disp_rand
	ldr r6, =0x00196225
	ldr r7, [r0, #0]
	ldr ip, =0x3C6EF35F
	ldr r3, =0x0218B9AC
	mla r6, r7, r6, ip
	mov r7, r6, lsr #0x10
	mov ip, lr, lsl #1
	mov r7, r7, lsl #0x10
	mov r7, r7, lsr #0x10
	adc r1, r1, #0
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #20
	and r1, r7, #0xf
	ldrh r3, [r3, ip]
	add r1, r2, r1
	str r6, [r0]
	mul r1, r3, r1
	str r1, [sp]
	ldrsh r0, [r5, #0xa]
	cmp r0, #0
	rsbgt r0, r1, #0
	strgt r0, [sp]
	ldrsh r0, [r5, #0xa]
	cmp r0, #0
	bne _021677AC
	ldr r0, =0x00196225
	ldr r1, =0x3C6EF35F
	ldr r2, =_obj_disp_rand
	mla r6, r0, r6, r1
	mov r0, r6, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	tst r0, #1
	ldrne r0, [sp]
	str r6, [r2]
	rsbne r0, r0, #0
	strne r0, [sp]
_021677AC:
	ldr r0, =0x00196225
	ldr r1, =0x3C6EF35F
	ldr r2, =0x0218B9B4
	mla r1, r6, r0, r1
	mov r0, r1, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r3, lr, lsl #1
	mov r0, r0, lsr #0x10
	and r0, r0, #7
	add r0, r0, #6
	ldrh r3, [r2, r3]
	rsb r0, r0, #0
	ldr r2, =_obj_disp_rand
	mul r6, r3, r0
	mov r0, r5
	str r1, [r2]
	str r6, [sp, #4]
	bl SailVoyageManager__GetSegmentSize
	ldr r1, [sp, #8]
	add r0, r1, r0, asr #2
	str r0, [sp, #8]
_02167800:
	add r1, sp, #0
	mov r0, #0x23
	bl SailEventManager__CreateObject
	mov r1, r0
	mov r0, r4
	bl NNS_FndAppendListObject
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}

// clang-format on
#endif
}

NONMATCH_FUNC StageTask *SailSeagull__CreateUnknown2(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, lr}
	ldr r3, =_obj_disp_rand
	ldr r1, =0x00196225
	ldr ip, [r3]
	ldr r2, =0x3C6EF35F
	mov r4, r0
	mla r1, ip, r1, r2
	mov r0, r1, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	and r0, r0, #3
	add r0, r0, #2
	mov r0, r0, lsl #0x10
	str r1, [r3]
	movs r5, r0, lsr #0x10
	mov r6, #0
	ldmeqia sp!, {r4, r5, r6, pc}
_02167878:
	mov r0, r4
	bl SailSeagull3__Create
	add r0, r6, #1
	mov r0, r0, lsl #0x10
	cmp r5, r0, lsr #16
	mov r6, r0, lsr #0x10
	bhi _02167878
	ldmia sp!, {r4, r5, r6, pc}

// clang-format on
#endif
}

NONMATCH_FUNC StageTask *SailStone__Create(SailEventManagerObject *mapObject)
{
    // https://decomp.me/scratch/aBonY -> 70.48%
#ifdef NON_MATCHING
    StageTask *work;
    SailObject *worker;

    fx32 v2 = FLOAT_TO_FX32(1.0);

    SailManager *manager             = SailManager__GetWork();
    SailVoyageManager *voyageManager = manager->voyageManager;

    u8 *segmentType;
    segmentType = &voyageManager->segmentList[mapObject->id].field_0;
    if (mapObject->type != SAILMAPOBJECT_26)
    {
        if (*segmentType == SAILVOYAGESEGMENT_TYPE_1 || *segmentType == SAILVOYAGESEGMENT_TYPE_8)
        {
            return SailIce__Create(mapObject);
        }
    }

    work = CreateStageTaskSimple();
    StageTask__SetType(work, SAILSTAGE_OBJ_TYPE_OBJECT);

    worker = StageTask__AllocateWorker(work, sizeof(SailObject));

    u16 anim;
    if (SailManager__GetShipType() != SHIP_SUBMARINE)
    {
        anim = ObjDispRandRepeat(2);
    }
    else
    {
        s32 type1 = ObjDispRandRepeat(2);
        s32 type2 = ObjDispRandRepeat(2);
        anim      = (u16)type1 + (u16)type2;
    }

    ObjAction3dNNModelLoad(work, NULL, "sb_stone.nsbmd", anim, GetObjectFileWork(OBJDATAWORK_32), SailManager__GetArchive());
    SailObject__InitCommon(work);
    SailObject__InitFromMapObject(work, mapObject);
    work->flag |= STAGE_TASK_FLAG_NO_OBJ_COLLISION;
    work->userFlag |= SAILOBJECT_FLAG_40000;

    fx32 scale_1 = work->scale.x;

    VecFx32 position;
    switch (SailManager__GetShipType())
    {
        default: {
            if ((worker->objectRef->flags & 7) != 0)
                v2 *= (worker->objectRef->flags & 7);

            fx32 scale_2  = MultiplyFX(scale_1, v2);
            work->scale.y = MultiplyFX(scale_2, 0x800 + (u32)(0xFF - (ObjDispRandRepeat((0x100 * 2) - 1))));

            if (worker->objectRef->type == SAILMAPOBJECT_26)
            {
                if (anim == 0)
                {
                    work->scale.x = MultiplyFX(scale_2, 0xA60);
                    work->scale.z = work->scale.x;
                }
                else
                {
                    work->scale.x = MultiplyFX(scale_2, 0x9C0);
                    work->scale.z = work->scale.x;
                }

                SailObject__SetupHitbox(work, &worker->collider[1], 1);
                SailObject__Func_21658D0(work, 1, MultiplyFX(0x1160, v2), 0);
                worker->collider[1].flags |= 0x4000;
                work->colliderList[1]->hitPower = 20;
                work->colliderList[1]->defPower = 0;
                work->flag &= ~STAGE_TASK_FLAG_NO_OBJ_COLLISION;
            }
            else
            {
                work->scale.x = MultiplyFX(scale_2, 0x800 + (u32)(0x1FF - ObjDispRandRepeat((0x200 * 2) - 1)));
                work->scale.z = MultiplyFX(scale_2, 0x800 + (u32)(0x1FF - ObjDispRandRepeat((0x200 * 2) - 1)));
            }
            break;
        }

        case SHIP_BOAT: {
            if ((worker->objectRef->flags & 7) != 0)
                v2 *= (worker->objectRef->flags & 7);

            if (mapObject->objectValue14)
            {
                v2 = ObjDispRandRange2(0x1000, 0x1800);
            }

            fx32 scale_2 = MultiplyFX(MultiplyFX(work->scale.x, 0x400), v2);

            work->scale.x = MultiplyFX(scale_2, 0x1000 + (u32)(0x1FF - ObjDispRandRepeat((0x200 * 2) - 1)));
            work->scale.y = MultiplyFX(scale_2, 0x1000 + (u32)(0xFF - ObjDispRandRepeat((0x100 * 2) - 1)));
            work->scale.z = MultiplyFX(scale_2, 0x1000 + (u32)(0x1FF - ObjDispRandRepeat((0x200 * 2) - 1)));

            if (mapObject->objectValue14)
            {
                fx32 value    = 0x1B00 + (0xFF - ObjDispRandRepeat((0x400 * 2) - 1));
                work->scale.x = MultiplyFX(work->scale.x, value);
                work->scale.z = MultiplyFX(work->scale.z, value);
            }

            if (anim != 0)
            {
                position.x = FLOAT_TO_FX32(0.0);
                position.y = FLOAT_TO_FX32(0.0);
                position.z = FLOAT_TO_FX32(0.0);
            }
            else
            {
                position.x = FLOAT_TO_FX32(0.0);
                position.y = FLOAT_TO_FX32(1.0);
                position.z = FLOAT_TO_FX32(0.0);
            }
            SailObject__Func_2165AF4(work, &position);
            SailObject__SetupHitbox(work, worker->collider, 0);
            if (!mapObject->objectValue14)
                SailObject__Func_21658A4(work, 0);
            SailObject__Func_21658D0(work, 0, MultiplyFX(v2, 0x2000), 0);

            work->flag &= ~STAGE_TASK_FLAG_NO_OBJ_COLLISION;

            fx32 health       = MultiplyFX(FLOAT_TO_FX32(40.0), v2);
            worker->field_120 = health;
            worker->health    = health;

            worker->dword118 = 300;
            worker->dword118 = MultiplyFX(v2, worker->dword118);

            break;
        }

        case SHIP_HOVER: {
            if ((worker->objectRef->flags & 7) != 0)
                v2 *= (worker->objectRef->flags & 7);

            fx32 scale_2 = MultiplyFX(scale_1, v2);

            work->scale.y = MultiplyFX(scale_2, 0x800 + (u32)(0xFF - ObjDispRandRepeat((0x100 * 2) - 1)));
            work->scale.x = MultiplyFX(scale_2, 0x800 + (u32)(0x1FF - ObjDispRandRepeat((0x200 * 2) - 1)));
            work->scale.z = MultiplyFX(scale_2, 0x800 + (u32)(0x1FF - ObjDispRandRepeat((0x200 * 2) - 1)));

            if (worker->objectRef->type == SAILMAPOBJECT_26)
            {
                SailObject__SetupHitbox(work, worker->collider, 0);
                SailObject__Func_21658D0(work, 0, MultiplyFX(v2, 0x1000), 0);
                work->flag &= ~STAGE_TASK_FLAG_NO_OBJ_COLLISION;
                worker->collider[0].atkPower = FLOAT_TO_FX32(64.0);

                OBS_RECT_WORK *collider = StageTask__GetCollider(work, 0);
                collider->defFlag |= 4;
                collider->hitPower = 20;

                const s32 value = FLOAT_TO_FX32(40.0);

                fx32 health       = MultiplyFX(value, v2);
                worker->field_120 = health;
                worker->health    = health;

                worker->dword118 = MultiplyFX(300, v2);
            }
            break;
        }

        case SHIP_SUBMARINE: {
            work->scale.x = MultiplyFX(scale_1, 0x1000 + (u32)(0x7FF - ObjDispRandRepeat((0x800 * 2) - 1)));
            work->scale.y = MultiplyFX(scale_1, 0x800 + (u32)(0x3FF - ObjDispRandRepeat((0x400 * 2) - 1)));
            work->scale.z = MultiplyFX(scale_1, 0x1000 + (u32)(0x7FF - ObjDispRandRepeat((0x800 * 2) - 1)));

            SailObject__SetLightColors(work, 5);

            if (mapObject->objectValue14)
            {
                fx32 scale = 0x1B00 + (0xFF - ObjDispRandRepeat((0x200 * 2) - 1));

                work->scale.x = MultiplyFX(work->scale.x, scale);
                work->scale.y = MultiplyFX(work->scale.y, scale);
                work->scale.z = MultiplyFX(work->scale.z, scale);

                work->scale.y = MultiplyFX(work->scale.y, 0x1400 + (u32)(0x7FF & ObjDispRandRepeat((0x800 * 2))));
            }

            if (anim != 0)
            {
                position.x = FLOAT_TO_FX32(0.0);
                position.y = FLOAT_TO_FX32(0.0);
                position.z = FLOAT_TO_FX32(0.0);
            }
            else
            {
                position.x = FLOAT_TO_FX32(0.0);
                position.y = FLOAT_TO_FX32(1.0);
                position.z = FLOAT_TO_FX32(0.0);
            }

            SailObject__Func_2165AF4(work, &position);
            break;
        }
    }

    work->dir.y = ObjDispRand();

    SailObject__ApplyRotation(work);
    StageTask__InitSeqPlayer(work);

    return work;
#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
	sub sp, sp, #0x14
	mov r9, r0
	mov r8, #0x1000
	bl SailManager__GetWork
	ldrh r1, [r9, #0x30]
	ldr r3, [r0, #0x98]
	ldrh r2, [r9, #0x2c]
	mov r0, #0x28
	cmp r1, #0x1a
	mul r0, r2, r0
	ldr r1, [r3, #0xc0]
	beq _021678F8
	ldrb r0, [r1, r0]
	cmp r0, #1
	cmpne r0, #8
	bne _021678F8
	mov r0, r9
	bl SailIce__Create
	add sp, sp, #0x14
	ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
_021678F8:
	bl CreateStageTask_
	mov r4, r0
	mov r1, #1
	bl StageTask__SetType
	mov r0, r4
	mov r1, #0x1a0
	bl StageTask__AllocateWorker
	mov r5, r0
	bl SailManager__GetShipType
	cmp r0, #3
	ldr r0, =0x00196225
	ldr r1, =0x3C6EF35F
	beq _02167950
	ldr r2, =_obj_disp_rand
	ldr r3, [r2, #0]
	mla r1, r3, r0, r1
	mov r0, r1, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	and r6, r0, #1
	str r1, [r2]
	b _02167994
_02167950:
	ldr r3, =_obj_disp_rand
	ldr r2, [r3, #0]
	mla r6, r2, r0, r1
	mla r0, r6, r0, r1
	mov r1, r6, lsr #0x10
	mov r2, r0, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r6, r1, lsr #0x10
	mov r2, r2, lsl #0x10
	mov r1, r2, lsr #0x10
	and r6, r6, #1
	and r2, r1, #1
	mov r1, r6, lsl #0x10
	add r1, r2, r1, lsr #16
	mov r1, r1, lsl #0x10
	str r0, [r3]
	mov r6, r1, lsr #0x10
_02167994:
	mov r0, #0x20
	bl GetObjectFileWork
	mov r7, r0
	bl SailManager__GetArchive
	str r7, [sp]
	str r0, [sp, #4]
	ldr r2, =aSbStoneNsbmd_0
	mov r0, r4
	mov r1, #0
	mov r3, r6
	bl ObjAction3dNNModelLoad
	mov r0, r4
	bl SailObject__InitCommon
	mov r0, r4
	mov r1, r9
	bl SailObject__InitFromMapObject
	ldr r0, [r4, #0x18]
	orr r0, r0, #2
	str r0, [r4, #0x18]
	ldr r0, [r4, #0x24]
	orr r0, r0, #0x40000
	str r0, [r4, #0x24]
	ldr r7, [r4, #0x38]
	bl SailManager__GetShipType
	cmp r0, #1
	beq _02167BE0
	cmp r0, #2
	beq _02167E88
	cmp r0, #3
	beq _02168054
	ldr r0, [r5, #0x164]
	ldr r11, =_obj_disp_rand
	ldr r0, [r0, #0x34]
	ldr lr, =0x00196225
	ands r0, r0, #7
	mulne r0, r8, r0
	movne r8, r0
	smull r9, r1, r7, r8
	ldr r7, [r11, #0]
	ldr r2, =0x3C6EF35F
	ldr r3, =0x000001FE
	mla r0, r7, lr, r2
	adds r7, r9, #0x800
	mov r9, r0, lsr #0x10
	mov r9, r9, lsl #0x10
	and r9, r3, r9, lsr #16
	adc r10, r1, #0
	mov r1, r7, lsr #0xc
	rsb r9, r9, #0xff
	orr r1, r1, r10, lsl #20
	add r7, r9, #0x800
	smull r9, r7, r1, r7
	adds r9, r9, #0x800
	adc r7, r7, #0
	mov r9, r9, lsr #0xc
	orr r9, r9, r7, lsl #20
	str r0, [r11]
	str r9, [r4, #0x3c]
	ldr r0, [r5, #0x164]
	mov r7, r8, asr #0x1f
	ldrh r9, [r0, #0x30]
	mov r0, r1, asr #0x1f
	mov r10, #0
	cmp r9, #0x1a
	mov r9, #0x800
	bne _02167B44
	cmp r6, #0
	moveq r2, #0xa60
	movne r2, #0x9c0
	umull r6, r3, r1, r2
	mla r3, r1, r10, r3
	mla r3, r0, r2, r3
	adds r1, r6, r9
	adc r0, r3, r10
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #20
	str r1, [r4, #0x38]
	str r1, [r4, #0x40]
	mov r0, r4
	add r1, r5, #0xa0
	mov r2, #1
	bl SailObject__SetupHitbox
	ldr r0, =0x00001160
	mov r3, #0
	umull r2, r1, r8, r0
	mla r1, r8, r3, r1
	mla r1, r7, r0, r1
	adds r2, r2, #0x800
	adc r1, r1, #0
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #20
	mov r0, r4
	mov r1, #1
	bl SailObject__Func_21658D0
	add r0, r5, #0x100
	ldrh r3, [r0, #0x14]
	mov r2, #0x14
	mov r1, #0
	orr r3, r3, #0x4000
	strh r3, [r0, #0x14]
	ldr r0, [r4, #0x148]
	strh r2, [r0, #0x2c]
	ldr r0, [r4, #0x148]
	strh r1, [r0, #0x2e]
	ldr r0, [r4, #0x18]
	bic r0, r0, #2
	str r0, [r4, #0x18]
	b _02168230
_02167B44:
	ldr r5, [r11, #0]
	add r6, r3, #0x200
	mla ip, r5, lr, r2
	mov r5, ip, lsr #0x10
	mov r5, r5, lsl #0x10
	and r6, r6, r5, lsr #16
	add r5, r3, #1
	sub r5, r5, r6
	add r6, r5, #0x800
	umull r8, r7, r1, r6
	mov r5, r6, asr #0x1f
	str ip, [r11]
	mla r7, r1, r5, r7
	adds r8, r8, r9
	mla r7, r0, r6, r7
	adc r5, r7, r10
	mov r6, r8, lsr #0xc
	orr r6, r6, r5, lsl #20
	str r6, [r4, #0x38]
	ldr r5, [r11, #0]
	add r6, r3, #0x200
	mla r2, r5, lr, r2
	mov r5, r2, lsr #0x10
	mov r5, r5, lsl #0x10
	and r5, r6, r5, lsr #16
	add r3, r3, #1
	sub r3, r3, r5
	add r5, r3, #0x800
	umull r7, r6, r1, r5
	mov r3, r5, asr #0x1f
	str r2, [r11]
	mla r6, r1, r3, r6
	adds r1, r7, r9
	mla r6, r0, r5, r6
	adc r0, r6, r10
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #20
	str r1, [r4, #0x40]
	b _02168230
_02167BE0:
	ldr r0, [r5, #0x164]
	ldr r0, [r0, #0x34]
	ands r0, r0, #7
	mulne r0, r8, r0
	movne r8, r0
	ldr r0, [r9, #0x38]
	cmp r0, #0
	beq _02167C2C
	ldr r3, =_obj_disp_rand
	ldr r0, =0x00196225
	ldr r7, [r3, #0]
	ldr r1, =0x3C6EF35F
	ldr r2, =0x000007FF
	mla r1, r7, r0, r1
	mov r0, r1, lsr #0x10
	mov r0, r0, lsl #0x10
	and r0, r2, r0, lsr #16
	str r1, [r3]
	add r8, r0, #0x1000
_02167C2C:
	ldr r1, [r4, #0x38]
	ldr r3, =_obj_disp_rand
	mov r0, r1, asr #0x1f
	mov r10, r0, lsl #0xa
	mov r0, #0x800
	adds r2, r0, r1, lsl #10
	orr r10, r10, r1, lsr #22
	ldr r7, [r3, #0]
	ldr r0, =0x00196225
	ldr r1, =0x3C6EF35F
	adc r10, r10, #0
	mov r2, r2, lsr #0xc
	mla r11, r7, r0, r1
	orr r2, r2, r10, lsl #20
	smull r10, r7, r2, r8
	adds r10, r10, #0x800
	adc r2, r7, #0
	mov r10, r10, lsr #0xc
	orr r10, r10, r2, lsl #20
	mov r2, r11, lsr #0x10
	str r11, [r3]
	mov r11, r2, lsl #0x10
	ldr r2, =0x000003FE
	mov r7, r8, asr #0x1f
	and r11, r2, r11, lsr #16
	rsb r11, r11, r2, lsr #1
	add r11, r11, #0x1000
	smull r11, ip, r10, r11
	adds r11, r11, #0x800
	adc ip, ip, #0
	mov r11, r11, lsr #0xc
	orr r11, r11, ip, lsl #20
	str r11, [r4, #0x38]
	ldr ip, [r3]
	sub r11, r2, #0x200
	mla lr, ip, r0, r1
	mov ip, lr, lsr #0x10
	mov ip, ip, lsl #0x10
	and r11, r11, ip, lsr #16
	rsb r11, r11, #0xff
	add r11, r11, #0x1000
	smull r11, ip, r10, r11
	adds r11, r11, #0x800
	adc ip, ip, #0
	mov r11, r11, lsr #0xc
	str lr, [r3]
	orr r11, r11, ip, lsl #20
	str r11, [r4, #0x3c]
	ldr r11, [r3, #0]
	mla ip, r11, r0, r1
	mov r11, ip, lsr #0x10
	mov r11, r11, lsl #0x10
	and r11, r2, r11, lsr #16
	rsb r11, r11, r2, lsr #1
	add r11, r11, #0x1000
	str ip, [r3]
	smull ip, r11, r10, r11
	adds ip, ip, #0x800
	adc r10, r11, #0
	mov r11, ip, lsr #0xc
	orr r11, r11, r10, lsl #20
	str r11, [r4, #0x40]
	ldr r10, [r9, #0x38]
	cmp r10, #0
	beq _02167D94
	ldr r10, [r3, #0]
	add r2, r2, #0x400
	mla r1, r10, r0, r1
	mov r0, r1, lsr #0x10
	str r1, [r3]
	mov r0, r0, lsl #0x10
	and r0, r2, r0, lsr #16
	ldr r1, =0x00001BFF
	ldr r2, [r4, #0x38]
	sub r0, r1, r0
	smull r10, r3, r2, r0
	adds r2, r10, #0x800
	adc r1, r3, #0
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #20
	str r2, [r4, #0x38]
	ldr r1, [r4, #0x40]
	smull r3, r2, r1, r0
	mov r0, #0x800
	adds r1, r3, r0
	mov r0, #0
	adc r0, r2, r0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #20
	str r1, [r4, #0x40]
_02167D94:
	cmp r6, #0
	beq _02167DB0
	mov r0, #0
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	b _02167DC4
_02167DB0:
	mov r1, #0
	mov r0, #0x1000
	str r1, [sp, #8]
	str r0, [sp, #0xc]
	str r1, [sp, #0x10]
_02167DC4:
	add r1, sp, #8
	mov r0, r4
	bl SailObject__Func_2165AF4
	mov r0, r4
	add r1, r5, #0x28
	mov r2, #0
	bl SailObject__SetupHitbox
	ldr r0, [r9, #0x38]
	cmp r0, #0
	bne _02167DF8
	mov r0, r4
	mov r1, #0
	bl SailObject__Func_21658A4
_02167DF8:
	mov r2, r7, lsl #0xd
	mov r0, #0x800
	mov r1, #0
	adds r0, r0, r8, lsl #13
	orr r2, r2, r8, lsr #19
	adc r6, r2, #0
	mov r2, r0, lsr #0xc
	mov r0, r4
	mov r3, r1
	orr r2, r2, r6, lsl #20
	bl SailObject__Func_21658D0
	mov r10, #0x28000
	umull r0, r6, r10, r8
	adds r0, r0, #0x800
	mov r9, r0, lsr #0xc
	mov r3, #0x12c
	umull r2, r1, r3, r8
	ldr r11, [r4, #0x18]
	mla r6, r10, r7, r6
	mov r0, r10, asr #0x1f
	mla r6, r0, r8, r6
	adc r0, r6, #0
	orr r9, r9, r0, lsl #20
	bic r11, r11, #2
	str r11, [r4, #0x18]
	str r9, [r5, #0x120]
	mla r1, r3, r7, r1
	mov r0, r3, asr #0x1f
	mla r1, r0, r8, r1
	adds r2, r2, #0x800
	adc r0, r1, #0
	mov r1, r2, lsr #0xc
	str r9, [r5, #0x11c]
	orr r1, r1, r0, lsl #20
	str r1, [r5, #0x118]
	b _02168230
_02167E88:
	ldr r0, [r5, #0x164]
	ldr r3, =_obj_disp_rand
	ldr r0, [r0, #0x34]
	ldr r11, [r3, #0]
	ands r0, r0, #7
	mulne r0, r8, r0
	movne r8, r0
	smull r10, r6, r7, r8
	adds r7, r10, #0x800
	ldr r1, =0x00196225
	ldr r2, =0x3C6EF35F
	ldr r0, =0x000001FE
	mla r9, r11, r1, r2
	mov r10, r9, lsr #0x10
	mov r10, r10, lsl #0x10
	and r10, r0, r10, lsr #16
	rsb r10, r10, #0xff
	adc r6, r6, #0
	mov r7, r7, lsr #0xc
	orr r7, r7, r6, lsl #20
	add r6, r10, #0x800
	smull r10, r6, r7, r6
	adds r10, r10, #0x800
	adc r6, r6, #0
	mov r10, r10, lsr #0xc
	str r9, [r3]
	orr r10, r10, r6, lsl #20
	str r10, [r4, #0x3c]
	ldr r9, [r3, #0]
	add r10, r0, #0x200
	mla r6, r9, r1, r2
	mov r9, r6, lsr #0x10
	mov r9, r9, lsl #0x10
	and r10, r10, r9, lsr #16
	add r9, r0, #1
	sub r9, r9, r10
	add r9, r9, #0x800
	smull r10, r9, r7, r9
	adds r10, r10, #0x800
	str r6, [r3]
	add r6, r0, #0x200
	adc r9, r9, #0
	mov r10, r10, lsr #0xc
	orr r10, r10, r9, lsl #20
	str r10, [r4, #0x38]
	ldr r9, [r3, #0]
	add r0, r0, #1
	mla r1, r9, r1, r2
	mov r2, r1, lsr #0x10
	mov r2, r2, lsl #0x10
	and r2, r6, r2, lsr #16
	sub r0, r0, r2
	add r0, r0, #0x800
	smull r2, r0, r7, r0
	adds r2, r2, #0x800
	adc r0, r0, #0
	mov r2, r2, lsr #0xc
	str r1, [r3]
	orr r2, r2, r0, lsl #20
	str r2, [r4, #0x40]
	ldr r0, [r5, #0x164]
	mov r6, r8, asr #0x1f
	ldrh r0, [r0, #0x30]
	mov r2, #0
	cmp r0, #0x1a
	bne _02168230
	mov r0, r4
	add r1, r5, #0x28
	bl SailObject__SetupHitbox
	mov r2, r6, lsl #0xc
	mov r0, #0x800
	mov r1, #0
	adds r0, r0, r8, lsl #12
	orr r2, r2, r8, lsr #20
	adc r7, r2, #0
	mov r2, r0, lsr #0xc
	mov r0, r4
	mov r3, r1
	orr r2, r2, r7, lsl #20
	bl SailObject__Func_21658D0
	ldr r1, [r4, #0x18]
	mov r0, r4
	bic r1, r1, #2
	str r1, [r4, #0x18]
	mov r1, #0x40000
	str r1, [r5, #0x98]
	mov r1, #0
	bl StageTask__GetCollider
	ldrh r2, [r0, #0x32]
	mov r3, #0x28000
	mov r1, #0x14
	orr r2, r2, #4
	strh r2, [r0, #0x32]
	strh r1, [r0, #0x2c]
	umull r0, r1, r3, r8
	adds r0, r0, #0x800
	mov r2, r0, lsr #0xc
	mla r1, r3, r6, r1
	mov r0, r3, asr #0x1f
	mla r1, r0, r8, r1
	adc r0, r1, #0
	orr r2, r2, r0, lsl #20
	str r2, [r5, #0x120]
	mov r3, #0x12c
	str r2, [r5, #0x11c]
	umull r2, r1, r3, r8
	mla r1, r3, r6, r1
	mov r0, r3, asr #0x1f
	mla r1, r0, r8, r1
	adds r2, r2, #0x800
	adc r0, r1, #0
	mov r1, r2, lsr #0xc
	orr r1, r1, r0, lsl #20
	str r1, [r5, #0x118]
	b _02168230
_02168054:
	ldr r5, =_obj_disp_rand
	mov r3, #0x800
	ldr r10, [r5, #0]
	ldr r0, =0x00196225
	ldr r1, =0x3C6EF35F
	ldr r2, =0x00000FFE
	mla r8, r10, r0, r1
	mov r10, r8, lsr #0x10
	mov r10, r10, lsl #0x10
	and r10, r2, r10, lsr #16
	rsb r10, r10, r2, lsr #1
	add r10, r10, #0x1000
	smull r11, r10, r7, r10
	adds r11, r11, #0x800
	adc r10, r10, #0
	mov r11, r11, lsr #0xc
	str r8, [r5]
	orr r11, r11, r10, lsl #20
	str r11, [r4, #0x38]
	ldr r10, [r5, #0]
	sub r11, r3, #2
	mla r8, r10, r0, r1
	mov r10, r8, lsr #0x10
	mov r10, r10, lsl #0x10
	and r10, r11, r10, lsr #16
	rsb r10, r10, r2, lsr #2
	add r10, r10, #0x800
	smull r11, r10, r7, r10
	adds r11, r11, #0x800
	adc r10, r10, #0
	mov r11, r11, lsr #0xc
	str r8, [r5]
	orr r11, r11, r10, lsl #20
	str r11, [r4, #0x3c]
	ldr r8, [r5, #0]
	sub r3, r3, #1
	mla r0, r8, r0, r1
	mov r1, r0, lsr #0x10
	mov r1, r1, lsl #0x10
	and r1, r2, r1, lsr #16
	sub r1, r3, r1
	add r1, r1, #0x1000
	smull r2, r1, r7, r1
	adds r2, r2, #0x800
	adc r1, r1, #0
	mov r2, r2, lsr #0xc
	str r0, [r5]
	orr r2, r2, r1, lsl #20
	mov r0, r4
	str r2, [r4, #0x40]
	mov r1, #5
	bl SailObject__SetLightColors
	ldr r0, [r9, #0x38]
	cmp r0, #0
	beq _021681F4
	mov r8, r5
	ldr r0, [r8, #0]
	ldr r3, =0x00196225
	ldr r5, =0x3C6EF35F
	ldr r1, =0x000003FE
	mla r2, r0, r3, r5
	mov r0, r2, lsr #0x10
	str r2, [r8]
	mov r0, r0, lsl #0x10
	and r0, r1, r0, lsr #16
	ldr r2, =0x00001BFF
	ldr r1, [r4, #0x38]
	sub r0, r2, r0
	smull r9, r2, r1, r0
	adds r9, r9, #0x800
	adc r1, r2, #0
	mov r2, r9, lsr #0xc
	orr r2, r2, r1, lsl #20
	str r2, [r4, #0x38]
	mov r7, #0x800
	ldr r2, [r4, #0x3c]
	sub r1, r7, #1
	smull r9, r7, r2, r0
	adds r9, r9, #0x800
	adc r2, r7, #0
	mov r7, r9, lsr #0xc
	orr r7, r7, r2, lsl #20
	str r7, [r4, #0x3c]
	ldr r2, [r4, #0x40]
	smull r7, r0, r2, r0
	adds r2, r7, #0x800
	adc r0, r0, #0
	mov r2, r2, lsr #0xc
	orr r2, r2, r0, lsl #20
	str r2, [r4, #0x40]
	ldr r0, [r8, #0]
	mla r2, r0, r3, r5
	mov r0, r2, lsr #0x10
	mov r0, r0, lsl #0x10
	and r0, r1, r0, lsr #16
	str r2, [r8]
	ldr r1, [r4, #0x3c]
	add r0, r0, #0x1400
	smull r2, r0, r1, r0
	adds r1, r2, #0x800
	adc r0, r0, #0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #20
	str r1, [r4, #0x3c]
_021681F4:
	cmp r6, #0
	beq _02168210
	mov r0, #0
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	b _02168224
_02168210:
	mov r1, #0
	mov r0, #0x1000
	str r1, [sp, #8]
	str r0, [sp, #0xc]
	str r1, [sp, #0x10]
_02168224:
	add r1, sp, #8
	mov r0, r4
	bl SailObject__Func_2165AF4
_02168230:
	ldr r3, =_obj_disp_rand
	ldr r1, =0x00196225
	ldr r5, [r3, #0]
	ldr r2, =0x3C6EF35F
	mov r0, r4
	mla r1, r5, r1, r2
	str r1, [r3]
	mov r1, r1, lsr #0x10
	strh r1, [r4, #0x32]
	bl SailObject__ApplyRotation
	mov r0, r4
	bl StageTask__InitSeqPlayer
	mov r0, r4
	add sp, sp, #0x14
	ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}

// clang-format on
#endif
}

NONMATCH_FUNC StageTask *SailStone__CreateFromSegment(SailVoyageSegment *voyageSegment, s32 a2)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
	sub sp, sp, #0xc
	mov r7, r0
	mov r6, r1
	bl SailManager__GetWork
	ldr r4, [r0, #0xa0]
	bl SailManager__GetWork
	add r2, sp, #0
	mov r1, #0
	mov r5, r0
	str r1, [r2]
	str r1, [r2, #4]
	str r1, [r2, #8]
	bl SailManager__GetShipType
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	cmp r0, #3
	addls pc, pc, r0, lsl #2
	b _021682F0
_021682E0: // jump table
	b _021682F0 // case 0
	b _0216838C // case 1
	b _021682F0 // case 2
	b _0216862C // case 3
_021682F0:
	ldr r1, =_obj_disp_rand
	ldr r2, =0x00196225
	ldr r8, [r1, #0]
	ldr r3, =0x3C6EF35F
	ldr r5, =0x0218B9AC
	mla r10, r8, r2, r3
	mla r9, r10, r2, r3
	mov r10, r10, lsr #0x10
	mla r2, r9, r2, r3
	mov r8, r0, lsl #1
	ldr r0, =0x0218B9B4
	mov r3, r10, lsl #0x10
	mov r9, r9, lsr #0x10
	mov r3, r3, lsr #0x10
	mov r9, r9, lsl #0x10
	and r3, r3, #0xff
	mov r10, r9, lsr #0x10
	mov r9, r2, lsr #0x10
	mov r9, r9, lsl #0x10
	ldrh r5, [r5, r8]
	add r11, r3, #0x58
	ldrh r3, [r0, r8]
	and r0, r10, #0xf
	mul r8, r5, r11
	mul r5, r3, r0
	mov r0, r7
	str r8, [sp]
	str r5, [sp, #4]
	str r2, [r1]
	mov r5, r9, lsr #0x10
	bl SailVoyageManager__GetSegmentSize
	mov r1, r5, lsl #0x12
	ldr r2, [r7, #0x24]
	mov r1, r1, lsr #0xe
	add r2, r2, r0
	add r0, r1, #0x10000
	sub r0, r2, r0
	str r0, [sp, #8]
	b _02168788
_0216838C:
	cmp r6, #1
	beq _0216845C
	cmp r6, #2
	ldrsh r8, [r7, #0xa]
	mov r5, #0xb
	beq _02168538
	cmp r8, #0
	rsblt r8, r8, #0
	mov r3, #0
	umull r9, r2, r8, r5
	mla r2, r8, r3, r2
	adds r3, r9, #0x800
	mov r8, r8, asr #0x1f
	mla r2, r8, r5, r2
	ldr r1, =_obj_disp_rand
	mov r5, #0x800
	ldr r10, [r1, #0]
	ldr r8, =0x00196225
	ldr r9, =0x3C6EF35F
	ldr r11, =0x0218B9AC
	mov r0, r0, lsl #1
	ldrh r0, [r11, r0]
	mla r11, r10, r8, r9
	adc r2, r2, #0
	mov r3, r3, lsr #0xc
	orr r3, r3, r2, lsl #20
	mla r2, r11, r8, r9
	add r3, r3, #0x10
	mov r8, r2, lsr #0x10
	mul r0, r3, r0
	mov r9, r11, lsr #0x10
	mov r3, r9, lsl #0x10
	sub r5, r5, #1
	and r3, r5, r3, lsr #16
	add r3, r3, #0x800
	smull r5, r3, r0, r3
	adds r5, r5, #0x800
	adc r0, r3, #0
	mov r3, r5, lsr #0xc
	orr r3, r3, r0, lsl #20
	mov r8, r8, lsl #0x10
	mov r0, r7
	str r3, [sp]
	str r2, [r1]
	mov r5, r8, lsr #0x10
	bl SailVoyageManager__GetSegmentSize
	ldr r2, [r7, #0x24]
	mov r1, r5, lsl #0x10
	add r0, r2, r0
	sub r0, r0, r1, lsr #16
	str r0, [sp, #8]
	b _02168788
_0216845C:
	ldr r1, =_obj_disp_rand
	ldr r3, =0x00196225
	ldr r2, [r1, #0]
	ldr r10, =0x3C6EF35F
	ldr r11, =0x0218B9AC
	mla r9, r2, r3, r10
	mla r8, r9, r3, r10
	mla r2, r8, r3, r10
	mla r3, r2, r3, r10
	str r9, [r1]
	mov ip, r9, lsr #0x10
	ldrh r9, [r5, #0x58]
	mov r10, r0, lsl #1
	mov r0, ip, lsl #0x10
	mov lr, r8, lsr #0x10
	mov r8, r0, lsr #0x10
	str r3, [r1]
	mov ip, r2, lsr #0x10
	ldr r0, =0x00007FFE
	mov r1, lr, lsl #0x10
	mov r2, r3, lsr #0x10
	and r3, r0, r1, lsr #16
	ldrh r1, [r11, r10]
	mov r9, r9, lsl #0x1e
	and r8, r8, #7
	add r8, r8, r9, lsr #27
	rsb r0, r3, r0, lsr #1
	mla r3, r1, r8, r0
	mov r0, r7
	str r3, [sp]
	mov r8, ip, lsl #0x10
	mov r9, r2, lsl #0x10
	bl SailVoyageManager__GetSegmentSize
	ldr r3, [r7, #0x24]
	ldr r1, =0x00003FFF
	add r0, r3, r0
	ldrh r10, [r5, #0x58]
	add r2, r1, #0x4000
	sub r0, r0, #0x16000
	mov r3, r10, asr #2
	add r3, r0, r3, lsl #16
	and r0, r2, r8, lsr #16
	and r1, r1, r9, lsr #16
	add r0, r3, r0
	add r0, r1, r0
	str r0, [sp, #8]
	ldrh r0, [r5, #0x58]
	tst r0, #1
	ldrne r0, [sp]
	rsbne r0, r0, #0
	strne r0, [sp]
	ldrh r0, [r5, #0x58]
	add r0, r0, #1
	strh r0, [r5, #0x58]
	b _02168788
_02168538:
	cmp r8, #0
	rsblt r8, r8, #0
	mov r3, #0
	umull r9, r2, r8, r5
	mla r2, r8, r3, r2
	adds r3, r9, #0x800
	mov r8, r8, asr #0x1f
	mla r2, r8, r5, r2
	ldr r1, =_obj_disp_rand
	mov r5, #0x800
	ldr r10, [r1, #0]
	ldr r8, =0x00196225
	ldr r9, =0x3C6EF35F
	ldr r11, =0x0218B9AC
	mov r0, r0, lsl #1
	ldrh r0, [r11, r0]
	mla r11, r10, r8, r9
	adc r2, r2, #0
	mov r3, r3, lsr #0xc
	orr r3, r3, r2, lsl #20
	mla r2, r11, r8, r9
	add r3, r3, #0x10
	mov r8, r2, lsr #0x10
	mul r0, r3, r0
	mov r9, r11, lsr #0x10
	mov r3, r9, lsl #0x10
	sub r5, r5, #1
	and r3, r5, r3, lsr #16
	add r3, r3, #0x800
	smull r5, r3, r0, r3
	adds r5, r5, #0x800
	adc r0, r3, #0
	mov r3, r5, lsr #0xc
	orr r3, r3, r0, lsl #20
	mov r8, r8, lsl #0x10
	mov r0, r7
	str r3, [sp]
	str r2, [r1]
	mov r5, r8, lsr #0x10
	bl SailVoyageManager__GetSegmentSize
	ldr r2, =_obj_disp_rand
	ldr r1, [r7, #0x24]
	ldr r3, [r2, #0]
	add r8, r1, r0
	ldr r0, =0x00196225
	ldr r1, =0x3C6EF35F
	sub r8, r8, #0x10000
	mla r1, r3, r0, r1
	mov r0, r1, lsr #0x10
	mov r3, r5, lsl #0x12
	mov r0, r0, lsl #0x10
	sub r3, r8, r3, lsr #13
	mov r0, r0, lsr #0x10
	str r3, [sp, #8]
	str r1, [r2]
	tst r0, #1
	beq _02168788
	ldr r0, [sp]
	rsb r0, r0, #0
	str r0, [sp]
	b _02168788
_0216862C:
	cmp r6, #1
	beq _021686AC
	ldr r1, =_obj_disp_rand
	mov r2, #0
	ldr r10, [r1, #0]
	ldr r8, =0x00196225
	ldr r9, =0x3C6EF35F
	ldr r3, =0x0218B9AC
	mla r5, r10, r8, r9
	mov r10, r5, lsr #0x10
	mov r0, r0, lsl #1
	mla r8, r5, r8, r9
	mov r5, r10, lsl #0x10
	mov r5, r5, lsr #0x10
	and r9, r5, #0xfe
	mov r5, r8, lsr #0x10
	mov r5, r5, lsl #0x10
	ldrh r10, [r3, r0]
	rsb r3, r9, #0x7f
	mov r0, r7
	mul r3, r10, r3
	str r3, [sp]
	str r2, [sp, #4]
	str r8, [r1]
	mov r5, r5, lsr #0x10
	bl SailVoyageManager__GetSegmentSize
	ldr r2, [r7, #0x24]
	mov r1, r5, lsl #0x11
	add r0, r2, r0
	sub r0, r0, r1, lsr #13
	str r0, [sp, #8]
	b _02168788
_021686AC:
	ldr r1, =_obj_disp_rand
	ldr r3, =0x00196225
	ldr r2, [r1, #0]
	ldr r11, =0x3C6EF35F
	mov ip, r0, lsl #1
	mla r10, r2, r3, r11
	mla r9, r10, r3, r11
	mla r2, r9, r3, r11
	mla r3, r2, r3, r11
	str r10, [r1]
	ldrh r8, [r5, #0x58]
	mov r10, r10, lsr #0x10
	mov r0, r10, lsl #0x10
	and r11, r8, #3
	mov r8, r2, lsr #0x10
	mov r10, r0, lsr #0x10
	ldr lr, =0x0218B9AC
	mov r9, r9, lsr #0x10
	str r3, [r1]
	mov r1, r9, lsl #0x10
	ldr r0, =0x00007FFE
	mov r2, r3, lsr #0x10
	and r3, r0, r1, lsr #16
	ldrh r1, [lr, ip]
	rsb r11, r11, r11, lsl #5
	and r9, r10, #7
	add r9, r11, r9
	rsb r0, r3, r0, lsr #1
	mla r3, r1, r9, r0
	mov r0, r7
	str r3, [sp]
	mov r8, r8, lsl #0x10
	mov r9, r2, lsl #0x10
	bl SailVoyageManager__GetSegmentSize
	ldr r3, [r7, #0x24]
	ldr r1, =0x00003FFF
	add r0, r3, r0
	ldrh r10, [r5, #0x58]
	add r2, r1, #0x4000
	sub r0, r0, #0x16000
	mov r3, r10, asr #2
	add r3, r0, r3, lsl #16
	and r0, r2, r8, lsr #16
	and r1, r1, r9, lsr #16
	add r0, r3, r0
	add r0, r1, r0
	str r0, [sp, #8]
	ldrh r0, [r5, #0x58]
	tst r0, #1
	ldrne r0, [sp]
	rsbne r0, r0, #0
	strne r0, [sp]
	ldrh r0, [r5, #0x58]
	add r0, r0, #1
	strh r0, [r5, #0x58]
_02168788:
	ldrsh r0, [r7, #0xa]
	cmp r0, #0
	ldrgt r0, [sp]
	rsbgt r0, r0, #0
	strgt r0, [sp]
	ldrsh r0, [r7, #0xa]
	cmp r0, #0
	bne _021687DC
	ldr r2, =_obj_disp_rand
	ldr r0, =0x00196225
	ldr r3, [r2, #0]
	ldr r1, =0x3C6EF35F
	mla r1, r3, r0, r1
	mov r0, r1, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	tst r0, #1
	ldrne r0, [sp]
	str r1, [r2]
	rsbne r0, r0, #0
	strne r0, [sp]
_021687DC:
	add r1, sp, #0
	mov r0, #0x21
	bl SailEventManager__CreateObject
	mov r1, r0
	cmp r6, #1
	moveq r0, #1
	streq r0, [r1, #0x38]
	mov r0, r4
	bl NNS_FndAppendListObject
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}

// clang-format on
#endif
}

StageTask *SailIce__Create(SailEventManagerObject *mapObject)
{
    StageTask *work;
    SailObject *worker;
    fx32 scale;
    u16 radius;
    u16 anim;

    anim   = 1;
    radius = 96;

    work = CreateStageTaskSimple();
    StageTask__SetType(work, SAILSTAGE_OBJ_TYPE_OBJECT);

    worker = StageTask__AllocateWorker(work, sizeof(SailObject));

    if (SailManager__GetShipType() == SHIP_BOAT)
        radius = 12;

    if (MATH_ABS(mapObject->unknown.x) > radius * _0218B9AC[SailManager__GetShipType()])
    {
        anim = ObjDispRandRepeat(2);
    }

    ObjAction3dNNModelLoad(work, NULL, "sb_ice.nsbmd", anim, GetObjectFileWork(OBJDATAWORK_33), SailManager__GetArchive());
    SailObject__InitCommon(work);
    SailObject__InitFromMapObject(work, mapObject);

    work->flag |= STAGE_TASK_FLAG_NO_OBJ_COLLISION;
    work->userFlag |= SAILOBJECT_FLAG_40000 | SAILOBJECT_FLAG_80000;

    scale = work->scale.x;
    if (SailManager__GetShipType() != SHIP_BOAT)
    {
        if (MATH_ABS(mapObject->unknown.x) > 96 * _0218B9AC[SailManager__GetShipType()])
        {
            work->scale.x = MultiplyFX(scale, 0xD00 + ObjDispRandRange4(0x100, 0x300));
            work->scale.y = MultiplyFX(scale, 0xD00 + ObjDispRandRange4(0x100, 0x300));
            work->scale.z = MultiplyFX(scale, 0xD00 + ObjDispRandRange4(0x100, 0x300));
        }
        else
        {
            work->scale.x = MultiplyFX(scale, 0x1100 + ObjDispRandRange4(0x100, 0x300));
            work->scale.y = MultiplyFX(scale, 0x400);
            work->scale.z = MultiplyFX(scale, 0x1100 + ObjDispRandRange4(0x100, 0x300));
        }
    }
    else
    {
        work->scale.x = MultiplyFX(scale, 0xB00 + ObjDispRandRange4(0x100, 0x300));
        work->scale.y = MultiplyFX(scale, 0x580 + ObjDispRandRange4(0x100, 0x300));
        work->scale.z = MultiplyFX(scale, 0xB00 + ObjDispRandRange4(0x100, 0x300));

        if (anim == 0)
        {
            work->scale.y = MultiplyFX(scale, 0x800 + ObjDispRandRange4(0x100, 0x300));
        }
        else
        {
            VecFx32 pos;
            pos.x = FLOAT_TO_FX32(0.0);
            pos.y = -FLOAT_TO_FX32(1.0);
            pos.z = FLOAT_TO_FX32(0.0);

            SailObject__Func_2165AF4(work, &pos);
        }

        SailObject__SetupHitbox(work, worker->collider, 0);
        SailObject__Func_21658A4(work, 0);
        SailObject__Func_21658D0(work, 0, 0x4200, 0);
        work->flag &= ~STAGE_TASK_FLAG_NO_OBJ_COLLISION;
        worker->field_120 = FLOAT_TO_FX32(100.0);
        worker->health    = FLOAT_TO_FX32(100.0);
        worker->dword118  = 500;
    }

    work->dir.y = ObjDispRand();

    SailObject__ApplyRotation(work);
    StageTask__InitSeqPlayer(work);

    SetTaskState(work, SailObject__Func_2166D50);

    return work;
}

NONMATCH_FUNC StageTask *SailIce__CreateFromSegment(SailVoyageSegment *voyageSegment, s32 a2)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
	sub sp, sp, #0xc
	mov r8, r0
	mov r7, r1
	bl SailManager__GetWork
	ldr r4, [r0, #0xa0]
	add r1, sp, #0
	mov r0, #0
	str r0, [r1]
	str r0, [r1, #4]
	str r0, [r1, #8]
	bl SailManager__GetShipType
	mov r0, r0, lsl #0x10
	mov r5, r0, lsr #0x10
	bl SailManager__GetWork
	mov r6, r0
	cmp r5, #0
	beq _02168CD4
	cmp r5, #1
	beq _02168E18
	cmp r5, #2
_02168CD4:
	cmp r7, #0
	ldr r9, =0x3C6EF35F
	beq _02168DA0
	ldr r3, =_obj_disp_rand
	ldr r2, =0x00196225
	ldr r0, [r3, #0]
	ldr r1, =0x0218B9AC
	mla r11, r0, r2, r9
	mla r10, r11, r2, r9
	str r11, [r3]
	mla r9, r10, r2, r9
	ldrh r0, [r6, #0x58]
	mov r2, r5, lsl #1
	mov r11, r11, lsr #0x10
	mov r5, r11, lsl #0x10
	mov r11, r5, lsr #0x10
	ldrh r1, [r1, r2]
	mov r2, r0, lsl #0x1e
	and r0, r11, #0x3f
	add r0, r0, r2, lsr #24
	mul r2, r1, r0
	mov r5, r9, lsr #0x10
	mov r10, r10, lsr #0x10
	str r9, [r3]
	mov r0, r8
	str r2, [sp]
	mov r9, r10, lsl #0x10
	mov r5, r5, lsl #0x10
	bl SailVoyageManager__GetSegmentSize
	ldr r3, [r8, #0x24]
	ldr r1, =0x00001FFF
	add r0, r3, r0
	ldrh r10, [r6, #0x58]
	add r2, r1, #0x2000
	sub r0, r0, #0x16000
	mov r3, r10, asr #2
	add r3, r0, r3, lsl #15
	and r0, r2, r9, lsr #16
	and r1, r1, r5, lsr #16
	add r0, r3, r0
	add r0, r1, r0
	str r0, [sp, #8]
	ldrh r0, [r6, #0x58]
	tst r0, #1
	ldrne r0, [sp]
	rsbne r0, r0, #0
	strne r0, [sp]
	ldrh r0, [r6, #0x58]
	add r0, r0, #1
	strh r0, [r6, #0x58]
	b _02168E0C
_02168DA0:
	ldr r10, =_obj_disp_rand
	ldr r6, =0x00196225
	ldr r1, [r10, #0]
	ldr r0, =0x0218B9AC
	mla r2, r1, r6, r9
	mov r3, r2, lsr #0x10
	mov r1, r5, lsl #1
	mla r5, r2, r6, r9
	mov r3, r3, lsl #0x10
	mov r2, r3, lsr #0x10
	ldrh r6, [r0, r1]
	and r3, r2, #0x7f
	add r1, r3, #0x60
	mul r1, r6, r1
	mov r2, r5, lsr #0x10
	mov r2, r2, lsl #0x10
	str r5, [r10]
	mov r0, r8
	str r1, [sp]
	mov r5, r2, lsr #0x10
	bl SailVoyageManager__GetSegmentSize
	ldr r2, [r8, #0x24]
	mov r1, r5, lsl #0x12
	add r0, r2, r0
	sub r0, r0, #0x10000
	sub r0, r0, r1, lsr #13
	str r0, [sp, #8]
_02168E0C:
	mov r0, #0
	str r0, [sp, #4]
	b _02168FB8
_02168E18:
	cmp r7, #0
	ldr r10, =0x3C6EF35F
	beq _02168EFC
	ldr r1, =_obj_disp_rand
	ldr r3, =0x00196225
	ldr r0, [r1, #0]
	ldr r11, =0x0218B9AC
	mla r9, r0, r3, r10
	mla r2, r9, r3, r10
	mla r0, r2, r3, r10
	mla r3, r0, r3, r10
	str r9, [r1]
	mov ip, r9, lsr #0x10
	ldrh r9, [r6, #0x58]
	mov r10, r5, lsl #1
	mov r5, ip, lsl #0x10
	mov ip, r2, lsr #0x10
	mov lr, r5, lsr #0x10
	mov r5, r0, lsr #0x10
	str r3, [r1]
	ldr r0, =0x00007FFE
	mov r1, ip, lsl #0x10
	mov r2, r3, lsr #0x10
	and r3, r0, r1, lsr #16
	ldrh r1, [r11, r10]
	mov r10, r9, lsl #0x1e
	and r9, lr, #7
	add r9, r9, r10, lsr #27
	rsb r0, r3, r0, lsr #1
	mla r3, r1, r9, r0
	mov r0, r8
	str r3, [sp]
	mov r5, r5, lsl #0x10
	mov r9, r2, lsl #0x10
	bl SailVoyageManager__GetSegmentSize
	ldr r3, [r8, #0x24]
	ldr r1, =0x00003FFF
	add r0, r3, r0
	ldrh r10, [r6, #0x58]
	add r2, r1, #0x4000
	sub r0, r0, #0x16000
	mov r3, r10, asr #2
	add r3, r0, r3, lsl #16
	and r0, r2, r5, lsr #16
	and r1, r1, r9, lsr #16
	add r0, r3, r0
	add r0, r1, r0
	str r0, [sp, #8]
	ldrh r0, [r6, #0x58]
	tst r0, #1
	ldrne r0, [sp]
	rsbne r0, r0, #0
	strne r0, [sp]
	ldrh r0, [r6, #0x58]
	add r0, r0, #1
	strh r0, [r6, #0x58]
	b _02168FB8
_02168EFC:
	ldrsh r6, [r8, #0xa]
	ldr r1, =_obj_disp_rand
	mov r3, #0xb
	cmp r6, #0
	rsblt r6, r6, #0
	mov r2, #0
	umull r9, r0, r6, r3
	mla r0, r6, r2, r0
	adds r2, r9, #0x800
	mov r6, r6, asr #0x1f
	mla r0, r6, r3, r0
	ldr r11, [r1, #0]
	ldr r9, =0x00196225
	adc r0, r0, #0
	mov r2, r2, lsr #0xc
	orr r2, r2, r0, lsl #20
	mov r0, r5, lsl #1
	ldr ip, =0x0218B9AC
	mla r5, r11, r9, r10
	add r3, r2, #0x10
	mla r2, r5, r9, r10
	ldrh r0, [ip, r0]
	mov r10, r5, lsr #0x10
	mov r5, r2, lsr #0x10
	mul r0, r3, r0
	mov r6, #0x800
	mov r9, r5, lsl #0x10
	mov r3, r10, lsl #0x10
	sub r5, r6, #1
	and r3, r5, r3, lsr #16
	add r3, r3, #0x800
	smull r5, r3, r0, r3
	adds r5, r5, #0x800
	adc r0, r3, #0
	mov r3, r5, lsr #0xc
	orr r3, r3, r0, lsl #20
	mov r0, r8
	str r3, [sp]
	str r2, [r1]
	mov r5, r9, lsr #0x10
	bl SailVoyageManager__GetSegmentSize
	ldr r2, [r8, #0x24]
	mov r1, r5, lsl #0x12
	add r0, r2, r0
	sub r0, r0, #0x10000
	sub r0, r0, r1, lsr #13
	str r0, [sp, #8]
_02168FB8:
	ldrsh r0, [r8, #0xa]
	cmp r0, #0
	ldrgt r0, [sp]
	rsbgt r0, r0, #0
	strgt r0, [sp]
	cmp r7, #0
	ldreqsh r0, [r8, #0xa]
	cmpeq r0, #0
	bne _02169010
	ldr r2, =_obj_disp_rand
	ldr r0, =0x00196225
	ldr r3, [r2, #0]
	ldr r1, =0x3C6EF35F
	mla r1, r3, r0, r1
	mov r0, r1, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	tst r0, #1
	ldrne r0, [sp]
	str r1, [r2]
	rsbne r0, r0, #0
	strne r0, [sp]
_02169010:
	add r1, sp, #0
	mov r0, #0x22
	bl SailEventManager__CreateObject
	mov r1, r0
	mov r0, r4
	bl NNS_FndAppendListObject
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}

// clang-format on
#endif
}

StageTask *SailSubFish__Create(SailEventManagerObject *mapObject)
{
    StageTask *work;
    SailObject *worker;

    work = CreateStageTaskSimple();
    StageTask__SetType(work, SAILSTAGE_OBJ_TYPE_OBJECT);

    worker = StageTask__AllocateWorker(work, sizeof(SailObject));
    UNUSED(worker);

    s32 anim = ObjDispRandRepeat(8) + ObjDispRandRepeat(2);
    ObjAction3dNNModelLoad(work, NULL, "sb_sub_fish.nsbmd", (u16)anim, GetObjectDataWork(OBJDATAWORK_34), SailManager__GetArchive());
    SailObject__InitCommon(work);
    SailObject__InitFromMapObject(work, mapObject);
    work->flag |= STAGE_TASK_FLAG_NO_OBJ_COLLISION;

    fx32 scale    = work->scale.x;
    scale         = MultiplyFX(scale, FLOAT_TO_FX32(0.5) + ObjDispRandRange(-0x100, 0x100));
    work->scale.x = scale;
    work->scale.y = scale;
    work->scale.z = scale;

    SailSubFish__SetupObject(work);

    return work;
}

StageTask *SailSubFish2__Create(StageTask *parent)
{
    StageTask *work;
    SailObject *worker;

    work = CreateStageTaskSimple();
    StageTask__SetType(work, SAILSTAGE_OBJ_TYPE_OBJECT);

    worker = StageTask__AllocateWorker(work, sizeof(SailObject));
    UNUSED(worker);

    s32 anim = ObjDispRandRepeat(8) + ObjDispRandRepeat(2);
    ObjAction3dNNModelLoad(work, NULL, "sb_sub_fish.nsbmd", (u16)anim, GetObjectDataWork(OBJDATAWORK_34), SailManager__GetArchive());
    SailObject__InitCommon(work);
    StageTask__SetParent(work, parent, 0);
    work->flag |= STAGE_TASK_FLAG_DISABLE_VIEWCHECK_EVENT | STAGE_TASK_FLAG_NO_OBJ_COLLISION;
    work->moveFlag |= STAGE_TASK_MOVE_FLAG_DISABLE_MOVE_EVENT;

    OBS_ACTION3D_NN_WORK *animator = work->obj_3d;
    fx32 scale                     = animator->ani.work.scale.x;
    scale                          = MultiplyFX(scale, ObjDispRandRange2(FLOAT_TO_FX32(0.75), FLOAT_TO_FX32(0.875)));
    animator->ani.work.scale.z = animator->ani.work.scale.y = animator->ani.work.scale.x = scale;

    SailSubFish2__SetupObject(work);

    return work;
}

void SailSubFish__CreateUnknown1(SailVoyageSegment *voyageSegment)
{
    SailEventManager *eventManager = SailManager__GetWork()->eventManager;

    VecFx32 position = { 0 };

    u16 shipType = SailManager__GetShipType();

    position.x = _0218B9AC[shipType] * ObjDispRandRange(-128, 128);
    position.y = _0218B9B4[shipType] * ObjDispRandRange3(15, 64);
    position.z = voyageSegment->field_24 + SailVoyageManager__GetSegmentSize(voyageSegment) - ((u16)(2 * ObjDispRand()) * 8);

    if (voyageSegment->targetSeaAngle > 0)
    {
        position.x = -position.x;
    }

    if (voyageSegment->targetSeaAngle == 0)
    {
        if (ObjDispRandRepeat(2) != 0)
            position.x = -position.x;
    }

    NNS_FndAppendListObject(&eventManager->stageObjectList, SailEventManager__CreateObject(SAILMAPOBJECT_36, &position));
}

void SailSubFish__CreateUnknown2(StageTask *parent)
{
    u16 i;
    u16 count;

    SailManager *manager = SailManager__GetWork();
    UNUSED(manager);

    count = ObjDispRandRange2(2, 10);
    for (i = 0; i < count; i++)
    {
        SailSubFish2__Create(parent);
    }
}

StageTask *SailChaosEmerald__Create(fx32 z)
{
    StageTask *work;
    SailObject *worker;

    SailManager *manager = SailManager__GetWork();

    work = CreateStageTaskSimple();
    StageTask__SetType(work, SAILSTAGE_OBJ_TYPE_EFFECT);

    worker = StageTask__AllocateWorker(work, sizeof(SailObject));

    ObjAction3dNNModelLoad(work, NULL, "sb_chaos.nsbmd", manager->rivalRaceID, GetObjectFileWork(OBJDATAWORK_102), SailManager__GetArchive());
    SailObject__InitCommon(work);

    work->flag |= STAGE_TASK_FLAG_DISABLE_VIEWCHECK_EVENT;
    worker->objectRadius.z = z;
    worker->objectRadius.y = -FLOAT_TO_FX32(1.953125);

    SailObject__Func_2166A2C(work);
    SailChaosEmerald__SetupObject(work);
    return work;
}

StageTask *SailGoal__Create(fx32 radius)
{
    StageTask *work;
    SailObject *worker;

    SailManager *manager = SailManager__GetWork();

    work = CreateStageTaskSimple();
    StageTask__SetType(work, SAILSTAGE_OBJ_TYPE_EFFECT);

    worker = StageTask__AllocateWorker(work, sizeof(SailObject));

    ObjAction3dNNModelLoad(work, NULL, "sb_goal.nsbmd", 0, GetObjectFileWork(OBJDATAWORK_46), SailManager__GetArchive());
    ObjAction3dNNMotionLoad(work, NULL, "sb_goal.nsbca", GetObjectFileWork(OBJDATAWORK_47), SailManager__GetArchive());
    AnimatorMDL__SetAnimation(&work->obj_3d->ani, 0, work->obj_3d->resources[B3D_RESOURCE_JOINT_ANIM], 0, 0);
    SailObject__SetAnimSpeed(work, FLOAT_TO_FX32(2.0));
    work->displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;
    work->obj_3d->ani.work.matrixOpIDs[0] = MATRIX_OP_SET_CAMERA_ROT_33;
    work->obj_3d->ani.work.matrixOpIDs[1] = MATRIX_OP_FLUSH_P_CAMERA3D;

    SailObject__InitCommon(work);
    work->flag |= STAGE_TASK_FLAG_DISABLE_VIEWCHECK_EVENT;

    worker->objectRadius.z = radius;
    switch (SailManager__GetShipType())
    {
        case SHIP_JET:
        case SHIP_HOVER:
        default:
            worker->objectRadius.y = -FLOAT_TO_FX32(1.953125);
            break;

        case SHIP_BOAT:
            worker->objectRadius.y = -FLOAT_TO_FX32(8.0);
            break;

        case SHIP_SUBMARINE:
            worker->objectRadius.y = -FLOAT_TO_FX32(22.0);
            break;
    }

    SailObject__Func_2166A2C(work);

    if (!manager->isRivalRace)
    {
        fx32 scale = MultiplyFX(work->scale.x, FLOAT_TO_FX32(2.0));

        work->scale.x = scale;
        work->scale.y = scale;
        work->scale.z = scale;
    }

    SailGoal__SetupObject(work);

    return work;
}

StageTask *SailGoalText__Create(u32 a1)
{
    StageTask *work;
    SailObject *worker;

    work = CreateStageTaskSimple();
    StageTask__SetType(work, SAILSTAGE_OBJ_TYPE_EFFECT);

    worker = StageTask__AllocateWorker(work, sizeof(SailObject));

    ObjObjectAction3dBACLoad(work, NULL, "/sb_cldm_goal.bac", OBJ_DATA_GFX_AUTO, OBJ_DATA_GFX_AUTO, GetObjectFileWork(OBJDATAWORK_49), SailManager__GetArchive());
    SailObject__InitCommon(work);
    work->obj_2dIn3d->ani.work.matrixOpIDs[0] = MATRIX_OP_SET_CAMERA_ROT_33;
    work->obj_2dIn3d->ani.work.matrixOpIDs[1] = MATRIX_OP_FLUSH_P_CAMERA3D;

    SailObject__InitCommon(work);
    work->flag |= STAGE_TASK_FLAG_DISABLE_VIEWCHECK_EVENT;
    worker->objectRadius.z = a1 - FLOAT_TO_FX32(1.0);
    work->userWork         = a1;

    switch (SailManager__GetShipType())
    {
        case SHIP_JET:
        case SHIP_HOVER:
        default:
            worker->objectRadius.y = -FLOAT_TO_FX32(1.953125);
            break;

        case SHIP_BOAT:
            worker->objectRadius.y = -FLOAT_TO_FX32(8.0);
            break;

        case SHIP_SUBMARINE:
            worker->objectRadius.y = -FLOAT_TO_FX32(22.0);
            break;
    }

    SailObject__Func_2166A2C(work);
    SailGoalText__SetupObject(work);

    return work;
}

StageTask *SailJetItem__Create(SailEventManagerObject *mapObject)
{
    StageTask *work;
    SailObject *worker;

    SailManager *manager = SailManager__GetWork();

    work = CreateStageTaskSimpleEx(TASK_PRIORITY_UPDATE_LIST_START + 0x1001, TASK_GROUP(1));
    StageTask__SetType(work, SAILSTAGE_OBJ_TYPE_OBJECT);

    worker = StageTask__AllocateWorker(work, sizeof(SailObject));

    ObjObjectAction3dBACLoad(work, NULL, "sb_item.bac", OBJ_DATA_GFX_AUTO, OBJ_DATA_GFX_AUTO, GetObjectFileWork(OBJDATAWORK_37), SailManager__GetArchive());
    SailObject__InitCommon(work);

    SailObject__InitFromMapObject(work, mapObject);

    work->position.y -= FLOAT_TO_FX32(1.0);
    work->userFlag |= SAILOBJECT_FLAG_10000;

    work->userWork = mapObject->viewRange;
    if (work->userWork > 16)
        work->userWork = 0;

    if (manager->missionType == MISSION_TYPE_REACH_GOAL && work->userWork <= 3)
        work->userWork = 11;

    StageTask__SetAnimation(work, (work->userWork >> 2) + 1);
    worker->dword118                          = 500;
    work->obj_2dIn3d->ani.work.matrixOpIDs[0] = MATRIX_OP_SET_CAMERA_ROT_43;
    work->obj_2dIn3d->ani.work.matrixOpIDs[1] = MATRIX_OP_FLUSH_P_CAMERA3D;

    SailObject__SetupHitbox(work, worker->collider, 0);
    SailObject__Func_21658D0(work, 0, 0x900, 0);

    OBS_RECT_WORK *collider = StageTask__GetCollider(work, 0);
    collider->hitPower      = 0;
    collider->defPower      = 0;

    if (SailManager__GetShipType() == SHIP_BOAT)
        worker->collider[0].hitCheck.field_24.x = FLOAT_TO_FX32(2.5);

    SailItem3__Create(work);
    StageTask__InitSeqPlayer(work);

    return work;
}

StageTask *SailItem3__Create(StageTask *parent)
{
    StageTask *work;
    SailObject *worker;

    work = CreateStageTaskSimpleEx(TASK_PRIORITY_UPDATE_LIST_START + 0x1001, TASK_GROUP(1));
    StageTask__SetType(work, SAILSTAGE_OBJ_TYPE_OBJECT);

    worker = StageTask__AllocateWorker(work, sizeof(SailObject));
    UNUSED(worker);

    ObjObjectAction3dBACLoad(work, NULL, "sb_item.bac", OBJ_DATA_GFX_AUTO, OBJ_DATA_GFX_AUTO, GetObjectFileWork(OBJDATAWORK_37), SailManager__GetArchive());
    SailObject__InitCommon(work);
    work->userFlag |= SAILOBJECT_FLAG_1;

    work->position = parent->position;
    StageTask__SetParent(work, parent, 1024);

    work->obj_2dIn3d->ani.work.matrixOpIDs[0] = MATRIX_OP_SET_CAMERA_ROT_43;
    work->obj_2dIn3d->ani.work.matrixOpIDs[1] = MATRIX_OP_FLUSH_P_CAMERA3D;

    if (SailManager__GetShipType() == SHIP_SUBMARINE)
    {
        work->scale.x = FLOAT_TO_FX32(0.15625);
        work->scale.y = FLOAT_TO_FX32(0.15625);
        work->scale.z = FLOAT_TO_FX32(0.15625);
    }

    return work;
}

StageTask *SailItemBonus__Create(StageTask *parent, u32 type)
{
    StageTask *work = CreateStageTaskSimple();
    StageTask__SetType(work, SAILSTAGE_OBJ_TYPE_EFFECT);

    ObjObjectAction3dBACLoad(work, NULL, "sb_logo_fix.bac", 1024, 16, GetObjectFileWork(OBJDATAWORK_41), SailManager__GetArchive());
    StageTask__SetAnimation(work, type + 4);
    SailObject__InitCommon(work);
    work->userFlag |= SAILOBJECT_FLAG_1;
    work->displayFlag |= DISPLAY_FLAG_USE_DEFAULT_CAMERA_CONFIG;

    VecFx32 worldPos = parent->position;
    worldPos.y       = -worldPos.y;

    int px;
    int py;
    NNS_G3dWorldPosToScrPos(&worldPos, &px, &py);
    work->position.x = FX32_FROM_WHOLE(px);
    work->position.y = FX32_FROM_WHOLE(py);

    work->scale.x = FLOAT_TO_FX32(1.0);
    work->scale.y = FLOAT_TO_FX32(1.0);
    work->scale.z = FLOAT_TO_FX32(1.0);
    work->position.y -= FLOAT_TO_FX32(20.0);
    work->velocity.y = -FLOAT_TO_FX32(1.0);

    SetTaskState(work, SailItemBonus__State_216CBF8);

    return work;
}

void SailObject__Destructor(Task *task)
{
    StageTask *work    = TaskGetWork(task, StageTask);
    SailObject *worker = GetStageTaskWorker(work, SailObject);

    ObjDraw__PaletteTex__Release(&worker->paletteTex);

    if (worker->objectRef && (worker->objectRef->flags & SAILMAPOBJECT_FLAG_20000000) == 0)
        SailEventManager__RemoveEntry(worker->objectRef);

    StageTask_Destructor(task);
}

BOOL SailObject__ViewCheck_Default(StageTask *work)
{
    s32 range          = 0;
    SailObject *worker = GetStageTaskWorker(work, SailObject);

    if ((work->flag & STAGE_TASK_FLAG_DISABLE_VIEWCHECK_EVENT) != 0)
        return FALSE;

    if (worker->objectRef != NULL)
    {
        if ((worker->objectRef->flags & SAILMAPOBJECT_FLAG_40000000) != 0)
            range = worker->objectRef->viewRange;
    }

    return SailEventManager__ViewCheck(&work->position, range) != FALSE;
}

NONMATCH_FUNC void SailObject__OnDefend_Default(OBS_RECT_WORK *rect1, OBS_RECT_WORK *rect2)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, r7, r8, r9, lr}
	sub sp, sp, #0x24
	mov r8, r1
	ldr r4, [r8, #0x3c]
	mov r9, r0
	ldr r0, [r4, #0x6c]
	ldr r5, [r9, #0x3c]
	ldr r7, [r0, #0x124]
	mov r6, #0
	bl SailManager__GetShipType
	cmp r0, #3
	ldreq r1, [r5, #0x6c]
	ldreqh r0, [r1, #0]
	cmpeq r0, #2
	bne _02169C1C
	ldr r0, [r1, #0x24]
	cmp r0, #0
	beq _02169C1C
	ldr r1, [r1, #0x124]
	ldr r0, [r4, #0x6c]
	ldr r1, [r1, #0x15c]
	cmp r1, r0
	beq _02169C1C
	mov r0, r9
	mov r1, r8
	bl ObjRect__FuncNoHit
	add sp, sp, #0x24
	ldmia sp!, {r4, r5, r6, r7, r8, r9, pc}
_02169C1C:
	add r0, r7, #0x100
	ldrh r0, [r0, #0x30]
	cmp r0, #0
	beq _02169C4C
	ldrh r0, [r5, #0x74]
	tst r0, #0x40
	beq _02169C4C
	mov r0, r9
	mov r1, r8
	bl ObjRect__FuncNoHit
	add sp, sp, #0x24
	ldmia sp!, {r4, r5, r6, r7, r8, r9, pc}
_02169C4C:
	ldrh r0, [r5, #0x74]
	tst r0, #0x1000
	ldreq r0, [r5, #0x6c]
	ldreqh r0, [r0, #0]
	cmpeq r0, #1
	bne _02169D54
	ldr r0, [r8, #0x18]
	bic r0, r0, #0x100
	str r0, [r8, #0x18]
	ldr r0, [r4, #0x6c]
	ldr r1, [r5, #0x6c]
	cmp r1, r0
	addeq sp, sp, #0x24
	ldmeqia sp!, {r4, r5, r6, r7, r8, r9, pc}
	add r2, sp, #0xc
	add r0, r0, #0x44
	add r1, r1, #0x44
	bl VEC_Subtract
	ldr r1, [sp, #0xc]
	ldr r0, [sp, #0x14]
	ldr r2, [sp, #0x10]
	orr r0, r1, r0
	orrs r0, r2, r0
	bne _02169CC4
	mov r0, #0
	mov r1, #0x1000
	str r1, [sp, #0xc]
	str r0, [sp, #0x10]
	str r0, [sp, #0x14]
	b _02169CD0
_02169CC4:
	add r0, sp, #0xc
	mov r1, r0
	bl VEC_Normalize
_02169CD0:
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #0x14]
	rsb r5, r0, #0
	mov r0, r5, asr #0x1f
	mov r3, r0, lsl #0xa
	mov r0, r1, asr #0x1f
	mov r2, r0, lsl #0xa
	mov r0, #0x800
	adds r6, r0, r5, lsl #10
	orr r3, r3, r5, lsr #22
	adc r5, r3, #0
	mov r6, r6, lsr #0xc
	orr r6, r6, r5, lsl #20
	mov r5, #0
	adds r3, r0, r1, lsl #10
	orr r2, r2, r1, lsr #22
	adc r0, r2, #0
	mov r1, r3, lsr #0xc
	orr r1, r1, r0, lsl #20
	str r1, [sp, #0x14]
	str r5, [sp, #0x10]
	str r6, [sp, #0xc]
	ldr r2, [r4, #0x6c]
	add r1, sp, #0xc
	add r0, r2, #0x44
	add r2, r2, #0x44
	bl VEC_Add
	add r0, r7, #0x170
	add r1, sp, #0xc
	mov r2, r0
	bl VEC_Add
	add sp, sp, #0x24
	ldmia sp!, {r4, r5, r6, r7, r8, r9, pc}
_02169D54:
	add r0, r4, #0x3c
	add r3, sp, #0x18
	ldmia r0, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	ldrh r0, [r5, #0]
	cmp r0, #2
	bne _02169DA4
	add r0, r5, #0x54
	add ip, sp, #0
	ldmia r0, {r0, r1, r2}
	stmia ip, {r0, r1, r2}
	ldr r0, [sp, #4]
	mov r1, ip
	rsb r0, r0, #0
	str r0, [sp, #4]
	ldr r0, [r4, #0x28]
	mov r2, r3
	mov r0, r0, lsl #2
	rsb r0, r0, #0
	bl VEC_MultAdd
_02169DA4:
	ldrh r0, [r5, #0x74]
	tst r0, #0x8000
	ldrne r0, [r5, #0x6c]
	cmpne r0, #0
	beq _02169DC8
	add r0, r0, #0x8c
	add r3, sp, #0x18
	ldmia r0, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
_02169DC8:
	ldrh r1, [r5, #0x74]
	tst r1, #4
	bne _02169E04
	ldrh r0, [r4, #0x74]
	tst r0, #0x20
	beq _02169DF8
	tst r1, #0x10
	beq _02169DF8
	add r0, sp, #0x18
	bl EffectSailGuard__Create
	mov r6, r0
	b _02169E04
_02169DF8:
	add r0, sp, #0x18
	bl EffectSailHit__Create
	mov r6, r0
_02169E04:
	cmp r6, #0
	beq _02169E98
	ldrh r0, [r5, #0x74]
	tst r0, #1
	beq _02169E4C
	ldr r2, [r6, #0x38]
	mov r0, #0x800
	mov r1, r2, asr #0x1f
	mov r1, r1, lsl #0xb
	adds r3, r0, r2, lsl #11
	orr r1, r1, r2, lsr #21
	adc r0, r1, #0
	mov r1, r3, lsr #0xc
	orr r1, r1, r0, lsl #20
	str r1, [r6, #0x38]
	str r1, [r6, #0x3c]
	str r1, [r6, #0x40]
	b _02169E84
_02169E4C:
	tst r0, #2
	beq _02169E84
	ldr r2, [r6, #0x38]
	mov r0, #0x800
	mov r1, r2, asr #0x1f
	mov r1, r1, lsl #0xa
	adds r3, r0, r2, lsl #10
	orr r1, r1, r2, lsr #22
	adc r0, r1, #0
	mov r1, r3, lsr #0xc
	orr r1, r1, r0, lsl #20
	str r1, [r6, #0x38]
	str r1, [r6, #0x3c]
	str r1, [r6, #0x40]
_02169E84:
	ldrh r0, [r5, #0]
	cmp r0, #2
	ldreq r0, [r6, #0x24]
	biceq r0, r0, #1
	streq r0, [r6, #0x24]
_02169E98:
	ldr r1, [r7, #0x158]
	cmp r1, #0
	beq _02169EB4
	ldr r0, [r5, #0x6c]
	cmp r1, r0
	addeq sp, sp, #0x24
	ldmeqia sp!, {r4, r5, r6, r7, r8, r9, pc}
_02169EB4:
	ldr r0, [r5, #0x6c]
	str r0, [r7, #0x158]
	ldrh r0, [r4, #0x74]
	tst r0, #0x20
	beq _02169F08
	ldrh r0, [r5, #0x74]
	tst r0, #0x10
	beq _02169F08
	ldr r0, [r7, #0x168]
	cmp r0, #0
	bne _02169EEC
	ldr r0, [r4, #0x6c]
	bl SailEnemyHealthBar__Create
	str r0, [r7, #0x168]
_02169EEC:
	ldr r0, [r4, #0x6c]
	add r2, sp, #0x18
	ldr r0, [r0, #0x138]
	mov r1, #0x1a
	bl SailAudio__PlaySpatialSequence
	add sp, sp, #0x24
	ldmia sp!, {r4, r5, r6, r7, r8, r9, pc}
_02169F08:
	ldrh r0, [r5, #0x74]
	ldr r6, [r5, #0x70]
	ands r1, r0, #0x40
	bne _02169F34
	ldr r0, [r4, #0x6c]
	ldr r0, [r0, #0x24]
	tst r0, #0x20
	beq _02169F34
	mov r6, r6, asr #2
	cmp r6, #0x1000
	movgt r6, #0x1000
_02169F34:
	cmp r1, #0
	beq _02169F58
	add r0, r7, #0x100
	mov r1, #4
	strh r1, [r0, #0x30]
	ldr r0, [r4, #0x6c]
	ldr r0, [r0, #0x24]
	tst r0, #0x80000
	movne r6, r6, lsl #2
_02169F58:
	ldr r0, [r4, #0x6c]
	ldr r0, [r0, #0x24]
	tst r0, #0x200000
	beq _02169F70
	cmp r6, #0x3c000
_02169F6C:
	movlt r6, #0x1000
_02169F70:
	ldrh r0, [r5, #0x74]
	tst r0, #0x400
	bne _02169F94
	ldr r0, [r5, #0x6c]
	mov r1, #0x4000
	str r1, [r0, #4]
	ldr r0, [r5, #0x6c]
	mov r1, #0x2000
	str r1, [r0, #8]
_02169F94:
	ldrh r0, [r5, #0x74]
	tst r0, #0x40
	ldreq r0, [r4, #0x6c]
	moveq r1, #0x2000
	streq r1, [r0, #8]
	ldr r0, [r4, #0x6c]
	mov r1, #0x4000
	str r1, [r0, #4]
	ldrh r0, [r5, #0x74]
	tst r0, #0x800
	bne _02169FE0
	bl SailManager__GetShipType
	cmp r0, #0
	beq _02169FD8
	bl SailManager__GetShipType
	cmp r0, #2
	bne _02169FE0
_02169FD8:
	mov r0, #3
	bl ShakeScreen
_02169FE0:
	bl SailManager__GetShipType
	cmp r0, #1
	bne _0216A05C
	ldrh r0, [r5, #0x74]
	tst r0, #0x10
	beq _0216A010
	ldr r0, [r4, #0x6c]
	add r2, sp, #0x18
	ldr r0, [r0, #0x138]
	mov r1, #0x19
	bl SailAudio__PlaySpatialSequence
	b _0216A04C
_0216A010:
	tst r0, #0x40
	beq _0216A030
	ldr r0, [r4, #0x6c]
	add r2, sp, #0x18
	ldr r0, [r0, #0x138]
	mov r1, #0x19
	bl SailAudio__PlaySpatialSequence
	b _0216A04C
_0216A030:
	tst r0, #0x8000
	beq _0216A04C
	ldr r0, [r4, #0x6c]
	add r2, sp, #0x18
	ldr r0, [r0, #0x138]
	mov r1, #0x1d
	bl SailAudio__PlaySpatialSequence
_0216A04C:
	mov r0, r9
	mov r1, r8
	mov r2, #0xa
	bl SailObject__GivePlayerScore
_0216A05C:
	bl SailManager__GetShipType
	cmp r0, #2
	bne _0216A098
	ldrh r0, [r5, #0x74]
	tst r0, #0x10
	beq _0216A088
	ldr r0, [r4, #0x6c]
	add r2, sp, #0x18
	ldr r0, [r0, #0x138]
	mov r1, #0x19
	bl SailAudio__PlaySpatialSequence
_0216A088:
	mov r0, r9
	mov r1, r8
	mov r2, #0xa
	bl SailObject__GivePlayerScore
_0216A098:
	ldr r0, [r4, #0x6c]
	ldr r0, [r0, #0x24]
	tst r0, #0x100000
	bne _0216A154
	ldr r0, [r7, #0x11c]
	sub r0, r0, r6
	str r0, [r7, #0x11c]
	ldr r0, [r4, #0x6c]
	ldr r1, [r0, #0x24]
	tst r1, #0x10000
	beq _0216A0D0
	ldr r1, [r5, #0x6c]
	bl SailItemBonus__GiveItem
	b _0216A154
_0216A0D0:
	ldr r1, [r7, #0x11c]
	cmp r1, #0
	bgt _0216A134
	bl SailObject__Action_Destroy
	bl SailManager__GetShipType
	cmp r0, #2
	ldreq r0, [r5, #0x6c]
	ldreqh r0, [r0, #0]
	cmpeq r0, #2
	bne _0216A108
	ldr r0, [r4, #0x6c]
	mov r1, #0xc
	str r1, [r0, #0x2c]
	b _0216A154
_0216A108:
	bl SailManager__GetShipType
	cmp r0, #2
	beq _0216A120
	bl SailManager__GetShipType
	cmp r0, #0
	bne _0216A154
_0216A120:
	mov r0, #0
	mov r2, r0
	mov r1, #0xd
	bl SailAudio__PlaySpatialSequence
	b _0216A154
_0216A134:
	ldr r1, [r7, #0x168]
	cmp r1, #0
	bne _0216A148
	bl SailEnemyHealthBar__Create
	str r0, [r7, #0x168]
_0216A148:
	add r0, r7, #0x100
	mov r1, #4
	strh r1, [r0, #0x2e]
_0216A154:
	mov r0, r9
	mov r1, r8
	bl SailObject__OnPlayerCollide
	add sp, sp, #0x24
	ldmia sp!, {r4, r5, r6, r7, r8, r9, pc}

// clang-format on
#endif
}

void SailObject__GivePlayerScore(OBS_RECT_WORK *rect1, OBS_RECT_WORK *rect2, u32 score)
{
    SailPlayer *player = NULL;

    SailColliderWork *collider = rect1->userData;
    StageTask *work            = collider->stageTask;

    if (work->objType == SAILSTAGE_OBJ_TYPE_PLAYER)
    {
        player = GetStageTaskWorker(work, SailPlayer);
    }
    else
    {
        if (work->parentObj != NULL && work->parentObj->objType == SAILSTAGE_OBJ_TYPE_PLAYER)
            player = GetStageTaskWorker(work->parentObj, SailPlayer);
    }

    if (player != NULL)
    {
        player->score += score;
        if (player->score > SAILPLAYER_MAX_SCORE)
            player->score = SAILPLAYER_MAX_SCORE;
    }
}

NONMATCH_FUNC void SailObject__OnPlayerCollide(OBS_RECT_WORK *rect1, OBS_RECT_WORK *rect2)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, lr}
	sub sp, sp, #0xc
	ldr r6, [r0, #0x3c]
	mov r4, r1
	ldr r1, [r6, #0x6c]
	ldr r5, [r4, #0x3c]
	ldrh r0, [r1, #0]
	ldr r2, [r5, #0x6c]
	mov r8, #0
	cmp r0, #0
	ldr r7, [r2, #0x124]
	ldreq r8, [r1, #0x124]
	beq _0216A210
	ldr r1, [r1, #0x11c]
	cmp r1, #0
	beq _0216A210
	ldrh r0, [r1, #0]
	cmp r0, #0
	ldreq r8, [r1, #0x124]
_0216A210:
	cmp r8, #0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, pc}
	bl SailManager__GetShipType
	cmp r0, #3
	addls pc, pc, r0, lsl #2
	b _0216A2A0
_0216A22C: // jump table
	b _0216A23C // case 0
	b _0216A250 // case 1
	b _0216A23C // case 2
	b _0216A250 // case 3
_0216A23C:
	add r0, r8, #0x100
	mov r1, #0x50
	strh r1, [r0, #0xe2]
	mov r1, #0
	strh r1, [r0, #0xe4]
_0216A250:
	add r0, r8, #0x100
	ldrh r2, [r0, #0xc4]
	ldr r1, =0x000003E7
	add r2, r2, #1
	strh r2, [r0, #0xc4]
	ldrh r2, [r0, #0xc4]
	cmp r2, r1
	strhih r1, [r0, #0xc4]
	add r0, r8, #0x100
	ldrh r2, [r0, #0xc4]
	ldrh r1, [r0, #0xc6]
	cmp r1, r2
	strloh r2, [r0, #0xc6]
	ldrh r0, [r6, #0x74]
	tst r0, #0x10
	bne _0216A2A0
	tst r0, #0x40
	ldreqb r0, [r8, #0x1b4]
	addeq r0, r0, #1
	streqb r0, [r8, #0x1b4]
_0216A2A0:
	ldr r0, [r7, #0x11c]
	cmp r0, #0
	addgt sp, sp, #0xc
	ldmgtia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, pc}
	bl SailManager__GetWork
	add r1, r8, #0x100
	mov r10, r0
	ldrh r0, [r1, #0xc4]
	mov r1, #0x32
	bl FX_DivS32
	ldr r1, [r5, #0x6c]
	add r0, r0, #1
	ldr r1, [r1, #0x24]
	mov r0, r0, lsl #0x10
	tst r1, #0x1000
	mov r9, r0, lsr #0x10
	ldrne r0, [r7, #0x118]
	add r3, sp, #0
	addne r0, r0, r0, lsr #1
	strne r0, [r7, #0x118]
	ldr r0, [r5, #0x6c]
	ldr r0, [r0, #0x24]
	tst r0, #0x2000
	ldrne r0, [r7, #0x118]
	addne r0, r0, r0
	strne r0, [r7, #0x118]
	ldr r2, [r8, #0x1a8]
	ldr r1, [r7, #0x118]
	ldr r0, =0x05F5E0FF
	mla r2, r1, r9, r2
	str r2, [r8, #0x1a8]
	cmp r2, r0
	strhi r0, [r8, #0x1a8]
	ldr r0, [r5, #0x6c]
	add r0, r0, #0x44
	ldmia r0, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	ldr r0, [sp, #4]
	rsb r2, r0, #0
	str r2, [sp, #4]
	ldr r1, [r7, #8]
	ldr r0, [r7, #0x50]
	add r0, r1, r0
	add r0, r2, r0
	str r0, [sp, #4]
	bl SailManager__GetShipType
	cmp r0, #2
	ldreq r0, [sp, #4]
	addeq r0, r0, #0x1000
	streq r0, [sp, #4]
	cmp r9, #9
	movhi r9, #9
	ldr r1, [r7, #0x118]
	add r0, sp, #0
	mov r2, r9
	bl SailScoreBonus__CreateWorld
	ldr r0, [r5, #0x6c]
	ldr r0, [r0, #0x24]
	tst r0, #0x800000
	ldreq r0, [r8, #0x1ac]
	addeq r0, r0, #1
	streq r0, [r8, #0x1ac]
	bl SailManager__GetShipType
	cmp r0, #1
	beq _0216A3FC
	cmp r0, #2
	bne _0216A410
	ldrh r0, [r6, #0x74]
	tst r0, #0x10
	beq _0216A3C8
	ldrb r0, [r8, #0x1b0]
	add r0, r0, #1
	strb r0, [r8, #0x1b0]
	b _0216A410
_0216A3C8:
	tst r0, #0x2000
	beq _0216A3EC
	ldrsh r0, [r4, #0x2e]
	cmp r0, #0xb
	blt _0216A3EC
	ldrb r0, [r8, #0x1b2]
	add r0, r0, #1
	strb r0, [r8, #0x1b2]
	b _0216A410
_0216A3EC:
	ldrb r0, [r8, #0x1b1]
	add r0, r0, #1
	strb r0, [r8, #0x1b1]
	b _0216A410
_0216A3FC:
	ldrh r0, [r6, #0x74]
	tst r0, #0x10
	ldrneb r0, [r8, #0x1b3]
	addne r0, r0, #1
	strneb r0, [r8, #0x1b3]
_0216A410:
	ldr r2, [r7, #0x164]
	cmp r2, #0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, pc}
	ldr r1, [r2, #0x34]
	tst r1, #0x20000000
	addne sp, sp, #0xc
	ldmneia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, pc}
	ldrh r0, [r2, #0x30]
	cmp r0, #0x1d
	addhs sp, sp, #0xc
	ldmhsia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, pc}
	tst r1, #0x80
	ldreqh r1, [r2, #0x32]
	ldreqh r0, [r10, #0x60]
	cmpeq r1, r0
	ldreqh r0, [r10, #0x5e]
	addeq r0, r0, #1
	streqh r0, [r10, #0x5e]
	add sp, sp, #0xc
	ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailLanding__State_216A46C(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r4, r0
	bl SailManager__GetWork
	ldr r3, [r0, #0x98]
	mov ip, #0
	ldrh r5, [r3, #0xfe]
	cmp r5, #0
	bls _0216A4D8
	ldr lr, [r4, #0x2c]
_0216A490:
	add r2, r3, ip, lsl #3
	ldr r1, [r2, #0xcc]
	ldrsh r0, [r1, #0x10]
	cmp lr, r0
	bne _0216A4C4
	ldrsh r0, [r1, #2]
	mov r0, r0, lsl #0xc
	str r0, [r4, #0x44]
	ldr r0, [r2, #0xcc]
	ldrsh r0, [r0, #4]
	mov r0, r0, lsl #0xc
	str r0, [r4, #0x4c]
	ldmia sp!, {r3, r4, r5, pc}
_0216A4C4:
	add r0, ip, #1
	mov r0, r0, lsl #0x10
	cmp r5, r0, lsr #16
	mov ip, r0, lsr #0x10
	bhi _0216A490
_0216A4D8:
	ldr r0, [r4, #0x18]
	orr r0, r0, #4
	str r0, [r4, #0x18]
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailLanding__Draw_216A4E8(void)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0x24
	bl GetCurrentTaskWork_
	mov r4, r0
	ldr r0, [r4, #0x18]
	ldr r5, [r4, #0x124]
	tst r0, #4
	addne sp, sp, #0x24
	ldmneia sp!, {r4, r5, r6, r7, pc}
	add r0, r4, #0x44
	add r3, sp, #0x18
	ldmia r0, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	mov r0, r3
	bl VEC_Mag
	cmp r0, #0x50000
	ble _0216A5B4
	cmp r0, #0x180000
	addgt sp, sp, #0x24
	ldmgtia sp!, {r4, r5, r6, r7, pc}
	rsb r0, r0, #0x180000
	mov r1, #0x130000
	bl FX_Div
	mov r2, #0x1f
	mov ip, #0
	umull r6, lr, r0, r2
	mov r1, r0, asr #0x1f
	mla lr, r0, ip, lr
	mov r7, r1, lsl #0xa
	mov r3, #0x800
	mla lr, r1, r2, lr
	adds r3, r3, r0, lsl #10
	orr r7, r7, r0, lsr #22
	adc r0, r7, #0
	mov r7, r3, lsr #0xc
	orr r7, r7, r0, lsl #20
	adds r3, r6, #0x800
	str r7, [r4, #0x38]
	str r7, [r4, #0x3c]
	str r7, [r4, #0x40]
	adc r0, lr, #0
	mov r1, r3, lsr #0xc
	orrs r1, r1, r0, lsl #20
	movmi r1, ip
	ldr r2, [r4, #0x134]
	mov r0, r1, lsl #0x1b
	ldr r1, [r2, #0xf4]
	bic r1, r1, #0x1f0000
	orr r0, r1, r0, lsr #11
	str r0, [r2, #0xf4]
	b _0216A5D8
_0216A5B4:
	mov r0, #0x400
	str r0, [r4, #0x38]
	str r0, [r4, #0x3c]
	str r0, [r4, #0x40]
	ldr r1, [r4, #0x134]
	ldr r0, [r1, #0xf4]
	bic r0, r0, #0x1f0000
	orr r0, r0, #0x1f0000
	str r0, [r1, #0xf4]
_0216A5D8:
	add r0, r4, #0x44
	add lr, sp, #0xc
	ldmia r0, {r0, r1, r2}
	stmia lr, {r0, r1, r2}
	mov ip, #0
	ldr r3, [sp, #0x10]
	add r1, sp, #0
	mov r0, lr
	mov r2, lr
	str ip, [sp]
	str ip, [sp, #8]
	str r3, [sp, #4]
	bl VEC_Subtract
	ldr r0, [sp, #0xc]
	cmp r0, #0
	ldreq r0, [sp, #0x10]
	cmpeq r0, #0
	ldreq r0, [sp, #0x14]
	cmpeq r0, #0
	moveq r0, #1
	streq r0, [sp, #0x14]
	add r0, sp, #0xc
	mov r1, r0
	bl VEC_Normalize
	add r1, sp, #0xc
	add r2, sp, #0
	mov r3, r1
	mov r0, #0x50000
	bl VEC_MultAdd
	add r0, sp, #0xc
	add r3, r4, #0x44
	ldmia r0, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	ldr r0, =0x00007FFF
	bl SailObject__ApplyFogBrightness
	mov r1, r0
	mov r0, r4
	bl SailObject__SetSpriteColor
	ldr r1, [r4, #0x134]
	mov r0, r4
	bl StageTask__Draw3D
	add ip, r4, #0x44
	add r4, r5, #0x10
	ldmia ip, {r0, r1, r2}
	stmia r4, {r0, r1, r2}
	add r3, sp, #0x18
	ldmia r3, {r0, r1, r2}
	stmia ip, {r0, r1, r2}
	add sp, sp, #0x24
	ldmia sp!, {r4, r5, r6, r7, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailLanding__Draw_216A6A4(void)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0xc
	bl SailManager__GetWork
	ldr r4, [r0, #0x98]
	bl GetCurrentTaskWork_
	mov r5, r0
	bl SailManager__GetWork
	ldr r1, [r0, #0x70]
	ldr r0, [r5, #0x18]
	ldr r6, [r1, #0x124]
	tst r0, #4
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, r6, r7, pc}
	ldr r1, [r4, #0x64]
	ldr r0, [r5, #0x44]
	mov r2, #0
	sub r0, r1, r0
	str r0, [sp]
	ldr r3, [r4, #0x68]
	ldr r1, [r5, #0x4c]
	sub r7, r3, r1
	mov r1, r7
	str r7, [sp, #4]
	str r2, [sp, #8]
	bl FX_Atan2Idx
	add r1, r6, #0x100
	ldrh r3, [r4, #0x34]
	ldrsh r2, [r1, #0xca]
	add r2, r3, r2
	sub r0, r0, r2
	mov r0, r0, lsl #0x10
	add r0, r2, r0, lsr #16
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	str r0, [r5, #0x28]
	mov r0, r0, lsl #0x10
	ldrh r2, [r4, #0x34]
	ldrsh r1, [r1, #0xca]
	mov r0, r0, lsr #0x10
	add r1, r2, r1
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	bl ObjRoopDiff16
	cmp r0, #0x2800
	addgt sp, sp, #0xc
	ldmgtia sp!, {r4, r5, r6, r7, pc}
	ldr r0, [sp]
	ldr r1, =0x00000F5E
	cmp r0, #0
	rsblt r0, r0, #0
	cmp r7, #0
	rsblt r7, r7, #0
	cmp r0, r7
	ldr r2, =0x0000065D
	mov r3, #0
	ble _0216A7C4
	umull lr, ip, r0, r1
	mla ip, r0, r3, ip
	umull r6, r4, r7, r2
	mov r0, r0, asr #0x1f
	mla ip, r0, r1, ip
	adds lr, lr, #0x800
	adc ip, ip, #0
	adds r1, r6, #0x800
	mov r6, lr, lsr #0xc
	mla r4, r7, r3, r4
	mov r0, r7, asr #0x1f
	mla r4, r0, r2, r4
	adc r0, r4, #0
	mov r1, r1, lsr #0xc
	orr r6, r6, ip, lsl #20
	b _0216A800
_0216A7C4:
	umull lr, ip, r7, r1
	mla ip, r7, r3, ip
	umull r6, r4, r0, r2
	mla r4, r0, r3, r4
	mov r7, r7, asr #0x1f
	mov r0, r0, asr #0x1f
	mla ip, r7, r1, ip
	adds lr, lr, #0x800
	adc r7, ip, #0
	adds r1, r6, #0x800
	mla r4, r0, r2, r4
	mov r6, lr, lsr #0xc
	adc r0, r4, #0
	mov r1, r1, lsr #0xc
	orr r6, r6, r7, lsl #20
_0216A800:
	orr r1, r1, r0, lsl #20
	add r0, r6, r1
	cmp r0, #0x40000
	movgt r0, #0x40000
	rsb r0, r0, #0x40000
	cmp r0, #0x40000
	bge _0216A894
	mov r1, #0x40000
	bl FX_Div
	mov r1, #0x1f
	mov r3, #0
	umull r6, r4, r0, r1
	mov ip, r0, asr #0x1f
	mla r4, r0, r3, r4
	mov r7, ip, lsl #9
	mov r2, #0x800
	mla r4, ip, r1, r4
	adds r2, r2, r0, lsl #9
	orr r7, r7, r0, lsr #23
	adc r0, r7, #0
	mov r7, r2, lsr #0xc
	orr r7, r7, r0, lsl #20
	adds r2, r6, #0x800
	str r7, [r5, #0x38]
	str r7, [r5, #0x3c]
	adc r0, r4, #0
	mov r1, r2, lsr #0xc
	str r7, [r5, #0x40]
	orrs r1, r1, r0, lsl #20
	movmi r1, r3
	ldr r2, [r5, #0x134]
	mov r0, r1, lsl #0x1b
	ldr r1, [r2, #0xf4]
	bic r1, r1, #0x1f0000
	orr r0, r1, r0, lsr #11
	str r0, [r2, #0xf4]
	b _0216A8B8
_0216A894:
	mov r0, #0x200
	str r0, [r5, #0x38]
	str r0, [r5, #0x3c]
	str r0, [r5, #0x40]
	ldr r1, [r5, #0x134]
	ldr r0, [r1, #0xf4]
	bic r0, r0, #0x1f0000
	orr r0, r0, #0x1f0000
	str r0, [r1, #0xf4]
_0216A8B8:
	add r0, r5, #0x44
	add r3, sp, #0
	ldmia r0, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	mov r4, #0x50000
	bl SailManager__GetShipType
	cmp r0, #1
	ldr r0, [r5, #0x28]
	ldr r1, =FX_SinCosTable_
	add r0, r0, #0x8000
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, asr #4
	mov r0, r0, lsl #2
	ldrsh r2, [r1, r0]
	moveq r4, #0x58000
	ldr r0, =0x00007FFF
	smull r3, r2, r4, r2
	adds r3, r3, #0x800
	adc r2, r2, #0
	mov r3, r3, lsr #0xc
	orr r3, r3, r2, lsl #20
	str r3, [r5, #0x44]
	ldr r2, [r5, #0x28]
	add r2, r2, #0x8000
	mov r2, r2, lsl #0x10
	mov r2, r2, lsr #0x10
	mov r2, r2, lsl #0x10
	mov r2, r2, lsr #0x10
	mov r2, r2, asr #4
	mov r2, r2, lsl #1
	add r2, r2, #1
	mov r2, r2, lsl #1
	ldrsh r1, [r1, r2]
	smull r2, r1, r4, r1
	adds r2, r2, #0x800
	adc r1, r1, #0
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #20
	str r2, [r5, #0x4c]
	bl SailObject__ApplyFogBrightness
	mov r1, r0
	mov r0, r5
	bl SailObject__SetSpriteColor
	ldr r1, [r5, #0x134]
	mov r0, r5
	bl StageTask__Draw3D
	add r0, sp, #0
	add r3, r5, #0x44
	ldmia r0, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}

// clang-format on
#endif
}

void SailMine__State_216A4E8(StageTask *work)
{
    OBS_RECT_WORK *collider = StageTask__GetCollider(work, 0);

    if (collider != NULL)
    {
        if ((collider->flag & OBS_RECT_WORK_FLAG_200) != 0)
        {
            SailAudio__PlaySpatialSequence(work->sequencePlayerPtr, SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_EXPLOSION, &work->position);
            DestroyStageTask(work);
            EffectSailBomb__Create(&work->position);
        }
    }
}

void SailJetBomber__Action_Init(StageTask *work)
{
    SetTaskState(work, SailJetBomber__State_216AA38);

    work->userTimer  = 32;
    work->velocity.y = -FLOAT_TO_FX32(0.125);

    work->flag |= STAGE_TASK_FLAG_DISABLE_VIEWCHECK_EVENT;
    work->moveFlag |= STAGE_TASK_MOVE_FLAG_HAS_GRAVITY;

    work->gravityStrength  = FLOAT_TO_FX32(0.0341796875);
    work->terminalVelocity = FLOAT_TO_FX32(0.15625);
}

NONMATCH_FUNC void SailJetBomber__State_216AA38(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, lr}
	mov r6, r0
	mov r1, #0
	ldr r4, [r6, #0x124]
	bl StageTask__GetCollider
	ldr r1, [r6, #0x48]
	mov r5, r0
	cmp r1, #0
	ble _0216AA7C
	ldr r0, [r6, #0x1c]
	mvn r1, #0xdf
	bic r0, r0, #0x80
	str r0, [r6, #0x1c]
	ldr r0, [r6, #0x9c]
	mov r2, #0x200
	bl ObjSpdUpSet
	str r0, [r6, #0x9c]
_0216AA7C:
	ldr r0, [r6, #0x1c]
	tst r0, #0x80
	bne _0216AAA8
	ldr r0, [r6, #0x48]
	cmp r0, #0
	bge _0216AAA8
	ldr r0, [r6, #0x9c]
	mov r1, #0x70
	mov r2, #0xc0
	bl ObjSpdUpSet
	str r0, [r6, #0x9c]
_0216AAA8:
	ldr r0, [r6, #0x2c]
	cmp r0, #6
	moveq r0, r0, lsl #0xc
	streq r0, [r6, #4]
	ldr r0, [r6, #0x2c]
	cmp r0, #0x10
	bge _0216AAEC
	tst r0, #2
	beq _0216AADC
	mov r0, r6
	mov r1, #0x1f
	bl SailObject__SetSpriteColor
	b _0216AB10
_0216AADC:
	ldr r1, =0x00007FFF
	mov r0, r6
	bl SailObject__SetSpriteColor
	b _0216AB10
_0216AAEC:
	tst r0, #4
	beq _0216AB04
	mov r0, r6
	mov r1, #0x1f
	bl SailObject__SetSpriteColor
	b _0216AB10
_0216AB04:
	ldr r1, =0x00007FFF
	mov r0, r6
	bl SailObject__SetSpriteColor
_0216AB10:
	cmp r5, #0
	beq _0216AB54
	ldr r0, [r5, #0x18]
	tst r0, #0x200
	beq _0216AB54
	ldr r0, [r6, #0x18]
	orr r0, r0, #4
	str r0, [r6, #0x18]
	ldr r0, [r6, #0x20]
	tst r0, #0x20
	bne _0216AB54
	add r0, r6, #0x44
	bl EffectSailBomb__Create
	ldr r0, [r6, #0x138]
	add r2, r6, #0x44
	mov r1, #0x12
	bl SailAudio__PlaySpatialSequence
_0216AB54:
	ldr r0, [r6, #0x2c]
	subs r0, r0, #1
	str r0, [r6, #0x2c]
	bne _0216ABB8
	ldr r1, [r6, #0x20]
	add r0, r6, #0x44
	orr r1, r1, #0x20
	str r1, [r6, #0x20]
	bl EffectSailBomb__Create
	ldr r3, [r0, #0x38]
	mov r1, #0x800
	mov r2, r3, asr #0x1f
	mov r2, r2, lsl #0xd
	adds r5, r1, r3, lsl #13
	orr r2, r2, r3, lsr #19
	adc r1, r2, #0
	mov r2, r5, lsr #0xc
	orr r2, r2, r1, lsl #20
	str r2, [r0, #0x38]
	str r2, [r0, #0x3c]
	str r2, [r0, #0x40]
	ldr r0, [r6, #0x138]
	add r2, r6, #0x44
	mov r1, #0x12
	bl SailAudio__PlaySpatialSequence
_0216ABB8:
	ldr r1, [r6, #0x2c]
	mvn r0, #3
	cmp r1, r0
	ldreq r0, [r4, #0x50]
	addeq r0, r0, r0, lsl #1
	streq r0, [r4, #0x50]
	ldr r1, [r6, #0x2c]
	mvn r0, #5
	cmp r1, r0
	ldrlt r0, [r6, #0x18]
	orrlt r0, r0, #4
	strlt r0, [r6, #0x18]
	ldmia sp!, {r4, r5, r6, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailJetBoatCloud__State_216AA38(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #0x40
	mov r5, r0
	ldr r4, [r5, #0x124]
	bl SailManager__GetWork
	ldr r2, [r4, #0x138]
	ldr r1, [r0, #0x34]
	mov r6, #0x800
	add r2, r2, r1, asr #9
	mov r1, r2, lsl #0x10
	mov r1, r1, lsr #0x10
	str r1, [r4, #0x138]
	ldr r3, [r5, #0x48]
	ldr r1, [r0, #0x3c]
	ldr r2, =FX_SinCosTable_
	sub r1, r3, r1, asr #5
	str r1, [r5, #0x48]
	ldr r3, [r4, #0x138]
	ldr r1, [r4, #0x13c]
	mov r3, r3, lsl #0x10
	mov r3, r3, lsr #0x10
	mov r3, r3, lsl #0x10
	mov r3, r3, lsr #0x10
	mov r3, r3, asr #4
	mov r3, r3, lsl #2
	ldrsh r8, [r2, r3]
	sub r7, r6, #0x7a00
	mov r3, #0x1f
	smull r8, r6, r1, r8
	adds r8, r8, #0x800
	adc r1, r6, #0
	mov r6, r8, lsr #0xc
	orr r6, r6, r1, lsl #20
	str r6, [r5, #0x44]
	ldr r6, [r4, #0x138]
	ldr r1, [r4, #0x13c]
	mov r6, r6, lsl #0x10
	mov r6, r6, lsr #0x10
	mov r6, r6, lsl #0x10
	mov r6, r6, lsr #0x10
	mov r6, r6, asr #4
	mov r6, r6, lsl #1
	add r6, r6, #1
	mov r6, r6, lsl #1
	ldrsh r2, [r2, r6]
	smull r6, r2, r1, r2
	adds r6, r6, #0x800
	adc r1, r2, #0
	mov r2, r6, lsr #0xc
	orr r2, r2, r1, lsl #20
	str r2, [r5, #0x4c]
	ldr r6, [r5, #0x134]
	ldrh r1, [r0, #0x30]
	ldr r2, [r6, #0xf4]
	bic r2, r2, #0x3f000000
	mov r1, r1, lsl #0x1a
	orr r1, r2, r1, lsr #2
	str r1, [r6, #0xf4]
	ldrh r1, [r0, #0x30]
	add r1, r1, #1
	strh r1, [r0, #0x30]
	ldr r2, [r5, #0x48]
	cmp r2, r7
	ble _0216AD00
	adds r1, r2, #0x6200
	rsbmi r1, r1, #0
	mov r1, r1, lsl #9
	mov r3, r1, lsr #0x10
_0216AD00:
	mov r1, #0x11800
	rsb r1, r1, #0
	cmp r2, r1
	bge _0216AD20
	adds r1, r2, #0x12800
	rsbmi r1, r1, #0
	mov r1, r1, lsl #9
	mov r3, r1, lsr #0x10
_0216AD20:
	ldr r7, [r5, #0x134]
	cmp r3, #0x20
	movhi r3, #0x1f
	cmp r3, #0
	moveq r3, #1
	ldr r6, [r7, #0xf4]
	mov r2, r3, lsl #0x1b
	bic r3, r6, #0x1f0000
	orr r2, r3, r2, lsr #11
	mov r1, #0x12800
	str r2, [r7, #0xf4]
	ldr r2, [r5, #0x48]
	rsb r1, r1, #0
	cmp r2, r1
	blt _0216AD68
	add r1, r1, #0xc600
	cmp r2, r1
	ble _0216AEB8
_0216AD68:
	ldr r0, [r5, #0x18]
	tst r0, #4
	bne _0216AEA4
	mov r0, #0
	add r8, sp, #0
	mov r1, r0
	stmia r8!, {r0, r1}
	stmia r8!, {r0, r1}
	ldr r2, =_obj_disp_rand
	stmia r8!, {r0, r1}
	stmia r8!, {r0, r1}
	stmia r8!, {r0, r1}
	stmia r8!, {r0, r1}
	stmia r8!, {r0, r1}
	stmia r8, {r0, r1}
	mov r8, #0x25
	ldr r3, [r2, #0]
	ldr r6, =0x00196225
	ldr r7, =0x3C6EF35F
	ldr lr, =0x0001FFFF
	mla ip, r3, r6, r7
	mov r1, ip, lsr #0x10
	mov r3, r1, lsl #0x10
	mla r1, ip, r6, r7
	and r7, lr, r3, lsr #16
	sub r3, r0, #0x4f000
	sub r3, r3, r7
	strh r8, [sp, #0x30]
	str ip, [r2]
	str r3, [sp, #0x28]
	ldr r7, [r4, #0x138]
	mov r6, r1, lsr #0x10
	strh r7, [sp, #0x2e]
	mov r4, r6, lsl #0x10
	sub r6, lr, #0x1c000
	and r6, r6, r4, lsr #16
	ldrh ip, [sp, #0x2e]
	rsb r6, r6, #0x2000
	str r1, [r2]
	add r6, ip, r6
	strh r6, [sp, #0x2e]
	ldrh r6, [sp, #0x2e]
	mov r4, #0x800
	ldr r7, =FX_SinCosTable_
	mov r2, r6, asr #4
	mov r6, r2, lsl #1
	add r2, r6, #1
	mov r6, r6, lsl #1
	mov r2, r2, lsl #1
	ldrsh r6, [r7, r6]
	ldrsh r2, [r7, r2]
	sub r1, r4, #0x13000
	smull r6, r7, r3, r6
	adds ip, r6, #0x800
	smull r6, r2, r3, r2
	adc r7, r7, r0
	adds r3, r6, #0x800
	mov r6, ip, lsr #0xc
	adc r0, r2, r0
	mov r2, r3, lsr #0xc
	orr r6, r6, r7, lsl #20
	orr r2, r2, r0, lsl #20
	str r6, [sp, #0x1c]
	str r2, [sp, #0x24]
	ldr r0, [r5, #0x48]
	cmp r0, r1
	sublt r0, r4, #0x6a00
	strlt r0, [sp, #0x20]
	mov r0, #0x6200
	ldr r1, [r5, #0x48]
	rsb r0, r0, #0
	cmp r1, r0
	ldr r1, [sp, #0x34]
	subgt r0, r0, #0xc600
	strgt r0, [sp, #0x20]
	orr r1, r1, #0x20000000
	add r0, sp, #0
	str r1, [sp, #0x34]
	bl SailEventManager__CreateObject2
_0216AEA4:
	ldr r0, [r5, #0x18]
	add sp, sp, #0x40
	orr r0, r0, #4
	str r0, [r5, #0x18]
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_0216AEB8:
	ldr r1, [r5, #0x20]
	orr r1, r1, #0x20
	str r1, [r5, #0x20]
	ldr r1, [r0, #0x94]
	ldr r0, [r4, #0x138]
	ldrh r2, [r1, #0x10]
	ldrsh r1, [r1, #0x12]
	add r1, r2, r1
	subs r0, r1, r0
	rsbmi r0, r0, #0
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	cmp r0, #0x1800
	blo _0216AEF8
	cmp r0, #0xe800
	bls _0216AF04
_0216AEF8:
	ldr r0, [r5, #0x20]
	bic r0, r0, #0x20
	str r0, [r5, #0x20]
_0216AF04:
	ldr r0, [r5, #0x28]
	mov r1, #1
	cmp r0, #0
	ldrne r0, [r5, #0x20]
	orrne r0, r0, #0x1000
	strne r0, [r5, #0x20]
	str r1, [r5, #0x28]
	ldr r0, [r5, #0x20]
	tst r0, #0x20
	addne sp, sp, #0x40
	ldmneia sp!, {r4, r5, r6, r7, r8, pc}
	rsb r0, r1, #0x8000
	bl SailObject__ApplyFogBrightness
	mov r1, r0
	mov r0, r5
	bl SailObject__SetSpriteColor
	add sp, sp, #0x40
	ldmia sp!, {r4, r5, r6, r7, r8, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailCloud__State_216AF60(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, r7, lr}
	mov r7, r0
	ldr r4, [r7, #0x124]
	bl SailManager__GetWork
	mov r5, r0
	bl SailManager__GetWork
	ldr r0, [r0, #0x70]
	ldr r6, [r0, #0x124]
	bl SailManager__GetWork
	ldr r2, [r4, #0x138]
	ldr r1, [r5, #0x34]
	ldr r3, [r0, #0x98]
	add r1, r2, r1, asr #9
	mov r0, r1, lsl #0x10
	mov r0, r0, lsr #0x10
	str r0, [r4, #0x138]
	ldr r0, [r7, #0x20]
	tst r0, #0x20000
	bne _0216B040
	add r0, r6, #0x100
	ldrh r1, [r3, #0x34]
	ldrsh r2, [r0, #0xca]
	ldr r3, [r4, #0x138]
	sub r0, r1, #0x8000
	add r0, r2, r0
	add r0, r3, r0
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, asr #4
	mov r6, r0, lsl #1
	ldr r1, [r7, #0x48]
	ldr r0, [r5, #0x3c]
	ldr r2, =FX_SinCosTable_
	sub r1, r1, r0, asr #5
	mov r0, r6, lsl #1
	str r1, [r7, #0x48]
	ldrsh r1, [r2, r0]
	ldr r3, [r4, #0x13c]
	add r0, r6, #1
	smull r6, r1, r3, r1
	adds r3, r6, #0x800
	mov r0, r0, lsl #1
	adc r1, r1, #0
	mov r3, r3, lsr #0xc
	orr r3, r3, r1, lsl #20
	str r3, [r7, #0x44]
	ldrsh r0, [r2, r0]
	ldr r1, [r4, #0x13c]
	smull r2, r0, r1, r0
	adds r1, r2, #0x800
	adc r0, r0, #0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #20
	str r1, [r7, #0x4c]
_0216B040:
	ldr r2, [r7, #0x134]
	ldrh r0, [r5, #0x30]
	ldr r1, [r2, #0xf4]
	bic r1, r1, #0x3f000000
	mov r0, r0, lsl #0x1a
	orr r0, r1, r0, lsr #2
	str r0, [r2, #0xf4]
	ldrh r0, [r5, #0x30]
	add r0, r0, #1
	strh r0, [r5, #0x30]
	ldr r0, [r7, #0x2c]
	cmp r0, #0
	ldrne r0, [r7, #0x20]
	orrne r0, r0, #0x1000
	strne r0, [r7, #0x20]
	ldr r0, [r7, #0x2c]
	add r1, r0, #1
	str r1, [r7, #0x2c]
	ldr r0, [r7, #0x28]
	cmp r1, r0
	movlo r0, r1, lsl #0x10
	blo _0216B0A4
	sub r0, r1, r0
	rsb r0, r0, #0x10
	mov r0, r0, lsl #0x10
_0216B0A4:
	mov r1, r0, lsr #0x10
	ldrh r0, [r5, #0x5a]
	cmp r0, #3
	bne _0216B0C0
	cmp r1, #0xe
	movhi r1, #0xe
	b _0216B0C8
_0216B0C0:
	cmp r1, #6
	movhi r1, #6
_0216B0C8:
	ldr r2, [r7, #0x134]
	cmp r1, #0
	moveq r1, #1
	mov r0, r1, lsl #0x1b
	ldr r1, [r2, #0xf4]
	bic r1, r1, #0x1f0000
	orr r0, r1, r0, lsr #11
	str r0, [r2, #0xf4]
	ldr r0, [r7, #0x28]
	ldr r1, [r7, #0x2c]
	add r0, r0, #0x10
	cmp r1, r0
	bne _0216B138
	ldr r0, [r7, #0x18]
	orr r0, r0, #4
	str r0, [r7, #0x18]
	ldrh r0, [r5, #0x5a]
	cmp r0, #2
	cmpne r0, #3
	ldmneia sp!, {r3, r4, r5, r6, r7, pc}
	ldr r0, [r7, #0x20]
	tst r0, #0x20000
	beq _0216B130
	mov r0, #0
	bl SailCloud__Create
	b _0216B138
_0216B130:
	mov r0, #1
	bl SailCloud__Create
_0216B138:
	ldrh r0, [r5, #0x5a]
	cmp r0, #2
	cmpne r0, #3
	ldrne r0, [r7, #0x28]
	strne r0, [r7, #0x2c]
	ldr r0, [r7, #0x20]
	tst r0, #0x20
	ldmneia sp!, {r3, r4, r5, r6, r7, pc}
	ldr r0, =0x00007FFF
	bl SailObject__ApplyFogBrightness
	mov r1, r0
	mov r0, r7
	bl SailObject__SetSpriteColor
	ldmia sp!, {r3, r4, r5, r6, r7, pc}

// clang-format on
#endif
}

void SailObject__Action_Destroy(StageTask *work)
{
    ShipType shipType = SailManager__GetShipType();

    if (shipType != SHIP_BOAT && shipType != SHIP_SUBMARINE)
        SailObject__Action_ExplodeSimple(work);
    else
        SailObject__Action_Explode(work);
}

void SailObject__Action_ExplodeSimple(StageTask *work)
{
    SailObject *worker = GetStageTaskWorker(work, SailObject);
    SailPlayer *player = GetStageTaskWorker(worker->player, SailPlayer);

    worker->field_138.x = ObjDispRandRange5(-FLOAT_TO_FX32(0.125), FLOAT_TO_FX32(0.125));
    worker->field_138.y = ObjDispRandRepeat(FLOAT_TO_FX32(0.125));
    worker->field_138.y = -FLOAT_TO_FX32(0.125) - worker->field_138.y;
    worker->field_138.z = ObjDispRandRange5(-FLOAT_TO_FX32(0.5), FLOAT_TO_FX32(0.5));
    worker->field_134   = -(player->speed + FLOAT_TO_FX32(1.0));

    SetTaskState(work, SailObject__State_ExplodeSimple);

    work->flag |= STAGE_TASK_FLAG_DISABLE_VIEWCHECK_EVENT | STAGE_TASK_FLAG_NO_OBJ_COLLISION;
    work->userFlag |= SAILOBJECT_FLAG_1;
    work->userTimer = 0;
}

NONMATCH_FUNC void SailObject__State_ExplodeSimple(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #0xc
	mov r5, r0
	ldr r4, [r5, #0x124]
	ldr r3, =FX_SinCosTable_
	add r1, r4, #0x100
	ldrh r2, [r1, #0x6e]
	ldr r1, [r4, #0x138]
	ldr ip, [r4, #0x134]
	add r1, r2, r1
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	mov r1, r1, asr #4
	mov lr, r1, lsl #1
	mov r1, lr, lsl #1
	ldrsh r2, [r3, r1]
	add r1, lr, #1
	mov r1, r1, lsl #1
	smull lr, r2, ip, r2
	adds ip, lr, #0x800
	adc r2, r2, #0
	mov ip, ip, lsr #0xc
	orr ip, ip, r2, lsl #20
	str ip, [r5, #0x98]
	ldrsh r1, [r3, r1]
	ldr r2, [r4, #0x134]
	smull r3, r1, r2, r1
	adds r2, r3, #0x800
	adc r1, r1, #0
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #20
	str r2, [r5, #0xa0]
	ldr r1, [r4, #0x13c]
	str r1, [r5, #0x9c]
	ldrh r1, [r5, #0x32]
	add r1, r1, #0x1800
	strh r1, [r5, #0x32]
	ldr r1, [r4, #0x140]
	ldrh r2, [r5, #0x34]
	add r1, r1, #0x1000
	add r1, r2, r1
	strh r1, [r5, #0x34]
	ldr r1, [r4, #0x140]
	ldrh r2, [r5, #0x30]
	rsb r1, r1, #0x1000
	add r1, r2, r1
	strh r1, [r5, #0x30]
	bl SailObject__ApplyRotation
	ldr r0, [r5, #0x2c]
	add r0, r0, #1
	str r0, [r5, #0x2c]
	ldr r0, [r5, #0x24]
	tst r0, #2
	beq _0216B3E0
	ldr r0, [r5, #0x2c]
	cmp r0, #0xc
	ble _0216B3E0
	add r1, sp, #0
	mov r0, r5
	bl SailObject__Func_2165A9C
	add r1, sp, #0
	add r0, r5, #0x44
	mov r2, r1
	bl VEC_Subtract
	ldr r0, [r5, #0x138]
	add r2, r5, #0x44
	mov r1, #0x13
	bl SailAudio__PlaySpatialSequence
	ldr r1, [r5, #0x18]
	add r0, sp, #0
	orr r1, r1, #4
	str r1, [r5, #0x18]
	bl EffectSailBomb__Create
	ldr r2, [r0, #0x38]
	ldr r1, [r4, #0x124]
	add sp, sp, #0xc
	smull r3, r1, r2, r1
	adds r2, r3, #0x800
	adc r1, r1, #0
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #20
	str r2, [r0, #0x38]
	str r2, [r0, #0x3c]
	str r2, [r0, #0x40]
	ldmia sp!, {r4, r5, pc}
_0216B3E0:
	ldr r0, [r5, #0x2c]
	cmp r0, #0x18
	addle sp, sp, #0xc
	ldmleia sp!, {r4, r5, pc}
	ldr r0, [r5, #0x18]
	orr r0, r0, #4
	str r0, [r5, #0x18]
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__Action_Explode(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r5, r0
	ldr r4, [r5, #0x124]
	ldr r2, =SailObject__State_Explode
	mov r1, #0
	str r2, [r5, #0xf4]
	ldr r2, [r5, #0x18]
	orr r2, r2, #0x12
	str r2, [r5, #0x18]
	str r1, [r5, #0x2c]
	ldr r1, [r5, #0x24]
	tst r1, #4
	beq _0216B480
	add r1, r5, #0x44
	bl EffectUnknown2161544__Create
	mov r0, #0x24
	str r0, [r5, #0x2c]
	add r0, r4, #0x100
	mov r1, #0x20
	strh r1, [r0, #0x2e]
	mov r1, #0x120
	str r1, [r5, #0x9c]
	ldr r0, [r5, #0x24]
	tst r0, #1
	moveq r0, #0x400
	subne r0, r1, #0x520
	str r0, [r4, #0x184]
	mov r0, #0
	str r0, [r4, #0x180]
	b _0216B4A8
_0216B480:
	bl SailManager__GetShipType
	cmp r0, #3
	ldr r0, [r5, #0x138]
	add r2, r5, #0x44
	bne _0216B4A0
	mov r1, #0x4f
	bl SailAudio__PlaySpatialSequence
	b _0216B4A8
_0216B4A0:
	mov r1, #0x27
	bl SailAudio__PlaySpatialSequence
_0216B4A8:
	mov r0, #0x4000
	str r0, [r5, #4]
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

void SailObject__CreateRingsForExplode1(StageTask *work)
{
    if ((work->userFlag & SAILOBJECT_FLAG_40000) != 0)
    {
        VecFx32 ringVelocity;
        VecFx32 ringPosition;

        ringVelocity.x = FLOAT_TO_FX32(0.0703125);
        ringVelocity.y = -FLOAT_TO_FX32(0.3125);
        ringVelocity.z = FLOAT_TO_FX32(0.0703125);
        SailObject__Func_2165A9C(work, &ringPosition);

        VEC_Subtract(&work->position, &ringPosition, &ringPosition);
        if ((work->userFlag & SAILOBJECT_FLAG_1000000) != 0)
        {
            ringPosition.y -= FLOAT_TO_FX32(1.0);
            ringVelocity.y -= FLOAT_TO_FX32(0.1875);
        }

        SailRingManager_CreateObjectRing(&ringPosition, &ringVelocity);

        ringVelocity.x = -ringVelocity.x;
        SailRingManager_CreateObjectRing(&ringPosition, &ringVelocity);

        ringVelocity.z = -ringVelocity.z;
        SailRingManager_CreateObjectRing(&ringPosition, &ringVelocity);

        ringVelocity.x = -ringVelocity.x;
        SailRingManager_CreateObjectRing(&ringPosition, &ringVelocity);

        if ((work->userFlag & SAILOBJECT_FLAG_2000000) != 0)
        {
            for (u16 i = 0; i < 2; i++)
            {
                if (i == 0)
                {
                    ringVelocity.x = FLOAT_TO_FX32(0.09375);
                    ringVelocity.y = -FLOAT_TO_FX32(0.625);
                    ringVelocity.z = FLOAT_TO_FX32(0.09375);
                }

                if (i == 1)
                {
                    ringVelocity.x = FLOAT_TO_FX32(0.125);
                    ringVelocity.y = -FLOAT_TO_FX32(0.4375);
                    ringVelocity.z = FLOAT_TO_FX32(0.125);
                }

                ringPosition.y -= FLOAT_TO_FX32(1.0);
                SailRingManager_CreateObjectRing(&ringPosition, &ringVelocity);

                ringVelocity.x = -ringVelocity.x;
                SailRingManager_CreateObjectRing(&ringPosition, &ringVelocity);

                ringVelocity.z = -ringVelocity.z;
                SailRingManager_CreateObjectRing(&ringPosition, &ringVelocity);

                ringVelocity.x = -ringVelocity.x;
                SailRingManager_CreateObjectRing(&ringPosition, &ringVelocity);
            }
        }
    }
}

void SailObject__CreateRingsForExplode2(StageTask *work)
{
    if ((work->userFlag & SAILOBJECT_FLAG_40000) != 0)
    {
        VecFx32 ringVelocity;
        VecFx32 ringPosition;

        ringVelocity.x = FLOAT_TO_FX32(0.1640625);
        ringVelocity.y = -FLOAT_TO_FX32(0.3125);
        ringVelocity.z = FLOAT_TO_FX32(0.1640625);
        SailObject__Func_2165A9C(work, &ringPosition);

        if ((work->userFlag & SAILOBJECT_FLAG_1000000) != 0)
        {
            ringPosition.y -= FLOAT_TO_FX32(1.0);
            ringVelocity.y -= FLOAT_TO_FX32(0.4375);
        }

        VEC_Subtract(&work->position, &ringPosition, &ringPosition);

        SailRingManager_CreateObjectRing(&ringPosition, &ringVelocity);

        ringVelocity.x = -ringVelocity.x;
        SailRingManager_CreateObjectRing(&ringPosition, &ringVelocity);

        ringVelocity.z = -ringVelocity.z;
        SailRingManager_CreateObjectRing(&ringPosition, &ringVelocity);

        ringVelocity.x = -ringVelocity.x;
        SailRingManager_CreateObjectRing(&ringPosition, &ringVelocity);

        ringVelocity.x = FLOAT_TO_FX32(0.0);
        ringVelocity.y = -FLOAT_TO_FX32(0.3125);
        ringVelocity.z = FLOAT_TO_FX32(0.125);
        if ((work->userFlag & SAILOBJECT_FLAG_1000000) != 0)
            ringVelocity.y -= FLOAT_TO_FX32(0.3125);

        SailRingManager_CreateObjectRing(&ringPosition, &ringVelocity);

        ringVelocity.z = -ringVelocity.z;
        SailRingManager_CreateObjectRing(&ringPosition, &ringVelocity);

        ringVelocity.x = FLOAT_TO_FX32(0.125);
        ringVelocity.y = -FLOAT_TO_FX32(0.3125);
        ringVelocity.z = FLOAT_TO_FX32(0.0);
        if ((work->userFlag & SAILOBJECT_FLAG_1000000) != 0)
            ringVelocity.y -= FLOAT_TO_FX32(0.3125);

        SailRingManager_CreateObjectRing(&ringPosition, &ringVelocity);

        ringVelocity.x = -ringVelocity.x;
        SailRingManager_CreateObjectRing(&ringPosition, &ringVelocity);
    }
}

NONMATCH_FUNC void SailObject__State_Explode(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, lr}
	sub sp, sp, #0xc
	mov r6, r0
	ldr r4, [r6, #0x124]
	bl SailObject__ApplyRotation
	ldr r0, [r6, #0x24]
	tst r0, #4
	beq _0216B818
	mov r0, r6
	bl SailObject__Func_2166A2C
	ldr r0, [r6, #4]
	cmp r0, #0
	moveq r0, #0x4000
	streq r0, [r6, #4]
	ldr r0, [r6, #0x2c]
	tst r0, #7
	bne _0216B818
	mov r0, r6
	bl SailObject__CreateRingsForExplode1
	bl SailManager__GetShipType
	cmp r0, #3
	ldr r0, [r6, #0x138]
	add r2, r6, #0x44
	bne _0216B810
	mov r1, #0x50
	bl SailAudio__PlaySpatialSequence
	b _0216B818
_0216B810:
	mov r1, #0x28
	bl SailAudio__PlaySpatialSequence
_0216B818:
	ldr r0, [r6, #0x2c]
	cmp r0, #0
	bne _0216B9C0
	ldr r0, [r6, #0x24]
	and r0, r0, #2
	orrs r0, r0, #8
	beq _0216B9C0
	add r1, sp, #0
	mov r0, r6
	bl SailObject__Func_2165A9C
	add r1, sp, #0
	add r0, r6, #0x44
	mov r2, r1
	bl VEC_Subtract
	ldr r0, [r6, #0x24]
	tst r0, #2
	beq _0216B970
	tst r0, #4
	beq _0216B88C
	bl SailManager__GetShipType
	cmp r0, #3
	ldr r0, [r6, #0x138]
	add r2, r6, #0x44
	bne _0216B884
	mov r1, #0x50
	bl SailAudio__PlaySpatialSequence
	b _0216B88C
_0216B884:
	mov r1, #0x28
	bl SailAudio__PlaySpatialSequence
_0216B88C:
	add r0, sp, #0
	bl EffectSailBomb__Create
	ldr r1, [r4, #0x50]
	cmp r1, #0x3000
	ble _0216B8CC
	ldr r2, [r0, #0x38]
	sub r1, r1, #0x2000
	smull r3, r1, r2, r1
	adds r2, r3, #0x800
	adc r1, r1, #0
	mov r5, r2, lsr #0xc
	orr r5, r5, r1, lsl #20
	str r5, [r0, #0x38]
	str r5, [r0, #0x3c]
	str r5, [r0, #0x40]
	b _0216B900
_0216B8CC:
	cmp r1, #0x1000
	ble _0216B900
	ldr r2, [r0, #0x38]
	sub r1, r1, #0x800
	smull r3, r1, r2, r1
	adds r2, r3, #0x800
	adc r1, r1, #0
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #20
	mov r5, r2, asr #1
	str r5, [r0, #0x38]
	str r5, [r0, #0x3c]
	str r5, [r0, #0x40]
_0216B900:
	ldr r1, [r6, #0x24]
	tst r1, #0x20000
	beq _0216B970
	mov r1, #0x2e00
	umull r4, r3, r5, r1
	mov r2, #0
	mla r3, r5, r2, r3
	mov r2, r5, asr #0x1f
	mla r3, r2, r1, r3
	adds r4, r4, #0x800
	adc r1, r3, #0
	mov r2, r4, lsr #0xc
	orr r2, r2, r1, lsl #20
	str r2, [r0, #0x38]
	str r2, [r0, #0x3c]
	str r2, [r0, #0x40]
	bl SailManager__GetShipType
	cmp r0, #3
	ldr r0, [r6, #0x138]
	add r2, r6, #0x44
	bne _0216B960
	mov r1, #0x51
	bl SailAudio__PlaySpatialSequence
	b _0216B968
_0216B960:
	mov r1, #0x29
	bl SailAudio__PlaySpatialSequence
_0216B968:
	add r0, r6, #0x44
	bl EffectSailUnknown21625C8__Create
_0216B970:
	ldr r0, [r6, #0x24]
	tst r0, #8
	beq _0216B9B4
	add r0, sp, #0
	bl EffectSailWater06__Create
	ldr r3, [r0, #0x38]
	mov r1, #0x800
	mov r2, r3, asr #0x1f
	mov r2, r2, lsl #0xd
	adds r4, r1, r3, lsl #13
	orr r2, r2, r3, lsr #19
	adc r1, r2, #0
	mov r2, r4, lsr #0xc
	orr r2, r2, r1, lsl #20
	str r2, [r0, #0x38]
	str r2, [r0, #0x3c]
	str r2, [r0, #0x40]
_0216B9B4:
	ldr r0, [r6, #0x20]
	orr r0, r0, #0x20
	str r0, [r6, #0x20]
_0216B9C0:
	ldr r0, [r6, #0x2c]
	cmp r0, #0
	bge _0216B9F4
	ldr r0, [r6, #0x24]
	tst r0, #4
	mov r0, r6
	bne _0216B9E4
	bl SailObject__CreateRingsForExplode1
	b _0216B9E8
_0216B9E4:
	bl SailObject__CreateRingsForExplode2
_0216B9E8:
	ldr r0, [r6, #0x18]
	orr r0, r0, #4
	str r0, [r6, #0x18]
_0216B9F4:
	ldr r0, [r6, #0x2c]
	sub r0, r0, #1
	str r0, [r6, #0x2c]
	add sp, sp, #0xc
	ldmia sp!, {r3, r4, r5, r6, pc}

// clang-format on
#endif
}

void SailBuoy__SetupObject(StageTask *work)
{
    SailObject *worker = GetStageTaskWorker(work, SailObject);

    switch (work->userWork)
    {
        // case 0:
        default:
            worker->field_138.x = FX32_FROM_WHOLE(GX_COLOR_FROM_888(0x60));
            worker->field_138.y = FX32_FROM_WHOLE(GX_COLOR_FROM_888(0xF8));
            worker->field_138.z = FX32_FROM_WHOLE(GX_COLOR_FROM_888(0x60));

            worker->field_144.x = FX32_FROM_WHOLE(GX_COLOR_FROM_888(0x40));
            worker->field_144.y = FX32_FROM_WHOLE(GX_COLOR_FROM_888(0xA0));
            worker->field_144.z = FX32_FROM_WHOLE(GX_COLOR_FROM_888(0x40));
            break;

        case 1:
            worker->field_138.x = FX32_FROM_WHOLE(GX_COLOR_FROM_888(0xF8));
            worker->field_138.y = FX32_FROM_WHOLE(GX_COLOR_FROM_888(0x50));
            worker->field_138.z = FX32_FROM_WHOLE(GX_COLOR_FROM_888(0x28));

            worker->field_144.x = FX32_FROM_WHOLE(GX_COLOR_FROM_888(0x38));
            worker->field_144.y = FX32_FROM_WHOLE(GX_COLOR_FROM_888(0x10));
            worker->field_144.z = FX32_FROM_WHOLE(GX_COLOR_FROM_888(0x000));
            break;

        case 2:
            worker->field_138.x = FX32_FROM_WHOLE(GX_COLOR_FROM_888(0xF8));
            worker->field_138.y = FX32_FROM_WHOLE(GX_COLOR_FROM_888(0xF8));
            worker->field_138.z = FX32_FROM_WHOLE(GX_COLOR_FROM_888(0xF8));

            worker->field_144.x = FX32_FROM_WHOLE(GX_COLOR_FROM_888(0x28));
            worker->field_144.y = FX32_FROM_WHOLE(GX_COLOR_FROM_888(0x40));
            worker->field_144.z = FX32_FROM_WHOLE(GX_COLOR_FROM_888(0x50));
            break;
    }

    SetTaskState(work, SailBuoy__State_216BAC0);

    work->userTimer = 0;
    work->userWork  = 0;
}

void SailBuoy__State_216BAC0(StageTask *work)
{
    SailObject *worker = GetStageTaskWorker(work, SailObject);

    if (work->userWork == 0)
    {
        work->userTimer += FLOAT_TO_FX32(0.125);
        if (work->userTimer >= FLOAT_TO_FX32(1.0))
        {
            work->userTimer = FLOAT_TO_FX32(1.0);
            work->userWork ^= 1;
        }
    }
    else
    {
        work->userTimer -= FLOAT_TO_FX32(0.125);
        if (work->userTimer < FLOAT_TO_FX32(0.0))
        {
            work->userTimer = FLOAT_TO_FX32(0.0);
            work->userWork ^= 1;
        }
    }

    s32 emissionR = ObjAlphaSet(worker->field_138.x, worker->field_144.x, work->userTimer);
    s32 emissionG = ObjAlphaSet(worker->field_138.y, worker->field_144.y, work->userTimer);
    s32 emissionB = ObjAlphaSet(worker->field_138.z, worker->field_144.z, work->userTimer);

    GXRgb color = GX_RGB(FX32_TO_WHOLE(emissionR), FX32_TO_WHOLE(emissionG), FX32_TO_WHOLE(emissionB));

    NNS_G3dMdlSetMdlEmi(work->obj_3d->ani.renderObj.resMdl, 1, color);
    work->dir.y = worker->objectAngle;
    SailObject__ApplyRotation(work);
}

void SailSeagull__SetupObject(StageTask *work)
{
    SailObject *worker = GetStageTaskWorker(work, SailObject);

    SailVoyageManager *voyageManager = SailManager__GetWork()->voyageManager;
    SailVoyageSegment *voyageSegment = &voyageManager->segmentList[FX32_TO_WHOLE(worker->objectRadius.z) >> 7];

    SetTaskState(work, SailSeagull__State_216BD1C);

    if (voyageSegment->targetSeaAngle != 0)
    {
        s32 range = 0x300 + ObjDispRandRepeat(0x200);

        worker->field_17C.y = -64;
        worker->field_17C.x = MultiplyFX(range, SinFX(voyageSegment->targetSeaAngle));
        worker->field_17C.z = MultiplyFX(range, CosFX(voyageSegment->targetSeaAngle));
    }
    else
    {
        worker->field_17C.x = mtMathRandRange(-0x200, 0x200);
        worker->field_17C.y = -64;
        worker->field_17C.z = -ObjDispRandRepeat(0x400);
    }

    work->userTimer = 32;
    work->userWork  = 0;
}

void SailSeagull__State_216BD1C(StageTask *work)
{
    SailObject *worker = GetStageTaskWorker(work, SailObject);

    work->userTimer--;

    if (work->userWork != 0)
    {
        worker->field_17C.y = ObjSpdUpSet(worker->field_17C.y, 16, 128);
        if (work->userTimer < 0)
        {
            work->userTimer = 32;
            work->userWork  = 0;
        }
    }
    else
    {
        worker->field_17C.y = ObjSpdUpSet(worker->field_17C.y, -16, 64);
        if (work->userTimer < 0)
        {
            work->userTimer = 32;
            work->userWork  = 1;
        }
    }

    SailObject__Func_2166A2C(work);
}

void SailSeagull2__SetupObject(StageTask *work)
{
    SailObject *worker = GetStageTaskWorker(work, SailObject);

    SailVoyageManager *voyageManager = SailManager__GetWork()->voyageManager;
    SailVoyageSegment *voyageSegment = &voyageManager->segmentList[FX32_TO_WHOLE(worker->objectRadius.z) >> 7];

    SetTaskState(work, SailSeagull2__State_216BF04);

    if (voyageSegment->targetSeaAngle != 0)
    {
        s32 range = 0x300 + ObjDispRandRepeat(0x200);

        worker->field_17C.y = 16;
        worker->field_17C.x = MultiplyFX(range, SinFX(voyageSegment->targetSeaAngle));
        worker->field_17C.z = MultiplyFX(range, CosFX(voyageSegment->targetSeaAngle));
    }
    else
    {
        worker->field_17C.x = mtMathRandRange(-0x100, 0x100);
        worker->field_17C.y = 16;

        worker->field_17C.z = -(ObjDispRandRepeat(0x40) + 128);
    }
}

void SailSeagull2__State_216BF04(StageTask *work)
{
    SailObject *worker = GetStageTaskWorker(work, SailObject);

    work->dir.y = worker->objectAngle;

    SailObject__ApplyRotation(work);
    SailObject__Func_2166A2C(work);
}

void SailSeagull3__State_216BF2C(StageTask *work)
{
    SailObject *worker = GetStageTaskWorker(work, SailObject);

    SetTaskState(work, SailSeagull3__State_216C03C);

    work->parentOffset.x = 4 * ObjDispRandRange(-FLOAT_TO_FX32(2.0), FLOAT_TO_FX32(2.0));
    work->parentOffset.y -= FLOAT_TO_FX32(6.0) + ObjDispRandRepeat(FLOAT_TO_FX32(4.0));
    work->parentOffset.z = 4 * ObjDispRandRange(-FLOAT_TO_FX32(2.0), FLOAT_TO_FX32(2.0));

    // TODO: clean this up
    worker->field_134 = 639 - ObjDispRandRepeat(0x100 - 1);
    work->userTimer   = 207 - ObjDispRandRepeat(0x20 - 1);

    work->dir.y = ObjDispRand();
}

void SailSeagull3__State_216C03C(StageTask *work)
{
    SailObject *worker = GetStageTaskWorker(work, SailObject);

    StageTask *parent        = work->parentObj;
    SailObject *parentWorker = GetStageTaskWorker(parent, SailObject);

    work->position = parentWorker->field_10;

    fx32 scale    = FX_Div(parent->scale.x, 1024);
    work->scale.x = scale;
    work->scale.y = work->scale.x;
    work->scale.z = work->scale.x;
    NNS_G3dMdlSetMdlAlphaAll(work->obj_3d->ani.renderObj.resMdl, parent->obj_2dIn3d->ani.polygonAttr.alpha);

    work->userWork--;
    work->velocity.y = _0218BC64[(work->userWork >> 2) & 0x7] >> 2;

    work->dir.y += work->userTimer;

    work->velocity.x = MultiplyFX(worker->field_134, SinFX(work->dir.y));
    work->velocity.z = MultiplyFX(worker->field_134, CosFX(work->dir.y));
    VEC_Add(&work->parentOffset, &work->velocity, &work->parentOffset);

    work->offset = work->parentOffset;

    SailObject__ApplyRotation(work);
}

void SailSubFish__SetupObject(StageTask *work)
{
    SetTaskState(work, SailSubFish__State_216C1E8);
    work->userTimer = 0;

    work->userWork = ObjDispRandRepeat(64) + 6;
    work->dir.y    = ObjDispRandRange(-FLOAT_DEG_TO_IDX(90.0), FLOAT_DEG_TO_IDX(90.0));
}

void SailSubFish__State_216C1E8(StageTask *work)
{
    SailObject *worker = GetStageTaskWorker(work, SailObject);

    work->userWork--;
    if (work->userWork == 0)
        work->userTimer = 1;

    if (work->userTimer != 0)
    {
        if (work->dir.y > FLOAT_DEG_TO_IDX(180.0))
            work->dir.y = ObjRoopMove16(work->dir.y, FLOAT_DEG_TO_IDX(270.0), FLOAT_DEG_TO_IDX(2.8125));
        else
            work->dir.y = ObjRoopMove16(work->dir.y, FLOAT_DEG_TO_IDX(90.0), FLOAT_DEG_TO_IDX(2.8125));
    }

    worker->field_17C.y += _0218BC64[(work->userWork >> 2) & 0x7] >> 1;

    worker->field_17C.x = MultiplyFX(FLOAT_TO_FX32(0.75), SinFX(work->dir.y));
    worker->field_17C.z = MultiplyFX(FLOAT_TO_FX32(0.75), CosFX(work->dir.y));
    SailObject__Func_2166A2C(work);

    u16 angleY  = work->dir.y;
    work->dir.y = -angleY;
    SailObject__ApplyRotation(work);
    work->dir.y = angleY;
}

void SailSubFish2__SetupObject(StageTask *work)
{
    SetTaskState(work, SailSubFish2__State_216C458);

    work->userTimer = ObjDispRandRepeat(128);
    work->userWork  = ObjDispRandRepeat(64) + 6;

    work->parentOffset.x = 16 * ObjDispRandRange(-FLOAT_TO_FX32(1.0), FLOAT_TO_FX32(1.0));
    work->parentOffset.y -= ObjDispRandRepeat(FLOAT_TO_FX32(8.0));
    work->parentOffset.z -= ObjDispRandRepeat(FLOAT_TO_FX32(4.0));

    if (ObjDispRandRepeat(2) != 0)
        work->dir.y = FLOAT_DEG_TO_IDX(90.0);
    else
        work->dir.y = -FLOAT_DEG_TO_IDX(90.0);

    work->dir.y = ObjDispRandRange(-FLOAT_TO_FX32(0.25), FLOAT_TO_FX32(0.25));
}

void SailSubFish2__State_216C458(StageTask *work)
{
    SailObject *worker = GetStageTaskWorker(work, SailObject);

    StageTask *parent        = work->parentObj;
    SailObject *parentWorker = GetStageTaskWorker(parent, SailObject);

    work->position = parentWorker->field_10;

    fx32 scale    = FX_Div(parent->scale.x, FLOAT_TO_FX32(0.25));
    work->scale.x = scale;
    work->scale.y = work->scale.x;
    work->scale.z = work->scale.x;

    work->userWork--;
    work->userTimer++;

    work->velocity.y  = _0218BC64[(work->userWork >> 2) & 0x7];
    worker->field_134 = 2 * _0218BC64[(work->userTimer >> 3) & 0x7];

    work->velocity.x = MultiplyFX(worker->field_134, CosFX(work->dir.y));
    work->velocity.z = MultiplyFX(worker->field_134, SinFX(work->dir.y));
    VEC_Add(&work->parentOffset, &work->velocity, &work->parentOffset);

    work->offset = work->parentOffset;

    SailObject__ApplyRotation(work);
}

void SailChaosEmerald__SetupObject(StageTask *work)
{
    SailObject *worker = GetStageTaskWorker(work, SailObject);

    worker->player = SailManager__GetWork()->sailPlayer;
    SetTaskState(work, SailChaosEmerald__State_216C5B0);
    work->userTimer = 0;
    work->userWork  = 0;
}

void SailChaosEmerald__State_216C5B0(StageTask *work)
{
    SailObject *worker = GetStageTaskWorker(work, SailObject);

    SailVoyageManager *voyageManager = SailManager__GetWork()->voyageManager;
    SailManager *manager             = SailManager__GetWork();

    worker->field_17C.y = _0218BC64[(work->userTimer >> 2) & 0x7] >> 2;
    work->userTimer++;

    SailObject__Func_2166A2C(work);
    work->dir.y = worker->objectAngle;
    SailObject__ApplyRotation(work);

    if ((manager->flags & SAILMANAGER_FLAG_8) == 0)
    {
        if (voyageManager->voyagePos > worker->objectRadius.z)
        {
            SailChaosEmerald__Func_216C650(work);
        }
    }
    else
    {
        work->displayFlag |= DISPLAY_FLAG_NO_DRAW;
    }
}

void SailChaosEmerald__Func_216C650(StageTask *work)
{
    SailObject *worker = GetStageTaskWorker(work, SailObject);

    worker->player      = SailManager__GetWork()->sailPlayer;
    worker->field_17C.y = 0;
    SetTaskState(work, SailChaosEmerald__State_216C69C);
    work->userTimer = 0;
    work->userWork  = 0;

    gameState.saveFile.chaosEmeraldID = SailManager__GetWork()->rivalRaceID;
}

void SailChaosEmerald__State_216C69C(StageTask *work)
{
    SailObject *worker = GetStageTaskWorker(work, SailObject);

    SailVoyageManager *voyageManager = SailManager__GetWork()->voyageManager;
    UNUSED(voyageManager);

    if (worker->player != NULL)
    {
        MtxFx33 mtx;
        VecFx32 offset;

        offset.x = -FLOAT_TO_FX32(0.25);
        offset.y = -FLOAT_TO_FX32(1.0625);
        offset.z = FLOAT_TO_FX32(0.0);
        MTX_RotY33(&mtx, SinFX(worker->player->dir.y), CosFX(worker->player->dir.y));
        MTX_MultVec33(&offset, &mtx, &offset);

        work->position.x = ObjShiftSet(work->position.x, worker->player->position.x + offset.x, 1, FLOAT_TO_FX32(0.0), FLOAT_TO_FX32(2.0));
        work->position.y = ObjShiftSet(work->position.y, worker->player->position.y + offset.y, 1, FLOAT_TO_FX32(0.0), FLOAT_TO_FX32(2.0));
        work->position.z = ObjShiftSet(work->position.z, worker->player->position.z + offset.z, 1, FLOAT_TO_FX32(0.0), FLOAT_TO_FX32(2.0));
    }
}

void SailGoal__SetupObject(StageTask *work)
{
    SailObject *worker = GetStageTaskWorker(work, SailObject);

    worker->player = SailManager__GetWork()->sailPlayer;
    SetTaskState(work, SailGoal__State_216C7E0);
    work->userTimer = 0;
    work->userWork  = 0;
}

void SailGoal__State_216C7E0(StageTask *work)
{
    SailObject *worker = GetStageTaskWorker(work, SailObject);

    SailVoyageManager *voyageManager = SailManager__GetWork()->voyageManager;
    SailManager *manager             = SailManager__GetWork();

    worker->field_17C.y = _0218BC64[(work->userTimer >> 2) & 0x7] >> 2;
    work->userTimer++;

    SailObject__Func_2166A2C(work);
    work->dir.y = worker->objectAngle;
    SailObject__ApplyRotation(work);

    if (voyageManager->voyagePos > worker->objectRadius.z)
    {
        fx32 scale = ObjShiftSet(work->scale.x, FLOAT_TO_FX32(8.0), 1, FLOAT_TO_FX32(1.0), FLOAT_TO_FX32(0.0625));
        if (!work->userWork)
        {
            work->userWork = 1;
            scale          = FLOAT_TO_FX32(1.0);
        }

        work->scale.x = scale;
        work->scale.y = scale;
        work->scale.z = scale;

        if (scale == FLOAT_TO_FX32(8.0))
            DestroyStageTask(work);
    }

    if (manager->isRivalRace)
    {
        if ((manager->flags & SAILMANAGER_FLAG_8) != 0)
            work->displayFlag |= DISPLAY_FLAG_NO_DRAW;
    }
}

void SailGoalText__SetupObject(StageTask *work)
{
    SailObject *worker = GetStageTaskWorker(work, SailObject);

    worker->player = SailManager__GetWork()->sailPlayer;
    SetTaskState(work, SailGoalText__State_216C8F8);
    work->userTimer = 0;
}

void SailGoalText__State_216C8F8(StageTask *work)
{
    SailObject *worker = GetStageTaskWorker(work, SailObject);

    SailVoyageManager *voyageManager = SailManager__GetWork()->voyageManager;

    worker->field_17C.y = _0218BC64[(work->userTimer >> 2) & 0x7] >> 2;
    work->userTimer++;

    SailObject__Func_2166A2C(work);

    if (voyageManager->voyagePos > work->userWork)
        DestroyStageTask(work);
}

void SailItemBonus__GiveItem(StageTask *work, StageTask *object)
{
    StageTask *player;
    SailPlayer *playerWorker;

    u32 score = 0;

    player = object;
    if (object->objType != SAILSTAGE_OBJ_TYPE_PLAYER)
    {
        if (player->parentObj == NULL)
            return;

        player = object->parentObj;
        if (player->objType != SAILSTAGE_OBJ_TYPE_PLAYER)
            return;
    }

    playerWorker = GetStageTaskWorker(player, SailPlayer);

    SailAudio__PlaySpatialSequence(work->sequencePlayerPtr, SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_ITEM, &work->position);

    switch (work->userWork)
    {
        default: // repair 25%
            SailPlayer__AddHealth(player, SAILPLAYER_HEALTH_MAX * 0.25f);
            break;

        case 1: // repair 50%
            SailPlayer__AddHealth(player, SAILPLAYER_HEALTH_MAX * 0.5f);
            break;

        case 2:                                                               // repair 75%
            SailPlayer__AddHealth(player, SAILPLAYER_HEALTH_MAX * 0.765625f); // 75%, but rounded up to a clean number in fixed-12
            break;

        case 3: // repair 100%
            SailPlayer__AddHealth(player, SAILPLAYER_HEALTH_MAX * 1.0f);
            break;

        case 4: // boost 10%
            SailAudio__PlaySpatialSequence(NULL, SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_TRICK_SUC, &work->position);
            // desite saying "boost 10%", it appears they used the "HEALTH_MAX" value instead of "BOOST_MAX" one.
            // because of this you won't get 10% boost, you'll get 10% of the max health added to the boost gauge instead!
            SailPlayer__GiveBoost(player, SAILPLAYER_HEALTH_MAX * 0.09765625); // 10%, but rounded down to a clean number in fixed-12
            break;

        case 5: // boost 20%
            SailAudio__PlaySpatialSequence(NULL, SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_TRICK_SUC, &work->position);
            // desite saying "boost 20%", it appears they used the "HEALTH_MAX" value instead of "BOOST_MAX" one.
            // because of this you won't get 20% boost, you'll get 20% of the max health added to the boost gauge instead!
            SailPlayer__GiveBoost(player, SAILPLAYER_HEALTH_MAX * 0.1953125); // 20%, but rounded down to a clean number in fixed-12
            break;

        case 6: // boost 50%
            SailAudio__PlaySpatialSequence(NULL, SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_TRICK_SUC, &work->position);
            // desite saying "boost 50%", it appears they used the "HEALTH_MAX" value instead of "BOOST_MAX" one.
            // because of this you won't get 50% boost, you'll get 50% of the max health added to the boost gauge instead!
            SailPlayer__GiveBoost(player, SAILPLAYER_HEALTH_MAX * 0.5f);
            break;

        case 7: // boost 100%
            SailAudio__PlaySpatialSequence(NULL, SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_TRICK_SUC, &work->position);
            // desite saying "boost 100%", it appears they used the "HEALTH_MAX" value instead of "BOOST_MAX" one.
            // because of this you won't get 100% boost, you'll get 100% of the max health added to the boost gauge instead!
            SailPlayer__GiveBoost(player, SAILPLAYER_HEALTH_MAX * 1.0f);
            break;

        case 8: // 10 rings
            SailAudio__PlaySpatialSequence(NULL, SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_RING, &work->position);
            playerWorker->rings += 10;
            break;

        case 9: // 20 rings
            SailAudio__PlaySpatialSequence(NULL, SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_RING, &work->position);
            playerWorker->rings += 20;
            break;

        case 10: // 30 rings
            SailAudio__PlaySpatialSequence(NULL, SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_RING, &work->position);
            playerWorker->rings += 30;
            break;

        case 11: // 50 rings
            SailAudio__PlaySpatialSequence(NULL, SND_SAIL_SEQARC_ARC_VOYAGE_SE_SEQ_SE_RING, &work->position);
            playerWorker->rings += 50;
            break;

        case 12: // 1000 score
            score = 1000;
            break;

        case 13: // 2000 score
            score = 2000;
            break;

        case 14: // 5000 score
            score = 5000;
            break;

        case 15: // 8000 score
            score = 8000;
            break;
    }

    if (playerWorker->rings > SAILPLAYER_MAX_RINGS)
        playerWorker->rings = SAILPLAYER_MAX_RINGS;

    if (score != 0)
    {
        u16 multiplier = 1;
        multiplier += FX_DivS32(playerWorker->scoreComboCurrent, 50);

        playerWorker->score += score * multiplier;
        if (playerWorker->score > SAILPLAYER_MAX_SCORE)
            playerWorker->score = SAILPLAYER_MAX_SCORE;
    }

    SailItemBonus__Create(work, work->userWork);

    if (SailManager__GetShipType() == SHIP_BOAT || SailManager__GetShipType() == SHIP_SUBMARINE)
        EffectSailBomb__Create(&work->position);

    work->flag |= STAGE_TASK_FLAG_NO_OBJ_COLLISION;
    QueueDestroyStageTask(work);
}

void SailItemBonus__State_216CBF8(StageTask *work)
{
    if (work->userTimer > 6)
        work->velocity.y = ObjSpdDownSet(work->velocity.y, FLOAT_TO_FX32(0.046875));

    if (work->userTimer > 30)
    {
        if ((work->userTimer & 1) != 0)
            work->displayFlag |= DISPLAY_FLAG_NO_DRAW;
        else
            work->displayFlag &= ~DISPLAY_FLAG_NO_DRAW;
    }

    if (work->userTimer > 64)
        DestroyStageTask(work);

    work->userTimer++;
}