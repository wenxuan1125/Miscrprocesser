#include "stm32l476xx.h"
#define TIME_SEC 23.90
extern void GPIO_init();
extern void max7219_init();
extern void max7219_send(unsigned char address, unsigned char
data);
#define SET_REG(REG, MASK, VAL) {((REG)=((REG) & (MASK)) | (VAL));};
//extern void Display();
//void Timer_init( TIM_TypeDef *timer)
void Timer_init() {
	//TODO: Initialize timer5

	// enable TIM5
	SET_REG(RCC->APB1ENR1, 0xFFFFFFF7, 0x8)
	// Tevent=(PSC+1)*(ARR+1)*Tint, Tevent=0.01 sec
	// set TIM5 prescalar register
	SET_REG(TIM5->PSC, 0xFFFF0000, 0x3E7)	// prescalar=999(+1)
	// set TIM5 auto-reload register
	SET_REG(TIM5->ARR, 0x0, 0x27)	// auto-reload=39(+1)
	// re-initializes TIM5 and generates an update of the registers
	SET_REG(TIM5->EGR, 0xFFFFFFFE, 0x1)
	// set TIM5 as up-counter
	SET_REG(TIM5->CR1, 0xFFFFFFEF, 0x10)
	// set TIM5 control register, start timer
	SET_REG(TIM5->CR1, 0xFFFFFFFE, 0x1)
}

void Display( int num){


	int digit;
	if( num<100){
		for( int i=1; i<=2; i++){
			digit=num%10;
			num=num/10;

			max7219_send(i, digit);
		}
		max7219_send(3, 128);  // '0' and decimal point

	}
	else{
		for( int i=1; i<=7; i++){
			digit=num%10;
			num=num/10;

			if( i==3)
				digit= digit | 0x80;	// decimal point

			max7219_send(i, digit);

			if(num==0)
				break;
		}
	}

}
/*
void Timer_start(TIM_TypeDef *timer) {
	//TODO: start timer and show the time on the 7-SEG LED.
}*/

int main(){
	GPIO_init();
	max7219_init();
	// clear
	for( int i=1; i<8; i++)
		max7219_send(i, 0xF);

	Timer_init();
	int num=0;
	while(num<=TIME_SEC*100+0.5) {
		//TODO: Polling the timer count and do lab requirements

		Display(num);

		while(1){
			int timer_val=TIM5->CNT & 0xFFFFFFFF;
			if( timer_val>=39)
				break;
		}
		num++;

	}
}
