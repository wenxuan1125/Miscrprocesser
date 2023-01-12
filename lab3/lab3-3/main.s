	.syntax unified
	.cpu cortex-m4
	.thumb

.data
	password: .byte 0x7
.text
	.global main
	.equ RCC_AHB2ENR, 0x4002104c	//enable port
	.equ GPIOA_MODER, 0x48000000	//pin mode( input, output...)
	.equ GPIOA_OTYPER, 0x48000004	//push pull/open drain
	.equ GPIOA_OSPEEDR, 0x48000008	//speed
	.equ GPIOA_PUPDR, 0x4800000C	//pull up/down
	.equ GPIOA_ODR, 0x48000014	//output address

	.equ GPIOB_MODER, 0x48000400	//pin mode( input, output...)
	.equ GPIOB_OTYPER, 0x48000404	//push pull/open drain
	.equ GPIOB_OSPEEDR, 0x48000408	//speed
	.equ GPIOB_PUPDR, 0x4800040C	//pull up/down
	.equ GPIOB_IDR, 0x48000410	//output address

	// pc13: user button
	.equ GPIOC_MODER, 0x48000800	//pin mode( input, output...)
	.equ GPIOC_OTYPER, 0x48000804	//push pull/open drain
	.equ GPIOC_OSPEEDR, 0x48000808	//speed
	.equ GPIOC_PUPDR, 0x4800080C	//pull up/down
	.equ GPIOC_IDR, 0x48000810	//input address

main:
	bl GPIO_init

	//let LED to be dark ( after initialized, LED will be bright)
	ldr r2, =GPIOA_ODR
	mov r1, #1
	lsl r1, r1, #5	// shift left 5
	strh r1, [r2]	//set the output


	ldr r0, =password
	ldrb r0, [r0]	// r0 is passward

Loop:
	/* todo: check the button status to determine whether to
		pause updating the LED pattern*/

	// user push button, r4=0
	bl CheckPress
	/*
	cmp r4, #0
	it eq
	ldreq r5, =300000
	bl Delay*/

	cmp r4, #0
	it ne	// not push button
	bne Loop

	bl ReadDIP

	//r4 store the DIP value, comparing with the password
	cmp r4, r0
	it ne
	bne DisplayLED_wrong

	b DisplayLED_right

DisplayLED_wrong:
	ldr r2, =GPIOA_ODR

	//shine
	mov r1, #0
	strh r1, [r2]	//set the output
	ldr r5, =300000
	bl Delay

	//dark
	mov r1, #1
	lsl r1, r1, #5	// shift left 5
	strh r1, [r2]	//set the output
	//ldr r5, =300000
	//bl Delay

	b Loop


DisplayLED_right:

	ldr r2, =GPIOA_ODR

	mov r1, #0
	strh r1, [r2]	//set the output
	ldr r5, =300000
	bl Delay

	mov r1, #1
	lsl r1, r1, #5	// shift left 5
	strh r1, [r2]	//set the output
	ldr r5, =300000
	bl Delay

	mov r1, #0
	strh r1, [r2]	//set the output
	ldr r5, =300000
	bl Delay

	mov r1, #1
	lsl r1, r1, #5	// shift left 5
	strh r1, [r2]	//set the output
	ldr r5, =300000
	bl Delay

	mov r1, #0
	strh r1, [r2]	//set the output
	ldr r5, =300000
	bl Delay

	mov r1, #1
	lsl r1, r1, #5	// shift left 5
	strh r1, [r2]	//set the output
	//ldr r5, =300000
	//bl Delay

	b Loop



CheckPress:
	/* todo: do debounce and check button state */

	// sample 3 values
	ldr r2, =GPIOC_IDR
	ldr r4, [r2]
	ldr r5, [r2]

	cmp r4, r5
	it ne
	bne CheckPress

	ldr r4, [r2]
	cmp r4, r5
	it ne
	bne CheckPress

	bx lr

ReadDIP:
	ldr r2, =GPIOB_IDR
	ldr r4, [r2]
	lsr r4, r4, #3	// shift right 3

	bx lr

Delay:
	/* TODO: Write a delay 1 sec function */
	// You can implement this part by busy waiting.
	// Timer and Interrupt will be introduced in later lectures.

	cmp r5, #0
	itt gt
	subgt r5, r5, #1
	bgt Delay

	bx lr
GPIO_init:
	/* todo: initialize LED, button GPIO pins */

	// enable AHB2 clock port a, port b and port c
	mov r0, #7
	ldr r1, =RCC_AHB2ENR
	str r0, [r1]

	//set PA5 as output mode
	mov r0, #0x400
	ldr r1, =GPIOA_MODER
	ldr r2, [r1]
	and r2, #0xFFFFF3FF
	orr r2, r2, r0
	str r2, [r1]

	// set pins PB3-6 as input mode
	mov r0, #0
	ldr r1, =GPIOB_MODER
	ldr r2, [r1]
	and r2, #0xFFFFC03F
	orr r2, r2, r0
	str r2, [r1]

	// keep PB3-6 PUPDR as the default value(pull-up).
	// set PB3-6 as Pull-up
	mov r0, #0x1640
	ldr r1, =GPIOB_PUPDR
	str r0, [r1]

	// set PA5 speed register
	mov r0, #0x800
	ldr r1, =GPIOA_OSPEEDR
	ldr r2, [r1]
	and r2, #0xFFFFF3FF
	orr r2, r2, r0
	str r2, [r1]

	// set PB3-6 speed register
	mov r0, #0x2A80
	ldr r1, =GPIOB_OSPEEDR
	ldr r2, [r1]
	and r2, #0xFFFFC03F
	orr r2, r2, r0
	str r2, [r1]

	// set PC13 as input mode
	mov r0, #0
	ldr r1, =GPIOC_MODER
	ldr r2, [r1]
	and r2, #0xF3FFFFFF
	orr r2, r2, r0
	str r2, [r1]

	// set PC13 as Pull-up
	mov r0, #0x4000000
	ldr r1, =GPIOC_PUPDR
	str r0, [r1]

	bx lr
