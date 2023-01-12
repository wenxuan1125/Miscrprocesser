	.syntax unified
	.cpu cortex-m4
	.thumb
.text					// text section identifier
	.global main		// export main as a global symbol
	.equ N, 101		 	// define a constant symbol N

fib:
	//todo

	//N>100
	cmp r0, #100
	itt gt
	movgt r4, #-1
	bxgt lr

	//N<0
	cmp r0, #0
	itt lt		// lo is unsigned lower, lt is signed less than
	movlt r4, #-1
	bxlt lr

	//N=0
	cmp r0, #0
	itt eq
	moveq r4, #0
	bxeq lr

	//N=1
	cmp r0, #1
	itt eq
	moveq r4, #1
	bxeq lr


	movs r3, #0		// r3 is i
	movs r4, #1		// r4 stores the result
loop:
	//overflow
	cmp r4, #0		// if the result after adding(r4) is less than 0, overflow happens
	itt lt
	movslt r4, #-2
	bxlt lr

	adds r3, r3, #1//r3 increment by 1
	cmp r3, #N
	itttt lo
	addslo r4, r1, r2
	movslo r1, r2
	movslo r2, r4
	blo loop

	bx lr


main:				// label <main>
	movs r0, #N
	movs r1, #0
	movs r2, #1

	bl fib

L: b L				// branch to L

