	.syntax unified
	.cpu cortex-m4
	.thumb
.data
	result: .byte 0
.text					// text section identifier
	.global main		// export main as a global symbol
	.equ X, 0xABCD 	// define a constant symbol X
	.equ Y, 0xEFAB


main:					// label <main>
	ldr r0, =X			// load 0x55AA00( it is an address) to register(r0)
						// ldr r0, =#X is also right
	ldr r1, =Y
	ldr r2, =result		// load the address of result to register(r2)
	ldr r2, [r2]		// load the value of result to register(r2)

	bl hamm

	ldr r6, =result
	str r2, [r6]

L: B L					// branch to L

hamm:
	//todo
	eors r0, r0, r1		// r0 xor r1
	movs r3, #0			// r3 is i
loop:

	and r4, r0, #1	// check whether the two bits are the same
	add r2, r2, r4	// r2 adds the result of the last line

	adds r3, r3, #1		// r3 increment by 1

	cmp r3, #32			// shift right for 31 times
	itt lo
	movlo r0, r0, lsr #1// r0 logically shift right 1 then moves to r0
	blo loop

	bx lr


