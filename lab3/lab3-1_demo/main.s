	.syntax unified
	.cpu cortex-m4
	.thumb

.data
	leds: .byte 0
.text
	.global main
	.equ RCC_AHB2ENR, 0x4002104c	//enable port
	.equ GPIOB_MODER, 0x48000400	//pin mode( input, output...)
	.equ GPIOB_OTYPER, 0x48000404	//push pull/open drain
	.equ GPIOB_OSPEEDR, 0x48000408	//speed
	.equ GPIOB_PUPDR, 0x4800040C	//pull up/down
	.equ GPIOB_ODR, 0x48000414	//output address

main:
	bl GPIO_init
	movs r1, #1
	ldr r0, =leds
	strb r1, [r0]
	mov r3, #0	//r3 is i
Loop:
	/* todo: write the display pattern into leds variable */
	cmp r3, #0
	ittt eq
	moveq r1, #1
	ldreq r0, =leds
	strbeq r1, [r0]


	cmp r3, #1
	ittt eq
	moveq r1, #3
	ldreq r0, =leds
	strbeq r1, [r0]

	cmp r3, #2
	ittt eq
	moveq r1, #6
	ldreq r0, =leds
	strbeq r1, [r0]

	cmp r3, #3
	ittt eq
	moveq r1, #12
	ldreq r0, =leds
	strbeq r1, [r0]

	cmp r3, #4
	ittt eq
	moveq r1, #8
	ldreq r0, =leds
	strbeq r1, [r0]

	cmp r3, #5
	ittt eq
	moveq r1, #12
	ldreq r0, =leds
	strbeq r1, [r0]

	cmp r3, #6
	ittt eq
	moveq r1, #6
	ldreq r0, =leds
	strbeq r1, [r0]

	cmp r3, #7
	ittt eq
	moveq r1, #3
	ldreq r0, =leds
	strbeq r1, [r0]

	cmp r3, #7
	ite eq
	moveq r3, #0
	addne r3, r3, #1


	bl DisplayLED
	//mov r4, #0
	ldr r4, =#1000000
	bl Delay
	b Loop

GPIO_init:
	/* todo: initialize LED GPIO pins as output */

	// enable AHB2 clock port b
	mov r0, #0x2
	ldr r1, =RCC_AHB2ENR
	str r0, [r1]

	// set pins PB3-6 as output mode
	mov r0, #0x1540
	ldr r1, =GPIOB_MODER
	ldr r2, [r1]
	and r2, #0xFFFFC03F
	orr r2, r2, r0
	str r2, [r1]


	// keep PUPDR as the default value(pull-up).
/*
	mov r0, #0x2A80
	ldr r1, =GPIOB_OSPEEDR
	ldr r2, [r1]
	and r2, #0xFFFFC03F
	orr r2, r2, r0
	str r2, [r1]*/


	// set output speed register
	mov r0, #0x2A80
	ldr r1, =GPIOB_OSPEEDR
	ldr r2, [r1]
	and r2, #0xFFFFC03F
	orr r2, r2, r0
	str r2, [r1]

	bx lr

DisplayLED:
	/* todo: display LED by leds */
	ldr r2, =GPIOB_ODR

	lsl r1, r1, #3	// shift left 3
	strh r1, [r2]	//set the output

	bx lr
Delay:
	/* todo: write a delay 1 sec function */
	// you can implement this part by busy waiting.
	// timer and interrupt will be introduced in later lectures.

	cmp r4, #0
	itt gt
	subgt r4, r4, #1
	bgt Delay

	bx lr
