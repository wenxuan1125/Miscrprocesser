	.syntax unified
	.cpu cortex-m4
	.thumb
.data
	//TODO: put your student id here
	student_id: .byte 4, 0, 0, 6, 1, 7, 0
	user_stack_bottom: .zero 128	//.zero <number_of_bytes>
.text
	.global main
	.equ RCC_AHB2ENR, 0x4002104c	//enable port
	.equ GPIOB_MODER, 0x48000400	//pin mode( input, output...)
	.equ GPIOB_OTYPER, 0x48000404	//push pull/open drain
	.equ GPIOB_OSPEEDR, 0x48000408	//speed
	.equ GPIOB_PUPDR, 0x4800040C	//pull up/down
	.equ GPIOB_ODR, 0x48000414	//output address
	.equ GPIOB_BSRR, 0x48000418
	.equ GPIOB_BRR, 0x48000428
	//MAX7219
	.equ DECODE_MODE, 0x09		//decode mode
	.equ DISPLAY_TEST, 0x0F
	.equ SCAN_LIMIT, 0x0B
	.equ INTENSITY, 0x0A
	.equ SHUTDOWN, 0x0C
	.equ DIN, 0x10	//PB4
	.equ CS, 0x20	//PB5
	.equ CLK, 0x8 //PB3
main:
	bl stack_init
	bl GPIO_init
	bl max7219_init


	//TODO: display your student id on 7-Seg LED
	ldr r9, =student_id

	mov r0, #1
	ldrb r1, [r9, #0]	// load byte from address r2+0
	bl max7219send

	mov r0, #2
	ldrb r1, [r9, #1]	// load byte from address r2+1
	bl max7219send

	mov r0, #3
	ldrb r1, [r9, #2]	// load byte from address r2+2
	bl max7219send

	mov r0, #4
	ldrb r1, [r9, #3]	// load byte from address r2+3
	bl max7219send

	mov r0, #5
	ldrb r1, [r9, #4]	// load byte from address r2+4
	bl max7219send

	mov r0, #6
	ldrb r1, [r9, #5]	// load byte from address r2+5
	bl max7219send

	mov r0, #7
	ldrb r1, [r9, #6]	// load byte from address r2+6
	bl max7219send

Program_end:
	b Program_end

stack_init:
	//todo: Setup the stack pointer(sp) to user_stack.
	ldr r2, =user_stack_bottom
	add r2, r2, #128
	msr msp, r2		// move the value in r2 to msp ( main stack pointer)
	bx lr

max7219send:
	//input parameter: r0 is ADDRESS , r1 is DATA
	//TODO: Use this function to send a message to max7219

	lsl r0, r0, #8
	add r0, r0, r1	//shift left 8 bits to connect the data

	ldr r1, =#CS
	ldr r2, =#DIN
	ldr r3, =#CLK
	ldr r4, =#GPIOB_BSRR
	ldr r5, =#GPIOB_BRR
	mov r6, #16	// r6 is i

max7219send_loop:
	mov r7, #1
	sub r8, r6, #1
	lsl r7, r7, r8	// r7 is mask
	str r3, [r5]
	tst r0,  r7
	beq bit_not_set
	str r2, [r4]
	b if_done

bit_not_set:
	str r2, [r5]

if_done:
	str r3, [r4]
	subs r6, r6, #1
	bgt max7219send_loop
	str r1, [r5]
	str r1, [r4]


	bx lr
max7219_init:
	//TODO: Initial max7219 registers.
	push {lr}
	ldr r0, =#DECODE_MODE
	ldr r1, =#0xff
	bl max7219send

	ldr r0, =#DISPLAY_TEST
	ldr r1, =#0x0	// normal operation
	bl max7219send

	ldr r0, =#SCAN_LIMIT
	ldr r1, =#0x06	// display digit 0-6
	bl max7219send

	ldr r0, =#INTENSITY
	ldr r1, =#0xA
	bl max7219send

	ldr r0, =#SHUTDOWN
	ldr r1, =#0x1	// normal operation
	bl max7219send

	pop {lr}
	bx lr

GPIO_init:
	//TODO: Initialize three GPIO pins as output for max7219 DIN, CS and CLK
	// enable AHB2 clock port b
	mov r0, #0x2
	ldr r1, =RCC_AHB2ENR
	str r0, [r1]

	// set pins PB3-5 as output mode
	mov r0, #0x540
	ldr r1, =GPIOB_MODER
	ldr r2, [r1]
	and r2, #0xFFFFF03F
	orr r2, r2, r0
	str r2, [r1]

	// keep PUPDR as the default value(pull-up).
	// set output speed register
	mov r0, #0xFC0
	ldr r1, =GPIOB_OSPEEDR
	ldr r2, [r1]
	and r2, #0xFFFFF03F
	orr r2, r2, r0
	str r2, [r1]

	bx lr
