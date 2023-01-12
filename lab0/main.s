	.syntax unified
	.cpu cortex-m4
	.thumb
/*
.text				// text section identifier
	.equ X, 0x55 	// define a constant symbol X
	.equ Y, 0x1234567
	.global main		// export main as a global symbol


main:				// label <main>
	movs r0, #X		// set register(r0) to 0x55
	ldr r1, =Y		// load 0x1234567( it means an address) to register(r1)
	adds r2, r0, r1 // add r0, r1 and store result in r2
*/

.data
	X: .word 100
	str: .asciz "Hello World!"
.text					// text section identifier
	.global main		// export main as a global symbol
	.equ AA, 0x55 		// define a constant symbol X


main:					// label <main>
	ldr r1, =X
	ldr r0, [r1]
	movs r2, #AA
	adds r2, r2, r0
	str r2, [r1]

	ldr r1, =str
	ldr r2, [r1]

L: B L				// branch to L
