	.syntax unified
	.cpu cortex-m4
	.thumb
.text
	.global max7219_init
	//MAX7219
	.equ DECODE_MODE, 0x09		//decode mode
	.equ DISPLAY_TEST, 0x0F
	.equ SCAN_LIMIT, 0x0B
	.equ INTENSITY, 0x0A
	.equ SHUTDOWN, 0x0C

max7219_init:
	//TODO: Initial max7219 registers.
	push {lr}
	ldr r0, =#DECODE_MODE
	ldr r1, =#0xff
	bl max7219_send

	ldr r0, =#DISPLAY_TEST
	ldr r1, =#0x0	// normal operation
	bl max7219_send

	ldr r0, =#SCAN_LIMIT
	ldr r1, =#0x01	// display digit 0-6
	bl max7219_send

	ldr r0, =#INTENSITY
	ldr r1, =#0xA
	bl max7219_send

	ldr r0, =#SHUTDOWN
	ldr r1, =#0x1	// normal operation
	bl max7219_send

	//clear
	mov r0, #1
	mov r1, #0x0
	push {r2, lr}
	bl max7219_send
	pop {r2, lr}

	mov r0, #2
	mov r1, #0x0
	push {r2, lr}
	bl max7219_send
	pop {r2, lr}

	mov r0, #3
	mov r1, #0x0
	push {r2, lr}
	bl max7219_send
	pop {r2, lr}

	mov r0, #4
	mov r1, #0x0
	push {r2, lr}
	bl max7219_send
	pop {r2, lr}

	mov r0, #5
	mov r1, #0x0
	push {r2, lr}
	bl max7219_send
	pop {r2, lr}

	mov r0, #6
	mov r1, #0x0
	push {r2, lr}
	bl max7219_send
	pop {r2, lr}

	mov r0, #7
	mov r1, #0x0
	push {r2, lr}
	bl max7219_send
	pop {r2, lr}


	mov r0, #8
	mov r1, #0x0
	push {r2, lr}
	bl max7219_send
	pop {r2, lr}

	pop {lr}
	bx lr
