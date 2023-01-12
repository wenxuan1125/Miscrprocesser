	.syntax unified
	.cpu cortex-m4
	.thumb

.data
	arr1: .word 0x19, 0x34, 0x14, 0x32, 0x52, 0x23, 0x61, 0x29
	arr2: .word 0x18, 0x17, 0x33, 0x16, 0xFA, 0x20, 0x55, 0xAC

.text
	.global main

do_sort:
	//todo
	movs r1, #-1		// r1 is i of the outer loop
	b outer_loop

outer_loop:
	cmp r1, #7		// if r1 >= 7, return (outer loop will run 7 times)
	it ge
	bxge lr

	//go to inner loop
	movs r2 ,#7		// r2 is j of the inner loop, the element to be compared
					// compare forward
	adds r1, r1, #1
	b inner_loop


inner_loop:
	//check how many times the inner loop has done
	cmp r2, r1
	it le	//r2 <= r1, go to outer loop
	ble outer_loop


	sub r3, r2, #1 		// r3 = r2-1
	mul r7, r2, r9
	mul r8, r3, r9
	ldr r4, [r0, r7]
	ldr r5, [r0, r8]

	/*ascend
	cmp r4, r5
	ittt lo
	movslo r6, r5
	movslo r5, r4
	movslo r4, r6
	*/

	//descend
	cmp r4, r5
	ittt gt
	movsgt r6, r5
	movsgt r5, r4
	movsgt r4, r6



	str r4, [r0, r7]
	str r5, [r0, r8]


	subs r2, r2, #1
	b inner_loop


main:
	movs r9 ,#4
	ldr r0, =arr1
	bl do_sort
	ldr r0, =arr2
	bl do_sort

L: b L
