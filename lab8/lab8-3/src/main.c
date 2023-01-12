#include <stdlib.h>
#include <string.h>
#include "stm32l476xx.h"
#define SET_REG(REG, MASK, VAL) {((REG)=((REG) & (MASK)) | (VAL));};
char send[32];
char buf[300];
int ADC_data = 1;

void GPIO_init(){

	// enable GPIOA, GPIOB and GPIOC
	// PA5 for LED (active high)
	SET_REG(RCC->AHB2ENR, 0xFFFFFFF8, 0x7)
	// set PA5 as output mode
	SET_REG(GPIOA->MODER, 0xFFFFF3FF, 0x400)
	// set PA5 speed register
	SET_REG(GPIOA->OSPEEDR, 0xFFFFF3FF, 0xC00)

	// PC13 for user button
	// set PC13 as input mode
	SET_REG(GPIOC->MODER, 0xF3FFFFFF, 0x0)
	// set PC13 as Pull-up
	SET_REG(GPIOC->PUPDR, 0xF3FFFFFF, 0x4000000)
	// set PC13 speed
	SET_REG(GPIOC->OSPEEDR, 0xF3FFFFFF, 0xC000000)

	// PC10 for tx, PC11 for rx, af mode
	SET_REG(GPIOC->MODER, 0xFF0FFFFF, 0xA00000)
	// set PC10, PC11 speed
	SET_REG(GPIOC->OSPEEDR, 0xFF0FFFFF, 0xF00000)
	// set PC10, PC11 push-pull
	SET_REG(GPIOC->OTYPER, 0xF3FF, 0x0)
	// set PC10, PC11 no pull-up, no pull-down
	SET_REG(GPIOC->PUPDR, 0xFF0FFFFF, 0x0)

	// set PC10, PC11 alternate function mode as AF7(USART1-3)
	SET_REG(GPIOC->AFR[1], 0xFFFF00FF, 0x7700)

	// PC0 to ADC123_IN1
	// set PC0 as analog mode (ADC input)
	SET_REG(GPIOC->MODER, 0xFFFFFFFE, 0x3)
	// set PC0 as Pull-up
	SET_REG(GPIOC->PUPDR, 0xFFFFFFFE, 0x1)
	// set PC0 speed
	SET_REG(GPIOC->OSPEEDR, 0xFFFFFFFE, 0x3)
	// connect analog switch to the ADC input
	SET_REG(GPIOC->ASCR, 0xFFFFFFFE, 0x1)

}
void init_UART() {
	// Initialize UART registers


	// enable USART3 clock
	SET_REG(RCC->APB1ENR1, 0xFFFBFFFF, 0x40000)

	// reset value:
	// turn off CLKEN, Due to asynchronous
	// turn off Other Mode
	// over-sampling 16


	// set USARTDIV
	SET_REG(USART3->BRR, 0xFFFFFF00, 4000000/9600)

	// Set word length as 8 bit, 1 start bit
	SET_REG(USART3->CR1, 0xEFFFEFFF, 0x0)

	// Set stop bit as 1 bit
	//SET_REG(USART3->CR2, 0xFFFFBFFF, 0x0)
	SET_REG(USART3->CR2, 0xFFFFBFFF, 0x1100)

	// enable Rx/Tx
	SET_REG(USART3->CR1, 0xFFFFFFF3, 0xC)

	// enable USART
	SET_REG(USART3->CR1, 0xFFFFFFFE, 0x1)


}
void configureADC() {
	// TODO setting ADC register
	// ADC1_IN1

	// enable ADC clock
	SET_REG(RCC->AHB2ENR, 0xFFFFDFFF, 0x2000)

	// only 1 conversion in the regular channel conversion sequence
	SET_REG(ADC1->SQR1, 0xFFFFFFF0, 0x0)
	// channel 1 ( mapping to PC0) is the 1st conversion in regular sequence
	SET_REG(ADC1->SQR1, 0xFFFFF83F, 0x40)

	// sampling time, 12.5 ADC clock cycles
	SET_REG(ADC1->SMPR1, 0xFFFFFFC7, 0x10)

	// single conversion mode
	SET_REG(ADC1->CFGR, 0xFFFFDFFF, 0x0)
	// data resolution as 12 bit
	SET_REG(ADC1->CFGR, 0xFFFFFFE7, 0x0)
	ADC1->CFGR &= ~ADC_CFGR_ALIGN;
	// hardware trigger detection disabled (conversions can be launched by software)
	SET_REG(ADC1->CFGR, 0xFFFFF3FF, 0x0)

	ADC123_COMMON->CCR |= 1 << 16; // ckmode
	ADC123_COMMON->CCR |= 4 << 8; // delay

	// end of regular conversion interrupt enable
	SET_REG(ADC1->IER, 0xFFFFFFFB, 0x4)

	// enables an interrupt or exception
	NVIC_EnableIRQ(ADC1_2_IRQn );



}
void startADC() {
	// TODO enable ADC


	//ADC exits Deep-power down mode
	SET_REG(ADC1->CR, 0xDFFFFFFF, 0x0)

	// ADC Voltage regulator enabled
	SET_REG(ADC1->CR, 0xEFFFFFFF, 0x10000000)
	// write 1 to enable the ADC
	SET_REG(ADC1->CR, 0xFFFFFFFE, 0x1)

	// wait for ADRDY=1
	while( (ADC1->ISR & 0x1)==0);
	// start regular conversion
	SET_REG(ADC1->CR, 0xFFFFFFFB, 0x4)

}
void SysTick_config() {

	// SysTick exception request enable
	SET_REG(SysTick->CTRL, 0xFFFFFFFD, 0x2)
	// RELOAD value=250000
	SET_REG(SysTick->LOAD, 0xFF000000, 250000)
	// counter enable
	SET_REG(SysTick->CTRL, 0xFFFFFFFE, 0x1)
}
void SysTick_Handler() {
	startADC();
	UART_Transmit_Number(ADC_data);

}


void ADC1_2_IRQHandler() {

	// wait for conversion complete
	while (!(ADC1->ISR & 0x4));

	ADC_data=(ADC1->DR) & 0xFFFF;

	NVIC_ClearPendingIRQ(ADC1_2_IRQn);

}
int UART_Transmit(uint8_t *arr, uint32_t size) {
	//TODO: Send str to UART and return how many bytes are successfully transmitted.
	for( int i=0; i<size; i++){

		USART3->TDR = *(arr+i);

		// wait for the character transmission to be completed
		while((USART3->ISR & 0x40) == 0);
	}

	return size;

}

void UART_Transmit_Number(int n) {
	int dig[12] = {0};
	for (int i = 0; i < 12; i ++) {
		dig[i] = n % 10;
		n /= 10;
	}
	for (int i = 11; i >= 0; i --) {
		char c = '0' + dig[i];
		UART_Transmit((uint8_t*)&c, 1);
	}

	//\012(\r):把游標移到行首,\015(\n):換行
	UART_Transmit((uint8_t*)"\r\n", 2);
}

char UART_Receive() {
	// TODO receive one character from UART

	// read data register not empty
	while (!(USART3->ISR & 0x20));


	// receive data value
	return USART3->RDR & 0xFF;
}

void read_cmd() {
	int ptr = 0;
	char c;
	do {
		c = UART_Receive();
		UART_Transmit((uint8_t*)&c, 1);


		if(c==8){
			//backspace
			UART_Transmit(" \b", 2);
			if(ptr>0)
				ptr--;
			else
				ptr=0;
		}

		else{
			buf[ptr] = c;
			ptr++;

		}


	} while (c != '\n' && c != '\r');
	buf[ptr++] = '\0';
	//buf[max_len++]='\0';
	UART_Transmit((uint8_t*)"\r\n", 2);
}


int main(){

	GPIO_init();
	init_UART();
	configureADC();


	while(1){
		UART_Transmit("> ", 2);
		read_cmd();

		if(buf[0]==13){
			// enter
			//UART_Transmit((uint8_t*)"\r\n", 2);
		}
		else if (strncmp(buf, "showid", 6) == 0) {
			UART_Transmit((uint8_t*)"0716004\r\n", 9);
		} else if (strncmp(buf, "light", 5) == 0) {
			SysTick_config();
			char c;
			do {
				c = UART_Receive();

			} while (c != 'q');

			// systick disable
			SET_REG(SysTick->CTRL, 0xFFFFFFFE, 0x0)
		} else if (strncmp(buf, "led on", 6) == 0) {
			GPIOA->ODR |= (1 << 5);
		} else if (strncmp(buf, "led off", 7) == 0) {
			GPIOA->ODR &= ~(1 << 5);
		} else {
			//UART_Transmit((uint8_t*)buf, 6);
			//UART_Transmit((uint8_t*)"\r\n", 2);
			UART_Transmit((uint8_t*)"Unknown Command\r\n", 20);

		}


	}

	return 0;
}
