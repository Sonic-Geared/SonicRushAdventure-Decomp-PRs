	.include "asm/macros.inc"
	.include "global.inc"
	
	.text

	arm_func_start CameraBoundsTrigger__Create
CameraBoundsTrigger__Create: // 0x02168644
	stmdb sp!, {r3, r4, r5, r6, r7, r8, lr}
	sub sp, sp, #0xc
	mov r3, #0x1800
	mov r4, r0
	mov r7, r1
	mov r6, r2
	mov r2, #0
	str r3, [sp]
	mov r5, #2
	str r5, [sp, #4]
	mov r5, #0x39c
	ldr r0, _021687B0 // =StageTask_Main
	ldr r1, _021687B4 // =GameObject__Destructor
	mov r3, r2
	str r5, [sp, #8]
	bl TaskCreate_
	mov r5, r0
	mov r0, #0
	bl OS_GetArenaLo
	cmp r5, r0
	addeq sp, sp, #0xc
	moveq r0, #0
	ldmeqia sp!, {r3, r4, r5, r6, r7, r8, pc}
	mov r0, r5
	bl GetTaskWork_
	mov r5, r0
	mov r1, #0
	mov r2, #0x39c
	bl MI_CpuFill8
	mov r0, r5
	mov r1, r4
	mov r2, r7
	mov r3, r6
	bl GameObject__InitFromObject
	ldr r1, [r5, #0x1c]
	ldr r0, _021687B8 // =mapCamera
	orr r1, r1, #0x2100
	str r1, [r5, #0x1c]
	ldr r1, [r5, #0x20]
	orr r1, r1, #0x20
	str r1, [r5, #0x20]
	ldr r0, [r0, #0xe0]
	tst r0, #1
	moveq r2, #2
	beq _02168704
	mov r2, #1
	sub r0, r2, #2
	strb r0, [r5, #0x398]
_02168704:
	cmp r2, #0
	mov r1, #0
	ble _0216879C
	ldr r3, _021687B8 // =mapCamera
	ldr r0, _021687BC // =ovl00_21687FC
	add ip, r5, #0x364
_0216871C:
	ldrsb r6, [r3, #0x46]
	add r1, r1, #1
	cmp r1, r2
	strb r6, [ip, #0x18]
	str r0, [ip, #0x14]
	ldrsb r7, [r4, #6]
	ldr r8, [r5, #0x44]
	ldr r6, [r3, #0x24]
	mla r6, r7, r6, r8
	str r6, [ip, #4]
	ldrsb r7, [r4, #7]
	ldr r8, [r5, #0x48]
	ldr r6, [r3, #0x28]
	mla r6, r7, r6, r8
	str r6, [ip, #8]
	ldrsb r7, [r4, #6]
	ldrb r6, [r4, #8]
	ldr lr, [r5, #0x44]
	ldr r8, [r3, #0x24]
	add r6, r7, r6
	mla r6, r8, r6, lr
	str r6, [ip, #0xc]
	ldr lr, [r3, #0x28]
	ldrsb r7, [r4, #7]
	ldrb r6, [r4, #9]
	ldr r8, [r5, #0x48]
	add r3, r3, #0x70
	add r6, r7, r6
	mla r6, lr, r6, r8
	str r6, [ip, #0x10]
	add ip, ip, #0x1c
	blt _0216871C
_0216879C:
	ldr r1, _021687C0 // =ovl00_21687C4
	mov r0, r5
	str r1, [r5, #0xf4]
	add sp, sp, #0xc
	ldmia sp!, {r3, r4, r5, r6, r7, r8, pc}
	.align 2, 0
_021687B0: .word StageTask_Main
_021687B4: .word GameObject__Destructor
_021687B8: .word mapCamera
_021687BC: .word ovl00_21687FC
_021687C0: .word ovl00_21687C4
	arm_func_end CameraBoundsTrigger__Create

	arm_func_start ovl00_21687C4
ovl00_21687C4: // 0x021687C4
	stmdb sp!, {r4, lr}
	mov r4, r0
	ldr r2, [r4, #0x378]
	cmp r2, #0
	beq _021687E0
	mov r1, #0
	blx r2
_021687E0:
	ldr r2, [r4, #0x394]
	cmp r2, #0
	ldmeqia sp!, {r4, pc}
	mov r0, r4
	mov r1, #1
	blx r2
	ldmia sp!, {r4, pc}
	arm_func_end ovl00_21687C4

	arm_func_start ovl00_21687FC
ovl00_21687FC: // 0x021687FC
	stmdb sp!, {r4, lr}
	mov r2, #0x1c
	mul lr, r1, r2
	add r4, r0, #0x364
	ldr r3, [r4, lr]
	ldr ip, _02168944 // =mapCamera
	mov r0, #0x70
	mla r2, r1, r0, ip
	tst r3, #1
	add r0, r4, lr
	beq _02168860
	ldrsb r1, [r2, #0x68]
	sub r1, r1, #1
	strb r1, [r2, #0x68]
	ldrsb r1, [r2, #0x68]
	cmp r1, #0
	bne _02168860
	ldr r1, [ip, #0x130]
	str r1, [r2, #0x58]
	ldr r1, [r2]
	bic r1, r1, #0x10
	str r1, [r2]
	ldr r1, [r0]
	bic r1, r1, #1
	str r1, [r0]
_02168860:
	ldr r1, [r0]
	tst r1, #2
	beq _021688A8
	ldrsb r1, [r2, #0x69]
	sub r1, r1, #1
	strb r1, [r2, #0x69]
	ldrsb r1, [r2, #0x69]
	cmp r1, #0
	bne _021688A8
	ldr r1, _02168944 // =mapCamera
	ldr r1, [r1, #0x134]
	str r1, [r2, #0x5c]
	ldr r1, [r2]
	bic r1, r1, #0x20
	str r1, [r2]
	ldr r1, [r0]
	bic r1, r1, #2
	str r1, [r0]
_021688A8:
	ldr r1, [r0]
	tst r1, #4
	beq _021688F0
	ldrsb r1, [r2, #0x6a]
	sub r1, r1, #1
	strb r1, [r2, #0x6a]
	ldrsb r1, [r2, #0x6a]
	cmp r1, #0
	bne _021688F0
	ldr r1, _02168944 // =mapCamera
	ldr r1, [r1, #0x138]
	str r1, [r2, #0x60]
	ldr r1, [r2]
	bic r1, r1, #0x10
	str r1, [r2]
	ldr r1, [r0]
	bic r1, r1, #4
	str r1, [r0]
_021688F0:
	ldr r1, [r0]
	tst r1, #8
	beq _02168938
	ldrsb r1, [r2, #0x6b]
	sub r1, r1, #1
	strb r1, [r2, #0x6b]
	ldrsb r1, [r2, #0x6b]
	cmp r1, #0
	bne _02168938
	ldr r1, _02168944 // =mapCamera
	ldr r1, [r1, #0x13c]
	str r1, [r2, #0x64]
	ldr r1, [r2]
	bic r1, r1, #0x20
	str r1, [r2]
	ldr r1, [r0]
	bic r1, r1, #8
	str r1, [r0]
_02168938:
	ldr r1, _02168948 // =ovl00_216894C
	str r1, [r0, #0x14]
	ldmia sp!, {r4, pc}
	.align 2, 0
_02168944: .word mapCamera
_02168948: .word ovl00_216894C
	arm_func_end ovl00_21687FC

	arm_func_start ovl00_216894C
ovl00_216894C: // 0x0216894C
	stmdb sp!, {r3, r4, r5, lr}
	mov r5, r0
	mov r4, r1
	bl ovl00_2168BC0
	cmp r0, #0
	ldmeqia sp!, {r3, r4, r5, pc}
	mov r0, r5
	mov r1, r4
	bl ovl00_2168974
	ldmia sp!, {r3, r4, r5, pc}
	arm_func_end ovl00_216894C

	arm_func_start ovl00_2168974
ovl00_2168974: // 0x02168974
	stmdb sp!, {r4, lr}
	ldr r3, [r0, #0x340]
	ldr lr, _02168B90 // =mapCamera
	mov r2, #0x70
	ldrh ip, [r3, #4]
	add r4, r0, #0x364
	mov r0, #0x1c
	mla r0, r1, r0, r4
	mla r2, r1, r2, lr
	tst ip, #1
	beq _021689C0
	ldr r1, [r0, #4]
	str r1, [r2, #0x58]
	ldrsb r1, [r2, #0x68]
	add r1, r1, #1
	strb r1, [r2, #0x68]
	ldr r1, [r0]
	orr r1, r1, #1
	str r1, [r0]
_021689C0:
	ldrh r1, [r3, #4]
	tst r1, #4
	beq _021689EC
	ldr r1, [r0, #0xc]
	str r1, [r2, #0x60]
	ldrsb r1, [r2, #0x6a]
	add r1, r1, #1
	strb r1, [r2, #0x6a]
	ldr r1, [r0]
	orr r1, r1, #4
	str r1, [r0]
_021689EC:
	ldr r1, _02168B90 // =mapCamera
	ldr r1, [r1, #0xe0]
	tst r1, #1
	beq _02168B2C
	tst r1, #2
	ldrh r1, [r3, #4]
	beq _02168A9C
	tst r1, #2
	beq _02168A50
	ldr r1, [r2, #8]
	ldr ip, [r0, #8]
	sub r1, r1, #0x110000
	cmp r1, ip
	addge r1, ip, #0x110000
	strge r1, [r2, #0x5c]
	bge _02168A38
	ldr r1, [r2]
	orr r1, r1, #0x20
	str r1, [r2]
_02168A38:
	ldrsb r1, [r2, #0x69]
	add r1, r1, #1
	strb r1, [r2, #0x69]
	ldr r1, [r0]
	orr r1, r1, #2
	str r1, [r0]
_02168A50:
	ldrh r1, [r3, #4]
	tst r1, #8
	beq _02168B84
	ldr r1, [r2, #8]
	ldr r3, [r0, #0x10]
	add r1, r1, #0xc0000
	cmp r1, r3
	strle r3, [r2, #0x64]
	ble _02168A80
	ldr r1, [r2]
	orr r1, r1, #0x20
	str r1, [r2]
_02168A80:
	ldrsb r1, [r2, #0x6b]
	add r1, r1, #1
	strb r1, [r2, #0x6b]
	ldr r1, [r0]
	orr r1, r1, #8
	str r1, [r0]
	b _02168B84
_02168A9C:
	tst r1, #2
	beq _02168ADC
	ldr ip, [r0, #8]
	ldr r1, [r2, #8]
	cmp r1, ip
	strge ip, [r2, #0x5c]
	bge _02168AC4
	ldr r1, [r2]
	orr r1, r1, #0x20
	str r1, [r2]
_02168AC4:
	ldrsb r1, [r2, #0x69]
	add r1, r1, #1
	strb r1, [r2, #0x69]
	ldr r1, [r0]
	orr r1, r1, #2
	str r1, [r0]
_02168ADC:
	ldrh r1, [r3, #4]
	tst r1, #8
	beq _02168B84
	ldr r1, [r2, #8]
	ldr r3, [r0, #0x10]
	add r1, r1, #0x1d0000
	cmp r1, r3
	suble r1, r3, #0x1d0000
	strle r1, [r2, #0x64]
	ble _02168B10
	ldr r1, [r2]
	orr r1, r1, #0x20
	str r1, [r2]
_02168B10:
	ldrsb r1, [r2, #0x6b]
	add r1, r1, #1
	strb r1, [r2, #0x6b]
	ldr r1, [r0]
	orr r1, r1, #8
	str r1, [r0]
	b _02168B84
_02168B2C:
	ldrh r1, [r3, #4]
	tst r1, #2
	beq _02168B58
	ldr r1, [r0, #8]
	str r1, [r2, #0x5c]
	ldrsb r1, [r2, #0x69]
	add r1, r1, #1
	strb r1, [r2, #0x69]
	ldr r1, [r0]
	orr r1, r1, #2
	str r1, [r0]
_02168B58:
	ldrh r1, [r3, #4]
	tst r1, #8
	beq _02168B84
	ldr r1, [r0, #0x10]
	str r1, [r2, #0x64]
	ldrsb r1, [r2, #0x6b]
	add r1, r1, #1
	strb r1, [r2, #0x6b]
	ldr r1, [r0]
	orr r1, r1, #8
	str r1, [r0]
_02168B84:
	ldr r1, _02168B94 // =ovl00_2168B98
	str r1, [r0, #0x14]
	ldmia sp!, {r4, pc}
	.align 2, 0
_02168B90: .word mapCamera
_02168B94: .word ovl00_2168B98
	arm_func_end ovl00_2168974

	arm_func_start ovl00_2168B98
ovl00_2168B98: // 0x02168B98
	stmdb sp!, {r3, r4, r5, lr}
	mov r5, r0
	mov r4, r1
	bl ovl00_2168BC0
	cmp r0, #0
	ldmneia sp!, {r3, r4, r5, pc}
	mov r0, r5
	mov r1, r4
	bl ovl00_21687FC
	ldmia sp!, {r3, r4, r5, pc}
	arm_func_end ovl00_2168B98

	arm_func_start ovl00_2168BC0
ovl00_2168BC0: // 0x02168BC0
	stmdb sp!, {r4, lr}
	mov r2, #0x1c
	mla r3, r1, r2, r0
	add r1, r3, #0x300
	ldrsb r4, [r1, #0x7c]
	sub r1, r2, #0x1d
	ldr r2, [r0, #0x340]
	cmp r4, r1
	mov r3, #0
	beq _02168C70
	ldr r1, _02168C78 // =gPlayerList
	ldrsb ip, [r2, #6]
	ldr r1, [r1, r4, lsl #2]
	ldr r4, [r0, #0x44]
	ldr lr, [r1, #0x44]
	add r4, r4, ip, lsl #12
	cmp r4, lr
	bgt _02168C70
	ldrb ip, [r2, #8]
	add ip, r4, ip, lsl #12
	cmp ip, lr
	blt _02168C70
	ldrsb lr, [r2, #7]
	ldr r0, [r0, #0x48]
	ldr ip, [r1, #0x48]
	add lr, r0, lr, lsl #12
	cmp lr, ip
	bgt _02168C70
	ldrb r0, [r2, #9]
	add r0, lr, r0, lsl #12
	cmp r0, ip
	blt _02168C70
	ldr r0, [r1, #0x18]
	ands r1, r0, #1
	bne _02168C58
	ldrh r0, [r2, #4]
	tst r0, #0x10
	bne _02168C6C
_02168C58:
	cmp r1, #0
	beq _02168C70
	ldrh r0, [r2, #4]
	tst r0, #0x20
	beq _02168C70
_02168C6C:
	mov r3, #1
_02168C70:
	mov r0, r3
	ldmia sp!, {r4, pc}
	.align 2, 0
_02168C78: .word gPlayerList
	arm_func_end ovl00_2168BC0