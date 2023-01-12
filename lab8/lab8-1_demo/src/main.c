#include "stm32l476xx.h"
#define SET_REG(REG, MASK, VAL) {((REG)=((REG) & (MASK)) | (VAL));};
#define MODIFY_REG(REG, MASK, VAL) {((REG)=((REG) & ~(MASK)) | (VAL));};

void GPIO_init(){
	// enable GPIOC
	SET_REG(RCC->AHB2ENR, 0xFFFFFFFB, 0x4)

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
void init_UART() {
	// Initialize UART registers

	//  AHB prescaler=2, set HCLK=2MHz
	SET_REG(RCC->CFGR, 0xFFFFFF0F, 0x80)

	// enable USART3 clock
	SET_REG(RCC->APB1ENR1, 0xFFFBFFFF, 0x40000)

	// reset value:
	// turn off CLKEN, Due to asynchronous
	// turn off Other Mode
	// over-sampling 16


	// set USARTDIV
	SET_REG(USART3->BRR, 0xFFFF0000, 2000000/115200)

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

int main(){

	GPIO_init();
	init_UART();

	// wait for the user button to be pressed

	int flag = 0;
		while (1) {
			while ((GPIOC->IDR&(1 << 13)) != 0) {
				flag++;
			}
			//\012:把游標移到行首,\015:換行
			if (flag > 500) {
				UART_Transmit("Hello World!\012\015", 14);
				flag = 0;
			}
		}

	return 0;
}

