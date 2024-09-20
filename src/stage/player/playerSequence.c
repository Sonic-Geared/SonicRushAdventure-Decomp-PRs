#include <stage/player/player.h>
#include <stage/gameObject.h>
#include <game/system/allocator.h>
#include <game/input/padInput.h>
#include <game/object/obj.h>
#include <game/object/objPacket.h>
#include <game/math/mtMath.h>
#include <game/system/system.h>
#include <game/game/gameState.h>
#include <game/audio/spatialAudio.h>
#include <game/object/objectManager.h>
#include <game/graphics/paletteQueue.h>
#include <game/stage/gameSystem.h>
#include <game/stage/mapSys.h>
#include <game/system/sysEvent.h>
#include <stage/core/bgmManager.h>
#include <stage/core/ringManager.h>
#include <stage/core/hud.h>
#include <game/graphics/drawFadeTask.h>
#include <game/graphics/screenShake.h>

// Related Objects
#include <stage/player/starCombo.h>
#include <stage/player/scoreBonus.h>
#include <stage/objects/playerSnowboard.h>

// Effects
#include <stage/effects/buttonPrompt.h>
#include <stage/effects/waterSplash.h>
#include <stage/effects/waterWake.h>
#include <stage/effects/waterGush.h>
#include <stage/effects/waterBubble.h>
#include <stage/effects/brakeDust.h>
#include <stage/effects/spindashDust.h>
#include <stage/effects/flameDust.h>
#include <stage/effects/flameJet.h>
#include <stage/effects/hummingTop.h>
#include <stage/effects/boost.h>
#include <stage/effects/playerTrail.h>
#include <stage/effects/shield.h>
#include <stage/effects/grind.h>
#include <stage/effects/trickSparkle.h>
#include <stage/effects/invincible.h>
#include <stage/effects/snowSmoke.h>
#include <stage/effects/drownAlert.h>
#include <stage/effects/playerIcon.h>
#include <stage/effects/battleAttack.h>

// Gimmick Objects
#include <stage/objects/jumpbox.h>
#include <stage/objects/hoverCrystal.h>

// --------------------
// TEMP
// --------------------

// TODO: SOME OF THESE FUNC SIGNATURES AREN'T RIGHT... decompile them
NOT_DECOMPILED void DiveStand__Func_2169F6C(void);
NOT_DECOMPILED void CannonPath__GetOffsetZ(void);
NOT_DECOMPILED void Grind3LineRingLoss__Create(Player *player);

NOT_DECOMPILED void _s32_div_f(void);

// --------------------
// INLINE FUNCTIONS
// --------------------

// extra macro for specific cases where the inline function won't match!
#define PlayPlayerSfxEx(seqPlayer, sfx) PlaySfxEx(seqPlayer, AUDIOMANAGER_PLAYERNO_AUTO, AUDIOMANAGER_BANKNO_AUTO, AUDIOMANAGER_PLAYERPRIO_AUTO, SND_ZONE_SEQARC_GAME_SE, sfx)

// --------------------
// FUNCTIONS
// --------------------

void Player__Action_StageStartSnowboard(Player *player)
{
    Player__ChangeAction(player, PLAYER_ACTION_IDLE_SNOWBOARD);
    ChangePlayerSnowboardAction(player, PLAYERSNOWBOARD_ACTION_IDLE);

    player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;
    player->objWork.moveFlag &= ~STAGE_TASK_MOVE_FLAG_IN_AIR;
    SetTaskState(&player->objWork, Player__State_StageStartSnowboard);
}

void Player__State_StageStartSnowboard(Player *work)
{
    // Empty
}

void Player__Action_Spring(Player *player, fx32 velX, fx32 velY)
{
    Player__Gimmick_Jump(player, velX, velY);
    PlayPlayerSfx(player, PLAYER_SEQPLAYER_COMMON, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_SPRING);
}

void Player__Gimmick_Jump(Player *player, fx32 velX, fx32 velY)
{
    if ((player->playerFlag & PLAYER_FLAG_DEATH) == 0)
    {
        Player__InitGimmick(player, TRUE);

        if ((player->objWork.moveFlag & STAGE_TASK_MOVE_FLAG_TOUCHING_FLOOR) != 0)
            player->objWork.velocity.x = player->objWork.groundVel;

        Player__Action_LandOnGround(player, FLOAT_DEG_TO_IDX(0.0));
        StageTask__ObjectSpdDirFall(&velX, &velY, player->objWork.fallDir);

        if ((player->objWork.moveFlag & STAGE_TASK_MOVE_FLAG_IN_AIR) == 0)
            player->cameraJumpPosY = player->objWork.position.y;

        player->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_DISABLE_SLOPE_ANGLES | STAGE_TASK_MOVE_FLAG_IN_AIR;
        player->objWork.moveFlag &= ~STAGE_TASK_MOVE_FLAG_TOUCHING_FLOOR;
        SetTaskState(&player->objWork, Player__State_Air);

        if (velX != 0)
        {
            if ((player->gimmickFlag & PLAYER_GIMMICK_SNOWBOARD) == 0)
            {
                Player__ChangeAction(player, PLAYER_ACTION_AIRFORWARD_01);
            }
            else
            {
                Player__ChangeAction(player, PLAYER_ACTION_AIRFORWARD_SNOWBOARD_01);
                ChangePlayerSnowboardAction(player, PLAYERSNOWBOARD_ACTION_10);
            }

            player->objWork.velocity.x = velX;
            if (player->objWork.velocity.x < 0)
            {
                if (player->objWork.groundVel > 0)
                    player->objWork.groundVel = 0;

                player->objWork.displayFlag |= DISPLAY_FLAG_FLIP_X;
            }
            else
            {
                if (player->objWork.groundVel < 0)
                    player->objWork.groundVel = 0;

                player->objWork.displayFlag &= ~DISPLAY_FLAG_FLIP_X;
            }

            player->overSpeedLimitTimer = 64;
        }
        else
        {
            if ((player->gimmickFlag & PLAYER_GIMMICK_SNOWBOARD) == 0)
            {
                Player__ChangeAction(player, PLAYER_ACTION_AIRRISE);
            }
            else
            {
                Player__ChangeAction(player, PLAYER_ACTION_AIRRISE_SNOWBOARD);
                ChangePlayerSnowboardAction(player, PLAYERSNOWBOARD_ACTION_AIRRISE);
            }

            player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;
            player->objWork.velocity.x = MultiplyFX(player->objWork.groundVel, CosFX(player->objWork.dir.z));
        }

        if (velY)
            player->objWork.velocity.y = velY;
        else
            player->objWork.velocity.y = MultiplyFX(player->objWork.groundVel, SinFX(player->objWork.dir.z));
        ObjRect__SetAttackStat(&player->colliders[1], 0, 0);
        player->playerFlag &= ~(PLAYER_FLAG_DISABLE_TRICK_FINISHER | PLAYER_FLAG_FINISHED_TRICK_COMBO | PLAYER_FLAG_ALLOW_TRICKS | PLAYER_FLAG_USER_FLAG);
        player->playerFlag |= PLAYER_FLAG_ALLOW_TRICKS | PLAYER_FLAG_USER_FLAG;
        player->objWork.userTimer  = 0;
        player->objWork.userWork   = 0;
        player->trickCooldownTimer = 0;

        if ((player->playerFlag & PLAYER_FLAG_IN_WATER) != 0)
        {
            if (!IsBossStage())
                player->objWork.velocity.x = (player->objWork.velocity.x >> 1) + (player->objWork.velocity.x >> 2);

            if (!IsBossStage())
                player->objWork.velocity.y = (player->objWork.velocity.y >> 1) + (player->objWork.velocity.y >> 2);

            CreateEffectWaterBubbleForPlayer(player, FLOAT_TO_FX32(0.0), FLOAT_TO_FX32(0.0), mapCamera.camera[player->cameraID].waterLevel);
        }
    }
}

void Player__Gimmick_201B418(Player *player, fx32 velX, fx32 velY, BOOL allowTricks)
{
    if ((player->playerFlag & PLAYER_FLAG_DEATH) != 0)
        return;

    Player__InitPhysics(player);
    Player__InitGimmick(player, allowTricks);
    if ((player->gimmickFlag & PLAYER_GIMMICK_SNOWBOARD) == 0)
    {
        Player__ChangeAction(player, PLAYER_ACTION_HOMING_ATTACK);
        player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;
    }
    else
    {
        Player__ChangeAction(player, PLAYER_ACTION_JUMP_SNOWBOARD_01);
        ChangePlayerSnowboardAction(player, PLAYERSNOWBOARD_ACTION_JUMP_01);
    }

    player->objWork.moveFlag &= ~STAGE_TASK_MOVE_FLAG_TOUCHING_FLOOR;
    player->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_DISABLE_SLOPE_ANGLES | STAGE_TASK_MOVE_FLAG_IN_AIR;
    player->objWork.velocity.x = velX;
    player->objWork.velocity.y = velY;
    ObjRect__SetAttackStat(&player->colliders[1], 2, PLAYER_HITPOWER_NORMAL);
    player->playerFlag &= ~(PLAYER_FLAG_DISABLE_TRICK_FINISHER | PLAYER_FLAG_FINISHED_TRICK_COMBO | PLAYER_FLAG_ALLOW_TRICKS | PLAYER_FLAG_USER_FLAG);
    player->playerFlag |= PLAYER_FLAG_ALLOW_TRICKS | PLAYER_FLAG_USER_FLAG;
    player->objWork.userTimer  = 0;
    player->objWork.userWork   = 0;
    player->trickCooldownTimer = 0;

    if (!allowTricks)
    {
        player->playerFlag &= ~PLAYER_FLAG_ALLOW_TRICKS;
        player->starComboCount = 0;
    }

    SetTaskState(&player->objWork, Player__State_Air);
}

void Player__Gimmick_201B500(Player *player, GameObjectTask *other, fx32 offsetX, fx32 offsetY, fx32 offsetZ)
{
    if (player->gimmickObj != other)
    {
        Player__InitPhysics(player);
        Player__InitGimmick(player, FALSE);

        player->gimmickObj = other;
        player->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_IN_AIR | STAGE_TASK_MOVE_FLAG_DISABLE_SLOPE_ANGLES | STAGE_TASK_MOVE_FLAG_DISABLE_MOVE_EVENT;
        player->objWork.moveFlag &= ~(STAGE_TASK_MOVE_FLAG_HAS_GRAVITY | STAGE_TASK_MOVE_FLAG_USE_SLOPE_FORCES);
        player->objWork.displayFlag &= ~DISPLAY_FLAG_APPLY_CAMERA_CONFIG;
        player->objWork.userFlag = 0;
        player->playerFlag &= ~(PLAYER_FLAG_DISABLE_TRICK_FINISHER | PLAYER_FLAG_FINISHED_TRICK_COMBO | PLAYER_FLAG_ALLOW_TRICKS | PLAYER_FLAG_USER_FLAG);
        player->playerFlag |= PLAYER_FLAG_DISABLE_TENSION_DRAIN;
        player->objWork.velocity.x = FLOAT_TO_FX32(0.0);
        player->objWork.velocity.y = FLOAT_TO_FX32(0.0);
        player->objWork.groundVel  = FLOAT_TO_FX32(0.0);
        player->objWork.userWork   = 0;
        player->objWork.userTimer  = 0;
        player->gimmickValue1      = offsetX;
        player->gimmickValue2      = offsetY;
        player->gimmickValue3      = offsetZ;

        SetTaskState(&player->objWork, Player__State_201B5A0);
    }
}

void Player__State_201B5A0(Player *work)
{
    GameObjectTask *gimmickObj = work->gimmickObj;

    if (gimmickObj != NULL)
    {
        work->objWork.prevPosition.x = work->objWork.position.x;
        work->objWork.prevPosition.y = work->objWork.position.y;
        work->objWork.prevPosition.z = work->objWork.position.z;

        if ((work->playerFlag & (PLAYER_FLAG_FINISHED_TRICK_COMBO | PLAYER_FLAG_ALLOW_TRICKS | PLAYER_FLAG_USER_FLAG)) != 0)
        {
            MtxFx33 matDirection;
            MtxFx33 matTemp;

            MTX_Identity33(&matDirection);

            if ((work->playerFlag & PLAYER_FLAG_DISABLE_TRICK_FINISHER) != 0)
            {
                MTX_RotZ33(&matDirection, SinFX(gimmickObj->objWork.dir.z), CosFX(gimmickObj->objWork.dir.z));
                work->objWork.dir.z = gimmickObj->objWork.dir.z;
            }

            if ((work->playerFlag & PLAYER_FLAG_USER_FLAG) != 0)
            {
                MTX_RotX33(&matTemp, SinFX(gimmickObj->objWork.dir.x), CosFX(gimmickObj->objWork.dir.x));
                work->objWork.dir.x = gimmickObj->objWork.dir.x;
                MTX_Concat33(&matDirection, &matTemp, &matDirection);
            }

            if ((work->playerFlag & PLAYER_FLAG_ALLOW_TRICKS) != 0)
            {
                MTX_RotY33(&matTemp, SinFX((s32)(u16)-gimmickObj->objWork.dir.y), CosFX((s32)(u16)-gimmickObj->objWork.dir.y));
                work->objWork.dir.y = gimmickObj->objWork.dir.y;
                MTX_Concat33(&matDirection, &matTemp, &matDirection);
            }

            if ((work->playerFlag & PLAYER_FLAG_FINISHED_TRICK_COMBO) != 0)
            {
                MTX_RotZ33(&matTemp, SinFX(gimmickObj->objWork.dir.z), CosFX(gimmickObj->objWork.dir.z));
                work->objWork.dir.z = gimmickObj->objWork.dir.z;
                MTX_Concat33(&matDirection, &matTemp, &matDirection);
            }

            VecFx32 offset;
            VEC_Set(&offset, work->gimmickValue1, work->gimmickValue2, work->gimmickValue3);
            MTX_MultVec33(&offset, &matDirection, &offset);

            if ((work->objWork.userFlag & 2) != 0)
            {
                VEC_Set(&work->objWork.position, gimmickObj->objWork.prevPosition.x + offset.x, gimmickObj->objWork.prevPosition.y + offset.y,
                        gimmickObj->objWork.prevPosition.z + offset.z);
            }
            else
            {
                VEC_Set(&work->objWork.position, gimmickObj->objWork.position.x + offset.x, gimmickObj->objWork.position.y + offset.y, gimmickObj->objWork.position.z + offset.z);
            }
        }
        else if ((work->objWork.userFlag & 2) != 0)
        {
            work->objWork.position.x = gimmickObj->objWork.prevPosition.x + work->gimmickValue1;
            work->objWork.position.y = gimmickObj->objWork.prevPosition.y + work->gimmickValue2;
            work->objWork.position.z = gimmickObj->objWork.prevPosition.z;
        }
        else
        {
            work->objWork.position.x = gimmickObj->objWork.position.x + work->gimmickValue1;
            work->objWork.position.y = gimmickObj->objWork.position.y + work->gimmickValue2;
            work->objWork.position.z = gimmickObj->objWork.position.z;
        }

        work->objWork.move.x = work->objWork.position.x - work->objWork.prevPosition.x;
        work->objWork.move.y = work->objWork.position.y - work->objWork.prevPosition.y;
        work->objWork.move.z = work->objWork.position.z - work->objWork.prevPosition.z;

        if ((work->objWork.userFlag & 0x40) != 0 && gimmickObj->objWork.shakeTimer != 0)
            work->objWork.shakeTimer = gimmickObj->objWork.shakeTimer + FLOAT_TO_FX32(1.0);

        if ((gimmickObj->objWork.userFlag & 1) != 0)
        {
            work->objWork.velocity.x = gimmickObj->objWork.velocity.x;
            work->objWork.velocity.y = gimmickObj->objWork.velocity.y;
            work->gimmickObj         = NULL;
        }
        else if ((gimmickObj->objWork.userFlag & 2) != 0)
        {
            work->objWork.velocity.x = gimmickObj->objWork.groundVel;
            work->gimmickObj         = NULL;
        }

        if ((gimmickObj->objWork.userFlag & 4) != 0)
        {
            work->objWork.velocity.x = work->objWork.move.x;
            work->objWork.velocity.y = work->objWork.move.y;
            work->gimmickObj         = NULL;
        }
    }

    if (work->gimmickObj == NULL || (work->objWork.userFlag & 1) != 0 && (work->inputKeyPress & PLAYER_INPUT_JUMP) != 0)
    {
        work->gimmickObj = NULL;

        work->objWork.moveFlag &= ~(STAGE_TASK_MOVE_FLAG_DISABLE_SLOPE_ANGLES | STAGE_TASK_MOVE_FLAG_DISABLE_MOVE_EVENT | STAGE_TASK_MOVE_FLAG_DISABLE_COLLIDE_EVENT)
                                  | STAGE_TASK_MOVE_FLAG_HAS_GRAVITY | STAGE_TASK_MOVE_FLAG_USE_SLOPE_FORCES;
        work->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_HAS_GRAVITY | STAGE_TASK_MOVE_FLAG_USE_SLOPE_FORCES;
        work->objWork.displayFlag |= DISPLAY_FLAG_APPLY_CAMERA_CONFIG;
        work->playerFlag &= ~(PLAYER_FLAG_2000 | PLAYER_FLAG_DISABLE_TENSION_DRAIN);
        work->gimmickFlag &= ~(PLAYER_GIMMICK_10 | PLAYER_GIMMICK_20 | PLAYER_GIMMICK_GRABBED);

        work->gimmickCamOffsetX = work->gimmickCamOffsetY = 0;
        work->objWork.dir.x = work->objWork.dir.y = work->objWork.dir.z = FLOAT_DEG_TO_IDX(0.0);

        StopPlayerSfx(work, PLAYER_SEQPLAYER_COMMON);

        u32 flag = work->objWork.userFlag;
        if ((flag & 1) != 0 && (work->inputKeyPress & PLAYER_INPUT_JUMP) != 0)
        {
            work->actionJump(work);
        }
        else if ((flag & 4) != 0)
        {
            fx32 velX = work->objWork.velocity.x;
            fx32 velY = work->objWork.velocity.y;
            work->actionJump(work);
            work->objWork.velocity.x = velX;
            work->objWork.velocity.y = velY;
        }
        else if ((flag & 8) != 0)
        {
            Player__Gimmick_Jump(work, work->objWork.velocity.x, work->objWork.velocity.y);

            if ((flag & 0x10) != 0)
                work->playerFlag |= PLAYER_FLAG_FINISHED_TRICK_COMBO;

            if ((flag & 0x20) != 0)
                work->playerFlag |= PLAYER_FLAG_DISABLE_TRICK_FINISHER;
        }
        else
        {
            Player__Action_LandOnGround(work, FLOAT_DEG_TO_IDX(0.0));
            work->onLandGround(work);
        }
    }
}

void Player__Action_DashRing(Player *player, fx32 x, fx32 y, fx32 velX, fx32 velY)
{
    player->gimmickFlag &= ~(PLAYER_GIMMICK_40 | PLAYER_GIMMICK_10);
    player->gimmickFlag &= ~(PLAYER_GIMMICK_80 | PLAYER_GIMMICK_20);

    MapSys__Func_20091D0(player->cameraID);
    MapSys__Func_20091F0(player->cameraID);
    player->objWork.dir.z = 0;

    if (x != 0)
        player->objWork.position.x = x;

    if (y != 0)
        player->objWork.position.y = y;

    Player__Gimmick_201BAC0(player, velX, velY);

    if (velX == 0)
        player->objWork.velocity.x = 0;

    player->overSpeedLimitTimer = 30;
    player->objWork.userTimer   = 30;
    player->objWork.moveFlag &= ~STAGE_TASK_MOVE_FLAG_HAS_GRAVITY;
}

NONMATCH_FUNC void Player__Gimmick_201BAC0(Player *player, fx32 velX, fx32 velY)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r0, r1, r2, r3}
	stmdb sp!, {r4, lr}
	mov r4, r0
	mov r1, #1
	bl Player__InitGimmick
	ldr r0, [r4, #0x1c]
	mov r1, #0
	tst r0, #1
	ldrne r0, [r4, #0xc8]
	strne r0, [r4, #0x98]
	mov r0, r4
	bl Player__Action_LandOnGround
	ldrh r2, [r4, #0xce]
	add r0, sp, #0xc
	add r1, sp, #0x10
	bl StageTask__ObjectSpdDirFall
	ldr r0, [r4, #0x1c]
	tst r0, #0x10
	ldreq r0, [r4, #0x48]
	streq r0, [r4, #0x6bc]
	ldr r1, [r4, #0x1c]
	ldr r0, =Player__State_Air
	orr r2, r1, #0x10
	orr r1, r2, #0x8000
	bic r1, r1, #1
	str r1, [r4, #0x1c]
	str r0, [r4, #0xf4]
	ldr r0, [sp, #0xc]
	cmp r0, #0
	ldr r0, [r4, #0x5dc]
	beq _0201BBC0
	tst r0, #0x800
	mov r0, r4
	bne _0201BB54
	mov r1, #0x19
	bl Player__ChangeAction
	b _0201BB68
_0201BB54:
	mov r1, #0x52
	bl Player__ChangeAction
	mov r0, r4
	mov r1, #0xb
	bl ChangePlayerSnowboardAction
_0201BB68:
	ldr r0, [r4, #0x20]
	orr r0, r0, #4
	str r0, [r4, #0x20]
	ldr r0, [sp, #0xc]
	str r0, [r4, #0x98]
	cmp r0, #0
	ldr r0, [r4, #0xc8]
	bge _0201BBA4
	cmp r0, #0
	movgt r0, #0
	strgt r0, [r4, #0xc8]
	ldr r0, [r4, #0x20]
	orr r0, r0, #1
	str r0, [r4, #0x20]
	b _0201BC30
_0201BBA4:
	cmp r0, #0
	movlt r0, #0
	strlt r0, [r4, #0xc8]
	ldr r0, [r4, #0x20]
	bic r0, r0, #1
	str r0, [r4, #0x20]
	b _0201BC30
_0201BBC0:
	tst r0, #0x800
	mov r0, r4
	bne _0201BBD8
	mov r1, #0x14
	bl Player__ChangeAction
	b _0201BBEC
_0201BBD8:
	mov r1, #0x4d
	bl Player__ChangeAction
	mov r0, r4
	mov r1, #7
	bl ChangePlayerSnowboardAction
_0201BBEC:
	ldr r1, [r4, #0x20]
	ldr r0, =FX_SinCosTable_
	orr r1, r1, #4
	str r1, [r4, #0x20]
	ldrh r1, [r4, #0x34]
	ldr r2, [r4, #0xc8]
	mov r1, r1, asr #4
	mov r1, r1, lsl #1
	add r1, r1, #1
	mov r1, r1, lsl #1
	ldrsh r0, [r0, r1]
	smull r1, r0, r2, r0
	adds r1, r1, #0x800
	adc r0, r0, #0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #20
	str r1, [r4, #0x98]
_0201BC30:
	ldr r0, [sp, #0x10]
	cmp r0, #0
	strne r0, [r4, #0x9c]
	bne _0201BC70
	ldrh r1, [r4, #0x34]
	ldr r0, =FX_SinCosTable_
	ldr r2, [r4, #0xc8]
	mov r1, r1, asr #4
	mov r1, r1, lsl #2
	ldrsh r0, [r0, r1]
	smull r1, r0, r2, r0
	adds r1, r1, #0x800
	adc r0, r0, #0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #20
	str r1, [r4, #0x9c]
_0201BC70:
	mov r1, #0
	mov r2, r1
	add r0, r4, #0x550
	bl ObjRect__SetAttackStat
	ldr r1, [r4, #0x5d8]
	add r0, r4, #0x500
	bic r1, r1, #0xf
	orr r1, r1, #3
	str r1, [r4, #0x5d8]
	mov r1, #0x30
	strh r1, [r0, #0xfa]
	mov r1, #0
	str r1, [r4, #0x2c]
	str r1, [r4, #0x28]
	strh r1, [r0, #0xd6]
	ldr r0, [r4, #0x5d8]
	tst r0, #0x4000000
	ldmeqia sp!, {r4, lr}
	addeq sp, sp, #0x10
	bxeq lr
	bl IsBossStage
	cmp r0, #0
	bne _0201BCDC
	ldr r1, [r4, #0x98]
	mov r0, r1, asr #2
	add r0, r0, r1, asr #1
	str r0, [r4, #0x98]
_0201BCDC:
	bl IsBossStage
	cmp r0, #0
	bne _0201BCF8
	ldr r1, [r4, #0x9c]
	mov r0, r1, asr #2
	add r0, r0, r1, asr #1
	str r0, [r4, #0x9c]
_0201BCF8:
	ldrb r2, [r4, #0x5d3]
	mov r0, #0x70
	mov r1, #0
	smulbb r3, r2, r0
	ldr r2, =0x02133B36
	mov r0, r4
	ldrh r3, [r2, r3]
	mov r2, r1
	bl CreateEffectWaterBubbleForPlayer
	ldmia sp!, {r4, lr}
	add sp, sp, #0x10
	bx lr

// clang-format on
#endif
}

void Player__Action_SpringboardLaunch(Player *player, fx32 velX, fx32 velY)
{
    StageTask__ObjectSpdDirFall(&velX, &velY, player->objWork.fallDir);
    Player__Gimmick_201BAC0(player, velX, velY);

    PlayPlayerSfx(player, PLAYER_SEQPLAYER_COMMON, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_JUMP_STAND);
}

u16 Player__Func_201BD9C(Player *player)
{
    if (StageTaskStateMatches(&player->objWork, Player__State_201BF3C))
        return TRUE;
    else
        return FALSE;
}

NONMATCH_FUNC void Player__Gimmick_201BDC0(Player *player, s32 a2, s32 a3, s32 a4, u16 a5)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	mov r8, r0
	mov r7, r1
	mov r6, r2
	mov r5, r3
	bl Player__Func_201BD9C
	cmp r0, #0
	ldmneia sp!, {r4, r5, r6, r7, r8, pc}
	ldrb r4, [r8, #0x710]
	mov r1, #0
	mov r0, r8
	strb r1, [r8, #0x710]
	bl Player__InitGimmick
	strb r4, [r8, #0x710]
	ldr r0, [r8, #0x5dc]
	mov r4, r5, asr #0xc
	tst r0, #0x800
	bne _0201BE28
	cmp r4, #2
	addne r0, r8, #0x500
	ldrnesh r0, [r0, #0xd4]
	cmpne r0, #0x5c
	beq _0201BE54
	mov r0, r8
	bl Player__HandleStartWalkAnimation
	b _0201BE54
_0201BE28:
	cmp r4, #2
	addne r0, r8, #0x500
	ldrnesh r0, [r0, #0xd4]
	cmpne r0, #0x41
	beq _0201BE54
	mov r0, r8
	mov r1, #0x41
	bl Player__ChangeAction
	mov r0, r8
	mov r1, #3
	bl ChangePlayerSnowboardAction
_0201BE54:
	ldr r1, [r8, #0x20]
	ldr r0, =0x00000FFF
	orr r1, r1, #4
	str r1, [r8, #0x20]
	ldr r2, [r8, #0x1c]
	ldrh r1, [sp, #0x18]
	orr r2, r2, #0x10
	orr r2, r2, #0x2000
	str r2, [r8, #0x1c]
	ldr r2, [r8, #0x5d8]
	and r0, r5, r0
	bic r2, r2, #3
	str r2, [r8, #0x5d8]
	str r7, [r8, #0x6f0]
	str r6, [r8, #0x6f4]
	str r4, [r8, #0x6f8]
	str r1, [r8, #0x6fc]
	str r0, [r8, #0x28]
	mov r0, #0
	str r0, [r8, #0x2c]
	ldr r0, [r8, #0x28]
	ldr r1, [r8, #0x44]
	tst r0, #1
	ldr r0, [r8, #0x6f0]
	beq _0201BEC8
	cmp r0, r1
	subgt r0, r0, r1
	strgt r0, [r8, #0x2c]
	b _0201BED4
_0201BEC8:
	cmp r0, r1
	sublt r0, r1, r0
	strlt r0, [r8, #0x2c]
_0201BED4:
	ldrsh r1, [r8, #0xf2]
	ldr r2, [r8, #0x6f4]
	add r0, r8, #0x2f4
	sub r1, r2, r1, lsl #12
	str r1, [r8, #0x6f4]
	ldr r1, [r8, #0x6f8]
	cmp r1, #1
	bne _0201BF10
	ldr r1, [r8, #0x28]
	tst r1, #2
	bne _0201BF1C
	ldr r1, [r0, #0x400]
	sub r1, r1, #0x4000
	str r1, [r0, #0x400]
	b _0201BF1C
_0201BF10:
	ldr r0, [r8, #0x28]
	orr r0, r0, #2
	str r0, [r8, #0x28]
_0201BF1C:
	ldr r1, =Player__State_201BF3C
	add r0, r8, #0x500
	str r1, [r8, #0xf4]
	mov r1, #0x10
	strh r1, [r0, #0xd6]
	ldmia sp!, {r4, r5, r6, r7, r8, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__State_201BF3C(Player *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, lr}
	sub sp, sp, #0xc
	mov r4, r0
	ldr r0, [r4, #0x6f8]
	cmp r0, #2
	beq _0201BFA8
	ldr r1, [r4, #0xc8]
	ldr r0, [r4, #0x644]
	cmp r1, #0
	rsblt r1, r1, #0
	cmp r1, r0
	bge _0201BFA8
	mov r0, r4
	bl Player__HandleFallOffSurface
	cmp r0, #0
	beq _0201BFA8
	mov r0, #0
	strh r0, [r4, #0x34]
	strh r0, [r4, #0x32]
	strh r0, [r4, #0x30]
	ldr r1, [r4, #0x1c]
	mov r0, r4
	bic r1, r1, #0x2000
	str r1, [r4, #0x1c]
	bl Player__Action_Launch
	add sp, sp, #0xc
	ldmia sp!, {r3, r4, pc}
_0201BFA8:
	add r0, r4, #0x700
	ldrh r0, [r0, #0x22]
	tst r0, #1
	ldrne r0, [r4, #0x5f0]
	cmpne r0, #0
	beq _0201C004
	ldr r0, [r4, #0x6f8]
	cmp r0, #2
	ldreq r0, [r4, #0x18]
	orreq r0, r0, #1
	streq r0, [r4, #0x18]
	mov r0, #0
	strh r0, [r4, #0x34]
	strh r0, [r4, #0x32]
	strh r0, [r4, #0x30]
	ldr r1, [r4, #0x1c]
	mov r0, r4
	bic r1, r1, #0x2000
	str r1, [r4, #0x1c]
	ldr r1, [r4, #0x5f0]
	blx r1
	add sp, sp, #0xc
	ldmia sp!, {r3, r4, pc}
_0201C004:
	add r0, r4, #0x500
	ldrsh r1, [r0, #0xd6]
	cmp r1, #0
	subne r1, r1, #1
	strneh r1, [r0, #0xd6]
	bne _0201C0D0
	ldr r0, [r4, #0x28]
	tst r0, #2
	ldrne r0, [r4, #0x1c]
	bicne r0, r0, #0x10
	strne r0, [r4, #0x1c]
	ldr r0, [r4, #0x1c]
	tst r0, #0xd
	beq _0201C0D0
	mov r0, #0
	strh r0, [r4, #0x34]
	strh r0, [r4, #0x32]
	strh r0, [r4, #0x30]
	ldr r0, [r4, #0x1c]
	bic r0, r0, #0x2000
	str r0, [r4, #0x1c]
	ldr r0, [r4, #0x6f8]
	cmp r0, #1
	bne _0201C08C
	ldr r0, [r4, #0x28]
	mov r0, r0, lsr #2
	tst r0, #1
	bne _0201C08C
	ldr r0, [r4, #0xc8]
	rsb r0, r0, #0
	str r0, [r4, #0xc8]
	ldr r0, [r4, #0x20]
	eor r0, r0, #1
	str r0, [r4, #0x20]
_0201C08C:
	ldr r1, [r4, #0xc8]
	mov r0, r4
	str r1, [r4, #0x98]
	mov r1, #0
	bl Player__Action_LandOnGround
	ldr r0, [r4, #0x6f8]
	cmp r0, #2
	bne _0201C0BC
	mov r0, r4
	bl Player__Action_Grind
	add sp, sp, #0xc
	ldmia sp!, {r3, r4, pc}
_0201C0BC:
	ldr r1, [r4, #0x5e4]
	mov r0, r4
	blx r1
	add sp, sp, #0xc
	ldmia sp!, {r3, r4, pc}
_0201C0D0:
	ldr r0, [r4, #0x6f8]
	cmp r0, #2
	beq _0201C114
	ldr r0, [r4, #0x5dc]
	tst r0, #0x800
	bne _0201C10C
	ldr r1, [r4, #0xc8]
	mov r0, r4
	bl Player__SetAnimSpeedFromVelocity
	add r0, r4, #0x500
	ldrsh r0, [r0, #0xd4]
	cmp r0, #0x5c
	beq _0201C10C
	mov r0, r4
	bl Player__HandleActiveWalkAnimation
_0201C10C:
	mov r0, r4
	bl Player__HandleGroundMovement
_0201C114:
	ldr r0, [r4, #0x6f8]
	cmp r0, #0
	beq _0201C130
	cmp r0, #1
	beq _0201C14C
	cmp r0, #2
	beq _0201C1BC
_0201C130:
	ldr r1, =0x001759D0
	mov r0, r4
	mov r2, #0x120
	mov r3, #0x26
	bl Player__Func_201C1EC
	add sp, sp, #0xc
	ldmia sp!, {r3, r4, pc}
_0201C14C:
	ldr r0, [r4, #0x6fc]
	cmp r0, #0
	bne _0201C188
	ldr r0, =0x00083F00
	mov r3, #0x80
	str r0, [sp]
	mov r0, r4
	ldr r1, =0x0021E520
	str r3, [sp, #4]
	mov r4, #0x20
	mov r2, #0x54
	str r4, [sp, #8]
	bl Player__Func_201C384
	add sp, sp, #0xc
	ldmia sp!, {r3, r4, pc}
_0201C188:
	mov r0, #0x50000
	str r0, [sp]
	mov r2, #0x40
	mov r0, r4
	str r2, [sp, #4]
	mov r4, #0x32
	ldr r1, =0x0013C030
	mov r2, #0x28
	mov r3, #0xc0
	str r4, [sp, #8]
	bl Player__Func_201C384
	add sp, sp, #0xc
	ldmia sp!, {r3, r4, pc}
_0201C1BC:
	ldr r1, =0x0013D9D0
	mov r0, r4
	mov r2, #0x100
	mov r3, #0x1e
	bl Player__Func_201C1EC
	add sp, sp, #0xc
	ldmia sp!, {r3, r4, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__Func_201C1EC(Player *player, s32 a2, s32 a3, s16 a4)
{
    // https://decomp.me/scratch/OYbFe -> 71.08%
#ifdef NON_MATCHING
    player->objWork.userTimer += MATH_ABS(player->objWork.groundVel);

    s16 v11  = (player->objWork.userTimer / a2) << 8;
    s32 v12  = ((player->objWork.userTimer - a2 * v11) << 8) / a2;
    s32 v13  = v12 << 4;
    u16 dirX = (v12 << 4);

    player->objWork.dir.x = dirX;
    if ((player->objWork.userWork & 1) != 0)
        player->objWork.dir.x = -player->objWork.dir.x;

    if (player->objWork.dir.x < 0x4000)
    {
        player->objWork.dir.z = player->objWork.dir.x;
    }
    else if (player->objWork.dir.x < 0x8000)
    {
        player->objWork.dir.z = 0x8000 - player->objWork.dir.x;
    }
    else
    {
        if (player->objWork.dir.x < 0xC000)
            player->objWork.dir.z = player->objWork.dir.x - 0x8000;
        else
            player->objWork.dir.z = 0x10000 - player->objWork.dir.x;
    }

    player->objWork.dir.z = player->objWork.dir.z >> 1;
    if (player->objWork.dir.x < 0x8000)
        player->objWork.dir.z = -player->objWork.dir.z;
    player->objWork.dir.x = -player->objWork.dir.x;

    fx32 cos = CosFX(dirX);
    s16 v18  = (a4 - player->objWork.hitboxRect.bottom);
    if ((player->objWork.userWork & 2) != 0)
        v18 = -v18;

    player->objWork.prevPosition.x = player->objWork.position.x;
    player->objWork.prevPosition.y = player->objWork.position.y;

    if ((player->objWork.userWork & 1) != 0)
    {
        player->objWork.position.x = player->gimmickValue1 - ((v11 * a3) << 12) - a3 * v13;
    }
    else
    {
        player->objWork.position.x = player->gimmickValue1 + ((v11 * a3) << 12) + a3 * v13;
    }

    player->objWork.position.y = player->gimmickValue2 + (v18 << 12) - cos * v18;

    player->objWork.move.x = player->objWork.position.x - player->objWork.prevPosition.x;
    player->objWork.move.y = player->objWork.position.y - player->objWork.prevPosition.y;
#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
	mov r7, r0
	ldr r4, [r7, #0xc8]
	ldr r0, [r7, #0x2c]
	cmp r4, #0
	rsblt r4, r4, #0
	add r8, r0, r4
	mov r9, r1
	mov r1, r9
	mov r0, r8
	mov r6, r2
	mov r5, r3
	str r8, [r7, #0x2c]
	bl _s32_div_f
	mov r0, r0, lsl #0x18
	mov r4, r0, asr #0x18
	mul r0, r9, r4
	sub r0, r8, r0
	mov r1, r9
	mov r0, r0, lsl #8
	bl _s32_div_f
	mov r1, r0, lsl #4
	mov r0, r1, lsl #0x14
	mov r0, r0, lsr #0x10
	strh r0, [r7, #0x30]
	ldr r2, [r7, #0x28]
	tst r2, #1
	ldrneh r2, [r7, #0x30]
	rsbne r2, r2, #0
	strneh r2, [r7, #0x30]
	ldrh r2, [r7, #0x30]
	cmp r2, #0x4000
	strloh r2, [r7, #0x34]
	blo _0201C298
	cmp r2, #0x8000
	rsblo r2, r2, #0x8000
	strloh r2, [r7, #0x34]
	blo _0201C298
	cmp r2, #0xc000
	sublo r2, r2, #0x8000
	strloh r2, [r7, #0x34]
	rsbhs r2, r2, #0x10000
	strhsh r2, [r7, #0x34]
_0201C298:
	ldrh r2, [r7, #0x34]
	mov r0, r0, lsl #0x10
	mov r2, r2, asr #1
	strh r2, [r7, #0x34]
	ldrh r2, [r7, #0x30]
	cmp r2, #0x8000
	ldrloh r2, [r7, #0x34]
	rsblo r2, r2, #0
	strloh r2, [r7, #0x34]
	ldrh r3, [r7, #0x30]
	mov r2, r0, lsr #0x10
	mov r2, r2, asr #4
	rsb r0, r3, #0
	strh r0, [r7, #0x30]
	ldrsh r0, [r7, #0xf2]
	mov r2, r2, lsl #1
	add r8, r2, #1
	sub r0, r5, r0
	ldr r2, [r7, #0x28]
	mov r0, r0, lsl #0x10
	mov r5, r0, asr #0x10
	tst r2, #2
	rsbne r2, r5, #0
	movne r2, r2, lsl #0x10
	movne r5, r2, asr #0x10
	ldr r2, [r7, #0x44]
	ldr r3, =FX_SinCosTable_
	str r2, [r7, #0x8c]
	ldr r2, [r7, #0x48]
	mov r8, r8, lsl #1
	str r2, [r7, #0x90]
	ldr r2, [r7, #0x28]
	ldrsh r0, [r3, r8]
	tst r2, #1
	mul r2, r4, r6
	ldreq r3, [r7, #0x6f0]
	addeq r2, r3, r2, lsl #12
	mlaeq r1, r6, r1, r2
	beq _0201C344
	mul r1, r6, r1
	ldr r3, [r7, #0x6f0]
	sub r2, r3, r2, lsl #12
	sub r1, r2, r1
_0201C344:
	str r1, [r7, #0x44]
	mul r1, r0, r5
	ldr r0, [r7, #0x6f4]
	add r0, r0, r5, lsl #12
	sub r0, r0, r1
	str r0, [r7, #0x48]
	ldr r1, [r7, #0x44]
	ldr r0, [r7, #0x8c]
	sub r0, r1, r0
	str r0, [r7, #0xbc]
	ldr r1, [r7, #0x48]
	ldr r0, [r7, #0x90]
	sub r0, r1, r0
	str r0, [r7, #0xc0]
	ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__Func_201C384(Player *player, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
	mov r10, r0
	mov r11, r1
	ldr r1, [sp, #0x28]
	ldr r0, [r10, #0xc8]
	str r1, [sp, #0x28]
	cmp r0, #0
	ldr r4, [r10, #0x28]
	ldr r1, [r10, #0x2c]
	mov r4, r4, lsl #0x16
	rsblt r0, r0, #0
	mov r9, r2
	adds r2, r1, r0
	rsbmi r1, r2, #0
	ldr r7, [sp, #0x2c]
	ldr r6, [sp, #0x30]
	ldr r0, [sp, #0x28]
	movpl r1, r2
	mov r8, r3
	mov r4, r4, asr #0x18
	str r2, [r10, #0x2c]
	cmp r1, r0
	blt _0201C73C
	ldr r0, [r10, #0x5d8]
	tst r0, #1
	bne _0201C470
	orr r0, r0, #1
	str r0, [r10, #0x5d8]
	ldr r0, [r10, #0x28]
	ldrsh r1, [r10, #0xf2]
	tst r0, #1
	sub r0, r7, r9
	beq _0201C418
	ldr r2, [r10, #0x6f0]
	add r0, r1, r0
	sub r0, r2, r0, lsl #12
	b _0201C424
_0201C418:
	ldr r2, [r10, #0x6f0]
	add r0, r1, r0
	add r0, r2, r0, lsl #12
_0201C424:
	str r0, [r10, #0x6f0]
	ldr r0, [r10, #0x28]
	ldr r1, [r10, #0x6f4]
	tst r0, #2
	rsbne r0, r6, r8, asr #2
	addne r0, r1, r0, lsl #12
	rsbeq r0, r6, r8, asr #2
	subeq r0, r1, r0, lsl #12
	str r0, [r10, #0x6f4]
	ldr r0, [r10, #0x28]
	tst r0, #2
	bne _0201C45C
	tst r4, #1
	beq _0201C468
_0201C45C:
	mov r0, #0xc000
	strh r0, [r10, #0x30]
	b _0201C470
_0201C468:
	mov r0, #0x4000
	strh r0, [r10, #0x30]
_0201C470:
	ldr r1, [r10, #0x2c]
	ldr r0, [sp, #0x28]
	sub r0, r1, r0
	adds r5, r0, r11, asr #2
	rsbmi r0, r5, #0
	movpl r0, r5
	mov r1, r11, asr #1
	add r0, r0, r11, asr #2
	str r1, [sp]
	bl FX_DivS32
	mov r0, r0, lsl #0x18
	cmp r4, r0, asr #24
	mov r0, r0, asr #0x18
	bgt _0201C614
	ldr r1, [r10, #0x5d8]
	tst r1, #2
	bne _0201C528
	orr r1, r1, #2
	str r1, [r10, #0x5d8]
	ldr r1, [r10, #0x28]
	tst r1, #1
	ldrsh r1, [r10, #0xf2]
	ldreq r2, [r10, #0x6f0]
	subeq r1, r9, r1
	addeq r1, r2, r1, lsl #12
	beq _0201C4E4
	ldr r2, [r10, #0x6f0]
	sub r1, r9, r1
	sub r1, r2, r1, lsl #12
_0201C4E4:
	str r1, [r10, #0x6f0]
	ldr r1, [r10, #0x28]
	tst r1, #2
	sub r1, r0, #1
	mov r0, r8, asr #1
	beq _0201C514
	mul r0, r1, r0
	ldr r1, [r10, #0x6f4]
	add r0, r0, r8, asr #2
	sub r0, r1, r0, lsl #12
	str r0, [r10, #0x6f4]
	b _0201C528
_0201C514:
	mul r0, r1, r0
	ldr r1, [r10, #0x6f4]
	add r0, r0, r8, asr #2
	add r0, r1, r0, lsl #12
	str r0, [r10, #0x6f4]
_0201C528:
	ldr r0, [sp]
	mul r1, r0, r4
	sub r0, r5, r1
	add r0, r0, r11, asr #2
	ldr r1, [sp, #0x28]
	mov r0, r0, lsl #8
	bl FX_DivS32
	mov r0, r0, lsl #4
	mov r1, r0, asr #0x1f
	mov r2, r1, lsl #0xe
	mov r1, #0x800
	adds r3, r1, r0, lsl #14
	orr r2, r2, r0, lsr #18
	adc r1, r2, #0
	mov r2, r3, lsr #0xc
	orr r2, r2, r1, lsl #20
	add r1, r2, #0xc000
	ldr r2, [r10, #0x28]
	mov r1, r1, lsl #0x10
	tst r2, #2
	mov r1, r1, lsr #0x10
	bne _0201C590
	tst r4, #1
	rsbeq r1, r1, #0
	moveq r1, r1, lsl #0x10
	moveq r1, r1, lsr #0x10
_0201C590:
	strh r1, [r10, #0x30]
	ldr r2, [r10, #0x28]
	tst r2, #2
	rsbne r1, r6, #0
	movne r1, r1, lsl #0x10
	movne r6, r1, asr #0x10
	tst r2, #1
	rsbne r1, r7, #0
	movne r1, r1, lsl #0x10
	movne r7, r1, asr #0x10
	tst r4, #1
	rsbeq r1, r7, #0
	moveq r1, r1, lsl #0x10
	moveq r7, r1, asr #0x10
	ldr r1, [r10, #0x44]
	str r1, [r10, #0x8c]
	ldr r1, [r10, #0x48]
	str r1, [r10, #0x90]
	ldr r1, [r10, #0x6f0]
	mla r1, r7, r0, r1
	str r1, [r10, #0x44]
	ldr r1, [r10, #0x6f4]
	mla r0, r6, r0, r1
	str r0, [r10, #0x48]
	ldr r1, [r10, #0x44]
	ldr r0, [r10, #0x8c]
	sub r0, r1, r0
	str r0, [r10, #0xbc]
	ldr r1, [r10, #0x48]
	ldr r0, [r10, #0x90]
	sub r0, r1, r0
	str r0, [r10, #0xc0]
	ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
_0201C614:
	mov r0, r5
	mov r1, r11
	bl FX_DivS32
	mov r0, r0, lsl #0x18
	mov r6, r0, asr #0x18
	mul r0, r11, r6
	mov r1, r11
	sub r0, r5, r0
	bl FX_Div
	mov r1, r0, lsl #0x14
	mov r1, r1, lsr #0x10
	add r2, r1, #0xc000
	and r2, r2, #0xff00
	strh r2, [r10, #0x32]
	ldr r2, [r10, #0x28]
	tst r2, #1
	ldrneh r2, [r10, #0x32]
	rsbne r2, r2, #0
	strneh r2, [r10, #0x32]
	ldr r2, [r10, #0x28]
	tst r2, #2
	bne _0201C67C
	tst r4, #1
	ldreqh r2, [r10, #0x32]
	rsbeq r2, r2, #0
	streqh r2, [r10, #0x32]
_0201C67C:
	mov r1, r1, lsl #0x10
	mov r2, r1, lsr #0x10
	mov r2, r2, asr #4
	mov r2, r2, lsl #1
	add r4, r2, #1
	ldr r2, [r10, #0x28]
	ldrsh r1, [r10, #0xf2]
	tst r2, #2
	rsbne r2, r8, #0
	movne r2, r2, lsl #0x10
	movne r8, r2, asr #0x10
	ldr r2, [r10, #0x44]
	sub r1, r9, r1
	str r2, [r10, #0x8c]
	ldr r2, [r10, #0x48]
	mov r1, r1, lsl #0x10
	str r2, [r10, #0x90]
	ldr r2, [r10, #0x28]
	ldr r3, =FX_SinCosTable_
	mov r4, r4, lsl #1
	mov r9, r1, asr #0x10
	ldrsh r1, [r3, r4]
	tst r2, #1
	beq _0201C6F0
	ldr r2, [r10, #0x6f0]
	sub r2, r2, r9, lsl #12
	mla r2, r1, r9, r2
	str r2, [r10, #0x44]
	b _0201C704
_0201C6F0:
	mul r2, r1, r9
	ldr r1, [r10, #0x6f0]
	add r1, r1, r9, lsl #12
	sub r1, r1, r2
	str r1, [r10, #0x44]
_0201C704:
	mul r1, r6, r8
	ldr r2, [r10, #0x6f4]
	add r1, r2, r1, lsl #12
	mla r0, r8, r0, r1
	str r0, [r10, #0x48]
	ldr r1, [r10, #0x44]
	ldr r0, [r10, #0x8c]
	sub r0, r1, r0
	str r0, [r10, #0xbc]
	ldr r1, [r10, #0x48]
	ldr r0, [r10, #0x90]
	sub r0, r1, r0
	str r0, [r10, #0xc0]
	ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
_0201C73C:
	mov r1, r0
	mov r0, r2, lsl #8
	bl FX_DivS32
	mov r0, r0, lsl #4
	mov r1, r0, asr #0x1f
	mov r2, r1, lsl #0xe
	mov r1, #0x800
	adds r3, r1, r0, lsl #14
	orr r2, r2, r0, lsr #18
	adc r1, r2, #0
	mov r3, r3, lsr #0xc
	orr r3, r3, r1, lsl #20
	ldr r2, [r10, #0x28]
	mov r1, r3, lsl #0x10
	tst r2, #2
	mov r1, r1, lsr #0x10
	bne _0201C788
	tst r4, #1
	beq _0201C794
_0201C788:
	rsb r1, r1, #0x10000
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
_0201C794:
	strh r1, [r10, #0x30]
	ldr r2, [r10, #0x28]
	tst r2, #2
	rsbne r1, r6, #0
	movne r1, r1, lsl #0x10
	movne r6, r1, asr #0x10
	tst r2, #1
	rsbne r1, r7, #0
	movne r1, r1, lsl #0x10
	movne r7, r1, asr #0x10
	ldr r1, [r10, #0x44]
	str r1, [r10, #0x8c]
	ldr r1, [r10, #0x48]
	str r1, [r10, #0x90]
	ldr r1, [r10, #0x6f0]
	mla r1, r7, r0, r1
	str r1, [r10, #0x44]
	ldr r1, [r10, #0x6f4]
	mla r0, r6, r0, r1
	str r0, [r10, #0x48]
	ldr r1, [r10, #0x44]
	ldr r0, [r10, #0x8c]
	sub r0, r1, r0
	str r0, [r10, #0xbc]
	ldr r1, [r10, #0x48]
	ldr r0, [r10, #0x90]
	sub r0, r1, r0
	str r0, [r10, #0xc0]
	ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}

// clang-format on
#endif
}

void Player__Gimmick_201C80C(Player *player, GameObjectTask *other, s32 value1, s32 timer)
{
    static const enum SND_ZONE_SEQARC_GAME_SE sfxJump[CHARACTER_COUNT] = {
        [CHARACTER_SONIC] = SND_ZONE_SEQARC_GAME_SE_SEQ_SE_SPIN, [CHARACTER_BLAZE] = SND_ZONE_SEQARC_GAME_SE_SEQ_SE_BURST
    };

    if (player->gimmickObj != other)
    {
        Player__InitPhysics(player);
        Player__InitGimmick(player, FALSE);

        player->gimmickObj = other;
        Player__ChangeAction(player, PLAYER_ACTION_ROLL);
        player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;
        SetTaskState(&player->objWork, Player__State_201C938);

        player->objWork.displayFlag &= ~DISPLAY_FLAG_FLIP_X;
        player->objWork.moveFlag |=
            STAGE_TASK_MOVE_FLAG_4000 | STAGE_TASK_MOVE_FLAG_DISABLE_OBJ_COLLISIONS | STAGE_TASK_MOVE_FLAG_DISABLE_COLLIDE_EVENT | STAGE_TASK_MOVE_FLAG_IN_AIR;
        player->objWork.moveFlag &= ~(STAGE_TASK_MOVE_FLAG_HAS_GRAVITY | STAGE_TASK_MOVE_FLAG_USE_SLOPE_ACCELERATION | STAGE_TASK_MOVE_FLAG_DISABLE_SLOPE_IDLE_ACCELERATION);
        player->playerFlag &= ~PLAYER_FLAG_USER_FLAG;
        player->playerFlag |= PLAYER_FLAG_DISABLE_TENSION_DRAIN;
        player->gimmickFlag |= PLAYER_GIMMICK_GRABBED;
        player->objWork.groundVel     = 0;
        player->objWork.velocity.x    = 0;
        player->objWork.velocity.y    = 0;
        player->objWork.dir.z         = 0;
        player->objWork.userWork      = 0;
        player->objWork.userTimer     = timer;
        player->gimmickValue1         = value1;
        player->gimmickValue2         = player->objWork.position.x;
        player->gimmickValue3         = player->objWork.position.y;
        player->colliders[0].defPower = PLAYER_DEFPOWER_INVINCIBLE;
        player->blinkTimer            = 0;
        player->objWork.displayFlag &= ~DISPLAY_FLAG_NO_DRAW;

        PlayPlayerSfxEx(&player->seqPlayers[PLAYER_SEQPLAYER_COMMON], sfxJump[player->characterID]);
    }
}

NONMATCH_FUNC void Player__State_201C938(Player *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	mov r4, r0
	add r0, r4, #0x500
	mov r1, #0xff
	strh r1, [r0, #0x3e]
	ldr r0, [r4, #0x28]
	cmp r0, #0
	beq _0201C968
	cmp r0, #1
	beq _0201CAE4
	b _0201CB88
_0201C968:
	ldr r0, [r4, #0x6d8]
	cmp r0, #0
	beq _0201CAB8
	ldr r0, [r4, #0x44]
	mov r3, #1
	str r0, [r4, #0x8c]
	ldr r0, [r4, #0x48]
	str r0, [r4, #0x90]
	ldr r0, [r4, #0x6f0]
	cmp r0, #0
	cmpne r0, #0x8000
	mov r0, #0x4000
	bne _0201CA04
	str r0, [sp]
	mov r0, #0x1000
	str r0, [sp, #4]
	ldr r1, [r4, #0x6d8]
	ldr r0, [r4, #0x48]
	ldr r1, [r1, #0x48]
	ldr r2, [r4, #0x6f8]
	bl ObjDiffSet
	str r0, [r4, #0x48]
	ldr r2, [r4, #0x6d8]
	ldr r1, [r2, #0x48]
	subs r0, r0, r1
	rsbmi r0, r0, #0
	cmp r0, #0x8000
	bge _0201CA68
	mov r0, #0x4000
	str r0, [sp]
	mov r0, #0x1000
	str r0, [sp, #4]
	ldr r0, [r4, #0x44]
	ldr r1, [r2, #0x44]
	ldr r2, [r4, #0x6f4]
	mov r3, #1
	bl ObjDiffSet
	str r0, [r4, #0x44]
	b _0201CA68
_0201CA04:
	str r0, [sp]
	mov r0, #0x1000
	str r0, [sp, #4]
	ldr r1, [r4, #0x6d8]
	ldr r0, [r4, #0x44]
	ldr r1, [r1, #0x44]
	ldr r2, [r4, #0x6f4]
	bl ObjDiffSet
	str r0, [r4, #0x44]
	ldr r2, [r4, #0x6d8]
	ldr r1, [r2, #0x44]
	subs r0, r0, r1
	rsbmi r0, r0, #0
	cmp r0, #0x8000
	bge _0201CA68
	mov r0, #0x4000
	str r0, [sp]
	mov r0, #0x1000
	str r0, [sp, #4]
	ldr r0, [r4, #0x48]
	ldr r1, [r2, #0x48]
	ldr r2, [r4, #0x6f8]
	mov r3, #1
	bl ObjDiffSet
	str r0, [r4, #0x48]
_0201CA68:
	ldr r2, [r4, #0x6d8]
	ldr r0, [r4, #0x44]
	ldr r1, [r2, #0x44]
	cmp r1, r0
	ldreq r1, [r2, #0x48]
	ldreq r0, [r4, #0x48]
	cmpeq r1, r0
	addne sp, sp, #8
	ldmneia sp!, {r4, pc}
	ldr r0, [r4, #0x1c]
	add sp, sp, #8
	bic r0, r0, #0x10
	bic r0, r0, #0x100
	str r0, [r4, #0x1c]
	ldr r0, [r4, #0x28]
	add r0, r0, #1
	str r0, [r4, #0x28]
	ldr r0, [r4, #0x6f0]
	strh r0, [r4, #0x34]
	ldmia sp!, {r4, pc}
_0201CAB8:
	ldr r0, [r4, #0x1c]
	add sp, sp, #8
	bic r0, r0, #0x10
	bic r0, r0, #0x100
	str r0, [r4, #0x1c]
	ldr r0, [r4, #0x28]
	add r0, r0, #1
	str r0, [r4, #0x28]
	ldr r0, [r4, #0x6f0]
	strh r0, [r4, #0x34]
	ldmia sp!, {r4, pc}
_0201CAE4:
	ldr r0, [r4, #0x1c]
	tst r0, #1
	bne _0201CB08
	ldrh r0, [r4, #0x34]
	add r0, r0, #0x8000
	strh r0, [r4, #0x34]
	ldr r0, [r4, #0x5d8]
	eor r0, r0, #1
	str r0, [r4, #0x5d8]
_0201CB08:
	ldr r0, [r4, #0x2c]
	sub r0, r0, #1
	cmp r0, #0
	addgt sp, sp, #8
	str r0, [r4, #0x2c]
	ldmgtia sp!, {r4, pc}
	ldr r0, [r4, #0x1c]
	tst r0, #1
	addeq sp, sp, #8
	ldmeqia sp!, {r4, pc}
	mov r0, #0x8000
	str r0, [r4, #0xc8]
	ldr r0, [r4, #0x5d8]
	mov ip, #0x4a
	tst r0, #1
	ldrne r0, [r4, #0xc8]
	sub r1, ip, #0x4b
	rsbne r0, r0, #0
	strne r0, [r4, #0xc8]
	ldr r0, [r4, #0x28]
	mov r3, r1
	add r2, r0, #1
	add r0, r4, #0x254
	str r2, [r4, #0x28]
	mov r2, #0
	str r2, [sp]
	mov r2, r1
	add r0, r0, #0x400
	str ip, [sp, #4]
	bl PlaySfxEx
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_0201CB88:
	ldr r0, [r4, #0x5d8]
	mov r2, #0xd000
	tst r0, #1
	ldr r0, [r4, #0xc8]
	beq _0201CBA8
	mvn r1, #0xff
	bl ObjSpdUpSet
	b _0201CBB0
_0201CBA8:
	mov r1, #0x100
	bl ObjSpdUpSet
_0201CBB0:
	str r0, [r4, #0xc8]
	ldr r1, [r4, #0xc8]
	mov r0, r4
	bl Player__SetAnimSpeedFromVelocity
	mov r0, #0
	strb r0, [r4, #0x6a9]
	add sp, sp, #8
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}

void Player__Func_201CBD0(Player *player, fx32 velocity, BOOL flag, u32 type)
{
    const s8 sfxEject[2] = { SND_ZONE_SEQARC_GAME_SE_SEQ_SE_FLOWER_EJECT, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_STEAM_PIPE };

    if (StageTaskStateMatches(&player->objWork, Player__State_201C938))
    {
        if (type >= 2)
            type = 0;

        s32 orientation = player->objWork.dir.z >> 13;
        if ((player->playerFlag & PLAYER_FLAG_USER_FLAG) != 0)
            orientation = (orientation + 4) & 7;

        if (!velocity)
            velocity = (s16)MATH_ABS(player->objWork.groundVel);

        fx32 velocity2 = MultiplyFX(velocity, SinFX(FLOAT_DEG_TO_IDX(45.0)));

        player->gimmickObj = NULL;
        player->objWork.moveFlag |= (STAGE_TASK_MOVE_FLAG_DISABLE_SLOPE_IDLE_ACCELERATION | STAGE_TASK_MOVE_FLAG_USE_SLOPE_ACCELERATION | STAGE_TASK_MOVE_FLAG_HAS_GRAVITY);
        player->objWork.moveFlag &= ~(STAGE_TASK_MOVE_FLAG_TOUCHING_FLOOR | STAGE_TASK_MOVE_FLAG_DISABLE_COLLIDE_EVENT | STAGE_TASK_MOVE_FLAG_DISABLE_OBJ_COLLISIONS
                                      | STAGE_TASK_MOVE_FLAG_DISABLE_MOVE_EVENT | STAGE_TASK_MOVE_FLAG_4000);
        player->objWork.dir.z = 0;
        player->playerFlag &= ~PLAYER_FLAG_DISABLE_TENSION_DRAIN;
        player->gimmickFlag &= ~PLAYER_GIMMICK_GRABBED;

        PlayPlayerSfxEx(&player->seqPlayers[PLAYER_SEQPLAYER_COMMON], sfxEject[type]);

        player->objWork.groundVel = 0;
        player->actionJump(player);
        player->objWork.velocity.x = 0;
        player->objWork.velocity.y = 0;

        switch (orientation)
        {
            case 0:
            default:
                player->objWork.velocity.x = velocity;
                break;

            case 1:
                player->objWork.velocity.x = velocity2;
                player->objWork.velocity.y = velocity2;
                break;

            case 2:
                player->objWork.velocity.y = velocity;
                break;

            case 3:
                player->objWork.displayFlag |= DISPLAY_FLAG_FLIP_X;
                player->objWork.velocity.x = -velocity2;
                player->objWork.velocity.y = velocity2;
                break;

            case 4:
                player->objWork.displayFlag |= DISPLAY_FLAG_FLIP_X;
                player->objWork.velocity.x = -velocity;
                break;

            case 5:
                player->objWork.displayFlag |= DISPLAY_FLAG_FLIP_X;
                player->objWork.velocity.x = -velocity2;
                player->objWork.velocity.y = -velocity2;
                break;

            case 6:
                player->objWork.velocity.y = -velocity;
                break;

            case 7:
                player->objWork.velocity.x = velocity2;
                player->objWork.velocity.y = -velocity2;
                break;
        }

        player->playerFlag |= PLAYER_FLAG_USER_FLAG;
        if (flag)
            player->playerFlag |= PLAYER_FLAG_ALLOW_TRICKS;

        player->colliders[0].defPower = PLAYER_DEFPOWER_NORMAL;
    }
}

NONMATCH_FUNC void Player__Gimmick_201CDDC(Player *player, u32 a2, s32 a3, s32 a4)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, r7, lr}
	sub sp, sp, #8
	mov r7, r0
	ldr r0, [r7, #0x1c]
	mov r6, r1
	mov r5, r2
	mov r4, r3
	tst r0, #0x8000
	beq _0201CE20
	ldr r0, [r7, #0x9c]
	ldr r1, [r7, #0x98]
	cmp r0, #0
	rsblt r0, r0, #0
	cmp r1, #0
	rsblt r1, r1, #0
	add r0, r1, r0
	b _0201CE4C
_0201CE20:
	ldr r0, [r7, #0x98]
	ldr r1, [r7, #0xc8]
	cmp r0, #0
	rsblt r0, r0, #0
	cmp r1, #0
	rsblt r1, r1, #0
	ldr r2, [r7, #0x9c]
	add r0, r1, r0
	cmp r2, #0
	rsblt r2, r2, #0
	add r0, r2, r0
_0201CE4C:
	str r0, [r7, #0xc8]
	ldr r0, [r7, #0xc8]
	cmp r0, #0x6000
	movlt r0, #0x6000
	strlt r0, [r7, #0xc8]
	blt _0201CE70
	cmp r0, #0x7800
	movgt r0, #0x7800
	strgt r0, [r7, #0xc8]
_0201CE70:
	ldr r0, [r7, #0xc8]
	mov r1, #0
	mov r0, r0, asr #4
	str r0, [r7, #0xc8]
	str r1, [r7, #0x98]
	mov r0, r7
	str r1, [r7, #0x9c]
	bl Player__InitPhysics
	mov r0, r7
	mov r1, #0
	bl Player__InitGimmick
	str r6, [r7, #0x6d8]
	ldr r1, [r7, #0xc8]
	mov r0, r7
	str r1, [r7, #0x6f4]
	mov r1, #0x25
	bl Player__ChangeAction
	ldr r1, [r7, #0x12c]
	mov r0, #0
	str r0, [r1, #0x118]
	ldr r1, [r7, #0x20]
	cmp r4, #0
	orr r1, r1, #4
	str r1, [r7, #0x20]
	ldr r1, [r7, #0x1c]
	bic r1, r1, #0xd0
	orr r1, r1, #0xa100
	str r1, [r7, #0x1c]
	ldr r1, [r7, #0x18]
	orr r1, r1, #2
	str r1, [r7, #0x18]
	ldr r1, [r7, #0x5d8]
	orr r1, r1, #0x2000
	orr r1, r1, #0x100000
	str r1, [r7, #0x5d8]
	ldr r1, [r7, #0x5dc]
	orr r1, r1, #0x38
	str r1, [r7, #0x5dc]
	ldr r1, [r7, #0x20]
	bic r1, r1, #1
	str r1, [r7, #0x20]
	strh r0, [r7, #0x30]
	moveq r0, #0x8000
	streqh r0, [r7, #0x32]
	ldr r3, [r6, #0x48]
	ldr r0, [r7, #0x48]
	ldr r2, [r6, #0x44]
	ldr r1, [r7, #0x44]
	sub r0, r3, r0
	sub r1, r2, r1
	bl FX_Atan2Idx
	mov r2, #0
	strh r2, [r7, #0x34]
	str r0, [r7, #0x6f8]
	str r2, [r7, #0x28]
	mov r6, #0x49
	sub r1, r6, #0x4a
	str r2, [r7, #0x2c]
	add r0, r7, #0x600
	strh r2, [r0, #0xde]
	add r4, r7, #0x254
	str r5, [r7, #0x6f0]
	str r2, [sp]
	mov r2, r1
	mov r3, r1
	add r0, r4, #0x400
	str r6, [sp, #4]
	bl PlaySfxEx
	ldr r0, =Player__Func_201CF94
	str r0, [r7, #0xf4]
	add sp, sp, #8
	ldmia sp!, {r3, r4, r5, r6, r7, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__Func_201CF94(Player *player)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	sub sp, sp, #8
	mov r5, r0
	ldr r0, [r5, #0x6d8]
	cmp r0, #0
	beq _0201D1E4
	ldrh r0, [r5, #0x32]
	cmp r0, #0
	ldr r0, [r5, #0x6f8]
	beq _0201CFE0
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r1, #0
	cmp r0, #0x4000
	bls _0201CFD8
	cmp r0, #0xc000
	movls r1, #1
_0201CFD8:
	mov r4, #1
	b _0201D000
_0201CFE0:
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r1, #1
	cmp r0, #0x4000
	bls _0201CFFC
	cmp r0, #0xc000
	movls r1, #0
_0201CFFC:
	mvn r4, #0
_0201D000:
	cmp r1, #0
	beq _0201D020
	ldr r2, [r5, #0x6f4]
	ldr r0, [r5, #0xc8]
	mov r1, r2, asr #5
	bl ObjSpdUpSet
	str r0, [r5, #0xc8]
	b _0201D044
_0201D020:
	ldr r1, [r5, #0x6f4]
	ldr r0, [r5, #0xc8]
	mov r1, r1, asr #5
	bl ObjSpdDownSet
	str r0, [r5, #0xc8]
	ldr r1, [r5, #0x6f4]
	cmp r0, r1, asr #1
	mov r0, r1, asr #1
	strlt r0, [r5, #0xc8]
_0201D044:
	ldr r2, [r5, #0x6f8]
	ldr r1, [r5, #0xc8]
	mov r0, r2, lsl #0x10
	mla r1, r4, r1, r2
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	str r1, [r5, #0x6f8]
	ldrh r2, [r5, #0x32]
	mov r1, r0, lsr #0x10
	cmp r2, #0
	beq _0201D084
	cmp r1, #0x8000
	bhs _0201D084
	ldr r0, [r5, #0x6f8]
	cmp r0, #0x8000
	bge _0201D0A0
_0201D084:
	cmp r2, #0
	bne _0201D0C8
	cmp r1, #0x8000
	bhs _0201D0C8
	ldr r0, [r5, #0x6f8]
	cmp r0, #0x8000
	ble _0201D0C8
_0201D0A0:
	mov r4, #0x4d
	sub r1, r4, #0x4e
	add r0, r5, #0x254
	mov r2, #0
	str r2, [sp]
	mov r2, r1
	mov r3, r1
	add r0, r0, #0x400
	str r4, [sp, #4]
	bl PlaySfxEx
_0201D0C8:
	ldrh r0, [r5, #0x32]
	cmp r0, #0
	ldr r0, [r5, #0x6f8]
	beq _0201D0E8
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add r0, r0, #0xc000
	b _0201D0F8
_0201D0E8:
	rsb r0, r0, #0
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add r0, r0, #0x4000
_0201D0F8:
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, asr #8
	add r0, r0, r0, lsl #2
	mov r1, r0, lsl #0x10
	mov r0, r5
	mov r1, r1, asr #8
	bl Player__SetAnimFrame
	ldr r1, [r5, #0x44]
	ldr r0, =FX_SinCosTable_
	str r1, [r5, #0x8c]
	ldr r1, [r5, #0x48]
	str r1, [r5, #0x90]
	ldr r2, [r5, #0x6f8]
	ldr r1, [r5, #0x6d8]
	mov r2, r2, lsl #0x10
	mov r2, r2, lsr #0x10
	mov r2, r2, lsl #0x10
	mov r2, r2, lsr #0x10
	mov r2, r2, asr #4
	mov r2, r2, lsl #1
	add r2, r2, #1
	mov r2, r2, lsl #1
	ldrsh r2, [r0, r2]
	ldr r3, [r5, #0x6f0]
	ldr r4, [r1, #0x44]
	smull r2, r1, r3, r2
	adds r2, r2, #0x800
	adc r1, r1, #0
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #20
	add r1, r4, r2
	str r1, [r5, #0x44]
	ldr r1, [r5, #0x6f8]
	ldr r2, [r5, #0x6d8]
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	mov r1, r1, asr #4
	mov r1, r1, lsl #2
	ldrsh r0, [r0, r1]
	ldr r1, [r5, #0x6f0]
	ldr r3, [r2, #0x48]
	smull r2, r0, r1, r0
	adds r1, r2, #0x800
	adc r0, r0, #0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #20
	add r0, r3, r1
	str r0, [r5, #0x48]
	ldr r1, [r5, #0x44]
	ldr r0, [r5, #0x8c]
	sub r0, r1, r0
	str r0, [r5, #0xbc]
	ldr r1, [r5, #0x48]
	ldr r0, [r5, #0x90]
	sub r0, r1, r0
	str r0, [r5, #0xc0]
_0201D1E4:
	ldr r0, [r5, #0x6d8]
	cmp r0, #0
	beq _0201D204
	add r0, r5, #0x700
	ldrh r0, [r0, #0x22]
	tst r0, #3
	addeq sp, sp, #8
	ldmeqia sp!, {r3, r4, r5, pc}
_0201D204:
	ldrh r0, [r5, #0x32]
	mov r2, #0x2000
	add r1, r5, #0x254
	cmp r0, #0
	ldr r0, [r5, #0x6f8]
	rsbeq r2, r2, #0
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	add r0, r0, #0x8000
	add r0, r0, r2
	mov r2, r0, lsl #0x10
	add r0, r1, #0x400
	mov r1, #0
	mov r4, r2, lsr #0x10
	bl NNS_SndPlayerStopSeq
	ldr ip, [r5, #0x6f4]
	mov r1, #0
	str r1, [r5, #0xc8]
	mov r0, r4, lsl #0x10
	strh r1, [r5, #0x32]
	mov r0, r0, lsr #0x10
	strh r1, [r5, #0x34]
	mov r0, r0, asr #4
	str r1, [r5, #0x6d8]
	mov r4, r0, lsl #1
	ldr r1, [r5, #0x1c]
	add r0, r4, #1
	orr r3, r1, #0xc0
	mov r1, r0, lsl #1
	ldr r2, =FX_SinCosTable_
	mov r0, r4, lsl #1
	bic r3, r3, #0x6100
	str r3, [r5, #0x1c]
	ldrsh r1, [r2, r1]
	mov ip, ip, lsl #4
	ldrsh r0, [r2, r0]
	smull r2, r1, ip, r1
	ldr r4, [r5, #0x18]
	adds r3, r2, #0x800
	bic r2, r4, #2
	str r2, [r5, #0x18]
	smull r0, r2, ip, r0
	adc ip, r1, #0
	adds r4, r0, #0x800
	mov r1, r3, lsr #0xc
	adc r3, r2, #0
	mov r2, r4, lsr #0xc
	orr r2, r2, r3, lsl #20
	ldr lr, [r5, #0x5d8]
	ldr r0, =0xFFEFDFFF
	orr r1, r1, ip, lsl #20
	and r0, lr, r0
	str r0, [r5, #0x5d8]
	ldr r0, [r5, #0x5dc]
	mov r3, #1
	bic r4, r0, #0x38
	mov r0, r5
	str r4, [r5, #0x5dc]
	bl Player__Gimmick_201B418
	mov r0, #5
	str r0, [r5, #0x2c]
	ldr r0, [r5, #0x1c]
	bic r0, r0, #0x80
	str r0, [r5, #0x1c]
	add sp, sp, #8
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

void Player__Gimmick_201D314(Player *player, GameObjectTask *other, s32 value1, s32 value2)
{
    if (player->gimmickObj != other)
    {
        Player__InitPhysics(player);
        Player__InitGimmick(player, 0);
        player->gimmickObj = other;
        player->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_DISABLE_MOVE_EVENT | STAGE_TASK_MOVE_FLAG_IN_AIR;
        player->playerFlag &= ~(PLAYER_FLAG_DISABLE_TRICK_FINISHER | PLAYER_FLAG_FINISHED_TRICK_COMBO | PLAYER_FLAG_ALLOW_TRICKS | PLAYER_FLAG_USER_FLAG);
        player->playerFlag |= PLAYER_FLAG_DISABLE_TENSION_DRAIN | PLAYER_FLAG_2000;
        player->gimmickFlag |= PLAYER_GIMMICK_20;
        player->gimmickCamOffsetY  = -58;
        player->objWork.velocity.x = 0;
        player->objWork.velocity.y = 0;
        player->objWork.groundVel  = 0;
        player->objWork.dir.z      = other->objWork.dir.z;
        player->objWork.userWork   = 0;
        player->objWork.userTimer  = 0;
        player->gimmickValue1      = value1;
        player->gimmickValue2      = value2;

        PlayStageSfx(SND_ZONE_SEQARC_GAME_SE_SEQ_SE_GIMMICK);

        SetTaskState(&player->objWork, Player__State_201D3E0);
    }
}

NONMATCH_FUNC void Player__State_201D3E0(Player *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, lr}
	mov r4, r0
	ldr r2, [r4, #0x6d8]
	cmp r2, #0
	beq _0201D514
	ldr r0, [r4, #0x44]
	ldr r1, =FX_SinCosTable_
	str r0, [r4, #0x8c]
	ldr r0, [r4, #0x48]
	str r0, [r4, #0x90]
	ldr r0, [r4, #0x4c]
	str r0, [r4, #0x94]
	ldrh r0, [r2, #0x34]
	strh r0, [r4, #0x34]
	ldr r0, [r4, #0x20]
	tst r0, #1
	ldreqh r0, [r4, #0x34]
	addeq r0, r0, #0x8000
	streqh r0, [r4, #0x34]
	ldrh r3, [r4, #0x34]
	ldr r0, [r4, #0x6f4]
	ldr lr, [r2, #0x8c]
	add r0, r3, r0
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, asr #4
	mov r0, r0, lsl #1
	add r0, r0, #1
	mov r0, r0, lsl #1
	ldrsh r0, [r1, r0]
	ldr r3, [r4, #0x6f0]
	smull ip, r0, r3, r0
	adds r3, ip, #0x800
	adc r0, r0, #0
	mov r3, r3, lsr #0xc
	orr r3, r3, r0, lsl #20
	add r0, lr, r3
	str r0, [r4, #0x44]
	ldrh ip, [r4, #0x34]
	ldr r3, [r4, #0x6f4]
	ldr r0, [r4, #0x6f0]
	add r3, ip, r3
	mov r3, r3, lsl #0x10
	mov r3, r3, lsr #0x10
	mov r3, r3, lsl #0x10
	mov r3, r3, lsr #0x10
	mov r3, r3, asr #4
	mov r3, r3, lsl #2
	ldrsh r1, [r1, r3]
	ldr ip, [r2, #0x90]
	smull r3, r1, r0, r1
	adds r3, r3, #0x800
	adc r0, r1, #0
	mov r1, r3, lsr #0xc
	orr r1, r1, r0, lsl #20
	add r0, ip, r1
	str r0, [r4, #0x48]
	ldr r0, [r2, #0x94]
	str r0, [r4, #0x4c]
	ldr r1, [r4, #0x44]
	ldr r0, [r4, #0x8c]
	sub r0, r1, r0
	str r0, [r4, #0xbc]
	ldr r1, [r4, #0x48]
	ldr r0, [r4, #0x90]
	sub r0, r1, r0
	str r0, [r4, #0xc0]
	ldr r1, [r4, #0x4c]
	ldr r0, [r4, #0x94]
	sub r0, r1, r0
	str r0, [r4, #0xc4]
	ldr r0, [r4, #0xbc]
	str r0, [r4, #0xc8]
	ldr r0, [r4, #0xc0]
	str r0, [r4, #0x9c]
_0201D514:
	ldr r0, [r4, #0x6d8]
	cmp r0, #0
	beq _0201D530
	add r0, r4, #0x700
	ldrh r0, [r0, #0x22]
	tst r0, #3
	ldmeqia sp!, {r4, pc}
_0201D530:
	mov r1, #0
	str r1, [r4, #0x6d8]
	ldr r2, [r4, #0x5dc]
	add r0, r4, #0x600
	bic r2, r2, #0x20
	str r2, [r4, #0x5dc]
	strh r1, [r0, #0xde]
	ldr r3, [r4, #0x5d8]
	ldr r0, =0xFFEFDFFF
	add r2, r4, #0x700
	and r0, r3, r0
	str r0, [r4, #0x5d8]
	ldr r0, [r4, #0x1c]
	bic r0, r0, #0x2000
	str r0, [r4, #0x1c]
	strh r1, [r4, #0x34]
	ldr r0, [r4, #0xc8]
	mov r0, r0, asr #1
	str r0, [r4, #0xc8]
	ldrh r0, [r2, #0x22]
	tst r0, #3
	beq _0201D598
	ldr r1, [r4, #0x5f0]
	mov r0, r4
	blx r1
	ldmia sp!, {r4, pc}
_0201D598:
	mov r0, r4
	bl Player__Action_LandOnGround
	ldr r1, [r4, #0x5e4]
	mov r0, r4
	blx r1
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__Action_MushroomBounce(Player *player, fx32 velX, fx32 velY, s32 timer)
{
#ifdef NON_MATCHING
    player->objWork.groundVel  = MTM_MATH_CLIP(player->objWork.groundVel, -player->spdThresholdDash, player->spdThresholdDash);
    player->objWork.velocity.x = MTM_MATH_CLIP(player->objWork.groundVel, -player->spdThresholdDash, player->spdThresholdDash);

    Player__Gimmick_Jump(player, velX, velY);
    player->objWork.moveFlag &= ~STAGE_TASK_MOVE_FLAG_HAS_GRAVITY;
    player->objWork.userTimer = 3 * timer + 1;

    Player__ChangeAction(player, PLAYER_ACTION_MUSHROOM_BOUNCE);
    StopPlayerSfx(player, PLAYER_SEQPLAYER_COMMON);
    PlayPlayerSfx(player, PLAYER_SEQPLAYER_COMMON, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_MUSHROOM);
#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	sub sp, sp, #8
	mov r5, r0
	ldr ip, [r5, #0xc8]
	mov r4, r3
	cmp ip, #0
	ldr r0, [r5, #0x64c]
	blt _0201D5E4
	cmp ip, r0
	strgt r0, [r5, #0xc8]
	b _0201D5F0
_0201D5E4:
	rsb r0, r0, #0
	cmp ip, r0
	strlt r0, [r5, #0xc8]
_0201D5F0:
	ldr r3, [r5, #0x98]
	ldr r0, [r5, #0x64c]
	cmp r3, #0
	blt _0201D60C
	cmp r3, r0
	strgt r0, [r5, #0x98]
	b _0201D618
_0201D60C:
	rsb r0, r0, #0
	cmp r3, r0
	strlt r0, [r5, #0x98]
_0201D618:
	mov r0, r5
	bl Player__Gimmick_Jump
	ldr r0, [r5, #0x1c]
	add r1, r4, r4, lsl #1
	bic r2, r0, #0x80
	mov r0, r5
	str r2, [r5, #0x1c]
	add r2, r1, #1
	mov r1, #0x26
	str r2, [r5, #0x2c]
	bl Player__ChangeAction
	add r0, r5, #0x254
	add r0, r0, #0x400
	mov r1, #0
	bl NNS_SndPlayerStopSeq
	mov r1, #0x4c
	add r0, r5, #0x254
	add r0, r0, #0x400
	mov r2, #0
	str r2, [sp]
	str r1, [sp, #4]
	sub r1, r1, #0x4d
	mov r2, r1
	mov r3, r1
	bl PlaySfxEx
	add sp, sp, #8
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__Func_201D684(Player *player, s32 a2, s32 a3, s32 a4)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	mov r4, r0
	ldr r1, [r4, #0x20]
	mov ip, #0
	bic r1, r1, #1
	str r1, [r4, #0x20]
	str ip, [r4, #0xc8]
	mov r1, r2
	str ip, [r4, #0x9c]
	mov r2, r3
	str ip, [r4, #0x98]
	bl Player__Gimmick_Jump
	add r0, r4, #0x700
	ldrh r3, [r0, #0x20]
	ldr r2, =Player__State_201D748
	add r1, r4, #0x600
	and r3, r3, #3
	strh r3, [r0, #0x20]
	str r2, [r4, #0xf4]
	ldr r2, [r4, #0x5d8]
	mov r0, #0
	orr r2, r2, #8
	orr r2, r2, #0x80000
	str r2, [r4, #0x5d8]
	strh r0, [r1, #0x92]
	ldr r0, [r4, #0x5dc]
	mov r1, #0x1e
	orr r0, r0, #0x2000000
	str r0, [r4, #0x5dc]
	mov r0, r4
	str r1, [r4, #0x6f4]
	bl Player__Action_StopSuperBoost
	ldr r0, [r4, #0x5d8]
	mov r2, #0x3c
	orr r0, r0, #0x100000
	str r0, [r4, #0x5d8]
	mov r3, #0
	add r0, r4, #0x254
	str r3, [sp]
	sub r1, r2, #0x3d
	str r2, [sp, #4]
	add r0, r0, #0x400
	mov r2, r1
	mov r3, r1
	bl PlaySfxEx
	add sp, sp, #8
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__State_201D748(Player *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, lr}
	mov r4, r0
	add r1, r4, #0x700
	ldrh r2, [r1, #0x20]
	and r2, r2, #3
	strh r2, [r1, #0x20]
	bl Player__State_Air
	ldr r1, [r4, #0x38]
	ldr r0, [r4, #0x6f4]
	add r0, r1, r0
	str r0, [r4, #0x38]
	cmp r0, #0x2800
	movgt r0, #0x2800
	strgt r0, [r4, #0x38]
	ldr r1, [r4, #0x38]
	ldr r0, =Player__State_201D748
	str r1, [r4, #0x40]
	str r1, [r4, #0x3c]
	ldr r1, [r4, #0xf4]
	cmp r1, r0
	ldmeqia sp!, {r4, pc}
	ldr r0, [r4, #0x5dc]
	bic r0, r0, #0x2000000
	str r0, [r4, #0x5dc]
	ldr r0, [r4, #0x5d8]
	bic r0, r0, #0x80000
	str r0, [r4, #0x5d8]
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__Func_201D7BC(Player *player, s32 a2)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r4, r0
	ldr r0, [r4, #0x6d8]
	cmp r0, r1
	ldmeqia sp!, {r3, r4, r5, pc}
	ldr r2, [r4, #0xf4]
	ldr r0, =Player__State_201D748
	cmp r2, r0
	ldmneia sp!, {r3, r4, r5, pc}
	mov r0, #0
	strb r0, [r4, #0x6c8]
	ldr r0, [r4, #0x5dc]
	bic r0, r0, #0x1000000
	str r0, [r4, #0x5dc]
	str r1, [r4, #0x6d8]
	ldr r0, [r4, #0x20]
	bic r0, r0, #0x200
	str r0, [r4, #0x20]
	ldr r2, [r1, #0x44]
	ldr r0, [r4, #0x44]
	ldr r1, [r4, #0x98]
	sub r0, r2, r0
	bl FX_DivS32
	mov r5, r0
	mov r1, r5
	mov r0, #0x4000
	bl FX_DivS32
	str r0, [r4, #0x6f0]
	ldr r0, [r4, #0x5dc]
	mov r1, r5
	orr r0, r0, #0x2000000
	str r0, [r4, #0x5dc]
	mov r0, #0x1800
	bl FX_DivS32
	str r0, [r4, #0x6f4]
	ldr r1, [r4, #0x5dc]
	add r0, r4, #0x600
	orr r1, r1, #0x30
	str r1, [r4, #0x5dc]
	mov r2, #0x50
	ldr r1, =Player__State_201D874
	strh r2, [r0, #0xde]
	str r1, [r4, #0xf4]
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__State_201D874(Player *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, lr}
	mov r4, r0
	ldr r1, [r4, #0x6d8]
	cmp r1, #0
	ldmeqia sp!, {r4, pc}
	add r1, r4, #0x700
	ldrh r2, [r1, #0x20]
	and r2, r2, #3
	strh r2, [r1, #0x20]
	bl Player__State_Air
	ldr r1, [r4, #0x6f0]
	ldrh r0, [r4, #0x32]
	mov r1, r1, lsl #0x10
	mov r2, r1, asr #0x10
	mov r1, #0xc000
	bl ObjRoopMove16
	strh r0, [r4, #0x32]
	ldr r1, [r4, #0x38]
	ldr r0, [r4, #0x6f4]
	add r0, r1, r0
	str r0, [r4, #0x38]
	cmp r0, #0x2800
	movgt r0, #0x2800
	strgt r0, [r4, #0x38]
	ldr r0, [r4, #0x38]
	str r0, [r4, #0x40]
	str r0, [r4, #0x3c]
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}

void Player__Gimmick_Grind3Line(Player *player)
{
    player->playerFlag |= PLAYER_FLAG_2000;
    player->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_RESET_FLOW | STAGE_TASK_MOVE_FLAG_DISABLE_MAP_COLLISIONS;
    Player__Action_LandOnGround(player, FLOAT_DEG_TO_IDX(0.0));

    player->objWork.velocity.x = player->objWork.velocity.y = 0;
    player->objWork.groundVel                               = 0;

    Player__ChangeAction(player, PLAYER_ACTION_GRIND2);
    player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;
    player->objWork.gravityStrength = FLOAT_TO_FX32(0.328125);
    Player__Action_StopBoost(player);

    SetTaskState(&player->objWork, Player__State_Grind3Line);
    ObjRect__SetOnDefend(&player->colliders[0], Player__OnDefend_Grind3Line);
    player->gimmickValue1 = 1;

    StopPlayerSfx(player, PLAYER_SEQPLAYER_GRIND);
    PlayPlayerSfx(player, PLAYER_SEQPLAYER_GRIND, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_GRIND);
}

void Player__State_Grind3Line(Player *work)
{
    Player__HandleRideGrind3Line(work);
}

void Player__HandleRideGrind3Line(Player *player)
{
    if ((player->objWork.moveFlag & STAGE_TASK_MOVE_FLAG_IN_AIR) == 0)
    {
        BOOL jumped = FALSE;
        fx32 velX   = 0;

        if ((player->inputKeyPress & PLAYER_INPUT_JUMP) != 0)
        {
            // just jumping
            jumped = TRUE;
        }
        else
        {
            if ((player->inputKeyDown & PAD_KEY_LEFT) != 0)
            {
                if (player->gimmickValue1 < 2)
                {
                    // hopping left one rail!
                    jumped = TRUE;
                    player->gimmickValue1++;
                    velX = -FLOAT_TO_FX32(2.9697265625);
                }
            }
            else if ((player->inputKeyDown & PAD_KEY_RIGHT) != 0)
            {
                if (player->gimmickValue1 > 0)
                {
                    // hopping right one rail!
                    jumped = TRUE;
                    player->gimmickValue1--;
                    velX = FLOAT_TO_FX32(2.9697265625);
                }
            }
        }

        if (jumped)
        {
            Player__ChangeAction(player, PLAYER_ACTION_HOMING_ATTACK);
            player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;

            player->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_DISABLE_SLOPE_ANGLES | STAGE_TASK_MOVE_FLAG_IN_AIR;

            if (velX != 0)
            {
                // player is hopping between rails
                player->objWork.velocity.x = velX;
                player->objWork.velocity.y = -FLOAT_TO_FX32(4.921875);
            }
            else
            {
                // player is jumping
                player->objWork.velocity.x = 0;
                player->objWork.velocity.y = -FLOAT_TO_FX32(8.203125);
            }

            StopPlayerSfx(player, PLAYER_SEQPLAYER_GRIND);
            PlayPlayerSfx(player, PLAYER_SEQPLAYER_COMMON, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_JUMP);
        }
    }
    else
    {
        if ((player->objWork.moveFlag & STAGE_TASK_MOVE_FLAG_TOUCHING_FLOOR) != 0)
        {
            // player has landed... put them back in the grind action!
            player->objWork.moveFlag &= ~STAGE_TASK_MOVE_FLAG_IN_AIR;
            player->objWork.velocity.x = player->objWork.velocity.y = 0;
            Player__ChangeAction(player, PLAYER_ACTION_GRIND2);
            player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;
            PlayPlayerSfx(player, PLAYER_SEQPLAYER_GRIND, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_GRIND);
        }
        else
        {
            // wait for it...
            if (player->objWork.userTimer != 0)
            {
                player->objWork.userTimer--;
                if (player->objWork.userTimer == 0)
                    player->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_HAS_GRAVITY;
            }
        }
    }
}

void Player__OnDefend_Grind3Line(OBS_RECT_WORK *rect1, OBS_RECT_WORK *rect2)
{
    Player *player = (Player *)rect2->parent;

    if (player->objWork.hitstopTimer != 0 || rect1->parent->objType == STAGE_OBJ_TYPE_PLAYER)
        return;

    if ((player->playerFlag & PLAYER_FLAG_SHIELD_REGULAR) == 0)
    {
        Player__GiveTension(player, -PLAYER_TENSION_HURT_PENALTY);
        UpdateTensionGaugeHUD(player->tension >> 4, 1);
    }

    if ((rect1->hitFlag & 4) != 0)
    {
        if (player->rings != 0)
        {
            PlayPlayerSfx(player, PLAYER_SEQPLAYER_COMMON, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_RINGLOST);
            Grind3LineRingLoss__Create(player);
        }

        Player__Action_Die(player);
        return;
    }

    if ((player->playerFlag & PLAYER_FLAG_SHIELD_REGULAR) == 0 && player->rings == 0)
    {
        Player__Action_Die(player);
        return;
    }

    if ((player->playerFlag & PLAYER_FLAG_SHIELD_REGULAR) == 0)
    {
        PlayPlayerSfx(player, PLAYER_SEQPLAYER_COMMON, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_RINGLOST);
        Grind3LineRingLoss__Create(player);
    }

    player->playerFlag &= ~(PLAYER_FLAG_SHIELD_MAGNET | PLAYER_FLAG_SHIELD_REGULAR);
    ShakeScreen(SCREENSHAKE_C_SHORT);

    player->objWork.shakeTimer    = 8;
    player->blinkTimer            = player->hurtInvulnDuration;
    player->colliders[0].defPower = PLAYER_DEFPOWER_INVINCIBLE;

    switch (player->characterID)
    {
        // case CHARACTER_SONIC:
        default:
            PlayPlayerSfx(player, PLAYER_SEQPLAYER_COMMON, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_OWA);
            break;

        case CHARACTER_BLAZE:
            PlayPlayerSfx(player, PLAYER_SEQPLAYER_COMMON, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_UPS);
            break;
    }
}

NONMATCH_FUNC void Player__Func_201DD24(Player *player)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, lr}
	ldr r1, [r0, #0x5d8]
	bic r1, r1, #0x2000
	str r1, [r0, #0x5d8]
	ldr r1, [r0, #0x5dc]
	bic r1, r1, #0x10
	str r1, [r0, #0x5dc]
	ldr r1, [r0, #0x5d8]
	orr r1, r1, #0x200000
	str r1, [r0, #0x5d8]
	ldr r1, [r0, #0x1c]
	orr r1, r1, #0x2080
	str r1, [r0, #0x1c]
	tst r1, #1
	bne _0201DD88
	ldr r1, [r0, #0x6d8]
	cmp r1, #0
	beq _0201DD88
	ldr r3, [r1, #0x44]
	ldr r1, =0x00141BB2
	ldr r2, [r0, #0x44]
	add r1, r3, r1
	sub r1, r1, r2
	str r1, [r0, #0x6f0]
	b _0201DDB4
_0201DD88:
	ldr r4, [r0, #0x6f0]
	ldr r1, =0x00059184
	ldr r2, =0x000E8A2E
	mov r3, #0
	mla r1, r4, r1, r2
	str r1, [r0, #0x6f0]
	ldr r1, [r0, #0x1c]
	bic r1, r1, #0x10
	str r1, [r0, #0x1c]
	str r3, [r0, #0x9c]
	str r3, [r0, #0x98]
_0201DDB4:
	mov r1, #0
	str r1, [r0, #0x6f4]
	ldr ip, [r0, #0x6f0]
	ldr r2, =0x0000647A
	mov r3, ip, asr #0x1f
	umull r4, lr, ip, r2
	mla lr, ip, r1, lr
	adds r4, r4, #0x800
	mla lr, r3, r2, lr
	adc r2, lr, #0
	mov r3, r4, lsr #0xc
	orr r3, r3, r2, lsl #20
	mov r3, r3, asr #2
	ldr ip, =0x66666667
	mov r2, r3, lsr #0x1f
	smull r3, r4, ip, r3
	add r4, r2, r4, asr #4
	str r4, [r0, #0x6f8]
	ldr r2, =Player__State_201DE24
	str r1, [r0, #0x28]
	str r2, [r0, #0xf4]
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__State_201DE24(Player *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, r7, lr}
	sub sp, sp, #8
	mov r7, r0
	ldr r0, [r7, #0x6d8]
	mov r4, #0
	cmp r0, #0
	ldrne r1, [r0, #0x44]
	ldrne r0, =0x00141BB2
	addne r4, r1, r0
	ldr r0, [r7, #0x6f4]
	cmp r0, #0
	beq _0201DE6C
	cmp r0, #1
	beq _0201E0C4
	cmp r0, #2
	beq _0201E108
	add sp, sp, #8
	ldmia sp!, {r3, r4, r5, r6, r7, pc}
_0201DE6C:
	ldr r0, [r7, #0x44]
	str r0, [r7, #0x8c]
	ldr r0, [r7, #0x48]
	str r0, [r7, #0x90]
	ldr r0, [r7, #0x4c]
	str r0, [r7, #0x94]
	ldr r1, [r7, #0x1c]
	tst r1, #1
	beq _0201DEF8
	add r0, r7, #0x500
	ldrsh r0, [r0, #0xd4]
	cmp r0, #0x28
	beq _0201DF34
	bic r0, r1, #0x10
	str r0, [r7, #0x1c]
	mov r1, #0
	str r1, [r7, #0x9c]
	str r1, [r7, #0x98]
	mov r0, r7
	mov r1, #0x28
	bl Player__ChangeAction
	ldr r0, [r7, #0x20]
	mov r5, #0x37
	orr r2, r0, #4
	sub r1, r5, #0x38
	add r0, r7, #0x258
	str r2, [r7, #0x20]
	mov r2, #0
	str r2, [sp]
	mov r2, r1
	mov r3, r1
	add r0, r0, #0x400
	str r5, [sp, #4]
	bl PlaySfxEx
	b _0201DF34
_0201DEF8:
	ldr r1, [r7, #0x98]
	cmp r1, #0
	ldreq r0, [r7, #0x9c]
	cmpeq r0, #0
	beq _0201DF34
	ldr r0, [r7, #0x6f0]
	sub r0, r0, r1
	str r0, [r7, #0x6f0]
	ldr r1, [r7, #0x9c]
	ldr r0, [r7, #0xd8]
	add r1, r1, r0
	str r1, [r7, #0x9c]
	ldr r0, [r7, #0x48]
	add r0, r0, r1
	str r0, [r7, #0x48]
_0201DF34:
	ldrh r5, [r7, #0x32]
	ldr r6, [r7, #0x6f0]
	ldr r2, =0x00000199
	mov r0, r5
	mov r1, #0
	bl ObjRoopMove16
	strh r0, [r7, #0x32]
	ldrh r1, [r7, #0x32]
	ldr r2, =FX_SinCosTable_
	mov r0, r6, asr #0x1f
	add r1, r1, #0x4000
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	add r1, r1, #0x8000
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	mov r1, r1, asr #4
	mov r1, r1, lsl #1
	add r3, r1, #1
	mov r3, r3, lsl #1
	ldrsh r2, [r2, r3]
	smull ip, r3, r2, r6
	adds ip, ip, #0x800
	adc r2, r3, #0
	mov r3, ip, lsr #0xc
	orr r3, r3, r2, lsl #20
	add r2, r4, r3
	str r2, [r7, #0x44]
	ldrh r3, [r7, #0x32]
	sub r2, r5, r3
	mov r2, r2, lsl #0x10
	movs r4, r2, asr #0x10
	ldr r2, =0x00000199
	rsbmi r4, r4, #0
	cmp r4, r2
	bge _0201E03C
	mov r3, r3, lsl #0x10
	mov r2, r5, lsl #0x10
	mov r3, r3, asr #0x10
	rsbs r4, r3, r2, asr #16
	ldr r2, =0x0000C199
	rsbmi r4, r4, #0
	sub r2, r2, r4
	mov r2, r2, lsl #0x10
	mov r2, r2, lsr #0x10
	mov r2, r2, lsl #0x10
	mov r2, r2, lsr #0x10
	mov r2, r2, asr #4
	mov r2, r2, lsl #1
	add r2, r2, #1
	ldr r3, =FX_SinCosTable_
	mov r2, r2, lsl #1
	ldrsh r2, [r3, r2]
	ldr r5, [r7, #0x44]
	umull r4, r3, r2, r6
	mla r3, r2, r0, r3
	mov r2, r2, asr #0x1f
	mla r3, r2, r6, r3
	adds r4, r4, #0x800
	adc r2, r3, #0
	mov r3, r4, lsr #0xc
	orr r3, r3, r2, lsl #20
	add r2, r5, r3
	str r2, [r7, #0x44]
_0201E03C:
	ldr r2, =FX_SinCosTable_
	mov r1, r1, lsl #1
	ldrsh r1, [r2, r1]
	umull r3, r2, r1, r6
	mla r2, r1, r0, r2
	mov r0, r1, asr #0x1f
	adds r1, r3, #0x800
	mla r2, r0, r6, r2
	adc r0, r2, #0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #20
	rsb r0, r1, #0
	str r0, [r7, #0x2c]
	ldr r1, [r7, #0x44]
	ldr r0, [r7, #0x8c]
	sub r0, r1, r0
	str r0, [r7, #0xbc]
	ldr r1, [r7, #0x48]
	ldr r0, [r7, #0x90]
	sub r0, r1, r0
	str r0, [r7, #0xc0]
	ldr r1, [r7, #0x4c]
	ldr r0, [r7, #0x94]
	sub r0, r1, r0
	str r0, [r7, #0xc4]
	ldrh r0, [r7, #0x32]
	cmp r0, #0
	addne sp, sp, #8
	ldmneia sp!, {r3, r4, r5, r6, r7, pc}
	ldr r0, [r7, #0x6f4]
	add sp, sp, #8
	add r0, r0, #1
	str r0, [r7, #0x6f4]
	ldmia sp!, {r3, r4, r5, r6, r7, pc}
_0201E0C4:
	ldr r0, [r7, #0x1c]
	add r2, r4, #0x12c000
	bic r0, r0, #0x2080
	str r0, [r7, #0x1c]
	ldr r0, [r7, #0x20]
	orr r0, r0, #0x200
	str r0, [r7, #0x20]
	ldr r1, [r7, #0x6f8]
	str r1, [r7, #0x98]
	ldr r0, [r7, #0x44]
	sub r0, r2, r0
	bl FX_DivS32
	add r0, r0, #0x78
	str r0, [r7, #0x28]
	ldr r0, [r7, #0x6f4]
	add r0, r0, #1
	str r0, [r7, #0x6f4]
_0201E108:
	ldr r1, [r7, #0x44]
	add r0, r4, #0x12c000
	cmp r1, r0
	addlt sp, sp, #8
	ldmltia sp!, {r3, r4, r5, r6, r7, pc}
	mov r0, r7
	bl Player__InitPhysics
	ldr r1, [r7, #0x1c]
	ldr r0, =0xEFFFEFFF
	add r3, r7, #0x258
	and r0, r1, r0
	orr r0, r0, #0x80
	str r0, [r7, #0x1c]
	ldr r0, [r7, #0x5d8]
	add r2, r7, #0x600
	bic r0, r0, #0x380000
	str r0, [r7, #0x5d8]
	ldr r0, [r7, #0x5dc]
	mov r1, #0
	bic r0, r0, #0x20
	str r0, [r7, #0x5dc]
	strh r1, [r2, #0xde]
	mov r4, #0x1e
	add r0, r3, #0x400
	strh r4, [r2, #0x98]
	bl NNS_SndPlayerStopSeq
	ldr r1, =0x000038E3
	ldr r2, =0xFFFEEEF0
	mov r0, r7
	bl Player__Action_Spring
	add r0, r7, #0x500
	mov r2, #0x5a
	ldr r1, =0x00000611
	strh r2, [r0, #0xfa]
	str r1, [r7, #0xd8]
	ldr r0, [r7, #0x5dc]
	ldr r1, =Player__OnDefend_Regular
	bic r0, r0, #0x2000000
	str r0, [r7, #0x5dc]
	mov r0, #0x1000
	str r1, [r7, #0x534]
	bl SetStageRingScale
	add sp, sp, #8
	ldmia sp!, {r3, r4, r5, r6, r7, pc}

// clang-format on
#endif
}

void Player__Gimmick_WaterRun(Player *player)
{
    if (!StageTaskStateMatches(&player->objWork, Player__State_WaterRun) && (player->objWork.moveFlag & STAGE_TASK_MOVE_FLAG_IN_AIR) == 0)
    {
        Player__InitGimmick(player, FALSE);
        Player__HandleStartWalkAnimation(player);
        player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;

        player->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_IN_AIR;
        player->objWork.moveFlag &= ~STAGE_TASK_MOVE_FLAG_HAS_GRAVITY;

        player->objWork.position.y = FX32_FROM_WHOLE(mapCamera.camera[player->cameraID].waterLevel - 15);
        SetTaskState(&player->objWork, Player__State_WaterRun);
        player->trickCooldownTimer = 8;

        PlayPlayerSfx(player, PLAYER_SEQPLAYER_COMMON, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_WATER_RUN);
    }
}

NONMATCH_FUNC void Player__State_WaterRun(Player *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, lr}
	mov r4, r0
	ldr r1, [r4, #0xc8]
	ldr r0, [r4, #0x648]
	cmp r1, #0
	rsblt r1, r1, #0
	cmp r1, r0
	bge _0201E304
	mov r0, r4
	bl Player__HandleFallOffSurface
	cmp r0, #0
	beq _0201E304
	add r0, r4, #0x254
	add r0, r0, #0x400
	mov r1, #0
	bl NNS_SndPlayerStopSeq
	mov r0, #0
	strh r0, [r4, #0x34]
	ldr r1, [r4, #0x1c]
	mov r0, r4
	orr r1, r1, #0x80
	str r1, [r4, #0x1c]
	bl Player__Action_Launch
	ldmia sp!, {r4, pc}
_0201E304:
	add r0, r4, #0x700
	ldrh r0, [r0, #0x22]
	tst r0, #3
	ldrne r0, [r4, #0x5f0]
	cmpne r0, #0
	beq _0201E350
	add r0, r4, #0x254
	add r0, r0, #0x400
	mov r1, #0
	bl NNS_SndPlayerStopSeq
	mov r0, #0
	strh r0, [r4, #0x34]
	ldr r1, [r4, #0x1c]
	mov r0, r4
	orr r1, r1, #0x80
	str r1, [r4, #0x1c]
	ldr r1, [r4, #0x5f0]
	blx r1
	ldmia sp!, {r4, pc}
_0201E350:
	add r0, r4, #0x500
	ldrsh r1, [r0, #0xd6]
	cmp r1, #0
	subne r1, r1, #1
	strneh r1, [r0, #0xd6]
	bne _0201E3BC
	ldr r0, [r4, #0x1c]
	tst r0, #0xd
	beq _0201E3BC
	add r0, r4, #0x254
	add r0, r0, #0x400
	mov r1, #0
	bl NNS_SndPlayerStopSeq
	mov r1, #0
	strh r1, [r4, #0x34]
	ldr r2, [r4, #0x1c]
	mov r0, r4
	bic r2, r2, #0x2000
	orr r2, r2, #0x80
	str r2, [r4, #0x1c]
	ldr r2, [r4, #0xc8]
	str r2, [r4, #0x98]
	bl Player__Action_LandOnGround
	ldr r1, [r4, #0x5e4]
	mov r0, r4
	blx r1
	ldmia sp!, {r4, pc}
_0201E3BC:
	ldr r1, [r4, #0xc8]
	mov r0, r4
	bl Player__SetAnimSpeedFromVelocity
	mov r0, r4
	bl Player__HandleActiveWalkAnimation
	mov r0, r4
	bl Player__HandleGroundMovement
	ldr r0, =playerGameStatus
	ldr r0, [r0, #0xc]
	tst r0, #7
	ldmneia sp!, {r4, pc}
	mov r0, r4
	bl CreateEffectWaterWakeForPlayer
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}

void Player__Action_SteamFan(Player *player, GameObjectTask *other, s32 fanRadius)
{
    if (player->gimmickObj != other)
    {
        if ((player->objWork.moveFlag & STAGE_TASK_MOVE_FLAG_DISABLE_SLOPE_ANGLES) != 0)
        {
            player->objWork.groundVel = FX_Sqrt(MT_SQUARED(player->objWork.velocity.x >> 6) + MT_SQUARED(player->objWork.velocity.y >> 6));
        }
        else
        {
            player->objWork.groundVel = MATH_ABS(player->objWork.groundVel);
        }

        player->objWork.velocity.x = FLOAT_TO_FX32(0.5);

        Player__InitPhysics(player);
        Player__InitGimmick(player, FALSE);
        player->gimmickObj = other;
        if (player->actionState != PLAYER_ACTION_2C)
        {
            Player__ChangeAction(player, PLAYER_ACTION_2C);
            player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;
        }
        SetTaskState(&player->objWork, Player__State_SteamFan);
        player->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_4000 | STAGE_TASK_MOVE_FLAG_DISABLE_MOVE_EVENT | STAGE_TASK_MOVE_FLAG_DISABLE_COLLIDE_EVENT | STAGE_TASK_MOVE_FLAG_IN_AIR;
        player->objWork.displayFlag &= ~DISPLAY_FLAG_FLIP_X;
        player->gimmickFlag |= PLAYER_GIMMICK_GRABBED;
        player->playerFlag |= PLAYER_FLAG_DISABLE_TENSION_DRAIN;

        player->objWork.velocity.y = player->objWork.velocity.z = FLOAT_TO_FX32(0.0);

        player->objWork.dir.z = FLOAT_DEG_TO_IDX(0.0);

        player->gimmickValue1 = FX_Sqrt(SquaredFX(player->gimmickObj->objWork.position.x - player->objWork.position.x)
                                        + SquaredFX(player->gimmickObj->objWork.position.y - player->objWork.position.y));
        player->gimmickValue2 = fanRadius;
    }
}

void Player__State_SteamFan(Player *work)
{
    if (work->gimmickObj == NULL || (work->inputKeyPress & PLAYER_INPUT_JUMP) != 0)
    {
        work->objWork.moveFlag &= ~(STAGE_TASK_MOVE_FLAG_4000 | STAGE_TASK_MOVE_FLAG_DISABLE_MOVE_EVENT | STAGE_TASK_MOVE_FLAG_DISABLE_COLLIDE_EVENT);
        work->gimmickFlag &= ~PLAYER_GIMMICK_GRABBED;
        work->playerFlag &= ~PLAYER_FLAG_DISABLE_TENSION_DRAIN;

        work->objWork.dir.z      = FLOAT_DEG_TO_IDX(0.0);
        work->objWork.velocity.x = work->objWork.groundVel = FLOAT_TO_FX32(0.0);
        work->actionJump(work);
        work->playerFlag |= PLAYER_FLAG_USER_FLAG;

        if (work->gimmickObj != NULL)
        {
            u16 angle = FX_Atan2Idx(work->objWork.position.y - work->gimmickObj->objWork.position.y, work->objWork.position.x - work->gimmickObj->objWork.position.x);

            work->objWork.velocity.x = MultiplyFX(CosFX((s32)angle), work->gimmickValue2);
            work->objWork.velocity.y = MultiplyFX(SinFX((s32)angle), work->gimmickValue2);

            if (work->objWork.velocity.x >= FLOAT_TO_FX32(0.0))
                work->objWork.displayFlag &= ~DISPLAY_FLAG_FLIP_X;
            else
                work->objWork.displayFlag |= DISPLAY_FLAG_FLIP_X;
        }

        work->overSpeedLimitTimer = 30;
        work->gimmickObj          = NULL;
    }
    else
    {
        u16 angle = work->gimmickObj->objWork.dir.z;

        fx32 radius;
        if (work->objWork.groundVel != FLOAT_TO_FX32(0.0))
        {
            work->gimmickValue1 = ObjSpdDownSet(work->gimmickValue1, work->objWork.groundVel);
            radius              = work->gimmickValue1;

            work->objWork.groundVel -= (work->objWork.groundVel >> 3);
            if (work->objWork.groundVel < FLOAT_TO_FX32(0.125) || !work->gimmickValue1)
                work->objWork.groundVel = FLOAT_TO_FX32(0.0);
        }
        else
        {
            if (work->gimmickValue1 > FLOAT_TO_FX32(40.0))
            {
                radius                   = MATH_MAX(work->gimmickValue1 - work->objWork.velocity.x, FLOAT_TO_FX32(40.0));
                work->gimmickValue1      = radius;
                work->objWork.velocity.x = ObjSpdUpSet(work->objWork.velocity.x, FLOAT_TO_FX32(0.25), FLOAT_TO_FX32(2.0));
            }
            else if (work->gimmickValue1 < FLOAT_TO_FX32(40.0))
            {
                radius                   = MATH_MIN(work->gimmickValue1 + work->objWork.velocity.x, FLOAT_TO_FX32(40.0));
                work->gimmickValue1      = radius;
                work->objWork.velocity.x = ObjSpdUpSet(work->objWork.velocity.x, FLOAT_TO_FX32(0.0625), FLOAT_TO_FX32(2.5));
            }
            else
            {
                radius = FLOAT_TO_FX32(40.0);
            }
        }

        work->objWork.position.x = work->gimmickObj->objWork.position.x + MultiplyFX(CosFX((s32)angle), radius);
        work->objWork.position.y = work->gimmickObj->objWork.position.y + MultiplyFX(SinFX((s32)angle), radius);

        work->objWork.prevPosition.x = work->objWork.position.x;
        work->objWork.prevPosition.y = work->objWork.position.y;

        work->objWork.move.x = work->objWork.position.x - work->objWork.prevPosition.x;
        work->objWork.move.y = work->objWork.position.y - work->objWork.prevPosition.y;
        work->objWork.move.z = work->objWork.position.z - work->objWork.prevPosition.z;
    }
}

void Player__Action_PopSteam(Player *player, GameObjectTask *other, fx32 velX, fx32 velY, fx32 speedThreshold, BOOL allowTricks)
{
    if ((player->playerFlag & PLAYER_FLAG_DEATH) == 0)
    {
        Player__InitPhysics(player);
        Player__InitGimmick(player, TRUE);

        player->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_DISABLE_SLOPE_ANGLES | STAGE_TASK_MOVE_FLAG_IN_AIR;
        player->objWork.moveFlag &= ~(STAGE_TASK_MOVE_FLAG_HAS_GRAVITY | STAGE_TASK_MOVE_FLAG_TOUCHING_FLOOR);
        player->objWork.velocity.x = velX;
        player->objWork.velocity.y = velY;

        if (velX != FLOAT_TO_FX32(0.0))
        {
            player->objWork.position.y = other->objWork.position.y;
            Player__ChangeAction(player, PLAYER_ACTION_AIRFORWARD_01);

            if (player->objWork.velocity.x < FLOAT_TO_FX32(0.0))
            {
                if (player->objWork.groundVel > FLOAT_TO_FX32(0.0))
                    player->objWork.groundVel = FLOAT_TO_FX32(0.0);

                player->objWork.displayFlag |= DISPLAY_FLAG_FLIP_X;
            }
            else
            {
                if (player->objWork.groundVel < FLOAT_TO_FX32(0.0))
                    player->objWork.groundVel = FLOAT_TO_FX32(0.0);

                player->objWork.displayFlag &= ~DISPLAY_FLAG_FLIP_X;
            }
        }
        else
        {
            player->objWork.position.x = other->objWork.position.x;
            Player__ChangeAction(player, PLAYER_ACTION_AIRRISE);
            player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;
            if (player->objWork.velocity.y > FLOAT_TO_FX32(0.0))
                player->objWork.dir.z = FLOAT_DEG_TO_IDX(180.0);
        }

        ObjRect__SetAttackStat(&player->colliders[1], 0, 0);
        player->gimmickValue1 = speedThreshold;
        player->gimmickValue2 = other->objWork.position.x;
        player->gimmickValue3 = other->objWork.position.y;
        player->gimmickValue4 = allowTricks;

        velX = MATH_ABS(velX);
        velY = MATH_ABS(velY);

        if (velX >= velY)
            velX = velY;

        player->objWork.userTimer = velX;

        SetTaskState(&player->objWork, Player__State_PopSteam);
    }
}

void Player__State_PopSteam(Player *work)
{
    if ((work->objWork.moveFlag & STAGE_TASK_MOVE_FLAG_TOUCHING_FLOOR) != 0 || work->objWork.userTimer >= MATH_ABS(work->objWork.velocity.x) + MATH_ABS(work->objWork.velocity.y))
    {
        Player__Action_LandOnGround(work, FLOAT_DEG_TO_IDX(0.0));
        work->starComboCount = 0;
        work->onLandGround(work);
    }
    else
    {
        fx32 x = MATH_ABS(work->objWork.position.x - work->gimmickValue2);
        fx32 y = MATH_ABS(work->objWork.position.y - work->gimmickValue3);
        if (work->gimmickValue1 * FX32_TO_WHOLE(work->gimmickValue1) <= x * FX32_TO_WHOLE(x) + y * FX32_TO_WHOLE(y))
        {
            work->gimmickValue3 = 0;
            work->gimmickValue2 = 0;
            work->gimmickValue1 = 0;
            work->playerFlag &= ~(PLAYER_FLAG_DISABLE_TRICK_FINISHER | PLAYER_FLAG_FINISHED_TRICK_COMBO | PLAYER_FLAG_ALLOW_TRICKS | PLAYER_FLAG_USER_FLAG);
            work->playerFlag |= PLAYER_FLAG_USER_FLAG;

            if (work->gimmickValue4 != 0)
                work->playerFlag |= PLAYER_FLAG_ALLOW_TRICKS;

            work->objWork.userTimer  = 0;
            work->objWork.userWork   = 0;
            work->trickCooldownTimer = FLOAT_TO_FX32(0.0);
            if (work->objWork.velocity.x != FLOAT_TO_FX32(0.0))
            {
                work->overSpeedLimitTimer = 30;
                work->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_HAS_GRAVITY;
            }
            else
            {
                work->objWork.userTimer = 30;
            }

            SetTaskState(&work->objWork, Player__State_Air);
        }
    }
}

void Player__Action_DreamWing(Player *player, GameObjectTask *other, fx32 velX, fx32 velY, s32 burstDelay)
{
    if ((player->playerFlag & PLAYER_FLAG_DEATH) == 0)
    {
        Player__InitPhysics(player);
        Player__InitGimmick(player, FALSE);
        Player__ChangeAction(player, PLAYER_ACTION_DREAMWING);
        player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;
        player->gimmickObj = other;
        player->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_DISABLE_OBJ_COLLISIONS | STAGE_TASK_MOVE_FLAG_IN_AIR;
        player->objWork.moveFlag &= ~STAGE_TASK_MOVE_FLAG_HAS_GRAVITY;
        player->objWork.moveFlag &= ~STAGE_TASK_MOVE_FLAG_TOUCHING_FLOOR;

        player->objWork.dir.z = FLOAT_DEG_TO_IDX(0.0);
        player->gimmickValue4 = player->objWork.groundVel;

        player->objWork.velocity.x = velX;
        player->objWork.velocity.y = velY;
        player->objWork.groundVel  = FLOAT_TO_FX32(0.0);

        player->gimmickValue1 = -velY;
        if (velY <= FLOAT_TO_FX32(0.0))
            player->gimmickValue1 = FLOAT_TO_FX32(2.0);

        player->objWork.position.x = other->objWork.position.x;
        player->objWork.position.y = other->objWork.position.y + FLOAT_TO_FX32(16.0);
        player->gimmickValue2      = burstDelay;
        player->gimmickValue3      = 0;
        player->objWork.userFlag   = 0;

        if ((other->objWork.displayFlag & DISPLAY_FLAG_FLIP_X) != 0)
            player->objWork.displayFlag |= DISPLAY_FLAG_FLIP_X;
        else
            player->objWork.displayFlag &= ~DISPLAY_FLAG_FLIP_X;

        ObjRect__SetAttackStat(&player->colliders[1], 0, 0);
        player->objWork.userTimer = 8;
        player->objWork.userWork  = 0;
        SetTaskState(&player->objWork, Player__State_DreamWing);
        EffectButtonPrompt__Create(&player->objWork, 0);
    }
}

void Player__State_DreamWing(Player *work)
{
    if (work->gimmickObj == NULL)
    {
        work->objWork.moveFlag &= ~(STAGE_TASK_MOVE_FLAG_DISABLE_MOVE_EVENT | STAGE_TASK_MOVE_FLAG_DISABLE_OBJ_COLLISIONS);
        work->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_HAS_GRAVITY;
        work->objWork.groundVel = work->gimmickValue4;
        Player__Action_Launch(work);
        return;
    }

    if (work->objWork.userTimer != 0)
    {
        work->objWork.userTimer--;
        work->objWork.moveFlag &= ~STAGE_TASK_MOVE_FLAG_TOUCHING_ANY;
        if (work->objWork.userTimer == 0)
            work->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_DISABLE_OBJ_COLLISIONS;
    }
    else
    {
        if ((work->objWork.moveFlag & STAGE_TASK_MOVE_FLAG_TOUCHING_FLOOR) != 0)
        {
            work->objWork.groundVel = work->gimmickValue4;
            Player__Action_LandOnGround(work, FLOAT_DEG_TO_IDX(0.0));
            work->onLandGround(work);
            work->objWork.moveFlag &= ~(STAGE_TASK_MOVE_FLAG_DISABLE_MOVE_EVENT | STAGE_TASK_MOVE_FLAG_DISABLE_OBJ_COLLISIONS);
            work->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_HAS_GRAVITY;
            work->gimmickObj = NULL;
            return;
        }

        if ((work->objWork.moveFlag & STAGE_TASK_MOVE_FLAG_TOUCHING_LWALL) != 0
            || (work->objWork.moveFlag & STAGE_TASK_MOVE_FLAG_TOUCHING_CEILING) != 0 && work->objWork.move.y <= -FLOAT_TO_FX32(1.0)
            || (work->inputKeyPress & PLAYER_INPUT_JUMP) != 0)
        {
            work->objWork.groundVel = work->gimmickValue4;
            Player__Action_Launch(work);
            work->objWork.moveFlag &= ~(STAGE_TASK_MOVE_FLAG_DISABLE_MOVE_EVENT | STAGE_TASK_MOVE_FLAG_DISABLE_OBJ_COLLISIONS);
            work->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_HAS_GRAVITY;
            work->gimmickObj = NULL;
            return;
        }
    }

    if ((work->inputKeyPress & PAD_KEY_UP) != 0)
        work->objWork.userWork++;

    if (work->gimmickValue2 != 0)
    {
        work->gimmickValue2--;
        if (work->gimmickValue2 == 0)
            work->objWork.userFlag |= 1;
    }
    else if ((work->objWork.userFlag & 1) != 0)
    {
        work->objWork.velocity.y += FLOAT_TO_FX32(0.1640625);
        if (work->objWork.velocity.y >= work->gimmickValue1)
        {
            work->objWork.userFlag &= ~1;
            work->objWork.velocity.y = work->gimmickValue1;
        }
    }

    if ((work->inputKeyPress & PAD_KEY_UP) != 0)
    {
        work->objWork.userWork++;
        work->objWork.userFlag |= 2;
        work->gimmickValue3      = 15;
        work->objWork.velocity.y = -FLOAT_TO_FX32(5.0);
        work->objWork.userFlag &= ~1;
        work->gimmickValue2 = 15;
    }

    if (work->gimmickValue3 != 0)
    {
        work->gimmickValue3--;
        if (work->gimmickValue3 == 0)
            work->objWork.userFlag &= ~2;
    }
}

void Player__Action_LargePiston1(Player *player, GameObjectTask *other, fx32 velX, fx32 velY, fx32 velZ, fx32 delay)
{
    if ((player->playerFlag & PLAYER_FLAG_DEATH) == 0)
    {
        Player__InitPhysics(player);

        if (player->actionState >= PLAYER_ACTION_TRICK_FINISH_V_01 && player->actionState <= PLAYER_ACTION_TRICK_FINISH)
        {
            Player__InitGimmick(player, TRUE);
            Player__ChangeAction(player, PLAYER_ACTION_AIRRISE);
            player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;

            if (velX > FLOAT_TO_FX32(0.0))
                player->objWork.dir.x = -FLOAT_DEG_TO_IDX(67.5);
            else
                player->objWork.dir.x = -FLOAT_DEG_TO_IDX(112.5);
            player->objWork.dir.y = FLOAT_DEG_TO_IDX(22.5);
            player->objWork.dir.z = FLOAT_DEG_TO_IDX(90.0);
        }
        else
        {
            Player__InitGimmick(player, FALSE);
            Player__ChangeAction(player, PLAYER_ACTION_PISTON_01);

            player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;
            player->objWork.dir.x = FLOAT_DEG_TO_IDX(0.0);

            if (velX > FLOAT_TO_FX32(0.0))
                player->objWork.dir.y = -FLOAT_DEG_TO_IDX(22.5);
            else
                player->objWork.dir.y = FLOAT_DEG_TO_IDX(22.5);

            if (velY != FLOAT_TO_FX32(0.0))
                player->objWork.dir.z = FLOAT_DEG_TO_IDX(45.0);
            else
                player->objWork.dir.z = FLOAT_DEG_TO_IDX(0.0);
        }

        player->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_DISABLE_OBJ_COLLISIONS | STAGE_TASK_MOVE_FLAG_DISABLE_COLLIDE_EVENT | STAGE_TASK_MOVE_FLAG_IN_AIR;
        player->objWork.moveFlag &= ~(STAGE_TASK_MOVE_FLAG_HAS_GRAVITY | STAGE_TASK_MOVE_FLAG_USE_SLOPE_FORCES);

        player->gimmickFlag |= PLAYER_GIMMICK_4000000 | PLAYER_GIMMICK_GRABBED;
        player->playerFlag |= PLAYER_FLAG_DISABLE_TENSION_DRAIN;

        if (velX > FLOAT_TO_FX32(0.0))
            player->gimmickCamGimmickCenterOffsetX = 64;
        else
            player->gimmickCamGimmickCenterOffsetX = -64;

        player->objWork.moveFlag &= ~STAGE_TASK_MOVE_FLAG_TOUCHING_FLOOR;
        player->objWork.displayFlag &= ~DISPLAY_FLAG_FLIP_X;
        ObjRect__SetAttackStat(&player->colliders[1], 0, 0);

        player->objWork.position.x = other->objWork.position.x;
        player->objWork.position.y = other->objWork.position.y;
        player->objWork.position.z = FLOAT_TO_FX32(0.0);

        player->objWork.shakeTimer   = FLOAT_TO_FX32(8.0);
        player->objWork.hitstopTimer = FLOAT_TO_FX32(8.0);
        player->objWork.velocity.x   = velX;
        player->objWork.velocity.y   = velY;
        player->objWork.velocity.z   = velZ;
        player->objWork.userTimer    = delay;
        player->trickCooldownTimer   = 0;
        player->playerFlag &= ~PLAYER_FLAG_FINISHED_TRICK_COMBO;

        SetTaskState(&player->objWork, Player__State_LargePiston1);
    }
}

void Player__State_LargePiston1(Player *work)
{
    if (work->objWork.userTimer != 0)
    {
        work->objWork.userTimer = StageTask__DecrementBySpeed(work->objWork.userTimer);
    }
    else
    {
        if (MATH_ABS(work->objWork.velocity.x) > FLOAT_TO_FX32(3.25))
        {
            work->objWork.velocity.x = ObjSpdDownSet(work->objWork.velocity.x, FLOAT_TO_FX32(0.0625));
            if (MATH_ABS(work->objWork.velocity.x) <= FLOAT_TO_FX32(3.25))
            {
                if (work->objWork.velocity.x >= FLOAT_TO_FX32(0.0))
                    work->objWork.velocity.x = FLOAT_TO_FX32(3.25);
                else
                    work->objWork.velocity.x = -FLOAT_TO_FX32(3.25);
            }
        }
    }

    if (work->objWork.velocity.z > FLOAT_TO_FX32(5.5))
    {
        work->objWork.velocity.z = ObjSpdDownSet(work->objWork.velocity.z, FLOAT_TO_FX32(0.125));
        if (work->objWork.velocity.z <= FLOAT_TO_FX32(5.5))
            work->objWork.velocity.z = FLOAT_TO_FX32(5.5);
    }

    if (work->objWork.hitstopTimer == FLOAT_TO_FX32(0.0))
    {
        if ((work->inputKeyPress & PLAYER_INPUT_JUMP) != 0)
            work->objWork.userWork = work->inputKeyPress;

        work->trickCooldownTimer++;
        if (work->trickCooldownTimer > 255)
            work->trickCooldownTimer = 255;

        if ((work->playerFlag & PLAYER_FLAG_FINISHED_TRICK_COMBO) == 0)
        {
            if (work->trickCooldownTimer > 24
                || (work->actionState < PLAYER_ACTION_TRICK_FINISH_H_01 || work->actionState > PLAYER_ACTION_TRICK_FINISH)
                       && (work->actionState < PLAYER_ACTION_TRICK_FINISH_H_SNOWBOARD_01 || work->actionState > PLAYER_ACTION_TRICK_FINISH_SNOWBOARD))
            {
                if (work->objWork.userWork != PAD_INPUT_FLAG_NONE)
                    Player__PerformTrick(work);
            }
        }
    }
    if (work->objWork.position.z >= FLOAT_TO_FX32(156.0))
    {
        work->objWork.moveFlag &= ~(STAGE_TASK_MOVE_FLAG_DISABLE_OBJ_COLLISIONS | STAGE_TASK_MOVE_FLAG_DISABLE_COLLIDE_EVENT);
        work->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_HAS_GRAVITY | STAGE_TASK_MOVE_FLAG_USE_SLOPE_FORCES;
        work->gimmickFlag &= ~(PLAYER_GIMMICK_GRABBED | PLAYER_GIMMICK_4000000);
        work->playerFlag &= PLAYER_FLAG_DISABLE_TENSION_DRAIN;

        work->gimmickCamGimmickCenterOffsetX = 0;
        work->objWork.velocity.z             = FLOAT_TO_FX32(0.0);
        work->objWork.dir.y                  = FLOAT_DEG_TO_IDX(0.0);

        Player__Action_Launch(work);
    }
}

void Player__Action_LargePiston2(Player *player, GameObjectTask *other, fx32 velX, fx32 velY, fx32 velZ, fx32 delay)
{
    if ((player->playerFlag & PLAYER_FLAG_DEATH) == 0 && StageTaskStateMatches(&player->objWork, Player__State_LargePiston1))
    {
        ObjRect__SetAttackStat(&player->colliders[1], 0, 0);

        if (player->actionState >= PLAYER_ACTION_TRICK_FINISH_V_01 && player->actionState <= PLAYER_ACTION_TRICK_FINISH)
        {
            Player__ChangeAction(player, PLAYER_ACTION_AIRRISE);
            player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;

            if (velY != FLOAT_TO_FX32(0.0))
            {
                player->objWork.dir.x = FLOAT_DEG_TO_IDX(0.0);

                if (velX >= FLOAT_TO_FX32(0.0))
                {
                    player->objWork.dir.y = FLOAT_DEG_TO_IDX(45.0);
                    player->objWork.dir.z = FLOAT_DEG_TO_IDX(67.5);
                }
                else
                {
                    player->objWork.dir.y = FLOAT_DEG_TO_IDX(135.0);
                    player->objWork.dir.z = -FLOAT_DEG_TO_IDX(67.5);
                }
            }
            else
            {
                player->objWork.dir.x = FLOAT_DEG_TO_IDX(45.0);
                player->objWork.dir.y = FLOAT_DEG_TO_IDX(45.0);
                player->objWork.dir.z = FLOAT_DEG_TO_IDX(67.5);
            }
        }
        else
        {
            player->starComboCount = 0;
            player->gimmickFlag &= ~PLAYER_GIMMICK_ALLOW_TRICK_COMBO;

            Player__ChangeAction(player, PLAYER_ACTION_PISTON_02);
            player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;

            player->objWork.dir.x = FLOAT_DEG_TO_IDX(0.0);

            if (velX >= FLOAT_TO_FX32(0.0))
                player->objWork.dir.y = FLOAT_DEG_TO_IDX(22.5);
            else
                player->objWork.dir.y = -FLOAT_DEG_TO_IDX(22.5);

            if (velY != FLOAT_TO_FX32(0.0))
                player->objWork.dir.z = FLOAT_DEG_TO_IDX(45.0);
            else
                player->objWork.dir.z = FLOAT_DEG_TO_IDX(0.0);
        }

        player->objWork.shakeTimer   = FLOAT_TO_FX32(8.0);
        player->objWork.hitstopTimer = FLOAT_TO_FX32(8.0);

        player->objWork.velocity.x = velX;
        player->objWork.velocity.y = velY;
        player->objWork.velocity.z = velZ;
        player->objWork.userTimer  = delay;
        player->trickCooldownTimer = 0;
        player->playerFlag &= ~PLAYER_FLAG_FINISHED_TRICK_COMBO;

        SetTaskState(&player->objWork, Player__State_LargePiston2);
    }
}

void Player__State_LargePiston2(Player *work)
{
    if (work->objWork.hitstopTimer == FLOAT_TO_FX32(0.0))
    {
        if (work->objWork.userTimer != 0)
        {
            work->objWork.userTimer = StageTask__DecrementBySpeed(work->objWork.userTimer);
        }
        else
        {
            if (MATH_ABS(work->objWork.velocity.x) > FLOAT_TO_FX32(3.25))
            {
                work->objWork.velocity.x = ObjSpdDownSet(work->objWork.velocity.x, FLOAT_TO_FX32(0.046875));
                if (MATH_ABS(work->objWork.velocity.x) <= FLOAT_TO_FX32(3.25))
                {
                    if (work->objWork.velocity.x >= FLOAT_TO_FX32(0.0))
                        work->objWork.velocity.x = FLOAT_TO_FX32(3.25);
                    else
                        work->objWork.velocity.x = -FLOAT_TO_FX32(3.25);
                }
            }
        }

        if (work->objWork.velocity.z < -FLOAT_TO_FX32(3.5))
        {
            work->objWork.velocity.z = ObjSpdDownSet(work->objWork.velocity.z, FLOAT_TO_FX32(0.25));
            if (work->objWork.velocity.z >= -FLOAT_TO_FX32(3.5))
                work->objWork.velocity.z = -FLOAT_TO_FX32(3.5);
        }
    }

    if (work->objWork.hitstopTimer == FLOAT_TO_FX32(0.0))
    {
        if ((work->inputKeyPress & PLAYER_INPUT_JUMP) != 0)
            work->objWork.userWork = work->inputKeyPress;

        work->trickCooldownTimer++;
        if (work->trickCooldownTimer > 255)
            work->trickCooldownTimer = 255;

        if ((work->playerFlag & PLAYER_FLAG_FINISHED_TRICK_COMBO) == 0)
        {
            if (work->trickCooldownTimer > 24
                || (work->actionState < PLAYER_ACTION_TRICK_FINISH_H_01 || work->actionState > PLAYER_ACTION_TRICK_FINISH)
                       && (work->actionState < PLAYER_ACTION_TRICK_FINISH_H_SNOWBOARD_01 || work->actionState > PLAYER_ACTION_TRICK_FINISH_SNOWBOARD))
            {
                if (work->objWork.userWork != PAD_INPUT_FLAG_NONE)
                    Player__PerformTrick(work);
            }
        }
    }

    if (work->objWork.position.z <= FLOAT_TO_FX32(0.0))
    {
        fx32 velX      = work->objWork.velocity.x;
        fx32 velY      = work->objWork.velocity.y;
        u32 playerFlag = work->playerFlag;

        work->objWork.moveFlag &= ~(STAGE_TASK_MOVE_FLAG_DISABLE_OBJ_COLLISIONS | STAGE_TASK_MOVE_FLAG_DISABLE_COLLIDE_EVENT);
        work->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_HAS_GRAVITY | STAGE_TASK_MOVE_FLAG_USE_SLOPE_FORCES;
        work->gimmickFlag &= ~(PLAYER_GIMMICK_GRABBED | PLAYER_GIMMICK_4000000);
        work->playerFlag &= ~PLAYER_FLAG_DISABLE_TENSION_DRAIN;

        work->gimmickCamGimmickCenterOffsetX = 0;
        work->objWork.velocity.z             = FLOAT_TO_FX32(0.0);
        work->objWork.dir.y                  = FLOAT_DEG_TO_IDX(0.0);

        Player__Action_Launch(work);

        work->overSpeedLimitTimer = 64;
        work->objWork.velocity.x  = 2 * velX;
        work->objWork.velocity.y  = velY;

        if (work->objWork.velocity.x >= FLOAT_TO_FX32(0.0))
            work->objWork.displayFlag &= ~DISPLAY_FLAG_FLIP_X;
        else
            work->objWork.displayFlag |= DISPLAY_FLAG_FLIP_X;

        work->playerFlag |= playerFlag & PLAYER_FLAG_FINISHED_TRICK_COMBO | PLAYER_FLAG_ALLOW_TRICKS;
    }
}

NONMATCH_FUNC void Player__Action_IcicleGrab(Player *player, GameObjectTask *other, s32 width)
{
    // https://decomp.me/scratch/ZvACC -> 99.76%
#ifdef NON_MATCHING
    if ((player->playerFlag & PLAYER_FLAG_DEATH) == 0)
    {
        Player__InitPhysics(player);
        Player__InitGimmick(player, FALSE);
        Player__ChangeAction(player, PLAYER_ACTION_ICICLE);

        player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;
        player->gimmickObj = other;
        player->objWork.moveFlag |= PLAYER_GIMMICK_2000 | PLAYER_GIMMICK_200 | PLAYER_GIMMICK_100 | PLAYER_GIMMICK_10;
        player->gimmickFlag |= PLAYER_GIMMICK_GRABBED | PLAYER_GIMMICK_10;
        player->playerFlag |= PLAYER_FLAG_DISABLE_TENSION_DRAIN;
        player->gimmickCamOffsetX = 0;
        player->objWork.dir.x = player->objWork.dir.y = player->objWork.dir.z = 0;
        player->objWork.displayFlag &= ~DISPLAY_FLAG_FLIP_X;

        ObjRect__SetAttackStat(&player->colliders[1], 0, 0);

        player->gimmickValue1 = width;
        fx32 icicleY          = other->objWork.position.y - FLOAT_TO_FX32(256.0);

        fx32 size;
        if (player->objWork.position.y > icicleY)
            size = FX_Div(68 * (player->gimmickValue1 - (player->objWork.position.y - icicleY)), player->gimmickValue1);
        else
            size = FLOAT_TO_FX32(68.0);

        if (player->objWork.position.x <= other->objWork.position.x)
        {
            player->objWork.position.x -= (size >> 1);
            player->gimmickValue2 = FLOAT_DEG_TO_IDX(0.0);
        }
        else
        {
            player->objWork.position.x += (size >> 1);
            player->gimmickValue2 = FLOAT_DEG_TO_IDX(180.0);
        }

        player->objWork.position.z = 0;
        player->objWork.velocity.x = player->objWork.velocity.y = 0;

        SetTaskState(&player->objWork, Player__State_IcicleGrab);
        PlayPlayerSfx(player, PLAYER_SEQPLAYER_COMMON, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_ICICLE_TURNING);
    }
#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #8
	mov r6, r0
	ldr r3, [r6, #0x5d8]
	mov r5, r1
	tst r3, #0x400
	mov r4, r2
	addne sp, sp, #8
	ldmneia sp!, {r4, r5, r6, pc}
	bl Player__InitPhysics
	mov r0, r6
	mov r1, #0
	bl Player__InitGimmick
	mov r0, r6
	mov r1, #0x2e
	bl Player__ChangeAction
	ldr r0, [r6, #0x20]
	mov r1, #0
	orr r0, r0, #4
	str r0, [r6, #0x20]
	str r5, [r6, #0x6d8]
	ldr r2, [r6, #0x1c]
	add r0, r6, #0x600
	orr r2, r2, #0x310
	orr r2, r2, #0x2000
	str r2, [r6, #0x1c]
	ldr r2, [r6, #0x5dc]
	orr r2, r2, #0x10
	orr r2, r2, #0x20000
	str r2, [r6, #0x5dc]
	ldr r2, [r6, #0x5d8]
	orr r2, r2, #0x100000
	str r2, [r6, #0x5d8]
	strh r1, [r0, #0xdc]
	strh r1, [r6, #0x34]
	strh r1, [r6, #0x32]
	strh r1, [r6, #0x30]
	ldr r2, [r6, #0x20]
	add r0, r6, #0x550
	bic r2, r2, #1
	str r2, [r6, #0x20]
	mov r2, r1
	bl ObjRect__SetAttackStat
	str r4, [r6, #0x6f0]
	ldr r1, [r5, #0x48]
	ldr r0, [r6, #0x48]
	sub r2, r1, #0x100000
	cmp r0, r2
	movle r0, #0x44000
	ble _0201F488
	ldr r1, [r6, #0x6f0]
	sub r0, r0, r2
	sub r2, r1, r0
	mov r0, #0x44
	mul r0, r2, r0
	bl FX_Div
_0201F488:
	ldr r2, [r5, #0x44]
	ldr r1, [r6, #0x44]
	cmp r1, r2
	addgt r0, r2, r0, asr #1
	strgt r0, [r6, #0x44]
	movgt r0, #0x8000
	bgt _0201F4B0
	sub r0, r2, r0, asr #1
	str r0, [r6, #0x44]
	mov r0, #0
_0201F4B0:
	str r0, [r6, #0x6f4]
	mov r3, #0
	str r3, [r6, #0x4c]
	str r3, [r6, #0x9c]
	mov r4, #0x52
	add r0, r6, #0x254
	ldr r2, =Player__State_IcicleGrab
	str r3, [r6, #0x98]
	str r2, [r6, #0xf4]
	sub r1, r4, #0x53
	str r3, [sp]
	mov r2, r1
	mov r3, r1
	add r0, r0, #0x400
	str r4, [sp, #4]
	bl PlaySfxEx
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, pc}

// clang-format on
#endif
}

void Player__State_IcicleGrab(Player *work)
{
    GameObjectTask *icicle = work->gimmickObj;
    if (icicle == NULL || (work->inputKeyPress & PLAYER_INPUT_JUMP) != 0)
    {
        work->gimmickFlag &= ~(PLAYER_GIMMICK_10 | PLAYER_GIMMICK_GRABBED);
        work->playerFlag &= ~PLAYER_FLAG_DISABLE_TENSION_DRAIN;
        work->objWork.moveFlag &= ~(STAGE_TASK_MOVE_FLAG_DISABLE_MOVE_EVENT | STAGE_TASK_MOVE_FLAG_DISABLE_OBJ_COLLISIONS | STAGE_TASK_MOVE_FLAG_DISABLE_COLLIDE_EVENT);
        work->objWork.dir.y     = FLOAT_DEG_TO_IDX(0.0);
        work->objWork.groundVel = FLOAT_TO_FX32(0.0);
        work->actionJump(work);

        work->playerFlag |= PLAYER_FLAG_USER_FLAG;
        work->objWork.velocity.y >>= 2;
        work->objWork.velocity.x = FLOAT_TO_FX32(3.0);

        if ((work->inputKeyDown & PAD_KEY_LEFT) != 0)
        {
            work->objWork.velocity.x = -work->objWork.velocity.x;
            work->objWork.displayFlag |= DISPLAY_FLAG_FLIP_X;
        }
        work->overSpeedLimitTimer = 30;
        work->gimmickObj          = NULL;

        StopPlayerSfx(work, PLAYER_SEQPLAYER_COMMON);
        return;
    }

    work->objWork.prevPosition.x = work->objWork.position.x;
    work->objWork.prevPosition.y = work->objWork.position.y;

    work->objWork.velocity.y = ObjSpdUpSet(work->objWork.velocity.y, FLOAT_TO_FX32(0.5), FLOAT_TO_FX32(4.0));
    work->objWork.position.y += work->objWork.velocity.y;

    fx32 icicleY = icicle->objWork.position.y - FLOAT_TO_FX32(256.0);

    fx32 size;
    if (work->objWork.position.y > icicleY)
        size = FX_Div(68 * (work->gimmickValue1 - (work->objWork.position.y - icicleY)), work->gimmickValue1);
    else
        size = FLOAT_TO_FX32(68.0);

    if (size <= FLOAT_TO_FX32(2.0))
    {
        work->gimmickFlag &= ~(PLAYER_GIMMICK_10 | PLAYER_GIMMICK_GRABBED);
        work->playerFlag &= ~PLAYER_FLAG_DISABLE_TENSION_DRAIN;
        work->objWork.moveFlag &= ~(STAGE_TASK_MOVE_FLAG_DISABLE_MOVE_EVENT | STAGE_TASK_MOVE_FLAG_DISABLE_OBJ_COLLISIONS | STAGE_TASK_MOVE_FLAG_DISABLE_COLLIDE_EVENT);
        work->objWork.dir.y      = FLOAT_DEG_TO_IDX(0.0);
        work->objWork.velocity.x = work->objWork.groundVel = FLOAT_TO_FX32(0.0);
        work->gimmickObj                                   = NULL;

        StopPlayerSfx(work, PLAYER_SEQPLAYER_COMMON);
        Player__Action_Launch(work);
    }
    else
    {
        work->gimmickValue2 += MultiplyFX(-64, (FLOAT_TO_FX32(68.0) - size)) - 128;
        work->objWork.dir.y = work->gimmickValue2;

        fx32 radius              = size >> 1;
        work->objWork.position.x = icicle->objWork.position.x + MultiplyFX(radius, CosFX((s32)(u16)(s32)(work->objWork.dir.y + FLOAT_DEG_TO_IDX(180.0))));
        work->objWork.position.z = MultiplyFX(radius, SinFX((s32)(u16)(s32)(work->objWork.dir.y + FLOAT_DEG_TO_IDX(180.0))));

        work->objWork.move.x = work->objWork.position.x - work->objWork.prevPosition.x;
        work->objWork.move.y = work->objWork.position.y - work->objWork.prevPosition.y;
        work->objWork.move.z = work->objWork.position.z - work->objWork.prevPosition.z;
    }
}

void Player__Action_IceSlide(Player *player, s32 _unused)
{
    if ((player->playerFlag & PLAYER_FLAG_DEATH) == 0 && !StageTaskStateMatches(&player->objWork, Player__State_IceSlide))
    {
        Player__InitGimmick(player, FALSE);
        Player__ChangeAction(player, PLAYER_ACTION_2F);
        player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;
        ObjRect__SetAttackStat(&player->colliders[1], 0, 0);

        if (MATH_ABS(player->objWork.velocity.x) < MATH_ABS(player->objWork.groundVel))
            player->objWork.velocity.x = player->objWork.groundVel;

        Player__Action_LandOnGround(player, player->objWork.dir.z);

        if (player->objWork.groundVel == FLOAT_TO_FX32(0.0))
        {
            if ((player->objWork.displayFlag & DISPLAY_FLAG_FLIP_X) != 0)
                player->objWork.groundVel = -FLOAT_TO_FX32(1.0);
            else
                player->objWork.groundVel = FLOAT_TO_FX32(1.0);
        }
        else
        {
            player->objWork.groundVel = MATH_ABS(player->objWork.groundVel);

            if (player->objWork.groundVel < FLOAT_TO_FX32(1.0))
                player->objWork.groundVel = FLOAT_TO_FX32(1.0);

            if (player->objWork.dir.z > FLOAT_DEG_TO_IDX(22.5) && player->objWork.dir.z < FLOAT_DEG_TO_IDX(337.5))
            {
                if (player->objWork.dir.z > FLOAT_DEG_TO_IDX(180.0))
                {
                    player->objWork.velocity.x = -player->objWork.velocity.x;
                    player->objWork.groundVel  = -player->objWork.groundVel;
                    if ((player->objWork.displayFlag & DISPLAY_FLAG_FLIP_X) == 0)
                    {
                        player->objWork.moveFlag &= ~STAGE_TASK_MOVE_FLAG_TOUCHING_LWALL;
                        player->objWork.displayFlag |= DISPLAY_FLAG_FLIP_X;
                    }
                }
                else
                {
                    if ((player->objWork.displayFlag & DISPLAY_FLAG_FLIP_X) != 0)
                    {
                        player->objWork.moveFlag &= ~STAGE_TASK_MOVE_FLAG_TOUCHING_LWALL;
                        player->objWork.displayFlag &= ~DISPLAY_FLAG_FLIP_X;
                    }
                }
            }
            else
            {
                if ((player->objWork.displayFlag & DISPLAY_FLAG_FLIP_X) != 0)
                {
                    player->objWork.velocity.x = -player->objWork.velocity.x;
                    player->objWork.groundVel  = -player->objWork.groundVel;
                }
            }
        }

        SetTaskState(&player->objWork, Player__State_IceSlide);
        PlayPlayerSfx(player, PLAYER_SEQPLAYER_COMMON, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_ICELAND);
    }
}

void Player__State_IceSlide(Player *player)
{
    if ((player->objWork.moveFlag & STAGE_TASK_MOVE_FLAG_TOUCHING_LWALL) != 0)
        player->objWork.displayFlag ^= DISPLAY_FLAG_FLIP_X;

    if ((player->objWork.moveFlag & STAGE_TASK_MOVE_FLAG_TOUCHING_FLOOR) == 0)
    {
        player->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_DISABLE_SLOPE_ANGLES | STAGE_TASK_MOVE_FLAG_IN_AIR;
        player->objWork.moveFlag &= ~STAGE_TASK_MOVE_FLAG_USE_SLOPE_ACCELERATION;

        player->objWork.velocity.x = MultiplyFX(player->objWork.groundVel, CosFX(player->objWork.dir.z));
        player->objWork.velocity.y = MultiplyFX(player->objWork.groundVel, SinFX(player->objWork.dir.z));

        if (player->objWork.velocity.x > -FLOAT_TO_FX32(2.0) && player->objWork.velocity.x < FLOAT_TO_FX32(2.0))
        {
            if ((player->objWork.displayFlag & DISPLAY_FLAG_FLIP_X) != 0)
                player->objWork.velocity.x = -FLOAT_TO_FX32(2.0);
            else
                player->objWork.velocity.x = FLOAT_TO_FX32(2.0);
        }

        player->gimmickValue1 = FLOAT_TO_FX32(0.625);
        Player__ChangeAction(player, PLAYER_ACTION_JUMPFALL);
        player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;
        SetTaskState(&player->objWork, Player__State_IceSlideLaunch);
        StopPlayerSfx(player, PLAYER_SEQPLAYER_COMMON);
    }

    if ((player->objWork.displayFlag & DISPLAY_FLAG_FLIP_X) != 0)
        player->objWork.groundVel = ObjSpdUpSet(player->objWork.groundVel, -FLOAT_TO_FX32(0.5), FLOAT_TO_FX32(8.0));
    else
        player->objWork.groundVel = ObjSpdUpSet(player->objWork.groundVel, FLOAT_TO_FX32(0.5), FLOAT_TO_FX32(8.0));
}

void Player__State_IceSlideLaunch(Player *work)
{
    if ((work->inputKeyPress & (PAD_BUTTON_A | PAD_BUTTON_B | PAD_BUTTON_R)) != 0)
    {
        work->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_USE_SLOPE_ACCELERATION;
        work->playerFlag |= PLAYER_FLAG_ALLOW_TRICKS | PLAYER_FLAG_USER_FLAG;
        SetTaskState(&work->objWork, Player__State_Air);
        work->objWork.userTimer  = 0;
        work->objWork.userWork   = 0;
        work->trickCooldownTimer = 0;
        work->objWork.dir.z      = FLOAT_DEG_TO_IDX(0.0);

        if ((work->inputKeyPress & PAD_BUTTON_R) != 0)
        {
            if ((work->inputKeyDown & PAD_KEY_UP) != 0)
            {
                Player__Action_TrickFinisherVertical(work);
            }
            else
            {
                if ((work->inputKeyDown & PAD_KEY_RIGHT) != 0)
                {
                    work->objWork.displayFlag &= ~DISPLAY_FLAG_FLIP_X;
                }
                else if ((work->inputKeyDown & PAD_KEY_LEFT) != 0)
                {
                    work->objWork.displayFlag |= DISPLAY_FLAG_FLIP_X;
                }
                Player__Action_TrickFinisherHorizontal(work);
            }
        }
        else
        {
            Player__PerformTrick(work);
        }
    }
    else if (work->objWork.move.y > FLOAT_TO_FX32(2.0) && (work->objWork.dir.z < FLOAT_DEG_TO_IDX(22.5) || work->objWork.dir.z > FLOAT_DEG_TO_IDX(337.5)))
    {
        work->objWork.moveFlag &= ~STAGE_TASK_MOVE_FLAG_DISABLE_SLOPE_ANGLES;
        work->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_USE_SLOPE_ACCELERATION;
        work->objWork.dir.z     = FLOAT_DEG_TO_IDX(0.0);
        work->objWork.groundVel = FLOAT_TO_FX32(0.0);

        fx32 velX = work->objWork.velocity.x;
        fx32 velY = work->objWork.velocity.y;
        Player__Action_Launch(work);
        work->objWork.velocity.x = velX;
        work->objWork.velocity.y = velY;
    }
    else
    {
        if ((work->objWork.moveFlag & STAGE_TASK_MOVE_FLAG_TOUCHING_FLOOR) != 0)
        {
            work->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_USE_SLOPE_ACCELERATION;
            work->objWork.dir.z     = FLOAT_DEG_TO_IDX(0.0);
            work->objWork.groundVel = work->objWork.velocity.x;
            Player__Action_LandOnGround(work, FLOAT_DEG_TO_IDX(0.0));
            work->onLandGround(work);
        }
        else
        {
            work->gimmickValue1 -= FLOAT_DEG_TO_IDX(0.087890625);
            if (work->gimmickValue1 < FLOAT_DEG_TO_IDX(5.625))
                work->gimmickValue1 = FLOAT_DEG_TO_IDX(5.625);

            fx32 spinSpeed = MultiplyFX(work->gimmickValue1, g_obj.speed);
            if ((work->objWork.displayFlag & DISPLAY_FLAG_FLIP_X) != 0)
                work->objWork.dir.z += (u16)spinSpeed;
            else
                work->objWork.dir.z -= (u16)spinSpeed;

            if ((work->objWork.displayFlag & DISPLAY_FLAG_FLIP_X) != 0)
            {
                if ((work->inputKeyDown & PAD_KEY_LEFT) != 0)
                {
                    work->objWork.velocity.x = ObjSpdUpSet(work->objWork.velocity.x, -FLOAT_TO_FX32(0.0625), FLOAT_TO_FX32(6.0));
                }
                else if ((work->inputKeyDown & PAD_KEY_RIGHT) != 0)
                {
                    work->objWork.velocity.x = ObjSpdDownSet(work->objWork.velocity.x, FLOAT_TO_FX32(0.0625));
                }
            }
            else
            {
                if ((work->inputKeyDown & PAD_KEY_RIGHT) != 0)
                {
                    work->objWork.velocity.x = ObjSpdUpSet(work->objWork.velocity.x, FLOAT_TO_FX32(0.0625), FLOAT_TO_FX32(6.0));
                }
                else if ((work->inputKeyDown & PAD_KEY_LEFT) != 0)
                {
                    work->objWork.velocity.x = ObjSpdDownSet(work->objWork.velocity.x, FLOAT_TO_FX32(0.0625));
                }
            }
        }
    }
}

void Player__Action_EnableSnowboard(Player *player, s32 a2)
{
    player->gimmickFlag |= PLAYER_GIMMICK_SNOWBOARD;

    switch (a2)
    {
        case 0:
            Player__Action_Launch(player);
            break;

        case 1:
            player->objWork.displayFlag &= ~DISPLAY_FLAG_FLIP_X;
            player->onLandGround(player);
            break;
    }
}

NONMATCH_FUNC void Player__Action_LoseSnowboard(Player *player)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, lr}
	ldr r1, [r0, #0x5dc]
	bic r1, r1, #0x800
	str r1, [r0, #0x5dc]
	ldr r1, [r0, #0x1c]
	orr r1, r1, #0x20000
	str r1, [r0, #0x1c]
	tst r1, #1
	beq _0201FD48
	ldr r1, [r0, #0xc8]
	ldr r2, [r0, #0x98]
	cmp r2, r1
	movge r1, r2
	mov r2, #0x6000
	cmp r1, #0x4800
	movlt r1, #0x4800
	rsb r2, r2, #0
	bl Player__Gimmick_201BAC0
	ldmia sp!, {r3, pc}
_0201FD48:
	ldr r1, [r0, #0x9c]
	cmp r1, #0
	bge _0201FD60
	mov r1, #0x19
	bl Player__ChangeAction
	ldmia sp!, {r3, pc}
_0201FD60:
	mov r1, #0x1a
	bl Player__ChangeAction
	ldmia sp!, {r3, pc}

// clang-format on
#endif
}

void Player__Action_Flipboard(Player *player, fx32 velX, fx32 velY)
{
    Player__Gimmick_201B418(player, velX, velY, TRUE);
}

NONMATCH_FUNC void Player__Gimmick_201FD7C(Player *player, GameObjectTask *other)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r4, r0
	ldr r2, [r4, #0x5d8]
	mov r5, r1
	tst r2, #0x400
	ldmneia sp!, {r3, r4, r5, pc}
	mov r1, #0
	bl Player__InitGimmick
	ldr r0, [r4, #0x1c]
	tst r0, #0x10
	beq _0201FDC0
	mov r0, r4
	mov r1, #0
	bl Player__Action_LandOnGround
	ldr r1, [r4, #0x5e4]
	mov r0, r4
	blx r1
_0201FDC0:
	str r5, [r4, #0x6d8]
	ldr r1, [r4, #0xf4]
	ldr r0, =Player__State_GroundIdle
	cmp r1, r0
	ldreq r0, =Player__Func_201FFD4
	streq r0, [r4, #0xf4]
	beq _0201FE00
	ldr r0, =Player__State_GroundMove
	cmp r1, r0
	ldreq r0, =Player__Func_201FF10
	streq r0, [r4, #0xf4]
	beq _0201FE00
	ldr r0, =Player__State_Roll
	cmp r1, r0
	ldreq r0, =Player__Func_2020098
	streq r0, [r4, #0xf4]
_0201FE00:
	ldr r0, [r4, #0x1c]
	orr r0, r0, #0x300
	str r0, [r4, #0x1c]
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__Func_201FE28(Player *player)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, lr}
	mov r4, r0
	ldr r1, [r4, #0xf4]
	ldr r0, =Player__State_GroundIdle
	cmp r1, r0
	ldreq r0, =Player__Func_201FF10
	streq r0, [r4, #0xf4]
	ldmeqia sp!, {r4, pc}
	ldr r0, =Player__State_GroundMove
	cmp r1, r0
	ldreq r0, =Player__Func_201FFD4
	streq r0, [r4, #0xf4]
	ldmeqia sp!, {r4, pc}
	ldr r0, =Player__State_Roll
	cmp r1, r0
	ldreq r0, =Player__Func_2020098
	streq r0, [r4, #0xf4]
	ldmeqia sp!, {r4, pc}
	ldr r0, =Player__State_Spindash
	cmp r1, r0
	ldreq r0, =Player__Func_202015C
	streq r0, [r4, #0xf4]
	ldmeqia sp!, {r4, pc}
	ldr r0, =Player__State_Crouch
	cmp r1, r0
	ldreq r0, =Player__Func_2020220
	streq r0, [r4, #0xf4]
	ldmeqia sp!, {r4, pc}
	ldr r0, [r4, #0x6d8]
	bl DiveStand__Func_2169F6C
	mov r0, #0
	str r0, [r4, #0x6d8]
	ldr r0, [r4, #0x1c]
	bic r0, r0, #0x2300
	str r0, [r4, #0x1c]
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__Func_201FEE0(Player *player){
#ifdef NON_MATCHING

#else
    // clang-format off
	ldr ip, [r0, #0x6d8]
	ldr r1, [r0, #0x48]
	ldr r2, [ip, #0x2c]
	ldr r3, [r0, #0xc0]
	sub r2, r2, #0xd000
	sub r1, r2, r1
	add r1, r3, r1
	str r1, [r0, #0xc0]
	ldr r1, [ip, #0x2c]
	sub r1, r1, #0xd000
	str r1, [r0, #0x48]
	bx lr

// clang-format on
#endif
}

NONMATCH_FUNC void Player__Func_201FF10(Player *player)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r4, r0
	ldr r2, [r4, #0x6d8]
	cmp r2, #0
	beq _0201FF64
	ldr r0, [r2, #0x340]
	ldrh r3, [r0, #2]
	cmp r3, #0x8f
	bne _0201FF48
	ldr r1, [r4, #0x44]
	ldr r0, [r2, #0x44]
	add r1, r1, #0x10000
	cmp r1, r0
	blt _0201FF64
_0201FF48:
	cmp r3, #0x95
	bne _0201FF8C
	ldr r1, [r4, #0x44]
	ldr r0, [r2, #0x44]
	sub r1, r1, #0x10000
	cmp r1, r0
	ble _0201FF8C
_0201FF64:
	mov r0, #0
	str r0, [r4, #0x6d8]
	ldr r0, [r4, #0x1c]
	ldr r1, =Player__State_GroundIdle
	bic r0, r0, #0x2300
	str r0, [r4, #0x1c]
	mov r0, r4
	str r1, [r4, #0xf4]
	bl Player__State_GroundIdle
	ldmia sp!, {r3, r4, r5, pc}
_0201FF8C:
	ldr r1, [r4, #0x1c]
	mov r0, r4
	orr r1, r1, #1
	str r1, [r4, #0x1c]
	ldr r1, [r4, #0x6d8]
	ldr r1, [r1, #0x28]
	strh r1, [r4, #0x34]
	bl Player__Func_201FEE0
	mov r0, r4
	ldr r5, [r4, #0xf4]
	bl Player__State_GroundIdle
	ldr r0, [r4, #0xf4]
	cmp r0, r5
	ldmeqia sp!, {r3, r4, r5, pc}
	mov r0, r4
	bl Player__Func_201FE28
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__Func_201FFD4(Player *player)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r4, r0
	ldr r2, [r4, #0x6d8]
	cmp r2, #0
	beq _02020028
	ldr r0, [r2, #0x340]
	ldrh r3, [r0, #2]
	cmp r3, #0x8f
	bne _0202000C
	ldr r1, [r4, #0x44]
	ldr r0, [r2, #0x44]
	add r1, r1, #0x10000
	cmp r1, r0
	blt _02020028
_0202000C:
	cmp r3, #0x95
	bne _02020050
	ldr r1, [r4, #0x44]
	ldr r0, [r2, #0x44]
	sub r1, r1, #0x10000
	cmp r1, r0
	ble _02020050
_02020028:
	mov r0, #0
	str r0, [r4, #0x6d8]
	ldr r0, [r4, #0x1c]
	ldr r1, =Player__State_GroundMove
	bic r0, r0, #0x2300
	str r0, [r4, #0x1c]
	mov r0, r4
	str r1, [r4, #0xf4]
	bl Player__State_GroundMove
	ldmia sp!, {r3, r4, r5, pc}
_02020050:
	ldr r1, [r4, #0x1c]
	mov r0, r4
	orr r1, r1, #1
	str r1, [r4, #0x1c]
	ldr r1, [r4, #0x6d8]
	ldr r1, [r1, #0x28]
	strh r1, [r4, #0x34]
	bl Player__Func_201FEE0
	mov r0, r4
	ldr r5, [r4, #0xf4]
	bl Player__State_GroundMove
	ldr r0, [r4, #0xf4]
	cmp r0, r5
	ldmeqia sp!, {r3, r4, r5, pc}
	mov r0, r4
	bl Player__Func_201FE28
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__Func_2020098(Player *player)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r4, r0
	ldr r2, [r4, #0x6d8]
	cmp r2, #0
	beq _020200EC
	ldr r0, [r2, #0x340]
	ldrh r3, [r0, #2]
	cmp r3, #0x8f
	bne _020200D0
	ldr r1, [r4, #0x44]
	ldr r0, [r2, #0x44]
	add r1, r1, #0x10000
	cmp r1, r0
	blt _020200EC
_020200D0:
	cmp r3, #0x95
	bne _02020114
	ldr r1, [r4, #0x44]
	ldr r0, [r2, #0x44]
	sub r1, r1, #0x10000
	cmp r1, r0
	ble _02020114
_020200EC:
	mov r0, #0
	str r0, [r4, #0x6d8]
	ldr r0, [r4, #0x1c]
	ldr r1, =Player__State_Roll
	bic r0, r0, #0x2300
	str r0, [r4, #0x1c]
	mov r0, r4
	str r1, [r4, #0xf4]
	bl Player__State_Roll
	ldmia sp!, {r3, r4, r5, pc}
_02020114:
	ldr r1, [r4, #0x1c]
	mov r0, r4
	orr r1, r1, #1
	str r1, [r4, #0x1c]
	ldr r1, [r4, #0x6d8]
	ldr r1, [r1, #0x28]
	strh r1, [r4, #0x34]
	bl Player__Func_201FEE0
	mov r0, r4
	ldr r5, [r4, #0xf4]
	bl Player__State_Roll
	ldr r0, [r4, #0xf4]
	cmp r0, r5
	ldmeqia sp!, {r3, r4, r5, pc}
	mov r0, r4
	bl Player__Func_201FE28
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__Func_202015C(Player *player)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r4, r0
	ldr r2, [r4, #0x6d8]
	cmp r2, #0
	beq _020201B0
	ldr r0, [r2, #0x340]
	ldrh r3, [r0, #2]
	cmp r3, #0x8f
	bne _02020194
	ldr r1, [r4, #0x44]
	ldr r0, [r2, #0x44]
	add r1, r1, #0x10000
	cmp r1, r0
	blt _020201B0
_02020194:
	cmp r3, #0x95
	bne _020201D8
	ldr r1, [r4, #0x44]
	ldr r0, [r2, #0x44]
	sub r1, r1, #0x10000
	cmp r1, r0
	ble _020201D8
_020201B0:
	mov r0, #0
	str r0, [r4, #0x6d8]
	ldr r0, [r4, #0x1c]
	ldr r1, =Player__State_Spindash
	bic r0, r0, #0x2300
	str r0, [r4, #0x1c]
	mov r0, r4
	str r1, [r4, #0xf4]
	bl Player__State_Spindash
	ldmia sp!, {r3, r4, r5, pc}
_020201D8:
	ldr r1, [r4, #0x1c]
	mov r0, r4
	orr r1, r1, #1
	str r1, [r4, #0x1c]
	ldr r1, [r4, #0x6d8]
	ldr r1, [r1, #0x28]
	strh r1, [r4, #0x34]
	bl Player__Func_201FEE0
	mov r0, r4
	ldr r5, [r4, #0xf4]
	bl Player__State_Spindash
	ldr r0, [r4, #0xf4]
	cmp r0, r5
	ldmeqia sp!, {r3, r4, r5, pc}
	mov r0, r4
	bl Player__Func_201FE28
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__Func_2020220(Player *player)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r4, r0
	ldr r2, [r4, #0x6d8]
	cmp r2, #0
	beq _02020274
	ldr r0, [r2, #0x340]
	ldrh r3, [r0, #2]
	cmp r3, #0x8f
	bne _02020258
	ldr r1, [r4, #0x44]
	ldr r0, [r2, #0x44]
	add r1, r1, #0x10000
	cmp r1, r0
	blt _02020274
_02020258:
	cmp r3, #0x95
	bne _0202029C
	ldr r1, [r4, #0x44]
	ldr r0, [r2, #0x44]
	sub r1, r1, #0x10000
	cmp r1, r0
	ble _0202029C
_02020274:
	mov r0, #0
	str r0, [r4, #0x6d8]
	ldr r0, [r4, #0x1c]
	ldr r1, =Player__State_Crouch
	bic r0, r0, #0x2300
	str r0, [r4, #0x1c]
	mov r0, r4
	str r1, [r4, #0xf4]
	bl Player__State_Crouch
	ldmia sp!, {r3, r4, r5, pc}
_0202029C:
	ldr r1, [r4, #0x1c]
	mov r0, r4
	orr r1, r1, #1
	str r1, [r4, #0x1c]
	ldr r1, [r4, #0x6d8]
	ldr r1, [r1, #0x28]
	strh r1, [r4, #0x34]
	bl Player__Func_201FEE0
	mov r0, r4
	ldr r5, [r4, #0xf4]
	bl Player__State_Crouch
	ldr r0, [r4, #0xf4]
	cmp r0, r5
	ldmeqia sp!, {r3, r4, r5, pc}
	mov r0, r4
	bl Player__Func_201FE28
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__Func_20202E4(Player *player, GameObjectTask *other)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r5, r0
	ldr r2, [r5, #0x5d8]
	mov r4, r1
	tst r2, #0x400
	ldmneia sp!, {r3, r4, r5, pc}
	ldr r1, [r5, #0x6d8]
	cmp r1, r4
	ldmneia sp!, {r3, r4, r5, pc}
	ldr r2, [r5, #0xf4]
	ldr r1, =Player__Func_20203B4
	cmp r2, r1
	ldmeqia sp!, {r3, r4, r5, pc}
	ldr r1, [r5, #0x5dc]
	tst r1, #0x800
	bne _02020330
	mov r1, #0x31
	bl Player__ChangeAction
	b _02020344
_02020330:
	mov r1, #0x5b
	bl Player__ChangeAction
	mov r0, r5
	mov r1, #0x1a
	bl ChangePlayerSnowboardAction
_02020344:
	ldr r0, [r5, #0x20]
	mov r1, #0
	orr r3, r0, #4
	mov r2, r1
	add r0, r5, #0x550
	str r3, [r5, #0x20]
	bl ObjRect__SetAttackStat
	mov r0, #0
	strh r0, [r5, #0x34]
	ldr r0, [r4, #0x340]
	ldrh r0, [r0, #2]
	cmp r0, #0x8f
	ldr r0, [r5, #0x20]
	biceq r0, r0, #1
	orrne r0, r0, #1
	str r0, [r5, #0x20]
	ldr r1, [r4, #0x8c]
	ldr r0, =Player__Func_20203B4
	str r1, [r5, #0x44]
	ldr r1, [r4, #0x90]
	add r1, r1, #0x2000
	str r1, [r5, #0x48]
	str r0, [r5, #0xf4]
	ldr r0, [r5, #0x1c]
	orr r0, r0, #0x2300
	str r0, [r5, #0x1c]
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__Func_20203B4(Player *player)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, lr}
	ldr r2, [r0, #0x6d8]
	cmp r2, #0
	bne _020203D8
	ldr r1, [r0, #0x1c]
	bic r1, r1, #0x2300
	str r1, [r0, #0x1c]
	bl Player__Action_Launch
	ldmia sp!, {r3, pc}
_020203D8:
	ldr r1, [r0, #0x44]
	str r1, [r0, #0x8c]
	ldr r1, [r0, #0x48]
	str r1, [r0, #0x90]
	ldr r1, [r2, #0x8c]
	str r1, [r0, #0x44]
	ldr r1, [r2, #0x90]
	add r1, r1, #0x2000
	str r1, [r0, #0x48]
	ldr r2, [r0, #0x44]
	ldr r1, [r0, #0x8c]
	sub r1, r2, r1
	str r1, [r0, #0xbc]
	ldr r2, [r0, #0x48]
	ldr r1, [r0, #0x90]
	sub r1, r2, r1
	str r1, [r0, #0xc0]
	ldmia sp!, {r3, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__Func_2020420(Player *player, GameObjectTask *other, fx32 velX, fx32 velY)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	mov r4, r0
	ldr r0, [r4, #0x6d8]
	cmp r0, r1
	moveq r0, #0
	streq r0, [r4, #0x6d8]
	mov r1, r2
	mov r0, r4
	mov r2, r3
	bl Player__Gimmick_Jump
	mov ip, #0x3c
	sub r1, ip, #0x3d
	add r0, r4, #0x254
	mov r2, #0
	str r2, [sp]
	mov r2, r1
	mov r3, r1
	add r0, r0, #0x400
	str ip, [sp, #4]
	bl PlaySfxEx
	add sp, sp, #8
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__Action_EnterHalfpipe(Player *player, GameObjectTask *other, BOOL flag)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r5, r0
	ldr r1, [r5, #0x5d8]
	mov r4, r2
	tst r1, #0x400
	ldmneia sp!, {r3, r4, r5, pc}
	ldr r2, [r5, #0xf4]
	ldr r1, =Player__State_Halfpipe
	cmp r2, r1
	ldmeqia sp!, {r3, r4, r5, pc}
	bl Player__InitPhysics
	mov r0, r5
	mov r1, #0
	bl Player__InitGimmick
	mov r1, #0
	mov r2, r1
	add r0, r5, #0x550
	bl ObjRect__SetAttackStat
	ldr r0, [r5, #0x5dc]
	orr r0, r0, #0x20000
	str r0, [r5, #0x5dc]
	ldr r0, [r5, #0x5d8]
	orr r0, r0, #0x100000
	str r0, [r5, #0x5d8]
	ldr r0, [r5, #0x1c]
	orr r0, r0, #0x2300
	str r0, [r5, #0x1c]
	ldr r0, [r5, #0x48]
	str r0, [r5, #0x6f0]
	ldr r0, [r5, #0xc8]
	cmp r0, #0
	bgt _0202050C
	bne _0202052C
	ldr r0, [r5, #0x20]
	tst r0, #1
	bne _0202052C
_0202050C:
	ldr r0, [r5, #0x20]
	bic r0, r0, #1
	str r0, [r5, #0x20]
	ldr r0, [r5, #0xc8]
	cmp r0, #0x2000
	movlt r0, #0x2000
	strlt r0, [r5, #0xc8]
	b _02020558
_0202052C:
	ldr r1, [r5, #0x20]
	mov r0, #0x2000
	orr r1, r1, #1
	str r1, [r5, #0x20]
	ldr r1, [r5, #0x5d8]
	rsb r0, r0, #0
	orr r1, r1, #1
	str r1, [r5, #0x5d8]
	ldr r1, [r5, #0xc8]
	cmp r1, r0
	strgt r0, [r5, #0xc8]
_02020558:
	cmp r4, #0
	ldrne r0, [r5, #0x5d8]
	orrne r0, r0, #1
	strne r0, [r5, #0x5d8]
	ldr r1, [r5, #0xc8]
	cmp r1, #0
	rsblt r1, r1, #0
	mov r0, r1, lsl #4
	add r0, r0, r1, lsl #5
	add r0, r0, r1, lsl #2
	str r0, [r5, #0x6f4]
	ldr r1, [r5, #0xc8]
	mov r0, #0
	str r1, [r5, #0x6fc]
	str r0, [r5, #0x2c]
	mov r0, #0xc000
	str r0, [r5, #0x6f8]
	ldr r0, [r5, #0x5dc]
	tst r0, #0x800
	mov r0, r5
	bne _020205B8
	mov r1, #0x30
	bl Player__ChangeAction
	b _020205CC
_020205B8:
	mov r1, #0x41
	bl Player__ChangeAction
	mov r0, r5
	mov r1, #3
	bl ChangePlayerSnowboardAction
_020205CC:
	ldr r1, [r5, #0x20]
	ldr r0, =Player__State_Halfpipe
	orr r1, r1, #4
	str r1, [r5, #0x20]
	str r0, [r5, #0xf4]
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__State_Halfpipe(Player *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	mov r4, r0
	ldr r1, [r4, #0x44]
	str r1, [r4, #0x8c]
	ldr r1, [r4, #0x48]
	str r1, [r4, #0x90]
	ldr r1, [r4, #0x4c]
	str r1, [r4, #0x94]
	bl Player__Func_2020DB8
	ldr r0, [r4, #0x6fc]
	cmp r0, #0x1000
	ble _0202063C
	movs r1, r0, asr #1
	rsbmi r2, r1, #0
	ldr r3, [r4, #0xc8]
	movpl r2, r1
	cmp r3, #0
	rsblt r3, r3, #0
	cmp r3, r2
	strlt r1, [r4, #0xc8]
	blt _02020664
_0202063C:
	cmp r0, #0x4000
	ble _02020664
	movs r0, r0, lsl #1
	rsbmi r1, r0, #0
	ldr r2, [r4, #0xc8]
	movpl r1, r0
	cmp r2, #0
	rsblt r2, r2, #0
	cmp r2, r1
	strgt r0, [r4, #0xc8]
_02020664:
	ldr r0, [r4, #0x6f8]
	add r0, r0, #0x99
	add r0, r0, #0x100
	str r0, [r4, #0x6f8]
	ldr r0, [r4, #0xc8]
	cmp r0, #0
	ble _02020694
	ldr r0, [r4, #0x44]
	add r0, r0, #0x198
	add r0, r0, #0x1800
	str r0, [r4, #0x44]
	b _020206D4
_02020694:
	bge _020206AC
	ldr r0, [r4, #0x44]
	sub r0, r0, #0x198
	sub r0, r0, #0x1800
	str r0, [r4, #0x44]
	b _020206D4
_020206AC:
	ldr r0, [r4, #0x20]
	tst r0, #1
	ldr r0, [r4, #0x44]
	addeq r0, r0, #0x198
	addeq r0, r0, #0x1800
	streq r0, [r4, #0x44]
	beq _020206D4
	sub r0, r0, #0x198
	sub r0, r0, #0x1800
	str r0, [r4, #0x44]
_020206D4:
	ldr r0, [r4, #0x6f8]
	ldr r2, [r4, #0x6f4]
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r1, r0, asr #4
	ldr r0, =FX_SinCosTable_
	mov r1, r1, lsl #2
	ldrsh r1, [r0, r1]
	mov r5, r2, asr #1
	mov r0, #0
	smull r3, r2, r1, r5
	adds r3, r3, #0x800
	adc r1, r2, #0
	mov r2, r3, lsr #0xc
	orr r2, r2, r1, lsl #20
	adds r5, r5, r2
	movmi r5, r0
	ldr r0, [r4, #0x6f0]
	sub r0, r0, r5
	str r0, [r4, #0x48]
	ldr r1, [r4, #0x44]
	ldr r0, [r4, #0x8c]
	sub r0, r1, r0
	str r0, [r4, #0xbc]
	ldr r1, [r4, #0x48]
	ldr r0, [r4, #0x90]
	sub r0, r1, r0
	str r0, [r4, #0xc0]
	ldr r0, [r4, #0x2c]
	cmp r0, #3
	addls pc, pc, r0, lsl #2
	b _02020AA8
_0202075C: // jump table
	b _0202076C // case 0
	b _02020818 // case 1
	b _020209AC // case 2
	b _02020A6C // case 3
_0202076C:
	cmp r5, #0x40000
	movgt r0, #0x40000
	movle r0, r5
	mov r1, #0x40000
	bl FX_Div
	bl Math__Func_207B14C
	strh r0, [r4, #0x30]
	ldr r0, [r4, #0x5d8]
	mov r1, r5
	tst r0, #1
	ldrneh r0, [r4, #0x30]
	rsbne r0, r0, #0x10000
	strneh r0, [r4, #0x30]
	mov r0, r4
	bl Player__Func_2020C00
	cmp r5, #0x80000
	blt _020207F8
	mov r0, #1
	str r0, [r4, #0x2c]
	ldr r0, [r4, #0x5dc]
	tst r0, #0x800
	beq _020207DC
	mov r0, r4
	mov r1, #0x42
	bl Player__ChangeAction
	mov r0, r4
	mov r1, #4
	bl ChangePlayerSnowboardAction
_020207DC:
	mov r1, #0
	str r1, [r4, #0x28]
	add r0, r4, #0x500
	strh r1, [r0, #0xd6]
	ldr r0, [r4, #0x5d8]
	bic r0, r0, #4
	str r0, [r4, #0x5d8]
_020207F8:
	ldr r0, [r4, #0xc0]
	cmp r0, #0
	movge r0, #2
	strge r0, [r4, #0x2c]
	ldr r0, [r4, #0x1c]
	orr r0, r0, #1
	str r0, [r4, #0x1c]
	b _02020AA8
_02020818:
	add r0, r4, #0x700
	ldrh r0, [r0, #0x22]
	tst r0, #3
	strne r0, [r4, #0x28]
	cmp r5, #0x80000
	bgt _02020878
	mov r0, #2
	str r0, [r4, #0x2c]
	ldr r0, [r4, #0x5dc]
	tst r0, #0x800
	mov r0, r4
	bne _02020854
	mov r1, #0x30
	bl Player__ChangeAction
	b _02020868
_02020854:
	mov r1, #0x41
	bl Player__ChangeAction
	mov r0, r4
	mov r1, #3
	bl ChangePlayerSnowboardAction
_02020868:
	ldr r0, [r4, #0x20]
	orr r0, r0, #4
	str r0, [r4, #0x20]
	b _02020990
_02020878:
	add r0, r4, #0x700
	ldrh r1, [r0, #0x22]
	ands r1, r1, #0x100
	beq _020208B4
	ldrh r0, [r0, #0x20]
	tst r0, #0x40
	beq _020208B4
	mov r0, r4
	bl Player__Action_ExitHalfpipe
	ldr r1, [r4, #0x5f0]
	mov r0, r4
	blx r1
	mov r0, r4
	bl Player__Action_TrickFinisherVertical
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_020208B4:
	cmp r1, #0
	beq _020208DC
	mov r0, r4
	bl Player__Action_ExitHalfpipe
	ldr r1, [r4, #0x5f0]
	mov r0, r4
	blx r1
	mov r0, r4
	bl Player__Action_TrickFinisherHorizontal
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_020208DC:
	add r0, r4, #0x500
	ldrsh r1, [r0, #0xd6]
	add r1, r1, #1
	strh r1, [r0, #0xd6]
	ldrsh r1, [r0, #0xd6]
	cmp r1, #0xff
	movgt r1, #0xff
	strgth r1, [r0, #0xd6]
	ldr r0, [r4, #0x5d8]
	tst r0, #4
	bne _02020950
	add r0, r4, #0x500
	ldrsh r1, [r0, #0xd6]
	cmp r1, #0x18
	bgt _0202093C
	ldrsh r0, [r0, #0xd4]
	cmp r0, #0x64
	blt _0202092C
	cmp r0, #0x69
	ble _02020950
_0202092C:
	cmp r0, #0x47
	blt _0202093C
	cmp r0, #0x4c
	ble _02020950
_0202093C:
	ldr r0, [r4, #0x28]
	cmp r0, #0
	beq _02020950
	mov r0, r4
	bl Player__PerformTrick
_02020950:
	ldr r0, [r4, #0xc0]
	mov r2, #0x200
	cmp r0, #0
	bgt _02020974
	ldrh r0, [r4, #0x30]
	mov r1, #0
	bl ObjRoopMove16
	strh r0, [r4, #0x30]
	b _02020990
_02020974:
	ldr r0, [r4, #0x5d8]
	tst r0, #1
	movne r1, #0xc000
	ldrh r0, [r4, #0x30]
	moveq r1, #0x4000
	bl ObjRoopMove16
	strh r0, [r4, #0x30]
_02020990:
	mov r0, r4
	mov r1, r5
	bl Player__Func_2020C00
	ldr r0, [r4, #0x1c]
	bic r0, r0, #1
	str r0, [r4, #0x1c]
	b _02020AA8
_020209AC:
	cmp r5, #0x40000
	movgt r0, #0x40000
	movle r0, r5
	mov r1, #0x40000
	bl FX_Div
	bl Math__Func_207B14C
	strh r0, [r4, #0x30]
	ldr r0, [r4, #0x5d8]
	mov r1, r5
	tst r0, #1
	ldrneh r0, [r4, #0x30]
	rsbne r0, r0, #0x10000
	strneh r0, [r4, #0x30]
	mov r0, r4
	bl Player__Func_2020C00
	ldr r0, [r4, #0xc0]
	cmp r0, #0
	bgt _02020A5C
	ldr r0, [r4, #0xc8]
	cmp r0, #0
	rsblt r0, r0, #0
	cmp r0, #0x80
	movge r0, #0
	strge r0, [r4, #0x2c]
	bge _02020A20
	mov r0, #3
	str r0, [r4, #0x2c]
	mov r0, #0
	str r0, [r4, #0xc8]
_02020A20:
	ldr r0, [r4, #0xc8]
	str r0, [r4, #0x6fc]
	ldr r0, [r4, #0x5d8]
	eor r0, r0, #1
	str r0, [r4, #0x5d8]
	ldr r1, [r4, #0xc8]
	ldr r0, [r4, #0x61c]
	cmp r1, #0
	rsblt r1, r1, #0
	cmp r1, r0
	movgt r1, r0
	mov r0, r1, lsl #4
	add r0, r0, r1, lsl #5
	add r0, r0, r1, lsl #2
	str r0, [r4, #0x6f4]
_02020A5C:
	ldr r0, [r4, #0x1c]
	orr r0, r0, #1
	str r0, [r4, #0x1c]
	b _02020AA8
_02020A6C:
	ldr r0, [r4, #0xc8]
	cmp r0, #0
	beq _02020A9C
	mov r0, #0
	str r0, [r4, #0x2c]
	ldr r1, [r4, #0xc8]
	cmp r1, #0
	rsblt r1, r1, #0
	mov r0, r1, lsl #4
	add r0, r0, r1, lsl #5
	add r0, r0, r1, lsl #2
	str r0, [r4, #0x6f4]
_02020A9C:
	ldr r0, [r4, #0x1c]
	orr r0, r0, #1
	str r0, [r4, #0x1c]
_02020AA8:
	ldr r1, [r4, #0x6f4]
	cmp r1, #0
	beq _02020BE0
	cmp r5, r1
	movge r5, #0x1000
	bge _02020AD0
	mov r0, r5
	bl FX_Div
	mov r0, r0, lsl #0x10
	mov r5, r0, asr #0x10
_02020AD0:
	mov r0, #0
	ldr r2, [r4, #0x6f4]
	mov r3, r5, asr #0x1f
	mov r1, #2
	mov lr, r0
	mov ip, #0x800
_02020AE8:
	sub r6, r2, r0
	umull r8, r7, r6, r5
	mla r7, r6, r3, r7
	mov r6, r6, asr #0x1f
	mla r7, r6, r5, r7
	adds r8, r8, ip
	adc r6, r7, lr
	mov r7, r8, lsr #0xc
	orr r7, r7, r6, lsl #20
	cmp r1, #0
	add r0, r0, r7
	sub r1, r1, #1
	bne _02020AE8
	movs r0, r0, asr #2
	mov r0, #0
	bmi _02020BC0
	mov r1, #2
	mov lr, r0
	mov ip, #0x800
_02020B34:
	sub r6, r2, r0
	umull r8, r7, r6, r5
	mla r7, r6, r3, r7
	mov r6, r6, asr #0x1f
	mla r7, r6, r5, r7
	adds r8, r8, ip
	adc r6, r7, lr
	mov r7, r8, lsr #0xc
	orr r7, r7, r6, lsl #20
	cmp r1, #0
	add r0, r0, r7
	sub r1, r1, #1
	bne _02020B34
	mov r0, r0, asr #2
	cmp r0, #0x50000
	movgt r0, #0x50000
	bgt _02020BC0
	mov r0, #0
	mov r1, #2
	mov lr, r0
	mov ip, #0x800
_02020B88:
	sub r6, r2, r0
	umull r8, r7, r6, r5
	mla r7, r6, r3, r7
	mov r6, r6, asr #0x1f
	mla r7, r6, r5, r7
	adds r8, r8, ip
	adc r6, r7, lr
	mov r7, r8, lsr #0xc
	orr r7, r7, r6, lsl #20
	cmp r1, #0
	add r0, r0, r7
	sub r1, r1, #1
	bne _02020B88
	mov r0, r0, asr #2
_02020BC0:
	str r0, [r4, #0x4c]
	ldr r0, [r4, #0x5d8]
	tst r0, #1
	beq _02020BE8
	ldr r0, [r4, #0x4c]
	rsb r0, r0, #0
	str r0, [r4, #0x4c]
	b _02020BE8
_02020BE0:
	mov r0, #0
	str r0, [r4, #0x4c]
_02020BE8:
	ldr r1, [r4, #0x4c]
	ldr r0, [r4, #0x94]
	sub r0, r1, r0
	str r0, [r4, #0xc4]
	ldmia sp!, {r4, r5, r6, r7, r8, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__Func_2020C00(Player *player, s32 a2)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	mov r4, r0
	ldr r0, [r4, #0x6f4]
	cmp r0, #0x40000
	movlt r0, #0
	strlth r0, [r4, #0x34]
	ldmltia sp!, {r4, r5, r6, r7, r8, pc}
	cmp r1, r0, asr #1
	mov r2, r0, asr #1
	ldr r0, [r4, #0xc0]
	mov r5, #1
	bge _02020CF8
	cmp r0, #0
	mov r0, r1
	mov r1, r2
	bge _02020CA0
	bl FX_Div
	mov r0, r0, lsl #0x10
	mov r2, r0, asr #0x10
	mov r0, #0
	mov r3, #0x1000
	mov r1, r2, asr #0x1f
	rsb r3, r3, #0
	mov lr, r0
	mov ip, #0x800
_02020C64:
	sub r6, r3, r0
	umull r8, r7, r6, r2
	mla r7, r6, r1, r7
	mov r6, r6, asr #0x1f
	mla r7, r6, r2, r7
	adds r8, r8, ip
	adc r6, r7, lr
	mov r7, r8, lsr #0xc
	orr r7, r7, r6, lsl #20
	cmp r5, #0
	add r0, r0, r7
	sub r5, r5, #1
	bne _02020C64
	strh r0, [r4, #0x34]
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_02020CA0:
	bl FX_Div
	mov r0, r0, lsl #0x10
	mov r8, r0, asr #0x10
	mov r6, #0
	mov r7, r8, asr #0x1f
	mov r1, r6
	mov r0, #0x800
_02020CBC:
	rsb r2, r6, #0x1000
	umull ip, r3, r2, r8
	mla r3, r2, r7, r3
	mov r2, r2, asr #0x1f
	mla r3, r2, r8, r3
	adds ip, ip, r0
	adc r2, r3, r1
	mov r3, ip, lsr #0xc
	orr r3, r3, r2, lsl #20
	cmp r5, #0
	add r6, r6, r3
	sub r5, r5, #1
	bne _02020CBC
	strh r6, [r4, #0x34]
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_02020CF8:
	cmp r0, #0
	sub r0, r1, r2
	mov r1, r2
	bge _02020D60
	bl FX_Div
	mov r0, r0, lsl #0x10
	mov r7, r0, asr #0x10
	mov r2, #0
	mov r6, r7, asr #0x1f
	mov r1, r2
	mov r0, #0x800
_02020D24:
	add r2, r2, #0x1000
	umull ip, r3, r2, r7
	mla r3, r2, r6, r3
	mov r2, r2, asr #0x1f
	mla r3, r2, r7, r3
	adds ip, ip, r0
	adc r2, r3, r1
	mov r3, ip, lsr #0xc
	orr r3, r3, r2, lsl #20
	cmp r5, #0
	sub r2, r3, #0x1000
	sub r5, r5, #1
	bne _02020D24
	strh r2, [r4, #0x34]
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
_02020D60:
	bl FX_Div
	mov r0, r0, lsl #0x10
	mov r7, r0, asr #0x10
	mov r2, #0
	mov r6, r7, asr #0x1f
	mov r1, r2
	mov r0, #0x800
_02020D7C:
	sub r2, r2, #0x1000
	umull ip, r3, r2, r7
	mla r3, r2, r6, r3
	mov r2, r2, asr #0x1f
	mla r3, r2, r7, r3
	adds ip, ip, r0
	adc r2, r3, r1
	mov r3, ip, lsr #0xc
	orr r3, r3, r2, lsl #20
	cmp r5, #0
	add r2, r3, #0x1000
	sub r5, r5, #1
	bne _02020D7C
	strh r2, [r4, #0x34]
	ldmia sp!, {r4, r5, r6, r7, r8, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__Func_2020DB8(Player *player)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, r7, lr}
	mov r7, r0
	ldr r1, [r7, #0x600]
	ldr r0, [r7, #0x608]
	ldr r2, [r7, #0x5d8]
	ldr r6, [r7, #0x604]
	tst r2, #0x100
	ldrne r6, [r7, #0x61c]
	mov r4, r1, asr #1
	mov r5, r0, asr #4
	tst r2, #0x80
	beq _02020DFC
	ldr r1, [r7, #0x620]
	ldr r0, [r7, #0x628]
	ldr r6, [r7, #0x624]
	mov r4, r1, asr #1
	mov r5, r0, asr #4
_02020DFC:
	ldrh r0, [r7, #0x34]
	cmp r0, #0
	beq _02020E40
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r1, r0, asr #4
	ldr r0, =FX_SinCosTable_
	mov r1, r1, lsl #2
	ldrsh r0, [r0, r1]
	ldr r1, [r7, #0x630]
	smull r2, r0, r1, r0
	adds r1, r2, #0x800
	adc r0, r0, #0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #20
	cmp r1, #0
	addgt r6, r6, r1
_02020E40:
	ldr r3, [r7, #0xc8]
	ldr r1, [r7, #0x644]
	cmp r3, #0
	rsblt r2, r3, #0
	movge r2, r3
	mov r0, #0
	cmp r2, r1
	ble _02020E88
	cmp r3, #0
	rsblt r3, r3, #0
	sub r0, r3, r1
	sub r1, r6, r1
	bl FX_Div
	cmp r0, #0x1000
	movgt r0, #0x1000
	mov r1, #0xf80
	mul r1, r0, r1
	mov r0, r1, asr #0xc
_02020E88:
	smull r1, r0, r4, r0
	adds r1, r1, #0x800
	adc r0, r0, #0
	mov r1, r1, lsr #0xc
	ldr r2, [r7, #0x638]
	orr r1, r1, r0, lsl #20
	cmp r2, r6
	sub r4, r4, r1
	blt _02020EDC
	ldr r1, [r7, #0xc8]
	cmp r1, #0
	rsblt r0, r1, #0
	movge r0, r1
	cmp r0, r6
	blt _02020EDC
	cmp r2, r1
	ble _02020ED8
	cmp r1, #0
	rsblt r1, r1, #0
	str r1, [r7, #0x638]
_02020ED8:
	ldr r6, [r7, #0x638]
_02020EDC:
	ldr r0, [r7, #0x5dc]
	tst r0, #0x800
	bne _0202100C
	add r0, r7, #0x700
	ldrh r0, [r0, #0x20]
	tst r0, #0x30
	beq _02020F9C
	tst r0, #0x10
	ldr r0, [r7, #0xc8]
	beq _02020F50
	cmp r0, #0
	blt _02020F2C
	mov r1, r4
	mov r2, r6
	bl ObjSpdUpSet
	str r0, [r7, #0xc8]
	ldr r0, [r7, #0x20]
	bic r0, r0, #1
	str r0, [r7, #0x20]
	ldmia sp!, {r3, r4, r5, r6, r7, pc}
_02020F2C:
	mov r1, r5
	bl ObjSpdDownSet
	str r0, [r7, #0xc8]
	cmp r0, #0
	ldmneia sp!, {r3, r4, r5, r6, r7, pc}
	ldr r0, [r7, #0x20]
	bic r0, r0, #1
	str r0, [r7, #0x20]
	ldmia sp!, {r3, r4, r5, r6, r7, pc}
_02020F50:
	cmp r0, #0
	bgt _02020F78
	mov r2, r6
	rsb r1, r4, #0
	bl ObjSpdUpSet
	str r0, [r7, #0xc8]
	ldr r0, [r7, #0x20]
	orr r0, r0, #1
	str r0, [r7, #0x20]
	ldmia sp!, {r3, r4, r5, r6, r7, pc}
_02020F78:
	mov r1, r5
	bl ObjSpdDownSet
	str r0, [r7, #0xc8]
	cmp r0, #0
	ldmneia sp!, {r3, r4, r5, r6, r7, pc}
	ldr r0, [r7, #0x20]
	orr r0, r0, #1
	str r0, [r7, #0x20]
	ldmia sp!, {r3, r4, r5, r6, r7, pc}
_02020F9C:
	add r0, r7, #0x600
	mov r1, #0
	strh r1, [r0, #0x7c]
	ldr r0, [r7, #0x98]
	rsb r1, r6, #0
	cmp r0, r1
	movlt r0, r1
	blt _02020FC4
	cmp r0, r6
	movgt r0, r6
_02020FC4:
	str r0, [r7, #0x98]
	ldr r0, [r7, #0xc8]
	cmp r0, r1
	blt _02020FE0
	cmp r0, r6
	movle r6, r0
	mov r1, r6
_02020FE0:
	str r1, [r7, #0xc8]
	ldrh r0, [r7, #0x34]
	add r0, r0, #0x2000
	and r0, r0, #0xff00
	cmp r0, #0x4000
	ldmgtia sp!, {r3, r4, r5, r6, r7, pc}
	ldr r0, [r7, #0xc8]
	mov r1, r5
	bl ObjSpdDownSet
	str r0, [r7, #0xc8]
	ldmia sp!, {r3, r4, r5, r6, r7, pc}
_0202100C:
	add r0, r7, #0x700
	ldrh r0, [r0, #0x20]
	cmp r4, #0x200
	movlt r4, #0x200
	tst r0, #0x20
	beq _02021044
	ldr r0, [r7, #0xc8]
	mov r1, r5
	bl ObjSpdDownSet
	str r0, [r7, #0xc8]
	cmp r0, #0x4000
	movlt r0, #0x4000
	strlt r0, [r7, #0xc8]
	ldmia sp!, {r3, r4, r5, r6, r7, pc}
_02021044:
	tst r0, #0x10
	beq _02021064
	ldr r0, [r7, #0xc8]
	mov r1, r4
	mov r2, r6
	bl ObjSpdUpSet
	str r0, [r7, #0xc8]
	ldmia sp!, {r3, r4, r5, r6, r7, pc}
_02021064:
	add r0, r7, #0x600
	mov r1, #0
	strh r1, [r0, #0x7c]
	ldr r0, [r7, #0xc8]
	mov r2, r6, asr #2
	mov r1, r4, asr #2
	cmp r0, #0x6000
	add r5, r2, r6, asr #1
	add r1, r1, r4, asr #1
	bge _0202109C
	mov r2, #0x6000
	bl ObjSpdUpSet
	str r0, [r7, #0xc8]
	b _020210BC
_0202109C:
	cmp r0, r6
	ble _020210BC
	mov r1, r4
	mov r2, r6
	rsb r0, r0, #0
	bl ObjSpdUpSet
	rsb r0, r0, #0
	str r0, [r7, #0xc8]
_020210BC:
	ldr r0, [r7, #0x98]
	cmp r0, r5
	strgt r5, [r7, #0x98]
	ldmia sp!, {r3, r4, r5, r6, r7, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__Action_ExitHalfpipe(Player *player)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, lr}
	mov r4, r0
	ldr r1, [r4, #0x5d8]
	tst r1, #0x400
	ldreq r2, [r4, #0xf4]
	ldreq r1, =Player__State_Halfpipe
	cmpeq r2, r1
	ldmneia sp!, {r4, pc}
	mov r1, #0
	str r1, [r4, #0x6d8]
	ldr r1, [r4, #0x5dc]
	bic r1, r1, #0x20000
	str r1, [r4, #0x5dc]
	ldr r1, [r4, #0x5d8]
	bic r1, r1, #0x100000
	str r1, [r4, #0x5d8]
	ldr r1, [r4, #0x1c]
	bic r1, r1, #0x2300
	str r1, [r4, #0x1c]
	ldr r2, [r4, #0x48]
	ldr r1, [r4, #0x6f0]
	cmp r2, r1
	beq _02021178
	ldr r1, [r4, #0x1c]
	bic r1, r1, #1
	str r1, [r4, #0x1c]
	ldr r1, [r4, #0x5f0]
	blx r1
	ldr r0, [r4, #0x5d8]
	orr r0, r0, #3
	str r0, [r4, #0x5d8]
	ldr r0, [r4, #0xbc]
	str r0, [r4, #0x98]
	ldr r0, [r4, #0xc0]
	str r0, [r4, #0x9c]
	ldr r0, [r4, #0x5dc]
	tst r0, #0x800
	ldmneia sp!, {r4, pc}
	mov r0, r4
	mov r1, #0x13
	bl Player__ChangeAction
	ldmia sp!, {r4, pc}
_02021178:
	ldr r1, [r4, #0x5e8]
	blx r1
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__Func_2021188(Player *player, u32 a2)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, lr}
	sub sp, sp, #4
	mov r2, #0
	mov r3, r2
	mov r4, r0
	str r2, [sp]
	bl Player__Gimmick_201B500
	mov r0, #0xa
	str r0, [r4, #0x24]
	ldr r1, [r4, #0x1c]
	mov r0, r4
	orr r1, r1, #0x100
	str r1, [r4, #0x1c]
	mov r1, #0x12
	bl Player__ChangeAction
	ldr r0, [r4, #0x20]
	mov r1, #0
	orr r0, r0, #4
	bic r0, r0, #1
	str r0, [r4, #0x20]
	ldr r0, [r4, #0x5d8]
	mov r2, r1
	orr r0, r0, #0x100000
	str r0, [r4, #0x5d8]
	ldr r3, [r4, #0x5dc]
	add r0, r4, #0x550
	orr r3, r3, #0x20000
	str r3, [r4, #0x5dc]
	bl ObjRect__SetAttackStat
	add sp, sp, #4
	ldmia sp!, {r3, r4, pc}

// clang-format on
#endif
}

void Player__Action_SpringCrystal(Player *player, fx32 velX, fx32 velY)
{
    Player__Gimmick_Jump(player, velX, velY);
}

void Player__Action_CraneGrab(Player *player, GameObjectTask *other)
{
    fx32 v4;
    if ((other->objWork.displayFlag & DISPLAY_FLAG_FLIP_X) == 0)
        v4 = -FLOAT_TO_FX32(46.0);
    else
        v4 = FLOAT_TO_FX32(46.0);

    Player__Gimmick_201B500(player, other, v4, FLOAT_TO_FX32(128.0), 0);

    player->playerFlag |= PLAYER_FLAG_FINISHED_TRICK_COMBO | PLAYER_FLAG_ALLOW_TRICKS | PLAYER_FLAG_USER_FLAG;
    player->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_DISABLE_COLLIDE_EVENT;
    player->gimmickFlag |= PLAYER_GIMMICK_GRABBED;

    Player__ChangeAction(player, PLAYER_ACTION_32);

    player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;
    player->objWork.displayFlag &= ~DISPLAY_FLAG_FLIP_X;
    player->objWork.displayFlag |= other->objWork.displayFlag & DISPLAY_FLAG_FLIP_X;

    PlayPlayerSfx(player, PLAYER_SEQPLAYER_COMMON, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_CRANE_TURN);
}

void Player__Action_Winch(Player *player, GameObjectTask *other, u32 displayFlag)
{
    Player__Gimmick_201B500(player, other, 0, FLOAT_TO_FX32(15.0), 0);
    SetTaskState(&player->objWork, Player__State_Winch);

    player->objWork.userFlag |= 1 | 2 | 8 | 64;
    player->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_DISABLE_COLLIDE_EVENT;
    player->objWork.displayFlag &= ~DISPLAY_FLAG_FLIP_X;

    Player__ChangeAction(player, PLAYER_ACTION_32);

    player->objWork.displayFlag |= displayFlag | DISPLAY_FLAG_DISABLE_LOOPING;
    player->objWork.moveFlag &= ~STAGE_TASK_MOVE_FLAG_TOUCHING_FLOOR;
    player->objWork.collisionFlag &= ~STAGE_TASK_COLLISION_FLAG_GRIND_RAIL;

    player->objWork.dir.x = player->objWork.dir.y = player->objWork.dir.z = 0;
}

void Player__State_Winch(Player *work)
{
    GameObjectTask *gimmick = work->gimmickObj;

    Player__State_201B5A0(work);

    if (!StageTaskStateMatches(&work->objWork, Player__State_Winch) && gimmick != NULL)
        Player__Action_AllowTrickCombos(work, gimmick);
}

void Player__Gimmick_2021394(Player *player, GameObjectTask *other)
{
    if (player->gimmickObj != other)
    {
        Player__InitPhysics(player);
        Player__InitGimmick(player, FALSE);

        player->gimmickObj = other;
        player->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_DISABLE_MOVE_EVENT | STAGE_TASK_MOVE_FLAG_DISABLE_COLLIDE_EVENT;
        player->objWork.moveFlag &= ~STAGE_TASK_MOVE_FLAG_TOUCHING_ANY;

        Player__Action_StopBoost(player);
        Player__Action_StopSuperBoost(player);
        player->playerFlag |= PLAYER_GIMMICK_BUNGEE;
        Player__ChangeAction(player, PLAYER_ACTION_HANG_ROT);
        player->objWork.displayFlag |= DISPLAY_FLAG_PAUSED;
        Player__SetAnimFrame(player, FLOAT_TO_FX32(40.0));
        player->objWork.userTimer = FLOAT_TO_FX32(40.0);
        player->objWork.displayFlag &= ~DISPLAY_FLAG_FLIP_X;
        player->objWork.position.x = other->objWork.position.x - FLOAT_TO_FX32(33.0);
        player->objWork.position.y = other->objWork.position.y - FLOAT_TO_FX32(15.0);
        player->objWork.groundVel  = FLOAT_TO_FX32(0.0);
        player->objWork.velocity.x = FLOAT_TO_FX32(0.0);
        player->objWork.velocity.y = FLOAT_TO_FX32(0.0);
        SetTaskState(&player->objWork, Player__State_202146C);
        ObjRect__SetOnDefend(&player->colliders[0], Player__OnDefend_Unknown);
        player->objWork.userWork = 0;
    }
}

NONMATCH_FUNC void Player__State_202146C(Player *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #0x34
	mov r5, r0
	ldr r4, [r5, #0x6d8]
	add r1, sp, #4
	mov ip, #0
	str ip, [r1]
	str ip, [r1, #4]
	str ip, [r1, #8]
	cmp r4, #0
	bne _020214C0
	ldr r1, [r5, #0x20]
	bic r1, r1, #0x30
	str r1, [r5, #0x20]
	ldr r1, [r5, #0x1c]
	bic r1, r1, #0x2100
	str r1, [r5, #0x1c]
	ldr r1, [r5, #0x5f0]
	blx r1
	add sp, sp, #0x34
	ldmia sp!, {r4, r5, pc}
_020214C0:
	add r0, r5, #0x44
	add r3, r5, #0x8c
	ldmia r0, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	ldr r0, [r5, #0x28]
	cmp r0, #3
	addls pc, pc, r0, lsl #2
	b _020216E4
_020214E0: // jump table
	b _020214F0 // case 0
	b _0202154C // case 1
	b _020215CC // case 2
	b _02021648 // case 3
_020214F0:
	ldr r0, [r5, #0x2c]
	subs r0, r0, #0x2000
	str r0, [r5, #0x2c]
	bpl _02021528
	ldr r0, [r5, #0x28]
	add r0, r0, #1
	str r0, [r5, #0x28]
	ldr r0, [r5, #0x12c]
	ldr r0, [r0, #0xe4]
	ldr r0, [r0, #8]
	ldrh r0, [r0, #4]
	mov r0, r0, lsl #0xc
	sub r0, r0, #1
	str r0, [r5, #0x2c]
_02021528:
	ldr r1, [r5, #0x2c]
	mov r0, r5
	bl Player__SetAnimFrame
	mov r1, #0x21000
	rsb r1, r1, #0
	add r0, r1, #0x12000
	str r1, [sp, #4]
	str r0, [sp, #8]
	b _020216E4
_0202154C:
	ldr r1, [r5, #0x2c]
	mov r0, r5
	sub r1, r1, #0x2000
	str r1, [r5, #0x2c]
	bl Player__SetAnimFrame
	ldr r0, [r5, #0x2c]
	cmp r0, #0x32000
	bgt _02021590
	ldr r1, [r5, #0x28]
	mov r0, #0
	add r1, r1, #1
	str r1, [r5, #0x28]
	ldr r1, [r5, #0x20]
	orr r1, r1, #0x20
	str r1, [r5, #0x20]
	str r0, [r5, #0x2c]
	b _020215B4
_02021590:
	rsb r1, r0, #0x50000
	movs r0, r1, asr #2
	str r0, [r5, #0x50]
	movmi r0, #0
	strmi r0, [r5, #0x50]
	movs r0, r1, asr #3
	str r0, [r5, #0x54]
	movmi r0, #0
	strmi r0, [r5, #0x54]
_020215B4:
	mov r1, #0x21000
	rsb r1, r1, #0
	add r0, r1, #0x12000
	str r1, [sp, #4]
	str r0, [sp, #8]
	b _020216E4
_020215CC:
	ldr r0, [r5, #0x2c]
	add r1, r0, #1
	str r1, [r5, #0x2c]
	cmp r1, #0x10
	blt _0202162C
	ldr r1, [r5, #0x28]
	mov r0, r5
	add r1, r1, #1
	str r1, [r5, #0x28]
	ldr r2, [r5, #0x20]
	mov r1, #1
	bic r2, r2, #0x30
	str r2, [r5, #0x20]
	bl Player__ChangeAction
	ldr r0, [r5, #0x20]
	mov r1, #0x10000
	orr r0, r0, #4
	str r0, [r5, #0x20]
	mov r0, #0
	str r0, [r5, #0x2c]
	sub r0, r1, #0x1a000
	str r1, [sp, #4]
	str r0, [sp, #8]
	b _020216E4
_0202162C:
	mov r0, #0x3100
	mul r0, r1, r0
	sub r1, r0, #0x21000
	sub r0, ip, #0xf000
	str r1, [sp, #4]
	str r0, [sp, #8]
	b _020216E4
_02021648:
	ldr r0, [r5, #0x2c]
	add r0, r0, #1
	str r0, [r5, #0x2c]
	cmp r0, #0x12
	blt _020216CC
	mov r2, #0x10000
	str ip, [r5, #0x6d8]
	mov r0, r5
	mov r1, r4
	sub r3, r2, #0x23000
	str ip, [sp]
	bl Player__Gimmick_201B500
	ldr r1, =Player__State_2021848
	ldr r0, =Player__OnDefend_Unknown
	str r1, [r5, #0xf4]
	str r0, [r5, #0x534]
	ldr r1, [r5, #0x1c]
	mov r0, #0x13000
	orr r1, r1, #0x100
	str r1, [r5, #0x1c]
	ldr r1, [r5, #0x5d8]
	rsb r0, r0, #0
	orr r1, r1, #7
	str r1, [r5, #0x5d8]
	ldr r1, [r5, #0x24]
	orr r1, r1, #8
	str r1, [r5, #0x24]
	ldr r1, [r5, #0x20]
	orr r1, r1, #0x200
	bic r1, r1, #1
	str r1, [r5, #0x20]
	str r0, [sp, #8]
	b _020216DC
_020216CC:
	rsb r0, r0, #0x12
	mov r0, r0, lsl #0xb
	sub r0, r0, #0x13000
	str r0, [sp, #8]
_020216DC:
	mov r0, #0x10000
	str r0, [sp, #4]
_020216E4:
	ldrh r1, [r4, #0x34]
	ldr r3, =FX_SinCosTable_
	add r0, sp, #0x10
	mov r1, r1, asr #4
	mov r2, r1, lsl #1
	add r1, r2, #1
	mov ip, r2, lsl #1
	mov r2, r1, lsl #1
	ldrsh r1, [r3, ip]
	ldrsh r2, [r3, r2]
	bl MTX_RotZ33_
	add r0, sp, #4
	add r1, sp, #0x10
	mov r2, r0
	bl MTX_MultVec33
	ldr r1, [r4, #0x44]
	ldr r0, [sp, #4]
	add r0, r1, r0
	str r0, [r5, #0x44]
	ldr r1, [r4, #0x48]
	ldr r0, [sp, #8]
	add r0, r1, r0
	str r0, [r5, #0x48]
	ldrh r0, [r4, #0x34]
	strh r0, [r5, #0x34]
	ldr r1, [r5, #0x44]
	ldr r0, [r5, #0x8c]
	sub r0, r1, r0
	str r0, [r5, #0xbc]
	ldr r1, [r5, #0x48]
	ldr r0, [r5, #0x90]
	sub r0, r1, r0
	str r0, [r5, #0xc0]
	ldr r1, [r5, #0x4c]
	ldr r0, [r5, #0x94]
	sub r0, r1, r0
	str r0, [r5, #0xc4]
	add sp, sp, #0x34
	ldmia sp!, {r4, r5, pc}

// clang-format on
#endif
}

void Player__Action_TruckLaunch(Player *player, GameObjectTask *other, s32 a3)
{
    if (player->gimmickObj == other)
    {
        ObjRect__SetOnDefend(&player->colliders[0], Player__OnDefend_Regular);
        player->gimmickObj = NULL;

        player->objWork.moveFlag &= ~(STAGE_TASK_MOVE_FLAG_DISABLE_SLOPE_ANGLES | STAGE_TASK_MOVE_FLAG_DISABLE_MOVE_EVENT | STAGE_TASK_MOVE_FLAG_DISABLE_COLLIDE_EVENT);
        player->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_HAS_GRAVITY | STAGE_TASK_MOVE_FLAG_USE_SLOPE_FORCES;
        player->objWork.displayFlag |= DISPLAY_FLAG_APPLY_CAMERA_CONFIG;
        player->objWork.displayFlag &= ~(DISPLAY_FLAG_NO_DRAW | DISPLAY_FLAG_PAUSED);
        player->playerFlag &= ~(PLAYER_FLAG_2000 | PLAYER_FLAG_DISABLE_TENSION_DRAIN);
        player->gimmickFlag &= ~(PLAYER_GIMMICK_10 | PLAYER_GIMMICK_20 | PLAYER_GIMMICK_GRABBED);

        player->gimmickCamOffsetX = player->gimmickCamOffsetY = 0;
        player->objWork.dir.x = player->objWork.dir.y = player->objWork.dir.z = FLOAT_DEG_TO_IDX(0.0);

        Player__Gimmick_Jump(player, player->objWork.move.x, -FLOAT_TO_FX32(8.0));

        if (!a3)
            player->playerFlag |= PLAYER_FLAG_DISABLE_TRICK_FINISHER;

        Player__Action_AllowTrickCombos(player, other);
    }
}

void Player__State_2021848(Player *work)
{
    if (work->actionState != PLAYER_ACTION_2D)
    {
        if ((work->inputKeyDown & PAD_KEY_DOWN) != 0)
        {
            Player__ChangeAction(work, PLAYER_ACTION_2D);
        }
    }
    else
    {
        if ((work->inputKeyDown & PAD_KEY_DOWN) == 0)
        {
            Player__ChangeAction(work, PLAYER_ACTION_IDLE);
            work->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;
        }
    }

    Player__State_201B5A0(work);
}

void Player__OnDefend_Unknown(OBS_RECT_WORK *rect1, OBS_RECT_WORK *rect2)
{
    Player *player = (Player *)rect2->parent;

    if (player->objWork.hitstopTimer != 0 || rect1->parent->objType == STAGE_OBJ_TYPE_PLAYER)
        return;

    if ((player->playerFlag & PLAYER_FLAG_SHIELD_REGULAR) == 0)
    {
        Player__GiveTension(player, -PLAYER_TENSION_HURT_PENALTY);
        UpdateTensionGaugeHUD(player->tension >> 4, 1);
    }

    if ((rect1->hitFlag & 4) != 0)
    {
        if (player->rings != 0)
        {
            PlayPlayerSfx(player, PLAYER_SEQPLAYER_COMMON, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_RINGLOST);
            CreateLoseRingEffect(player, player->rings);
        }

        Player__Action_Die(player);
        ObjRect__SetOnDefend(&player->colliders[0], Player__OnDefend_Regular);
        return;
    }

    if ((player->playerFlag & PLAYER_FLAG_SHIELD_REGULAR) == 0 && player->rings == 0)
    {
        Player__Action_Die(player);
        ObjRect__SetOnDefend(&player->colliders[0], Player__OnDefend_Regular);
        return;
    }

    if ((player->playerFlag & PLAYER_FLAG_SHIELD_REGULAR) == 0)
    {
        PlayPlayerSfx(player, PLAYER_SEQPLAYER_COMMON, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_RINGLOST);
        CreateLoseRingEffect(player, player->rings);
    }

    player->playerFlag &= ~(PLAYER_FLAG_SHIELD_MAGNET | PLAYER_FLAG_SHIELD_REGULAR);
    ShakeScreen(SCREENSHAKE_C_SHORT);

    player->objWork.shakeTimer    = 8;
    player->blinkTimer            = player->hurtInvulnDuration;
    player->colliders[0].defPower = PLAYER_DEFPOWER_INVINCIBLE;

    switch (player->characterID)
    {
        // case CHARACTER_SONIC:
        default:
            PlayPlayerSfx(player, PLAYER_SEQPLAYER_COMMON, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_OWA);
            break;

        case CHARACTER_BLAZE:
            PlayPlayerSfx(player, PLAYER_SEQPLAYER_COMMON, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_UPS);
            break;
    }
}

void Player__Func_2021A84(Player *player, GameObjectTask *other)
{
    if (player->gimmickObj == other)
    {
        player->objWork.flag &= ~STAGE_TASK_FLAG_ON_PLANE_B;
        player->gimmickFlag |= PLAYER_GIMMICK_10;
        player->gimmickCamOffsetX = 0;
        Player__ChangeAction(player, PLAYER_ACTION_BALANCE_BACKWARD);
        player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;
        player->objWork.displayFlag &= ~DISPLAY_FLAG_PAUSED;
        player->objWork.displayFlag &= ~DISPLAY_FLAG_APPLY_CAMERA_CONFIG;
        SetTaskState(&player->objWork, Player__State_201B5A0);
    }
}

void Player__Func_2021AE8(Player *player, GameObjectTask *other)
{
    if (player->gimmickObj == other)
    {
        player->objWork.flag &= ~STAGE_TASK_FLAG_ON_PLANE_B;
        player->gimmickFlag |= PLAYER_GIMMICK_20;
        player->gimmickCamOffsetY = 64;
        Player__ChangeAction(player, PLAYER_ACTION_IDLE);
        player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;
        SetTaskState(&player->objWork, Player__State_2021848);
    }
}

void Player__Func_2021B44(Player *player, GameObjectTask *other)
{
    if (player->gimmickObj == other)
    {
        player->objWork.flag |= STAGE_TASK_FLAG_ON_PLANE_B;
        player->objWork.displayFlag |= DISPLAY_FLAG_APPLY_CAMERA_CONFIG;
        player->gimmickFlag &= ~PLAYER_GIMMICK_20;
        player->gimmickCamOffsetY = 0;
    }
}

void Player__Func_2021B84(Player *player, GameObjectTask *other)
{
    Player__Gimmick_201B500(player, other, 0, 0, 0);

    SetTaskState(&player->objWork, Player__State_AnchorRope);

    player->playerFlag |= PLAYER_FLAG_ALLOW_TRICKS | PLAYER_FLAG_USER_FLAG;
    player->objWork.userFlag |= 1 | 2 | 8;
    player->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_DISABLE_COLLIDE_EVENT;
    player->gimmickFlag |= PLAYER_GIMMICK_GRABBED | PLAYER_GIMMICK_10;
    player->playerFlag |= PLAYER_FLAG_DISABLE_TENSION_DRAIN;

    player->gimmickCamOffsetX = 0;
    Player__ChangeAction(player, PLAYER_ACTION_33);
    player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING | DISPLAY_FLAG_FLIP_X;

    player->objWork.dir.x = player->objWork.dir.y = player->objWork.dir.z = 0;
}

NONMATCH_FUNC void Player__State_AnchorRope(Player *work)
{
#ifdef NON_MATCHING
    Player__State_201B5A0(work);

    if (StageTaskStateMatches(&work->objWork, Player__State_AnchorRope))
    {
        GameObjectTask *gimmick = work->gimmickObj;
        if (gimmick != NULL)
        {
            if ((gimmick->objWork.position.x - work->objWork.position.x <= 0 && gimmick->objWork.position.x - work->objWork.prevPosition.x > 0)
                || (gimmick->objWork.position.x - work->objWork.position.x >= 0 && gimmick->objWork.position.x - work->objWork.prevPosition.x < 0))
            {
                if (work->objWork.position.z > 0)
                    PlayPlayerSfx(work, PLAYER_SEQPLAYER_COMMON, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_ANCHOR_ROPE);
            }
        }
    }
    else
    {
        work->objWork.position.z = 0;
    }
#else
    // clang-format off
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	mov r4, r0
	bl Player__State_201B5A0
	ldr r1, [r4, #0xf4]
	ldr r0, =Player__State_AnchorRope
	cmp r1, r0
	bne _02021CD4
	ldr r0, [r4, #0x6d8]
	cmp r0, #0
	addeq sp, sp, #8
	ldmeqia sp!, {r4, pc}
	ldr r2, [r0, #0x44]
	ldr r1, [r4, #0x44]
	ldr r0, [r4, #0x8c]
	sub r1, r2, r1
	cmp r1, #0
	sub r0, r2, r0
	bgt _02021C7C
	cmp r0, #0
	bgt _02021C94
_02021C7C:
	cmp r1, #0
	addlt sp, sp, #8
	ldmltia sp!, {r4, pc}
	cmp r0, #0
	addge sp, sp, #8
	ldmgeia sp!, {r4, pc}
_02021C94:
	ldr r0, [r4, #0x4c]
	cmp r0, #0
	addle sp, sp, #8
	ldmleia sp!, {r4, pc}
	mov ip, #0x6c
	sub r1, ip, #0x6d
	add r0, r4, #0x254
	mov r2, #0
	str r2, [sp]
	mov r2, r1
	mov r3, r1
	add r0, r0, #0x400
	str ip, [sp, #4]
	bl PlaySfxEx
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_02021CD4:
	mov r0, #0
	str r0, [r4, #0x4c]
	add sp, sp, #8
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}

void Player__Func_2021CE8(Player *player, GameObjectTask *other)
{
    fx32 v3;

    if (player->characterID == CHARACTER_SONIC)
        v3 = FLOAT_TO_FX32(40.0);
    else
        v3 = FLOAT_TO_FX32(42.0);
    Player__Gimmick_201B500(player, other, 0, v3, 0);

    SetTaskState(&player->objWork, Player__State_2021DD4);

    player->playerFlag |= PLAYER_FLAG_FINISHED_TRICK_COMBO;
    player->objWork.userFlag |= 2 | 4;
    player->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_DISABLE_COLLIDE_EVENT;
    player->gimmickFlag |= PLAYER_GIMMICK_GRABBED | PLAYER_GIMMICK_10;
    player->playerFlag |= PLAYER_FLAG_DISABLE_TENSION_DRAIN;

    player->gimmickCamOffsetX = 0;
    player->objWork.userWork  = 0;
    player->objWork.userTimer = 0;
    Player__ChangeAction(player, PLAYER_ACTION_HOMING_ATTACK);
    player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;

    ObjRect__SetAttackStat(&player->colliders[1], 0, 0);
    player->colliders[0].defPower = PLAYER_DEFPOWER_INVINCIBLE;
    player->blinkTimer            = 0;
    player->objWork.displayFlag &= ~DISPLAY_FLAG_NO_DRAW;

    player->objWork.dir.x = player->objWork.dir.y = player->objWork.dir.z = 0;
}

void Player__State_2021DD4(Player *work)
{
    if (work->gimmickObj != NULL && (work->gimmickObj->flags & 2) != 0)
        work->objWork.displayFlag |= DISPLAY_FLAG_NO_DRAW;

    work->objWork.userWork &= ~1;

    if ((work->inputKeyPress & PLAYER_INPUT_JUMP) != 0)
    {
        work->objWork.userWork |= 1;
        work->objWork.userTimer++;
    }

    if (work->objWork.userTimer >= 5)
        work->objWork.userWork |= 2;

    Player__State_201B5A0(work);

    if (!StageTaskStateMatches(&work->objWork, Player__State_2021DD4))
    {
        work->colliders[0].defPower = PLAYER_DEFPOWER_NORMAL;
        work->playerFlag |= PLAYER_FLAG_USER_FLAG;
        work->objWork.displayFlag &= ~DISPLAY_FLAG_NO_DRAW;

        if (work->characterID == CHARACTER_SONIC)
            work->objWork.position.y += FLOAT_TO_FX32(2.0);
    }
}

void Player__Gimmick_2021E9C(Player *player, GameObjectTask *other)
{
    fx32 velX;
    fx32 velY;

    if ((player->objWork.moveFlag & STAGE_TASK_MOVE_FLAG_DISABLE_SLOPE_ANGLES) != 0)
    {
        velX = player->objWork.velocity.x;
        velY = player->objWork.velocity.y;
    }
    else
    {
        velX = MultiplyFX(player->objWork.groundVel, CosFX(player->objWork.dir.z));
        velY = MultiplyFX(player->objWork.groundVel, SinFX(player->objWork.dir.z));
    }

    if (velY >= 0 && (player->playerFlag & PLAYER_FLAG_DEATH) == 0)
    {
        Player__InitGimmick(player, TRUE);
        player->gimmickObj = other;

        if (velY < FLOAT_TO_FX32(6.0))
            velY = FLOAT_TO_FX32(6.0);

        player->gimmickValue1      = velX;
        player->gimmickValue2      = -velY;
        player->objWork.velocity.x = 0;
        player->objWork.velocity.y = velY;
        player->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_DISABLE_SLOPE_ANGLES | STAGE_TASK_MOVE_FLAG_IN_AIR;
        player->objWork.moveFlag &= ~STAGE_TASK_MOVE_FLAG_HAS_GRAVITY;

        Player__ChangeAction(player, PLAYER_ACTION_JUMPFALL);
        player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;
        ObjRect__SetAttackStat(&player->colliders[1], 0, 0);
        player->objWork.userWork = 0;
        SetTaskState(&player->objWork, Player__State_2021FA8);
    }
}

NONMATCH_FUNC void Player__State_2021FA8(Player *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r5, r0
	ldr r0, [r5, #0x9c]
	sub r0, r0, r0, asr #2
	str r0, [r5, #0x9c]
	cmp r0, #0x2000
	bgt _02021FD8
	add r0, r5, #0x700
	ldrh r0, [r0, #0x20]
	tst r0, #3
	movne r0, #1
	strne r0, [r5, #0x28]
_02021FD8:
	ldr r0, [r5, #0x9c]
	cmp r0, #0x400
	ldmgtia sp!, {r3, r4, r5, pc}
	ldr r0, [r5, #0x28]
	ldr r4, [r5, #0x6d8]
	cmp r0, #0
	ldr r0, [r5, #0x1c]
	mov r1, #0
	orr r0, r0, #0x80
	str r0, [r5, #0x1c]
	ldr r2, [r5, #0xc8]
	subne r1, r1, #0x2000
	cmp r2, #0
	ldr r0, [r5, #0x64c]
	blt _02022020
	cmp r2, r0
	strgt r0, [r5, #0xc8]
	b _0202202C
_02022020:
	rsb r0, r0, #0
	cmp r2, r0
	strlt r0, [r5, #0xc8]
_0202202C:
	ldr r2, [r5, #0x98]
	ldr r0, [r5, #0x64c]
	cmp r2, #0
	blt _02022048
	cmp r2, r0
	strgt r0, [r5, #0x98]
	b _02022054
_02022048:
	rsb r0, r0, #0
	cmp r2, r0
	strlt r0, [r5, #0x98]
_02022054:
	ldr r2, [r5, #0x6f4]
	mov r0, r5
	add r2, r2, r1
	mov r1, #0
	bl Player__Action_Trampoline
	mov r0, r5
	mov r1, r4
	add r2, r5, #0x600
	mov r3, #2
	strh r3, [r2, #0x98]
	bl Player__Action_AllowTrickCombos
	mov r0, #0
	str r0, [r5, #0x6d8]
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

void Player__Action_Trampoline(Player *player, fx32 velX, fx32 velY)
{
    Player__Gimmick_Jump(player, velX, velY);

    player->objWork.moveFlag &= ~STAGE_TASK_MOVE_FLAG_HAS_GRAVITY;
    player->objWork.userTimer = 1;
    player->objWork.displayFlag |= DISPLAY_FLAG_400;

    Player__ChangeAction(player, PLAYER_ACTION_TRAMPOLINE);
    ObjRect__SetAttackStat(&player->colliders[1], 0, 0);

    PlayPlayerSfx(player, PLAYER_SEQPLAYER_COMMON, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_TRAMPOLINE);
}

NONMATCH_FUNC void Player__Gimmick_2022108(Player *player, GameObjectTask *other, s32 a3)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, lr}
	mov r4, r1
	mov r5, r0
	mov r1, #0
	mov r6, r2
	bl Player__InitGimmick
	mov r0, r5
	bl Player__InitState
	str r4, [r5, #0x6d8]
	cmp r6, #0
	beq _02022144
	cmp r6, #1
	beq _02022168
	cmp r6, #2
	b _020221B4
_02022144:
	mov r0, r5
	mov r1, #0x13
	bl Player__ChangeAction
	ldr r1, [r5, #0x20]
	ldr r0, =Player__State_20222E4
	orr r1, r1, #4
	str r1, [r5, #0x20]
	str r0, [r5, #0xf4]
	b _02022244
_02022168:
	mov r0, r5
	mov r1, #0x6b
	bl Player__ChangeAction
	ldr r0, [r5, #0x20]
	orr r0, r0, #4
	str r0, [r5, #0x20]
	ldr r0, [r5, #0x1c]
	orr r0, r0, #0x2000
	str r0, [r5, #0x1c]
	ldr r1, [r5, #0x44]
	ldr r0, [r4, #0x44]
	cmp r1, r0
	ldr r0, [r5, #0x20]
	biclt r0, r0, #1
	orrge r0, r0, #1
	str r0, [r5, #0x20]
	ldr r0, =Player__Func_20223F8
	str r0, [r5, #0xf4]
	b _02022244
_020221B4:
	mov r0, r5
	mov r1, #0x25
	bl Player__ChangeAction
	ldr r1, [r5, #0x20]
	mov r0, r5
	orr r2, r1, #0x10
	mov r1, #0x28000
	str r2, [r5, #0x20]
	bl Player__SetAnimFrame
	mov r0, #0x28000
	str r0, [r5, #0x2c]
	ldr r1, [r5, #0x44]
	ldr r0, [r4, #0x44]
	cmp r1, r0
	ldr r0, [r5, #0x20]
	bge _02022208
	bic r0, r0, #1
	str r0, [r5, #0x20]
	ldr r0, [r4, #0x44]
	sub r0, r0, #0xe000
	b _02022218
_02022208:
	orr r0, r0, #1
	str r0, [r5, #0x20]
	ldr r0, [r4, #0x44]
	add r0, r0, #0xe000
_02022218:
	str r0, [r5, #0x44]
	ldr r0, [r4, #0x48]
	sub r0, r0, #0x4c000
	str r0, [r5, #0x48]
	ldr r1, [r5, #0x1c]
	ldr r0, =Player__Func_20224BC
	orr r1, r1, #0x2000
	str r1, [r5, #0x1c]
	str r0, [r5, #0xf4]
	mov r0, #0
	str r0, [r5, #0x9c]
_02022244:
	mov r0, r5
	bl Player__Action_StopSuperBoost
	mov r0, r5
	bl Player__Action_StopBoost
	mov r3, #0
	add r1, r5, #0x600
	strh r3, [r1, #0x82]
	ldr r2, [r5, #0x20]
	add r0, r5, #0x500
	bic r2, r2, #0x20
	str r2, [r5, #0x20]
	mov r2, #0xff
	strh r2, [r0, #0x3e]
	ldr r2, [r5, #0x1c]
	mov r0, #0x40
	orr r2, r2, #0x110
	orr r2, r2, #0x8000
	str r2, [r5, #0x1c]
	ldr r2, [r5, #0x5dc]
	orr r2, r2, #0x30
	str r2, [r5, #0x5dc]
	strh r3, [r1, #0xdc]
	strh r0, [r1, #0xde]
	ldr r0, [r5, #0x5d8]
	orr r0, r0, #0x2000
	orr r0, r0, #0x100000
	str r0, [r5, #0x5d8]
	str r3, [r5, #0x98]
	str r3, [r5, #0xc8]
	strh r3, [r5, #0x34]
	str r3, [r5, #0x28]
	str r3, [r5, #0x24]
	ldr r0, [r5, #0x44]
	str r0, [r5, #0x6f0]
	ldr r0, [r5, #0x48]
	str r0, [r5, #0x6f4]
	ldmia sp!, {r4, r5, r6, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__State_20222E4(Player *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	sub sp, sp, #8
	mov r5, r0
	ldr r4, [r5, #0x6d8]
	cmp r4, #0
	beq _020223C4
	ldr r0, [r5, #0x44]
	str r0, [r5, #0x8c]
	ldr r0, [r5, #0x48]
	str r0, [r5, #0x90]
	ldr r0, [r5, #0x28]
	cmp r0, #0
	addne sp, sp, #8
	ldmneia sp!, {r3, r4, r5, pc}
	mov r0, #0x4000
	str r0, [sp]
	mov r0, #0x800
	str r0, [sp, #4]
	ldr r0, [r5, #0x44]
	ldr r1, [r4, #0x44]
	ldr r2, [r5, #0x6f0]
	mov r3, #1
	bl ObjDiffSet
	str r0, [r5, #0x44]
	ldr r1, [r4, #0x48]
	ldr r0, [r5, #0x48]
	sub r1, r1, #0x27000
	cmp r0, r1
	blt _02022370
	str r1, [r5, #0x48]
	ldr r1, [r5, #0x1c]
	mov r0, #0
	orr r1, r1, #0x2000
	str r1, [r5, #0x1c]
	str r0, [r5, #0x9c]
_02022370:
	ldr r1, [r5, #0x44]
	ldr r0, [r4, #0x44]
	cmp r1, r0
	addne sp, sp, #8
	ldmneia sp!, {r3, r4, r5, pc}
	ldr r0, [r4, #0x48]
	ldr r1, [r5, #0x48]
	sub r0, r0, #0x27000
	cmp r1, r0
	addne sp, sp, #8
	ldmneia sp!, {r3, r4, r5, pc}
	ldr r0, =Player__Func_2022694
	add sp, sp, #8
	str r0, [r5, #0xf4]
	ldr r0, [r5, #0x20]
	bic r0, r0, #1
	str r0, [r5, #0x20]
	ldr r0, [r5, #0x24]
	orr r0, r0, #1
	str r0, [r5, #0x24]
	ldmia sp!, {r3, r4, r5, pc}
_020223C4:
	add r1, r5, #0x500
	mov r2, #0x3f
	strh r2, [r1, #0x3e]
	ldr r1, [r5, #0x5e4]
	cmp r1, #0
	addeq sp, sp, #8
	ldmeqia sp!, {r3, r4, r5, pc}
	bl Player__InitState
	ldr r0, [r5, #0x5e4]
	blx r0
	add sp, sp, #8
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__Func_20223F8(Player *player)
{
#ifdef NON_MATCHING
    GameObjectTask *gimmick = player->gimmickObj;
    if (gimmick != NULL)
    {
        player->objWork.position.x = ObjDiffSet(player->objWork.position.x, gimmick->objWork.position.x, player->gimmickValue1, 1, FLOAT_TO_FX32(4.0), FLOAT_TO_FX32(0.5));
        if (player->objWork.position.x == gimmick->objWork.position.x)
        {
            SetTaskState(&player->objWork, Player__State_20222E4);
            Player__ChangeAction(player, PLAYER_ACTION_JUMPFALL);

            player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;
            player->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_HAS_GRAVITY | STAGE_TASK_MOVE_FLAG_IN_AIR;
            player->objWork.moveFlag &= ~(STAGE_TASK_MOVE_FLAG_TOUCHING_FLOOR | STAGE_TASK_MOVE_FLAG_DISABLE_MOVE_EVENT);
        }
    }
    else
    {
        player->colliders[0].defPower = PLAYER_DEFPOWER_NORMAL;

        if (player->onLandGround != NULL)
        {
            Player__InitState(player);
            player->onLandGround(player);
        }
    }
#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	sub sp, sp, #8
	mov r4, r0
	ldr r5, [r4, #0x6d8]
	cmp r5, #0
	beq _02022484
	mov r0, #0x4000
	str r0, [sp]
	mov r0, #0x800
	str r0, [sp, #4]
	ldr r0, [r4, #0x44]
	ldr r1, [r5, #0x44]
	ldr r2, [r4, #0x6f0]
	mov r3, #1
	bl ObjDiffSet
	str r0, [r4, #0x44]
	ldr r1, [r5, #0x44]
	cmp r0, r1
	addne sp, sp, #8
	ldmneia sp!, {r3, r4, r5, pc}
	ldr r1, =Player__State_20222E4
	mov r0, r4
	str r1, [r4, #0xf4]
	mov r1, #0x13
	bl Player__ChangeAction
	ldr r1, [r4, #0x20]
	ldr r0, =0xFFFFDFFE
	orr r1, r1, #4
	str r1, [r4, #0x20]
	ldr r1, [r4, #0x1c]
	add sp, sp, #8
	orr r1, r1, #0x90
	and r0, r1, r0
	str r0, [r4, #0x1c]
	ldmia sp!, {r3, r4, r5, pc}
_02022484:
	add r1, r4, #0x500
	mov r2, #0x3f
	strh r2, [r1, #0x3e]
	ldr r1, [r4, #0x5e4]
	cmp r1, #0
	addeq sp, sp, #8
	ldmeqia sp!, {r3, r4, r5, pc}
	bl Player__InitState
	ldr r0, [r4, #0x5e4]
	blx r0
	add sp, sp, #8
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__Func_20224BC(Player *player)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	sub sp, sp, #8
	mov r5, r0
	ldr r4, [r5, #0x6d8]
	cmp r4, #0
	beq _02022660
	ldr r1, [r5, #0x44]
	str r1, [r5, #0x8c]
	ldr r1, [r5, #0x48]
	str r1, [r5, #0x90]
	ldr r1, [r5, #0x28]
	cmp r1, #0
	beq _02022504
	cmp r1, #1
	beq _0202254C
	cmp r1, #2
	beq _020225A0
	b _02022638
_02022504:
	ldr r0, [r5, #0x2c]
	subs r0, r0, #0x2000
	str r0, [r5, #0x2c]
	bpl _0202253C
	ldr r0, [r5, #0x28]
	add r0, r0, #1
	str r0, [r5, #0x28]
	ldr r0, [r5, #0x12c]
	ldr r0, [r0, #0xe4]
	ldr r0, [r0, #8]
	ldrh r0, [r0, #4]
	mov r0, r0, lsl #0xc
	sub r0, r0, #1
	str r0, [r5, #0x2c]
_0202253C:
	ldr r1, [r5, #0x2c]
	mov r0, r5
	bl Player__SetAnimFrame
	b _02022638
_0202254C:
	ldr r1, [r5, #0x2c]
	sub r1, r1, #0x2000
	str r1, [r5, #0x2c]
	bl Player__SetAnimFrame
	ldr r0, [r5, #0x2c]
	cmp r0, #0x32000
	bgt _02022638
	ldr r1, [r5, #0x28]
	mov r0, r5
	add r1, r1, #1
	str r1, [r5, #0x28]
	ldr r2, [r5, #0x20]
	mov r1, #0x13
	orr r2, r2, #0x400
	str r2, [r5, #0x20]
	bl Player__ChangeAction
	ldr r0, [r5, #0x20]
	orr r0, r0, #4
	bic r0, r0, #0x10
	str r0, [r5, #0x20]
	b _02022638
_020225A0:
	mov r0, #0x4000
	str r0, [sp]
	mov r0, #0x1000
	str r0, [sp, #4]
	ldr r0, [r5, #0x44]
	ldr r1, [r4, #0x44]
	ldr r2, [r5, #0x6f0]
	mov r3, #1
	bl ObjDiffSet
	str r0, [r5, #0x44]
	mov r0, #0x4000
	str r0, [sp]
	mov r0, #0x1000
	str r0, [sp, #4]
	ldr r1, [r4, #0x48]
	ldr r0, [r5, #0x48]
	ldr r2, [r5, #0x6f4]
	sub r1, r1, #0x27000
	mov r3, #1
	bl ObjDiffSet
	str r0, [r5, #0x48]
	ldr r1, [r5, #0x44]
	ldr r0, [r4, #0x44]
	cmp r1, r0
	bne _02022638
	ldr r0, [r4, #0x48]
	ldr r1, [r5, #0x48]
	sub r0, r0, #0x27000
	cmp r1, r0
	bne _02022638
	ldr r0, =Player__Func_2022694
	str r0, [r5, #0xf4]
	ldr r0, [r5, #0x20]
	bic r0, r0, #1
	str r0, [r5, #0x20]
	ldr r0, [r5, #0x24]
	orr r0, r0, #1
	str r0, [r5, #0x24]
_02022638:
	ldr r1, [r5, #0x44]
	ldr r0, [r5, #0x8c]
	add sp, sp, #8
	sub r0, r1, r0
	str r0, [r5, #0xbc]
	ldr r1, [r5, #0x48]
	ldr r0, [r5, #0x90]
	sub r0, r1, r0
	str r0, [r5, #0xc0]
	ldmia sp!, {r3, r4, r5, pc}
_02022660:
	add r1, r5, #0x500
	mov r2, #0x3f
	strh r2, [r1, #0x3e]
	ldr r1, [r5, #0x5e4]
	cmp r1, #0
	addeq sp, sp, #8
	ldmeqia sp!, {r3, r4, r5, pc}
	bl Player__InitState
	ldr r0, [r5, #0x5e4]
	blx r0
	add sp, sp, #8
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__Func_2022694(Player *player)
{
#ifdef NON_MATCHING
    if (player->gimmickObj != NULL)
    {
        player->objWork.dir.y    = FLOAT_DEG_TO_IDX(90.0);
        player->objWork.offset.z = -FLOAT_TO_FX32(16.0);
    }
    else
    {
        player->colliders[0].defPower = PLAYER_DEFPOWER_NORMAL;

        if (player->onLandGround != NULL)
        {
            Player__InitState(player);
            player->onLandGround(player);
        }
    }
#else
    // clang-format off
	stmdb sp!, {r4, lr}
	mov r4, r0
	ldr r1, [r4, #0x6d8]
	cmp r1, #0
	beq _020226BC
	mov r0, #0x4000
	strh r0, [r4, #0x32]
	sub r0, r0, #0x14000
	str r0, [r4, #0x58]
	ldmia sp!, {r4, pc}
_020226BC:
	add r1, r4, #0x500
	mov r2, #0x3f
	strh r2, [r1, #0x3e]
	ldr r1, [r4, #0x5e4]
	cmp r1, #0
	ldmeqia sp!, {r4, pc}
	bl Player__InitState
	ldr r0, [r4, #0x5e4]
	blx r0
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}

void Player__Action_PRCannon(Player *player, GameObjectTask *other)
{
    if (StageTaskStateMatches(&player->objWork, Player__Func_2022694))
    {
        player->gimmickObj = other;
        Player__ChangeAction(player, PLAYER_ACTION_AIRRISE);

        player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;
        player->objWork.velocity.y = 0;
        player->objWork.displayFlag &= ~(DISPLAY_FLAG_FLIP_X | DISPLAY_FLAG_APPLY_CAMERA_CONFIG);

        player->objWork.dir = other->objWork.dir;

        player->objWork.moveFlag |=
            STAGE_TASK_MOVE_FLAG_DISABLE_SLOPE_ANGLES | STAGE_TASK_MOVE_FLAG_DISABLE_MOVE_EVENT | STAGE_TASK_MOVE_FLAG_DISABLE_COLLIDE_EVENT | STAGE_TASK_MOVE_FLAG_IN_AIR;
        player->gimmickCamOffsetY = 25;
        player->playerFlag |= PLAYER_FLAG_2000;
        player->objWork.userWork = 0;
        player->objWork.userFlag = 0;
        SetTaskState(&player->objWork, Player__State_CannonLanched);
        PlayPlayerSfx(player, PLAYER_SEQPLAYER_COMMON, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_PL_CANNON);
    }
}

NONMATCH_FUNC void Player__State_CannonLanched(Player *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	sub sp, sp, #8
	mov r5, r0
	ldr r4, [r5, #0x6d8]
	cmp r4, #0
	beq _02022C0C
	add ip, r5, #0x44
	add r3, r5, #0x8c
	ldmia ip, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	ldr r0, [r4, #0x28]
	cmp r0, #3
	bhs _0202280C
	add r0, r4, #0x44
	ldmia r0, {r0, r1, r2}
	stmia ip, {r0, r1, r2}
	bl CannonPath__GetOffsetZ
	str r0, [r5, #0x58]
	b _0202281C
_0202280C:
	ldr r0, [r4, #0x44]
	str r0, [r5, #0x44]
	ldr r0, [r4, #0x48]
	str r0, [r5, #0x48]
_0202281C:
	ldr r0, [r4, #0x28]
	cmp r0, #4
	addls pc, pc, r0, lsl #2
	b _02022BD4
_0202282C: // jump table
	b _02022840 // case 0
	b _02022840 // case 1
	b _02022880 // case 2
	b _02022AE0 // case 3
	b _02022AF4 // case 4
_02022840:
	ldrh r0, [r5, #0x30]
	mov r1, #0x3000
	mov r2, #0x380
	bl ObjRoopMove16
	strh r0, [r5, #0x30]
	ldrh r0, [r5, #0x32]
	mov r1, #0xe000
	mov r2, #0x380
	bl ObjRoopMove16
	strh r0, [r5, #0x32]
	ldrh r0, [r5, #0x34]
	mov r1, #0x4000
	mov r2, #0x380
	bl ObjRoopMove16
	strh r0, [r5, #0x34]
	b _02022BD4
_02022880:
	ldr r2, [r5, #0x24]
	tst r2, #2
	beq _02022954
	add r0, r5, #0x700
	ldrh r1, [r0, #0x22]
	ldr r0, =0x00000103
	and r0, r1, r0
	cmp r0, #2
	bne _02022954
	add r0, r5, #0x500
	ldrsh r0, [r0, #0xd4]
	cmp r0, #0x67
	mov r0, r5
	bne _020228D8
	mov r1, #0x68
	bl Player__ChangeAction
	ldrb r1, [r5, #0x6c9]
	mov r2, #0xa0
	mov r0, r5
	mov r1, r2, asr r1
	bl Player__GiveTension
	b _020228F4
_020228D8:
	mov r1, #0x67
	bl Player__ChangeAction
	ldrb r1, [r5, #0x6c9]
	mov r2, #0xa0
	mov r0, r5
	mov r1, r2, asr r1
	bl Player__GiveTension
_020228F4:
	ldr r1, [r5, #0x24]
	mov r0, r5
	bic r1, r1, #2
	str r1, [r5, #0x24]
	mov r1, #0xc8
	bl Player__GiveScore
	ldr r0, [r5, #0x24]
	tst r0, #0x20
	mov r0, r5
	beq _02022924
	bl StarCombo__FinishTrickCombo
	b _02022928
_02022924:
	bl StarCombo__PerformTrick
_02022928:
	mov r4, #0x3b
	sub r1, r4, #0x3c
	add r0, r5, #0x254
	mov r2, #0
	str r2, [sp]
	mov r2, r1
	mov r3, r1
	add r0, r0, #0x400
	str r4, [sp, #4]
	bl PlaySfxEx
	b _02022AA0
_02022954:
	tst r2, #4
	beq _020229FC
	add r0, r5, #0x700
	ldrh r1, [r0, #0x22]
	ldr r0, =0x00000103
	and r0, r1, r0
	cmp r0, #1
	bne _020229FC
	mov r1, #0
	strb r1, [r5, #0x6c9]
	mov r0, r5
	mov r1, #0x69
	bl Player__ChangeAction
	ldr r0, [r5, #0x24]
	mov r2, #0x140
	bic r0, r0, #4
	str r0, [r5, #0x24]
	ldrb r1, [r5, #0x6c9]
	mov r0, r5
	mov r1, r2, asr r1
	bl Player__GiveTension
	mov r0, r5
	mov r1, #0x190
	bl Player__GiveScore
	ldr r0, [r5, #0x24]
	tst r0, #0x20
	mov r0, r5
	beq _020229CC
	bl StarCombo__FinishTrickCombo
	b _020229D0
_020229CC:
	bl StarCombo__PerformTrick
_020229D0:
	mov r4, #0x3b
	sub r1, r4, #0x3c
	add r0, r5, #0x254
	mov r2, #0
	str r2, [sp]
	mov r2, r1
	mov r3, r1
	add r0, r0, #0x400
	str r4, [sp, #4]
	bl PlaySfxEx
	b _02022AA0
_020229FC:
	tst r2, #8
	beq _02022AA0
	add r0, r5, #0x700
	ldrh r1, [r0, #0x22]
	ldr r0, =0x00000103
	and r0, r1, r0
	cmp r0, #0x100
	bne _02022AA0
	mov r1, #0
	strb r1, [r5, #0x6c9]
	mov r0, r5
	mov r1, #0x64
	bl Player__ChangeAction
	ldr r0, [r5, #0x24]
	mov r2, #0x140
	bic r0, r0, #8
	str r0, [r5, #0x24]
	ldrb r1, [r5, #0x6c9]
	mov r0, r5
	mov r1, r2, asr r1
	bl Player__GiveTension
	mov r0, r5
	mov r1, #0xc8
	bl Player__GiveScore
	ldr r0, [r5, #0x24]
	tst r0, #0x20
	mov r0, r5
	beq _02022A74
	bl StarCombo__FinishTrickCombo
	b _02022A78
_02022A74:
	bl StarCombo__PerformTrick
_02022A78:
	mov r4, #0x3b
	sub r1, r4, #0x3c
	add r0, r5, #0x254
	mov r2, #0
	str r2, [sp]
	mov r2, r1
	mov r3, r1
	add r0, r0, #0x400
	str r4, [sp, #4]
	bl PlaySfxEx
_02022AA0:
	add r0, r5, #0x500
	ldrsh r0, [r0, #0xd4]
	cmp r0, #0x14
	beq _02022BD4
	ldr r0, [r5, #0x20]
	tst r0, #8
	beq _02022BD4
	orr r1, r0, #0x400
	mov r0, r5
	str r1, [r5, #0x20]
	mov r1, #0x14
	bl Player__ChangeAction
	ldr r0, [r5, #0x20]
	orr r0, r0, #4
	str r0, [r5, #0x20]
	b _02022BD4
_02022AE0:
	bl CannonPath__GetOffsetZ
	ldr r1, [r4, #0x4c]
	add r0, r1, r0
	str r0, [r5, #0x4c]
	b _02022BD4
_02022AF4:
	bl CannonPath__GetOffsetZ
	mov r1, #0xc8000
	rsb r1, r1, #0
	cmp r0, r1
	ble _02022B44
	ldrh r0, [r5, #0x30]
	mov r1, #0
	mov r2, #0xb6
	bl ObjRoopMove16
	strh r0, [r5, #0x30]
	ldrh r0, [r5, #0x32]
	mov r1, #0
	mov r2, #0xb6
	bl ObjRoopMove16
	strh r0, [r5, #0x32]
	ldrh r0, [r5, #0x34]
	mov r1, #0
	mov r2, #0x16c
	bl ObjRoopMove16
	strh r0, [r5, #0x34]
_02022B44:
	bl CannonPath__GetOffsetZ
	mov r1, #0x12c000
	rsb r1, r1, #0
	cmp r0, r1
	ble _02022B74
	ldr r0, [r5, #0x4c]
	mov r1, #0x1000
	bl ObjSpdDownSet
	mov r1, #0x1000
	rsb r1, r1, #0
	and r0, r0, r1
	str r0, [r5, #0x4c]
_02022B74:
	add r0, r5, #0x600
	ldrsh r1, [r0, #0xde]
	sub r1, r1, #1
	strh r1, [r0, #0xde]
	ldrsh r1, [r0, #0xde]
	cmp r1, #0
	movlt r1, #0
	strlth r1, [r0, #0xde]
	add r0, r5, #0x500
	ldrsh r0, [r0, #0xd4]
	cmp r0, #0x13
	beq _02022BD4
	ldrh r0, [r5, #0x34]
	cmp r0, #0x2000
	bhi _02022BD4
	ldr r1, [r5, #0x20]
	mov r0, r5
	orr r1, r1, #0x400
	str r1, [r5, #0x20]
	mov r1, #0x13
	bl Player__ChangeAction
	ldr r0, [r5, #0x20]
	orr r0, r0, #4
	str r0, [r5, #0x20]
_02022BD4:
	ldr r1, [r5, #0x44]
	ldr r0, [r5, #0x8c]
	add sp, sp, #8
	sub r0, r1, r0
	str r0, [r5, #0xbc]
	ldr r1, [r5, #0x48]
	ldr r0, [r5, #0x90]
	sub r0, r1, r0
	str r0, [r5, #0xc0]
	ldr r1, [r5, #0x4c]
	ldr r0, [r5, #0x94]
	sub r0, r1, r0
	str r0, [r5, #0xc4]
	ldmia sp!, {r3, r4, r5, pc}
_02022C0C:
	add r1, r5, #0x500
	mov r2, #0x3f
	strh r2, [r1, #0x3e]
	ldr r1, [r5, #0x5e4]
	cmp r1, #0
	addeq sp, sp, #8
	ldmeqia sp!, {r3, r4, r5, pc}
	bl Player__InitState
	ldr r0, [r5, #0x5e4]
	blx r0
	add sp, sp, #8
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

void Player__Func_2022C40(Player *player)
{
    if (StageTaskStateMatches(&player->objWork, Player__State_CannonLanched))
    {
        player->objWork.moveFlag &=
            ~(STAGE_TASK_MOVE_FLAG_IN_AIR | STAGE_TASK_MOVE_FLAG_DISABLE_COLLIDE_EVENT | STAGE_TASK_MOVE_FLAG_DISABLE_MOVE_EVENT | STAGE_TASK_MOVE_FLAG_DISABLE_SLOPE_ANGLES);
        player->objWork.displayFlag |= DISPLAY_FLAG_APPLY_CAMERA_CONFIG;
        player->gimmickFlag &= ~(PLAYER_GIMMICK_80 | PLAYER_GIMMICK_40 | PLAYER_GIMMICK_20 | PLAYER_GIMMICK_10);

        player->gimmickCamOffsetX = 0;
        player->gimmickCamOffsetY = 0;
        player->playerFlag &= ~(PLAYER_FLAG_2000 | PLAYER_FLAG_DISABLE_TENSION_DRAIN);
        player->colliders[0].defPower = PLAYER_DEFPOWER_NORMAL;

        player->objWork.dir.y = 0;
        Player__Action_Launch(player);

        player->objWork.velocity.x = player->objWork.move.x;
        player->objWork.velocity.y = player->objWork.move.y;
    }
}

void Player__Func_2022CD4(Player *player, u32 flags)
{
    u32 id = flags & ~0x80000000;
    if (StageTaskStateMatches(&player->objWork, Player__State_CannonLanched))
    {
        if (id >= 3)
            id = 0;

        player->objWork.userFlag = (player->objWork.userFlag | (1 << (id + 1))) & ~0x20;

        if (flags & 0x80000000)
            player->objWork.userFlag |= 0x20;
    }
}

void Player__Func_2022D24(Player *player, u8 flag)
{
    if (StageTaskStateMatches(&player->objWork, Player__State_CannonLanched))
        player->objWork.userFlag &= ~(1 << (flag + 1));
}

void Player__Gimmick_JumpBox(Player *player, GameObjectTask *other, CharacterID characterID)
{
    if ((player->playerFlag & PLAYER_FLAG_DEATH) != 0)
        return;

    Player__InitGimmick(player, FALSE);
    player->gimmickObj = other;

    Player__ChangeAction(player, PLAYER_ACTION_HANG_ROT);

    player->objWork.displayFlag |= DISPLAY_FLAG_PAUSED;
    Player__SetAnimFrame(player, FLOAT_TO_FX32(35.0));
    player->objWork.userTimer = FLOAT_TO_FX32(35.0);

    if (player->characterID == characterID)
        player->objWork.userFlag = FALSE;
    else
        player->objWork.userFlag = TRUE;

    player->gimmickFlag |= PLAYER_GIMMICK_20 | PLAYER_GIMMICK_10;
    player->gimmickCamOffsetX = 0;
    player->gimmickCamOffsetY = 64;

    player->playerFlag |= PLAYER_FLAG_DISABLE_TENSION_DRAIN;
    player->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_DISABLE_MOVE_EVENT | STAGE_TASK_MOVE_FLAG_DISABLE_COLLIDE_EVENT;

    player->objWork.velocity.x = player->objWork.velocity.y = 0;

    player->objWork.dir.z    = FLOAT_DEG_TO_IDX(0.0);
    player->objWork.userWork = JUMPBOX_STATE_CLIMBING;

    player->gimmickValue3 = 0;
    player->gimmickValue1 = player->objWork.position.x;
    player->gimmickValue2 = player->objWork.position.y;

    SetTaskState(&player->objWork, Player__State_JumpBox);
    PlayPlayerSfx(player, PLAYER_SEQPLAYER_COMMON, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_JUMP);
}

NONMATCH_FUNC void Player__State_JumpBox(Player *work)
{
    // https://decomp.me/scratch/2HcIQ -> 99.97%
    // small register issue around dir.z
#ifdef NON_MATCHING
    GameObjectTask *gimmickObj = work->gimmickObj;
    fx32 xOffset;
    fx32 launchDir;
    u16 dir;
    u16 id;
    u32 x, y;
    u32 velXStore, velYStore;

    if (work->gimmickObj == NULL)
    {
        work->actionJump(work);
        return;
    }

    work->objWork.prevPosition = work->objWork.position;

    switch (work->objWork.userWork)
    {
            // preparing...
            // the player is moving towards the target position to vault over here
        case JUMPBOX_STATE_CLIMBING:
            if ((work->objWork.displayFlag & DISPLAY_FLAG_FLIP_X) == 0)
                xOffset = -FLOAT_TO_FX32(2.0);
            else
                xOffset = FLOAT_TO_FX32(2.0);

            work->objWork.userTimer -= FLOAT_TO_FX32(0.625);
            work->gimmickValue3 += FLOAT_TO_FX32(0.125);

            if (work->gimmickValue3 >= FLOAT_TO_FX32(1.0))
            {
                work->objWork.userWork++;
                work->objWork.position.x = gimmickObj->objWork.position.x;
                work->objWork.position.y = gimmickObj->objWork.position.y - FLOAT_TO_FX32(62.0);
                EffectButtonPrompt__Create(&work->objWork, 1);
            }
            else
            {
                work->objWork.position.x = mtLerp((s16)work->gimmickValue3, work->gimmickValue1, gimmickObj->objWork.position.x + xOffset);
                work->objWork.position.y = mtLerpEx((s16)work->gimmickValue3, work->gimmickValue2, gimmickObj->objWork.position.y - FLOAT_TO_FX32(62.0), 2);
            }

            break;

            // main action area: press the jump button!!
            // player is vaulting over the jumpbox here!
        case JUMPBOX_STATE_VAULTING:
            work->objWork.userTimer += -FLOAT_TO_FX32(1.208251953125);
            if (work->objWork.userTimer <= FLOAT_TO_FX32(1.0))
            {
                work->objWork.userWork++;
                work->gimmickValue4 = -FLOAT_TO_FX32(1.208251953125);
                break;
            }

            if ((work->inputKeyPress & PLAYER_INPUT_JUMP) != 0)
            {
                id               = work->gimmickObj->mapObject->id;
                work->gimmickObj = NULL;
                work->gimmickFlag &= ~(PLAYER_GIMMICK_20 | PLAYER_GIMMICK_10);
                work->gimmickCamOffsetX = 0;
                work->gimmickCamOffsetY = 0;
                work->playerFlag &= ~PLAYER_FLAG_DISABLE_TENSION_DRAIN;
                work->objWork.displayFlag &= ~DISPLAY_FLAG_PAUSED;
                work->objWork.moveFlag &= ~(STAGE_TASK_MOVE_FLAG_DISABLE_MOVE_EVENT | STAGE_TASK_MOVE_FLAG_DISABLE_COLLIDE_EVENT);

                launchDir = (work->objWork.displayFlag & DISPLAY_FLAG_FLIP_X) != 0 ? -1 : 1;

                if ((work->objWork.userFlag & CHARACTER_BLAZE) != 0)
                {
                    if (id == MAPOBJECT_240)
                    {
                        y = gimmickObj->mapObject->height;
                        x = gimmickObj->mapObject->width;

                        if (y > 16)
                            y = 16;

                        if (x > 4)
                            x = 4;

                        Player__Action_JumpBoxPlaneSwitchLaunch(work, launchDir * (FLOAT_TO_FX32(1.3125) * x + FLOAT_TO_FX32(7.5)), -FLOAT_TO_FX32(1.3125) * y - FLOAT_TO_FX32(4.0),
                                                                FLOAT_TO_FX32(4.0));
                    }
                    else
                    {
                        x = MTM_MATH_CLIP(gimmickObj->mapObject->top, 0, 4);

                        Player__Action_JumpBoxLaunch(work, launchDir * (FLOAT_TO_FX32(1.3125) * x + FLOAT_TO_FX32(7.5)), -FLOAT_TO_FX32(4.0));
                    }
                }
                else
                {
                    dir = MultiplyFX(FX_Div(work->objWork.userTimer, NNS_G3dAnmObjGetNumFrame(work->objWork.obj_3d->ani.currentAnimObj[B3D_ANIM_JOINT_ANIM])), FLOAT_TO_FX32(16.0));

                    if (id == MAPOBJECT_240)
                    {
                        y = MTM_MATH_CLIP(gimmickObj->mapObject->top, 0, 16);
                        x = MTM_MATH_CLIP(gimmickObj->mapObject->left, 0, 9);

                        Player__Action_JumpBoxPlaneSwitchLaunch(work, launchDir * (FLOAT_TO_FX32(1.3125) * x + FLOAT_TO_FX32(2.0)), -FLOAT_TO_FX32(1.3125) * y - FLOAT_TO_FX32(7.5),
                                                                -FLOAT_TO_FX32(4.0));
                    }
                    else
                    {
                        y = MTM_MATH_CLIP(gimmickObj->mapObject->left, 0, 16);

                        Player__Action_JumpBoxLaunch(work, FX32_FROM_WHOLE(launchDir << 1), -FLOAT_TO_FX32(1.3125) * y - FLOAT_TO_FX32(7.5));
                    }

                    if ((work->objWork.displayFlag & DISPLAY_FLAG_FLIP_X) != 0)
                    {
                        dir = FLOAT_DEG_TO_IDX(180.0) + dir;
                    }
                    else
                    {
                        dir = FLOAT_DEG_TO_IDX(180.0) - dir;
                    }
                    work->objWork.dir.z = dir;
                }

                Player__Action_AllowTrickCombos(work, gimmickObj);
                PlayPlayerSfx(work, PLAYER_SEQPLAYER_COMMON, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_TOBIBAKO);
                return;
            }
            break;

            // reached the other side of the jumpbox... its over
            // player is vaulting over the other side of the jumpbox here
        case JUMPBOX_STATE_VAULTED:
            work->objWork.userTimer += work->gimmickValue4;
            work->gimmickValue4 -= FLOAT_TO_FX32(0.0625);

            if (work->objWork.userTimer < 0)
            {
                work->objWork.userTimer += NNS_G3dAnmObjGetNumFrame(work->objWork.obj_3d->ani.currentAnimObj[B3D_ANIM_JOINT_ANIM]) - 1;
                work->objWork.userWork++;

                if ((work->objWork.displayFlag & DISPLAY_FLAG_FLIP_X) != 0)
                    work->objWork.velocity.x = -FLOAT_TO_FX32(2.0);
                else
                    work->objWork.velocity.x = FLOAT_TO_FX32(2.0);

                work->objWork.velocity.y = FLOAT_TO_FX32(0.5);
            }

            break;

            // finishing up...
            // player is letting go of the jump bpx here
        case JUMPBOX_STATE_EXIT:
            work->objWork.userTimer += work->gimmickValue4;
            work->gimmickValue4 -= FLOAT_TO_FX32(0.0625);

            if ((work->objWork.displayFlag & DISPLAY_FLAG_FLIP_X) != 0)
                work->objWork.velocity.x = ObjSpdUpSet(work->objWork.velocity.x, -FLOAT_TO_FX32(0.25), FLOAT_TO_FX32(2.0));
            else
                work->objWork.velocity.x = ObjSpdUpSet(work->objWork.velocity.x, FLOAT_TO_FX32(0.25), FLOAT_TO_FX32(2.0));

            work->objWork.velocity.y = ObjSpdUpSet(work->objWork.velocity.y, FLOAT_TO_FX32(0.03125), FLOAT_TO_FX32(5.0));
            work->objWork.position.x += work->objWork.velocity.x;
            work->objWork.position.y += work->objWork.velocity.y;

            if (work->objWork.userTimer <= FLOAT_TO_FX32(46.0))
            {
                work->gimmickObj = NULL;
                work->gimmickFlag &= ~(PLAYER_GIMMICK_20 | PLAYER_GIMMICK_10);
                work->gimmickCamOffsetX = 0;
                work->gimmickCamOffsetY = 0;
                work->playerFlag &= ~PLAYER_FLAG_DISABLE_TENSION_DRAIN;
                work->objWork.displayFlag &= ~DISPLAY_FLAG_PAUSED;
                work->objWork.moveFlag &= ~(STAGE_TASK_MOVE_FLAG_DISABLE_MOVE_EVENT | STAGE_TASK_MOVE_FLAG_DISABLE_COLLIDE_EVENT);

                if ((work->objWork.displayFlag & DISPLAY_FLAG_FLIP_X) != 0)
                    work->objWork.groundVel -= FLOAT_TO_FX32(1.0);
                else
                    work->objWork.groundVel += FLOAT_TO_FX32(1.0);

                velXStore = work->objWork.velocity.x;
                velYStore = work->objWork.velocity.y;
                work->objWork.displayFlag |= DISPLAY_FLAG_400;
                Player__Action_Launch(work);
                work->objWork.velocity.x = velXStore;
                work->objWork.velocity.y = velYStore;

                return;
            }
            break;

        default:
            break;
    }

    Player__SetAnimFrame(work, work->objWork.userTimer);
    work->objWork.move.x = work->objWork.position.x - work->objWork.prevPosition.x;
    work->objWork.move.y = work->objWork.position.y - work->objWork.prevPosition.y;
#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
	sub sp, sp, #8
	mov r5, r0
	ldr r4, [r5, #0x6d8]
	cmp r4, #0
	bne _02022E80
	ldr r1, [r5, #0x5f0]
	blx r1
	add sp, sp, #8
	ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
_02022E80:
	add r0, r5, #0x44
	add r3, r5, #0x8c
	ldmia r0, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	ldr r0, [r5, #0x28]
	cmp r0, #3
	addls pc, pc, r0, lsl #2
	b _020233C4
_02022EA0: // jump table
	b _02022EB0 // case 0
	b _02022FD0 // case 1
	b _0202323C // case 2
	b _020232B4 // case 3
_02022EB0:
	ldr r0, [r5, #0x20]
	mov r2, #0x2000
	tst r0, #1
	ldr r0, [r5, #0x2c]
	rsbeq r2, r2, #0
	sub r0, r0, #0xa00
	str r0, [r5, #0x2c]
	ldr r0, [r5, #0x6f8]
	add r0, r0, #0x200
	str r0, [r5, #0x6f8]
	cmp r0, #0x1000
	blt _02022F10
	ldr r1, [r5, #0x28]
	mov r0, r5
	add r1, r1, #1
	str r1, [r5, #0x28]
	ldr r2, [r4, #0x44]
	mov r1, #1
	str r2, [r5, #0x44]
	ldr r2, [r4, #0x48]
	sub r2, r2, #0x3e000
	str r2, [r5, #0x48]
	bl EffectButtonPrompt__Create
	b _020233C4
_02022F10:
	mov r0, r0, lsl #0x10
	mov r6, r0, asr #0x10
	ldr r1, [r4, #0x44]
	ldr r0, [r5, #0x6f0]
	add r1, r1, r2
	mov r3, r6, asr #0x1f
	mov r2, #1
	mov ip, #0
	mov r7, #0x800
_02022F34:
	sub r8, r1, r0
	umull lr, r9, r8, r6
	mla r9, r8, r3, r9
	mov r8, r8, asr #0x1f
	mla r9, r8, r6, r9
	adds lr, lr, r7
	adc r8, r9, ip
	mov r9, lr, lsr #0xc
	orr r9, r9, r8, lsl #20
	cmp r2, #0
	add r0, r0, r9
	sub r2, r2, #1
	bne _02022F34
	str r0, [r5, #0x44]
	ldr r0, [r5, #0x6f8]
	ldr r1, [r4, #0x48]
	mov r0, r0, lsl #0x10
	mov r4, r0, asr #0x10
	ldr r0, [r5, #0x6f4]
	sub r1, r1, #0x3e000
	mov r3, r4, asr #0x1f
	mov r2, #2
	mov r7, #0
	mov r6, #0x800
_02022F94:
	sub ip, r1, r0
	umull r8, lr, ip, r4
	mla lr, ip, r3, lr
	mov ip, ip, asr #0x1f
	adds r9, r8, r6
	mla lr, ip, r4, lr
	adc r8, lr, r7
	mov r9, r9, lsr #0xc
	orr r9, r9, r8, lsl #20
	cmp r2, #0
	add r0, r0, r9
	sub r2, r2, #1
	bne _02022F94
	str r0, [r5, #0x48]
	b _020233C4
_02022FD0:
	ldr r1, [r5, #0x2c]
	ldr r0, =0xFFFFECAB
	add r1, r1, r0
	str r1, [r5, #0x2c]
	cmp r1, #0x1000
	bgt _02022FFC
	ldr r1, [r5, #0x28]
	add r1, r1, #1
	str r1, [r5, #0x28]
	str r0, [r5, #0x6fc]
	b _020233C4
_02022FFC:
	add r0, r5, #0x700
	ldrh r0, [r0, #0x22]
	tst r0, #3
	beq _020233C4
	ldr r1, [r5, #0x6d8]
	mov r0, #0
	ldr r2, [r1, #0x340]
	add r1, r5, #0x600
	ldrh r6, [r2, #2]
	str r0, [r5, #0x6d8]
	ldr r2, [r5, #0x5dc]
	bic r2, r2, #0x30
	str r2, [r5, #0x5dc]
	strh r0, [r1, #0xdc]
	strh r0, [r1, #0xde]
	ldr r1, [r5, #0x5d8]
	bic r1, r1, #0x100000
	str r1, [r5, #0x5d8]
	ldr r1, [r5, #0x20]
	bic r1, r1, #0x10
	str r1, [r5, #0x20]
	ldr r1, [r5, #0x1c]
	bic r1, r1, #0x2100
	str r1, [r5, #0x1c]
	ldr r1, [r5, #0x20]
	tst r1, #1
	subne r7, r0, #1
	ldr r0, [r5, #0x24]
	moveq r7, #1
	tst r0, #1
	beq _02023100
	cmp r6, #0xf0
	ldr r0, [r4, #0x340]
	bne _020230C8
	ldrb r3, [r0, #9]
	ldrb r2, [r0, #8]
	mov r0, #0x1500
	cmp r3, #0x10
	movhi r3, #0x10
	cmp r2, #4
	movhi r2, #4
	mul r1, r2, r0
	sub r0, r0, #0x2a00
	mul r2, r3, r0
	add r1, r1, #0x7800
	mul r1, r7, r1
	mov r0, r5
	sub r2, r2, #0x4000
	mov r3, #0x4000
	bl Player__Action_JumpBoxPlaneSwitchLaunch
	b _02023200
_020230C8:
	ldrsb r1, [r0, #7]
	cmp r1, #0
	movlt r1, #0
	blt _020230E0
	cmp r1, #4
	movgt r1, #4
_020230E0:
	mov r2, #0x1500
	mul r0, r1, r2
	add r0, r0, #0x7800
	mul r1, r7, r0
	mov r0, r5
	sub r2, r2, #0x5500
	bl Player__Action_JumpBoxLaunch
	b _02023200
_02023100:
	ldr r1, [r5, #0x12c]
	ldr r0, [r5, #0x2c]
	ldr r1, [r1, #0xe4]
	ldr r1, [r1, #8]
	ldrh r1, [r1, #4]
	mov r1, r1, lsl #0xc
	bl FX_Div
	mov r1, r0, asr #0x1f
	mov r2, r1, lsl #0x10
	mov r1, #0x800
	adds r1, r1, r0, lsl #16
	orr r2, r2, r0, lsr #16
	adc r0, r2, #0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #20
	mov r0, r1, lsl #0x10
	cmp r6, #0xf0
	mov r6, r0, lsr #0x10
	mov r0, #0
	ldr r1, [r4, #0x340]
	bne _020231B0
	ldrsb r8, [r1, #7]
	cmp r8, #0
	movlt r8, r0
	blt _0202316C
	cmp r8, #0x10
	movgt r8, #0x10
_0202316C:
	ldrsb r0, [r1, #6]
	cmp r0, #0
	movlt r0, #0
	blt _02023184
	cmp r0, #9
	movgt r0, #9
_02023184:
	mov r3, #0x1500
	mul r1, r0, r3
	sub r0, r3, #0x2a00
	add r1, r1, #0x2000
	mul r2, r8, r0
	mul r1, r7, r1
	mov r0, r5
	sub r2, r2, #0x7800
	sub r3, r3, #0x5500
	bl Player__Action_JumpBoxPlaneSwitchLaunch
	b _020231E4
_020231B0:
	ldrsb r1, [r1, #6]
	cmp r1, #0
	movlt r1, r0
	blt _020231C8
	cmp r1, #0x10
	movgt r1, #0x10
_020231C8:
	mov r0, #0x1500
	rsb r0, r0, #0
	mul r2, r1, r0
	mov r0, r5
	mov r1, r7, lsl #0xd
	sub r2, r2, #0x7800
	bl Player__Action_JumpBoxLaunch
_020231E4:
	ldr r0, [r5, #0x20]
	tst r0, #1
	addne r0, r6, #0x8000
	rsbeq r0, r6, #0x8000
	mov r0, r0, lsl #0x10
	mov r6, r0, lsr #0x10
	strh r6, [r5, #0x34]
_02023200:
	mov r0, r5
	mov r1, r4
	bl Player__Action_AllowTrickCombos
	mov r4, #0x6b
	sub r1, r4, #0x6c
	add r0, r5, #0x254
	mov r2, #0
	str r2, [sp]
	mov r2, r1
	mov r3, r1
	add r0, r0, #0x400
	str r4, [sp, #4]
	bl PlaySfxEx
	add sp, sp, #8
	ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
_0202323C:
	ldr r1, [r5, #0x2c]
	ldr r0, [r5, #0x6fc]
	add r0, r1, r0
	str r0, [r5, #0x2c]
	ldr r0, [r5, #0x6fc]
	sub r0, r0, #0x100
	str r0, [r5, #0x6fc]
	ldr r0, [r5, #0x2c]
	cmp r0, #0
	bge _020233C4
	ldr r0, [r5, #0x12c]
	ldr r1, [r5, #0x2c]
	ldr r0, [r0, #0xe4]
	ldr r0, [r0, #8]
	ldrh r0, [r0, #4]
	mov r0, r0, lsl #0xc
	sub r0, r0, #1
	add r0, r1, r0
	str r0, [r5, #0x2c]
	ldr r0, [r5, #0x28]
	add r0, r0, #1
	str r0, [r5, #0x28]
	ldr r0, [r5, #0x20]
	tst r0, #1
	mov r0, #0x2000
	rsbne r0, r0, #0
	str r0, [r5, #0x98]
	mov r0, #0x800
	str r0, [r5, #0x9c]
	b _020233C4
_020232B4:
	ldr r1, [r5, #0x2c]
	ldr r0, [r5, #0x6fc]
	mov r2, #0x2000
	add r0, r1, r0
	str r0, [r5, #0x2c]
	ldr r0, [r5, #0x6fc]
	mov r1, #0x400
	sub r0, r0, #0x100
	str r0, [r5, #0x6fc]
	ldr r0, [r5, #0x20]
	tst r0, #1
	ldr r0, [r5, #0x98]
	beq _020232F4
	rsb r1, r1, #0
	bl ObjSpdUpSet
	b _020232F8
_020232F4:
	bl ObjSpdUpSet
_020232F8:
	str r0, [r5, #0x98]
	ldr r0, [r5, #0x9c]
	mov r1, #0x80
	mov r2, #0x5000
	bl ObjSpdUpSet
	str r0, [r5, #0x9c]
	ldr r1, [r5, #0x44]
	ldr r0, [r5, #0x98]
	add r0, r1, r0
	str r0, [r5, #0x44]
	ldr r1, [r5, #0x48]
	ldr r0, [r5, #0x9c]
	add r0, r1, r0
	str r0, [r5, #0x48]
	ldr r0, [r5, #0x2c]
	cmp r0, #0x2e000
	bgt _020233C4
	mov r2, #0
	str r2, [r5, #0x6d8]
	ldr r1, [r5, #0x5dc]
	add r0, r5, #0x600
	bic r1, r1, #0x30
	str r1, [r5, #0x5dc]
	strh r2, [r0, #0xdc]
	strh r2, [r0, #0xde]
	ldr r0, [r5, #0x5d8]
	bic r0, r0, #0x100000
	str r0, [r5, #0x5d8]
	ldr r0, [r5, #0x20]
	bic r0, r0, #0x10
	str r0, [r5, #0x20]
	ldr r0, [r5, #0x1c]
	bic r0, r0, #0x2100
	str r0, [r5, #0x1c]
	ldr r0, [r5, #0x20]
	tst r0, #1
	ldr r0, [r5, #0xc8]
	subne r0, r0, #0x1000
	addeq r0, r0, #0x1000
	str r0, [r5, #0xc8]
	ldr r0, [r5, #0x20]
	ldr r4, [r5, #0x98]
	orr r1, r0, #0x400
	ldr r6, [r5, #0x9c]
	mov r0, r5
	str r1, [r5, #0x20]
	bl Player__Action_Launch
	str r4, [r5, #0x98]
	add sp, sp, #8
	str r6, [r5, #0x9c]
	ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
_020233C4:
	ldr r1, [r5, #0x2c]
	mov r0, r5
	bl Player__SetAnimFrame
	ldr r1, [r5, #0x44]
	ldr r0, [r5, #0x8c]
	sub r0, r1, r0
	str r0, [r5, #0xbc]
	ldr r1, [r5, #0x48]
	ldr r0, [r5, #0x90]
	sub r0, r1, r0
	str r0, [r5, #0xc0]
	add sp, sp, #8
	ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}

// clang-format on
#endif
}

void Player__Action_JumpBoxLaunch(Player *player, fx32 velX, fx32 velY)
{
    Player__Gimmick_Jump(player, velX, velY);

    if (MATH_ABS(velY) > MATH_ABS(velX))
    {
        if ((player->gimmickFlag & PLAYER_GIMMICK_SNOWBOARD) == 0)
        {
            Player__ChangeAction(player, PLAYER_ACTION_AIRRISE);
        }
        else
        {
            Player__ChangeAction(player, PLAYER_ACTION_AIRRISE_SNOWBOARD);
            ChangePlayerSnowboardAction(player, PLAYERSNOWBOARD_ACTION_AIRRISE);
        }
    }
}

void Player__Action_JumpBoxPlaneSwitchLaunch(Player *player, fx32 velX, fx32 velY, fx32 velZ)
{
    player->objWork.groundVel  = 0;
    player->objWork.velocity.x = player->objWork.velocity.y = 0;

    Player__Gimmick_Jump(player, velX, velY);
    Player__ChangeAction(player, PLAYER_ACTION_AIRRISE);
    player->objWork.velocity.z = velZ;
    player->playerFlag |= PLAYER_FLAG_DISABLE_INPUT_READ | PLAYER_FLAG_SLOWMO | PLAYER_FLAG_DISABLE_TRICK_FINISHER | PLAYER_FLAG_FINISHED_TRICK_COMBO;
    player->slomoTimer   = 0;
    player->inputKeyDown = player->inputKeyPress = player->inputKeyRepeat = PAD_INPUT_NONE_MASK;
    player->gimmickFlag |= PLAYER_GIMMICK_20000000;

    if (velZ <= 0)
        player->objWork.flag |= STAGE_TASK_FLAG_ON_PLANE_B;
    else
        player->objWork.flag &= ~STAGE_TASK_FLAG_ON_PLANE_B;

    if (velZ < 0)
    {
        if (velX >= 0)
        {
            player->objWork.dir.y = -FLOAT_DEG_TO_IDX(45.0);
        }
        else
        {
            player->objWork.dir.y = FLOAT_DEG_TO_IDX(45.0);
        }
    }
    else
    {
        if (velX >= 0)
        {
            player->objWork.dir.y = FLOAT_DEG_TO_IDX(45.0);
        }
        else
        {
            player->objWork.dir.y = -FLOAT_DEG_TO_IDX(45.0);
        }
    }

    player->colliders[0].defPower = PLAYER_DEFPOWER_INVINCIBLE;

    SetTaskState(&player->objWork, Player__State_JumpBoxPlaneSwitchLaunch);
}

void Player__State_JumpBoxPlaneSwitchLaunch(Player *work)
{
    work->colliders[0].defPower = PLAYER_DEFPOWER_INVINCIBLE;

    if (work->objWork.velocity.z >= 0)
    {
        if (work->objWork.position.z + work->objWork.velocity.z >= FLOAT_TO_FX32(50.0))
        {
            work->objWork.velocity.z = FLOAT_TO_FX32(50.0) - work->objWork.position.z;
        }
    }
    else
    {
        if (work->objWork.position.z + work->objWork.velocity.z <= -FLOAT_TO_FX32(80.0))
        {
            work->objWork.velocity.z = -FLOAT_TO_FX32(80.0) - work->objWork.position.z;
        }
    }

    work->objWork.dir.y = ObjRoopMove16(work->objWork.dir.y, 0, FLOAT_TO_FX32(0.03125));

    Player__State_Air(work);

    if (!StageTaskStateMatches(&work->objWork, Player__State_JumpBoxPlaneSwitchLaunch))
    {
        work->playerFlag &= ~(PLAYER_FLAG_DISABLE_INPUT_READ | PLAYER_FLAG_SLOWMO);
        work->objWork.dir.y         = 0;
        work->colliders[0].defPower = PLAYER_DEFPOWER_NORMAL;
    }
}

void Player__Action_PlaneSwitchSpring(Player *player, fx32 velX, fx32 velY)
{
    player->objWork.groundVel  = 0;
    player->objWork.velocity.x = player->objWork.velocity.y = 0;

    Player__Gimmick_Jump(player, velX, velY);
    player->playerFlag |= PLAYER_FLAG_SLOWMO | PLAYER_FLAG_DISABLE_TRICK_FINISHER | PLAYER_FLAG_USER_FLAG;
    player->slomoTimer = 0;

    PlayPlayerSfx(player, PLAYER_SEQPLAYER_COMMON, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_SPRING);

    if (player->objWork.position.z < 0)
    {
        player->objWork.velocity.z = FLOAT_TO_FX32(4.0);
    }
    else if (player->objWork.position.z > 0)
    {
        player->objWork.velocity.z = -FLOAT_TO_FX32(3.0);
    }

    player->objWork.flag |= STAGE_TASK_FLAG_ON_PLANE_B;
    SetTaskState(&player->objWork, Player__State_PlaneSwitchSpring);
}

void Player__State_PlaneSwitchSpring(Player *work)
{
    u16 targetDir = 0;
    fx32 speed    = FLOAT_TO_FX32(0.0625);

    if (work->objWork.velocity.z >= 0)
    {
        if (work->objWork.position.z + work->objWork.velocity.z >= 0)
        {
            work->objWork.velocity.z = -work->objWork.position.z;
        }
    }
    else
    {
        if (work->objWork.position.z + work->objWork.velocity.z <= 0)
        {
            work->objWork.velocity.z = -work->objWork.position.z;
        }
    }

    if (work->objWork.velocity.z < 0)
    {
        speed = FLOAT_TO_FX32(0.25);

        if (work->objWork.velocity.x >= 0)
            targetDir = -FLOAT_DEG_TO_IDX(45.0);
        else
            targetDir = FLOAT_DEG_TO_IDX(45.0);
    }
    else if (work->objWork.velocity.z > 0)
    {
        speed = FLOAT_TO_FX32(0.25);

        if (work->objWork.velocity.x >= 0)
            targetDir = FLOAT_DEG_TO_IDX(45.0);
        else
            targetDir = -FLOAT_DEG_TO_IDX(45.0);
    }

    work->objWork.dir.y = ObjRoopMove16(work->objWork.dir.y, targetDir, speed);

    Player__State_Air(work);

    if (!StageTaskStateMatches(&work->objWork, Player__State_PlaneSwitchSpring) || (work->objWork.velocity.z == 0 && work->objWork.dir.y == 0))
    {
        work->objWork.dir.y = 0;
        work->gimmickFlag &= ~PLAYER_GIMMICK_20000000;
        work->playerFlag &= ~PLAYER_FLAG_SLOWMO;
    }
}

void Player__Func_202374C(Player *player)
{
    if (!StageTaskStateMatches(&player->objWork, Player__State_PlaneSwitchSpring) && !StageTaskStateMatches(&player->objWork, Player__State_JumpBoxPlaneSwitchLaunch))
    {
        player->gimmickFlag &= ~PLAYER_GIMMICK_20000000;
        player->objWork.flag |= STAGE_TASK_FLAG_ON_PLANE_B;

        if (player->objWork.position.z != 0)
            player->blazeHoverTimer = 0;
    }
}

void Player__Func_202379C(Player *player, GameObjectTask *other)
{
    Player__Gimmick_201B500(player, other, 0, 0, 0);
    SetTaskState(&player->objWork, Player__State_2023858);

    player->playerFlag |= PLAYER_FLAG_FINISHED_TRICK_COMBO;
    player->objWork.userFlag |= (1 | 2 | 8);
    player->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_DISABLE_COLLIDE_EVENT;
    player->gimmickFlag |= PLAYER_GIMMICK_GRABBED | PLAYER_GIMMICK_20 | PLAYER_GIMMICK_10;
    player->playerFlag |= PLAYER_FLAG_DISABLE_TENSION_DRAIN;

    player->gimmickCamOffsetX = 0;
    player->gimmickCamOffsetY = 160;
    Player__ChangeAction(player, PLAYER_ACTION_32);

    player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;
    player->objWork.displayFlag &= ~DISPLAY_FLAG_FLIP_X;
    player->objWork.displayFlag |= other->objWork.displayFlag & DISPLAY_FLAG_FLIP_X;

    player->objWork.dir.x = player->objWork.dir.y = player->objWork.dir.z = 0;
}

NONMATCH_FUNC void Player__State_2023858(Player *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, r7, lr}
	mov r7, r0
	ldr r4, [r7, #0x6d8]
	mov r1, #0
	mov r5, r1
	mov r6, r1
	cmp r4, #0
	beq _020238E4
	ldr r0, [r4, #0x24]
	tst r0, #1
	bne _020238E4
	add r0, r7, #0x700
	ldrh r0, [r0, #0x22]
	tst r0, #3
	beq _020238E4
	ldrh r0, [r4, #0x34]
	ldr r5, [r4, #0x98]
	ldr r6, [r4, #0x9c]
	cmp r0, #0x8000
	movhi r0, r1
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, asr #4
	mov r0, r0, lsl #1
	add r1, r0, #1
	ldr r0, =FX_SinCosTable_
	mov r1, r1, lsl #1
	ldrsh r0, [r0, r1]
	smull r1, r0, r5, r0
	adds r1, r1, #0x800
	adc r0, r0, #0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #20
	sub r6, r6, r1, asr #1
	sub r5, r5, r1
_020238E4:
	mov r0, r7
	bl Player__State_201B5A0
	cmp r5, #0
	cmpeq r6, #0
	beq _02023918
	str r5, [r7, #0x98]
	str r6, [r7, #0x9c]
	add r0, r7, #0x500
	mov r1, #0x40
	strh r1, [r0, #0xfa]
	ldr r0, [r7, #0x5d8]
	orr r0, r0, #1
	str r0, [r7, #0x5d8]
_02023918:
	ldr r1, [r7, #0xf4]
	ldr r0, =Player__State_2023858
	cmp r1, r0
	cmpne r4, #0
	ldmeqia sp!, {r3, r4, r5, r6, r7, pc}
	mov r0, r7
	mov r1, r4
	bl Player__Action_AllowTrickCombos
	ldmia sp!, {r3, r4, r5, r6, r7, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__Gimmick_2023944(Player *player, GameObjectTask *other)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r4, r1
	mov r5, r0
	mov r1, #0
	bl Player__InitGimmick
	mov r0, r5
	bl Player__InitState
	ldr r1, =Player__State_2023A4C
	str r4, [r5, #0x6d8]
	ldr r0, =Player__OnDefend_Regular4
	str r1, [r5, #0xf4]
	str r0, [r5, #0x534]
	ldr r1, [r5, #0x1c]
	ldr r0, =0xFFFF7F7F
	orr r1, r1, #0x110
	and r0, r1, r0
	str r0, [r5, #0x1c]
	ldr r1, [r5, #0x20]
	mov r0, r5
	bic r2, r1, #1
	str r2, [r5, #0x20]
	ldr r1, [r4, #0x20]
	and r1, r1, #1
	orr r1, r2, r1
	str r1, [r5, #0x20]
	bl Player__Action_StopBoost
	mov r0, r5
	bl Player__Action_StopSuperBoost
	ldr r0, [r5, #0x5dc]
	mov r2, #0
	orr r0, r0, #0x10
	str r0, [r5, #0x5dc]
	ldr r0, [r5, #0x5d8]
	orr r0, r0, #0x2000
	orr r0, r0, #0x100000
	str r0, [r5, #0x5d8]
	ldr r0, [r5, #0x20]
	tst r0, #1
	movne r1, #0x70
	add r0, r5, #0x600
	mvneq r1, #0x6f
	strh r1, [r0, #0xdc]
	add r1, r5, #0x600
	strh r2, [r1, #0xde]
	mov r0, r5
	mov r1, #0x38
	bl Player__ChangeAction
	ldr r1, [r5, #0x20]
	add r0, r4, #0x44
	orr r1, r1, #4
	bic r1, r1, #0x200
	str r1, [r5, #0x20]
	add r4, r5, #0x44
	ldmia r0, {r0, r1, r2}
	stmia r4, {r0, r1, r2}
	mov r3, #0
	strh r3, [r5, #0x34]
	strh r3, [r5, #0x32]
	strh r3, [r5, #0x30]
	str r3, [r5, #0xc8]
	str r3, [r5, #0x9c]
	str r3, [r5, #0x98]
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__State_2023A4C(Player *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
	mov r5, r0
	ldr r1, [r5, #0x6d8]
	mov r4, #0
	cmp r1, #0
	beq _02023A98
	ldr r1, [r1, #0x1c]
	tst r1, #0xf
	beq _02023A98
	bl Player__Func_2023FC8
	ldr r0, [r5, #0x20]
	mov r2, #0x3000
	tst r0, #1
	mov r1, #0x2000
	rsbeq r1, r1, #0
	mov r0, r5
	rsb r2, r2, #0
	bl Player__Action_HurtAlt
	ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
_02023A98:
	ldr r0, [r5, #0x24]
	tst r0, #1
	beq _02023C3C
	ldr r0, [r5, #0x2c]
	add r0, r0, #0x80
	str r0, [r5, #0x2c]
	cmp r0, #0x800
	bge _02023B24
	ldr r6, [r5, #0x6f0]
	ldr r1, [r5, #0x6f4]
	mov r0, r0, lsl #0x11
	sub r1, r1, r6
	mov r3, r0, asr #0x10
	add r9, r6, r1, asr #1
	mov r2, r3, asr #0x1f
	mov r1, #1
	mov r8, #0
	mov r7, #0x800
_02023AE0:
	sub r10, r9, r6
	umull r0, ip, r10, r3
	mla ip, r10, r2, ip
	mov r9, r10, asr #0x1f
	adds r0, r0, r7
	mla ip, r9, r3, ip
	adc r9, ip, r8
	mov r0, r0, lsr #0xc
	orr r0, r0, r9, lsl #20
	cmp r1, #0
	add r9, r6, r0
	sub r1, r1, #1
	bne _02023AE0
	ldr r0, [r5, #0x4c]
	sub r0, r9, r0
	str r0, [r5, #0xa0]
	b _02023C00
_02023B24:
	cmp r0, #0x1000
	bge _02023B9C
	sub r0, r0, #0x800
	mov r0, r0, lsl #0x11
	mov r9, r0, asr #0x10
	ldr r10, [r5, #0x6f4]
	ldr r1, [r5, #0x6f0]
	mov r8, r9, asr #0x1f
	sub r0, r10, r1
	add r6, r1, r0, asr #1
	mov r7, #1
	mov r1, #0
	mov r0, #0x800
_02023B58:
	sub r3, r10, r6
	umull r2, ip, r3, r9
	adds r2, r2, r0
	mov lr, r2, lsr #0xc
	mla ip, r3, r8, ip
	mov r2, r3, asr #0x1f
	mla ip, r2, r9, ip
	adc r2, ip, r1
	orr lr, lr, r2, lsl #20
	cmp r7, #0
	add r6, r6, lr
	sub r7, r7, #1
	bne _02023B58
	ldr r0, [r5, #0x4c]
	sub r0, r6, r0
	str r0, [r5, #0xa0]
	b _02023C00
_02023B9C:
	ldr r2, [r5, #0x6f4]
	ldr r0, [r5, #0x6f0]
	mov r1, #1
	sub r0, r2, r0
	mov r0, r0, asr #1
	mov r6, #0
	mov r3, #0x800
_02023BB8:
	sub r8, r2, r0
	mov r7, r8, asr #0x1f
	mov r7, r7, lsl #0xc
	adds r9, r3, r8, lsl #12
	orr r7, r7, r8, lsr #20
	adc r7, r7, r6
	mov r8, r9, lsr #0xc
	orr r8, r8, r7, lsl #20
	cmp r1, #0
	add r0, r0, r8
	sub r1, r1, #1
	bne _02023BB8
	ldr r1, [r5, #0x4c]
	sub r0, r0, r1
	str r0, [r5, #0xa0]
	ldr r0, [r5, #0x24]
	bic r0, r0, #1
	str r0, [r5, #0x24]
_02023C00:
	ldr r3, [r5, #0x4c]
	ldr r0, [r5, #0x94]
	ldr r2, [r5, #0x44]
	ldr r1, [r5, #0x8c]
	sub r0, r3, r0
	sub r1, r2, r1
	bl FX_Atan2Idx
	strh r0, [r5, #0x32]
	ldr r0, [r5, #0x20]
	tst r0, #1
	beq _02023DE8
	ldrh r0, [r5, #0x32]
	add r0, r0, #0x8000
	strh r0, [r5, #0x32]
	b _02023DE8
_02023C3C:
	mov r1, #0
	strh r1, [r5, #0x32]
	str r1, [r5, #0xa0]
	ldr r0, [r5, #0x20]
	tst r0, #1
	beq _02023C6C
	mov r0, #0x200
	sub r11, r1, #0x200
	mov r7, #0x20
	mov r6, #0x10
	str r0, [sp]
	b _02023C80
_02023C6C:
	mov r6, #0x20
	sub r0, r6, #0x220
	str r0, [sp]
	mov r11, #0x200
	mov r7, #0x10
_02023C80:
	ldr r0, [r5, #0xc8]
	add r1, r5, #0x700
	cmp r0, #0
	ldrh r4, [r1, #0x20]
	rsblt r1, r0, #0
	movge r1, r0
	cmp r1, #0x4000
	bge _02023CB0
	mov r1, r11
	mov r2, #0x4000
	bl ObjSpdUpSet
	str r0, [r5, #0xc8]
_02023CB0:
	tst r4, r7
	beq _02023CE4
	ldr r0, [r5, #0xc8]
	cmp r0, #0
	rsblt r1, r0, #0
	movge r1, r0
	cmp r1, #0x6000
	bge _02023DB0
	mov r1, r11
	mov r2, #0x6000
	bl ObjSpdUpSet
	str r0, [r5, #0xc8]
	b _02023DB0
_02023CE4:
	tst r4, r6
	beq _02023D50
	cmp r11, #0
	ble _02023D1C
	ldr r0, [r5, #0xc8]
	cmp r0, #0x2000
	ble _02023DB0
	mov r1, #0x400
	bl ObjSpdDownSet
	str r0, [r5, #0xc8]
	cmp r0, #0x2000
	movlt r0, #0x2000
	strlt r0, [r5, #0xc8]
	b _02023DB0
_02023D1C:
	mov r1, #0x2000
	ldr r0, [r5, #0xc8]
	rsb r1, r1, #0
	cmp r0, r1
	bge _02023DB0
	mov r1, #0x400
	bl ObjSpdDownSet
	mov r1, #0x2000
	rsb r1, r1, #0
	str r0, [r5, #0xc8]
	cmp r0, r1
	strgt r1, [r5, #0xc8]
	b _02023DB0
_02023D50:
	cmp r11, #0
	ble _02023D80
	ldr r0, [r5, #0xc8]
	cmp r0, #0x4000
	ble _02023DB0
	mov r1, #0x400
	bl ObjSpdDownSet
	str r0, [r5, #0xc8]
	cmp r0, #0x4000
	movlt r0, #0x4000
	strlt r0, [r5, #0xc8]
	b _02023DB0
_02023D80:
	mov r1, #0x4000
	ldr r0, [r5, #0xc8]
	rsb r1, r1, #0
	cmp r0, r1
	bge _02023DB0
	mov r1, #0x400
	bl ObjSpdDownSet
	mov r1, #0x4000
	rsb r1, r1, #0
	str r0, [r5, #0xc8]
	cmp r0, r1
	strgt r1, [r5, #0xc8]
_02023DB0:
	ldr r0, [r5, #0x4c]
	cmp r0, #0
	beq _02023DE8
	ldrb r0, [r5, #0x6c8]
	cmp r0, #0
	bne _02023DE8
	ldr r0, [r5, #0x24]
	mov r1, #0
	orr r0, r0, #1
	str r0, [r5, #0x24]
	str r1, [r5, #0x2c]
	ldr r0, [r5, #0x4c]
	str r0, [r5, #0x6f0]
	str r1, [r5, #0x6f4]
_02023DE8:
	ldrb r2, [r5, #0x5d3]
	mov r0, #0x70
	ldr r1, =0x02133B36
	smulbb r0, r2, r0
	ldrh r0, [r1, r0]
	ldr r1, [r5, #0x48]
	cmp r0, r1, asr #12
	movge r0, #0
	strgeh r0, [r5, #0x34]
	bge _02023E2C
	tst r4, #0x40
	beq _02023E2C
	ldrsh r0, [r5, #0x34]
	ldr r1, [sp]
	mov r2, #0x1800
	bl ObjSpdUpSet
	strh r0, [r5, #0x34]
_02023E2C:
	tst r4, #0x80
	beq _02023E4C
	ldrsh r0, [r5, #0x34]
	mov r1, r11
	mov r2, #0x1800
	bl ObjSpdUpSet
	strh r0, [r5, #0x34]
	b _02023E68
_02023E4C:
	tst r4, #0x40
	bne _02023E68
	ldrh r0, [r5, #0x34]
	mov r1, #0
	mov r2, #0x200
	bl ObjRoopMove16
	strh r0, [r5, #0x34]
_02023E68:
	ldr r0, [r5, #0x5d8]
	tst r0, #0x4000000
	ldmneia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
	ldr r0, =playerGameStatus
	ldr r0, [r0, #0xc]
	tst r0, #7
	ldmneia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
	ldr r0, [r5, #0x20]
	mov r2, #0x2000
	tst r0, #1
	mov r1, #0x6000
	rsbne r1, r1, #0
	mov r0, r5
	rsb r2, r2, #0
	mov r3, #1
	bl EffectWaterGush__Create
	ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}

// clang-format on
#endif
}

void Player__Func_2023EB4(Player *player)
{
    if (StageTaskStateMatches(&player->objWork, Player__State_2023A4C))
        SetTaskState(&player->objWork, Player__State_2023ED4);
}

NONMATCH_FUNC void Player__State_2023ED4(Player *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r4, r0
	ldr r5, [r4, #0x6d8]
	cmp r5, #0
	beq _02023F1C
	ldr r1, [r5, #0x1c]
	tst r1, #4
	beq _02023F1C
	bl Player__Func_2023FC8
	ldr r0, [r4, #0x20]
	mov r2, #0x3000
	tst r0, #1
	mov r1, #0x2000
	rsbeq r1, r1, #0
	mov r0, r4
	rsb r2, r2, #0
	bl Player__Action_HurtAlt
	ldmia sp!, {r3, r4, r5, pc}
_02023F1C:
	ldr r0, [r4, #0x5d8]
	tst r0, #0x4000000
	bne _02023F58
	mov r0, r4
	bl Player__Func_2023FC8
	mov r1, #0
	mov r0, r4
	sub r2, r1, #0x8000
	bl Player__Gimmick_Jump
	cmp r5, #0
	ldmeqia sp!, {r3, r4, r5, pc}
	mov r0, r4
	mov r1, r5
	bl Player__Action_AllowTrickCombos
	ldmia sp!, {r3, r4, r5, pc}
_02023F58:
	ldr r0, [r4, #0x20]
	mov r1, #0x400
	tst r0, #1
	ldrh r0, [r4, #0x34]
	beq _02023F8C
	rsb r1, r1, #0
	cmp r0, #0x8000
	mov r5, #0x300
	bls _02023FA0
	add r0, r5, #0x300
	mov r0, r0, lsl #0x10
	mov r5, r0, asr #0x10
	b _02023FA0
_02023F8C:
	sub r5, r1, #0x700
	cmp r0, #0x8000
	sublo r0, r5, #0x300
	movlo r0, r0, lsl #0x10
	movlo r5, r0, asr #0x10
_02023FA0:
	ldr r0, [r4, #0xc8]
	mov r2, #0xa000
	bl ObjSpdUpSet
	str r0, [r4, #0xc8]
	ldrsh r0, [r4, #0x34]
	mov r1, r5
	mov r2, #0x4000
	bl ObjSpdUpSet
	strh r0, [r4, #0x34]
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

void Player__Func_2023FC8(Player *player)
{
    player->gimmickObj = NULL;

    player->objWork.displayFlag |= DISPLAY_FLAG_APPLY_CAMERA_CONFIG;
    player->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_DISABLE_SLOPE_ANGLES | STAGE_TASK_MOVE_FLAG_HAS_GRAVITY;
    player->objWork.moveFlag &= ~STAGE_TASK_MOVE_FLAG_DISABLE_COLLIDE_EVENT;
    player->gimmickFlag &= ~(PLAYER_GIMMICK_40 | PLAYER_GIMMICK_10);
    player->playerFlag &= ~(PLAYER_FLAG_2000 | PLAYER_FLAG_DISABLE_TENSION_DRAIN);
    player->gimmickCamOffsetX = 0;
    player->gimmickCamOffsetY = 0;

    ObjRect__SetOnDefend(&player->colliders[0], Player__OnDefend_Regular);
}

void Player__OnDefend_Regular4(OBS_RECT_WORK *rect1, OBS_RECT_WORK *rect2)
{
    Player *player = (Player *)rect2->parent;

    Player__Func_2023FC8(player);
    Player__OnDefend_Regular(rect1, rect2);
}

NONMATCH_FUNC void Player__Func_2024054(Player *player, GameObjectTask *other)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, r7, lr}
	mov r7, r0
	mov r6, r1
	ldr r3, [r7, #0xf4]
	ldr r2, =Player__State_2023A4C
	ldr r4, [r6, #0x340]
	cmp r3, r2
	ldmneia sp!, {r3, r4, r5, r6, r7, pc}
	ldr r1, [r7, #0x24]
	tst r1, #1
	ldmneia sp!, {r3, r4, r5, r6, r7, pc}
	mov r1, #0xc8
	bl Player__GiveScore
	ldrh r0, [r4, #2]
	ldrb r1, [r7, #0x6c9]
	cmp r0, #0xdd
	bne _020240B8
	mov r2, #0x140
	mov r0, r7
	mov r5, r2, asr r1
	bl StarCombo__FinishTrickCombo
	mov r0, r7
	mov r1, r6
	bl Player__Func_2023EB4
	b _02024184
_020240B8:
	mov r2, #0xa0
	mov r0, r7
	mov r5, r2, asr r1
	bl StarCombo__PerformTrick
	ldrh r0, [r4, #2]
	cmp r0, #0xd8
	blo _02024154
	cmp r0, #0xdb
	bhi _02024154
	ldr r0, [r7, #0x24]
	mov r1, #0
	orr r0, r0, #1
	str r0, [r7, #0x24]
	str r1, [r7, #0x2c]
	ldrh r0, [r4, #2]
	sub r0, r0, #0xd8
	cmp r0, #3
	addls pc, pc, r0, lsl #2
	b _02024184
_02024104: // jump table
	b _02024114 // case 0
	b _02024134 // case 1
	b _02024124 // case 2
	b _02024144 // case 3
_02024114:
	str r1, [r7, #0x6f0]
	mov r0, #0x5a000
	str r0, [r7, #0x6f4]
	b _02024184
_02024124:
	str r1, [r7, #0x6f0]
	sub r0, r1, #0x5a000
	str r0, [r7, #0x6f4]
	b _02024184
_02024134:
	mov r0, #0x5a000
	str r0, [r7, #0x6f0]
	str r1, [r7, #0x6f4]
	b _02024184
_02024144:
	sub r0, r1, #0x5a000
	str r0, [r7, #0x6f0]
	str r1, [r7, #0x6f4]
	b _02024184
_02024154:
	ldr r0, [r7, #0x20]
	mov r1, #0x5000
	tst r0, #1
	ldr r0, [r7, #0xc8]
	mov r2, #0x8000
	beq _0202417C
	rsb r1, r1, #0
	bl ObjSpdUpSet
	str r0, [r7, #0xc8]
	b _02024184
_0202417C:
	bl ObjSpdUpSet
	str r0, [r7, #0xc8]
_02024184:
	mov r0, r7
	mov r1, r5
	bl Player__GiveTension
	ldmia sp!, {r3, r4, r5, r6, r7, pc}

// clang-format on
#endif
}

void Player__Action_HoverCrystal(Player *player, GameObjectTask *other, fx32 left, fx32 y, fx32 right)
{
    if (StageTaskStateMatches(&player->objWork, Player__State_HoverCrystal))
    {
        player->gimmickValue1 = left - FLOAT_TO_FX32(1.0);

        if (y < player->gimmickValue2 || player->gimmickValue2 == 0)
            player->gimmickValue2 = y;

        player->gimmickValue3 = right + FLOAT_TO_FX32(1.0);
        player->gimmickObj    = other;
    }
    else
    {
        if ((player->objWork.position.y >= y || (other->objWork.displayFlag & DISPLAY_FLAG_FLIP_Y) != 0)
            && (player->objWork.position.y <= y || (other->objWork.displayFlag & DISPLAY_FLAG_FLIP_Y) == 0))
        {
            Player__InitGimmick(player, FALSE);
            Player__ChangeAction(player, PLAYER_ACTION_39);
            player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;

            if ((player->objWork.moveFlag & STAGE_TASK_MOVE_FLAG_TOUCHING_FLOOR) != 0)
                player->objWork.velocity.x = player->objWork.groundVel;

            fx32 weight = other->mapObject->flags & HOVERCRYSTAL_OBJFLAG_WEIGHT_MASK;
            if (weight != 0)
            {
                player->objWork.velocity.x >>= weight;
                player->objWork.velocity.y >>= weight;
                player->objWork.groundVel >>= weight;
            }
            player->objWork.dir.z = FLOAT_DEG_TO_IDX(0.0);

            player->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_DISABLE_SLOPE_ANGLES | STAGE_TASK_MOVE_FLAG_IN_AIR;
            player->objWork.moveFlag &= ~STAGE_TASK_MOVE_FLAG_HAS_GRAVITY;
            player->objWork.userFlag = 0;

            player->gimmickFlag |= PLAYER_GIMMICK_GRABBED;
            player->gimmickObj    = other;
            player->gimmickValue1 = left - FLOAT_TO_FX32(1.0);
            player->gimmickValue2 = y;
            player->gimmickValue3 = right + FLOAT_TO_FX32(1.0);

            SetTaskState(&player->objWork, Player__State_HoverCrystal);

            PlayPlayerSfx(player, PLAYER_SEQPLAYER_COMMON, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_AIR_SWITCH);
        }
    }
}

void Player__State_HoverCrystal(Player *work)
{
    Player__HandleAirMovement(work);

    if (work->gimmickObj != NULL)
    {
        if ((work->objWork.position.y > work->gimmickValue2 && (work->objWork.displayFlag & DISPLAY_FLAG_FLIP_Y) == 0)
            || (work->objWork.position.y < work->gimmickValue2 && (work->objWork.displayFlag & DISPLAY_FLAG_FLIP_Y) != 0))
        {
            work->objWork.velocity.y = ObjSpdUpSet(work->objWork.velocity.y, -FLOAT_TO_FX32(0.1953125), FLOAT_TO_FX32(4.5));
            work->objWork.userFlag |= 1;
        }
        else
        {
            if (work->objWork.velocity.y < 0)
            {
                if (MATH_ABS(work->objWork.move.y) > FLOAT_TO_FX32(2.0))
                    work->objWork.velocity.y = ObjSpdDownSet(work->objWork.velocity.y, FLOAT_TO_FX32(0.40625));
            }

            work->objWork.velocity.y = ObjSpdUpSet(work->objWork.velocity.y, FLOAT_TO_FX32(0.1953125), FLOAT_TO_FX32(4.5));

            if ((work->objWork.userFlag & 1) != 0)
            {
                work->objWork.userFlag &= ~1;
                PlayPlayerSfx(work, PLAYER_SEQPLAYER_COMMON, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_AIR_SWITCH);
            }
        }

        if (work->objWork.position.x <= work->gimmickValue1 || work->objWork.position.x >= work->gimmickValue3)
            work->gimmickObj = NULL;
    }

    if (work->gimmickObj != NULL)
    {
        work->gimmickValue2 = 0;
    }
    else
    {
        work->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_DISABLE_SLOPE_ANGLES | STAGE_TASK_MOVE_FLAG_HAS_GRAVITY | STAGE_TASK_MOVE_FLAG_IN_AIR;
        work->gimmickFlag &= ~PLAYER_GIMMICK_GRABBED;
        Player__Action_LandOnGround(work, 0);
        work->onLandGround(work);
    }
}

void Player__Action_BalloonRide(Player *player, GameObjectTask *other, s32 a3)
{
    Player__InitPhysics(player);
    Player__InitGimmick(player, FALSE);

    FadeOutPlayerSfx(player, PLAYER_SEQPLAYER_GRINDTRICKSUCCES, 32);
    ReleasePlayerSfx(player, PLAYER_SEQPLAYER_GRINDTRICKSUCCES);
    Player__ChangeAction(player, PLAYER_ACTION_3A);

    player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;
    player->objWork.velocity.x >>= 1;
    player->objWork.velocity.y >>= 2;
    player->objWork.groundVel >>= 1;
    player->objWork.dir.z      = 0;
    player->objWork.position.x = other->objWork.position.x;
    player->objWork.position.y = other->objWork.position.y + FLOAT_TO_FX32(16.0);
    player->objWork.position.z = other->objWork.position.z;
    player->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_DISABLE_SLOPE_ANGLES | STAGE_TASK_MOVE_FLAG_IN_AIR;
    player->objWork.moveFlag &= ~STAGE_TASK_MOVE_FLAG_HAS_GRAVITY;
    player->objWork.displayFlag &= ~DISPLAY_FLAG_FLIP_X;

    player->gimmickObj = other;
    player->gimmickFlag |= PLAYER_GIMMICK_4000000;
    player->gimmickCamGimmickCenterOffsetY = 64;
    player->playerFlag |= PLAYER_FLAG_DISABLE_TENSION_DRAIN;
    player->gimmickValue1 = a3;

    SetTaskState(&player->objWork, Player__State_BalloonRide);
    Player__Action_StopBoost(player);
    Player__Action_StopSuperBoost(player);
    PlayPlayerSfx(player, PLAYER_SEQPLAYER_COMMON, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_GIMMICK);
}

NONMATCH_FUNC void Player__State_BalloonRide(Player *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, lr}
	mov r4, r0
	ldr r0, [r4, #0x6d8]
	cmp r0, #0
	beq _020245DC
	ldr r0, [r0, #0x18]
	tst r0, #0xc
	bne _020245DC
	add r0, r4, #0x700
	ldrh r0, [r0, #0x22]
	tst r0, #3
	beq _02024658
_020245DC:
	mov r1, #0
	str r1, [r4, #0x6d8]
	ldr r2, [r4, #0x5dc]
	add r0, r4, #0x600
	bic r2, r2, #0x4000000
	str r2, [r4, #0x5dc]
	strh r1, [r0, #0xe6]
	ldr r2, [r4, #0x5d8]
	add r0, r4, #0x700
	bic r2, r2, #0x100000
	str r2, [r4, #0x5d8]
	ldr r2, [r4, #0x1c]
	orr r2, r2, #0x90
	orr r2, r2, #0x8000
	str r2, [r4, #0x1c]
	ldrh r0, [r0, #0x22]
	tst r0, #3
	beq _02024640
	str r1, [r4, #0x98]
	str r1, [r4, #0x9c]
	str r1, [r4, #0xc8]
	ldr r1, [r4, #0x5f0]
	mov r0, r4
	blx r1
	ldmia sp!, {r4, pc}
_02024640:
	mov r0, r4
	bl Player__Action_LandOnGround
	ldr r1, [r4, #0x5e4]
	mov r0, r4
	blx r1
	ldmia sp!, {r4, pc}
_02024658:
	ldr r0, [r4, #0x9c]
	ldr r2, [r4, #0x6f0]
	mvn r1, #0xff
	bl ObjSpdUpSet
	str r0, [r4, #0x9c]
	add r0, r4, #0x700
	ldrh r0, [r0, #0x20]
	tst r0, #0x30
	beq _020246D4
	tst r0, #0x10
	ldr r0, [r4, #0x98]
	mov r2, #0x5000
	beq _020246B0
	mov r1, #0x100
	bl ObjSpdUpSet
	str r0, [r4, #0x98]
	ldrsh r0, [r4, #0x34]
	mov r1, #0x40
	mov r2, #0x1000
	bl ObjSpdUpSet
	strh r0, [r4, #0x34]
	ldmia sp!, {r4, pc}
_020246B0:
	mvn r1, #0xff
	bl ObjSpdUpSet
	str r0, [r4, #0x98]
	ldrsh r0, [r4, #0x34]
	mvn r1, #0x3f
	mov r2, #0x1000
	bl ObjSpdUpSet
	strh r0, [r4, #0x34]
	ldmia sp!, {r4, pc}
_020246D4:
	ldr r0, [r4, #0x98]
	mov r1, #0x100
	bl ObjSpdDownSet
	str r0, [r4, #0x98]
	ldrh r0, [r4, #0x34]
	mov r1, #0
	mov r2, #0x20
	bl ObjRoopMove16
	strh r0, [r4, #0x34]
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}

void Player__Action_WaterGun(Player *player, GameObjectTask *other)
{
    Player__InitGimmick(player, FALSE);
    player->gimmickObj = other;
    Player__ChangeAction(player, PLAYER_ACTION_WATERGUN_02);

    player->objWork.groundVel  = 0;
    player->objWork.velocity.x = player->objWork.velocity.y = 0;
    player->objWork.dir.z                                   = FLOAT_DEG_TO_IDX(0.0);
    player->objWork.position.x                              = other->objWork.position.x;
    player->objWork.position.z                              = other->objWork.position.z;

    if ((other->objWork.displayFlag & DISPLAY_FLAG_FLIP_X) != 0)
        player->objWork.position.x += FLOAT_TO_FX32(30.0);
    else
        player->objWork.position.x -= FLOAT_TO_FX32(30.0);

    player->objWork.displayFlag &= ~DISPLAY_FLAG_FLIP_X;
    player->objWork.displayFlag |= other->objWork.displayFlag & DISPLAY_FLAG_FLIP_X;
    player->gimmickFlag |= PLAYER_GIMMICK_GRABBED | PLAYER_GIMMICK_20 | PLAYER_GIMMICK_10;
    player->playerFlag |= PLAYER_FLAG_DISABLE_TENSION_DRAIN;
    player->gimmickCamOffsetY = 32;

    if ((player->objWork.displayFlag & DISPLAY_FLAG_FLIP_X) != 0)
        player->gimmickCamOffsetX = 60;
    else
        player->gimmickCamOffsetX = -60;

    player->colliders[0].defPower = PLAYER_DEFPOWER_INVINCIBLE;
    player->blinkTimer            = 0;
    player->objWork.displayFlag &= ~DISPLAY_FLAG_NO_DRAW;
    SetTaskState(&player->objWork, Player__State_WaterGun);
    PlayPlayerSfx(player, PLAYER_SEQPLAYER_COMMON, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_GIMMICK);
}

NONMATCH_FUNC void Player__State_WaterGun(Player *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, lr}
	mov r4, r0
	ldr r2, [r4, #0x6d8]
	cmp r2, #0
	beq _02024840
	ldr r1, [r2, #0x18]
	tst r1, #0xc
	bne _02024840
	ldr r1, [r2, #0x24]
	tst r1, #1
	beq _02024894
_02024840:
	mov r1, #0
	str r1, [r4, #0x6d8]
	ldr r3, [r4, #0x5dc]
	ldr r0, =0xFFFDFF0F
	add r2, r4, #0x600
	and r0, r3, r0
	str r0, [r4, #0x5dc]
	ldr r0, [r4, #0x5d8]
	add r3, r4, #0x500
	bic r0, r0, #0x100000
	str r0, [r4, #0x5d8]
	strh r1, [r2, #0xdc]
	strh r1, [r2, #0xde]
	mov r2, #0x3f
	mov r0, r4
	strh r2, [r3, #0x3e]
	bl Player__Action_LandOnGround
	ldr r1, [r4, #0x5e4]
	mov r0, r4
	blx r1
	ldmia sp!, {r4, pc}
_02024894:
	tst r1, #2
	add r1, r4, #0x500
	ldrsh r1, [r1, #0xd4]
	beq _020248C0
	cmp r1, #0x3b
	ldmeqia sp!, {r4, pc}
	mov r1, #0x3b
	bl Player__ChangeAction
	mov r0, #0x8000
	str r0, [r4, #4]
	ldmia sp!, {r4, pc}
_020248C0:
	cmp r1, #0x3c
	ldmeqia sp!, {r4, pc}
	mov r1, #0x3c
	bl Player__ChangeAction
	mov r0, #0x8000
	str r0, [r4, #4]
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__Action_Bungee(Player *player, GameObjectTask *other, u32 a3, u32 a4)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #8
	mov r7, r0
	ldr r4, [r7, #0xc8]
	mov r8, r1
	mov r1, #0
	mov r6, r2
	mov r5, r3
	bl Player__InitGimmick
	mov r0, r7
	str r8, [r7, #0x6d8]
	mov r1, #0x3d
	bl Player__ChangeAction
	ldr r1, [r7, #0x20]
	ldr r0, =Player__State_Bungee
	orr r1, r1, #4
	str r1, [r7, #0x20]
	str r0, [r7, #0xf4]
	ldr r0, [r7, #0x1c]
	orr r0, r0, #0x10
	orr r0, r0, #0xc000
	bic r0, r0, #0xc0
	str r0, [r7, #0x1c]
	ldr r0, [r7, #0x5d8]
	orr r0, r0, #0x100000
	str r0, [r7, #0x5d8]
	ldrh r0, [r7, #0x34]
	cmp r0, #0x4000
	cmpne r0, #0xc000
	bne _0202497C
	ldr r0, [r7, #0xc8]
	cmp r0, #0x9000
	movgt r0, #0x9000
	strgt r0, [r7, #0xc8]
	mov r0, #0x9000
	ldr r1, [r7, #0xc8]
	rsb r0, r0, #0
	cmp r1, r0
	strlt r0, [r7, #0xc8]
_0202497C:
	ldrh r0, [r7, #0x34]
	ldr r2, =FX_SinCosTable_
	ldr r1, [r7, #0xc8]
	mov r0, r0, asr #4
	mov r0, r0, lsl #1
	add r0, r0, #1
	mov r0, r0, lsl #1
	ldrsh r0, [r2, r0]
	smull r3, r0, r1, r0
	adds r1, r3, #0x800
	adc r0, r0, #0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #20
	str r1, [r7, #0x98]
	ldrh r0, [r7, #0x34]
	ldr r1, [r7, #0xc8]
	mov r0, r0, asr #4
	mov r0, r0, lsl #2
	ldrsh r0, [r2, r0]
	smull r2, r0, r1, r0
	adds r1, r2, #0x800
	adc r0, r0, #0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #20
	str r1, [r7, #0x9c]
	ldr r0, [r7, #0xc8]
	mov r0, r0, lsl #4
	mov r1, r0, asr #0xc
	mul r0, r1, r1
	mov r0, r0, lsl #1
	str r0, [r7, #0x28]
	cmp r0, #0x8000
	movhi r0, #0x8000
	strhi r0, [r7, #0x28]
	ldrh r0, [r7, #0x34]
	cmp r0, #0x4000
	cmpne r0, #0xc000
	bne _02024A38
	mov r1, #0
	str r1, [r7, #0x6f0]
	ldr r0, [r7, #0x9c]
	rsb r0, r0, #0
	mov r0, r0, asr #4
	str r0, [r7, #0x6f4]
	str r1, [r7, #0x98]
	str r1, [r7, #0xc8]
	b _02024A58
_02024A38:
	ldr r0, [r7, #0x98]
	rsb r0, r0, #0
	mov r0, r0, asr #4
	str r0, [r7, #0x6f0]
	ldr r0, [r7, #0x9c]
	rsb r0, r0, #0
	mov r0, r0, asr #4
	str r0, [r7, #0x6f4]
_02024A58:
	ldrh r0, [r7, #0x34]
	cmp r4, #0
	mov r4, #0
	sublt r0, r0, #0x4000
	addge r0, r0, #0x4000
	strh r0, [r7, #0x34]
	str r6, [r7, #0x6f8]
	str r5, [r7, #0x6fc]
	str r4, [r7, #0x2c]
	sub r1, r4, #1
	str r4, [r7, #0x24]
	add r0, r7, #0x254
	str r4, [sp]
	mov r4, #0x110
	mov r2, r1
	mov r3, r1
	add r0, r0, #0x400
	str r4, [sp, #4]
	bl PlaySfxEx
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void Player__State_Bungee(Player *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r5, r0
	ldr r1, [r5, #0x24]
	cmp r1, #0
	beq _02024ADC
	cmp r1, #1
	beq _02024B94
	cmp r1, #2
	beq _02024BF4
	b _02024C74
_02024ADC:
	ldr r0, [r5, #0x6d8]
	cmp r0, #0
	beq _02024B3C
	ldr r1, [r5, #0x6fc]
	ldr r0, [r5, #0x48]
	ldr r3, [r5, #0x6f8]
	sub r0, r1, r0
	mov r0, r0, asr #0xc
	mul r1, r0, r0
	ldr r2, [r5, #0x44]
	ldr r0, [r5, #0x28]
	sub r2, r3, r2
	mov r2, r2, asr #0xc
	mla r1, r2, r2, r1
	cmp r1, r0
	bls _02024B3C
	mov r0, #8
	str r0, [r5, #0x2c]
	mov r0, #0
	str r0, [r5, #0x98]
	str r0, [r5, #0x9c]
	ldr r0, [r5, #0x24]
	add r0, r0, #1
	str r0, [r5, #0x24]
_02024B3C:
	ldr r0, [r5, #0xbc]
	cmp r0, #0
	ldreq r0, [r5, #0xc0]
	cmpeq r0, #0
	bne _02024C74
	ldr r0, [r5, #0x5e4]
	cmp r0, #0
	beq _02024C74
	mov r0, #0
	strh r0, [r5, #0x34]
	str r0, [r5, #0x6d8]
	ldr r1, [r5, #0x1c]
	mov r0, r5
	orr r1, r1, #0xc0
	bic r1, r1, #0xc000
	str r1, [r5, #0x1c]
	ldr r1, [r5, #0x5d8]
	bic r1, r1, #0x100000
	str r1, [r5, #0x5d8]
	ldr r1, [r5, #0x5e4]
	blx r1
	ldmia sp!, {r3, r4, r5, pc}
_02024B94:
	ldr r0, [r5, #0x2c]
	mov r0, r0, lsl #1
	add r0, r0, #8
	and r0, r0, #7
	sub r0, r0, #4
	mov r0, r0, lsl #0xc
	str r0, [r5, #0x50]
	ldr r0, [r5, #0x2c]
	mov r0, r0, lsl #1
	add r0, r0, #8
	and r0, r0, #7
	sub r0, r0, #4
	mov r0, r0, lsl #0xc
	str r0, [r5, #0x54]
	ldr r0, [r5, #0x2c]
	subs r0, r0, #1
	str r0, [r5, #0x2c]
	bne _02024C74
	mov r0, #0x1c
	str r0, [r5, #0x28]
	ldr r0, [r5, #0x24]
	add r0, r0, #1
	str r0, [r5, #0x24]
	ldmia sp!, {r3, r4, r5, pc}
_02024BF4:
	ldr r1, [r5, #0x28]
	sub r1, r1, #1
	str r1, [r5, #0x28]
	ldr r2, [r5, #0x98]
	ldr r1, [r5, #0x6f0]
	add r1, r2, r1
	str r1, [r5, #0x98]
	ldr r2, [r5, #0x9c]
	ldr r1, [r5, #0x6f4]
	add r1, r2, r1
	str r1, [r5, #0x9c]
	ldr r1, [r5, #0x28]
	cmp r1, #0
	ldmneia sp!, {r3, r4, r5, pc}
	ldr r4, [r5, #0x6d8]
	mov r1, #0
	strh r1, [r5, #0x34]
	str r1, [r5, #0x6d8]
	ldr r1, [r5, #0x1c]
	orr r1, r1, #0xc0
	bic r1, r1, #0xc000
	str r1, [r5, #0x1c]
	ldr r1, [r5, #0x5d8]
	bic r1, r1, #0x100000
	str r1, [r5, #0x5d8]
	ldr r1, [r5, #0x98]
	ldr r2, [r5, #0x9c]
	bl Player__Action_Spring
	mov r0, r5
	mov r1, r4
	bl Player__Action_AllowTrickCombos
	ldmia sp!, {r3, r4, r5, pc}
_02024C74:
	add r0, r5, #0x700
	ldrh r0, [r0, #0x22]
	tst r0, #3
	ldrne r0, [r5, #0x5f0]
	cmpne r0, #0
	ldmeqia sp!, {r3, r4, r5, pc}
	mov r0, #0
	strh r0, [r5, #0x34]
	str r0, [r5, #0x6d8]
	ldr r1, [r5, #0x1c]
	mov r0, r5
	orr r1, r1, #0xc0
	bic r1, r1, #0xc000
	str r1, [r5, #0x1c]
	ldr r1, [r5, #0x5d8]
	bic r1, r1, #0x100000
	str r1, [r5, #0x5d8]
	ldr r1, [r5, #0x5f0]
	blx r1
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

void Player__Action_SpringRope(Player *player, GameObjectTask *other, s32 timer)
{
    Player__InitState(player);
    player->gimmickObj = other;

    Player__ChangeAction(player, PLAYER_ACTION_33);
    player->objWork.displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;
    SetTaskState(&player->objWork, Player__State_SpringRope);

    player->objWork.flag |= STAGE_TASK_FLAG_NO_OBJ_COLLISION;
    player->objWork.moveFlag |= STAGE_TASK_MOVE_FLAG_DISABLE_MOVE_EVENT | STAGE_TASK_MOVE_FLAG_DISABLE_COLLIDE_EVENT | STAGE_TASK_MOVE_FLAG_IN_AIR;
    player->objWork.displayFlag &= ~(DISPLAY_FLAG_FLIP_X | DISPLAY_FLAG_APPLY_CAMERA_CONFIG);

    player->playerFlag |= PLAYER_FLAG_DISABLE_TENSION_DRAIN | PLAYER_FLAG_2000;
    player->gimmickFlag |= PLAYER_GIMMICK_GRABBED | PLAYER_GIMMICK_20 | PLAYER_GIMMICK_10;

    player->gimmickCamOffsetX = player->gimmickCamOffsetY = 0;
    player->objWork.velocity.x = player->objWork.velocity.y = player->objWork.velocity.z = 0;

    player->objWork.groundVel = FLOAT_TO_FX32(0.375);
    player->objWork.dir.z     = 0;
    player->objWork.userWork  = FLOAT_DEG_TO_IDX(337.5);
    player->gimmickValue2     = 0;
    player->objWork.userTimer = timer;

    PlayPlayerSfx(player, PLAYER_SEQPLAYER_COMMON, SND_ZONE_SEQARC_GAME_SE_SEQ_SE_SPRING);
}

NONMATCH_FUNC void Player__State_SpringRope(Player *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #0x5c
	mov r5, r0
	ldr r0, [r5, #0x6d8]
	cmp r0, #0
	beq _02024DE0
	add r0, r5, #0x700
	ldrh r0, [r0, #0x22]
	tst r0, #3
	beq _02024E4C
_02024DE0:
	mov r1, #0
	str r1, [r5, #0x6d8]
	ldr r0, [r5, #0x18]
	bic r0, r0, #2
	str r0, [r5, #0x18]
	ldr r2, [r5, #0x1c]
	ldr r0, =0xFFEFDFFF
	bic r2, r2, #0x2100
	str r2, [r5, #0x1c]
	ldr r3, [r5, #0x5d8]
	ldr r2, =0xFFFDFFCF
	and r0, r3, r0
	str r0, [r5, #0x5d8]
	ldr r0, [r5, #0x5dc]
	and r0, r0, r2
	str r0, [r5, #0x5dc]
	ldr r2, [r5, #0x20]
	mov r0, r5
	orr r2, r2, #0x200
	str r2, [r5, #0x20]
	strh r1, [r5, #0x34]
	strh r1, [r5, #0x32]
	strh r1, [r5, #0x30]
	ldr r1, [r5, #0x5f0]
	blx r1
	add sp, sp, #0x5c
	ldmia sp!, {r4, r5, pc}
_02024E4C:
	ldr r0, [r5, #0xc8]
	mov r1, #0x60
	mov r2, #0x2800
	ldrh r4, [r5, #0x32]
	bl ObjSpdUpSet
	mov r1, #6
	mul r1, r0, r1
	str r0, [r5, #0xc8]
	ldr r0, [r5, #0x6f4]
	sub r0, r0, r1
	str r0, [r5, #0x6f4]
	mov r0, r0, asr #4
	strh r0, [r5, #0x32]
	ldrh r0, [r5, #0x32]
	cmp r0, r4
	bls _02024EB4
	ldr ip, =0x00000111
	add r0, r5, #0x254
	rsb r1, ip, #0x110
	mov r2, #0
	str r2, [sp]
	mov r2, r1
	mov r3, r1
	add r0, r0, #0x400
	str ip, [sp, #4]
	bl PlaySfxEx
_02024EB4:
	ldrh r0, [r5, #0x32]
	cmp r0, #0x8000
	bhs _02024EF0
	cmp r4, #0x8000
	blo _02024EF0
	ldr r4, =0x00000111
	add r0, r5, #0x254
	rsb r1, r4, #0x110
	mov r2, #0
	str r2, [sp]
	mov r2, r1
	mov r3, r1
	add r0, r0, #0x400
	str r4, [sp, #4]
	bl PlaySfxEx
_02024EF0:
	ldr r1, [r5, #0x2c]
	ldr r0, [r5, #0xc8]
	sub r0, r1, r0
	str r0, [r5, #0x2c]
	ldr r1, [r5, #0x28]
	cmp r1, #0
	beq _02024F30
	ldr r0, =0x0000FFFF
	cmp r1, r0
	bhs _02024F30
	add r1, r1, #0x40
	cmp r1, r0
	str r1, [r5, #0x28]
	movhi r0, #0
	strhi r0, [r5, #0x28]
	b _02024F38
_02024F30:
	mov r0, #0
	str r0, [r5, #0x28]
_02024F38:
	add r0, r5, #0x44
	add r3, r5, #0x8c
	ldmia r0, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	add r0, sp, #0x38
	bl MTX_Identity33_
	ldr r0, [r5, #0x28]
	ldr r2, =FX_SinCosTable_
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, asr #4
	mov r1, r0, lsl #1
	add r0, r1, #1
	mov r1, r1, lsl #1
	mov r0, r0, lsl #1
	ldrsh r1, [r2, r1]
	ldrsh r2, [r2, r0]
	add r0, sp, #0x14
	bl MTX_RotZ33_
	add r0, sp, #0x38
	add r1, sp, #0x14
	mov r2, r0
	bl MTX_Concat33
	ldrh r1, [r5, #0x32]
	ldr r3, =FX_SinCosTable_
	add r0, sp, #0x14
	rsb r1, r1, #0
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	mov r1, r1, asr #4
	mov r2, r1, lsl #1
	mov r1, r2, lsl #1
	add r2, r2, #1
	mov r2, r2, lsl #1
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	blx MTX_RotY33_
	add r0, sp, #0x38
	add r1, sp, #0x14
	mov r2, r0
	bl MTX_Concat33
	ldr r1, [r5, #0x2c]
	mov r0, #0
	str r1, [sp, #8]
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	add r0, sp, #8
	add r1, sp, #0x38
	mov r2, r0
	bl MTX_MultVec33
	ldr r1, [r5, #0x6d8]
	ldr r0, [sp, #8]
	ldr r1, [r1, #0x44]
	sub r0, r1, r0
	str r0, [r5, #0x44]
	ldr r1, [r5, #0x6d8]
	ldr r0, [sp, #0xc]
	ldr r1, [r1, #0x48]
	sub r0, r1, r0
	str r0, [r5, #0x48]
	ldr r1, [r5, #0x6d8]
	ldr r0, [sp, #0x10]
	ldr r1, [r1, #0x4c]
	sub r0, r1, r0
	str r0, [r5, #0x4c]
	ldr r1, [r5, #0x44]
	ldr r0, [r5, #0x8c]
	sub r0, r1, r0
	str r0, [r5, #0xbc]
	ldr r1, [r5, #0x48]
	ldr r0, [r5, #0x90]
	sub r0, r1, r0
	str r0, [r5, #0xc0]
	ldr r1, [r5, #0x4c]
	ldr r0, [r5, #0x94]
	sub r0, r1, r0
	str r0, [r5, #0xc4]
	ldr r0, [r5, #0x2c]
	cmp r0, #0x6000
	addge sp, sp, #0x5c
	ldmgeia sp!, {r4, r5, pc}
	mov r1, #0
	str r1, [r5, #0x6d8]
	ldr r0, [r5, #0x18]
	bic r0, r0, #2
	str r0, [r5, #0x18]
	ldr r2, [r5, #0x1c]
	ldr r0, =0xFFEFDFFF
	bic r2, r2, #0x2100
	str r2, [r5, #0x1c]
	ldr r3, [r5, #0x5d8]
	ldr r2, =0xFFFDFFCF
	and r0, r3, r0
	str r0, [r5, #0x5d8]
	ldr r0, [r5, #0x5dc]
	and r0, r0, r2
	str r0, [r5, #0x5dc]
	ldr r2, [r5, #0x20]
	mov r0, r5
	orr r2, r2, #0x200
	str r2, [r5, #0x20]
	str r1, [r5, #0xc8]
	strh r1, [r5, #0x34]
	strh r1, [r5, #0x32]
	strh r1, [r5, #0x30]
	ldr r1, [r5, #0x5f0]
	blx r1
	add sp, sp, #0x5c
	ldmia sp!, {r4, r5, pc}

// clang-format on
#endif
}
