	.include "asm/macros.inc"
	.include "global.inc"

	.bss

exBossSysAdminTask__dword_217626C: // 0x0217626C
    .space 0x04
	
exBossSysAdminTask__unk_2176270: // 0x02176270
    .space 0x04
	
exBossSysAdminBiforTask__TaskSingleton: // 0x02176274
    .space 0x04
	
exBossSysAdminTask__TaskSingleton: // 0x02176278
    .space 0x04
	
exBossSysAdminTask__unk_217627C: // 0x0217627C
    .space 0x04

exBossSysAdminTask__unk_2176280: // 0x02176280
    .space 0x04
	
	.text

	arm_func_start exBossSysAdminTask__RunTaskUnknownEvent
exBossSysAdminTask__RunTaskUnknownEvent: // 0x0215DC14
	stmdb sp!, {r3, lr}
	bl GetExTaskWorkCurrent_
	bl GetExTaskCurrent
	ldr r0, [r0, #8]
	blx r0
	ldmia sp!, {r3, pc}
	arm_func_end exBossSysAdminTask__RunTaskUnknownEvent

	arm_func_start exBossSysAdminTask__Action_StartMete0
exBossSysAdminTask__Action_StartMete0: // 0x0215DC2C
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	bl GetExTaskWorkCurrent_
	mov r4, r0
	add r0, r4, #0x6c
	mov r1, #1
	bl exBossHelpers__SetAnimation
	add r0, r4, #0x3f8
	bl exDrawReqTask__Func_21641F0
	bl exBossEffectFireTask__Create
	mov r0, #0
	str r0, [sp]
	ldr r1, _0215DC94 // =0x00000103
	str r1, [sp, #4]
	sub r1, r1, #0x104
	mov r2, r1
	mov r3, r1
	bl PlayVoiceClipEx
	bl exBossMeteAdminTask__Create
	bl GetExTaskCurrent
	ldr r1, _0215DC98 // =exBossSysAdminTask__Func_215DC9C
	str r1, [r0]
	bl exBossSysAdminTask__Func_215DC9C
	bl exBossSysAdminTask__RunTaskUnknownEvent
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_0215DC94: .word 0x00000103
_0215DC98: .word exBossSysAdminTask__Func_215DC9C
	arm_func_end exBossSysAdminTask__Action_StartMete0

	arm_func_start exBossSysAdminTask__Func_215DC9C
exBossSysAdminTask__Func_215DC9C: // 0x0215DC9C
	stmdb sp!, {r4, lr}
	bl GetExTaskWorkCurrent_
	mov r4, r0
	add r0, r4, #0x6c
	bl exDrawReqTask__Model__Animate
	add r0, r4, #0x6c
	bl exDrawReqTask__Model__IsAnimFinished
	cmp r0, #0
	beq _0215DCC8
	bl exBossSysAdminTask__Func_215DCE4
	ldmia sp!, {r4, pc}
_0215DCC8:
	add r0, r4, #0x6c
	bl exHitCheckTask__AddHitCheck
	add r0, r4, #0x6c
	add r1, r4, #0x3f8
	bl exDrawReqTask__AddRequest
	bl exBossSysAdminTask__RunTaskUnknownEvent
	ldmia sp!, {r4, pc}
	arm_func_end exBossSysAdminTask__Func_215DC9C

	arm_func_start exBossSysAdminTask__Func_215DCE4
exBossSysAdminTask__Func_215DCE4: // 0x0215DCE4
	stmdb sp!, {r4, lr}
	bl GetExTaskWorkCurrent_
	mov r4, r0
	mov r2, #0xd2
	add r0, r4, #0x6c
	mov r1, #2
	strh r2, [r4, #0x56]
	bl exBossHelpers__SetAnimation
	add r0, r4, #0x3f8
	bl exDrawReqTask__Func_2164218
	bl exBossMeteLockOnTask__Create
	bl GetExTaskCurrent
	ldr r1, _0215DD28 // =exBossSysAdminTask__Func_215DD2C
	str r1, [r0]
	bl exBossSysAdminTask__Func_215DD2C
	bl exBossSysAdminTask__RunTaskUnknownEvent
	ldmia sp!, {r4, pc}
	.align 2, 0
_0215DD28: .word exBossSysAdminTask__Func_215DD2C
	arm_func_end exBossSysAdminTask__Func_215DCE4

	arm_func_start exBossSysAdminTask__Func_215DD2C
exBossSysAdminTask__Func_215DD2C: // 0x0215DD2C
	stmdb sp!, {r4, lr}
	bl GetExTaskWorkCurrent_
	mov r4, r0
	add r0, r4, #0x6c
	bl exDrawReqTask__Model__Animate
	ldrsh r1, [r4, #0x56]
	sub r0, r1, #1
	strh r0, [r4, #0x56]
	cmp r1, #0
	bge _0215DD5C
	bl exBossSysAdminTask__Func_215DD78
	ldmia sp!, {r4, pc}
_0215DD5C:
	add r0, r4, #0x6c
	bl exHitCheckTask__AddHitCheck
	add r0, r4, #0x6c
	add r1, r4, #0x3f8
	bl exDrawReqTask__AddRequest
	bl exBossSysAdminTask__RunTaskUnknownEvent
	ldmia sp!, {r4, pc}
	arm_func_end exBossSysAdminTask__Func_215DD2C

	arm_func_start exBossSysAdminTask__Func_215DD78
exBossSysAdminTask__Func_215DD78: // 0x0215DD78
	stmdb sp!, {r4, lr}
	bl GetExTaskWorkCurrent_
	mov r4, r0
	mov r0, #0
	strh r0, [r4, #0x56]
	bl exBossEffectFireTask__Func_21581C0
	add r0, r4, #0x6c
	mov r1, #3
	bl exBossHelpers__SetAnimation
	add r0, r4, #0x3f8
	bl exDrawReqTask__Func_21641F0
	bl GetExTaskCurrent
	ldr r1, _0215DDBC // =exBossSysAdminTask__Func_215DDC0
	str r1, [r0]
	bl exBossSysAdminTask__Func_215DDC0
	bl exBossSysAdminTask__RunTaskUnknownEvent
	ldmia sp!, {r4, pc}
	.align 2, 0
_0215DDBC: .word exBossSysAdminTask__Func_215DDC0
	arm_func_end exBossSysAdminTask__Func_215DD78

	arm_func_start exBossSysAdminTask__Func_215DDC0
exBossSysAdminTask__Func_215DDC0: // 0x0215DDC0
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	bl GetExTaskWorkCurrent_
	mov r4, r0
	add r0, r4, #0x6c
	bl exDrawReqTask__Model__Animate
	ldr r0, [r4, #0x3b0]
	ldr r0, [r0, #0]
	cmp r0, #0xf000
	blt _0215DE1C
	mov ip, #0xc9
	sub r1, ip, #0xca
	mov r0, #0
	mov r2, r1
	mov r3, r1
	stmia sp, {r0, ip}
	bl PlaySfxEx
	bl GetExTaskCurrent
	ldr r1, _0215DE3C // =exBossSysAdminTask__Func_215DE40
	str r1, [r0]
	bl exBossSysAdminTask__Func_215DE40
	add sp, sp, #8
	ldmia sp!, {r4, pc}
_0215DE1C:
	add r0, r4, #0x6c
	bl exHitCheckTask__AddHitCheck
	add r0, r4, #0x6c
	add r1, r4, #0x3f8
	bl exDrawReqTask__AddRequest
	bl exBossSysAdminTask__RunTaskUnknownEvent
	add sp, sp, #8
	ldmia sp!, {r4, pc}
	.align 2, 0
_0215DE3C: .word exBossSysAdminTask__Func_215DE40
	arm_func_end exBossSysAdminTask__Func_215DDC0

	arm_func_start exBossSysAdminTask__Func_215DE40
exBossSysAdminTask__Func_215DE40: // 0x0215DE40
	stmdb sp!, {r4, lr}
	bl GetExTaskWorkCurrent_
	mov r4, r0
	add r0, r4, #0x6c
	bl exDrawReqTask__Model__Animate
	ldr r0, [r4, #0x3b0]
	ldr r0, [r0, #0]
	cmp r0, #0x23000
	bne _0215DE6C
	bl exBossSysAdminTask__Func_215DE88
	ldmia sp!, {r4, pc}
_0215DE6C:
	add r0, r4, #0x6c
	bl exHitCheckTask__AddHitCheck
	add r0, r4, #0x6c
	add r1, r4, #0x3f8
	bl exDrawReqTask__AddRequest
	bl exBossSysAdminTask__RunTaskUnknownEvent
	ldmia sp!, {r4, pc}
	arm_func_end exBossSysAdminTask__Func_215DE40

	arm_func_start exBossSysAdminTask__Func_215DE88
exBossSysAdminTask__Func_215DE88: // 0x0215DE88
	stmdb sp!, {r3, lr}
	bl GetExTaskWorkCurrent_
	bl exBossMeteMeteoTask__Create
	bl GetExTaskCurrent
	ldr r1, _0215DEAC // =exBossSysAdminTask__Func_215DEB0
	str r1, [r0]
	bl exBossSysAdminTask__Func_215DEB0
	bl exBossSysAdminTask__RunTaskUnknownEvent
	ldmia sp!, {r3, pc}
	.align 2, 0
_0215DEAC: .word exBossSysAdminTask__Func_215DEB0
	arm_func_end exBossSysAdminTask__Func_215DE88

	arm_func_start exBossSysAdminTask__Func_215DEB0
exBossSysAdminTask__Func_215DEB0: // 0x0215DEB0
	stmdb sp!, {r4, lr}
	bl GetExTaskWorkCurrent_
	mov r4, r0
	add r0, r4, #0x6c
	bl exDrawReqTask__Model__Animate
	add r0, r4, #0x6c
	bl exDrawReqTask__Model__IsAnimFinished
	cmp r0, #0
	beq _0215DEDC
	bl exBossSysAdminTask__Action_FinishMeteorAttack
	ldmia sp!, {r4, pc}
_0215DEDC:
	add r0, r4, #0x6c
	bl exHitCheckTask__AddHitCheck
	add r0, r4, #0x6c
	add r1, r4, #0x3f8
	bl exDrawReqTask__AddRequest
	bl exBossSysAdminTask__RunTaskUnknownEvent
	ldmia sp!, {r4, pc}
	arm_func_end exBossSysAdminTask__Func_215DEB0

	arm_func_start exBossSysAdminTask__Action_FinishMeteorAttack
exBossSysAdminTask__Action_FinishMeteorAttack: // 0x0215DEF8
	stmdb sp!, {r3, lr}
	bl GetExTaskWorkCurrent_
	ldr r0, [r0, #0x548]
	blx r0
	ldmia sp!, {r3, pc}
	arm_func_end exBossSysAdminTask__Action_FinishMeteorAttack

	arm_func_start exBossSysAdminTask__GetBossWork
exBossSysAdminTask__GetBossWork: // 0x0215DF0C
	ldr r0, _0215DF18 // =exBossSysAdminTask__dword_217626C
	ldr r0, [r0, #0x14]
	bx lr
	.align 2, 0
_0215DF18: .word exBossSysAdminTask__dword_217626C
	arm_func_end exBossSysAdminTask__GetBossWork

	arm_func_start exBossSysAdminTask__Func_215DF1C
exBossSysAdminTask__Func_215DF1C: // 0x0215DF1C
	ldr r0, _0215DF28 // =exBossSysAdminTask__dword_217626C
	ldr r0, [r0, #4]
	bx lr
	.align 2, 0
_0215DF28: .word exBossSysAdminTask__dword_217626C
	arm_func_end exBossSysAdminTask__Func_215DF1C

	arm_func_start exBossSysAdminTask__Func_215DF2C
exBossSysAdminTask__Func_215DF2C: // 0x0215DF2C
	ldr r1, _0215DF38 // =exBossSysAdminTask__dword_217626C
	str r0, [r1, #4]
	bx lr
	.align 2, 0
_0215DF38: .word exBossSysAdminTask__dword_217626C
	arm_func_end exBossSysAdminTask__Func_215DF2C

	arm_func_start exBossSysAdminTask__Main_Init
exBossSysAdminTask__Main_Init: // 0x0215DF3C
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	bl GetExTaskWorkCurrent_
	mov r5, r0
	bl GetCurrentTask
	ldr r1, _0215E028 // =exBossSysAdminTask__dword_217626C
	mov r2, #0
	str r0, [r1, #0xc]
	str r5, [r1, #0x14]
	mov r0, #1
	strh r2, [r5, #0x64]
	bl exBossSysAdminTask__Func_215DF2C
	bl exBossSysAdminBiforTask__Create
	ldr r1, _0215E02C // =0x0217431C
	add r0, r5, #0x6c
	ldr r2, [r1, #0]
	str r2, [r5, #0x54c]
	ldr r1, [r1, #0]
	str r1, [r5, #0x548]
	bl exBossHelpers__LoadAssets
	add r0, r5, #0x3f8
	mov r1, #0xa800
	bl exDrawReqTask__SetConfigPriority
	add r0, r5, #0x3f8
	bl exDrawReqTask__Func_2164218
	mov r7, #0
	add r8, r5, #0x1d0
	mov r6, r7
	mov r4, r7
_0215DFAC:
	mov r0, r8
	mov r1, r6
	bl SetPaletteAnimation
	add r0, r7, #1
	mov r0, r0, lsl #0x10
	mov r7, r0, asr #0x10
	strh r4, [r5, #0x5a]
	cmp r7, #0xf
	add r8, r8, #0x20
	blt _0215DFAC
	ldrb r2, [r5, #2]
	mov r1, #0x64000
	mov r0, #0x800
	bic r2, r2, #1
	strb r2, [r5, #2]
	str r1, [r5, #0x3c0]
	str r0, [r5, #0x3c]
	ldrb r1, [r5, #1]
	mov r0, #1
	orr r1, r1, #0x80
	strb r1, [r5, #1]
	strh r4, [r5, #0x60]
	str r4, [r5, #0x48]
	str r4, [r5, #0x4c]
	str r4, [r5, #0x50]
	strh r4, [r5, #0x54]
	str r0, [r5, #4]
	bl GetExTaskCurrent
	ldr r1, _0215E030 // =exBossSysAdminTask__Main_WaitForTitleCard
	str r1, [r0]
	ldmia sp!, {r4, r5, r6, r7, r8, pc}
	.align 2, 0
_0215E028: .word exBossSysAdminTask__dword_217626C
_0215E02C: .word 0x0217431C
_0215E030: .word exBossSysAdminTask__Main_WaitForTitleCard
	arm_func_end exBossSysAdminTask__Main_Init

	arm_func_start exBossSysAdminTask__Func8
exBossSysAdminTask__Func8: // 0x0215E034
	stmdb sp!, {r3, lr}
	bl GetExTaskWorkCurrent_
	bl CheckExStageFinished
	cmp r0, #0
	ldmeqia sp!, {r3, pc}
	bl GetExTaskCurrent
	ldr r1, _0215E05C // =exBossSysAdminTask__Main_Blank
	str r1, [r0]
	bl exBossSysAdminTask__Main_Blank
	ldmia sp!, {r3, pc}
	.align 2, 0
_0215E05C: .word exBossSysAdminTask__Main_Blank
	arm_func_end exBossSysAdminTask__Func8

	arm_func_start exBossSysAdminTask__Destructor
exBossSysAdminTask__Destructor: // 0x0215E060
	stmdb sp!, {r3, lr}
	bl GetExTaskWorkCurrent_
	add r0, r0, #0x6c
	bl exBossHelpers__Func_2154390
	ldr r0, _0215E080 // =exBossSysAdminTask__dword_217626C
	mov r1, #0
	str r1, [r0, #0xc]
	ldmia sp!, {r3, pc}
	.align 2, 0
_0215E080: .word exBossSysAdminTask__dword_217626C
	arm_func_end exBossSysAdminTask__Destructor

	arm_func_start exBossSysAdminTask__Main_WaitForTitleCard
exBossSysAdminTask__Main_WaitForTitleCard: // 0x0215E084
	stmdb sp!, {r4, lr}
	bl GetExTaskWorkCurrent_
	mov r4, r0
	add r0, r4, #0x6c
	bl exDrawReqTask__Model__Animate
	bl GetExSystemStatus
	ldrb r0, [r0, #3]
	cmp r0, #4
	bne _0215E0B0
	bl exBossSysAdminTask__Action_InitialFlee
	ldmia sp!, {r4, pc}
_0215E0B0:
	add r0, r4, #0x6c
	add r1, r4, #0x3f8
	bl exDrawReqTask__AddRequest
	bl GetExTaskCurrent
	ldr r0, [r0, #8]
	blx r0
	ldmia sp!, {r4, pc}
	arm_func_end exBossSysAdminTask__Main_WaitForTitleCard

	arm_func_start exBossSysAdminTask__Action_InitialFlee
exBossSysAdminTask__Action_InitialFlee: // 0x0215E0CC
	stmdb sp!, {r3, lr}
	bl GetExTaskWorkCurrent_
	bl GetExTaskCurrent
	ldr r1, _0215E0E8 // =exBossSysAdminTask__Main_InitialFlee
	str r1, [r0]
	bl exBossSysAdminTask__Main_InitialFlee
	ldmia sp!, {r3, pc}
	.align 2, 0
_0215E0E8: .word exBossSysAdminTask__Main_InitialFlee
	arm_func_end exBossSysAdminTask__Action_InitialFlee

	arm_func_start exBossSysAdminTask__Main_InitialFlee
exBossSysAdminTask__Main_InitialFlee: // 0x0215E0EC
	stmdb sp!, {r4, lr}
	bl GetExTaskWorkCurrent_
	mov r4, r0
	add r0, r4, #0x6c
	bl exDrawReqTask__Model__Animate
	ldr r1, [r4, #0x3c0]
	ldr r0, [r4, #0x3c]
	add r0, r1, r0
	str r0, [r4, #0x3c0]
	ldr r1, [r4, #0x3bc]
	cmp r1, #0x5a000
	bge _0215E138
	mov r0, #0x5a000
	rsb r0, r0, #0
	cmp r1, r0
	ble _0215E138
	ldr r0, [r4, #0x3c0]
	cmp r0, #0xc8000
	blt _0215E140
_0215E138:
	bl exBossSysAdminTask__Action_WaitForFlag215DF1C
	ldmia sp!, {r4, pc}
_0215E140:
	add r0, r4, #0x6c
	add r1, r4, #0x3f8
	bl exDrawReqTask__AddRequest
	bl GetExTaskCurrent
	ldr r0, [r0, #8]
	blx r0
	ldmia sp!, {r4, pc}
	arm_func_end exBossSysAdminTask__Main_InitialFlee

	arm_func_start exBossSysAdminTask__Action_WaitForFlag215DF1C
exBossSysAdminTask__Action_WaitForFlag215DF1C: // 0x0215E15C
	stmdb sp!, {r3, lr}
	bl GetExTaskWorkCurrent_
	mov r0, #0
	bl exBossSysAdminTask__Func_215DF2C
	bl GetExTaskCurrent
	ldr r1, _0215E180 // =exBossSysAdminTask__Main_WaitForFlag215DF1C
	str r1, [r0]
	bl exBossSysAdminTask__Main_WaitForFlag215DF1C
	ldmia sp!, {r3, pc}
	.align 2, 0
_0215E180: .word exBossSysAdminTask__Main_WaitForFlag215DF1C
	arm_func_end exBossSysAdminTask__Action_WaitForFlag215DF1C

	arm_func_start exBossSysAdminTask__Main_WaitForFlag215DF1C
exBossSysAdminTask__Main_WaitForFlag215DF1C: // 0x0215E184
	stmdb sp!, {r3, lr}
	bl GetExTaskWorkCurrent_
	bl exBossSysAdminTask__Func_215DF1C
	cmp r0, #0
	beq _0215E1A0
	bl exBossSysAdminTask__Action_RegenerateHealth
	ldmia sp!, {r3, pc}
_0215E1A0:
	bl GetExTaskCurrent
	ldr r0, [r0, #8]
	blx r0
	ldmia sp!, {r3, pc}
	arm_func_end exBossSysAdminTask__Main_WaitForFlag215DF1C

	arm_func_start exBossSysAdminTask__Action_RegenerateHealth
exBossSysAdminTask__Action_RegenerateHealth: // 0x0215E1B0
	stmdb sp!, {r3, lr}
	bl GetExTaskWorkCurrent_
	bl GetExSystemStatus
	mov r1, #5
	strb r1, [r0, #3]
	bl exBossSysAdminTask__GetBossWork
	mov r1, #0
	strh r1, [r0, #0x62]
	bl GetExTaskCurrent
	ldr r1, _0215E1E4 // =exBossSysAdminTask__Main_RegenerateHealth
	str r1, [r0]
	bl exBossSysAdminTask__Main_RegenerateHealth
	ldmia sp!, {r3, pc}
	.align 2, 0
_0215E1E4: .word exBossSysAdminTask__Main_RegenerateHealth
	arm_func_end exBossSysAdminTask__Action_RegenerateHealth

	arm_func_start exBossSysAdminTask__Main_RegenerateHealth
exBossSysAdminTask__Main_RegenerateHealth: // 0x0215E1E8
	stmdb sp!, {r4, lr}
	bl GetExTaskWorkCurrent_
	mov r4, r0
	add r0, r4, #0x6c
	bl exDrawReqTask__Model__Animate
	bl exBossSysAdminTask__MoveRandom
	ldr r0, _0215E290 // =exBossSysAdminTask__dword_217626C
	ldrsh r1, [r0, #0]
	cmp r1, #0xaf
	bge _0215E22C
	add r1, r1, #1
	strh r1, [r0]
	bl exBossSysAdminTask__GetBossWork
	ldr r1, _0215E290 // =exBossSysAdminTask__dword_217626C
	ldrsh r1, [r1, #0]
	strh r1, [r0, #0x62]
	b _0215E274
_0215E22C:
	bl exBossSysAdminTask__GetBossWork
	mov r1, #0xb0
	strh r1, [r0, #0x62]
	ldr r0, [r4, #0x3c0]
	cmp r0, #0x6e000
	bgt _0215E274
	ldr r0, _0215E290 // =exBossSysAdminTask__dword_217626C
	mov r1, #0
	strh r1, [r0]
	bl GetExSystemStatus
	mov r1, #6
	strb r1, [r0, #3]
	bl exBossSysAdminTask__SetNextTimer
	bl GetExTaskCurrent
	ldr r1, _0215E294 // =exBossSysAdminTask__Main_DragonAttackIdle
	str r1, [r0]
	bl exBossSysAdminTask__Main_DragonAttackIdle
	ldmia sp!, {r4, pc}
_0215E274:
	add r0, r4, #0x6c
	add r1, r4, #0x3f8
	bl exDrawReqTask__AddRequest
	bl GetExTaskCurrent
	ldr r0, [r0, #8]
	blx r0
	ldmia sp!, {r4, pc}
	.align 2, 0
_0215E290: .word exBossSysAdminTask__dword_217626C
_0215E294: .word exBossSysAdminTask__Main_DragonAttackIdle
	arm_func_end exBossSysAdminTask__Main_RegenerateHealth

	arm_func_start exBossSysAdminTask__Action_DragonAttackIdle
exBossSysAdminTask__Action_DragonAttackIdle: // 0x0215E298
	stmdb sp!, {r4, lr}
	bl GetExTaskWorkCurrent_
	mov r4, r0
	add r0, r4, #0x6c
	mov r1, #0
	bl exBossHelpers__SetAnimation
	add r0, r4, #0x3f8
	bl exDrawReqTask__Func_2164218
	bl exBossSysAdminTask__SetNextTimer
	bl GetExTaskCurrent
	ldr r1, _0215E2D0 // =exBossSysAdminTask__Main_DragonAttackIdle
	str r1, [r0]
	bl exBossSysAdminTask__Main_DragonAttackIdle
	ldmia sp!, {r4, pc}
	.align 2, 0
_0215E2D0: .word exBossSysAdminTask__Main_DragonAttackIdle
	arm_func_end exBossSysAdminTask__Action_DragonAttackIdle

	arm_func_start exBossSysAdminTask__Main_DragonAttackIdle
exBossSysAdminTask__Main_DragonAttackIdle: // 0x0215E2D4
	stmdb sp!, {r4, r5, r6, lr}
	bl GetExTaskWorkCurrent_
	mov r4, r0
	add r0, r4, #0x6c
	bl exDrawReqTask__Model__Animate
	ldrb r0, [r4, #1]
	orr r0, r0, #0x80
	strb r0, [r4, #1]
	bl exBossSysAdminTask__MoveRandom
	ldrsh r0, [r4, #0x5e]
	cmp r0, #0
	bgt _0215E3DC
	bl exBossFireDoraTask__AnyActive
	cmp r0, #0
	bne _0215E3C8
	ldr r1, _0215E408 // =_mt_math_rand
	ldr r0, _0215E40C // =0x0217431C
	ldr r5, [r1, #0]
	ldr r2, _0215E410 // =0x00196225
	ldr r3, _0215E414 // =0x3C6EF35F
	ldr r6, _0215E418 // =0x51EB851F
	mla r2, r5, r2, r3
	mov r3, r2, lsr #0x10
	mov r3, r3, lsl #0x10
	mov r5, r3, lsr #0x10
	mov ip, r5, lsr #0x1f
	smull lr, r5, r6, r5
	add r5, ip, r5, asr #5
	mov lr, #0x64
	smull r5, ip, lr, r5
	ldr r0, [r0, #4]
	str r2, [r1]
	str r0, [r4, #0x548]
	rsb r5, r5, r3, lsr #16
	bl GetExPlayerWorker
	ldrb r0, [r0, #0x6a]
	mov r0, r0, lsl #0x1f
	movs r0, r0, lsr #0x1f
	bne _0215E39C
	cmp r5, #0x32
	blt _0215E388
	ldrb r0, [r4, #2]
	orr r0, r0, #0x20
	strb r0, [r4, #2]
	b _0215E3E4
_0215E388:
	bl GetExTaskCurrent
	ldr r1, _0215E41C // =exBossSysAdminTask__Main_StartFw0_3
	str r1, [r0]
	bl exBossSysAdminTask__Main_StartFw0_3
	ldmia sp!, {r4, r5, r6, pc}
_0215E39C:
	cmp r5, #0x32
	blt _0215E3B4
	ldrb r0, [r4, #2]
	orr r0, r0, #0x20
	strb r0, [r4, #2]
	b _0215E3E4
_0215E3B4:
	bl GetExTaskCurrent
	ldr r1, _0215E41C // =exBossSysAdminTask__Main_StartFw0_3
	str r1, [r0]
	bl exBossSysAdminTask__Main_StartFw0_3
	ldmia sp!, {r4, r5, r6, pc}
_0215E3C8:
	bl GetExTaskCurrent
	ldr r1, _0215E41C // =exBossSysAdminTask__Main_StartFw0_3
	str r1, [r0]
	bl exBossSysAdminTask__Main_StartFw0_3
	ldmia sp!, {r4, r5, r6, pc}
_0215E3DC:
	sub r0, r0, #1
	strh r0, [r4, #0x5e]
_0215E3E4:
	add r0, r4, #0x6c
	add r1, r4, #0x3f8
	bl exDrawReqTask__AddRequest
	add r0, r4, #0x6c
	bl exHitCheckTask__AddHitCheck
	bl GetExTaskCurrent
	ldr r0, [r0, #8]
	blx r0
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_0215E408: .word _mt_math_rand
_0215E40C: .word 0x0217431C
_0215E410: .word 0x00196225
_0215E414: .word 0x3C6EF35F
_0215E418: .word 0x51EB851F
_0215E41C: .word exBossSysAdminTask__Main_StartFw0_3
	arm_func_end exBossSysAdminTask__Main_DragonAttackIdle

	arm_func_start exBossSysAdminTask__Action_StartFw0_3
exBossSysAdminTask__Action_StartFw0_3: // 0x0215E420
	stmdb sp!, {r4, lr}
	bl GetExTaskWorkCurrent_
	mov r4, r0
	add r0, r4, #0x6c
	mov r1, #0
	bl exBossHelpers__SetAnimation
	add r0, r4, #0x3f8
	bl exDrawReqTask__Func_2164218
	bl GetExTaskCurrent
	ldr r1, _0215E454 // =exBossSysAdminTask__Main_StartFw0_3
	str r1, [r0]
	bl exBossSysAdminTask__Main_StartFw0_3
	ldmia sp!, {r4, pc}
	.align 2, 0
_0215E454: .word exBossSysAdminTask__Main_StartFw0_3
	arm_func_end exBossSysAdminTask__Action_StartFw0_3

	arm_func_start exBossSysAdminTask__Main_StartFw0_3
exBossSysAdminTask__Main_StartFw0_3: // 0x0215E458
	stmdb sp!, {r4, r5, r6, lr}
	bl GetExTaskWorkCurrent_
	mov r4, r0
	add r0, r4, #0x6c
	bl exDrawReqTask__Model__Animate
	ldrb r0, [r4, #1]
	orr r0, r0, #0x80
	strb r0, [r4, #1]
	bl exBossSysAdminTask__MoveRandom
	ldrsh r0, [r4, #0x5e]
	cmp r0, #0
	bgt _0215E540
	ldr r1, _0215E56C // =_mt_math_rand
	ldr r0, _0215E570 // =0x0217431C
	ldr r5, [r1, #0]
	ldr r2, _0215E574 // =0x00196225
	ldr r3, _0215E578 // =0x3C6EF35F
	ldr r6, _0215E57C // =0x51EB851F
	mla r2, r5, r2, r3
	mov r3, r2, lsr #0x10
	mov r3, r3, lsl #0x10
	mov r5, r3, lsr #0x10
	mov ip, r5, lsr #0x1f
	smull lr, r5, r6, r5
	add r5, ip, r5, asr #5
	mov lr, #0x64
	smull r5, ip, lr, r5
	ldr r0, [r0, #0]
	str r2, [r1]
	str r0, [r4, #0x548]
	rsb r5, r5, r3, lsr #16
	bl GetExPlayerWorker
	ldrb r0, [r0, #0x6a]
	mov r0, r0, lsl #0x1f
	movs r0, r0, lsr #0x1f
	bne _0215E514
	cmp r5, #0x46
	blt _0215E500
	ldrb r0, [r4, #2]
	orr r0, r0, #4
	strb r0, [r4, #2]
	b _0215E548
_0215E500:
	bge _0215E548
	ldrb r0, [r4, #2]
	orr r0, r0, #8
	strb r0, [r4, #2]
	b _0215E548
_0215E514:
	cmp r5, #0x46
	blt _0215E52C
	ldrb r0, [r4, #2]
	orr r0, r0, #4
	strb r0, [r4, #2]
	b _0215E548
_0215E52C:
	bge _0215E548
	ldrb r0, [r4, #2]
	orr r0, r0, #8
	strb r0, [r4, #2]
	b _0215E548
_0215E540:
	sub r0, r0, #1
	strh r0, [r4, #0x5e]
_0215E548:
	add r0, r4, #0x6c
	add r1, r4, #0x3f8
	bl exDrawReqTask__AddRequest
	add r0, r4, #0x6c
	bl exHitCheckTask__AddHitCheck
	bl GetExTaskCurrent
	ldr r0, [r0, #8]
	blx r0
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_0215E56C: .word _mt_math_rand
_0215E570: .word 0x0217431C
_0215E574: .word 0x00196225
_0215E578: .word 0x3C6EF35F
_0215E57C: .word 0x51EB851F
	arm_func_end exBossSysAdminTask__Main_StartFw0_3

	arm_func_start exBossSysAdminTask__Action_StartFw0_4
exBossSysAdminTask__Action_StartFw0_4: // 0x0215E580
	stmdb sp!, {r4, lr}
	bl GetExTaskWorkCurrent_
	mov r4, r0
	add r0, r4, #0x6c
	mov r1, #0
	bl exBossHelpers__SetAnimation
	add r0, r4, #0x3f8
	bl exDrawReqTask__Func_2164218
	bl GetExTaskCurrent
	ldr r1, _0215E5B4 // =exBossSysAdminTask__Main_StartFw0_4
	str r1, [r0]
	bl exBossSysAdminTask__Main_StartFw0_4
	ldmia sp!, {r4, pc}
	.align 2, 0
_0215E5B4: .word exBossSysAdminTask__Main_StartFw0_4
	arm_func_end exBossSysAdminTask__Action_StartFw0_4

	arm_func_start exBossSysAdminTask__Main_StartFw0_4
exBossSysAdminTask__Main_StartFw0_4: // 0x0215E5B8
	stmdb sp!, {r4, lr}
	bl GetExTaskWorkCurrent_
	mov r4, r0
	add r0, r4, #0x6c
	bl exDrawReqTask__Model__Animate
	ldrb r0, [r4, #1]
	orr r0, r0, #0x80
	strb r0, [r4, #1]
	bl exBossSysAdminTask__MoveRandom
	ldrsh r0, [r4, #0x5e]
	cmp r0, #0
	bgt _0215E648
	ldr r3, _0215E674 // =_mt_math_rand
	ldr r2, _0215E678 // =0x0217431C
	ldr ip, [r3]
	ldr r0, _0215E67C // =0x00196225
	ldr r1, _0215E680 // =0x3C6EF35F
	ldr r2, [r2, #0]
	mla r0, ip, r0, r1
	str r0, [r3]
	str r2, [r4, #0x548]
	bl GetExPlayerWorker
	ldrb r0, [r0, #0x6a]
	mov r0, r0, lsl #0x1f
	movs r0, r0, lsr #0x1f
	bne _0215E634
	bl GetExTaskCurrent
	ldr r1, _0215E684 // =exBossSysAdminTask__Main_DragonAttackIdle
	str r1, [r0]
	bl exBossSysAdminTask__Main_DragonAttackIdle
	ldmia sp!, {r4, pc}
_0215E634:
	bl GetExTaskCurrent
	ldr r1, _0215E684 // =exBossSysAdminTask__Main_DragonAttackIdle
	str r1, [r0]
	bl exBossSysAdminTask__Main_DragonAttackIdle
	ldmia sp!, {r4, pc}
_0215E648:
	sub r2, r0, #1
	add r0, r4, #0x6c
	add r1, r4, #0x3f8
	strh r2, [r4, #0x5e]
	bl exDrawReqTask__AddRequest
	add r0, r4, #0x6c
	bl exHitCheckTask__AddHitCheck
	bl GetExTaskCurrent
	ldr r0, [r0, #8]
	blx r0
	ldmia sp!, {r4, pc}
	.align 2, 0
_0215E674: .word _mt_math_rand
_0215E678: .word 0x0217431C
_0215E67C: .word 0x00196225
_0215E680: .word 0x3C6EF35F
_0215E684: .word exBossSysAdminTask__Main_DragonAttackIdle
	arm_func_end exBossSysAdminTask__Main_StartFw0_4

	arm_func_start exBossSysAdminTask__Action_StartFw0_5
exBossSysAdminTask__Action_StartFw0_5: // 0x0215E688
	stmdb sp!, {r4, lr}
	bl GetExTaskWorkCurrent_
	mov r4, r0
	add r0, r4, #0x6c
	mov r1, #0
	bl exBossHelpers__SetAnimation
	add r0, r4, #0x3f8
	bl exDrawReqTask__Func_2164218
	bl exBossSysAdminTask__SetNextTimer
	bl GetExTaskCurrent
	ldr r1, _0215E6C0 // =exBossSysAdminTask__Main_StartFw0_5
	str r1, [r0]
	bl exBossSysAdminTask__Main_StartFw0_5
	ldmia sp!, {r4, pc}
	.align 2, 0
_0215E6C0: .word exBossSysAdminTask__Main_StartFw0_5
	arm_func_end exBossSysAdminTask__Action_StartFw0_5

	arm_func_start exBossSysAdminTask__Main_StartFw0_5
exBossSysAdminTask__Main_StartFw0_5: // 0x0215E6C4
	stmdb sp!, {r4, r5, r6, lr}
	bl GetExTaskWorkCurrent_
	mov r4, r0
	add r0, r4, #0x6c
	bl exDrawReqTask__Model__Animate
	ldrb r0, [r4, #1]
	orr r0, r0, #0x80
	strb r0, [r4, #1]
	bl exBossSysAdminTask__MoveRandom
	ldrsh r0, [r4, #0x5e]
	cmp r0, #0
	bgt _0215E7B8
	bl exBossFireDoraTask__AnyActive
	cmp r0, #0
	bne _0215E7A4
	bl exBossHomingLaserTask__AnyActive
	cmp r0, #0
	bne _0215E7A4
	ldr r1, _0215E7E4 // =_mt_math_rand
	ldr r0, _0215E7E8 // =0x0217431C
	ldr r5, [r1, #0]
	ldr r2, _0215E7EC // =0x00196225
	ldr r3, _0215E7F0 // =0x3C6EF35F
	ldr r6, _0215E7F4 // =0x51EB851F
	mla r2, r5, r2, r3
	mov r3, r2, lsr #0x10
	mov r3, r3, lsl #0x10
	mov r5, r3, lsr #0x10
	mov ip, r5, lsr #0x1f
	smull lr, r5, r6, r5
	add r5, ip, r5, asr #5
	mov lr, #0x64
	smull r5, ip, lr, r5
	ldr r0, [r0, #0x10]
	str r2, [r1]
	str r0, [r4, #0x548]
	rsb r5, r5, r3, lsr #16
	bl GetExPlayerWorker
	ldrb r0, [r0, #0x6a]
	mov r0, r0, lsl #0x1f
	movs r0, r0, lsr #0x1f
	bne _0215E788
	ldrb r0, [r4, #2]
	cmp r5, #0x1e
	orrge r0, r0, #0x20
	strgeb r0, [r4, #2]
	orrlt r0, r0, #0x10
	strltb r0, [r4, #2]
	b _0215E7C0
_0215E788:
	ldrb r0, [r4, #2]
	cmp r5, #0x1e
	orrge r0, r0, #0x20
	strgeb r0, [r4, #2]
	orrlt r0, r0, #0x10
	strltb r0, [r4, #2]
	b _0215E7C0
_0215E7A4:
	bl GetExTaskCurrent
	ldr r1, _0215E7F8 // =exBossSysAdminTask__Main_StartFw0_6
	str r1, [r0]
	bl exBossSysAdminTask__Main_StartFw0_6
	ldmia sp!, {r4, r5, r6, pc}
_0215E7B8:
	sub r0, r0, #1
	strh r0, [r4, #0x5e]
_0215E7C0:
	add r0, r4, #0x6c
	add r1, r4, #0x3f8
	bl exDrawReqTask__AddRequest
	add r0, r4, #0x6c
	bl exHitCheckTask__AddHitCheck
	bl GetExTaskCurrent
	ldr r0, [r0, #8]
	blx r0
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_0215E7E4: .word _mt_math_rand
_0215E7E8: .word 0x0217431C
_0215E7EC: .word 0x00196225
_0215E7F0: .word 0x3C6EF35F
_0215E7F4: .word 0x51EB851F
_0215E7F8: .word exBossSysAdminTask__Main_StartFw0_6
	arm_func_end exBossSysAdminTask__Main_StartFw0_5

	arm_func_start exBossSysAdminTask__Action_StartFw0_6
exBossSysAdminTask__Action_StartFw0_6: // 0x0215E7FC
	stmdb sp!, {r4, lr}
	bl GetExTaskWorkCurrent_
	mov r4, r0
	add r0, r4, #0x6c
	mov r1, #0
	bl exBossHelpers__SetAnimation
	add r0, r4, #0x3f8
	bl exDrawReqTask__Func_2164218
	bl GetExTaskCurrent
	ldr r1, _0215E830 // =exBossSysAdminTask__Main_StartFw0_6
	str r1, [r0]
	bl exBossSysAdminTask__Main_StartFw0_6
	ldmia sp!, {r4, pc}
	.align 2, 0
_0215E830: .word exBossSysAdminTask__Main_StartFw0_6
	arm_func_end exBossSysAdminTask__Action_StartFw0_6

	arm_func_start exBossSysAdminTask__Main_StartFw0_6
exBossSysAdminTask__Main_StartFw0_6: // 0x0215E834
	stmdb sp!, {r4, r5, r6, lr}
	bl GetExTaskWorkCurrent_
	mov r4, r0
	add r0, r4, #0x6c
	bl exDrawReqTask__Model__Animate
	ldrb r0, [r4, #1]
	orr r0, r0, #0x80
	strb r0, [r4, #1]
	bl exBossSysAdminTask__MoveRandom
	ldrsh r0, [r4, #0x5e]
	cmp r0, #0
	bgt _0215E95C
	ldr r1, _0215E988 // =_mt_math_rand
	ldr r0, _0215E98C // =0x0217431C
	ldr r5, [r1, #0]
	ldr r2, _0215E990 // =0x00196225
	ldr r3, _0215E994 // =0x3C6EF35F
	ldr r6, _0215E998 // =0x51EB851F
	mla r2, r5, r2, r3
	mov r3, r2, lsr #0x10
	mov r3, r3, lsl #0x10
	mov r5, r3, lsr #0x10
	mov ip, r5, lsr #0x1f
	smull lr, r5, r6, r5
	add r5, ip, r5, asr #5
	mov lr, #0x64
	smull r5, ip, lr, r5
	ldr r0, [r0, #0x14]
	str r2, [r1]
	str r0, [r4, #0x548]
	rsb r5, r5, r3, lsr #16
	bl GetExPlayerWorker
	ldrb r0, [r0, #0x6a]
	mov r0, r0, lsl #0x1f
	movs r0, r0, lsr #0x1f
	bne _0215E910
	cmp r5, #0x1e
	bge _0215E8DC
	ldrb r0, [r4, #2]
	orr r0, r0, #4
	strb r0, [r4, #2]
	b _0215E964
_0215E8DC:
	blt _0215E8F8
	cmp r5, #0x46
	bge _0215E8F8
	ldrb r0, [r4, #2]
	orr r0, r0, #8
	strb r0, [r4, #2]
	b _0215E964
_0215E8F8:
	cmp r5, #0x46
	blt _0215E964
	ldrb r0, [r4, #2]
	orr r0, r0, #0x40
	strb r0, [r4, #2]
	b _0215E964
_0215E910:
	cmp r5, #0x1e
	bge _0215E928
	ldrb r0, [r4, #2]
	orr r0, r0, #4
	strb r0, [r4, #2]
	b _0215E964
_0215E928:
	blt _0215E944
	cmp r5, #0x46
	bge _0215E944
	ldrb r0, [r4, #2]
	orr r0, r0, #8
	strb r0, [r4, #2]
	b _0215E964
_0215E944:
	cmp r5, #0x46
	blt _0215E964
	ldrb r0, [r4, #2]
	orr r0, r0, #0x40
	strb r0, [r4, #2]
	b _0215E964
_0215E95C:
	sub r0, r0, #1
	strh r0, [r4, #0x5e]
_0215E964:
	add r0, r4, #0x6c
	add r1, r4, #0x3f8
	bl exDrawReqTask__AddRequest
	add r0, r4, #0x6c
	bl exHitCheckTask__AddHitCheck
	bl GetExTaskCurrent
	ldr r0, [r0, #8]
	blx r0
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_0215E988: .word _mt_math_rand
_0215E98C: .word 0x0217431C
_0215E990: .word 0x00196225
_0215E994: .word 0x3C6EF35F
_0215E998: .word 0x51EB851F
	arm_func_end exBossSysAdminTask__Main_StartFw0_6

	arm_func_start exBossSysAdminTask__Action_StartFw0_7
exBossSysAdminTask__Action_StartFw0_7: // 0x0215E99C
	stmdb sp!, {r4, lr}
	bl GetExTaskWorkCurrent_
	mov r4, r0
	add r0, r4, #0x6c
	mov r1, #0
	bl exBossHelpers__SetAnimation
	add r0, r4, #0x3f8
	bl exDrawReqTask__Func_2164218
	bl GetExTaskCurrent
	ldr r1, _0215E9D0 // =exBossSysAdminTask__Main_StartFw0_7
	str r1, [r0]
	bl exBossSysAdminTask__Main_StartFw0_7
	ldmia sp!, {r4, pc}
	.align 2, 0
_0215E9D0: .word exBossSysAdminTask__Main_StartFw0_7
	arm_func_end exBossSysAdminTask__Action_StartFw0_7

	arm_func_start exBossSysAdminTask__Main_StartFw0_7
exBossSysAdminTask__Main_StartFw0_7: // 0x0215E9D4
	stmdb sp!, {r4, lr}
	bl GetExTaskWorkCurrent_
	mov r4, r0
	add r0, r4, #0x6c
	bl exDrawReqTask__Model__Animate
	ldrb r0, [r4, #1]
	orr r0, r0, #0x80
	strb r0, [r4, #1]
	bl exBossSysAdminTask__MoveRandom
	ldrsh r0, [r4, #0x5e]
	cmp r0, #0
	bgt _0215EA64
	ldr r3, _0215EA90 // =_mt_math_rand
	ldr r2, _0215EA94 // =0x0217431C
	ldr ip, [r3]
	ldr r0, _0215EA98 // =0x00196225
	ldr r1, _0215EA9C // =0x3C6EF35F
	ldr r2, [r2, #0xc]
	mla r0, ip, r0, r1
	str r0, [r3]
	str r2, [r4, #0x548]
	bl GetExPlayerWorker
	ldrb r0, [r0, #0x6a]
	mov r0, r0, lsl #0x1f
	movs r0, r0, lsr #0x1f
	bne _0215EA50
	bl GetExTaskCurrent
	ldr r1, _0215EAA0 // =exBossSysAdminTask__Main_StartFw0_5
	str r1, [r0]
	bl exBossSysAdminTask__Main_StartFw0_5
	ldmia sp!, {r4, pc}
_0215EA50:
	bl GetExTaskCurrent
	ldr r1, _0215EAA0 // =exBossSysAdminTask__Main_StartFw0_5
	str r1, [r0]
	bl exBossSysAdminTask__Main_StartFw0_5
	ldmia sp!, {r4, pc}
_0215EA64:
	sub r2, r0, #1
	add r0, r4, #0x6c
	add r1, r4, #0x3f8
	strh r2, [r4, #0x5e]
	bl exDrawReqTask__AddRequest
	add r0, r4, #0x6c
	bl exHitCheckTask__AddHitCheck
	bl GetExTaskCurrent
	ldr r0, [r0, #8]
	blx r0
	ldmia sp!, {r4, pc}
	.align 2, 0
_0215EA90: .word _mt_math_rand
_0215EA94: .word 0x0217431C
_0215EA98: .word 0x00196225
_0215EA9C: .word 0x3C6EF35F
_0215EAA0: .word exBossSysAdminTask__Main_StartFw0_5
	arm_func_end exBossSysAdminTask__Main_StartFw0_7

	arm_func_start exBossSysAdminTask__Action_StartFw0_8
exBossSysAdminTask__Action_StartFw0_8: // 0x0215EAA4
	stmdb sp!, {r4, lr}
	bl GetExTaskWorkCurrent_
	mov r4, r0
	add r0, r4, #0x6c
	mov r1, #0
	bl exBossHelpers__SetAnimation
	add r0, r4, #0x3f8
	bl exDrawReqTask__Func_2164218
	bl exBossSysAdminTask__SetNextTimer
	bl GetExTaskCurrent
	ldr r1, _0215EADC // =exBossSysAdminTask__Main_StartFw0_8
	str r1, [r0]
	bl exBossSysAdminTask__Main_StartFw0_8
	ldmia sp!, {r4, pc}
	.align 2, 0
_0215EADC: .word exBossSysAdminTask__Main_StartFw0_8
	arm_func_end exBossSysAdminTask__Action_StartFw0_8

	arm_func_start exBossSysAdminTask__Main_StartFw0_8
exBossSysAdminTask__Main_StartFw0_8: // 0x0215EAE0
	stmdb sp!, {r4, r5, r6, lr}
	bl GetExTaskWorkCurrent_
	mov r4, r0
	add r0, r4, #0x6c
	bl exDrawReqTask__Model__Animate
	ldrb r0, [r4, #1]
	orr r0, r0, #0x80
	strb r0, [r4, #1]
	bl exBossSysAdminTask__MoveRandom
	ldrsh r0, [r4, #0x5e]
	cmp r0, #0
	bgt _0215EBD4
	bl exBossFireDoraTask__AnyActive
	cmp r0, #0
	bne _0215EBC0
	bl exBossHomingLaserTask__AnyActive
	cmp r0, #0
	bne _0215EBC0
	ldr r1, _0215EC00 // =_mt_math_rand
	ldr r0, _0215EC04 // =0x0217431C
	ldr r5, [r1, #0]
	ldr r2, _0215EC08 // =0x00196225
	ldr r3, _0215EC0C // =0x3C6EF35F
	ldr r6, _0215EC10 // =0x51EB851F
	mla r2, r5, r2, r3
	mov r3, r2, lsr #0x10
	mov r3, r3, lsl #0x10
	mov r5, r3, lsr #0x10
	mov ip, r5, lsr #0x1f
	smull lr, r5, r6, r5
	add r5, ip, r5, asr #5
	mov lr, #0x64
	smull r5, ip, lr, r5
	ldr r0, [r0, #0x1c]
	str r2, [r1]
	str r0, [r4, #0x548]
	rsb r5, r5, r3, lsr #16
	bl GetExPlayerWorker
	ldrb r0, [r0, #0x6a]
	mov r0, r0, lsl #0x1f
	movs r0, r0, lsr #0x1f
	bne _0215EBA4
	ldrb r0, [r4, #2]
	cmp r5, #0x32
	orrge r0, r0, #0x20
	strgeb r0, [r4, #2]
	orrlt r0, r0, #0x10
	strltb r0, [r4, #2]
	b _0215EBDC
_0215EBA4:
	ldrb r0, [r4, #2]
	cmp r5, #0x32
	orrge r0, r0, #0x20
	strgeb r0, [r4, #2]
	orrlt r0, r0, #0x10
	strltb r0, [r4, #2]
	b _0215EBDC
_0215EBC0:
	bl GetExTaskCurrent
	ldr r1, _0215EC14 // =exBossSysAdminTask__Main_StartFw0_9
	str r1, [r0]
	bl exBossSysAdminTask__Main_StartFw0_9
	ldmia sp!, {r4, r5, r6, pc}
_0215EBD4:
	sub r0, r0, #1
	strh r0, [r4, #0x5e]
_0215EBDC:
	add r0, r4, #0x6c
	add r1, r4, #0x3f8
	bl exDrawReqTask__AddRequest
	add r0, r4, #0x6c
	bl exHitCheckTask__AddHitCheck
	bl GetExTaskCurrent
	ldr r0, [r0, #8]
	blx r0
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_0215EC00: .word _mt_math_rand
_0215EC04: .word 0x0217431C
_0215EC08: .word 0x00196225
_0215EC0C: .word 0x3C6EF35F
_0215EC10: .word 0x51EB851F
_0215EC14: .word exBossSysAdminTask__Main_StartFw0_9
	arm_func_end exBossSysAdminTask__Main_StartFw0_8

	arm_func_start exBossSysAdminTask__Action_StartFw0_9
exBossSysAdminTask__Action_StartFw0_9: // 0x0215EC18
	stmdb sp!, {r4, lr}
	bl GetExTaskWorkCurrent_
	mov r4, r0
	add r0, r4, #0x6c
	mov r1, #0
	bl exBossHelpers__SetAnimation
	add r0, r4, #0x3f8
	bl exDrawReqTask__Func_2164218
	bl GetExTaskCurrent
	ldr r1, _0215EC4C // =exBossSysAdminTask__Main_StartFw0_9
	str r1, [r0]
	bl exBossSysAdminTask__Main_StartFw0_9
	ldmia sp!, {r4, pc}
	.align 2, 0
_0215EC4C: .word exBossSysAdminTask__Main_StartFw0_9
	arm_func_end exBossSysAdminTask__Action_StartFw0_9

	arm_func_start exBossSysAdminTask__Main_StartFw0_9
exBossSysAdminTask__Main_StartFw0_9: // 0x0215EC50
	stmdb sp!, {r4, r5, r6, lr}
	bl GetExTaskWorkCurrent_
	mov r4, r0
	add r0, r4, #0x6c
	bl exDrawReqTask__Model__Animate
	ldrb r0, [r4, #1]
	orr r0, r0, #0x80
	strb r0, [r4, #1]
	bl exBossSysAdminTask__MoveRandom
	ldrsh r0, [r4, #0x5e]
	cmp r0, #0
	bgt _0215EDB8
	ldr r1, _0215EDE4 // =_mt_math_rand
	ldr r0, _0215EDE8 // =0x0217431C
	ldr r5, [r1, #0]
	ldr r2, _0215EDEC // =0x00196225
	ldr r3, _0215EDF0 // =0x3C6EF35F
	ldr r6, _0215EDF4 // =0x51EB851F
	mla r2, r5, r2, r3
	mov r3, r2, lsr #0x10
	mov r3, r3, lsl #0x10
	mov r5, r3, lsr #0x10
	mov ip, r5, lsr #0x1f
	smull lr, r5, r6, r5
	add r5, ip, r5, asr #5
	mov lr, #0x64
	smull r5, ip, lr, r5
	ldr r0, [r0, #0x20]
	str r2, [r1]
	str r0, [r4, #0x548]
	rsb r5, r5, r3, lsr #16
	bl GetExPlayerWorker
	ldrb r0, [r0, #0x6a]
	mov r0, r0, lsl #0x1f
	movs r0, r0, lsr #0x1f
	bne _0215ED4C
	cmp r5, #0x14
	bge _0215ECF8
	ldrb r0, [r4, #2]
	orr r0, r0, #4
	strb r0, [r4, #2]
	b _0215EDC0
_0215ECF8:
	blt _0215ED14
	cmp r5, #0x32
	bge _0215ED14
	ldrb r0, [r4, #2]
	orr r0, r0, #8
	strb r0, [r4, #2]
	b _0215EDC0
_0215ED14:
	cmp r5, #0x32
	blt _0215ED34
	cmp r5, #0x46
	bge _0215ED34
	ldrb r0, [r4, #2]
	orr r0, r0, #0x40
	strb r0, [r4, #2]
	b _0215EDC0
_0215ED34:
	cmp r5, #0x46
	ble _0215EDC0
	ldrb r0, [r4, #2]
	orr r0, r0, #0x80
	strb r0, [r4, #2]
	b _0215EDC0
_0215ED4C:
	cmp r5, #0x14
	bge _0215ED64
	ldrb r0, [r4, #2]
	orr r0, r0, #4
	strb r0, [r4, #2]
	b _0215EDC0
_0215ED64:
	blt _0215ED80
	cmp r5, #0x32
	bge _0215ED80
	ldrb r0, [r4, #2]
	orr r0, r0, #8
	strb r0, [r4, #2]
	b _0215EDC0
_0215ED80:
	cmp r5, #0x32
	blt _0215EDA0
	cmp r5, #0x46
	bge _0215EDA0
	ldrb r0, [r4, #2]
	orr r0, r0, #0x40
	strb r0, [r4, #2]
	b _0215EDC0
_0215EDA0:
	cmp r5, #0x46
	ble _0215EDC0
	ldrb r0, [r4, #2]
	orr r0, r0, #0x80
	strb r0, [r4, #2]
	b _0215EDC0
_0215EDB8:
	sub r0, r0, #1
	strh r0, [r4, #0x5e]
_0215EDC0:
	add r0, r4, #0x6c
	add r1, r4, #0x3f8
	bl exDrawReqTask__AddRequest
	add r0, r4, #0x6c
	bl exHitCheckTask__AddHitCheck
	bl GetExTaskCurrent
	ldr r0, [r0, #8]
	blx r0
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_0215EDE4: .word _mt_math_rand
_0215EDE8: .word 0x0217431C
_0215EDEC: .word 0x00196225
_0215EDF0: .word 0x3C6EF35F
_0215EDF4: .word 0x51EB851F
	arm_func_end exBossSysAdminTask__Main_StartFw0_9

	arm_func_start exBossSysAdminTask__Action_StartFw0_10
exBossSysAdminTask__Action_StartFw0_10: // 0x0215EDF8
	stmdb sp!, {r4, lr}
	bl GetExTaskWorkCurrent_
	mov r4, r0
	add r0, r4, #0x6c
	mov r1, #0
	bl exBossHelpers__SetAnimation
	add r0, r4, #0x3f8
	bl exDrawReqTask__Func_2164218
	bl GetExTaskCurrent
	ldr r1, _0215EE2C // =exBossSysAdminTask__Main_StartFw0_10
	str r1, [r0]
	bl exBossSysAdminTask__Main_StartFw0_10
	ldmia sp!, {r4, pc}
	.align 2, 0
_0215EE2C: .word exBossSysAdminTask__Main_StartFw0_10
	arm_func_end exBossSysAdminTask__Action_StartFw0_10

	arm_func_start exBossSysAdminTask__Main_StartFw0_10
exBossSysAdminTask__Main_StartFw0_10: // 0x0215EE30
	stmdb sp!, {r4, lr}
	bl GetExTaskWorkCurrent_
	mov r4, r0
	add r0, r4, #0x6c
	bl exDrawReqTask__Model__Animate
	ldrb r0, [r4, #1]
	orr r0, r0, #0x80
	strb r0, [r4, #1]
	bl exBossSysAdminTask__MoveRandom
	ldrsh r0, [r4, #0x5e]
	cmp r0, #0
	bgt _0215EEC0
	ldr r3, _0215EEEC // =_mt_math_rand
	ldr r2, _0215EEF0 // =0x0217431C
	ldr ip, [r3]
	ldr r0, _0215EEF4 // =0x00196225
	ldr r1, _0215EEF8 // =0x3C6EF35F
	ldr r2, [r2, #0x18]
	mla r0, ip, r0, r1
	str r0, [r3]
	str r2, [r4, #0x548]
	bl GetExPlayerWorker
	ldrb r0, [r0, #0x6a]
	mov r0, r0, lsl #0x1f
	movs r0, r0, lsr #0x1f
	bne _0215EEAC
	bl GetExTaskCurrent
	ldr r1, _0215EEFC // =exBossSysAdminTask__Main_StartFw0_8
	str r1, [r0]
	bl exBossSysAdminTask__Main_StartFw0_8
	ldmia sp!, {r4, pc}
_0215EEAC:
	bl GetExTaskCurrent
	ldr r1, _0215EEFC // =exBossSysAdminTask__Main_StartFw0_8
	str r1, [r0]
	bl exBossSysAdminTask__Main_StartFw0_8
	ldmia sp!, {r4, pc}
_0215EEC0:
	sub r2, r0, #1
	add r0, r4, #0x6c
	add r1, r4, #0x3f8
	strh r2, [r4, #0x5e]
	bl exDrawReqTask__AddRequest
	add r0, r4, #0x6c
	bl exHitCheckTask__AddHitCheck
	bl GetExTaskCurrent
	ldr r0, [r0, #8]
	blx r0
	ldmia sp!, {r4, pc}
	.align 2, 0
_0215EEEC: .word _mt_math_rand
_0215EEF0: .word 0x0217431C
_0215EEF4: .word 0x00196225
_0215EEF8: .word 0x3C6EF35F
_0215EEFC: .word exBossSysAdminTask__Main_StartFw0_8
	arm_func_end exBossSysAdminTask__Main_StartFw0_10

	arm_func_start exBossSysAdminTask__SetNextTimer
exBossSysAdminTask__SetNextTimer: // 0x0215EF00
	stmdb sp!, {r3, r4, r5, lr}
	bl GetExTaskWorkCurrent_
	ldr lr, _0215EF88 // =_mt_math_rand
	ldr r1, _0215EF8C // =0x00196225
	ldr r3, [lr]
	ldr r2, _0215EF90 // =0x3C6EF35F
	ldr ip, _0215EF94 // =0x51EB851F
	mla r5, r3, r1, r2
	mov r1, r5, lsr #0x10
	mov r1, r1, lsl #0x10
	mov r3, r1, lsr #0x10
	mov r2, r3, lsr #0x1f
	smull r3, r4, ip, r3
	add r4, r2, r4, asr #5
	mov ip, #0x64
	smull r2, r3, ip, r4
	rsb r4, r2, r1, lsr #16
	cmp r4, #0x32
	str r5, [lr]
	movlt r1, #2
	strlth r1, [r0, #0x5e]
	ldmltia sp!, {r3, r4, r5, pc}
	cmp r4, #0x46
	movlt r1, #0x3c
	strlth r1, [r0, #0x5e]
	ldmltia sp!, {r3, r4, r5, pc}
	cmp r4, #0x5a
	movlt r1, #0x14
	strlth r1, [r0, #0x5e]
	ldmltia sp!, {r3, r4, r5, pc}
	cmp r4, #0x64
	movlt r1, #0xf0
	strlth r1, [r0, #0x5e]
	ldmia sp!, {r3, r4, r5, pc}
	.align 2, 0
_0215EF88: .word _mt_math_rand
_0215EF8C: .word 0x00196225
_0215EF90: .word 0x3C6EF35F
_0215EF94: .word 0x51EB851F
	arm_func_end exBossSysAdminTask__SetNextTimer

	arm_func_start exBossSysAdminTask__Main_Blank
exBossSysAdminTask__Main_Blank: // 0x0215EF98
	bx lr
	arm_func_end exBossSysAdminTask__Main_Blank

	arm_func_start exBossSysAdminTask__Create
exBossSysAdminTask__Create: // 0x0215EF9C
	stmdb sp!, {r4, lr}
	sub sp, sp, #0x10
	mov r4, #0
	str r4, [sp]
	mov r1, #0x550
	ldr r0, _0215F004 // =aExbosssysadmin_0
	str r1, [sp, #4]
	str r0, [sp, #8]
	ldr r0, _0215F008 // =exBossSysAdminTask__Main_Init
	ldr r1, _0215F00C // =exBossSysAdminTask__Destructor
	mov r2, #0x3800
	mov r3, #5
	str r4, [sp, #0xc]
	bl ExTaskCreate_
	mov r4, r0
	bl GetExTaskWork_
	mov r1, #0
	mov r2, #0x550
	bl MI_CpuFill8
	mov r0, r4
	bl GetExTask
	ldr r1, _0215F010 // =exBossSysAdminTask__Func8
	str r1, [r0, #8]
	mov r0, #1
	add sp, sp, #0x10
	ldmia sp!, {r4, pc}
	.align 2, 0
_0215F004: .word aExbosssysadmin_0
_0215F008: .word exBossSysAdminTask__Main_Init
_0215F00C: .word exBossSysAdminTask__Destructor
_0215F010: .word exBossSysAdminTask__Func8
	arm_func_end exBossSysAdminTask__Create

	arm_func_start exBossSysAdminTask__GetSingleton
exBossSysAdminTask__GetSingleton: // 0x0215F014
	ldr r0, _0215F020 // =exBossSysAdminTask__dword_217626C
	ldr r0, [r0, #0xc]
	bx lr
	.align 2, 0
_0215F020: .word exBossSysAdminTask__dword_217626C
	arm_func_end exBossSysAdminTask__GetSingleton

	arm_func_start exBossSysAdminTask__Destroy
exBossSysAdminTask__Destroy: // 0x0215F024
	stmdb sp!, {r3, lr}
	ldr r0, _0215F048 // =exBossSysAdminTask__dword_217626C
	ldr r0, [r0, #0xc]
	cmp r0, #0
	ldmeqia sp!, {r3, pc}
	bl GetExTask
	ldr r1, _0215F04C // =ExTask_State_Destroy
	str r1, [r0]
	ldmia sp!, {r3, pc}
	.align 2, 0
_0215F048: .word exBossSysAdminTask__dword_217626C
_0215F04C: .word ExTask_State_Destroy
	arm_func_end exBossSysAdminTask__Destroy

	.data

_0217431C:
	.word exBossSysAdminTask__Action_DragonAttackIdle
	.word exBossSysAdminTask__Action_StartFw0_3
	.word exBossSysAdminTask__Action_StartFw0_4
	.word exBossSysAdminTask__Action_StartFw0_5
	.word exBossSysAdminTask__Action_StartFw0_6
	.word exBossSysAdminTask__Action_StartFw0_7
	.word exBossSysAdminTask__Action_StartFw0_8
	.word exBossSysAdminTask__Action_StartFw0_9
	.word exBossSysAdminTask__Action_StartFw0_10
	.word exBossSysAdminTask__Action_StartMete0
	.word exBossSysAdminTask__Action_StartFire0
	.word exBossSysAdminTask__Action_StartHomi0
	.word exBossSysAdminTask__Action_StartDora0
	.word exBossSysAdminTask__Action_StartWave0
	.word exBossSysAdminTask__Action_StartLine0
	.word exBossSysAdminTask__Action_StartDmg0
	.word exBossSysAdminTask__Action_StartBDmg0
	.word exBossSysAdminTask__Action_StartBDmg1_Last
	.word exBossSysAdminTask__Action_StartBDmg1_First

aExbosssysadmin_0: // 0x02174368
	.asciz "exBossSysAdminTask"
	.align 4
	
aExbosssysadmin: // 0x0217437C
	.asciz "exBossSysAdminBiforTask"