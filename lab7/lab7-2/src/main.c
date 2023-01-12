#include "stm32l476xx.h"
#define SET_REG(REG, MASK, VAL) {((REG)=((REG) & (MASK)) | (VAL));};
#define X0 0b1000000	//Pb6
#define X1 0b10000000	//Pb7
#define X2 0b100000000	//Pb8
#define X3 0b1000000000	//Pb9
#define Y0 0b1			//Pc0
#define Y1 0b10			//Pc1
#define Y2 0b100		//Pc2
#define Y3 0b1000		//Pc3

unsigned int x_pin[4] = {X0, X1, X2, X3};
unsigned int y_pin[4] = {Y0, Y1, Y2, Y3};
int table[4][4]={ 1, 2, 3, 10,
				   4, 5, 6, 11,
				   7, 8, 9, 12,
				   15, 0, 14, 13};

void GPIO_init() {
	// enable GPIOA, GPIOB and GPIOC
	// PA5 for LED (active high)
	SET_REG(RCC->AHB2ENR, 0xFFFFFFF8, 0x7)
	// set PA5 as output mode
	SET_REG(GPIOA->MODER, 0xFFFFF3FF, 0x400)
	// set PA5 speed register
	SET_REG(GPIOA->OSPEEDR, 0xFFFFF3FF, 0xC00)

	// set pins PB6-9 as output mode
	SET_REG(GPIOB->MODER, 0xFFF00FFF, 0x55000)
	// set pins PC0-3 as input mode
	SET_REG(GPIOC->MODER, 0xFFFFFF00, 0x0)


	// set PC0-3 as Pull-down
	SET_REG(GPIOC->PUPDR, 0xFFFFFF00, 0xAA)
	// set PB6-9 speed as Very-high
	SET_REG(GPIOB->OSPEEDR, 0xFFF00FFF, 0xFF000)
	// set PC0-3 speed as Very-high
	SET_REG(GPIOC->OSPEEDR, 0xFFFFFF00, 0xFF)
}
int keypad_scan(){
	int read_val;

	for(int i = 0; i < 4; i++){
		SET_REG(GPIOB->ODR, 0xFFFFFC3F, x_pin[i])

		for(int j = 0; j < 4; j++){
			read_val = GPIOC->IDR & y_pin[j];

			if(read_val != 0){
				return table[j][i];
			}
		}
	}
	return -1;
}


void EXTI_config() {

	// enable SYSCFG
	SET_REG(RCC->APB2ENR, 0xFFFFFFFE, 0x1)
	// configure EXTI0, EXTI1, EXTI2 and EXTI3 input as pc0-3
	SET_REG(SYSCFG->EXTICR[0], 0xFFFF0000, 0x2222)
	// interrupt on line0-3 is not masked
	SET_REG(EXTI->IMR1, 0xFFFFFFF0, 0xF)
	// falling trigger enabled for line0-3
	SET_REG(EXTI->FTSR1, 0xFFFFFFF0, 0xF)
	//SET_REG(EXTI->RTSR1, 0xFFFFFFF0, 0xF)

}
void NVIC_config() {

	// enables an interrupt or exception
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);
	NVIC_EnableIRQ(EXTI3_IRQn);
}
void EXTI0_IRQHandler() {
	int num=keypad_scan();

	// debounce
	//while( keypad_scan()==num);

	for( int i=0; i<num; i++){
		// turn on LED
		SET_REG(GPIOA->ODR, 0xFFDF, 0x20)
		// delay 0.5 sec
		for( int j=0; j<100000; j++);
		// turn off LED
		SET_REG(GPIOA->ODR, 0xFFDF, 0x0)
		// delay 0.5 sec
		for( int j=0; j<100000; j++);
	}

	// interrupt end, clear pending interrupt flag for line0-3
	SET_REG(EXTI->PR1, 0xFFFFFFF0, 0xF)
}
void EXTI1_IRQHandler() {
	int num=keypad_scan();

	// debounce
	//while( keypad_scan()==num);

	for( int i=0; i<num; i++){
		// turn on LED
		SET_REG(GPIOA->ODR, 0xFFDF, 0x20)
		// delay 0.5 sec
		for( int j=0; j<100000; j++);
		// turn off LED
		SET_REG(GPIOA->ODR, 0xFFDF, 0x0)
		// delay 0.5 sec
		for( int j=0; j<100000; j++);
	}

	// interrupt end, clear pending interrupt flag for lin0-3
	SET_REG(EXTI->PR1, 0xFFFFFFF0, 0xF)
}
void EXTI2_IRQHandler() {
	int num=keypad_scan();

	// debounce
	//while( keypad_scan()==num);

	for( int i=0; i<num; i++){
		// turn on LED
		SET_REG(GPIOA->ODR, 0xFFDF, 0x20)
		// delay 0.5 sec
		for( int j=0; j<100000; j++);
		// turn off LED
		SET_REG(GPIOA->ODR, 0xFFDF, 0x0)
		// delay 0.5 sec
		for( int j=0; j<100000; j++);
	}

	// interrupt end, clear pending interrupt flag for line0-3
	SET_REG(EXTI->PR1, 0xFFFFFFF0, 0xF)
}
void EXTI3_IRQHandler() {
	int num=keypad_scan();

	// debounce
	//while( keypad_scan()==num);

	for( int i=0; i<num; i++){
		// turn on LED
		SET_REG(GPIOA->ODR, 0xFFDF, 0x20)
		// delay 0.5 sec
		for( int j=0; j<100000; j++);
		// turn off LED
		SET_REG(GPIOA->ODR, 0xFFDF, 0x0)
		// delay 0.5 sec
		for( int j=0; j<100000; j++);
	}

	// interrupt end, clear pending interrupt flag for line0-3
	SET_REG(EXTI->PR1, 0xFFFFFFF0, 0xF)
}
int main() {
	NVIC_config();
	EXTI_config();
	GPIO_init();

	//SET_REG(GPIOB->ODR, 0xFFFFFC3F, 0x3C0)

	while(1){
		// make keypad detect the interrupt
		SET_REG(GPIOB->ODR, 0xFFFFFC3F, x_pin[0])
		SET_REG(GPIOB->ODR, 0xFFFFFC3F, x_pin[1])
		SET_REG(GPIOB->ODR, 0xFFFFFC3F, x_pin[2])
		SET_REG(GPIOB->ODR, 0xFFFFFC3F, x_pin[3])

		// turn on LED
		SET_REG(GPIOA->ODR, 0xFFDF, 0x20);
	}


}
