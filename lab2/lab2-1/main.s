	.syntax unified
	.cpu cortex-m4
	.thumb

.data
	result: .zero 8

.text
	.global main
	.equ X, 0x12345678
	.equ Y, 0xABCDEF00
	.equ mask, 0xFFFF
	.equ mask2, 0xFFFF0000
main:
	ldr r0, =X
	ldr r1, =Y

	ldr r3, =mask
	bl kara_mul

	ldr r0, =result
	strd r3, r2, [r0]

L: b L

kara_mul:
	and r4, r0, r3	// r4 is Xr
	lsr r0, r0, #16 // r0 logically shift right 16
	and r5, r0, r3	// r5 is Xl

	and r6, r1, r3	// r6 is Yr
	lsr r1, r1, #16 // r1 logically shift right 16
	and r7, r1, r3	// r7 is Yl

	add r0, r4, r5	// (Xl+Xr)(Yl+Yr)
	add r1, r6, r7	// r0 and r1 are temp
	umull r2, r3, r0, r1 // multiply r0 and r1, writes the top 32 bits to r3
						 // and the bottom 32 bits to r2

	mul r0, r5, r7	// (XlYl+XrYr)
	mul r1, r4, r6
	adds r0, r0, r1
	mov r1, #0
	adc r1, r1, #0


	subs r2, r2, r0		// (Xl+Xr)(Yl+Yr)-(XlYl+XrYr) is in r2 and r3
	sbc r3, r3, r1

	ldr r0, =mask2
	and r1, r0, r2
	lsr r1, r1, #16 // r1 logically shift right 16
	lsl r2, r2, #16 // r2 logically shift left 16
	lsl r3, r3, #16 // r3 logically shift left 16
	add r3, r3, r1	// 2^16*[(Xl+Xr)(Yl+Yr)-(Xl+Yl)(Xr+Yr)] is in r2 and r3


	umull r0, r1, r4, r6 // XrYr
						 // multiply r4 and r6, writes the top 32 bits to r1 (should be 0)
						 // and the bottom 32 bits to r0
	adds r2, r2, r0
	adc r3, r3, r1		//2^16*[(Xl+Xr)(Yl+Yr)-(Xl+Yl)(Xr+Yr)]+XrYr is in r2 and r3

	umull r0, r1, r5, r7 // XlYl
						 // multiply r5 and r7, writes the top 32 bits to r1 (should be 0)
						 // and the bottom 32 bits to r0
	add r3, r3, r0
	bx lr
