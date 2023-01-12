	.syntax unified
	.cpu cortex-m4
	.thumb
.text
	.global GPIO_init
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
	.equ GPIOB_ODR, 0x48000414	//output address

	.equ GPIOC_MODER, 0x48000800	//pin mode( input, output...)
	.equ GPIOC_OTYPER, 0x48000804	//push pull/open drain
	.equ GPIOC_OSPEEDR, 0x48000808	//speed
	.equ GPIOC_PUPDR, 0x4800080C	//pull up/down
	.equ GPIOC_IDR, 0x48000810	//input address


GPIO_init:
	//TODO: Initialize three GPIO pins as output for max7219 DIN, CS and CLK

	// enable AHB2 clock port b
	push {r4, r5, r6}
	mov r4, #0x2
	ldr r5, =RCC_AHB2ENR
	str r4, [r5]

	// set pins PB3-5 as output mode
	mov r4, #0x540
	ldr r5, =GPIOB_MODER
	ldr r6, [r5]
	and r6, #0xFFFFF03F
	orr r6, r6, r4
	str r6, [r5]

	// keep PUPDR as the default value(pull-up).
	// set output speed register
	mov r4, #0xFC0
	ldr r5, =GPIOB_OSPEEDR
	ldr r6, [r5]
	and r6, #0xFFFFF03F
	orr r6, r6, r4
	str r6, [r5]

	pop {r4, r5, r6}
	bx lr

/*
	// enable AHB2 clock port a, b and c
	push {r4, r5, r6}
	mov r4, #0x7
	ldr r5, =RCC_AHB2ENR
	str r4, [r5]


	// set pins PA5-8 as input mode
	mov r4, #0x0
	ldr r5, =GPIOA_MODER
	ldr r6, [r5]
	and r6, #0xFFFC03FF
	orr r6, r6, r4
	str r6, [r5]

	// set pins PB3-5 as output mode
	mov r4, #0x540
	ldr r5, =GPIOB_MODER
	ldr r6, [r5]
	and r6, #0xFFFFF03F
	orr r6, r6, r4
	str r6, [r5]


	// set pins PC5-8 as output mode
	mov r4, #0x15400
	ldr r5, =GPIOC_MODER
	ldr r6, [r5]
	and r6, #0xFFFC03FF
	orr r6, r6, r4
	str r6, [r5]

	// set PA5-8 as Pull-up
	mov r4, #0x15400
	ldr r5, =GPIOA_PUPDR
	ldr r6, [r5]
	and r6, #0xFFFC03FF
	orr r6, r6, r4
	str r6, [r5]

	// set PA5-8 speed as Very-high
	mov r4, #0x3FC00
	ldr r5, =GPIOA_OSPEEDR
	ldr r6, [r5]
	and r6, #0xFFFC03FF
	orr r6, r6, r4
	str r6, [r5]

	// set PB3-5 speed as Very-high
	mov r4, #0xFC0
	ldr r5, =GPIOB_OSPEEDR
	ldr r6, [r5]
	and r6, #0xFFFFF03F
	orr r6, r6, r4
	str r6, [r5]


	// set PC5-8 speed as Very-high
	mov r4, #0x3FC00
	ldr r5, =GPIOC_OSPEEDR
	ldr r6, [r5]
	and r6, #0xFFFC03FF
	orr r6, r6, r4
	str r6, [r5]

	pop {r4, r5, r6}
	bx lr*/

