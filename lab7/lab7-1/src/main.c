#include "stm32l476xx.h"
#define SET_REG(REG, MASK, VAL) {((REG)=((REG) & (MASK)) | (VAL));};


void GPIO_init(){

	// enable GPIOA
	// PA5 for LED (active high)
	SET_REG(RCC->AHB2ENR, 0xFFFFFFFE, 0x1)
	// set PA5 as output mode
	SET_REG(GPIOA->MODER, 0xFFFFF3FF, 0x400)
	// set PA5 speed register
	SET_REG(GPIOA->OSPEEDR, 0xFFFFF3FF, 0xC00)

}

void SystemClock_Config() {
	// set HSI as system clock source

	// HSI16 clock enable
	SET_REG(RCC->CR, 0xFFFFFEFF, 0x100)

	// system clock switch to HSI16 oscillator
	SET_REG(RCC->CFGR, 0xFFFFFFFC, 0x1)
	// AHB prescaler, SYSCLK divided by 2
	// before going to SysTick, the clock will be divided by 8
	// so clk=1Mhz
	SET_REG(RCC->CFGR, 0xFFFFFF0F, 0x80)
}
void SysTick_config() {

	// SysTick exception request enable
	SET_REG(SysTick->CTRL, 0xFFFFFFFD, 0x2)
	// RELOAD value=3000000
	SET_REG(SysTick->LOAD, 0xFF000000, 0x2DC6C0)
	// counter enable
	SET_REG(SysTick->CTRL, 0xFFFFFFFE, 0x1)
}
void SysTick_Handler() {
	if((GPIOA->ODR & 0x20) ==0){
		// dark to bright
		SET_REG(GPIOA->ODR, 0xFFDF, 0x20)
	}
	else{
		// bright to dark
		SET_REG(GPIOA->ODR, 0xFFDF, 0x0)
	}
}

int main(){
	GPIO_init();
	SystemClock_Config();
	SysTick_config();
	while(1);
}
