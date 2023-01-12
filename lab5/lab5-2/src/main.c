#include "stm32l476xx.h"
extern void GPIO_init();
extern void max7219_init();
extern void max7219_send(unsigned char address, unsigned char
data);

//TODO: define your gpio pin
#define X0 0b1000000	//Pb6
#define X1 0b10000000	//Pb7
#define X2 0b100000000	//Pb8
#define X3 0b1000000000	//Pb9
#define Y0 0b1			//Pc0
#define Y1 0b10			//Pc1
#define Y2 0b100		//Pc2
#define Y3 0b1000		//Pc3
#define SET_REG(REG, MASK, VAL) {((REG)=((REG) & (~(MASK))) | (VAL));};

unsigned int x_pin[4] = {X0, X1, X2, X3};
unsigned int y_pin[4] = {Y0, Y1, Y2, Y3};
char table[4][4]={ 1, 2, 3, 10,
				   4, 5, 6, 11,
				   7, 8, 9, 12,
				   15, 0, 14, 13};


/* TODO: initial keypad gpio pin, X as output and Y as input */
void keypad_init(){

	// enable GPIOB
	SET_REG(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN, RCC_AHB2ENR_GPIOBEN)
	// enable GPIOC
	SET_REG(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN, RCC_AHB2ENR_GPIOCEN)


	// mask is complement
	// set pins PB6-9 as output mode
	SET_REG(GPIOB->MODER, 0xFF000, 0x55000)
	// set pins PC0-3 as input mode
	SET_REG(GPIOC->MODER, 0xFF, 0x0)


	// set PC0-3 as Pull-down
	SET_REG(GPIOC->PUPDR, 0xFF, 0xAA)
	// set PB6-9 speed as Very-high
	SET_REG(GPIOB->OSPEEDR, 0xFF000, 0xFF000)
	// set PC0-3 speed as Very-high
	SET_REG(GPIOC->OSPEEDR, 0xFF, 0xFF)
}
/* TODO: scan keypad value
	return: >=0: key-value pressed¡A-1: keypad is free
*/
char keypad_scan(){
	char key_val=-1, read_val=0;

	for( int i=0; i<4; i++){
		SET_REG(GPIOB->ODR, 0x3C0, x_pin[i]);

		for( int j=0; j<4; j++){

			read_val=GPIOC->IDR&y_pin[j];

			if(read_val!=0){
				key_val=table[j][i];
				return key_val;
			}
		}
	}

	return key_val;
}

void display( char display_num){

	if( display_num==255){
		// no button was pressed
		max7219_send(0x1, 0xF);
		max7219_send(0x2, 0xF);
	}
	else if(display_num>9){
		max7219_send(0x1, display_num%10);
		max7219_send(0x2, display_num/10);
	}
	else{
		max7219_send(0x1, display_num);
		max7219_send(0x2, 0xF);
	}

}


int main(){

	GPIO_init();
	max7219_init();
	keypad_init();

	while(1){
   		char key=keypad_scan();
		display(key);
	}

	return 0;
}
