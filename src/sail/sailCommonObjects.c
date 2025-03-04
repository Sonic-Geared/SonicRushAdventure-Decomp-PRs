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

NOT_DECOMPILED const void *StageTask__shakeOffsetTable;
NOT_DECOMPILED const void *shipShiftUnknown;

NOT_DECOMPILED void EffectSailHit__Create(void);
NOT_DECOMPILED void EffectSailBomb__Create(void);
NOT_DECOMPILED void EffectUnknown2161544__Create(void);
NOT_DECOMPILED void EffectSailWater06__Create(void);
NOT_DECOMPILED void EffectSailBomb__Create(void);
NOT_DECOMPILED void EffectSailGuard__Create(void);
NOT_DECOMPILED void EffectSailUnknown21625C8__Create(void);

// --------------------
// VARIABLES
// --------------------

NOT_DECOMPILED const void *_0218BC58[3];
NOT_DECOMPILED const void *_0218BC64;

NOT_DECOMPILED const char *aSbLandBac;
NOT_DECOMPILED const char *aSbMineBac_0;
NOT_DECOMPILED const char *aSbBomberBac;
NOT_DECOMPILED const char *aSbCloudBac_0;
NOT_DECOMPILED const char *aSbBuoyNsbmd_0;
NOT_DECOMPILED const char *aSbBuoyNsbca;
NOT_DECOMPILED const char *aSbSeagullBac;
NOT_DECOMPILED const char *aSbSeagullNsbmd_0;
NOT_DECOMPILED const char *aSbStoneNsbmd_0;
NOT_DECOMPILED const char *aSbIceNsbmd_0;
NOT_DECOMPILED const char *aSbSubFishNsbmd_0;
NOT_DECOMPILED const char *aSbChaosNsbmd_0;
NOT_DECOMPILED const char *aSbGoalNsbmd_0;
NOT_DECOMPILED const char *aSbGoalNsbca;
NOT_DECOMPILED const char *aSbCldmGoalBac;
NOT_DECOMPILED const char *aSbItemBac;

// --------------------
// FUNCTIONS
// --------------------

NONMATCH_FUNC void SailObject__Func_21646DC(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r5, r0
	ldr r1, [r5, #0x12c]
	mov r4, #0
	cmp r1, #0
	ldreq r0, [r5, #0x130]
	cmpeq r0, #0
	beq _0216472C
	cmp r1, #0
	movne r4, r1
	ldreq r4, [r5, #0x130]
	mov r0, #0x200
	str r0, [r4, #0x18]
	str r0, [r4, #0x1c]
	str r0, [r4, #0x20]
	ldr r1, [r5, #0x20]
	ldr r0, =SailObject__Func_2164F10
	orr r1, r1, #0x100
	str r1, [r5, #0x20]
	str r0, [r5, #0xfc]
_0216472C:
	ldr r0, [r5, #0x134]
	cmp r0, #0
	beq _02164754
	mov r0, #0x80
	str r0, [r5, #0x38]
	str r0, [r5, #0x3c]
	str r0, [r5, #0x40]
	ldr r0, [r5, #0x20]
	orr r0, r0, #0x100
	str r0, [r5, #0x20]
_02164754:
	ldr r0, [r5, #0x24]
	tst r0, #0x10000000
	bne _0216493C
	bl SailManager__GetShipType
	cmp r0, #3
	addls pc, pc, r0, lsl #2
	b _0216493C
_02164770: // jump table
	b _02164780 // case 0
	b _021647C8 // case 1
	b _021648F8 // case 2
	b _02164860 // case 3
_02164780:
	ldr r0, [r5, #0x24]
	tst r0, #0x40000000
	beq _0216493C
	ldr r2, [r4, #0x18]
	mov r0, #0x2e0
	umull ip, r3, r2, r0
	mov r1, #0
	mla r3, r2, r1, r3
	mov r1, r2, asr #0x1f
	adds r2, ip, #0x800
	mla r3, r1, r0, r3
	adc r0, r3, #0
	mov r1, r2, lsr #0xc
	orr r1, r1, r0, lsl #20
	str r1, [r4, #0x18]
	str r1, [r4, #0x1c]
	str r1, [r4, #0x20]
	b _0216493C
_021647C8:
	ldr r0, [r5, #0x24]
	tst r0, #0x20000000
	bne _0216493C
	tst r0, #0x40000000
	bne _0216493C
	tst r0, #0x80000000
	bne _0216493C
	cmp r4, #0
	beq _02164820
	ldr r2, [r4, #0x18]
	mov r0, #0x800
	mov r1, r2, asr #0x1f
	mov r1, r1, lsl #0xe
	adds r3, r0, r2, lsl #14
	orr r1, r1, r2, lsr #18
	adc r0, r1, #0
	mov r1, r3, lsr #0xc
	orr r1, r1, r0, lsl #20
	str r1, [r4, #0x18]
	str r1, [r4, #0x1c]
	str r1, [r4, #0x20]
	b _0216493C
_02164820:
	ldr r0, [r5, #0x134]
	cmp r0, #0
	beq _0216493C
	ldr r2, [r5, #0x38]
	mov r0, #0x800
	mov r1, r2, asr #0x1f
	mov r1, r1, lsl #0xe
	adds r3, r0, r2, lsl #14
	orr r1, r1, r2, lsr #18
	adc r0, r1, #0
	mov r1, r3, lsr #0xc
	orr r1, r1, r0, lsl #20
	str r1, [r5, #0x38]
	str r1, [r5, #0x3c]
	str r1, [r5, #0x40]
	b _0216493C
_02164860:
	ldr r0, [r5, #0x24]
	tst r0, #0x20000000
	bne _0216493C
	tst r0, #0x40000000
	bne _0216493C
	tst r0, #0x80000000
	bne _0216493C
	cmp r4, #0
	beq _021648B8
	ldr r2, [r4, #0x18]
	mov r0, #0x800
	mov r1, r2, asr #0x1f
	mov r1, r1, lsl #0xe
	adds r3, r0, r2, lsl #14
	orr r1, r1, r2, lsr #18
	adc r0, r1, #0
	mov r1, r3, lsr #0xc
	orr r1, r1, r0, lsl #20
	str r1, [r4, #0x18]
	str r1, [r4, #0x1c]
	str r1, [r4, #0x20]
	b _0216493C
_021648B8:
	ldr r0, [r5, #0x134]
	cmp r0, #0
	beq _0216493C
	ldr r2, [r5, #0x38]
	mov r0, #0x800
	mov r1, r2, asr #0x1f
	mov r1, r1, lsl #0xe
	adds r3, r0, r2, lsl #14
	orr r1, r1, r2, lsr #18
	adc r0, r1, #0
	mov r1, r3, lsr #0xc
	orr r1, r1, r0, lsl #20
	str r1, [r5, #0x38]
	str r1, [r5, #0x3c]
	str r1, [r5, #0x40]
	b _0216493C
_021648F8:
	ldr r0, [r5, #0x24]
	tst r0, #0x40000000
	beq _0216493C
	ldr r2, [r4, #0x18]
	mov r0, #0x2e0
	umull ip, r3, r2, r0
	mov r1, #0
	mla r3, r2, r1, r3
	mov r1, r2, asr #0x1f
	adds r2, ip, #0x800
	mla r3, r1, r0, r3
	adc r0, r3, #0
	mov r1, r2, lsr #0xc
	orr r1, r1, r0, lsl #20
	str r1, [r4, #0x18]
	str r1, [r4, #0x1c]
	str r1, [r4, #0x20]
_0216493C:
	mov r0, r5
	mov r1, #0x1000
	bl SailObject__SetAnimSpeed
	ldr r0, =SailObject__DefaultIn
	str r0, [r5, #0xf8]
	ldrh r0, [r5, #0]
	cmp r0, #1
	ldreq r0, =SailObject__DefaultLast
	streq r0, [r5, #0x10c]
	ldrh r0, [r5, #0]
	cmp r0, #1
	bne _021649B0
	ldr r4, [r5, #0x124]
	bl SailManager__GetWork
	ldr r0, [r0, #0x70]
	mov r1, #0x1000
	str r0, [r4, #0x15c]
	ldr r0, =SailObject__ViewCheck_2169B60
	str r1, [r4, #0x124]
	str r0, [r5, #0x110]
	ldr r0, [r5, #0x18]
	ldr r1, =SailObject__Destructor_2169B20
	bic r0, r0, #0x10
	str r0, [r5, #0x18]
	ldr r0, [r5, #0x24]
	orr r0, r0, #0x40
	str r0, [r5, #0x24]
	ldr r0, [r5, #0x120]
	bl SetTaskDestructorEvent
_021649B0:
	mov r0, r5
	mov r1, #0
	bl SailObject__Func_21650B4
	ldr r0, [r5, #0x18]
	orr r0, r0, #0x4000
	str r0, [r5, #0x18]
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__InitFromMapObject(StageTask *work, SailEventManagerObject *mapObject)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, r7, lr}
	mov r7, r0
	mov r6, r1
	ldr r4, [r7, #0x124]
	bl SailManager__GetWork
	ldr r5, [r0, #0x98]
	cmp r6, #0
	ldmeqia sp!, {r3, r4, r5, r6, r7, pc}
	add r0, r6, #0x1c
	add r3, r7, #0x44
	ldmia r0, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	mov r0, #0
	str r0, [r4, #0x164]
	ldr r0, [r6, #0x34]
	tst r0, #0x20000000
	ldmneia sp!, {r3, r4, r5, r6, r7, pc}
	str r7, [r6, #8]
	add r0, r6, #0x10
	add r3, r4, #0x170
	ldmia r0, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	ldrh r2, [r6, #0x2c]
	add r0, r4, #0x100
	mov r1, #0x28
	strh r2, [r0, #0x6c]
	ldrh r2, [r6, #0x2e]
	strh r2, [r0, #0x6e]
	ldrh r2, [r6, #0x2c]
	ldr r0, [r5, #0xc0]
	mla r0, r2, r1, r0
	bl SailVoyageManager__GetVoyageUnknownValue
	ldr r3, [r4, #0x178]
	ldr r2, =0x0007FFFF
	mov r1, r0
	and r0, r3, r2
	bl FX_Div
	ldr r5, [r5, #0xc0]
	mov r1, r0
	ldrh r3, [r6, #0x2c]
	mov r0, #0x28
	add r2, r4, #0x1c
	mla r0, r3, r0, r5
	add r3, r4, #0x24
	bl SailVoyageManager__Func_2158888
	str r6, [r4, #0x164]
	ldmia sp!, {r3, r4, r5, r6, r7, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__SetAnimSpeed(StageTask *work, fx32 speed)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, lr}
	ldr lr, [r0, #0x12c]
	cmp lr, #0
	beq _02164AD4
	mov r2, r1, asr #0x1f
	mov r3, r2, lsl #0xd
	mov r2, #0x800
	adds ip, r2, r1, lsl #13
	orr r3, r3, r1, lsr #19
	adc r2, r3, #0
	mov r3, ip, lsr #0xc
	orr r3, r3, r2, lsl #20
	str r3, [lr, #0x118]
_02164AD4:
	ldr lr, [r0, #0x128]
	cmp lr, #0
	beq _02164B04
	mov r2, r1, asr #0x1f
	mov r3, r2, lsl #0xd
	mov r2, #0x800
	adds ip, r2, r1, lsl #13
	orr r3, r3, r1, lsr #19
	adc r2, r3, #0
	mov r3, ip, lsr #0xc
	orr r3, r3, r2, lsl #20
	str r3, [lr, #0x38]
_02164B04:
	ldr ip, [r0, #0x134]
	cmp ip, #0
	ldmeqia sp!, {r3, pc}
	mov r0, r1, asr #0x1f
	mov r2, r0, lsl #0xd
	mov r0, #0x800
	adds r3, r0, r1, lsl #13
	orr r2, r2, r1, lsr #19
	adc r0, r2, #0
	mov r1, r3, lsr #0xc
	orr r1, r1, r0, lsl #20
	str r1, [ip, #0xc8]
	ldmia sp!, {r3, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__Func_2164B38(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	sub sp, sp, #0x30
	mov r5, r0
	ldr r4, [r5, #0x11c]
	ldr r3, =FX_SinCosTable_
	ldrh lr, [r4, #0x32]
	add r0, sp, #0
	mov r1, lr, asr #4
	mov r2, r1, lsl #1
	add r1, r2, #1
	mov ip, r2, lsl #1
	mov r2, r1, lsl #1
	ldrsh r1, [r3, ip]
	ldrsh r2, [r3, r2]
	strh lr, [r5, #0x32]
	bl MTX_RotY33_
	add r1, sp, #0
	add r2, sp, #0x24
	add r0, r5, #0x68
	bl MTX_MultVec33
	ldr r1, [r4, #0x44]
	ldr r0, [sp, #0x24]
	add r0, r1, r0
	str r0, [r5, #0x44]
	ldr r1, [r4, #0x48]
	ldr r0, [sp, #0x28]
	add r0, r1, r0
	str r0, [r5, #0x48]
	ldr r1, [r4, #0x4c]
	ldr r0, [sp, #0x2c]
	add r0, r1, r0
	str r0, [r5, #0x4c]
	ldr r0, [r5, #0x20]
	bic r1, r0, #0x20
	str r1, [r5, #0x20]
	ldr r0, [r4, #0x20]
	and r0, r0, #0x20
	orr r0, r1, r0
	str r0, [r5, #0x20]
	add sp, sp, #0x30
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__SetupAnimator3D(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #0x24
	mov r5, r0
	ldr r4, [r5, #0x12c]
	cmp r4, #0
	bne _02164C14
	ldr r4, [r5, #0x130]
	cmp r4, #0
	bne _02164C14
	ldr r4, [r5, #0x134]
	cmp r4, #0
	addeq sp, sp, #0x24
	ldmeqia sp!, {r4, r5, pc}
_02164C14:
	add r0, r4, #0x24
	bl MTX_Identity33_
	ldrh r0, [r5, #0x30]
	cmp r0, #0
	beq _02164C68
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, asr #4
	mov r1, r0, lsl #1
	add r0, r1, #1
	ldr r2, =FX_SinCosTable_
	mov r1, r1, lsl #1
	mov r0, r0, lsl #1
	ldrsh r1, [r2, r1]
	ldrsh r2, [r2, r0]
	add r0, sp, #0
	bl MTX_RotX33_
	add r0, r4, #0x24
	add r1, sp, #0
	mov r2, r0
	bl MTX_Concat33
_02164C68:
	ldrh r0, [r5, #0x34]
	cmp r0, #0
	beq _02164CB4
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, asr #4
	mov r1, r0, lsl #1
	add r0, r1, #1
	ldr r2, =FX_SinCosTable_
	mov r1, r1, lsl #1
	mov r0, r0, lsl #1
	ldrsh r1, [r2, r1]
	ldrsh r2, [r2, r0]
	add r0, sp, #0
	bl MTX_RotZ33_
	add r0, r4, #0x24
	add r1, sp, #0
	mov r2, r0
	bl MTX_Concat33
_02164CB4:
	ldrh r0, [r5, #0x32]
	cmp r0, #0
	addeq sp, sp, #0x24
	ldmeqia sp!, {r4, r5, pc}
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, asr #4
	mov r1, r0, lsl #1
	add r0, r1, #1
	ldr r2, =FX_SinCosTable_
	mov r1, r1, lsl #1
	mov r0, r0, lsl #1
	ldrsh r1, [r2, r1]
	ldrsh r2, [r2, r0]
	add r0, sp, #0
	bl MTX_RotY33_
	add r0, r4, #0x24
	add r1, sp, #0
	mov r2, r0
	bl MTX_Concat33
	add sp, sp, #0x24
	ldmia sp!, {r4, r5, pc}

// clang-format on
#endif
}

void SailObject__Func_2164D10(StageTask *work, GXRgb color)
{
    if (work->obj_2dIn3d != NULL)
        work->obj_2dIn3d->ani.color = color;
}

NONMATCH_FUNC void SailObject__DefaultIn(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, r7, lr}
	bl GetCurrentTaskWork_
	mov r4, r0
	ldr r0, [r4, #0x24]
	tst r0, #1
	bne _02164D50
	bl SailVoyageManager__GetVoyageUnknownPos
	mov r1, r0
	add r0, r4, #0x44
	mov r2, r0
	bl VEC_Subtract
_02164D50:
	ldr r0, [r4, #0x18]
	tst r0, #0x4000
	beq _02164D6C
	ldr r1, [r4, #4]
	mov r0, r4
	mov r1, r1, asr #0xc
	bl SailObject__ShakeScreen
_02164D6C:
	ldr r0, [r4, #0x24]
	tst r0, #0x40
	beq _02164DD8
	ldr r1, [r4, #0x124]
	cmp r1, #0
	ldmeqia sp!, {r3, r4, r5, r6, r7, pc}
	ldr r0, [r1, #0x15c]
	cmp r0, #0
	beq _02164DA0
	ldr r0, [r0, #0x18]
	tst r0, #4
	movne r0, #0
	strne r0, [r1, #0x15c]
_02164DA0:
	ldr r0, [r1, #0x158]
	cmp r0, #0
	beq _02164DBC
	ldr r0, [r0, #0x18]
	tst r0, #4
	movne r0, #0
	strne r0, [r1, #0x158]
_02164DBC:
	ldr r0, [r1, #0x160]
	cmp r0, #0
	beq _02164DD8
	ldr r0, [r0, #0x18]
	tst r0, #4
	movne r0, #0
	strne r0, [r1, #0x160]
_02164DD8:
	ldrh r0, [r4, #0]
	cmp r0, #1
	ldmneia sp!, {r3, r4, r5, r6, r7, pc}
	bl SailManager__GetWork
	ldr r5, [r4, #0x124]
	ldr r0, [r0, #0x98]
	cmp r5, #0
	ldmeqia sp!, {r3, r4, r5, r6, r7, pc}
	ldr r1, [r5, #0x178]
	ldr r0, [r0, #0x74]
	add r0, r1, r0
	str r0, [r5, #0x178]
	bl SailManager__GetShipType
	cmp r0, #3
	ldmneia sp!, {r3, r4, r5, r6, r7, pc}
	ldr r1, [r4, #0x44]
	ldr r0, [r4, #0x4c]
	cmp r1, #0
	rsblt r1, r1, #0
	cmp r0, #0
	rsblt r0, r0, #0
	cmp r1, r0
	movle r1, r0
	mov r0, #0x1000
	cmp r1, #0x60000
	movgt r0, #0
	bgt _02164E54
	cmp r1, #0x50000
	subgt r0, r1, #0x50000
	rsbgt r0, r0, #0x10000
	movgt r0, r0, asr #4
_02164E54:
	ldr r1, [r4, #0x12c]
	cmp r0, #0x500
	movlt r0, #0x500
	cmp r1, #0
	ldmeqia sp!, {r3, r4, r5, r6, r7, pc}
	mov r1, #0x1f
	umull lr, r6, r0, r1
	mov r3, #0
	mov r2, #0x11
	umull ip, r4, r0, r2
	mov r7, r0, asr #0x1f
	mla r6, r0, r3, r6
	mla r4, r0, r3, r4
	adds r3, lr, #0x800
	mla r6, r7, r1, r6
	adc r1, r6, #0
	mov r6, r3, lsr #0xc
	adds r3, ip, #0x800
	mla r4, r7, r2, r4
	mov r2, r7, lsl #3
	orr r6, r6, r1, lsl #20
	mov r1, r6, lsl #0x10
	mov r6, r1, lsr #0x10
	orr lr, r6, r6, lsl #5
	mov r1, #0x800
	adc r4, r4, #0
	mov ip, r3, lsr #0xc
	adds r3, r1, r0, lsl #3
	orr r2, r2, r0, lsr #29
	orr ip, ip, r4, lsl #20
	mov r0, ip, lsl #0x10
	mov ip, r0, lsr #0x10
	orr r4, ip, ip, lsl #5
	orr lr, lr, r6, lsl #10
	add r1, r5, #0x100
	adc r0, r2, #0
	mov r2, r3, lsr #0xc
	orr r2, r2, r0, lsl #20
	mov r0, r2, lsl #0x10
	mov r2, r0, lsr #0x10
	orr r0, r2, r2, lsl #5
	orr r3, r4, ip, lsl #10
	strh lr, [r1, #0x98]
	strh r3, [r1, #0x9a]
	orr r0, r0, r2, lsl #10
	strh r0, [r1, #0x9c]
	ldmia sp!, {r3, r4, r5, r6, r7, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__Func_2164F10(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	bl GetCurrentTaskWork_
	mov r4, r0
	ldrh r0, [r4, #0]
	ldr r5, [r4, #0x124]
	cmp r0, #0
	beq _02164F40
	cmp r0, #1
	beq _02164F8C
	cmp r0, #2
	beq _02164FD8
	b _0216502C
_02164F40:
	add r0, r5, #0x200
	ldrh r0, [r0, #0x70]
	bl SailObject__Func_2165038
	mov r1, r0
	mov r0, #0
	bl NNS_G3dGlbLightColor
	add r0, r5, #0x200
	ldrh r0, [r0, #0x72]
	bl SailObject__Func_2165038
	mov r1, r0
	mov r0, #1
	bl NNS_G3dGlbLightColor
	add r0, r5, #0x200
	ldrh r0, [r0, #0x74]
	bl SailObject__Func_2165038
	mov r1, r0
	mov r0, #2
	bl NNS_G3dGlbLightColor
	b _0216502C
_02164F8C:
	add r0, r5, #0x100
	ldrh r0, [r0, #0x98]
	bl SailObject__Func_2165038
	mov r1, r0
	mov r0, #0
	bl NNS_G3dGlbLightColor
	add r0, r5, #0x100
	ldrh r0, [r0, #0x9a]
	bl SailObject__Func_2165038
	mov r1, r0
	mov r0, #1
	bl NNS_G3dGlbLightColor
	add r0, r5, #0x100
	ldrh r0, [r0, #0x9c]
	bl SailObject__Func_2165038
	mov r1, r0
	mov r0, #2
	bl NNS_G3dGlbLightColor
	b _0216502C
_02164FD8:
	ldr r0, [r4, #0x24]
	tst r0, #0x400000
	beq _0216502C
	add r0, r5, #0x100
	ldrh r0, [r0, #0x98]
	bl SailObject__Func_2165038
	mov r1, r0
	mov r0, #0
	bl NNS_G3dGlbLightColor
	add r0, r5, #0x100
	ldrh r0, [r0, #0x9a]
	bl SailObject__Func_2165038
	mov r1, r0
	mov r0, #1
	bl NNS_G3dGlbLightColor
	add r0, r5, #0x100
	ldrh r0, [r0, #0x9c]
	bl SailObject__Func_2165038
	mov r1, r0
	mov r0, #2
	bl NNS_G3dGlbLightColor
_0216502C:
	mov r0, r4
	bl StageTask__Draw
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__Func_2165038(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r4, r0
	bl SailManager__GetWork
	mov r3, r4, asr #0xa
	mov r1, r4, asr #5
	ldr r2, [r0, #0x6c]
	and r3, r3, #0x1f
	smull r2, ip, r3, r2
	adds r5, r2, #0x800
	ldr r2, [r0, #0x64]
	and r3, r4, #0x1f
	ldr r0, [r0, #0x68]
	and r1, r1, #0x1f
	smull r2, r4, r3, r2
	adc lr, ip, #0
	adds ip, r2, #0x800
	mov r5, r5, lsr #0xc
	smull r2, r0, r1, r0
	adc r3, r4, #0
	adds r1, r2, #0x800
	mov r2, ip, lsr #0xc
	adc r0, r0, #0
	mov r1, r1, lsr #0xc
	orr r2, r2, r3, lsl #20
	orr r1, r1, r0, lsl #20
	orr r5, r5, lr, lsl #20
	orr r0, r2, r1, lsl #5
	orr r0, r0, r5, lsl #10
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__Func_21650B4(StageTask *work, s32 a2){
#ifdef NON_MATCHING

#else
    // clang-format off
	ldrh r2, [r0, #0]
	ldr r3, [r0, #0x124]
	cmp r2, #0
	beq _021650D8
	cmp r2, #1
	beq _021650F8
	cmp r2, #2
	beq _021650EC
	bx lr
_021650D8:
	add r2, r3, #0x72
	add r0, r3, #0x270
	add r2, r2, #0x200
	add r3, r3, #0x274
	b _0216511C
_021650EC:
	ldr r2, [r0, #0x24]
	tst r2, #0x400000
	bxeq lr
_021650F8:
	ldr r0, [r0, #0x24]
	add r2, r3, #0x9a
	tst r0, #0x8000
	add r0, r3, #0x198
	add r2, r2, #0x100
	add r3, r3, #0x19c
	beq _0216511C
	cmp r1, #0
	moveq r1, #5
_0216511C:
	cmp r1, #5
	addls pc, pc, r1, lsl #2
	b _02165140
_02165128: // jump table
	b _02165140 // case 0
	b _0216515C // case 1
	b _02165170 // case 2
	b _02165184 // case 3
	b _02165198 // case 4
	b _021651AC // case 5
_02165140:
	ldr ip, =0x00007FFF
	ldr r1, =0x00004631
	strh ip, [r0]
	ldr r0, =0x00002108
	strh r1, [r2]
	strh r0, [r3]
	bx lr
_0216515C:
	mov r1, #0x1f
	strh r1, [r0]
	strh r1, [r2]
	strh r1, [r3]
	bx lr
_02165170:
	mov r1, #0x7c00
	strh r1, [r0]
	strh r1, [r2]
	strh r1, [r3]
	bx lr
_02165184:
	ldr r1, =0x000003FF
	strh r1, [r0]
	strh r1, [r2]
	strh r1, [r3]
	bx lr
_02165198:
	ldr r1, =0x00001084
	strh r1, [r0]
	strh r1, [r2]
	strh r1, [r3]
	bx lr
_021651AC:
	ldr ip, =0x00007D4A
	ldr r1, =0x000044C6
	strh ip, [r0]
	ldr r0, =0x00002042
	strh r1, [r2]
	strh r0, [r3]
	bx lr

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__DefaultLast(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, lr}
	bl GetCurrentTaskWork_
	ldr r4, [r0, #0x124]
	add r1, r4, #0x100
	ldrh r2, [r1, #0x30]
	cmp r2, #0
	subne r2, r2, #1
	strneh r2, [r1, #0x30]
	add r1, r4, #0x100
	ldrh r2, [r1, #0x2e]
	cmp r2, #0
	beq _02165240
	sub r2, r2, #1
	strh r2, [r1, #0x2e]
	ldrh r1, [r1, #0x2e]
	tst r1, #2
	beq _02165238
	mov r1, #1
	bl SailObject__Func_21650B4
	b _02165240
_02165238:
	mov r1, #0
	bl SailObject__Func_21650B4
_02165240:
	mov r0, #0
	str r0, [r4, #0x158]
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}

void SailObject__Func_216524C(StageTask *work, void *unknown)
{
    // Nothing to do.
}

NONMATCH_FUNC void SailObject__DefaultOnCheck(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	ldr r3, [r0, #0x3c]
	mov r0, #0
	ldrh r2, [r3, #0]
	mov lr, r0
	mov r4, r0
	mov r5, r0
	cmp r2, #1
	ldr ip, [r1, #0x3c]
	beq _02165284
	cmp r2, #2
	beq _0216528C
	ldmia sp!, {r3, r4, r5, pc}
_02165284:
	add r0, r3, #4
	b _02165290
_0216528C:
	add r4, r3, #4
_02165290:
	ldrh r1, [ip]
	cmp r1, #1
	beq _021652A8
	cmp r1, #2
	beq _021652B0
	b _021652B8
_021652A8:
	add lr, ip, #4
	b _021652C0
_021652B0:
	add r5, ip, #4
	b _021652C0
_021652B8:
	mov r0, #0
	ldmia sp!, {r3, r4, r5, pc}
_021652C0:
	cmp r0, #0
	cmpne lr, #0
	beq _021652D8
	mov r1, lr
	bl SailObject__CheckCollisions
	ldmia sp!, {r3, r4, r5, pc}
_021652D8:
	cmp r0, #0
	cmpne r5, #0
	beq _021652F0
	mov r1, r5
	bl SailObject__Func_2165624
	ldmia sp!, {r3, r4, r5, pc}
_021652F0:
	cmp lr, #0
	cmpne r4, #0
	beq _0216530C
	mov r0, lr
	mov r1, r4
	bl SailObject__Func_2165624
	ldmia sp!, {r3, r4, r5, pc}
_0216530C:
	cmp r4, #0
	mov r0, #0
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__CheckCollisions(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, r7, r8, lr}
	sub sp, sp, #0xc
	mov r5, r0
	mov r4, r1
	ldr r3, [r5, #8]
	ldr r2, [r4, #8]
	ldr r1, [r5, #0]
	ldr r0, [r4, #0]
	sub r2, r3, r2
	subs r1, r1, r0
	rsbmi r1, r1, #0
	cmp r2, #0
	rsblt r2, r2, #0
	cmp r1, r2
	ldr r3, =0x00000F5E
	ldr r6, =0x0000065D
	mov r7, #0
	ble _0216539C
	umull r0, lr, r1, r3
	mla lr, r1, r7, lr
	umull ip, r8, r2, r6
	mov r1, r1, asr #0x1f
	mla lr, r1, r3, lr
	adds r0, r0, #0x800
	adc r3, lr, #0
	adds r1, ip, #0x800
	mov ip, r0, lsr #0xc
	mla r8, r2, r7, r8
	mov r0, r2, asr #0x1f
	mla r8, r0, r6, r8
	adc r0, r8, #0
	mov r1, r1, lsr #0xc
	b _021653D4
_0216539C:
	umull r0, lr, r2, r3
	mla lr, r2, r7, lr
	umull ip, r8, r1, r6
	mov r2, r2, asr #0x1f
	mla lr, r2, r3, lr
	adds r0, r0, #0x800
	adc r3, lr, #0
	adds r2, ip, #0x800
	mov ip, r0, lsr #0xc
	mla r8, r1, r7, r8
	mov r0, r1, asr #0x1f
	mla r8, r0, r6, r8
	adc r0, r8, #0
	mov r1, r2, lsr #0xc
_021653D4:
	orr ip, ip, r3, lsl #20
	orr r1, r1, r0, lsl #20
	add r0, ip, r1
	cmp r0, #0x100000
	addgt sp, sp, #0xc
	movgt r0, #0
	ldmgtia sp!, {r3, r4, r5, r6, r7, r8, pc}
	add r2, sp, #0
	mov r0, r5
	mov r1, r4
	bl VEC_Subtract
	add r0, sp, #0
	mov r1, r0
	bl VEC_DotProduct
	ldr r7, [r4, #0x24]
	ldr r8, [r5, #0x24]
	mov r6, r0
	add r2, r8, r7
	smull r0, r1, r2, r2
	adds r2, r0, #0x800
	mov r0, #0
	adc r1, r1, r0
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #20
	sub r1, r6, r2
	cmp r1, #0
	addgt sp, sp, #0xc
	ldmgtia sp!, {r3, r4, r5, r6, r7, r8, pc}
	ldr r1, [r5, #0x28]
	cmp r1, #0
	ldreq r0, [r4, #0x28]
	cmpeq r0, #0
	beq _021654B8
	ldr r2, [r5, #4]
	ldr r0, [r4, #4]
	cmp r1, #0
	sub r2, r2, r0
	ldr r0, [r4, #0x28]
	moveq r1, r8
	cmp r0, #0
	addne r1, r1, r0
	addeq r1, r1, r7
	smull r0, ip, r2, r2
	adds lr, r0, #0x800
	mov r0, #0
	smull r3, r2, r1, r1
	adc ip, ip, r0
	adds r3, r3, #0x800
	mov lr, lr, lsr #0xc
	adc r1, r2, r0
	mov r2, r3, lsr #0xc
	orr lr, lr, ip, lsl #20
	orr r2, r2, r1, lsl #20
	sub r1, lr, r2
	cmp r1, #0
	addgt sp, sp, #0xc
	ldmgtia sp!, {r3, r4, r5, r6, r7, r8, pc}
_021654B8:
	ldr r0, [r5, #0x2c]
	cmp r0, #0
	ldreq r0, [r4, #0x2c]
	cmpeq r0, #0
	beq _021655BC
	ldr r3, [r4, #0]
	ldr r0, [r5, #0]
	ldr r2, [r4, #8]
	ldr r1, [r5, #8]
	sub r0, r3, r0
	sub r1, r2, r1
	bl FX_Atan2Idx
	ldr r3, [r5, #0x2c]
	cmp r3, #0
	beq _0216553C
	ldrh r1, [r5, #0x30]
	ldr r2, =FX_SinCosTable_
	sub r3, r8, r3
	sub r1, r0, r1
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	mov r1, r1, asr #4
	mov r1, r1, lsl #2
	ldrsh r1, [r2, r1]
	smull r2, r1, r3, r1
	adds r2, r2, #0x800
	adc r1, r1, #0
	mov r2, r2, lsr #0xc
	orrs r2, r2, r1, lsl #20
	rsbmi r2, r2, #0
	sub r8, r8, r2
_0216553C:
	ldr r2, [r4, #0x2c]
	cmp r2, #0
	beq _02165590
	ldrh r3, [r4, #0x30]
	ldr r1, =FX_SinCosTable_
	sub r2, r7, r2
	sub r0, r0, r3
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, asr #4
	mov r0, r0, lsl #2
	ldrsh r0, [r1, r0]
	smull r1, r0, r2, r0
	adds r1, r1, #0x800
	adc r0, r0, #0
	mov r1, r1, lsr #0xc
	orrs r1, r1, r0, lsl #20
	rsbmi r1, r1, #0
	sub r7, r7, r1
_02165590:
	add r2, r8, r7
	smull r0, r1, r2, r2
	adds r2, r0, #0x800
	mov r0, #0
	adc r1, r1, r0
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #20
	sub r1, r6, r2
	cmp r1, #0
	addgt sp, sp, #0xc
	ldmgtia sp!, {r3, r4, r5, r6, r7, r8, pc}
_021655BC:
	mov r0, r5
	mov r1, r4
	add r2, r5, #0x38
	bl VEC_Add
	ldr r0, [r5, #0x38]
	add r1, r5, #0x38
	mov r0, r0, asr #1
	str r0, [r5, #0x38]
	ldr r0, [r5, #0x3c]
	add r3, r4, #0x38
	mov r0, r0, asr #1
	str r0, [r5, #0x3c]
	ldr r0, [r5, #0x40]
	mov r0, r0, asr #1
	str r0, [r5, #0x40]
	ldr r0, [r5, #0x3c]
	rsb r0, r0, #0
	str r0, [r5, #0x3c]
	ldmia r1, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	mov r0, #1
	add sp, sp, #0xc
	ldmia sp!, {r3, r4, r5, r6, r7, r8, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__Func_2165624(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, r7, r8, lr}
	sub sp, sp, #0x24
	mov r6, r0
	mov r5, r1
	ldr r4, [r6, #0x24]
	ldr r3, [r5, #0x48]
	add r2, sp, #0x18
	add r0, r5, #0xc
	add r4, r4, r3
	bl VEC_Subtract
	add r2, sp, #0xc
	mov r0, r6
	mov r1, r5
	bl VEC_Subtract
	add r0, sp, #0xc
	add r1, sp, #0x18
	bl VEC_DotProduct
	movs r7, r0
	addmi sp, sp, #0x24
	movmi r0, #0
	ldmmiia sp!, {r3, r4, r5, r6, r7, r8, pc}
	add r0, sp, #0x18
	mov r1, r0
	bl VEC_DotProduct
	mov r1, r0
	cmp r7, r1
	addgt sp, sp, #0x24
	movgt r0, #0
	ldmgtia sp!, {r3, r4, r5, r6, r7, r8, pc}
	mov r0, r7
	bl FX_Div
	ldr r2, [sp, #0x18]
	ldr r3, [sp, #0x1c]
	smull r2, r8, r0, r2
	adds r2, r2, #0x800
	ldr r1, [sp, #0x20]
	smull r7, lr, r0, r3
	smull ip, r3, r0, r1
	adc r1, r8, #0
	adds r0, r7, #0x800
	adc r7, lr, #0
	mov lr, r0, lsr #0xc
	adds ip, ip, #0x800
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #20
	ldr r8, [sp, #0xc]
	ldr r1, [sp, #0x10]
	orr lr, lr, r7, lsl #20
	sub r7, r1, lr
	sub r2, r8, r2
	adc r3, r3, #0
	mov ip, ip, lsr #0xc
	ldr r1, [sp, #0x14]
	orr ip, ip, r3, lsl #20
	sub r3, r1, ip
	add r0, sp, #0
	mov r1, r0
	str r2, [sp]
	str r7, [sp, #4]
	str r3, [sp, #8]
	bl VEC_DotProduct
	smull r2, r1, r4, r4
	adds r2, r2, #0x800
	adc r1, r1, #0
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #20
	cmp r0, r2
	addgt sp, sp, #0x24
	mov r0, #0
	ldmgtia sp!, {r3, r4, r5, r6, r7, r8, pc}
	add r1, sp, #0
	mov r0, r6
	add r2, r5, #0x5c
	bl VEC_Subtract
	ldr r1, [r5, #0x60]
	add r0, r5, #0x5c
	rsb r1, r1, #0
	str r1, [r5, #0x60]
	add r3, r6, #0x38
	ldmia r0, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	mov r0, #1
	add sp, sp, #0x24
	ldmia sp!, {r3, r4, r5, r6, r7, r8, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__SetupHitbox(StageTask *work, SailColliderWork *userData, s32 id)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, lr}
	mov r5, r1
	mov r1, #0
	mov r6, r0
	mov r4, r2
	mov r3, r1
	bl StageTask__InitCollider
	mov r0, r6
	mov r1, r4
	bl StageTask__GetCollider
	mov r2, #0
	ldr r1, =0x00080004
	str r2, [r0, #0x24]
	str r1, [r0, #0x18]
	ldr r1, =SailObject__DefaultOnCheck
	str r5, [r0, #0x3c]
	str r1, [r0, #0x28]
	cmp r4, #3
	addls pc, pc, r4, lsl #2
	b _021657D4
_021657C4: // jump table
	b _021657D4 // case 0
	b _02165804 // case 1
	b _02165804 // case 2
	b _021657D4 // case 3
_021657D4:
	mov r1, #0
	strh r1, [r0, #0x2c]
	mov r1, #0xa
	strh r1, [r0, #0x2e]
	ldrh r1, [r0, #0x30]
	orr r1, r1, #1
	bic r1, r1, #2
	strh r1, [r0, #0x30]
	ldrh r1, [r0, #0x32]
	bic r1, r1, #1
	strh r1, [r0, #0x32]
	b _02165814
_02165804:
	mov r1, #0xa
	strh r1, [r0, #0x2c]
	mov r1, #0x64
	strh r1, [r0, #0x2e]
_02165814:
	ldrh r1, [r6, #0]
	cmp r1, #0
	beq _02165830
	cmp r1, #1
	beq _0216584C
	cmp r1, #2
	bne _0216584C
_02165830:
	mov r1, #1
	orr r1, r1, #0x200
	strh r1, [r0, #0x34]
	ldr r1, [r0, #0x18]
	orr r1, r1, #0x20
	str r1, [r0, #0x18]
	b _0216588C
_0216584C:
	ldr r2, =0x00000102
	cmp r4, #0
	mov r1, #0x40000
	strh r2, [r0, #0x34]
	str r1, [r5, #0x70]
	cmpne r4, #3
	bne _0216588C
	mov r1, #0xa
	strh r1, [r0, #0x2c]
	mov r2, #5
	ldr r1, =SailObject__OnDefend_2169BAC
	strh r2, [r0, #0x2e]
	str r1, [r0, #0x24]
	ldr r1, [r0, #0x18]
	orr r1, r1, #0x20
	str r1, [r0, #0x18]
_0216588C:
	str r6, [r5, #0x6c]
	ldmia sp!, {r4, r5, r6, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__Func_21658A4(StageTask *work, s32 id)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, lr}
	ldrh r2, [r0, #0]
	cmp r2, #1
	ldmneia sp!, {r3, pc}
	bl StageTask__GetCollider
	ldrh r2, [r0, #0x34]
	mov r1, #8
	orr r2, r2, #0x200
	strh r2, [r0, #0x34]
	strh r1, [r0, #0x2c]
	ldmia sp!, {r3, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__Func_21658D0(StageTask *work, s32 id, s32 a3, VecFx32 *a4)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0xc
	mov r5, r0
	mov r7, r2
	mov r6, r3
	bl StageTask__GetCollider
	ldr r4, [r0, #0x3c]
	mov r0, #1
	strh r0, [r4]
	add ip, r5, #0x44
	add r3, r4, #4
	ldmia ip, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	str r7, [r4, #0x28]
	cmp r6, #0
	str ip, [r4, #0x38]
	addne r3, r4, #0x10
	ldmneia r6, {r0, r1, r2}
	stmneia r3, {r0, r1, r2}
	add r1, sp, #0
	mov r0, r5
	bl SailObject__Func_2165A9C
	ldr r1, [r4, #0x10]
	ldr r0, [sp]
	add r0, r1, r0
	str r0, [r4, #0x10]
	ldr r1, [r4, #0x14]
	ldr r0, [sp, #4]
	sub r0, r1, r0
	str r0, [r4, #0x14]
	ldr r1, [r4, #0x18]
	ldr r0, [sp, #8]
	add r0, r1, r0
	str r0, [r4, #0x18]
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__Func_2165960(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0xc
	mov r7, r0
	mov r6, r2
	mov r5, r3
	bl StageTask__GetCollider
	ldr r4, [r0, #0x3c]
	mov r0, #2
	strh r0, [r4]
	add r3, r4, #0x1c
	ldmia r5, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	ldr ip, [sp, #0x20]
	add r3, r4, #0x28
	ldmia ip, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	mov r0, ip
	mov r1, r5
	add r2, r4, #0x54
	str r6, [r4, #0x4c]
	bl VEC_Subtract
	add r0, r4, #0x54
	mov r1, r0
	bl VEC_Normalize
	add r0, r7, #0x44
	str r0, [r4, #0x50]
	ldr r0, [sp, #0x24]
	cmp r0, #0
	addne r3, r4, #0x40
	ldmneia r0, {r0, r1, r2}
	stmneia r3, {r0, r1, r2}
	add r1, sp, #0
	mov r0, r7
	bl SailObject__Func_2165A9C
	ldr r1, [r4, #0x40]
	ldr r0, [sp]
	add r0, r1, r0
	str r0, [r4, #0x40]
	ldr r1, [r4, #0x44]
	ldr r0, [sp, #4]
	sub r0, r1, r0
	str r0, [r4, #0x44]
	ldr r1, [r4, #0x48]
	ldr r0, [sp, #8]
	add r0, r1, r0
	str r0, [r4, #0x48]
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__ShakeScreen(StageTask *work, s32 timer)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r4, r1
	mov r5, r0
	bl SailManager__GetShipType
	cmp r4, #0
	mov r0, r0, lsl #0x10
	ldmeqia sp!, {r3, r4, r5, pc}
	ldr r2, =StageTask__shakeOffsetTable
	and r1, r4, #0xf
	ldrsb r3, [r2, r1]
	ldr ip, =shipShiftUnknown
	add r1, r4, #1
	and r1, r1, #0xf
	ldrsb r1, [r2, r1]
	ldrb r0, [ip, r0, lsr #16]
	ldr r2, [r5, #0x50]
	mov r3, r3, lsl #0xc
	add r2, r2, r3, asr r0
	str r2, [r5, #0x50]
	ldr r2, [r5, #0x54]
	mov r1, r1, lsl #0xc
	add r1, r2, r1, asr r0
	str r1, [r5, #0x54]
	ldr r1, [r5, #0x18]
	tst r1, #0x20000
	ldreq r1, [r5, #0x58]
	addeq r0, r1, r3, asr r0
	streq r0, [r5, #0x58]
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__Func_2165A9C(StageTask *work, VecFx32 *position){
#ifdef NON_MATCHING

#else
    // clang-format off
	ldrh r2, [r0, #0]
	mov r3, r1
	cmp r2, #0
	beq _02165AB8
	cmp r2, #1
	beq _02165ACC
	b _02165AE0
_02165AB8:
	ldr r0, [r0, #0x124]
	add r0, r0, #4
	ldmia r0, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	bx lr
_02165ACC:
	ldr r0, [r0, #0x124]
	add r0, r0, #4
	ldmia r0, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	bx lr
_02165AE0:
	mov r0, #0
	str r0, [r3]
	str r0, [r3, #4]
	str r0, [r3, #8]
	bx lr

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__Func_2165AF4(StageTask *work, VecFx32 *position){
#ifdef NON_MATCHING

#else
    // clang-format off
	ldrh r2, [r0, #0]
	cmp r2, #0
	beq _02165B0C
	cmp r2, #1
	beq _02165B20
	bx lr
_02165B0C:
	ldr r3, [r0, #0x124]
	ldmia r1, {r0, r1, r2}
	add r3, r3, #4
	stmia r3, {r0, r1, r2}
	bx lr
_02165B20:
	ldr r3, [r0, #0x124]
	ldmia r1, {r0, r1, r2}
	add r3, r3, #4
	stmia r3, {r0, r1, r2}
	bx lr

// clang-format on
#endif
}

NONMATCH_FUNC StageTask *SailLanding__Create(SailEventManagerObject *mapObject)
{
#ifdef NON_MATCHING

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
	bl SailObject__Func_21646DC
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
	ldr r1, =SailObject__Func_216A46C
	ldr r0, =SailObject__Func_216A6A4
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
	ldr r0, =SailObject__Func_216A4E8
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

NONMATCH_FUNC StageTask *SailJetMine__Create(StageTask *work)
{
#ifdef NON_MATCHING

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
	bl SailObject__Func_21646DC
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
	ldr r1, =SailObject__Func_216A9A4
	mov r0, r4
	str r1, [r4, #0xf4]
	add sp, sp, #0xc
	ldmia sp!, {r3, r4, r5, r6, r7, r8, pc}

// clang-format on
#endif
}

NONMATCH_FUNC StageTask *SailJetBomber__Create(StageTask *work)
{
#ifdef NON_MATCHING

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
	bl SailObject__Func_21646DC
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
	bl SailObject__Func_216A9F0
	mov r0, r4
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, r6, r7, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailJetBoatCloud__CreateUnknown(void)
{
#ifdef NON_MATCHING

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

NONMATCH_FUNC StageTask *SailJetBoatCloud__Create(StageTask *work)
{
#ifdef NON_MATCHING

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
	bl SailObject__Func_21646DC
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
	ldr r1, =SailObject__Func_216ABF0
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
#ifdef NON_MATCHING

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
	bl SailObject__Func_21646DC
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
	ldr r1, =SailObject__State_216AF60
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

NONMATCH_FUNC void SailObject__Func_2166728(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, lr}
	sub sp, sp, #0xc
	mov lr, r0
	ldr r4, [lr, #0x124]
	add r3, sp, #0
	ldr r0, [r4, #0x15c]
	add r0, r0, #0x44
	ldmia r0, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	ldr ip, [r4, #0x15c]
	ldrh r0, [ip]
	cmp r0, #0
	beq _0216676C
	cmp r0, #1
	cmpne r0, #2
	beq _02166784
	b _021667A4
_0216676C:
	ldr r1, [ip, #0x124]
	mov r2, r3
	add r0, ip, #0x44
	add r1, r1, #4
	bl VEC_Subtract
	b _021667A4
_02166784:
	ldr r0, [lr, #0x24]
	tst r0, #0x40
	beq _021667A4
	ldr r1, [ip, #0x124]
	add r2, sp, #0
	add r0, ip, #0x44
	add r1, r1, #4
	bl VEC_Subtract
_021667A4:
	add r0, sp, #0
	add r3, r4, #0x10
	ldmia r0, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	add sp, sp, #0xc
	ldmia sp!, {r3, r4, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__Func_21667BC(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, lr}
	sub sp, sp, #0xc
	ldr r4, [r0, #0x124]
	add ip, sp, #0
	ldr r0, [r4, #0x15c]
	add r0, r0, #0x44
	ldmia r0, {r0, r1, r2}
	stmia ip, {r0, r1, r2}
	ldr r3, [r4, #0x15c]
	ldrh r0, [r3, #0]
	cmp r0, #0
	beq _021667F8
	cmp r0, #1
	beq _02166810
	b _02166824
_021667F8:
	ldr r1, [r3, #0x124]
	mov r2, ip
	add r0, r3, #0x44
	add r1, r1, #4
	bl VEC_Subtract
	b _02166824
_02166810:
	ldr r1, [r3, #0x124]
	mov r2, ip
	add r0, r3, #0x44
	add r1, r1, #4
	bl VEC_Subtract
_02166824:
	ldr r0, [sp, #4]
	str r0, [r4, #0x14]
	add sp, sp, #0xc
	ldmia sp!, {r3, r4, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__Func_2166834(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	sub sp, sp, #0x18
	mov r5, r0
	ldr r4, [r5, #0x124]
	add ip, r5, #0x44
	add r3, sp, #0xc
	ldmia ip, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	mov r0, ip
	mov r2, r3
	add r1, r4, #4
	bl VEC_Subtract
	add r0, r4, #0x10
	add r3, sp, #0
	ldmia r0, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	add r1, sp, #0xc
	mov r0, r5
	mov r2, r3
	bl SailObject__Func_216688C
	add sp, sp, #0x18
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__Func_216688C(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #0x54
	ldr r4, [r0, #0x12c]
	ldr r0, =_0218BC58
	add lr, sp, #0x18
	mov r3, r1
	mov r5, r2
	ldmia r0, {r0, r1, r2}
	stmia lr, {r0, r1, r2}
	ldmia r3, {r0, r1, r2}
	add ip, sp, #0xc
	stmia ip, {r0, r1, r2}
	add r3, sp, #0
	ldmia r5, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	mov r1, r3
	ldr r3, [sp, #4]
	mov r0, ip
	ldr ip, [sp, #0x10]
	rsb r3, r3, #0
	rsb ip, ip, #0
	str r3, [sp, #4]
	mov r2, lr
	add r3, sp, #0x24
	str ip, [sp, #0x10]
	bl Unknown2066510__Func_2066A4C
	add r1, r4, #0x24
	add r0, sp, #0x24
	bl MI_Copy36B
	add sp, sp, #0x54
	ldmia sp!, {r4, r5, pc}

// clang-format on
#endif
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
	bl SailVoyageManager__GetVoyageUnknownValue
	ldr r3, [r4, #0x178]
	ldr r2, =0x0007FFFF
	mov r1, r0
	and r0, r3, r2
	bl FX_Div
	mov r7, r0
	mov r0, r5
	mov r1, r7
	bl SailVoyageManager__Func_2158854
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
	bl SailVoyageManager__GetVoyageUnknownValue
	ldr r3, [r5, #0x178]
	ldr r2, =0x0007FFFF
	mov r1, r0
	and r0, r3, r2
	bl FX_Div
	mov r8, r0
	mov r0, r6
	mov r1, r8
	bl SailVoyageManager__Func_2158854
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
	bl SailVoyageManager__GetVoyageUnknownValue
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

NONMATCH_FUNC void SailObject__Func_2166D18(StageTask *work){
#ifdef NON_MATCHING

#else
    // clang-format off
	ldr r2, [r0, #0x2c]
	ldr r1, =_0218BC64
	mov r2, r2, asr #2
	mov r2, r2, lsl #0x1d
	mov r2, r2, lsr #0x1c
	ldrsh r1, [r1, r2]
	ldr r2, [r0, #0x9c]
	add r1, r2, r1
	str r1, [r0, #0x9c]
	ldr r1, [r0, #0x2c]
	add r1, r1, #1
	str r1, [r0, #0x2c]
	bx lr

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__Func_2166D50(StageTask *work){
#ifdef NON_MATCHING

#else
    // clang-format off
	ldr r2, [r0, #0x2c]
	ldr r1, =_0218BC64
	mov r2, r2, asr #2
	mov r2, r2, lsl #0x1d
	mov r2, r2, lsr #0x1c
	ldrsh r1, [r1, r2]
	rsb r1, r1, #0
	mov r1, r1, asr #2
	str r1, [r0, #0x9c]
	ldr r1, [r0, #0x2c]
	add r1, r1, #1
	str r1, [r0, #0x2c]
	bx lr

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__Func_2166D88()
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
	sub sp, sp, #0x30
	ldr r4, =FX_SinCosTable_
	mov r9, #0
	add r5, sp, #0
	add r6, sp, #0x24
	mov r8, #0xf
_02166DA4:
	mov r0, r8
	mov r1, r9
	bl ObjRect__RegistGetNext
	cmp r0, #0
	addeq sp, sp, #0x30
	ldmeqia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
	ldr r1, [r0, #0x18]
	tst r1, #0x800
	bne _02166EF4
	tst r1, #0x80000
	beq _02166EF4
	ldr r7, [r0, #0x3c]
	ldrh r1, [r7, #0]
	cmp r1, #1
	beq _02166DEC
	cmp r1, #2
	beq _02166EAC
	b _02166EF4
_02166DEC:
	add r7, r7, #4
	ldr r1, [r7, #0xc]
	cmp r1, #0
	ldreq r1, [r7, #0x14]
	cmpeq r1, #0
	ldreq r1, [r7, #0x2c]
	cmpeq r1, #0
	beq _02166E1C
	ldr r0, [r0, #0x1c]
	cmp r0, #0
	ldrneh r0, [r0, #0x32]
	strneh r0, [r7, #0x30]
_02166E1C:
	ldr r0, [r7, #0x34]
	add r3, r7, #0xc
	ldmia r0, {r0, r1, r2}
	stmia r7, {r0, r1, r2}
	ldr r0, [r7, #4]
	rsb r0, r0, #0
	str r0, [r7, #4]
	ldmia r3, {r0, r1, r2}
	stmia r6, {r0, r1, r2}
	ldrh r1, [r7, #0x30]
	cmp r1, #0
	beq _02166E98
	ldr r0, [r7, #0xc]
	cmp r0, #0
	ldreq r0, [r7, #0x14]
	cmpeq r0, #0
	beq _02166E98
	mov r0, r1, lsl #0x10
	mov r0, r0, lsr #0x10
	mov r0, r0, asr #4
	mov r0, r0, lsl #1
	mov r1, r0, lsl #1
	add r0, r4, r0, lsl #1
	ldrsh r1, [r4, r1]
	ldrsh r2, [r0, #2]
	mov r0, r5
	bl MTX_RotY33_
	mov r0, r6
	mov r1, r5
	mov r2, r6
	bl MTX_MultVec33
_02166E98:
	mov r0, r7
	mov r1, r6
	mov r2, r7
	bl VEC_Subtract
	b _02166EF4
_02166EAC:
	ldr r0, [r7, #0x50]
	ldmia r0, {r0, r1, r2}
	stmia r6, {r0, r1, r2}
	ldr r1, [sp, #0x28]
	mov r0, r6
	rsb r3, r1, #0
	mov r2, r6
	add r1, r7, #0x40
	str r3, [sp, #0x28]
	bl VEC_Subtract
	mov r1, r6
	add r0, r7, #0x1c
	add r2, r7, #4
	bl VEC_Add
	add r0, r7, #0x28
	add r2, r7, #0x10
	mov r1, r6
	bl VEC_Add
_02166EF4:
	add r0, r9, #1
	mov r0, r0, lsl #0x10
	mov r9, r0, asr #0x10
	b _02166DA4
_02166F04:
    add sp, sp, #0x30
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}

// clang-format on
#endif
}

NONMATCH_FUNC StageTask *SailBuoy__Create(StageTask *work)
{
#ifdef NON_MATCHING

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
	bl SailObject__Func_21646DC
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
	bl SailVoyageManager__GetVoyageUnknownValue
	mov r7, r0
	mov r0, r6
	bl SailVoyageManager__GetVoyageUnknownValue
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
	bl SailVoyageManager__GetVoyageUnknownValue
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
	bl SailVoyageManager__GetVoyageUnknownValue
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
#ifdef NON_MATCHING

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
	bl SailObject__Func_21646DC
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
#ifdef NON_MATCHING

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
	bl SailObject__Func_21646DC
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

NONMATCH_FUNC StageTask *SailSeagull3__Create(SailEventManagerObject *mapObject)
{
#ifdef NON_MATCHING

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
	bl SailObject__Func_21646DC
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
	bl SailVoyageManager__GetVoyageUnknownValue
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
    // https://decomp.me/scratch/aBonY -> 81.61%
#ifdef NON_MATCHING
    StageTask *work;
    SailObject *worker;

    fx32 v2 = FLOAT_TO_FX32(1.0);

    SailManager *manager = SailManager__GetWork();

    if (mapObject->type != SAILMAPOBJECT_26)
    {
        if (manager->voyageManager->segmentList[mapObject->id].field_0 == 1 || manager->voyageManager->segmentList[mapObject->id].field_0 == 8)
        {
            return SailIce__Create(mapObject);
        }
    }

    work = CreateStageTaskSimple();
    StageTask__SetType(work, 1);

    worker = StageTask__AllocateWorker(work, sizeof(SailObject));

    u16 anim;
    if (SailManager__GetShipType() != SHIP_SUBMARINE)
    {
        anim = ObjDispRand() & 1;
    }
    else
    {
        s32 lol  = ObjDispRand();
        s32 lol2 = ObjDispRand();
        anim     = (u16)(lol & 1) + (u16)(lol2 & 1);
    }

    ObjAction3dNNModelLoad(work, NULL, "sb_stone.nsbmd", anim, GetObjectFileWork(OBJDATAWORK_32), SailManager__GetArchive());
    SailObject__Func_21646DC(work);
    SailObject__InitFromMapObject(work, mapObject);
    work->flag |= STAGE_TASK_FLAG_NO_OBJ_COLLISION;
    work->userFlag |= 0x40000;

    fx32 scale_1 = work->scale.x;

    VecFx32 position;
    switch (SailManager__GetShipType())
    {
        default: {
            if ((worker->objectRef->flags & 7) != 0)
                v2 *= (worker->objectRef->flags & 7);

            fx32 scale_2  = MultiplyFX(scale_1, v2);
            work->scale.y = MultiplyFX(scale_2, 0x800 + (u32)(0xFF - (ObjDispRand() & 0x1FE)));

            if (worker->objectRef->type == SAILMAPOBJECT_26)
            {
                s32 s;
                if (anim == 0)
                    s = MultiplyFX(scale_2, 0xA60);
                else
                    s = MultiplyFX(scale_2, 0x9C0);

                work->scale.x = s;
                work->scale.z = s;
                SailObject__SetupHitbox(work, &worker->collider[1], 1);
                SailObject__Func_21658D0(work, 1, MultiplyFX(0x1160, v2), 0);
                worker->collider[1].field_74 |= 0x4000;
                work->colliderList[1]->hitPower = 20;
                work->colliderList[1]->defPower = 0;
                work->flag &= ~STAGE_TASK_FLAG_NO_OBJ_COLLISION;
            }
            else
            {
                work->scale.x = MultiplyFX(scale_2, 0x800 + (u32)((1 - (ObjDispRand() & 0x3FE)) + 0x800));
                work->scale.z = MultiplyFX(scale_2, 0x800 + (u32)((1 - (ObjDispRand() & 0x3FE)) + 0x800));
            }
            break;
        }

        case SHIP_BOAT: {
            if ((worker->objectRef->flags & 7) != 0)
                v2 *= (worker->objectRef->flags & 7);

            if (mapObject->objectValue14)
            {
                v2 = (ObjDispRand() & 0x7FF) + 4096;
            }

            fx32 scale_2 = MultiplyFX(scale_1, v2);

            work->scale.x = MultiplyFX(scale_2, 0x1000 + (0xFF - (ObjDispRand() & 0x1FE)));
            work->scale.y = MultiplyFX(scale_2, 0x1000 + (0xFF - (ObjDispRand() & 0x3FE)));
            work->scale.z = MultiplyFX(scale_2, 0x1000 + (0xFF - (ObjDispRand() & 0x3FE)));

            if (mapObject->objectValue14)
            {
                fx32 value    = 0x1B00 + (0xFF - (ObjDispRand() & 0x3FE));
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

            fx32 value        = MultiplyFX(0x28000, v2);
            worker->field_120 = value;
            worker->field_11C = value;
            worker->dword118  = MultiplyFX(0x12C, v2);
            break;
        }

        case SHIP_HOVER: {
            if ((worker->objectRef->flags & 7) != 0)
                v2 *= (worker->objectRef->flags & 7);

            fx32 scale_2 = MultiplyFX(scale_1, v2);

            work->scale.x = MultiplyFX(scale_2, 0x100 + (u32)((1 - (ObjDispRand() & 0x1FE)) + 0x800));
            work->scale.y = MultiplyFX(scale_2, 0x200 + (u32)((1 - (ObjDispRand() & 0x3FE)) + 0x800));
            work->scale.z = MultiplyFX(scale_2, 0x200 + (u32)((1 - (ObjDispRand() & 0x3FE)) + 0x800));

            if (worker->objectRef->type == SAILMAPOBJECT_26)
            {
                SailObject__SetupHitbox(work, worker->collider, 0);
                SailObject__Func_21658D0(work, 0, MultiplyFX(v2, 0x1000), 0);
                work->flag &= ~STAGE_TASK_FLAG_NO_OBJ_COLLISION;
                worker->collider[0].atkPower = 0x40000;

                OBS_RECT_WORK *collider = StageTask__GetCollider(work, 0);
                collider->defFlag |= 4;
                collider->hitPower = 20;

                fx32 value        = MultiplyFX(0x28000, v2);
                worker->field_120 = value;
                worker->field_11C = value;
                worker->dword118  = MultiplyFX(0x12C, v2);
            }
            break;
        }

        case SHIP_SUBMARINE: {
            work->scale.x = MultiplyFX(scale_1, 0x1000 + (u32)((1 - (ObjDispRand() & 0x3FE)) + 0x800));
            work->scale.y = MultiplyFX(scale_1, 0x800 + (u32)(1 - (ObjDispRand() & 0x7FE)));
            work->scale.z = MultiplyFX(scale_1, 0x1000 + (u32)((1 - (ObjDispRand() & 0x3FE)) + 0x800));

            SailObject__Func_21650B4(work, 5);

            if (mapObject->objectValue14)
            {
                fx32 scale = 0x1B00 + (0xFF - (ObjDispRand() & 0x3FE));

                work->scale.x = MultiplyFX(work->scale.x, scale);
                work->scale.y = MultiplyFX(work->scale.y, scale);
                work->scale.z = MultiplyFX(work->scale.z, scale);

                work->scale.y = MultiplyFX(work->scale.y, 0x1400 + (ObjDispRand() & 0x7FF));
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

    SailObject__SetupAnimator3D(work);
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
	bl SailObject__Func_21646DC
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
	bl SailObject__Func_21650B4
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
	bl SailObject__SetupAnimator3D
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
	bl SailVoyageManager__GetVoyageUnknownValue
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
	bl SailVoyageManager__GetVoyageUnknownValue
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
	bl SailVoyageManager__GetVoyageUnknownValue
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
	bl SailVoyageManager__GetVoyageUnknownValue
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
	bl SailVoyageManager__GetVoyageUnknownValue
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
	bl SailVoyageManager__GetVoyageUnknownValue
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
    StageTask__SetType(work, 1);

    worker = StageTask__AllocateWorker(work, sizeof(SailObject));

    if (SailManager__GetShipType() == SHIP_BOAT)
        radius = 12;

    if (MATH_ABS(mapObject->unknown.x) > radius * _0218B9AC[SailManager__GetShipType()])
    {
        anim = ObjDispRand() & 1;
    }

    ObjAction3dNNModelLoad(work, NULL, "sb_ice.nsbmd", anim, GetObjectFileWork(OBJDATAWORK_33), SailManager__GetArchive());
    SailObject__Func_21646DC(work);
    SailObject__InitFromMapObject(work, mapObject);

    work->flag |= STAGE_TASK_FLAG_NO_OBJ_COLLISION;
    work->userFlag |= 0xC0000;

    scale = work->scale.x;
    if (SailManager__GetShipType() != SHIP_BOAT)
    {
        if (MATH_ABS(mapObject->unknown.x) > 96 * _0218B9AC[SailManager__GetShipType()])
        {
            work->scale.x = MultiplyFX(scale, 0xD00 + (0xFF - (ObjDispRand() & 0x3FE)));
            work->scale.y = MultiplyFX(scale, 0xD00 + (0xFF - (ObjDispRand() & 0x3FE)));
            work->scale.z = MultiplyFX(scale, 0xD00 + (0xFF - (ObjDispRand() & 0x3FE)));
        }
        else
        {
            work->scale.x = MultiplyFX(scale, 0x1100 + (0xFF - (ObjDispRand() & 0x3FE)));
            work->scale.y = MultiplyFX(scale, 0x400);
            work->scale.z = MultiplyFX(scale, 0x1100 + (0xFF - (ObjDispRand() & 0x3FE)));
        }
    }
    else
    {
        work->scale.x = MultiplyFX(scale, 0xB00 + (0xFF - (ObjDispRand() & 0x3FE)));
        work->scale.y = MultiplyFX(scale, 0x580 + (0xFF - (ObjDispRand() & 0x3FE)));
        work->scale.z = MultiplyFX(scale, 0xB00 + (0xFF - (ObjDispRand() & 0x3FE)));

        if (anim == 0)
        {
            work->scale.y = MultiplyFX(scale, 0x800 + (0xFF - (ObjDispRand() & 0x3FE)));
        }
        else
        {
            VecFx32 pos;
            pos.x = 0;
            pos.y = -4096;
            pos.z = 0;

            SailObject__Func_2165AF4(work, &pos);
        }

        SailObject__SetupHitbox(work, worker->collider, 0);
        SailObject__Func_21658A4(work, 0);
        SailObject__Func_21658D0(work, 0, 0x4200, 0);
        work->flag &= ~STAGE_TASK_FLAG_NO_OBJ_COLLISION;
        worker->field_120 = 0x64000;
        worker->field_11C = 0x64000;
        worker->dword118  = 500;
    }

    work->dir.y = ObjDispRand();

    SailObject__SetupAnimator3D(work);
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
	bl SailVoyageManager__GetVoyageUnknownValue
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
	bl SailVoyageManager__GetVoyageUnknownValue
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
	bl SailVoyageManager__GetVoyageUnknownValue
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
	bl SailVoyageManager__GetVoyageUnknownValue
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
    StageTask__SetType(work, 1);

    worker = StageTask__AllocateWorker(work, sizeof(SailObject));
    UNUSED(worker);

    s32 anim = (ObjDispRand() & 7) + (ObjDispRand() & 1);
    ObjAction3dNNModelLoad(work, NULL, "sb_sub_fish.nsbmd", (u16)anim, GetObjectDataWork(OBJDATAWORK_34), SailManager__GetArchive());
    SailObject__Func_21646DC(work);
    SailObject__InitFromMapObject(work, mapObject);
    work->flag |= STAGE_TASK_FLAG_NO_OBJ_COLLISION;

    fx32 scale    = work->scale.x;
    scale         = MultiplyFX(scale, 0x800 + (u32)(0xFF - (ObjDispRand() & 0x1FE)));
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
    StageTask__SetType(work, 1);

    worker = StageTask__AllocateWorker(work, sizeof(SailObject));
    UNUSED(worker);

    s32 anim = (ObjDispRand() & 7) + (ObjDispRand() & 1);
    ObjAction3dNNModelLoad(work, NULL, "sb_sub_fish.nsbmd", (u16)anim, GetObjectDataWork(OBJDATAWORK_34), SailManager__GetArchive());
    SailObject__Func_21646DC(work);
    StageTask__SetParent(work, parent, 0);
    work->flag |= STAGE_TASK_FLAG_DISABLE_VIEWCHECK_EVENT | STAGE_TASK_FLAG_NO_OBJ_COLLISION;
    work->moveFlag |= STAGE_TASK_MOVE_FLAG_DISABLE_MOVE_EVENT;

    OBS_ACTION3D_NN_WORK *animator = work->obj_3d;
    fx32 scale                     = animator->ani.work.scale.x;
    scale                          = MultiplyFX(scale, 0xC00 + (ObjDispRand() & 0x1FF));
    animator->ani.work.scale.z = animator->ani.work.scale.y = animator->ani.work.scale.x = scale;

    SailSubFish2__SetupObject(work);

    return work;
}

void SailSubFish__CreateUnknown1(SailVoyageSegment *voyageSegment)
{
    SailEventManager *eventManager = SailManager__GetWork()->eventManager;

    VecFx32 position = { 0 };

    u16 shipType = SailManager__GetShipType();

    position.x = _0218B9AC[shipType] * (127 - (ObjDispRand() & 0xFE));
    position.y = _0218B9B4[shipType] * (-16 - (ObjDispRand() & 0x3F));
    position.z = voyageSegment->field_24 + SailVoyageManager__GetVoyageUnknownValue(voyageSegment) - ((u16)(2 * ObjDispRand()) * 8);

    if (voyageSegment->field_A > 0)
    {
        position.x = -position.x;
    }

    if (voyageSegment->field_A == 0)
    {
        if ((ObjDispRand() & 1) != 0)
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

    count = (ObjDispRand() & 7) + 2;
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
    StageTask__SetType(work, 2);

    worker = StageTask__AllocateWorker(work, sizeof(SailObject));

    ObjAction3dNNModelLoad(work, NULL, "sb_chaos.nsbmd", manager->rivalRaceID, GetObjectFileWork(OBJDATAWORK_102), SailManager__GetArchive());
    SailObject__Func_21646DC(work);

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
    StageTask__SetType(work, 2);

    worker = StageTask__AllocateWorker(work, sizeof(SailObject));

    ObjAction3dNNModelLoad(work, NULL, "sb_goal.nsbmd", 0, GetObjectFileWork(OBJDATAWORK_46), SailManager__GetArchive());
    ObjAction3dNNMotionLoad(work, NULL, "sb_goal.nsbca", GetObjectFileWork(OBJDATAWORK_47), SailManager__GetArchive());
    AnimatorMDL__SetAnimation(&work->obj_3d->ani, 0, work->obj_3d->resources[B3D_RESOURCE_JOINT_ANIM], 0, 0);
    SailObject__SetAnimSpeed(work, FLOAT_TO_FX32(2.0));
    work->displayFlag |= DISPLAY_FLAG_DISABLE_LOOPING;
    work->obj_3d->ani.work.matrixOpIDs[0] = MATRIX_OP_SET_CAMERA_ROT_33;
    work->obj_3d->ani.work.matrixOpIDs[1] = MATRIX_OP_FLUSH_P_CAMERA3D;

    SailObject__Func_21646DC(work);
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
    StageTask__SetType(work, 2);

    worker = StageTask__AllocateWorker(work, sizeof(SailObject));

    ObjObjectAction3dBACLoad(work, NULL, "/sb_cldm_goal.bac", OBJ_DATA_GFX_AUTO, OBJ_DATA_GFX_AUTO, GetObjectFileWork(OBJDATAWORK_49), SailManager__GetArchive());
    SailObject__Func_21646DC(work);
    work->obj_2dIn3d->ani.work.matrixOpIDs[0] = MATRIX_OP_SET_CAMERA_ROT_33;
    work->obj_2dIn3d->ani.work.matrixOpIDs[1] = MATRIX_OP_FLUSH_P_CAMERA3D;

    SailObject__Func_21646DC(work);
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
    StageTask__SetType(work, 1);

    worker = StageTask__AllocateWorker(work, sizeof(SailObject));

    ObjObjectAction3dBACLoad(work, NULL, "sb_item.bac", OBJ_DATA_GFX_AUTO, OBJ_DATA_GFX_AUTO, GetObjectFileWork(OBJDATAWORK_37), SailManager__GetArchive());
    SailObject__Func_21646DC(work);

    SailObject__InitFromMapObject(work, mapObject);

    work->position.y -= FLOAT_TO_FX32(1.0);
    work->userFlag |= 0x10000;

    work->userWork = mapObject->objectValue10;
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
        worker->collider[0].field_28.x = FLOAT_TO_FX32(2.5);

    SailItem3__Create(work);
    StageTask__InitSeqPlayer(work);

    return work;
}

StageTask *SailItem3__Create(StageTask *parent)
{
    StageTask *work;
    SailObject *worker;

    work = CreateStageTaskSimpleEx(TASK_PRIORITY_UPDATE_LIST_START + 0x1001, TASK_GROUP(1));
    StageTask__SetType(work, 1);

    worker = StageTask__AllocateWorker(work, sizeof(SailObject));
    UNUSED(worker);

    ObjObjectAction3dBACLoad(work, NULL, "sb_item.bac", OBJ_DATA_GFX_AUTO, OBJ_DATA_GFX_AUTO, GetObjectFileWork(OBJDATAWORK_37), SailManager__GetArchive());
    SailObject__Func_21646DC(work);
    work->userFlag |= 1;

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

StageTask *SailItemBonus__Create(StageTask *parent, u16 type)
{
    StageTask *work = CreateStageTaskSimple();
    StageTask__SetType(work, 2);

    ObjObjectAction3dBACLoad(work, NULL, "sb_logo_fix.bac", 1024, 16, GetObjectFileWork(OBJDATAWORK_41), SailManager__GetArchive());
    StageTask__SetAnimation(work, type + 4);
    SailObject__Func_21646DC(work);
    work->userFlag |= 1;
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

NONMATCH_FUNC void SailObject__Destructor_2169B20(Task *task)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r5, r0
	bl GetTaskWork_
	ldr r4, [r0, #0x124]
	add r0, r4, #0x18c
	bl ObjDraw__PaletteTex__Release
	ldr r0, [r4, #0x164]
	cmp r0, #0
	beq _02169B54
	ldr r1, [r0, #0x34]
	tst r1, #0x20000000
	bne _02169B54
	bl SailEventManager__RemoveEntry
_02169B54:
	mov r0, r5
	bl StageTask_Destructor
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__ViewCheck_2169B60(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, lr}
	ldr r1, [r0, #0x18]
	ldr r2, [r0, #0x124]
	tst r1, #0x10
	mov r1, #0
	movne r0, r1
	ldmneia sp!, {r3, pc}
	ldr r3, [r2, #0x164]
	cmp r3, #0
	beq _02169B94
	ldr r2, [r3, #0x34]
	tst r2, #0x40000000
	ldrne r1, [r3, #0x28]
_02169B94:
	add r0, r0, #0x44
	bl SailEventManager__ViewCheck
	cmp r0, #0
	movne r0, #1
	moveq r0, #0
	ldmia sp!, {r3, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__OnDefend_2169BAC(StageTask *work)
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
	bl SailBoatWeaponHUD__Create
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
	bl SailObject__Func_216A168
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
	bl SailObject__Func_216A168
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
	bl SailObject__Func_216B178
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
	bl SailBoatWeaponHUD__Create
	str r0, [r7, #0x168]
_0216A148:
	add r0, r7, #0x100
	mov r1, #4
	strh r1, [r0, #0x2e]
_0216A154:
	mov r0, r9
	mov r1, r8
	bl SailObject__Func_216A1C4
	add sp, sp, #0x24
	ldmia sp!, {r4, r5, r6, r7, r8, r9, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__Func_216A168(StageTask *work){
#ifdef NON_MATCHING

#else
    // clang-format off
	ldr r0, [r0, #0x3c]
	mov r3, #0
	ldr r1, [r0, #0x6c]
	ldrh r0, [r1, #0]
	cmp r0, #0
	ldreq r3, [r1, #0x124]
	beq _0216A19C
	ldr r1, [r1, #0x11c]
	cmp r1, #0
	beq _0216A19C
	ldrh r0, [r1, #0]
	cmp r0, #0
	ldreq r3, [r1, #0x124]
_0216A19C:
	cmp r3, #0
	bxeq lr
	ldr r1, [r3, #0x1a8]
	ldr r0, =0x05F5E0FF
	add r1, r1, r2
	str r1, [r3, #0x1a8]
	cmp r1, r0
	strhi r0, [r3, #0x1a8]
	bx lr

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__Func_216A1C4(StageTask *work)
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

NONMATCH_FUNC void SailObject__Func_216A46C(StageTask *work)
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

NONMATCH_FUNC void SailObject__Func_216A4E8(StageTask *work)
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
	bl SailObject__Func_2165038
	mov r1, r0
	mov r0, r4
	bl SailObject__Func_2164D10
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

NONMATCH_FUNC void SailObject__Func_216A6A4(StageTask *work)
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
	bl SailObject__Func_2165038
	mov r1, r0
	mov r0, r5
	bl SailObject__Func_2164D10
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

NONMATCH_FUNC void SailObject__Func_216A9A4(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, lr}
	mov r1, #0
	mov r4, r0
	bl StageTask__GetCollider
	cmp r0, #0
	ldmeqia sp!, {r4, pc}
	ldr r0, [r0, #0x18]
	tst r0, #0x200
	ldmeqia sp!, {r4, pc}
	ldr r0, [r4, #0x138]
	add r2, r4, #0x44
	mov r1, #0x12
	bl SailAudio__PlaySpatialSequence
	ldr r1, [r4, #0x18]
	add r0, r4, #0x44
	orr r1, r1, #4
	str r1, [r4, #0x18]
	bl EffectSailBomb__Create
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__Func_216A9F0(StageTask *work){
#ifdef NON_MATCHING

#else
    // clang-format off
	ldr r2, =SailObject__State_216AA38
	mov r1, #0x20
	str r2, [r0, #0xf4]
	str r1, [r0, #0x2c]
	sub r1, r1, #0x220
	str r1, [r0, #0x9c]
	ldr r1, [r0, #0x18]
	mov r2, #0x8c
	orr r1, r1, #0x10
	str r1, [r0, #0x18]
	ldr r3, [r0, #0x1c]
	mov r1, #0x280
	orr r3, r3, #0x80
	str r3, [r0, #0x1c]
	str r2, [r0, #0xd8]
	str r1, [r0, #0xdc]
	bx lr

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__State_216AA38(StageTask *work)
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
	bl SailObject__Func_2164D10
	b _0216AB10
_0216AADC:
	ldr r1, =0x00007FFF
	mov r0, r6
	bl SailObject__Func_2164D10
	b _0216AB10
_0216AAEC:
	tst r0, #4
	beq _0216AB04
	mov r0, r6
	mov r1, #0x1f
	bl SailObject__Func_2164D10
	b _0216AB10
_0216AB04:
	ldr r1, =0x00007FFF
	mov r0, r6
	bl SailObject__Func_2164D10
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

NONMATCH_FUNC void SailObject__Func_216ABF0(StageTask *work)
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
	bl SailObject__Func_2165038
	mov r1, r0
	mov r0, r5
	bl SailObject__Func_2164D10
	add sp, sp, #0x40
	ldmia sp!, {r4, r5, r6, r7, r8, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__State_216AF60(StageTask *work)
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
	bl SailObject__Func_2165038
	mov r1, r0
	mov r0, r7
	bl SailObject__Func_2164D10
	ldmia sp!, {r3, r4, r5, r6, r7, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__Func_216B178(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, lr}
	mov r4, r0
	bl SailManager__GetShipType
	cmp r0, #1
	cmpne r0, #3
	mov r0, r4
	beq _0216B19C
	bl SailObject__Func_216B1A4
	ldmia sp!, {r4, pc}
_0216B19C:
	bl SailObject__Func_216B408
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__Func_216B1A4(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, r7, lr}
	ldr r6, =_obj_disp_rand
	ldr r2, [r0, #0x124]
	ldr r1, [r6, #0]
	ldr r4, =0x00196225
	ldr r5, =0x3C6EF35F
	ldr lr, [r2, #0x15c]
	mla r7, r1, r4, r5
	mov r1, r7, lsr #0x10
	mov r3, r1, lsl #0x10
	ldr r1, [lr, #0x124]
	ldr ip, =0x000003FF
	str r7, [r6]
	and r3, ip, r3, lsr #16
	rsb r3, r3, #0x200
	str r3, [r2, #0x138]
	ldr r3, [r6, #0]
	mov lr, #0x200
	mla r7, r3, r4, r5
	mov r3, r7, lsr #0x10
	mov r3, r3, lsl #0x10
	sub ip, ip, #0x200
	rsb lr, lr, #0
	and r3, ip, r3, lsr #16
	str r7, [r6]
	sub r3, lr, r3
	str r3, [r2, #0x13c]
	ldr r3, [r6, #0]
	mov ip, lr, lsr #0x14
	mla r4, r3, r4, r5
	mov r3, r4, lsr #0x10
	mov r3, r3, lsl #0x10
	and r3, ip, r3, lsr #16
	str r4, [r6]
	rsb r3, r3, #0x800
	str r3, [r2, #0x140]
	ldr r3, [r1, #0x10]
	ldr r1, =SailObject__Func_216B284
	add r3, r3, #0x1000
	rsb r3, r3, #0
	str r3, [r2, #0x134]
	str r1, [r0, #0xf4]
	ldr r2, [r0, #0x18]
	mov r1, #0
	orr r2, r2, #0x12
	str r2, [r0, #0x18]
	ldr r2, [r0, #0x24]
	orr r2, r2, #1
	str r2, [r0, #0x24]
	str r1, [r0, #0x2c]
	ldmia sp!, {r3, r4, r5, r6, r7, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__Func_216B284(StageTask *work)
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
	bl SailObject__SetupAnimator3D
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

NONMATCH_FUNC void SailObject__Func_216B408(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r5, r0
	ldr r4, [r5, #0x124]
	ldr r2, =SailObject__Func_216B7A4
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

NONMATCH_FUNC void SailObject__Func_216B4B8(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
	sub sp, sp, #0x18
	mov r4, r0
	ldr r1, [r4, #0x24]
	tst r1, #0x40000
	addeq sp, sp, #0x18
	ldmeqia sp!, {r4, r5, r6, r7, r8, r9, r10, pc}
	mov r3, #0x120
	sub r2, r3, #0x620
	add r1, sp, #0
	str r3, [sp, #0xc]
	str r2, [sp, #0x10]
	str r3, [sp, #0x14]
	bl SailObject__Func_2165A9C
	add r1, sp, #0
	add r0, r4, #0x44
	mov r2, r1
	bl VEC_Subtract
	ldr r0, [r4, #0x24]
	tst r0, #0x1000000
	beq _0216B524
	ldr r1, [sp, #4]
	ldr r0, [sp, #0x10]
	sub r1, r1, #0x1000
	sub r0, r0, #0x300
	str r1, [sp, #4]
	str r0, [sp, #0x10]
_0216B524:
	add r0, sp, #0
	add r1, sp, #0xc
	bl SailRingManager_CreateObjectRing
	ldr r1, [sp, #0xc]
	add r0, sp, #0
	rsb r2, r1, #0
	add r1, sp, #0xc
	str r2, [sp, #0xc]
	bl SailRingManager_CreateObjectRing
	ldr r1, [sp, #0x14]
	add r0, sp, #0
	rsb r2, r1, #0
	add r1, sp, #0xc
	str r2, [sp, #0x14]
	bl SailRingManager_CreateObjectRing
	ldr r1, [sp, #0xc]
	add r0, sp, #0
	rsb r2, r1, #0
	add r1, sp, #0xc
	str r2, [sp, #0xc]
	bl SailRingManager_CreateObjectRing
	ldr r0, [r4, #0x24]
	tst r0, #0x2000000
	addeq sp, sp, #0x18
	ldmeqia sp!, {r4, r5, r6, r7, r8, r9, r10, pc}
	mov r8, #0xa00
	rsb r8, r8, #0
	mov r10, #0
	add r6, r8, #0x300
	mov r9, #0x180
	mov r7, #0x200
	add r5, sp, #0
	add r4, sp, #0xc
_0216B5A8:
	ldr r1, [sp, #4]
	cmp r10, #0
	sub r2, r1, #0x1000
	streq r9, [sp, #0xc]
	streq r8, [sp, #0x10]
	streq r9, [sp, #0x14]
	cmp r10, #1
	streq r7, [sp, #0xc]
	mov r0, r5
	mov r1, r4
	streq r6, [sp, #0x10]
	streq r7, [sp, #0x14]
	str r2, [sp, #4]
	bl SailRingManager_CreateObjectRing
	ldr r1, [sp, #0xc]
	mov r0, r5
	rsb r2, r1, #0
	mov r1, r4
	str r2, [sp, #0xc]
	bl SailRingManager_CreateObjectRing
	ldr r1, [sp, #0x14]
	mov r0, r5
	rsb r2, r1, #0
	mov r1, r4
	str r2, [sp, #0x14]
	bl SailRingManager_CreateObjectRing
	ldr r1, [sp, #0xc]
	mov r0, r5
	rsb r1, r1, #0
	str r1, [sp, #0xc]
	mov r1, r4
	bl SailRingManager_CreateObjectRing
	add r0, r10, #1
	mov r0, r0, lsl #0x10
	mov r10, r0, lsr #0x10
	cmp r10, #2
	blo _0216B5A8
	add sp, sp, #0x18
	ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__Func_216B644(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, lr}
	sub sp, sp, #0x18
	mov r4, r0
	ldr r1, [r4, #0x24]
	tst r1, #0x40000
	addeq sp, sp, #0x18
	ldmeqia sp!, {r4, pc}
	mov r3, #0x2a0
	sub r2, r3, #0x7a0
	add r1, sp, #0
	str r3, [sp, #0xc]
	str r2, [sp, #0x10]
	str r3, [sp, #0x14]
	bl SailObject__Func_2165A9C
	ldr r0, [r4, #0x24]
	tst r0, #0x1000000
	beq _0216B6A0
	ldr r1, [sp, #4]
	ldr r0, [sp, #0x10]
	sub r1, r1, #0x1000
	sub r0, r0, #0x700
	str r1, [sp, #4]
	str r0, [sp, #0x10]
_0216B6A0:
	add r1, sp, #0
	add r0, r4, #0x44
	mov r2, r1
	bl VEC_Subtract
	add r0, sp, #0
	add r1, sp, #0xc
	bl SailRingManager_CreateObjectRing
	ldr r1, [sp, #0xc]
	add r0, sp, #0
	rsb r2, r1, #0
	add r1, sp, #0xc
	str r2, [sp, #0xc]
	bl SailRingManager_CreateObjectRing
	ldr r1, [sp, #0x14]
	add r0, sp, #0
	rsb r2, r1, #0
	add r1, sp, #0xc
	str r2, [sp, #0x14]
	bl SailRingManager_CreateObjectRing
	ldr r1, [sp, #0xc]
	add r0, sp, #0
	rsb r2, r1, #0
	add r1, sp, #0xc
	str r2, [sp, #0xc]
	bl SailRingManager_CreateObjectRing
	mov r2, #0
	sub r1, r2, #0x500
	mov r0, #0x200
	str r2, [sp, #0xc]
	str r1, [sp, #0x10]
	str r0, [sp, #0x14]
	ldr r0, [r4, #0x24]
	tst r0, #0x1000000
	subne r0, r1, #0x500
	strne r0, [sp, #0x10]
	add r0, sp, #0
	add r1, sp, #0xc
	bl SailRingManager_CreateObjectRing
	ldr r1, [sp, #0x14]
	add r0, sp, #0
	rsb r2, r1, #0
	add r1, sp, #0xc
	str r2, [sp, #0x14]
	bl SailRingManager_CreateObjectRing
	mov r2, #0x200
	sub r1, r2, #0x700
	mov r0, #0
	str r2, [sp, #0xc]
	str r1, [sp, #0x10]
	str r0, [sp, #0x14]
	ldr r0, [r4, #0x24]
	tst r0, #0x1000000
	subne r0, r1, #0x500
	strne r0, [sp, #0x10]
	add r0, sp, #0
	add r1, sp, #0xc
	bl SailRingManager_CreateObjectRing
	ldr r1, [sp, #0xc]
	add r0, sp, #0
	rsb r2, r1, #0
	add r1, sp, #0xc
	str r2, [sp, #0xc]
	bl SailRingManager_CreateObjectRing
	add sp, sp, #0x18
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailObject__Func_216B7A4(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, lr}
	sub sp, sp, #0xc
	mov r6, r0
	ldr r4, [r6, #0x124]
	bl SailObject__SetupAnimator3D
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
	bl SailObject__Func_216B4B8
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
	bl SailObject__Func_216B4B8
	b _0216B9E8
_0216B9E4:
	bl SailObject__Func_216B644
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

NONMATCH_FUNC void SailBuoy__SetupObject(StageTask *work){
#ifdef NON_MATCHING

#else
    // clang-format off
	ldr r2, [r0, #0x28]
	ldr r1, [r0, #0x124]
	cmp r2, #1
	beq _0216BA4C
	cmp r2, #2
	mov r2, #0x1f000
	beq _0216BA80
	mov r3, #0xc000
	str r3, [r1, #0x138]
	str r2, [r1, #0x13c]
	str r3, [r1, #0x140]
	mov r3, #0x8000
	str r3, [r1, #0x144]
	mov r2, #0x14000
	str r2, [r1, #0x148]
	str r3, [r1, #0x14c]
	b _0216BAA4
_0216BA4C:
	mov r2, #0x1f000
	str r2, [r1, #0x138]
	mov r2, #0xa000
	str r2, [r1, #0x13c]
	mov r2, #0x5000
	str r2, [r1, #0x140]
	mov r2, #0x7000
	str r2, [r1, #0x144]
	mov r2, #0x2000
	str r2, [r1, #0x148]
	mov r2, #0
	str r2, [r1, #0x14c]
	b _0216BAA4
_0216BA80:
	str r2, [r1, #0x138]
	str r2, [r1, #0x13c]
	str r2, [r1, #0x140]
	mov r2, #0x5000
	str r2, [r1, #0x144]
	mov r2, #0x8000
	str r2, [r1, #0x148]
	mov r2, #0xa000
	str r2, [r1, #0x14c]
_0216BAA4:
	ldr r2, =SailBuoy__State_216BAC0
	mov r1, #0
	str r2, [r0, #0xf4]
	str r1, [r0, #0x2c]
	str r1, [r0, #0x28]
	bx lr

// clang-format on
#endif
}

NONMATCH_FUNC void SailBuoy__State_216BAC0(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, r7, lr}
	mov r6, r0
	ldr r0, [r6, #0x28]
	ldr r5, [r6, #0x124]
	cmp r0, #0
	ldr r0, [r6, #0x2c]
	bne _0216BB04
	add r0, r0, #0x200
	str r0, [r6, #0x2c]
	cmp r0, #0x1000
	blt _0216BB24
	mov r0, #0x1000
	str r0, [r6, #0x2c]
	ldr r0, [r6, #0x28]
	eor r0, r0, #1
	str r0, [r6, #0x28]
	b _0216BB24
_0216BB04:
	subs r0, r0, #0x200
	str r0, [r6, #0x2c]
	bpl _0216BB24
	mov r0, #0
	str r0, [r6, #0x2c]
	ldr r0, [r6, #0x28]
	eor r0, r0, #1
	str r0, [r6, #0x28]
_0216BB24:
	ldr r1, [r6, #0x2c]
	ldr r0, [r5, #0x138]
	mov r2, r1, lsl #0x10
	ldr r1, [r5, #0x144]
	mov r2, r2, lsr #0x10
	bl ObjAlphaSet
	ldr r1, [r6, #0x2c]
	mov r4, r0
	mov r2, r1, lsl #0x10
	ldr r0, [r5, #0x13c]
	ldr r1, [r5, #0x148]
	mov r2, r2, lsr #0x10
	bl ObjAlphaSet
	ldr r1, [r6, #0x2c]
	mov r7, r0
	mov r2, r1, lsl #0x10
	ldr r0, [r5, #0x140]
	ldr r1, [r5, #0x14c]
	mov r2, r2, lsr #0x10
	bl ObjAlphaSet
	mov r1, r7, asr #0xc
	mov r2, r0, asr #0xc
	mov r0, r1, lsl #5
	orr r0, r0, r4, asr #12
	orr r0, r0, r2, lsl #10
	mov r1, r0, lsl #0x10
	ldr r3, [r6, #0x12c]
	mov r2, r1, lsr #0x10
	ldr r0, [r3, #0x94]
	mov r1, #1
	bl NNS_G3dMdlSetMdlEmi
	add r0, r5, #0x100
	ldrh r1, [r0, #0x6e]
	mov r0, r6
	strh r1, [r6, #0x32]
	bl SailObject__SetupAnimator3D
	ldmia sp!, {r3, r4, r5, r6, r7, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailSeagull__SetupObject(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, lr}
	mov r5, r0
	ldr r4, [r5, #0x124]
	bl SailManager__GetWork
	ldr r1, [r0, #0x98]
	ldr r0, [r4, #0x178]
	ldr r1, [r1, #0xc0]
	mov r2, r0, asr #0x13
	mov ip, #0x28
	ldr r0, =SailSeagull__State_216BD1C
	mla r1, r2, ip, r1
	str r0, [r5, #0xf4]
	ldrsh r0, [r1, #0xa]
	cmp r0, #0
	beq _0216BC88
	ldr r3, =_obj_disp_rand
	ldr r0, =0x00196225
	ldr lr, [r3]
	ldr r2, =0x3C6EF35F
	sub r6, ip, #0x68
	mla r2, lr, r0, r2
	str r2, [r3]
	str r6, [r4, #0x180]
	ldrh r0, [r1, #0xa]
	mov ip, r2, lsr #0x10
	ldr r3, =FX_SinCosTable_
	mov r0, r0, asr #4
	mov r6, r0, lsl #2
	ldr r2, =0x000001FF
	mov r0, ip, lsl #0x10
	and r0, r2, r0, lsr #16
	ldrsh r2, [r3, r6]
	add r0, r0, #0x300
	smull r6, r2, r0, r2
	adds r6, r6, #0x800
	adc r2, r2, #0
	mov r6, r6, lsr #0xc
	orr r6, r6, r2, lsl #20
	str r6, [r4, #0x17c]
	ldrh r1, [r1, #0xa]
	mov r1, r1, asr #4
	mov r1, r1, lsl #1
	add r1, r1, #1
	mov r1, r1, lsl #1
	ldrsh r1, [r3, r1]
	smull r2, r1, r0, r1
	adds r2, r2, #0x800
	adc r0, r1, #0
	mov r1, r2, lsr #0xc
	orr r1, r1, r0, lsl #20
	str r1, [r4, #0x184]
	b _0216BCE8
_0216BC88:
	ldr lr, =_mt_math_rand
	ldr r1, =0x000003FE
	ldr r0, [lr]
	ldr r2, =0x00196225
	ldr r3, =0x3C6EF35F
	sub r6, ip, #0x68
	mla ip, r0, r2, r3
	mov r0, ip, lsr #0x10
	mov r0, r0, lsl #0x10
	and r0, r1, r0, lsr #16
	str ip, [lr]
	rsb r0, r0, r1, lsr #1
	str r0, [r4, #0x17c]
	ldr ip, =_obj_disp_rand
	str r6, [r4, #0x180]
	ldr r0, [ip]
	add r1, r1, #1
	mla r2, r0, r2, r3
	mov r0, r2, lsr #0x10
	mov r0, r0, lsl #0x10
	and r0, r1, r0, lsr #16
	str r2, [ip]
	rsb r0, r0, #0
	str r0, [r4, #0x184]
_0216BCE8:
	mov r0, #0x20
	str r0, [r5, #0x2c]
	mov r0, #0
	str r0, [r5, #0x28]
	ldmia sp!, {r4, r5, r6, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailSeagull__State_216BD1C(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r4, r0
	ldr r0, [r4, #0x2c]
	ldr r5, [r4, #0x124]
	sub r0, r0, #1
	str r0, [r4, #0x2c]
	ldr r0, [r4, #0x28]
	cmp r0, #0
	ldr r0, [r5, #0x180]
	beq _0216BD74
	mov r1, #0x10
	mov r2, #0x80
	bl ObjSpdUpSet
	str r0, [r5, #0x180]
	ldr r0, [r4, #0x2c]
	cmp r0, #0
	bge _0216BDA0
	mov r0, #0x20
	str r0, [r4, #0x2c]
	mov r0, #0
	str r0, [r4, #0x28]
	b _0216BDA0
_0216BD74:
	mvn r1, #0xf
	mov r2, #0x40
	bl ObjSpdUpSet
	str r0, [r5, #0x180]
	ldr r0, [r4, #0x2c]
	cmp r0, #0
	bge _0216BDA0
	mov r0, #0x20
	str r0, [r4, #0x2c]
	mov r0, #1
	str r0, [r4, #0x28]
_0216BDA0:
	mov r0, r4
	bl SailObject__Func_2166A2C
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailSeagull2__SetupObject(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r5, r0
	ldr r4, [r5, #0x124]
	bl SailManager__GetWork
	ldr r1, [r0, #0x98]
	ldr r0, [r4, #0x178]
	ldr r1, [r1, #0xc0]
	mov r3, r0, asr #0x13
	mov r0, #0x28
	ldr r2, =SailSeagull2__State_216BF04
	mla r1, r3, r0, r1
	str r2, [r5, #0xf4]
	ldrsh r0, [r1, #0xa]
	cmp r0, #0
	beq _0216BE7C
	ldr r3, =_obj_disp_rand
	ldr r0, =0x00196225
	ldr ip, [r3]
	ldr r2, =0x3C6EF35F
	mov r5, #0x10
	mla r2, ip, r0, r2
	str r2, [r3]
	str r5, [r4, #0x180]
	ldrh r0, [r1, #0xa]
	mov ip, r2, lsr #0x10
	ldr r3, =FX_SinCosTable_
	mov r0, r0, asr #4
	mov r5, r0, lsl #2
	ldr r2, =0x000001FF
	mov r0, ip, lsl #0x10
	and r0, r2, r0, lsr #16
	ldrsh r2, [r3, r5]
	add r0, r0, #0x300
	smull r5, r2, r0, r2
	adds r5, r5, #0x800
	adc r2, r2, #0
	mov r5, r5, lsr #0xc
	orr r5, r5, r2, lsl #20
	str r5, [r4, #0x17c]
	ldrh r1, [r1, #0xa]
	mov r1, r1, asr #4
	mov r1, r1, lsl #1
	add r1, r1, #1
	mov r1, r1, lsl #1
	ldrsh r1, [r3, r1]
	smull r2, r1, r0, r1
	adds r2, r2, #0x800
	adc r0, r1, #0
	mov r1, r2, lsr #0xc
	orr r1, r1, r0, lsl #20
	str r1, [r4, #0x184]
	ldmia sp!, {r3, r4, r5, pc}
_0216BE7C:
	ldr r5, =_mt_math_rand
	ldr r2, =0x00196225
	ldr r0, [r5, #0]
	ldr r3, =0x3C6EF35F
	ldr r1, =0x000001FE
	mla ip, r0, r2, r3
	mov r0, ip, lsr #0x10
	mov r0, r0, lsl #0x10
	and r0, r1, r0, lsr #16
	str ip, [r5]
	rsb r0, r0, #0xff
	str r0, [r4, #0x17c]
	mov r0, #0x10
	ldr r1, =_obj_disp_rand
	str r0, [r4, #0x180]
	ldr r0, [r1, #0]
	mla r2, r0, r2, r3
	mov r0, r2, lsr #0x10
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	and r0, r0, #0x3f
	add r0, r0, #0x80
	str r2, [r1]
	rsb r0, r0, #0
	str r0, [r4, #0x184]
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailSeagull2__State_216BF04(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, lr}
	mov r4, r0
	ldr r1, [r4, #0x124]
	add r1, r1, #0x100
	ldrh r1, [r1, #0x6e]
	strh r1, [r4, #0x32]
	bl SailObject__SetupAnimator3D
	mov r0, r4
	bl SailObject__Func_2166A2C
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailSeagull3__State_216BF2C(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, lr}
	ldr r1, [r0, #0x124]
	ldr r2, =SailSeagull3__State_216C03C
	ldr r5, =_obj_disp_rand
	str r2, [r0, #0xf4]
	ldr r2, [r5, #0]
	ldr lr, =0x00196225
	ldr r4, =0x3C6EF35F
	ldr ip, =0x00003FFE
	mla r3, r2, lr, r4
	mov r2, r3, lsr #0x10
	mov r2, r2, lsl #0x10
	and r2, ip, r2, lsr #16
	rsb r2, r2, ip, lsr #1
	str r3, [r5]
	mov r2, r2, lsl #2
	str r2, [r0, #0x68]
	ldr r2, [r5, #0]
	add r3, ip, #1
	mla r6, r2, lr, r4
	mov r2, r6, lsr #0x10
	str r6, [r5]
	mov r2, r2, lsl #0x10
	and r2, r3, r2, lsr #16
	ldr r3, [r0, #0x6c]
	add r2, r2, #0x6000
	sub r2, r3, r2
	str r2, [r0, #0x6c]
	ldr r2, [r5, #0]
	ldr r3, =0x0000027F
	mla r6, r2, lr, r4
	mov r2, r6, lsr #0x10
	mov r2, r2, lsl #0x10
	and r2, ip, r2, lsr #16
	rsb r2, r2, ip, lsr #1
	str r6, [r5]
	mov r2, r2, lsl #2
	str r2, [r0, #0x70]
	ldr r2, [r5, #0]
	mla ip, r2, lr, r4
	mov r2, ip, lsr #0x10
	mov r2, r2, lsl #0x10
	mov r2, r2, lsr #0x10
	and r2, r2, #0xfe
	str ip, [r5]
	sub r2, r3, r2
	str r2, [r1, #0x134]
	ldr r1, [r5, #0]
	mla r2, r1, lr, r4
	mov r1, r2, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	and r1, r1, #0x1e
	str r2, [r5]
	rsb r1, r1, #0xcf
	str r1, [r0, #0x2c]
	ldr r1, [r5, #0]
	mla r2, r1, lr, r4
	str r2, [r5]
	mov r1, r2, lsr #0x10
	strh r1, [r0, #0x32]
	ldmia sp!, {r4, r5, r6, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailSeagull3__State_216C03C(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, lr}
	mov r5, r0
	ldr r6, [r5, #0x11c]
	ldr r4, [r5, #0x124]
	ldr r0, [r6, #0x124]
	add r3, r5, #0x44
	add r0, r0, #0x10
	ldmia r0, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	ldr r0, [r6, #0x38]
	mov r1, #0x400
	bl FX_Div
	str r0, [r5, #0x38]
	str r0, [r5, #0x3c]
	ldr r0, [r5, #0x38]
	str r0, [r5, #0x40]
	ldr r0, [r6, #0x134]
	ldr r2, [r5, #0x12c]
	ldr r1, [r0, #0xf4]
	ldr r0, [r2, #0x94]
	mov r1, r1, lsl #0xb
	mov r1, r1, lsr #0x1b
	bl NNS_G3dMdlSetMdlAlphaAll
	ldr r1, [r5, #0x28]
	ldr r0, =_0218BC64
	sub r1, r1, #1
	str r1, [r5, #0x28]
	mov r1, r1, lsr #2
	mov r1, r1, lsl #0x1d
	mov r1, r1, lsr #0x1c
	ldrsh r1, [r0, r1]
	ldr ip, =FX_SinCosTable_
	add r0, r5, #0x68
	mov r1, r1, asr #2
	str r1, [r5, #0x9c]
	ldrh r3, [r5, #0x32]
	ldr r2, [r5, #0x2c]
	add r1, r5, #0x98
	add r2, r3, r2
	strh r2, [r5, #0x32]
	ldrh r3, [r5, #0x32]
	ldr lr, [r4, #0x134]
	mov r2, r0
	mov r3, r3, asr #4
	mov r3, r3, lsl #2
	ldrsh r3, [ip, r3]
	smull r6, r3, lr, r3
	adds r6, r6, #0x800
	adc r3, r3, #0
	mov r6, r6, lsr #0xc
	orr r6, r6, r3, lsl #20
	str r6, [r5, #0x98]
	ldrh r3, [r5, #0x32]
	ldr r4, [r4, #0x134]
	mov r3, r3, asr #4
	mov r3, r3, lsl #1
	add r3, r3, #1
	mov r3, r3, lsl #1
	ldrsh r3, [ip, r3]
	smull ip, r3, r4, r3
	adds r4, ip, #0x800
	adc r3, r3, #0
	mov r4, r4, lsr #0xc
	orr r4, r4, r3, lsl #20
	str r4, [r5, #0xa0]
	bl VEC_Add
	add r0, r5, #0x68
	add r3, r5, #0x50
	ldmia r0, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	mov r0, r5
	bl SailObject__SetupAnimator3D
	ldmia sp!, {r4, r5, r6, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailSubFish__SetupObject(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, lr}
	ldr r2, =SailSubFish__State_216C1E8
	mov r1, #0
	str r2, [r0, #0xf4]
	ldr lr, =_obj_disp_rand
	str r1, [r0, #0x2c]
	ldr r1, [lr]
	ldr r2, =0x00196225
	ldr r3, =0x3C6EF35F
	ldr ip, =0x00007FFE
	mla r4, r1, r2, r3
	mov r1, r4, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	and r1, r1, #0x3f
	str r4, [lr]
	add r1, r1, #6
	str r1, [r0, #0x28]
	ldr r1, [lr]
	mla r2, r1, r2, r3
	mov r1, r2, lsr #0x10
	mov r1, r1, lsl #0x10
	and r1, ip, r1, lsr #16
	str r2, [lr]
	rsb r1, r1, ip, lsr #1
	strh r1, [r0, #0x32]
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailSubFish__State_216C1E8(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, lr}
	mov r5, r0
	ldr r0, [r5, #0x28]
	ldr r4, [r5, #0x124]
	subs r0, r0, #1
	str r0, [r5, #0x28]
	moveq r0, #1
	streq r0, [r5, #0x2c]
	ldr r0, [r5, #0x2c]
	cmp r0, #0
	beq _0216C240
	ldrh r0, [r5, #0x32]
	mov r2, #0x200
	cmp r0, #0x8000
	bls _0216C234
	mov r1, #0xc000
	bl ObjRoopMove16
	strh r0, [r5, #0x32]
	b _0216C240
_0216C234:
	mov r1, #0x4000
	bl ObjRoopMove16
	strh r0, [r5, #0x32]
_0216C240:
	ldr r1, [r5, #0x28]
	ldr r0, =_0218BC64
	mov r1, r1, lsr #2
	mov r1, r1, lsl #0x1d
	mov r1, r1, lsr #0x1c
	ldrsh r0, [r0, r1]
	ldr r1, [r4, #0x180]
	ldr ip, =FX_SinCosTable_
	add r0, r1, r0, asr #1
	str r0, [r4, #0x180]
	ldrh r0, [r5, #0x32]
	mov r2, #0
	mov r1, #0xc00
	mov r0, r0, asr #4
	mov r0, r0, lsl #2
	ldrsh r3, [ip, r0]
	mov r0, r5
	umull r6, lr, r3, r1
	mla lr, r3, r2, lr
	mov r3, r3, asr #0x1f
	adds r6, r6, #0x800
	mla lr, r3, r1, lr
	adc r3, lr, #0
	mov r6, r6, lsr #0xc
	orr r6, r6, r3, lsl #20
	str r6, [r4, #0x17c]
	ldrh r3, [r5, #0x32]
	mov r3, r3, asr #4
	mov r3, r3, lsl #1
	add r3, r3, #1
	mov r3, r3, lsl #1
	ldrsh r3, [ip, r3]
	umull lr, ip, r3, r1
	adds lr, lr, #0x800
	mla ip, r3, r2, ip
	mov r2, r3, asr #0x1f
	mla ip, r2, r1, ip
	adc r1, ip, #0
	mov r2, lr, lsr #0xc
	orr r2, r2, r1, lsl #20
	str r2, [r4, #0x184]
	bl SailObject__Func_2166A2C
	ldrh r4, [r5, #0x32]
	mov r0, r5
	rsb r1, r4, #0
	strh r1, [r5, #0x32]
	bl SailObject__SetupAnimator3D
	strh r4, [r5, #0x32]
	ldmia sp!, {r4, r5, r6, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailSubFish2__SetupObject(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, lr}
	ldr r1, =SailSubFish2__State_216C458
	ldr r5, =_obj_disp_rand
	str r1, [r0, #0xf4]
	ldr r1, [r5, #0]
	ldr lr, =0x00196225
	ldr r4, =0x3C6EF35F
	ldr r3, =0x00007FFF
	mla r2, r1, lr, r4
	mov r1, r2, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	str r2, [r5]
	and r1, r1, #0x7f
	str r1, [r0, #0x2c]
	ldr r1, [r5, #0]
	ldr r2, =0x00001FFE
	mla r6, r1, lr, r4
	mov r1, r6, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	and r1, r1, #0x3f
	str r6, [r5]
	add r1, r1, #6
	str r1, [r0, #0x28]
	ldr r1, [r5, #0]
	sub ip, r3, #0x4000
	mla r6, r1, lr, r4
	mov r1, r6, lsr #0x10
	mov r1, r1, lsl #0x10
	and r1, r2, r1, lsr #16
	rsb r1, r1, r2, lsr #1
	str r6, [r5]
	mov r1, r1, lsl #4
	str r1, [r0, #0x68]
	ldr r1, [r5, #0]
	mla r2, r1, lr, r4
	mov r1, r2, lsr #0x10
	str r2, [r5]
	mov r1, r1, lsl #0x10
	and r1, r3, r1, lsr #16
	ldr r2, [r0, #0x6c]
	ldr r3, =0x000007FE
	sub r1, r2, r1
	str r1, [r0, #0x6c]
	ldr r1, [r5, #0]
	mla r2, r1, lr, r4
	mov r1, r2, lsr #0x10
	str r2, [r5]
	mov r1, r1, lsl #0x10
	ldr r2, [r0, #0x70]
	and r1, ip, r1, lsr #16
	sub r1, r2, r1
	str r1, [r0, #0x70]
	ldr r1, [r5, #0]
	mla r2, r1, lr, r4
	mov r1, r2, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	tst r1, #1
	movne r1, #0x4000
	str r2, [r5]
	moveq r1, #0xc000
	strh r1, [r0, #0x32]
	ldr r4, =_obj_disp_rand
	ldr r1, =0x00196225
	ldr r5, [r4, #0]
	ldr r2, =0x3C6EF35F
	mla r2, r5, r1, r2
	mov r1, r2, lsr #0x10
	mov r1, r1, lsl #0x10
	and r1, r3, r1, lsr #16
	str r2, [r4]
	rsb r1, r1, r3, lsr #1
	strh r1, [r0, #0x32]
	ldmia sp!, {r4, r5, r6, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailSubFish2__State_216C458(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, lr}
	mov r5, r0
	ldr r6, [r5, #0x11c]
	ldr r4, [r5, #0x124]
	ldr r0, [r6, #0x124]
	add r3, r5, #0x44
	add r0, r0, #0x10
	ldmia r0, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	ldr r0, [r6, #0x38]
	mov r1, #0x400
	bl FX_Div
	str r0, [r5, #0x38]
	str r0, [r5, #0x3c]
	ldr r0, [r5, #0x38]
	ldr r6, =_0218BC64
	str r0, [r5, #0x40]
	ldr r0, [r5, #0x28]
	ldr lr, =FX_SinCosTable_
	sub r0, r0, #1
	str r0, [r5, #0x28]
	ldr r1, [r5, #0x2c]
	add r0, r5, #0x68
	add r1, r1, #1
	str r1, [r5, #0x2c]
	ldr r2, [r5, #0x28]
	add r1, r5, #0x98
	mov r2, r2, lsr #2
	mov r2, r2, lsl #0x1d
	mov r2, r2, lsr #0x1c
	ldrsh r3, [r6, r2]
	mov r2, r0
	str r3, [r5, #0x9c]
	ldr r3, [r5, #0x2c]
	mov r3, r3, asr #3
	mov r3, r3, lsl #0x1d
	mov r3, r3, lsr #0x1c
	ldrsh r3, [r6, r3]
	mov r3, r3, lsl #1
	str r3, [r4, #0x134]
	ldrh ip, [r5, #0x32]
	mov ip, ip, asr #4
	mov ip, ip, lsl #1
	add ip, ip, #1
	mov ip, ip, lsl #1
	ldrsh ip, [lr, ip]
	smull r6, ip, r3, ip
	adds r6, r6, #0x800
	adc r3, ip, #0
	mov r6, r6, lsr #0xc
	orr r6, r6, r3, lsl #20
	str r6, [r5, #0x98]
	ldrh r3, [r5, #0x32]
	ldr r4, [r4, #0x134]
	mov r3, r3, asr #4
	mov r3, r3, lsl #2
	ldrsh r3, [lr, r3]
	smull ip, r3, r4, r3
	adds r4, ip, #0x800
	adc r3, r3, #0
	mov r4, r4, lsr #0xc
	orr r4, r4, r3, lsl #20
	str r4, [r5, #0xa0]
	bl VEC_Add
	add r0, r5, #0x68
	add r3, r5, #0x50
	ldmia r0, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	mov r0, r5
	bl SailObject__SetupAnimator3D
	ldmia sp!, {r4, r5, r6, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailChaosEmerald__SetupObject(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r5, r0
	ldr r4, [r5, #0x124]
	bl SailManager__GetWork
	ldr r1, [r0, #0x70]
	ldr r0, =SailChaosEmerald__State_216C5B0
	str r1, [r4, #0x15c]
	str r0, [r5, #0xf4]
	mov r0, #0
	str r0, [r5, #0x2c]
	str r0, [r5, #0x28]
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailChaosEmerald__State_216C5B0(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, r7, lr}
	mov r7, r0
	ldr r5, [r7, #0x124]
	bl SailManager__GetWork
	ldr r6, [r0, #0x98]
	bl SailManager__GetWork
	ldr r2, [r7, #0x2c]
	ldr r1, =_0218BC64
	mov r2, r2, asr #2
	mov r2, r2, lsl #0x1d
	mov r2, r2, lsr #0x1c
	ldrsh r1, [r1, r2]
	mov r4, r0
	mov r0, r7
	mov r1, r1, asr #2
	str r1, [r5, #0x180]
	ldr r1, [r7, #0x2c]
	add r1, r1, #1
	str r1, [r7, #0x2c]
	bl SailObject__Func_2166A2C
	add r0, r5, #0x100
	ldrh r1, [r0, #0x6e]
	mov r0, r7
	strh r1, [r7, #0x32]
	bl SailObject__SetupAnimator3D
	ldr r0, [r4, #0x24]
	tst r0, #8
	bne _0216C63C
	ldr r1, [r6, #0x44]
	ldr r0, [r5, #0x178]
	cmp r1, r0
	ldmleia sp!, {r3, r4, r5, r6, r7, pc}
	mov r0, r7
	bl SailChaosEmerald__Func_216C650
	ldmia sp!, {r3, r4, r5, r6, r7, pc}
_0216C63C:
	ldr r0, [r7, #0x20]
	orr r0, r0, #0x20
	str r0, [r7, #0x20]
	ldmia sp!, {r3, r4, r5, r6, r7, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailChaosEmerald__Func_216C650(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r5, r0
	ldr r4, [r5, #0x124]
	bl SailManager__GetWork
	ldr r0, [r0, #0x70]
	mov r1, #0
	str r0, [r4, #0x15c]
	ldr r0, =SailChaosEmerald__State_216C69C
	str r1, [r4, #0x180]
	str r0, [r5, #0xf4]
	str r1, [r5, #0x2c]
	str r1, [r5, #0x28]
	bl SailManager__GetWork
	ldrh r1, [r0, #0x10]
	ldr r0, =gameState
	strb r1, [r0, #0x150]
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailChaosEmerald__State_216C69C(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #0x34
	mov r5, r0
	ldr r4, [r5, #0x124]
	bl SailManager__GetWork
	ldr r0, [r4, #0x15c]
	cmp r0, #0
	addeq sp, sp, #0x34
	ldmeqia sp!, {r4, r5, pc}
	mov r2, #0x400
	rsb r2, r2, #0
	sub r1, r2, #0xd00
	mov r0, #0
	str r2, [sp, #4]
	str r1, [sp, #8]
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x15c]
	ldr r3, =FX_SinCosTable_
	ldrh r1, [r0, #0x32]
	add r0, sp, #0x10
	mov r1, r1, asr #4
	mov r2, r1, lsl #1
	add r1, r2, #1
	mov ip, r2, lsl #1
	mov r2, r1, lsl #1
	ldrsh r1, [r3, ip]
	ldrsh r2, [r3, r2]
	bl MTX_RotY33_
	add r0, sp, #4
	add r1, sp, #0x10
	mov r2, r0
	bl MTX_MultVec33
	mov r0, #0x2000
	str r0, [sp]
	ldr r0, [r4, #0x15c]
	ldr r1, [sp, #4]
	ldr r2, [r0, #0x44]
	ldr r0, [r5, #0x44]
	add r1, r2, r1
	mov r2, #1
	mov r3, #0
	bl ObjShiftSet
	str r0, [r5, #0x44]
	mov r0, #0x2000
	str r0, [sp]
	ldr r2, [r4, #0x15c]
	ldr r1, [sp, #8]
	ldr r3, [r2, #0x48]
	ldr r0, [r5, #0x48]
	add r1, r3, r1
	mov r2, #1
	mov r3, #0
	bl ObjShiftSet
	str r0, [r5, #0x48]
	mov r0, #0x2000
	str r0, [sp]
	ldr r1, [r4, #0x15c]
	ldr r0, [r5, #0x4c]
	ldr r3, [r1, #0x4c]
	ldr r1, [sp, #0xc]
	mov r2, #1
	add r1, r3, r1
	mov r3, #0
	bl ObjShiftSet
	str r0, [r5, #0x4c]
	add sp, sp, #0x34
	ldmia sp!, {r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailGoal__SetupObject(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r5, r0
	ldr r4, [r5, #0x124]
	bl SailManager__GetWork
	ldr r1, [r0, #0x70]
	ldr r0, =SailGoal__State_216C7E0
	str r1, [r4, #0x15c]
	str r0, [r5, #0xf4]
	mov r0, #0
	str r0, [r5, #0x2c]
	str r0, [r5, #0x28]
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailGoal__State_216C7E0(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, r7, lr}
	mov r7, r0
	ldr r4, [r7, #0x124]
	bl SailManager__GetWork
	ldr r5, [r0, #0x98]
	bl SailManager__GetWork
	ldr r2, [r7, #0x2c]
	ldr r1, =_0218BC64
	mov r2, r2, asr #2
	mov r2, r2, lsl #0x1d
	mov r2, r2, lsr #0x1c
	ldrsh r1, [r1, r2]
	mov r6, r0
	mov r0, r7
	mov r1, r1, asr #2
	str r1, [r4, #0x180]
	ldr r1, [r7, #0x2c]
	add r1, r1, #1
	str r1, [r7, #0x2c]
	bl SailObject__Func_2166A2C
	add r0, r4, #0x100
	ldrh r1, [r0, #0x6e]
	mov r0, r7
	strh r1, [r7, #0x32]
	bl SailObject__SetupAnimator3D
	ldr r1, [r5, #0x44]
	ldr r0, [r4, #0x178]
	cmp r1, r0
	ble _0216C8A0
	mov r0, #0x100
	str r0, [sp]
	ldr r0, [r7, #0x38]
	mov r1, #0x8000
	mov r2, #1
	mov r3, #0x1000
	bl ObjShiftSet
	ldr r1, [r7, #0x28]
	cmp r1, #0
	moveq r0, #1
	streq r0, [r7, #0x28]
	moveq r0, #0x1000
	str r0, [r7, #0x38]
	str r0, [r7, #0x3c]
	str r0, [r7, #0x40]
	cmp r0, #0x8000
	ldreq r0, [r7, #0x18]
	orreq r0, r0, #4
	streq r0, [r7, #0x18]
_0216C8A0:
	ldr r0, [r6, #0xc]
	cmp r0, #0
	ldmeqia sp!, {r3, r4, r5, r6, r7, pc}
	ldr r0, [r6, #0x24]
	tst r0, #8
	ldrne r0, [r7, #0x20]
	orrne r0, r0, #0x20
	strne r0, [r7, #0x20]
	ldmia sp!, {r3, r4, r5, r6, r7, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailGoalText__SetupObject(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r5, r0
	ldr r4, [r5, #0x124]
	bl SailManager__GetWork
	ldr r1, [r0, #0x70]
	ldr r0, =SailGoalText__State_216C8F8
	str r1, [r4, #0x15c]
	str r0, [r5, #0xf4]
	mov r0, #0
	str r0, [r5, #0x2c]
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailGoalText__State_216C8F8(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, lr}
	mov r5, r0
	ldr r4, [r5, #0x124]
	bl SailManager__GetWork
	ldr r2, [r5, #0x2c]
	ldr r1, =_0218BC64
	mov r2, r2, asr #2
	mov r2, r2, lsl #0x1d
	mov r2, r2, lsr #0x1c
	ldrsh r1, [r1, r2]
	ldr r6, [r0, #0x98]
	mov r0, r5
	mov r1, r1, asr #2
	str r1, [r4, #0x180]
	ldr r1, [r5, #0x2c]
	add r1, r1, #1
	str r1, [r5, #0x2c]
	bl SailObject__Func_2166A2C
	ldr r1, [r6, #0x44]
	ldr r0, [r5, #0x28]
	cmp r1, r0
	ldrhi r0, [r5, #0x18]
	orrhi r0, r0, #4
	strhi r0, [r5, #0x18]
	ldmia sp!, {r4, r5, r6, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailItemBonus__GiveItem(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, r7, lr}
	mov r6, r1
	ldrh r1, [r6, #0]
	mov r7, r0
	mov r5, #0
	cmp r1, #0
	beq _0216C994
	ldr r6, [r6, #0x11c]
	cmp r6, #0
	ldmeqia sp!, {r3, r4, r5, r6, r7, pc}
	ldrh r0, [r6, #0]
	cmp r0, #0
	ldmneia sp!, {r3, r4, r5, r6, r7, pc}
_0216C994:
	ldr r0, [r7, #0x138]
	add r2, r7, #0x44
	mov r1, #0x15
	ldr r4, [r6, #0x124]
	bl SailAudio__PlaySpatialSequence
	ldr r0, [r7, #0x28]
	cmp r0, #0xf
	addls pc, pc, r0, lsl #2
	b _0216C9F8
_0216C9B8: // jump table
	b _0216C9F8 // case 0
	b _0216CA0C // case 1
	b _0216CA20 // case 2
	b _0216CA34 // case 3
	b _0216CA48 // case 4
	b _0216CA68 // case 5
	b _0216CA88 // case 6
	b _0216CAA8 // case 7
	b _0216CAC8 // case 8
	b _0216CAE8 // case 9
	b _0216CB08 // case 10
	b _0216CB28 // case 11
	b _0216CB48 // case 12
	b _0216CB50 // case 13
	b _0216CB58 // case 14
	b _0216CB60 // case 15
_0216C9F8:
	mov r1, #0x40000
	mov r0, r6
	rsb r1, r1, #0
	bl SailPlayer__RemoveHealth
	b _0216CB64
_0216CA0C:
	mov r1, #0x80000
	mov r0, r6
	rsb r1, r1, #0
	bl SailPlayer__RemoveHealth
	b _0216CB64
_0216CA20:
	mov r1, #0xc4000
	mov r0, r6
	rsb r1, r1, #0
	bl SailPlayer__RemoveHealth
	b _0216CB64
_0216CA34:
	mov r1, #0x100000
	mov r0, r6
	rsb r1, r1, #0
	bl SailPlayer__RemoveHealth
	b _0216CB64
_0216CA48:
	add r2, r7, #0x44
	mov r0, #0
	mov r1, #0xb
	bl SailAudio__PlaySpatialSequence
	mov r0, r6
	mov r1, #0x19000
	bl SailPlayer__GiveBoost
	b _0216CB64
_0216CA68:
	add r2, r7, #0x44
	mov r0, #0
	mov r1, #0xb
	bl SailAudio__PlaySpatialSequence
	mov r0, r6
	mov r1, #0x32000
	bl SailPlayer__GiveBoost
	b _0216CB64
_0216CA88:
	add r2, r7, #0x44
	mov r0, #0
	mov r1, #0xb
	bl SailAudio__PlaySpatialSequence
	mov r0, r6
	mov r1, #0x80000
	bl SailPlayer__GiveBoost
	b _0216CB64
_0216CAA8:
	add r2, r7, #0x44
	mov r0, #0
	mov r1, #0xb
	bl SailAudio__PlaySpatialSequence
	mov r0, r6
	mov r1, #0x100000
	bl SailPlayer__GiveBoost
	b _0216CB64
_0216CAC8:
	add r2, r7, #0x44
	mov r0, #0
	mov r1, #0x14
	bl SailAudio__PlaySpatialSequence
	ldr r0, [r4, #0x1a4]
	add r0, r0, #0xa
	str r0, [r4, #0x1a4]
	b _0216CB64
_0216CAE8:
	add r2, r7, #0x44
	mov r0, #0
	mov r1, #0x14
	bl SailAudio__PlaySpatialSequence
	ldr r0, [r4, #0x1a4]
	add r0, r0, #0x14
	str r0, [r4, #0x1a4]
	b _0216CB64
_0216CB08:
	add r2, r7, #0x44
	mov r0, #0
	mov r1, #0x14
	bl SailAudio__PlaySpatialSequence
	ldr r0, [r4, #0x1a4]
	add r0, r0, #0x1e
	str r0, [r4, #0x1a4]
	b _0216CB64
_0216CB28:
	add r2, r7, #0x44
	mov r0, #0
	mov r1, #0x14
	bl SailAudio__PlaySpatialSequence
	ldr r0, [r4, #0x1a4]
	add r0, r0, #0x32
	str r0, [r4, #0x1a4]
	b _0216CB64
_0216CB48:
	mov r5, #0x3e8
	b _0216CB64
_0216CB50:
	mov r5, #0x7d0
	b _0216CB64
_0216CB58:
	ldr r5, =0x00001388
	b _0216CB64
_0216CB60:
	mov r5, #0x1f40
_0216CB64:
	ldr r1, [r4, #0x1a4]
	ldr r0, =0x0000270F
	cmp r1, r0
	strhi r0, [r4, #0x1a4]
	cmp r5, #0
	beq _0216CBB0
	add r0, r4, #0x100
	ldrh r0, [r0, #0xc4]
	mov r1, #0x32
	bl FX_DivS32
	add r0, r0, #1
	mov r0, r0, lsl #0x10
	ldr r1, [r4, #0x1a8]
	mov r0, r0, lsr #0x10
	mla r1, r5, r0, r1
	ldr r0, =0x05F5E0FF
	str r1, [r4, #0x1a8]
	cmp r1, r0
	strhi r0, [r4, #0x1a8]
_0216CBB0:
	ldr r1, [r7, #0x28]
	mov r0, r7
	bl SailItemBonus__Create
	bl SailManager__GetShipType
	cmp r0, #1
	beq _0216CBD4
	bl SailManager__GetShipType
	cmp r0, #3
	bne _0216CBDC
_0216CBD4:
	add r0, r7, #0x44
	bl EffectSailBomb__Create
_0216CBDC:
	ldr r0, [r7, #0x18]
	orr r0, r0, #0xa
	str r0, [r7, #0x18]
	ldmia sp!, {r3, r4, r5, r6, r7, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void SailItemBonus__State_216CBF8(StageTask *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, lr}
	mov r4, r0
	ldr r0, [r4, #0x2c]
	cmp r0, #6
	ble _0216CC1C
	ldr r0, [r4, #0x9c]
	mov r1, #0xc0
	bl ObjSpdDownSet
	str r0, [r4, #0x9c]
_0216CC1C:
	ldr r0, [r4, #0x2c]
	cmp r0, #0x1e
	ble _0216CC40
	tst r0, #1
	ldr r0, [r4, #0x20]
	orrne r0, r0, #0x20
	strne r0, [r4, #0x20]
	biceq r0, r0, #0x20
	streq r0, [r4, #0x20]
_0216CC40:
	ldr r0, [r4, #0x2c]
	cmp r0, #0x40
	ldrgt r0, [r4, #0x18]
	orrgt r0, r0, #4
	strgt r0, [r4, #0x18]
	ldr r0, [r4, #0x2c]
	add r0, r0, #1
	str r0, [r4, #0x2c]
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}
