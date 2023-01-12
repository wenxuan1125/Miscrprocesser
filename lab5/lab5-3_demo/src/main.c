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
char pressed[4][4];
char order[4][4];
char press_order=1;

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

void keypad_init2(){

	// enable GPIOB
	SET_REG(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN, RCC_AHB2ENR_GPIOBEN)
	// enable GPIOC
	SET_REG(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN, RCC_AHB2ENR_GPIOCEN)


	// mask is complement
	// set pins PB6-9 as input mode
	SET_REG(GPIOB->MODER, 0xFF000, 0x0)
	// set pins PC0-3 as output mode
	SET_REG(GPIOC->MODER, 0xFF, 0x55)


	// set PB6-9 as Pull-down
	SET_REG(GPIOB->PUPDR, 0xFF00, 0xAA000)
	// set PB6-9 speed as Very-high
	SET_REG(GPIOB->OSPEEDR, 0xFF000, 0xFF000)
	// set PC0-3 speed as Very-high
	SET_REG(GPIOC->OSPEEDR, 0xFF, 0xFF)
}
/* TODO: scan keypad value
	return: >=0: key-value pressed¡A-1: keypad is free
*/
char keypad_scan(){

	char flag=0;
	int read_val=0;

	for( int i=0; i<4; i++){
		for( int j=0; j<4; j++)
			pressed[i][j]=0;
	}

	keypad_init();
	for( int i=0; i<4; i++){
		SET_REG(GPIOB->ODR, 0x3C0, x_pin[i]);

		for( int j=0; j<4; j++){

			read_val=GPIOC->IDR&y_pin[j];

			// if both of two scans read 0, the button goes from pressed to non-pressed
			if(read_val==0 && order[j][i]!=0){
				flag=1;
			}

			// the button is pressed, give it order
			if(read_val!=0){
				pressed[j][i]=1;

				if( order[j][i]==0){
					order[j][i]=press_order;
					press_order++;
				}

			}
		}
	}

	keypad_init2();
	for( int i=0; i<4; i++){
		SET_REG(GPIOC->ODR, 0xF, y_pin[i]);

		for( int j=0; j<4; j++){

			read_val=GPIOB->IDR&x_pin[j];

			// the button goes from pressed to non-pressed
			if(read_val==0 && order[i][j]!=0 && flag){
				order[i][j]=0;
				for( int i=0; i<4; i++){
					for( int j=0; j<4; j++){
						if(order[i][j]==2)
							order[i][j]=1;
					}
				}

				press_order--;
			}


			if(read_val!=0){
				pressed[i][j]=1;

				if( order[i][j]==0){
					order[i][j]=press_order;
					press_order++;
				}
			}
		}
	}


	// check how many buttons are pressed
	int num_press=0;
	for( int i=0; i<4; i++){
		for( int j=0; j<4; j++){
			if(pressed[i][j]==1)
				num_press++;
		}

	}


	// if no button is pressed, initialize the order matrix
	if(num_press==0){
		for( int i=0; i<4; i++){
			for( int j=0; j<4; j++)
				order[i][j]=0;
		}
		press_order=1;
	}




	if( num_press==0)
		return -1;
	else if( num_press==1)
		return 1;
	else if( num_press==2)
		return 2;

}



void display( char key){
	if( key==255){
		// no button is pressed
		for( char i=1; i<=8; i++)
			max7219_send(i, 0xF);

	}
	else if(key==1){
		// only one button is pressed
		char display_num, digit=1;
		for( int i=0; i<4; i++){
			for( int j=0; j<4; j++){
				if(pressed[i][j]==1){
					display_num=table[i][j];
					break;
				}
			}
		}

		if(display_num>9){
			max7219_send(0x1, display_num%10);
			max7219_send(0x2, display_num/10);
			digit=digit+2;
		}
		else{
			max7219_send(0x1, display_num);
			digit++;
		}
		for( char i=digit; i<=8; i++)
			max7219_send(i, 0xF);
	}
	else{
		// two buttons are pressed
		char digit=1, display_num1, display_num2, sum;

		for( int i=0; i<4; i++){
			for( int j=0; j<4; j++){
				if(order[i][j]==1)
					display_num1=table[i][j];
				else if(order[i][j]==2)
					display_num2=table[i][j];
			}
		}

		sum=display_num1+display_num2;
		if(sum>9){
			max7219_send(0x1, sum%10);
			max7219_send(0x2, sum/10);
			digit=3;
		}
		else{
			max7219_send(0x1, sum);
			digit=2;

		}

		//space
		max7219_send(digit, 0xF);
		digit++;

		//num2
		if(display_num2>9){
			max7219_send(digit, display_num2%10);
			max7219_send(digit+1, display_num2/10);
			digit=digit+2;
		}
		else{
			max7219_send(digit, display_num2);
			digit++;
		}

		//space
		max7219_send(digit, 0xF);
		digit++;

		//num1
		if(display_num1>9){
			max7219_send(digit, display_num1%10);
			max7219_send(digit+1, display_num1/10);
			digit=digit+2;
		}
		else{
			max7219_send(digit, display_num1);
			digit++;
		}

		while(digit<=8){
			max7219_send(digit, 0xF);
			digit++;
		}
	}
}



int main(){

	GPIO_init();
	max7219_init();
	keypad_init();

	for( int i=0; i<4; i++){
		for( int j=0; j<4; j++)
			order[i][j]=0;
	}

	while(1){
   		char key=keypad_scan();
		display(key);
		//for( int i=0; i<5000; i++);
	}

	return 0;
}
