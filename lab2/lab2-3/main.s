	.syntax unified
	.cpu cortex-m4
	.thumb

.data
	result: .word 0
	max_size: .word 0
	user_stack_bottom: .zero 128	//.zero <number_of_bytes>

.text
	.global main
	m: .word 0x5E
	n: .word 0x60

GCD:
	//todo: Implement your GCD function

	cmp r0, #0
	itt eq
	moveq r2, r1 // r2 is the result
	bxeq lr

	cmp r1, #0
	itt eq
	moveq r2, r0 // r2 is the result
	bxeq lr

	and r4, r0, #1		// r4=a%2
	and r5, r1, #1		// r5=b%2

	orr r6, r4, r5		// if(a%2==0 && b%2==0) r6=0, else r6=1
	cmp r6, #0
	it eq
	beq handle_if

	cmp r4, #0
	it eq
	beq handle_first_elif

	cmp r5, #0
	it eq
	beq handle_second_elif

handle_else:
	cmp r0, r1
	ite lt
	sublt r6, r1, r0
	subge r6, r0, r1		// abs(a-b)


	cmp r0, r1
	it lo
	movlo r1, r0

	mov r0, r6
	push {lr}
	add r7, r7, #4
	bl GCD
	pop {lr}
	bx lr

handle_if:
	lsr r0, r0, #1 // r0(a) logically shift right 1
	lsr r1, r1, #1 // r1(b) logically shift right 1
	push {lr}
	add r7, r7, #4
	bl GCD
	lsl r2, r2, #1 // r2 logically shift left 1 (*2)
	pop {lr}
	bx lr

handle_first_elif:
	lsr r0, r0, #1 // r0(a) logically shift right 1
	push {lr}
	add r7, r7, #4
	bl GCD
	pop {lr}
	bx lr

handle_second_elif:
	lsr r1, r1, #1 // r1(b) logically shift right 1
	push {lr}
	add r7, r7, #4
	bl GCD
	pop {lr}
	bx lr





main:
	// r0 = m, r1 = n
	ldr r0, =m
	ldr r0, [r0]
	ldr r1, =n
	ldr r1, [r1]
	mov r7, #0	// r7 is stack num
	bl stack_init
	bl GCD
	// get return val and store into result
	ldr r0, =result
	str r2, [r0]
	ldr r0, =max_size
	str r7, [r0]

L:  b L

stack_init:
	//todo: Setup the stack pointer(sp) to user_stack.
	ldr r3, =user_stack_bottom
	add r3, r3, #128
	msr msp, r3
	//mrs r4, msp		// original stack pointer address
	bx lr

