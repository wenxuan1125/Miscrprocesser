#include "cmsis_gcc.h"
#include "core_cm4.h"
#include "core_cmFunc.h"
#include "core_cmInstr.h"
#include "core_cmSimd.h"
#include "stm32l476xx.h"
#include "system_stm32l4xx.h"
#define SET_REG(REG, MASK, VAL) {((REG)=((REG) & (MASK)) | (VAL));};

void GPIO_init(){

	// enable GPIOA and GPIOC
	// PA5 for LED, PC13 for user button
	SET_REG(RCC->AHB2ENR, 0xFFFFFFFA, 0x5)
	// set PA5 as output mode
	SET_REG(GPIOA->MODER, 0xFFFFF3FF, 0x400)
	// set PA5 speed register
	SET_REG(GPIOA->OSPEEDR, 0xFFFFF3FF, 0xC00)

	// set PC13 as input mode
	SET_REG(GPIOC->MODER, 0xF3FFFFFF, 0x0)
	// set PC13 as Pull-up
	SET_REG(GPIOA->PUPDR, 0xF3FFFFFF, 0x4000000)
}
void TIM7_init(){
	// enable TIM7
	SET_REG(RCC->APB1ENR1, 0xFFFFFFDF, 0x20)
	// set TIM7 prescalar register
	SET_REG(TIM7->PSC, 0xFFFF0000, 0x3E7)	// prescalar=999(+1)
	// set TIM7 auto-reload register
	SET_REG(TIM7->ARR, 0xFFFF0000, 0xF9F)	// auto-reload=3999(+1)
	// re-initializes TIM7 and generates an update of the registers
	SET_REG(TIM7->EGR, 0xFFFFFFFE, 0x1)
	// set TIM7 control register, start timer
	SET_REG(TIM7->CR1, 0xFFFFFFFE, 0x1)

}

void Delay1sUnder4MHz(){
	while(1){
		int timer_val=TIM7->CNT & 0xFFFF;
		if( timer_val>=3999)
			break;
	}


}
void Set_HCLK(int freq){
	// 1. change to the temporary clock source if needed
	// 2. set the target clock source
	// 3. change to the target clock source


	// set TIM7 control register, stop timer
	SET_REG(TIM7->CR1, 0xFFFFFFFE, 0x0)

	// CFGR reset value
	SET_REG(RCC->CFGR, 0x0, 0x0);

	// disable the PLL by setting PLLON to 0
	SET_REG(RCC->CR, 0xFEFFFFFF, 0x0)

	// wait until PLLRDY is cleared and PLL is now fully stopped
	while (RCC->CR & 0x2000000);


	// change PLL parameter
	if(freq==1){

		// PLLM=1, PLLN=16, PLLR=4, PLL as system clock
		SET_REG(RCC->PLLCFGR, 0xF9FF808C, 0x2001001);
		// AHB prescalar=16
		SET_REG(RCC->CFGR, 0xFFFFFF0F, 0xB0);
	}
	else if(freq==6){

		// PLLM=1, PLLN=24, PLLR=4, PLL as system clock
		SET_REG(RCC->PLLCFGR, 0xF9FF808C, 0x2001801);
		// AHB prescalar=4
		SET_REG(RCC->CFGR, 0xFFFFFF0F, 0x90);

	}
	else if(freq==10){

		// PLLM=1, PLLN=40, PLLR=4, PLL as system clock
		SET_REG(RCC->PLLCFGR, 0xF9FF808C, 0x2002801);
		// AHB prescalar=4
		SET_REG(RCC->CFGR, 0xFFFFFF0F, 0x90);

	}
	else if(freq==16){

		// PLLM=1, PLLN=64, PLLR=4, PLL as system clock
		SET_REG(RCC->PLLCFGR, 0xF9FF808C, 0x2004001);
		// AHB prescalar=4
		SET_REG(RCC->CFGR, 0xFFFFFF0F, 0x90);

	}
	else{

		// PLLM=1, PLLN=40, PLLR=4, PLL as system clock
		SET_REG(RCC->PLLCFGR, 0xF9FF808C, 0x2002801);
		// AHB prescalar=1
		SET_REG(RCC->CFGR, 0xFFFFFF0F, 0x0);

	}

	// enable the PLL again by setting PLLON to 1
	SET_REG(RCC->CR, 0xFEFFFFFF, 0x1000000)
	// wait until PLLRDY is ready
	while (!(RCC->CR & 0x02000000));
	// enable the desired PLL outputs (PLLCLK) by configuring PLLREN
	SET_REG(RCC->PLLCFGR, 0xFEFFFFFF, 0x1000000);
	//system clock switch: PLL selected as system clock
	SET_REG(RCC->CFGR, 0xFFFFFFFC, 0x3);

	// set TIM7 control register, start timer
	SET_REG(TIM7->CR1, 0xFFFFFFFE, 0x1)


}
int main(){
	// Do initializations.
	GPIO_init();
	TIM7_init();

	int freq[] = {1, 6, 10, 16, 40};
	int i=0;
	for(;;){
		// change LED state
		// active high
		SET_REG(GPIOA->ODR, 0xFFFFFFDF, 0x20); 	//
		Delay1sUnder4MHz();
		SET_REG(GPIOA->ODR, 0xFFFFFFDF, 0x0);
		Delay1sUnder4MHz();

		// change HCLK if button pressed
		int flag=0;
		while(!(GPIOC->IDR & 0x2000))
			flag=1;
		if(flag){
			Set_HCLK(freq[i]);
			i++;
			i=i%5;
		}

	}
}

