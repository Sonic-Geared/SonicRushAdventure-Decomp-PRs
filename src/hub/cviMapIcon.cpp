#include <hub/cviMapIcon.hpp>
#include <game/file/fileUnknown.h>
#include <game/file/binaryBundle.h>
#include <game/input/padInput.h>
#include <game/input/touchInput.h>
#include <game/graphics/drawState.h>
#include <game/graphics/drawReqTask.h>
#include <hub/hubConfig.h>

// --------------------
// TEMP
// --------------------

extern "C"
{

NOT_DECOMPILED void _ZN10HubControl17GetFileFrom_ViActEt(void);
NOT_DECOMPILED void _ZN10HubControl12Func_2157178Ev(void);
NOT_DECOMPILED void _ZN10HubControl12Func_215B51CEl(void);

NOT_DECOMPILED void Unknown2051334__Func_20516B8(void);
NOT_DECOMPILED void Unknown2051334__Func_2051600(void);

}

// --------------------
// VARIABLES
// --------------------

NOT_DECOMPILED void *aBbViDockBb;

// --------------------
// FUNCTIONS
// --------------------

CViMapIcon::CViMapIcon()
{
    this->sprIcon = NULL;

    MI_CpuClear32(&this->aniIconOutline, sizeof(this->aniCursor));
    MI_CpuClear32(&this->aniIconCenter, sizeof(this->aniCursor));
    MI_CpuClear32(&this->aniSonicMarker, sizeof(this->aniCursor));
    MI_CpuClear32(&this->aniCursor, sizeof(this->aniCursor));

    ViMapIcon__Release(this);
}

CViMapIcon::~CViMapIcon()
{
    ViMapIcon__Release(this);
}

NONMATCH_FUNC void ViMapIcon__Func_2163058(CViMapIcon *work, BOOL useEngineB)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, lr}
	sub sp, sp, #0x1c
	mov r5, r1
	mov r6, r0
	bl ViMapIcon__Release
	cmp r5, #0
	ldreq r4, =0x05000200
	mov r0, #0
	ldrne r4, =0x05000600
	bl _ZN10HubControl17GetFileFrom_ViActEt
	mov r1, #0
	str r0, [r6, #8]
	bl Sprite__GetSpriteSize3FromAnim
	mov r1, r0
	mov r0, r5
	bl VRAMSystem__AllocSpriteVram
	str r5, [sp]
	mov r2, #0
	str r2, [sp, #4]
	str r0, [sp, #8]
	str r2, [sp, #0xc]
	str r4, [sp, #0x10]
	mov r0, #2
	str r0, [sp, #0x14]
	mov r0, #0x10
	str r0, [sp, #0x18]
	ldr r1, [r6, #8]
	add r0, r6, #0xd8
	mov r3, #0x64
	bl AnimatorSprite__Init
	mov r1, #4
	add r0, r6, #0x100
	strh r1, [r0, #0x28]
	mov r1, #0
	add r0, r6, #0xd8
	mov r2, r1
	bl AnimatorSprite__ProcessAnimation
	ldr r1, [r6, #0x114]
	mov r0, r6
	bic r1, r1, #0x60
	str r1, [r6, #0x114]
	bl ViMapIcon__Func_21636C8
	ldr r0, [r6, #8]
	mov r1, #1
	bl Sprite__GetSpriteSize3FromAnim
	mov r1, r0
	mov r0, r5
	bl VRAMSystem__AllocSpriteVram
	str r5, [sp]
	mov r1, #0
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	str r4, [sp, #0x10]
	mov r0, #2
	str r0, [sp, #0x14]
	mov r0, #0x11
	str r0, [sp, #0x18]
	ldr r1, [r6, #8]
	add r0, r6, #0x10
	mov r2, #1
	mov r3, #0x60
	bl AnimatorSprite__Init
	mov r0, #5
	strh r0, [r6, #0x60]
	mov r0, #0x10
	mov r1, #0
	strh r0, [r6, #0x64]
	add r0, r6, #0x10
	mov r2, r1
	bl AnimatorSprite__ProcessAnimation
	ldr r0, [r6, #0x4c]
	mov r1, #2
	bic r0, r0, #0x60
	orr r0, r0, #0x18
	str r0, [r6, #0x4c]
	ldr r0, [r6, #8]
	bl Sprite__GetSpriteSize3FromAnim
	mov r1, r0
	mov r0, r5
	bl VRAMSystem__AllocSpriteVram
	str r5, [sp]
	mov r1, #0
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	str r4, [sp, #0x10]
	mov r2, #2
	str r2, [sp, #0x14]
	mov r0, #0x12
	str r0, [sp, #0x18]
	ldr r1, [r6, #8]
	add r0, r6, #0x74
	mov r3, #0x30
	bl AnimatorSprite__Init
	mov r0, #5
	strh r0, [r6, #0xc4]
	mov r0, #0x10
	mov r1, #0
	strh r0, [r6, #0xc8]
	add r0, r6, #0x74
	mov r2, r1
	bl AnimatorSprite__ProcessAnimation
	ldr r0, [r6, #0xb0]
	mov r1, #3
	bic r0, r0, #0x60
	orr r0, r0, #0x18
	str r0, [r6, #0xb0]
	ldr r0, [r6, #8]
	bl Sprite__GetSpriteSize3FromAnim
	mov r1, r0
	mov r0, r5
	bl VRAMSystem__AllocSpriteVram
	str r5, [sp]
	mov r1, #0
	str r1, [sp, #4]
	str r0, [sp, #8]
	str r1, [sp, #0xc]
	str r4, [sp, #0x10]
	str r1, [sp, #0x14]
	str r1, [sp, #0x18]
	ldr r1, [r6, #8]
	add r0, r6, #0x18c
	mov r2, #3
	mov r3, #0x30
	bl AnimatorSprite__Init
	mov r1, #5
	add r0, r6, #0x100
	strh r1, [r0, #0xdc]
	mov r1, #0x10
	strh r1, [r0, #0xe0]
	mov r1, #0
	add r0, r6, #0x18c
	mov r2, r1
	bl AnimatorSprite__ProcessAnimation
	ldr r0, [r6, #0x1c8]
	bic r0, r0, #0x60
	orr r0, r0, #0x18
	str r0, [r6, #0x1c8]
	add sp, sp, #0x1c
	ldmia sp!, {r3, r4, r5, r6, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Release(CViMapIcon *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, lr}
	mov r4, r0
	add r0, r4, #0x18c
	bl AnimatorSprite__Release
	add r0, r4, #0x74
	bl AnimatorSprite__Release
	add r0, r4, #0x10
	bl AnimatorSprite__Release
	add r0, r4, #0xd8
	bl AnimatorSprite__Release
	mov r0, #0
	add r1, r4, #0x74
	mov r2, #0x64
	bl MIi_CpuClear32
	mov r0, #0
	add r1, r4, #0x10
	mov r2, #0x64
	bl MIi_CpuClear32
	mov r0, #0
	add r1, r4, #0xd8
	mov r2, #0x64
	bl MIi_CpuClear32
	mov r0, #0
	add r1, r4, #0x18c
	mov r2, #0x64
	bl MIi_CpuClear32
	mov r0, #0
	str r0, [r4, #8]
	strh r0, [r4, #0xc]
	strh r0, [r4, #0xe]
	add r1, r4, #0x14c
	mov r2, #0x40
	bl MIi_CpuClear32
	mov r1, #0
	str r1, [r4, #4]
	mov r0, #9
	str r0, [r4, #0x13c]
	add r0, r4, #0x100
	strh r1, [r0, #0x40]
	strh r1, [r0, #0x42]
	str r1, [r4, #0x144]
	str r1, [r4, #0x148]
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Func_2163340(CViMapIcon *work, u8 id, BOOL enabled){
#ifdef NON_MATCHING

#else
    // clang-format off
	cmp r2, #0
	ldrne r3, [r0, #4]
	mov r2, #1
	orrne r1, r3, r2, lsl r1
	mvneq r1, r2, lsl r1
	ldreq r2, [r0, #4]
	andeq r1, r2, r1
	str r1, [r0, #4]
	bx lr

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Func_2163364(CViMapIcon *work, u16 x, u16 y){
#ifdef NON_MATCHING

#else
    // clang-format off
	strh r1, [r0, #0xc]
	strh r2, [r0, #0xe]
	bx lr

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__GetIconPosition(CViMapIcon *work, u32 area, u16 *x, u16 *y){
#ifdef NON_MATCHING

#else
    // clang-format off
	cmp r2, #0
	beq _02163388
	add ip, r0, r1, lsl #3
	add ip, ip, #0x100
	ldrh ip, [ip, #0x50]
	strh ip, [r2]
_02163388:
	cmp r3, #0
	bxeq lr
	add r0, r0, r1, lsl #3
	add r0, r0, #0x100
	ldrh r0, [r0, #0x52]
	strh r0, [r3]
	bx lr

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__SetIconID2(CViMapIcon *work, u32 icon){
#ifdef NON_MATCHING

#else
    // clang-format off
	str r1, [r0, #0x13c]
	add r1, r0, #0x100
	mov r2, #0
	strh r2, [r1, #0x40]
	strh r2, [r1, #0x42]
	str r2, [r0, #0x144]
	str r2, [r0, #0x148]
	bx lr

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__SetIconID(CViMapIcon *work, u32 icon)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r5, r0
	add r2, r5, #0x42
	mov r4, r1
	add r1, r5, #0x140
	add r2, r2, #0x100
	bl ViMapIcon__Func_21637A0
	str r4, [r5, #0x13c]
	mov r0, #0x20
	str r0, [r5, #0x144]
	mov r0, #0
	str r0, [r5, #0x148]
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC s32 ViMapIcon__GetCurrentIcon(CViMapIcon *work){
#ifdef NON_MATCHING

#else
    // clang-format off
	ldr r0, [r0, #0x13c]
	bx lr

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Func_2163400(CViMapIcon *work){
#ifdef NON_MATCHING

#else
    // clang-format off
	ldr r2, [r0, #0x148]
	ldr r1, [r0, #0x144]
	cmp r2, r1
	bxhs lr
	add r2, r2, #1
	str r2, [r0, #0x148]
	ldr r1, [r0, #0x144]
	cmp r2, r1
	bxne lr
	add r1, r0, #0x100
	mov r2, #0
	strh r2, [r1, #0x40]
	strh r2, [r1, #0x42]
	str r2, [r0, #0x144]
	str r2, [r0, #0x148]
	bx lr

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Func_2163440(CViMapIcon *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r5, r0
	ldr r1, [r5, #4]
	tst r1, #1
	beq _02163490
	add r1, sp, #0
	add r2, sp, #2
	bl ViMapIcon__Func_21637A0
	ldrh r3, [sp]
	ldrh r1, [r5, #0xc]
	ldrh r2, [sp, #2]
	ldrh r0, [r5, #0xe]
	sub r1, r3, r1
	mov r1, r1, lsl #0x10
	sub r0, r2, r0
	mov r2, r0, lsl #0x10
	mov r0, r5
	mov r1, r1, asr #0x10
	mov r2, r2, asr #0x10
	bl ViMapIcon__Func_21638A4
_02163490:
	ldr r0, [r5, #4]
	tst r0, #2
	ldmeqia sp!, {r3, r4, r5, pc}
	mov r4, #0
_021634A0:
	add r1, r5, r4, lsl #3
	ldr r0, [r1, #0x14c]
	tst r0, #1
	beq _021634E4
	add r0, r1, #0x100
	ldrh r3, [r0, #0x50]
	ldrh r1, [r5, #0xc]
	ldrh r2, [r0, #0x52]
	ldrh r0, [r5, #0xe]
	sub r1, r3, r1
	mov r1, r1, lsl #0x10
	sub r0, r2, r0
	mov r2, r0, lsl #0x10
	mov r0, r5
	mov r1, r1, asr #0x10
	mov r2, r2, asr #0x10
	bl ViMapIcon__Func_2163738
_021634E4:
	add r4, r4, #1
	cmp r4, #8
	blt _021634A0
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC s32 ViMapIcon__GetIconFromTouchPos(CViMapIcon *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r4, r0
	bl IsTouchInputEnabled
	cmp r0, #0
	beq _0216351C
	ldr r0, =touchInput
	ldrh r0, [r0, #0x12]
	tst r0, #4
	movne r0, #1
	bne _02163520
_0216351C:
	mov r0, #0
_02163520:
	cmp r0, #0
	beq _02163534
	bl _ZN10HubControl12Func_2157178Ev
	cmp r0, #0
	bne _0216353C
_02163534:
	mov r0, #9
	ldmia sp!, {r3, r4, r5, pc}
_0216353C:
	ldr r0, =touchInput
	ldrh r1, [r4, #0xc]
	ldrh r3, [r0, #0x1c]
	ldrh r2, [r0, #0x1e]
	ldrh r0, [r4, #0xe]
	add r1, r3, r1
	mov r3, r1, lsl #0x10
	add r0, r2, r0
	mov ip, r0, lsl #0x10
	mov r0, #9
	mov r1, #0
_02163568:
	add r5, r4, r1, lsl #3
	ldr r2, [r5, #0x14c]
	tst r2, #1
	beq _021635C8
	add r2, r5, #0x100
	ldrh lr, [r2, #0x50]
	ldrh r5, [r2, #0x52]
	sub r2, lr, #0xc
	mov r2, r2, lsl #0x10
	mov r2, r2, lsr #0x10
	rsb r2, r2, r3, lsr #16
	mov r2, r2, lsl #0x10
	mov r2, r2, lsr #0x10
	cmp r2, #0x18
	bhs _021635C8
	sub r2, r5, #0xc
	mov r2, r2, lsl #0x10
	mov r2, r2, lsr #0x10
	rsb r2, r2, ip, lsr #16
	mov r2, r2, lsl #0x10
	mov r2, r2, lsr #0x10
	cmp r2, #0x18
	movlo r0, r1
	ldmloia sp!, {r3, r4, r5, pc}
_021635C8:
	add r1, r1, #1
	cmp r1, #8
	blt _02163568
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC s32 ViMapIcon__Func_21635DC(CViMapIcon *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, lr}
	mov r4, r0
	ldr r1, [r4, #0x148]
	ldr r0, [r4, #0x144]
	cmp r1, r0
	ldrlo r0, =padInput
	ldrloh r0, [r0, #4]
	ldrhs r0, =padInput
	ldrhsh r0, [r0, #0]
	tst r0, #0x20
	ldrne r5, =ViMapIcon__Func_2163904
	bne _02163638
	tst r0, #0x40
	ldrne r5, =ViMapIcon__Func_216392C
	bne _02163638
	tst r0, #0x10
	ldrne r5, =ViMapIcon__Func_2163954
	bne _02163638
	tst r0, #0x80
	ldrne r5, =ViMapIcon__Func_216397C
	bne _02163638
	mov r0, #9
	ldmia sp!, {r4, r5, r6, pc}
_02163638:
	mov r6, #0
_0216363C:
	add r2, r6, #1
	ldr r0, [r4, #0x13c]
	mov r2, r2, lsl #0x10
	mov r1, r6
	mov r6, r2, lsr #0x10
	blx r5
	cmp r0, #8
	movge r0, #9
	ldmgeia sp!, {r4, r5, r6, pc}
	add r1, r4, r0, lsl #3
	ldr r1, [r1, #0x14c]
	tst r1, #1
	beq _0216363C
	ldmia sp!, {r4, r5, r6, pc}

// clang-format on
#endif
}

NONMATCH_FUNC BOOL ViMapIcon__IsMoving(CViMapIcon *work){
#ifdef NON_MATCHING

#else
    // clang-format off
	ldr r1, [r0, #0x148]
	ldr r0, [r0, #0x144]
	cmp r1, r0
	movlo r0, #1
	movhs r0, #0
	bx lr

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Func_21636A0(CViMapIcon *work){
#ifdef NON_MATCHING

#else
    // clang-format off
	ldr ip, =ViMapIcon__Func_21636C8
	bx ip

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Func_21636AC(CViMapIcon *work, s16 x, s16 y){
#ifdef NON_MATCHING

#else
    // clang-format off
	add r3, r0, #0x100
	strh r1, [r3, #0x94]
	ldr ip, =AnimatorSprite__DrawFrame
	add r0, r0, #0x18c
	strh r2, [r3, #0x96]
	bx ip

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Func_21636C8(CViMapIcon *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, r7, lr}
	mov r4, r0
	add r1, r4, #0x14c
	mov r0, #0
	mov r2, #0x40
	bl MIi_CpuClear32
	add r0, r4, #0x52
	add r6, r0, #0x100
	add r7, r4, #0x150
	mov r5, #0
_021636F0:
	mov r0, r5
	bl _ZN10HubControl12Func_215B51CEl
	cmp r0, #0
	beq _02163720
	add ip, r4, r5, lsl #3
	ldr r1, [ip, #0x14c]
	mov r0, r5
	orr r3, r1, #1
	mov r1, r7
	mov r2, r6
	str r3, [ip, #0x14c]
	bl ViMapIcon__Func_21638D0
_02163720:
	add r5, r5, #1
	cmp r5, #8
	add r6, r6, #8
	add r7, r7, #8
	blt _021636F0
	ldmia sp!, {r3, r4, r5, r6, r7, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Func_2163738(CViMapIcon *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, lr}
	mov r5, r1
	mvn r1, #0xf
	mov r6, r0
	mov r4, r2
	cmp r5, r1
	ldmleia sp!, {r4, r5, r6, pc}
	cmp r5, #0x110
	ldmgeia sp!, {r4, r5, r6, pc}
	cmp r4, r1
	ldmleia sp!, {r4, r5, r6, pc}
	cmp r4, #0xd0
	ldmgeia sp!, {r4, r5, r6, pc}
	strh r5, [r6, #0x7c]
	strh r4, [r6, #0x7e]
	mov r0, #1
	str r0, [r6, #0xcc]
	add r0, r6, #0x74
	bl AnimatorSprite__DrawFrame
	strh r5, [r6, #0x18]
	strh r4, [r6, #0x1a]
	mov r1, #0
	add r0, r6, #0x10
	str r1, [r6, #0x68]
	bl AnimatorSprite__DrawFrame
	ldmia sp!, {r4, r5, r6, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Func_21637A0(CViMapIcon *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
	mov r9, r1
	ldr r1, [r0, #0x144]
	ldr r5, [r0, #0x148]
	mov r8, r2
	cmp r5, r1
	blo _021637F8
	cmp r9, #0
	beq _021637D8
	ldr r1, [r0, #0x13c]
	add r1, r0, r1, lsl #3
	add r1, r1, #0x100
	ldrh r1, [r1, #0x50]
	strh r1, [r9]
_021637D8:
	cmp r8, #0
	ldmeqia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
	ldr r1, [r0, #0x13c]
	add r0, r0, r1, lsl #3
	add r0, r0, #0x100
	ldrh r0, [r0, #0x52]
	strh r0, [r8]
	ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
_021637F8:
	ldr r3, [r0, #0x13c]
	add r2, r0, #0x100
	add r0, r0, r3, lsl #3
	add r0, r0, #0x100
	ldrh r4, [r0, #0x50]
	ldrh r3, [r0, #0x52]
	mov r0, r5, lsl #0xc
	mov r6, r4, lsl #0xc
	mov r7, r3, lsl #0xc
	ldrh r5, [r2, #0x40]
	ldrh r4, [r2, #0x42]
	bl FX_DivS32
	smull r2, r1, r0, r0
	adds r2, r2, #0x800
	adc r1, r1, #0
	mov r2, r2, lsr #0xc
	orr r2, r2, r1, lsl #20
	cmp r9, #0
	rsb r0, r2, r0, lsl #1
	mov r2, #0
	mov r1, #0x800
	beq _02163874
	sub r3, r6, r5, lsl #12
	smull ip, r6, r3, r0
	adds r3, ip, r1
	adc r1, r6, r2
	mov r2, r3, lsr #0xc
	orr r2, r2, r1, lsl #20
	add r1, r2, r5, lsl #12
	mov r1, r1, asr #0xc
	strh r1, [r9]
_02163874:
	cmp r8, #0
	ldmeqia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
	sub r1, r7, r4, lsl #12
	smull r2, r0, r1, r0
	adds r1, r2, #0x800
	adc r0, r0, #0
	mov r1, r1, lsr #0xc
	orr r1, r1, r0, lsl #20
	add r0, r1, r4, lsl #12
	mov r0, r0, asr #0xc
	strh r0, [r8]
	ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Func_21638A4(CViMapIcon *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, lr}
	mov r4, r0
	strh r1, [r4, #0xe0]
	mov r1, #0
	strh r2, [r4, #0xe2]
	mov r2, r1
	add r0, r4, #0xd8
	bl AnimatorSprite__ProcessAnimation
	add r0, r4, #0xd8
	bl AnimatorSprite__DrawFrame
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Func_21638D0(CViMapIcon *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r0, r0, lsl #0x10
	mov r5, r1
	mov r0, r0, lsr #0x10
	mov r4, r2
	bl HubConfig__Func_2152960
	cmp r5, #0
	ldrneh r1, [r0, #0]
	strneh r1, [r5]
	cmp r4, #0
	ldrneh r0, [r0, #2]
	strneh r0, [r4]
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Func_2163904(CViMapIcon *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, lr}
	mov r0, r0, lsl #0x10
	mov r4, r1
	mov r0, r0, lsr #0x10
	bl HubConfig__Func_2152960
	cmp r4, #3
	movhs r0, #9
	addlo r0, r0, r4, lsl #2
	ldrlo r0, [r0, #0xc]
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Func_216392C(CViMapIcon *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, lr}
	mov r0, r0, lsl #0x10
	mov r4, r1
	mov r0, r0, lsr #0x10
	bl HubConfig__Func_2152960
	cmp r4, #3
	movhs r0, #9
	addlo r0, r0, r4, lsl #2
	ldrlo r0, [r0, #0x18]
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Func_2163954(CViMapIcon *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, lr}
	mov r0, r0, lsl #0x10
	mov r4, r1
	mov r0, r0, lsr #0x10
	bl HubConfig__Func_2152960
	cmp r4, #3
	movhs r0, #9
	addlo r0, r0, r4, lsl #2
	ldrlo r0, [r0, #0x24]
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Func_216397C(CViMapIcon *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, lr}
	mov r0, r0, lsl #0x10
	mov r4, r1
	mov r0, r0, lsr #0x10
	bl HubConfig__Func_2152960
	cmp r4, #3
	movhs r0, #9
	addlo r0, r0, r4, lsl #2
	ldrlo r0, [r0, #0x30]
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Func_21639A4(CViMapIcon *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, lr}
	mov r5, r1
	mov r6, r0
	mov r4, r2
	cmp r5, #8
	movge r5, #9
	mov r1, r6
	mov r0, #0
	mov r2, #0xe0
	bl MIi_CpuClear32
	stmia r6, {r4, r5}
	mov r0, #0
	strh r0, [r6, #0x78]
	ldr r0, [r6, #4]
	cmp r0, #8
	ldmgeia sp!, {r4, r5, r6, pc}
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bl HubConfig__GetDockBackInfo
	ldrh r1, [r0, #0x10]
	ldr r0, =aBbViDockBb
	mov r2, #0
	bl ReadFileFromBundle
	str r0, [r6, #0xdc]
	ldr r1, [r6, #4]
	ldr r2, [r6, #0]
	add r0, r6, #8
	bl ViMapIcon__Func_216400C
	mov r0, r6
	bl ViMapIcon__Func_216428C
	strh r0, [r6, #0x1c]
	ldr r1, [r6, #4]
	ldr r2, [r6, #0xdc]
	ldr r3, [r6, #0]
	add r0, r6, #0xbc
	bl ViMapIcon__Func_21640F4
	ldr r1, [r6, #4]
	add r0, r6, #0x7c
	bl ViMapIcon__Func_2164224
	mov r0, r6
	bl ViMapIcon__Func_2163C80
	ldmia sp!, {r4, r5, r6, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Func_2163A50(CViMapIcon *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, lr}
	mov r4, r0
	ldr r0, [r4, #0xdc]
	cmp r0, #0
	beq _02163A70
	bl _FreeHEAP_USER
	mov r0, #0
	str r0, [r4, #0xdc]
_02163A70:
	mov r0, #9
	str r0, [r4, #4]
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Func_2163A7C(CViMapIcon *work){
#ifdef NON_MATCHING

#else
    // clang-format off
	str r1, [r0]
	bx lr

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Func_2163A84(CViMapIcon *work){
#ifdef NON_MATCHING

#else
    // clang-format off
	ldr r2, [r1, #0]
	str r2, [r0, #8]
	ldr r2, [r1, #4]
	str r2, [r0, #0xc]
	ldr r1, [r1, #8]
	str r1, [r0, #0x10]
	bx lr

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Func_2163AA0(CViMapIcon *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
	mov r7, r0
	mov r4, r1
	mov r6, r2
	add r0, r7, #0x60
	add r1, r7, #0x48
	mov r2, #0x18
	mov r5, r3
	bl MIi_CpuCopy32
	ldr r1, [r4, #0]
	ldr r0, [sp, #0x24]
	str r1, [r7, #0x30]
	ldr r1, [r4, #4]
	cmp r0, #0
	str r1, [r7, #0x34]
	ldr r0, [r4, #8]
	str r0, [r7, #0x38]
	beq _02163B20
	ldr r2, [sp, #0x20]
	mov r0, #0x3000
	umull r4, r3, r2, r0
	mov r1, #0
	mla r3, r2, r1, r3
	mov r1, r2, asr #0x1f
	adds r2, r4, #0x800
	mla r3, r1, r0, r3
	adc r0, r3, #0
	mov r1, r2, lsr #0xc
	ldr r2, [r7, #0x30]
	orr r1, r1, r0, lsl #20
	add r0, r2, r1
	str r0, [r7, #0x30]
_02163B20:
	ldr r9, [sp, #0x20]
	mov r1, #0xa000
	umull r0, lr, r9, r1
	mov r3, #0
	mov r2, #0x18000
	umull ip, r4, r9, r2
	adds r8, r0, #0x800
	mla lr, r9, r3, lr
	mov r0, r9, asr #0x1f
	mla r4, r9, r3, r4
	mla lr, r0, r1, lr
	adc r3, lr, #0
	mov r8, r8, lsr #0xc
	adds r1, ip, #0x800
	mla r4, r0, r2, r4
	ldr r0, [r7, #0x34]
	orr r8, r8, r3, lsl #20
	add r2, r0, r8
	adc r0, r4, #0
	mov r1, r1, lsr #0xc
	str r2, [r7, #0x34]
	orr r1, r1, r0, lsl #20
	ldr r0, =0x0000F8E4
	str r1, [r7, #0x3c]
	strh r0, [r7, #0x40]
	ldr r0, [r5, #8]
	ldrh r4, [r7, #0x5a]
	cmp r0, #0
	bge _02163C00
	ldr r0, [r5, #0]
	bl Math__Func_207B1A4
	cmp r0, #0x4000
	bhs _02163BD4
	ldr r1, [sp, #0x24]
	cmp r1, #0
	ldrne r2, =0x000031C7
	ldreq r2, =0x00002AAA
	cmp r0, r2
	blo _02163C00
	ldrh r1, [r7, #0x1a]
	sub r0, r0, r2
	add r0, r1, r0
	mov r0, r0, lsl #0x10
	mov r4, r0, lsr #0x10
	b _02163C00
_02163BD4:
	ldr r1, [sp, #0x24]
	cmp r1, #0
	ldrne r2, =0x00005C71
	ldreq r2, =0x00005555
	cmp r0, r2
	bhi _02163C00
	ldrh r1, [r7, #0x1a]
	sub r0, r0, r2
	add r0, r1, r0
	mov r0, r0, lsl #0x10
	mov r4, r0, lsr #0x10
_02163C00:
	ldr r0, =0x00000E38
	strh r4, [r7, #0x42]
	strh r0, [r7, #0x44]
	strh r6, [r7, #0x78]
	mov r0, #0
	strh r0, [r7, #0x7a]
	mov r0, #1
	str r0, [r7, #0x2c]
	ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Func_2163C3C(CViMapIcon *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, lr}
	mov r5, r0
	mov r4, r1
	add r0, r5, #0x60
	add r1, r5, #0x48
	mov r2, #0x18
	bl MIi_CpuCopy32
	add r1, r5, #0x30
	mov r0, #0
	mov r2, #0x18
	bl MIi_CpuClear32
	strh r4, [r5, #0x78]
	mov r0, #0
	strh r0, [r5, #0x7a]
	mov r0, #2
	str r0, [r5, #0x2c]
	ldmia sp!, {r3, r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Func_2163C80(CViMapIcon *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, r7, lr}
	sub sp, sp, #0x50
	mov r4, r0
	ldrh r1, [r4, #0x78]
	cmp r1, #0
	bne _02163CC4
	add r0, r4, #8
	add r1, r4, #0x60
	mov r2, #0x18
	bl MIi_CpuCopy32
	ldr r0, [r4, #0]
	cmp r0, #0
	bne _02163DC0
	mov r0, r4
	add r1, r4, #0x60
	bl ViMapIcon__Func_21643AC
	b _02163DC0
_02163CC4:
	ldrh r0, [r4, #0x7a]
	cmp r0, r1
	blo _02163D30
	ldr r0, [r4, #0x2c]
	mov r2, #0x18
	tst r0, #2
	beq _02163D08
	add r0, r4, #8
	add r1, r4, #0x60
	bl MIi_CpuCopy32
	ldr r0, [r4, #0]
	cmp r0, #0
	bne _02163D14
	mov r0, r4
	add r1, r4, #0x60
	bl ViMapIcon__Func_21643AC
	b _02163D14
_02163D08:
	add r0, r4, #0x30
	add r1, r4, #0x60
	bl MIi_CpuCopy32
_02163D14:
	ldr r0, [r4, #0x2c]
	tst r0, #1
	bne _02163DC0
	mov r0, #0
	strh r0, [r4, #0x78]
	str r0, [r4, #0x2c]
	b _02163DC0
_02163D30:
	mov r7, r1, lsl #5
	mov r6, r0, lsl #5
	mov r0, r7
	mov r1, r6
	mov r2, #0x2000
	bl Unknown2051334__Func_2051600
	ldr r1, [r4, #0x2c]
	mov r5, r0
	tst r1, #2
	beq _02163D94
	add r0, r4, #8
	add r1, r4, #0x60
	mov r2, #0x18
	bl MIi_CpuCopy32
	mov r0, r4
	add r1, r4, #0x60
	bl ViMapIcon__Func_21643AC
	mov r2, r6
	mov r3, r5
	str r7, [sp]
	add r1, r4, #0x60
	add r0, r4, #0x48
	str r1, [sp, #4]
	bl ViMapIcon__Func_21642AC
	b _02163DB4
_02163D94:
	mov r2, r6
	mov r3, r5
	str r7, [sp]
	add ip, r4, #0x60
	add r0, r4, #0x48
	add r1, r4, #0x30
	str ip, [sp, #4]
	bl ViMapIcon__Func_21642AC
_02163DB4:
	ldrh r0, [r4, #0x7a]
	add r0, r0, #1
	strh r0, [r4, #0x7a]
_02163DC0:
	ldr r0, [r4, #0x60]
	mov ip, #0
	str r0, [r4, #0xa0]
	ldr r0, [r4, #0x64]
	mov r1, #0x1000
	str r0, [r4, #0xa4]
	ldr r0, [r4, #0x68]
	ldr r3, =FX_SinCosTable_
	str r0, [r4, #0xa8]
	str ip, [r4, #0x94]
	str ip, [r4, #0x98]
	ldr r2, [r4, #0x6c]
	add r0, sp, #0x2c
	str r2, [r4, #0x9c]
	str ip, [r4, #0xac]
	str r1, [r4, #0xb0]
	str ip, [r4, #0xb4]
	ldrh r1, [r4, #0x74]
	strh r1, [r4, #0xb8]
	ldrh r1, [r4, #0x70]
	mov r1, r1, asr #4
	mov r2, r1, lsl #1
	add r1, r2, #1
	mov ip, r2, lsl #1
	mov r2, r1, lsl #1
	ldrsh r1, [r3, ip]
	ldrsh r2, [r3, r2]
	bl MTX_RotX33_
	ldrh r1, [r4, #0x72]
	ldr r3, =FX_SinCosTable_
	add r0, sp, #8
	sub r1, r1, #0x8000
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	mov r1, r1, asr #4
	mov r2, r1, lsl #1
	add r1, r2, #1
	mov ip, r2, lsl #1
	mov r2, r1, lsl #1
	ldrsh r1, [r3, ip]
	ldrsh r2, [r3, r2]
	bl MTX_RotY33_
	add r0, sp, #0x2c
	add r1, sp, #8
	mov r2, r0
	bl MTX_Concat33
	add r0, r4, #0x94
	add r1, sp, #0x2c
	mov r2, r0
	bl MTX_MultVec33
	add r0, r4, #0xac
	add r1, sp, #0x2c
	mov r2, r0
	bl MTX_MultVec33
	add r0, r4, #0x94
	add r1, r4, #0xa0
	mov r2, r0
	bl VEC_Add
	add sp, sp, #0x50
	ldmia sp!, {r3, r4, r5, r6, r7, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Func_2163EBC(CViMapIcon *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #0x54
	ldr r2, =0xBFFF0000
	ldr r1, =NNS_G3dGlb
	mov r4, r0
	str r2, [r1, #0xa0]
	ldr r0, [r4, #0xdc]
	ldr r1, =0x001FFFF8
	bl LoadDrawState
	add r1, sp, #4
	mov r0, #0
	mov r2, #0x50
	bl MIi_CpuClear16
	ldr r0, [r4, #0xdc]
	add r1, sp, #4
	bl GetDrawStateCameraProjection
	ldr r0, [r4, #0xdc]
	add r1, sp, #4
	bl GetDrawStateCameraView
	ldrh r1, [r4, #0xb8]
	add r0, sp, #4
	strh r1, [sp, #4]
	bl Camera3D__LoadState
	mov r0, #0
	ldr r2, =0x00007FFF
	str r0, [sp]
	mov r1, #0x1f
	mov r3, r0
	bl G3X_SetClearColor
	ldr r0, [r4, #0]
	cmp r0, #1
	addeq sp, sp, #0x54
	ldmeqia sp!, {r4, r5, pc}
	ldr r0, [r4, #0x94]
	ldr ip, =NNS_G3dGlb
	ldr lr, =NNS_G3dGlb+0x0000004C
	str r0, [ip, #0x240]
	ldr r1, [r4, #0x98]
	add r0, r4, #0x94
	str r1, [ip, #0x244]
	ldr r2, [r4, #0x9c]
	add r1, r4, #0xac
	str r2, [ip, #0x248]
	ldr r3, [r4, #0xac]
	add r2, r4, #0xa0
	str r3, [ip, #0x24c]
	ldr r5, [r4, #0xb0]
	mov r3, #0
	str r5, [ip, #0x250]
	ldr r5, [r4, #0xb4]
	str r5, [ip, #0x254]
	ldr r5, [r4, #0xa0]
	str r5, [ip, #0x258]
	ldr r5, [r4, #0xa4]
	str r5, [ip, #0x25c]
	ldr r5, [r4, #0xa8]
	str r5, [ip, #0x260]
	str lr, [sp]
	bl G3i_LookAt_
	ldr r0, =NNS_G3dGlb
	mov r5, #0
	ldr r1, [r0, #0xfc]
	bic r1, r1, #0xe8
	str r1, [r0, #0xfc]
_02163FBC:
	add r0, r4, r5, lsl #3
	ldrsh r1, [r0, #0xbc]
	ldrsh r2, [r0, #0xbe]
	ldrsh r3, [r0, #0xc0]
	mov r0, r5
	bl NNS_G3dGlbLightVector
	add r0, r4, r5, lsl #3
	ldrh r1, [r0, #0xc2]
	mov r0, r5
	bl NNS_G3dGlbLightColor
	add r5, r5, #1
	cmp r5, #4
	blt _02163FBC
	add sp, sp, #0x54
	ldmia sp!, {r4, r5, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Func_216400C(CViMapIcon *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, lr}
	mov r4, r0
	cmp r1, #8
	blt _02164030
	mov r1, r4
	mov r0, #0
	mov r2, #0x18
	bl MIi_CpuClear32
	ldmia sp!, {r4, pc}
_02164030:
	cmp r2, #2
	beq _021640C0
	mov r0, r1, lsl #0x10
	mov r0, r0, lsr #0x10
	bl HubConfig__GetDockBackInfo
	ldr r0, [r0, #0]
	cmp r0, #7
	bge _02164090
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bl HubConfig__GetDockStageConfig
	ldr r2, [r0, #0x14]
	mov r1, #0
	str r2, [r4, #0xc]
	str r1, [r4]
	str r1, [r4, #4]
	str r1, [r4, #8]
	ldrh r2, [r0, #0x18]
	mov r1, #0x8000
	ldr r0, =0x0000FFFF
	strh r2, [r4, #0x10]
	strh r1, [r4, #0x12]
	strh r0, [r4, #0x14]
	ldmia sp!, {r4, pc}
_02164090:
	mov r0, #0x80000
	str r0, [r4, #0xc]
	mov r0, #0
	str r0, [r4]
	str r0, [r4, #4]
	str r0, [r4, #8]
	strh r0, [r4, #0x10]
	mov r1, #0x8000
	ldr r0, =0x0000FFFF
	strh r1, [r4, #0x12]
	strh r0, [r4, #0x14]
	ldmia sp!, {r4, pc}
_021640C0:
	mov r0, #0x80000
	str r0, [r4, #0xc]
	mov r0, #0
	str r0, [r4]
	str r0, [r4, #4]
	str r0, [r4, #8]
	strh r0, [r4, #0x10]
	mov r1, #0x8000
	ldr r0, =0x0000FFFF
	strh r1, [r4, #0x12]
	strh r0, [r4, #0x14]
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Func_21640F4(CViMapIcon *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #0x50
	mov r5, r2
	mov r6, r1
	mov r8, r0
	add r1, sp, #0x30
	mov r0, r5
	mov r2, #0
	mov r4, r3
	bl GetDrawStateLight
	add r1, sp, #0x38
	mov r0, r5
	mov r2, #1
	bl GetDrawStateLight
	add r1, sp, #0x40
	mov r0, r5
	mov r2, #2
	bl GetDrawStateLight
	mov r0, r5
	add r1, sp, #0x48
	mov r2, #3
	bl GetDrawStateLight
	add r0, sp, #0x30
	mov r1, r8
	mov r2, #0x20
	bl MIi_CpuCopy32
	cmp r4, #0
	addne sp, sp, #0x50
	ldmneia sp!, {r4, r5, r6, r7, r8, pc}
	mov r0, r6, lsl #0x10
	mov r0, r0, lsr #0x10
	bl HubConfig__GetDockBackInfo
	ldrh r1, [r0, #0x18]
	ldr r3, =FX_SinCosTable_
	add r0, sp, #0xc
	mov r1, r1, asr #4
	mov r2, r1, lsl #1
	add r1, r2, #1
	mov r4, r2, lsl #1
	mov r2, r1, lsl #1
	ldrsh r1, [r3, r4]
	ldrsh r2, [r3, r2]
	bl MTX_RotY33_
	mov r7, #0
	add r6, sp, #0x30
	add r5, sp, #0
	add r4, sp, #0xc
_021641B0:
	mov r1, r7, lsl #3
	add r0, r6, r7, lsl #3
	ldrsh lr, [r6, r1]
	ldrsh ip, [r0, #2]
	ldrsh r3, [r0, #4]
	mov r0, r5
	mov r1, r4
	mov r2, r5
	str lr, [sp]
	str ip, [sp, #4]
	str r3, [sp, #8]
	bl MTX_MultVec33
	ldr r1, [sp]
	mov r0, r7, lsl #3
	strh r1, [r8, r0]
	ldr r0, [sp, #4]
	add r2, r8, r7, lsl #3
	strh r0, [r2, #2]
	ldr r1, [sp, #8]
	add r0, r6, r7, lsl #3
	strh r1, [r2, #4]
	ldrh r0, [r0, #6]
	add r7, r7, #1
	cmp r7, #4
	strh r0, [r2, #6]
	blt _021641B0
	add sp, sp, #0x50
	ldmia sp!, {r4, r5, r6, r7, r8, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Func_2164224(CViMapIcon *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r4, lr}
	mov r4, r0
	cmp r1, #8
	ldmgeia sp!, {r4, pc}
	mov r0, r1, lsl #0x10
	mov r0, r0, lsr #0x10
	bl HubConfig__GetDockBackInfo
	ldr r0, [r0, #0]
	cmp r0, #7
	ldmgeia sp!, {r4, pc}
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bl HubConfig__GetDockStageConfig
	ldr r1, [r0, #0x1c]
	str r1, [r4]
	ldr r1, [r0, #0x20]
	str r1, [r4, #4]
	ldr r1, [r0, #0x24]
	str r1, [r4, #8]
	ldr r1, [r0, #0x28]
	str r1, [r4, #0xc]
	ldr r1, [r0, #0x2c]
	str r1, [r4, #0x10]
	ldr r0, [r0, #0x30]
	str r0, [r4, #0x14]
	ldmia sp!, {r4, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Func_216428C(CViMapIcon *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, lr}
	sub sp, sp, #0x20
	ldr r0, [r0, #0xdc]
	add r1, sp, #0
	bl GetDrawStateCameraProjection
	ldrh r0, [sp]
	add sp, sp, #0x20
	ldmia sp!, {r3, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Func_21642AC(CViMapIcon *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
	mov r9, r0
	mov r8, r1
	ldr r1, [r8, #0]
	ldr r0, [r9, #0]
	mov r7, r2
	mov r6, r3
	cmp r0, r1
	ldr r5, [sp, #0x20]
	ldr r4, [sp, #0x24]
	beq _021642E0
	mov r2, r5
	bl Unknown2051334__Func_20516B8
_021642E0:
	str r0, [r4]
	ldr r1, [r8, #4]
	ldr r0, [r9, #4]
	cmp r0, r1
	beq _02164300
	mov r2, r5
	mov r3, r6
	bl Unknown2051334__Func_20516B8
_02164300:
	str r0, [r4, #4]
	ldr r1, [r8, #8]
	ldr r0, [r9, #8]
	cmp r0, r1
	beq _02164320
	mov r2, r5
	mov r3, r6
	bl Unknown2051334__Func_20516B8
_02164320:
	str r0, [r4, #8]
	ldr r1, [r8, #0xc]
	ldr r0, [r9, #0xc]
	cmp r0, r1
	beq _02164340
	mov r2, r5
	mov r3, r6
	bl Unknown2051334__Func_20516B8
_02164340:
	str r0, [r4, #0xc]
	ldrh r1, [r8, #0x10]
	ldrh r0, [r9, #0x10]
	cmp r0, r1
	beq _02164360
	mov r2, r5
	mov r3, r7
	bl Unknown2051334__Func_20516B8
_02164360:
	strh r0, [r4, #0x10]
	ldrh r1, [r8, #0x12]
	ldrh r0, [r9, #0x12]
	cmp r0, r1
	beq _02164380
	mov r2, r5
	mov r3, r7
	bl Unknown2051334__Func_20516B8
_02164380:
	strh r0, [r4, #0x12]
	ldrh r1, [r8, #0x14]
	ldrh r0, [r9, #0x14]
	cmp r0, r1
	streqh r0, [r4, #0x14]
	ldmeqia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
	mov r2, r5
	mov r3, r6
	bl Unknown2051334__Func_20516B8
	strh r0, [r4, #0x14]
	ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}

// clang-format on
#endif
}

NONMATCH_FUNC void ViMapIcon__Func_21643AC(CViMapIcon *work)
{
#ifdef NON_MATCHING

#else
    // clang-format off
	ldr r2, [r0, #0x7c]
	ldr r3, [r1, #0]
	cmp r3, r2
	strlt r2, [r1]
	blt _021643CC
	ldr r2, [r0, #0x88]
	cmp r3, r2
	strgt r2, [r1]
_021643CC:
	ldr r2, [r0, #0x80]
	ldr r3, [r1, #4]
	cmp r3, r2
	strlt r2, [r1, #4]
	blt _021643EC
	ldr r2, [r0, #0x8c]
	cmp r3, r2
	strgt r2, [r1, #4]
_021643EC:
	ldr r3, [r0, #0x84]
	ldr r2, [r1, #8]
	cmp r2, r3
	strlt r3, [r1, #8]
	bxlt lr
	ldr r0, [r0, #0x90]
	cmp r2, r0
	strgt r0, [r1, #8]
	bx lr

// clang-format on
#endif
}