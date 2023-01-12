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


void GPIO_init(){
	// enable GPIOA, GPIOB and GPIOC
	// PA0 used to PWM channel1's output of TIM5
	SET_REG(RCC->AHB2ENR, 0xFFFFFFF8, 0x7)
	// set PA0 ( for LED, active high) as alternate function mode
	SET_REG(GPIOA->MODER, 0xFFFFFFFC, 0x2)
	// set PA5 speed register
	SET_REG(GPIOA->OSPEEDR, 0xFFFFFFFC, 0x3)

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
void GPIO_init_AF(){
	//TODO: Initial GPIO pin as alternate function
	// set alternate function selection as AF2 for PA0
	SET_REG(GPIOA->AFR[0], 0xFFFFFFF0, 0x2)

}



void Timer_init(){
	//TODO: Initialize timer

	// enable TIM5
	SET_REG(RCC->APB1ENR1, 0xFFFFFFF7, 0x8)
	// Tevent=(PSC+1)*(ARR+1)*Tint
	// set TIM5 prescalar register
	SET_REG(TIM5->PSC, 0xFFFF0000, 39)	// prescalar=39(+1)
	// set TIM5 auto-reload register
	SET_REG(TIM5->ARR, 0x0, 99)	// auto-reload=99(+1)
	//SET_REG(TIM5->ARR, 0x0, 299)	// auto-reload=299(+1)


	// re-initializes TIM5 and generates an update of the registers
	SET_REG(TIM5->EGR, 0xFFFFFFFE, 0x1)
	// set TIM5 as up-counter
	SET_REG(TIM5->CR1, 0xFFFFFFEF, 0x10)

	// set TIM5 control register, start timer
	//SET_REG(TIM5->CR1, 0xFFFFFFFE, 0x1)
}
void PWM_channel_init(){
	//TODO: Initialize timer PWM channel

	// set CCR1 value = 49
	SET_REG(TIM5->CCR1, 0x0, 49)
	//SET_REG(TIM5->CCR1, 0x0, 149)

	// set CC1S as 00 ( CC1 channel configured as output)
	// set OC1M as 111 ( TIMx_CNT<TIMx_CCR1 is inactive)
	SET_REG(TIM5->CCMR1, 0xFFFFFF8C, 0x70)

	// enable CH1 channel ( OC1 signal is output on the corresponding output pin)
	SET_REG(TIM5->CCER, 0xFFFFFFFE, 0x1)
	// set TIM5 control register, start timer
	SET_REG(TIM5->CR1, 0xFFFFFFFE, 0x1)

}
void PWM_change( int value){

	// set TIM5 control register, stop timer
	SET_REG(TIM5->CR1, 0xFFFFFFFE, 0x1)

	// change CCR1 value
	SET_REG(TIM5->CCR1, 0xFFFF0000, value)
	// set CC1 channel as output, and if TIMx_CNT<TIMx_CCR1, output is inactive
	SET_REG(TIM5->CCMR1, 0xFFFFFF8C, 0x70)
	// enable CC1 channel
	SET_REG(TIM5->CCER, 0xFFFFFFFE, 0x1)

	// set TIM5 control register, start timer
	SET_REG(TIM5->CR1, 0xFFFFFFFE, 0x1)


}

char keypad_scan(){
	char read_val=0;
	int flag=0;
	for( int i=0; i<4; i++){
		SET_REG(GPIOB->ODR, 0xFFFFFC3F, x_pin[i]);

		for( int j=0; j<4; j++){


			while(GPIOC->IDR&y_pin[j])
				flag=1;

			if(flag){
				if(i==2 && j==3)
					return '+';
				else if(i==0 && j==3)
					return '-';
			}
		}
	}

	return 0;
}

int main(){
	GPIO_init();
	GPIO_init_AF();


	Timer_init();
	PWM_channel_init();

	//TODO: Scan the keypad and use PWM to send to LED
	int value=49;
	//int value=149;
	while(1){
		char mode=keypad_scan();
		if( mode=='+'){
			// add

			if( value>=13)
				value=value-5;
			/*if( value>=40)
				value=value-15;*/



			PWM_change( value);
		}
		else if( mode=='-'){
			//sub
			if( value<=87)
				value=value+5;

			/*if( value<=260)
				value=value+15;*/

			PWM_change( value);
		}
	}
}
