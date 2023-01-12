	.syntax unified
	.cpu cortex-m4
	.thumb
.data
	//infix_expr: .asciz "{]-99+ [ 10 + 20-0] }"
	infix_expr: .asciz "{-99+ [ 10 + 20-10 }"
	user_stack_bottom: .zero 128	//.zero <number_of_bytes>
.text
	.global main
	//move infix_expr here. Please refer to the question below.
main:
	bl stack_init
	ldr r1, =infix_expr
	mov r0, #0
	bl pare_check
L: b L

stack_init:
	//todo: Setup the stack pointer(sp) to user_stack.
	ldr r2, =user_stack_bottom
	add r2, r2, #128
	msr msp, r2		// move the value in r2 to msp ( main stack pointer)
	mrs r4, msp		// original stack pointer address
	bx lr
pare_check:
	//todo: check parentheses balance, and set the error code to R0.
	ldrb r2, [r1]
	add r1, r1, #1

	cmp r2, #0 // '\0'
	it eq
	beq handle_0

	cmp r2, #123 // '{'
	it eq
	pusheq {r2}

	cmp r2, #91 // '['
	it eq
	pusheq {r2}


	cmp r2, #93 // ']'
	itt eq
	popeq {r3}
	beq handle_93

	cmp r2, #125 // '}'
	itt eq
	popeq {r3}
	beq handle_125


	b pare_check



handle_93:
	cmp r3, #91
	itt ne
	movne r0, #-1
	bxne lr

	b pare_check

handle_125:
	cmp r3, #123
	itt ne
	movne r0, #-1
	bxne lr

	b pare_check

handle_0:
	mrs r5, msp
	cmp r4, r5		// check whether the stack is empty
	it ne
	movne r0, #-1

	bx lr


