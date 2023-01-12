/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

int mute=0;

// star
int song1[48]={
		12,12,19,19,21,21,19,19,
		17,17,16,16,14,14,12,12,
		19,19,17,17,16,16,14,14,
		19,19,17,17,16,16,14,14,
		12,12,19,19,21,21,19,19,
		17,17,16,16,14,14,12,12};
int stop1[48]={
		1,1,1,1,1,1,0,1,
		1,1,1,1,1,1,0,1,
		1,1,1,1,1,1,0,1,
		1,1,1,1,1,1,0,1,
		1,1,1,1,1,1,0,1,
		1,1,1,1,1,1,0,1};
int len1=48;
int delay11=9000000;
int delay21=400000;

// greensleeves
int song2[198]={
		// 1-7
		36,36,36,36,19,19,
		22,22,22,22,24,24,
		26,26,26,27,26,26,
		24,24,24,24,21,21,
		17,17,17,19,21,21,
		22,22,22,22,19,19,
		19,19,19,18,19,19,
		//8-16
		21,21,21,21,18,18,
		14,14,14,14,19,19,
		22,22,22,22,24,24,
		26,26,26,27,26,26,
		24,24,24,24,21,21,
		17,17,17,19,21,21,
		22,22,22,21,19,19,
		18,18,18,16,18,18,
		19,19,19,19,19,19,
		//17-25
		19,19,19,19,19,19,
		29,29,29,29,29,29,
		29,29,29,28,26,26,
		24,24,24,24,21,21,
		17,17,17,19,21,21,
		22,22,22,22,19,19,
		19,19,19,18,19,19,
		21,21,21,21,18,18,
		14,14,14,14,14,14,
		//26-33
		29,29,29,29,29,29,
		29,29,29,28,26,26,
		24,24,24,24,21,21,
		17,17,17,19,21,21,
		22,22,22,21,19,19,
		18,18,18,16,18,18,
		19,19,19,19,19,19,
		19,19,19,19,19,19
};
int stop2[198]={
		// 1-7
		0,0,0,0,0,1,
		0,0,0,1,0,1,
		0,0,1,1,0,1,
		0,0,0,1,0,1,
		0,0,1,1,0,1,
		0,0,0,1,0,1,
		0,0,1,1,0,1,
		//8-16
		0,0,0,1,0,1,
		0,0,0,1,0,1,
		0,0,0,1,0,1,
		0,0,1,1,0,1,
		0,0,0,1,0,1,
		0,0,1,1,0,1,
		0,0,1,1,0,1,
		0,0,1,1,0,1,
		0,0,0,0,0,1,
		//17-25
		0,0,0,0,0,1,
		0,0,0,0,0,1,
		0,0,1,1,0,1,
		0,0,0,1,0,1,
		0,0,1,1,0,1,
		0,0,0,1,0,1,
		0,0,1,1,0,1,
		0,0,0,1,0,1,
		0,0,0,0,0,1,
		//26-33
		0,0,0,0,0,1,
		0,0,1,1,0,1,
		0,0,0,1,0,1,
		0,0,1,1,0,1,
		0,0,1,1,0,1,
		0,0,1,1,0,1,
		0,0,0,0,0,1,
		0,0,0,0,0,1
};
int len2=198;
int delay12=2000000;
int delay22=200000;

// totoro
int song3[304]={
	19,19,24,24,23,23,24,19,
	19,19,19,19,19,19,19,19,
	36,36,24,24,23,23,24,28,
	28,28,28,28,28,28,28,28,
	29,29,28,28,26,26,24,29,
	29,29,28,28,26,26,24,24,
	24,24,24,26,26,26,26,26,
	21,21,21,23,23,23,23,23,
	36,36,24,24,23,23,24,19,
	19,19,19,19,19,19,19,19,
	36,36,24,24,23,23,24,31,
	31,31,31,31,31,31,31,31,
	29,29,29,29,29,28,26,29,
	29,29,29,29,36,26,28,29,
	28,28,28,28,28,26,24,28,
	28,28,28,28,28,28,28,28,
	21,21,23,23,24,24,26,21,
	21,21,23,23,24,26,24,31,
	31,31,31,31,31,31,31,31,
	36,36,36,36,24,26,28,29,	//
	31,31,28,24,36,31,31,31,
	29,29,26,26,26,26,26,26,
	29,29,26,23,36,29,29,29,
	28,24,24,24,24,24,24,24,
	36,36,20,20,24,24,29,29,
	28,28,31,24,24,24,36,28,
	29,28,29,28,29,28,24,26,
	26,26,26,26,24,26,28,29,
	31,31,28,24,36,31,31,31,
	29,29,26,26,26,26,26,26,
	29,29,26,23,36,29,29,29,
	28,28,24,24,24,24,24,24,
	21,21,33,33,31,29,28,29,
	31,31,31,24,24,24,24,28,
	29,28,24,29,28,24,33,31,
	31,31,31,31,31,31,31,31,
	36,36,19,19,29,28,26,28,
	24,24,24,24,24,24,24,24
};
int stop3[304]={
	0,1,0,1,0,1,1,0,
	0,0,0,0,0,0,0,1,
	0,0,0,1,0,1,1,0,
	0,0,0,0,0,0,0,1,
	0,1,0,1,0,1,1,0,
	0,1,0,1,0,1,0,1,
	0,0,1,1,0,0,0,1,
	0,0,1,1,0,0,0,1,
	0,0,0,1,0,1,1,0,
	0,0,0,0,0,0,0,1,
	0,0,0,1,0,1,1,0,
	0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,0,
	0,0,0,0,0,1,1,1,
	0,1,0,1,1,1,1,0,
	0,0,0,0,0,0,0,1,
	0,1,0,1,0,1,1,0,
	1,1,0,1,1,1,1,0,
	0,0,0,0,0,0,0,1,
	0,0,0,0,1,1,1,1,	//
	0,1,1,1,0,0,0,1,
	0,1,0,0,0,0,0,1,
	0,1,1,1,0,0,0,1,
	0,1,0,0,0,0,0,1,
	0,0,0,1,0,1,0,1,
	0,1,1,0,0,1,0,1,
	1,1,1,1,1,1,1,0,
	0,0,0,1,1,1,1,1,
	0,1,1,1,0,0,0,1,
	0,1,0,0,0,0,0,1,
	0,1,1,1,0,0,0,1,
	0,1,0,0,0,0,0,1,
	0,1,0,1,1,1,1,1,
	0,0,1,1,0,0,1,1,
	1,1,1,1,1,1,1,0,
	0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,1
};
int len3=304;
int delay13=2000000;
int delay23=300000;


// the harmonious blacksmith
int song4[312]={
		//1-13
		36,36,36,36,36,36,20,21,23,16,18,20,15,16,18,11,23,21,20,21,23,16,18,20,
		15,16,18,11,23,21,20,22,23,25,27,28,18,20,22,23,25,27,25,27,23,18,23,22,
		23,18,15,11,23,21,20,21,23,16,18,20,15,16,18,11,23,21,20,21,23,16,18,20,
		15,16,18,11,23,21,20,22,23,25,27,28,18,20,22,23,25,27,25,27,23,18,23,22,
		23,18,15,11,23,21,20,21,23,16,28,27,25,27,28,21,23,25,20,21,23,16,28,27,
		25,27,28,21,23,25,23,25,27,28,30,32,21,23,25,23,25,21,20,21,20,18,20,16,
		15,18,16,15,16,18,11,13,15,16,18,20,13,15,16,18,20,21,15,16,18,20,21,23,
		16,18,20,21,23,25,27,28,30,21,20,18,28,27,25,23,21,20,18,20,16,11,16,15,
		16,11,8,4,23,21,20,21,23,16,28,27,25,27,28,21,23,25,20,21,23,16,28,27,
		25,27,28,21,23,25,23,25,27,28,30,32,21,23,25,23,25,21,20,21,20,18,20,16,
		15,18,16,15,16,18,11,13,15,16,18,20,13,15,16,18,20,21,15,16,18,20,21,23,
		16,18,20,21,23,25,27,28,30,21,20,18,28,27,25,23,21,20,18,20,16,11,16,15,
		16,11,8,4,4,4,4,4,4,4,4,4,36,36,36,36,36,36,36,36,36,36,36,36
};
int stop4[312]={
		//1-13
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1
};
int len4=312;
int delay14=1500000;
int delay24=180000;


// the show
int song5[312]={
		//1-10
		28,28,28,26,28,26,28,28,
		28,28,28,26,28,31,31,26,
		26,26,26,24,26,26,36,36,
		26,26,26,26,28,29,29,28,
		28,28,28,28,28,26,24,28,
		28,28,28,28,28,26,28,29,
		29,28,28,21,21,21,36,29,
		29,28,28,26,26,24,26,24,
		24,24,24,24,24,24,24,24,
		36,36,36,36,28,28,29,26,
		//11-20
		26,26,36,36,26,26,28,24,
		24,24,36,24,24,24,24,24,
		33,33,31,31,29,29,31,28,
		28,28,36,27,28,28,29,29,
		26,26,36,24,26,26,28,24,
		24,24,24,24,24,24,36,21,
		24,24,26,26,28,29,29,31,
		31,31,36,36,31,31,28,31,
		31,31,36,31,31,31,33,28,
		28,28,36,36,36,26,28,28,
		//21-30
		29,29,28,28,26,24,26,26,
		26,26,26,26,26,26,26,36,
		28,28,28,26,28,26,28,28,
		28,28,28,26,28,31,31,26,
		26,26,26,24,26,26,36,26,
		26,26,26,26,28,29,29,28,
		28,28,28,28,28,26,24,28,
		28,28,28,28,28,26,28,29,
		29,28,28,21,21,21,36,29,
		29,28,28,26,26,24,26,28,
		//31-39
		28,28,28,26,28,26,28,28,
		28,28,28,26,28,31,31,26,
		26,26,26,24,26,26,36,26,
		26,26,26,26,28,29,29,28,
		28,28,28,28,28,26,24,28,
		28,28,28,28,28,26,28,29,
		29,28,28,21,21,21,36,29,
		29,29,28,28,26,24,26,24,
		24,24,24,24,24,24,24,36
};
int stop5[312]={
		//1-10
		0,1,1,1,1,1,0,1,
		0,1,1,1,1,0,1,0,
		0,1,1,1,0,1,0,0,
		0,1,1,1,1,0,1,0,
		0,1,0,1,1,1,1,0,
		0,1,0,1,1,1,1,0,
		1,0,1,0,0,1,0,0,
		1,0,1,0,1,1,1,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,1,1,0,
		//11-20
		0,1,0,0,0,1,1,0,
		0,1,0,1,0,1,0,1,
		0,1,0,1,1,1,1,0,
		0,1,0,1,0,1,0,1,
		0,1,0,1,0,1,1,0,
		0,0,0,0,0,1,0,1,
		0,1,0,1,1,0,1,0,
		0,1,0,0,0,1,1,0,
		0,1,0,1,0,1,1,0,
		0,1,0,0,0,1,1,1,
		//21-30
		0,1,0,1,1,1,1,0,
		0,0,0,0,0,0,0,0,//
		0,1,1,1,1,1,0,1,
		0,1,1,1,1,0,1,0,
		0,1,1,1,0,1,0,1,
		0,1,1,1,1,0,1,0,
		0,1,0,1,1,1,1,0,
		0,1,0,1,1,1,1,0,
		1,0,1,0,0,1,0,0,
		1,0,1,0,1,1,1,1,
		//31-39
		0,1,1,1,1,1,0,1,
		0,1,1,1,1,0,1,0,
		0,1,1,1,0,1,0,0,
		1,1,1,0,1,0,1,0,
		0,1,0,1,1,1,1,0,
		0,1,1,1,1,1,1,0,
		1,0,1,0,0,1,0,1,
		0,1,0,1,1,1,1,0,
		0,0,0,0,0,0,0,0
};
int len5=312;
int delay15=2000000;
int delay25=200000;

// canon
int song6_1[464]={
		//1-5
		28,28,28,28,26,26,26,26,24,24,24,24,23,23,23,23,
		21,21,21,21,19,19,19,19,21,21,21,21,23,23,23,23,
		24,24,24,24,23,23,23,23,21,21,21,21,19,19,19,19,
		17,17,17,17,16,16,16,16,17,17,17,17,14,14,14,14,
		12,12,16,16,19,19,17,17,16,16,12,12,16,16,14,14,
		//6-10
		12,12,21,21,12,12,19,19,17,17,21,21,19,19,17,17,
		16,16,12,12,14,14,23,23,24,24,28,28,31,31,19,19,
		21,21,17,17,19,19,16,16,12,12,24,24,24,24,24,23,
		24,23,24,12,11,19,14,16,12,24,23,21,23,28,31,33,
		29,28,26,29,28,26,24,23,21,19,17,16,14,17,16,14,
		//11-15
		12,14,16,17,19,14,19,17,16,21,19,17,19,17,16,14,
		12,21,21,23,24,23,21,19,17,16,14,21,19,21,19,17,
		16,16,28,28,26,26,26,26,36,36,24,24,28,28,28,28,
		33,33,33,33,31,31,31,31,33,33,33,33,35,35,35,35,
		37,37,24,24,23,23,23,23,36,36,21,21,24,24,24,24,
		//16-20
		24,24,24,24,24,24,24,24,24,24,29,29,26,26,31,31,
		28,28,28,28,28,29,28,26,24,24,24,24,24,26,24,23,
		21,21,21,21,24,24,24,24,24,22,21,22,19,19,19,19,
		19,19,19,31,31,33,31,29,28,28,28,28,28,29,28,26,
		24,22,21,22,19,19,19,19,17,17,24,24,24,24,24,23,
		//21-25
		24,24,24,24,24,24,23,23,23,23,21,21,21,21,19,19,
		19,19,17,17,17,17,16,16,16,16,16,14,14,14,14,14,
		16,16,28,28,28,28,26,26,24,24,37,37,37,37,22,22,
		33,33,33,33,37,37,31,31,33,33,33,33,31,31,31,31,
		31,31,31,31,19,19,19,17,16,16,16,16,28,28,28,26,
		//26-29
		24,24,24,24,24,24,24,24,24,24,24,24,24,24,23,23,
		28,28,16,16,14,14,26,26,24,24,12,12,11,11,23,23,
		24,24,33,33,31,31,19,19,17,17,17,26,19,19,26,26,
		28,28,28,28,28,28,28,28,36,36,36,36,36,36,36,36
};
int stop6_1[464]={
		//1-5
		0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
		0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
		0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
		0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
		0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
		//6-10
		0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
		0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
		0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		//11-15
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
		0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
		0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
		//16-20
		0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,
		0,0,1,1,0,1,0,1,0,0,1,1,0,1,0,1,
		0,0,0,1,0,0,0,1,0,1,0,1,0,0,1,1,
		0,0,1,1,0,1,0,1,0,0,1,1,0,1,0,1,
		0,1,0,1,0,0,1,1,0,1,0,1,0,0,1,1,
		//21-25
		0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,
		0,1,0,0,0,1,0,0,0,0,1,1,0,0,0,1,
		0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,
		0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,
		0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
		//26-29
		0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,
		0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
		0,1,0,1,0,1,0,1,0,0,1,1,0,1,0,1,
		0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0


};

int song6_2[464]={
		//1-5
		36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,
		36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,
		28,28,28,28,26,26,26,26,24,24,24,24,23,23,23,23,
		21,21,21,21,19,19,19,19,21,21,21,21,23,23,23,23,
		24,24,24,24,23,23,23,23,21,21,21,21,19,19,19,19,
		//6-10
		17,17,17,17,16,16,16,16,17,17,17,17,14,14,14,14,
		12,12,16,16,19,19,17,17,16,16,12,12,16,16,14,14,
		12,12,9,9,12,12,19,19,17,17,21,21,19,19,17,17,
		16,16,12,12,14,14,23,23,24,24,28,28,31,31,19,19,
		21,21,17,17,19,19,16,16,12,12,24,24,24,24,24,23,
		//11-15
		24,23,24,12,11,19,14,16,12,24,23,21,23,28,31,33,
		29,28,26,29,28,26,24,23,21,19,17,16,14,17,16,14,
		12,14,16,17,19,14,19,17,16,21,19,17,19,17,16,14,
		12,9,21,23,24,23,21,19,17,16,14,21,19,21,19,17,
		16,16,28,28,26,26,26,26,36,36,24,24,28,28,28,28,
		//16-20
		33,33,33,33,31,31,31,31,33,33,33,33,35,35,35,35,
		24,24,24,24,23,23,23,23,21,21,21,21,19,19,19,19,
		12,12,12,14,16,16,16,16,21,21,21,21,14,14,14,14,
		16,16,16,28,28,29,28,26,24,24,24,24,24,26,24,23,
		21,21,21,21,24,24,24,24,24,22,21,22,19,19,19,19,
		//21-25
		19,19,19,31,31,33,31,29,28,28,28,28,28,29,28,26,
		24,22,21,22,19,19,19,19,17,17,24,24,23,23,23,23,
		24,24,24,24,24,24,23,23,23,23,21,21,21,21,19,19,
		19,19,17,17,17,17,16,16,16,16,16,14,14,14,14,14,
		16,16,28,28,28,28,26,26,24,24,37,37,37,37,34,34,
		//26-29
		33,33,33,33,37,37,31,31,33,33,33,33,31,31,31,31,
		24,24,12,12,11,11,23,23,21,21,9,9,7,7,19,19,
		17,17,29,29,28,28,16,16,14,14,21,21,14,14,23,23,
		24,24,24,24,24,24,24,24,36,36,36,36,36,36,36,36,


};
int stop6_2[464]={
		//1-5
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
		0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
		0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
		//6-10
		0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
		0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
		0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
		0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
		0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
		//11-15
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
		//16-20
		0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
		0,0,1,1,0,0,0,1,0,0,0,1,0,0,0,1,
		0,0,1,1,0,0,0,1,0,0,0,1,0,0,1,1,
		0,0,1,1,0,1,0,1,0,0,1,1,0,1,0,1,
		0,0,0,1,0,0,0,1,0,1,0,1,0,0,1,1,
		//21-25
		0,0,1,1,0,1,0,1,0,0,1,1,0,1,0,1,
		0,1,0,1,0,0,1,1,0,1,0,1,0,0,1,1,
		0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,
		0,1,0,0,0,1,0,0,0,0,1,1,0,0,0,1,
		0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,
		//26-29
		0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,
		0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
		0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
		0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0
};


int len6=464;
int delay16=3000000;
int delay26=180000;




int* song_1=song1;
int* song_2=song1;
int* stop_1=stop1;
int* stop_2=stop1;
int len=48;
int start_i=0;
int delay1=9000000;
int delay2=400000;
int reset_delay1=9000000;
int reset_delay2=400000;
uint8_t aRxBuffer[2];
int i=0;


uint16_t sine_wave_array1[128]={
		3071, 3116, 3152, 3177, 3193, 3199, 3195, 3182, 3161, 3132,
		3095, 3052, 3003, 2948, 2890, 2827, 2763, 2696, 2629, 2562,
		2496, 2432, 2371, 2313, 2259, 2210, 2167, 2130, 2099, 2075,
		2058, 2049, 2047, 2053, 2066, 2086, 2114, 2148, 2188, 2234,
		2285, 2341, 2401, 2464, 2529, 2596, 2663, 2730, 2795, 2859,
		2919, 2976, 3028, 3074, 3114, 3147, 3173, 3190, 3198, 3197,
		3186, 3166, 3135, 3095, 3044, 2984, 2913, 2834, 2745, 2648,
		2543, 2430, 2312, 2187, 2058, 1925, 1789, 1651, 1513, 1375,
		1238, 1103, 973, 846, 725, 611, 505, 406, 317, 238,
		169, 111, 65, 31, 9, 0, 3, 19, 47, 87,
		139, 202, 276, 360, 454, 557, 667, 785, 909, 1037,
		1170, 1306, 1444, 1582, 1720, 1857, 1992, 2123, 2250, 2372,
		2487, 2596, 2697, 2790, 2875, 2950, 3015, 3071};

// piano
uint16_t sine_wave_array2[128]={
		2047, 2254, 2456, 2647, 2822, 2978, 3111, 3219, 3301, 3356,
		3385, 3391, 3376, 3342, 3295, 3239, 3177, 3113, 3052, 2997,
		2951, 2915, 2890, 2877, 2875, 2883, 2900, 2923, 2950, 2978,
		3005, 3029, 3047, 3058, 3061, 3055, 3040, 3018, 2988, 2953,
		2913, 2871, 2828, 2786, 2746, 2709, 2676, 2647, 2622, 2601,
		2582, 2564, 2546, 2527, 2505, 2479, 2448, 2412, 2369, 2320,
		2266, 2207, 2145, 2080, 2014, 1949, 1887, 1828, 1774, 1725,
		1682, 1646, 1615, 1589, 1567, 1548, 1530, 1512, 1493, 1472,
		1447, 1418, 1385, 1348, 1308, 1266, 1223, 1181, 1141, 1106,
		1076, 1054, 1039, 1033, 1036, 1047, 1065, 1089, 1116, 1144,
		1171, 1194, 1211, 1219, 1217, 1204, 1179, 1143, 1097, 1042,
		981, 917, 855, 799, 752, 718, 703, 709, 738, 793,
		875, 983, 1116, 1272, 1447, 1638, 1840, 2047};

// triangle
uint16_t sine_wave_array3[128]={
	0, 64, 128, 193, 257, 322, 386, 451, 515, 580,
	644, 709, 773, 838, 902, 967, 1031, 1096, 1160, 1225,
	1289, 1354, 1418, 1483, 1547, 1612, 1676, 1741, 1805, 1870,
	1934, 1999, 2063, 2128, 2192, 2257, 2321, 2386, 2450, 2515,
	2579, 2644, 2708, 2772, 2837, 2901, 2966, 3030, 3095, 3159,
	3224, 3288, 3353, 3417, 3482, 3546, 3611, 3675, 3740, 3804,
	3869, 3933, 3998, 4062, 4062, 3998, 3933, 3869, 3804, 3740,
	3675, 3611, 3546, 3482, 3417, 3353, 3288, 3224, 3159, 3095,
	3030, 2966, 2901, 2837, 2772, 2708, 2644, 2579, 2515, 2450,
	2386, 2321, 2257, 2192, 2128, 2063, 1999, 1934, 1870, 1805,
	1741, 1676, 1612, 1547, 1483, 1418, 1354, 1289, 1225, 1160,
	1096, 1031, 967, 902, 838, 773, 709, 644, 580, 515,
	451, 386, 322, 257, 193, 128, 64, 0};
uint16_t sine_wave_array4[128]={
		3337, 3710, 521, 3741, 2590, 400, 1141, 2240, 3921, 3952,
		646, 3975, 3920, 1988, 3278, 582, 1728, 3750, 3245, 3930,
		2686, 147, 3478, 3825, 2780, 3103, 3044, 1607, 2685, 702,
		2892, 131, 1134, 190, 398, 3373, 2846, 1299, 3892, 142,
		1797, 1563, 3135, 3257, 766, 2006, 1825, 2647, 2905, 3091,
		1131, 2784, 2683, 666, 488, 2041, 3931, 1394, 2397, 917,
		3077, 1045, 2072, 2863, 3649, 3929, 2241, 568, 612, 1055,
		3443, 1042, 3335, 998, 3806, 1434, 806, 1029, 2523, 1939,
		1441, 3403, 2397, 2252, 3756, 1171, 3101, 3087, 1558, 2326,
		311, 221, 2174, 3191, 3825, 532, 2330, 1923, 49, 1381,
		665, 3253, 1275, 2165, 679, 2466, 1077, 2679, 2823, 3064,
		1845, 344, 938, 3741, 624, 3382, 2205, 4080, 321, 1813,
		437, 3939, 19, 3174, 3347, 3558, 346, 1638};

uint16_t* sine_wave_array=sine_wave_array1;

const int pitch[39]={
		9555, 9018, 8512, 8034, 7583, 7158, 6756, 6377, 6018, 5681, 5362, 5061,
		4777, 4509, 4256, 4017, 3791, 3578, 3377, 3188, 3009, 2840, 2680, 2530,
		2388, 2254, 2127, 2008, 1895, 1789, 1688, 1593, 1504, 1419, 1340, 1264,
		0, 1193

};

/*const int pitch[37]={
		4777, 4509, 4256, 4017, 3791, 3578, 3377, 3188, 3009, 2840, 2680, 2530,
		2388, 2254, 2127, 2008, 1895, 1789, 1688, 1593, 1504, 1419, 1340, 1264,
		1193, 563, 531, 501, 473, 446, 421, 398, 375, 354, 334, 315, 0
};*/

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
DAC_HandleTypeDef hdac1;
DMA_HandleTypeDef hdma_dac_ch1;
DMA_HandleTypeDef hdma_dac_ch2;

TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim7;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_DAC1_Init(void);
static void MX_TIM6_Init( int p);
static void MX_USART2_UART_Init(void);
static void MX_TIM7_Init( int p);
static void MX_TIM4_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	HAL_UART_Transmit(&huart1, (uint8_t *)aRxBuffer, 1,0xFFFF);
	if( aRxBuffer[0]=='s'){
		if(mute){
			mute=0;
			HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
			HAL_TIM_Base_Start(&htim4);
		}
		else{
			mute=1;
			HAL_TIM_PWM_Stop(&htim4,TIM_CHANNEL_1);
			HAL_TIM_Base_Stop(&htim4);
		}

	}
	else if(aRxBuffer[0]=='1'){
		song_1=song1;
		stop_1=stop1;
		song_2=song1;
		stop_2=stop1;
		len=len1;
		mute=0;
		delay1=delay11;
		delay2=delay21;
		reset_delay1=delay11;
		reset_delay2=delay21;
		start_i=0;
		i=0;

		mute=0;
		HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
		HAL_TIM_Base_Start(&htim4);
	}
	else if(aRxBuffer[0]=='2'){
		song_1=song2;
		stop_1=stop2;
		song_2=song2;
		stop_2=stop2;
		len=len2;
		mute=0;
		delay1=delay12;
		delay2=delay22;
		reset_delay1=delay12;
		reset_delay2=delay22;
		start_i=0;
		i=0;

		mute=0;
		HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
		HAL_TIM_Base_Start(&htim4);
	}
	else if(aRxBuffer[0]=='3'){
		song_1=song3;
		stop_1=stop3;
		song_2=song3;
		stop_2=stop3;
		len=len3;
		mute=0;
		delay1=delay13;
		delay2=delay23;
		reset_delay1=delay13;
		reset_delay2=delay23;
		start_i=0;
		i=0;

		mute=0;
		HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
		HAL_TIM_Base_Start(&htim4);
	}
	else if(aRxBuffer[0]=='4'){
		song_1=song4;
		stop_1=stop4;
		song_2=song4;
		stop_2=stop4;
		len=len4;
		mute=0;
		delay1=delay14;
		delay2=delay24;
		reset_delay1=delay14;
		reset_delay2=delay24;
		start_i=0;
		i=0;

		mute=0;
		HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
		HAL_TIM_Base_Start(&htim4);
	}
	else if(aRxBuffer[0]=='5'){
		song_1=song5;
		stop_1=stop5;
		song_2=song5;
		stop_2=stop5;
		len=len5;
		mute=0;
		delay1=delay15;
		delay2=delay25;
		start_i=0;
		i=0;
		reset_delay1=delay15;
		reset_delay2=delay25;

		mute=0;
		HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
		HAL_TIM_Base_Start(&htim4);
	}
	else if(aRxBuffer[0]=='6'){
		song_1=song6_1;
		stop_1=stop6_1;
		song_2=song6_2;
		stop_2=stop6_2;
		len=len6;
		mute=0;
		delay1=delay16;
		delay2=delay26;
		reset_delay1=delay16;
		reset_delay2=delay26;

		start_i=0;
		i=0;

		mute=0;
		HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
		HAL_TIM_Base_Start(&htim4);
	}

	else if(aRxBuffer[0]=='i'){
		delay1*=0.9;
		delay2*=0.9;
	}
	else if(aRxBuffer[0]=='d'){

		delay1*=1.1;
		delay2*=1.15;
	}
	else if(aRxBuffer[0]=='r'){

		delay1=reset_delay1;
		delay2=reset_delay2;
	}
	else if(aRxBuffer[0]=='o'){
		sine_wave_array=sine_wave_array1;
	}
	else if(aRxBuffer[0]=='p'){
		sine_wave_array=sine_wave_array2;
	}
	else if(aRxBuffer[0]=='t'){
		sine_wave_array=sine_wave_array3;
	}
	else if(aRxBuffer[0]=='q'){
		sine_wave_array=sine_wave_array4;
	}






	HAL_UART_Receive_IT(&huart1, (uint8_t *)aRxBuffer, 1);
}

int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_DAC1_Init();
  MX_TIM6_Init(pitch[0]);
  MX_USART2_UART_Init();
  MX_TIM7_Init(pitch[0]);
  MX_TIM4_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  HAL_TIM_Base_Stop(&htim6);
  HAL_TIM_Base_Stop(&htim7);
  HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
  HAL_TIM_Base_Start(&htim4);

  while (1)
  {
      /* USER CODE END WHILE */

      for(i=start_i; i<len; i++){

          start_i=0;
          if(!mute){
              MX_TIM6_Init(pitch[song_1[i]]);
              HAL_TIM_Base_Start(&htim6);
              HAL_DAC_Start(&hdac1,DAC_CHANNEL_1);
              HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_1, (uint32_t*)sine_wave_array, 128, DAC_ALIGN_12B_R);

              MX_TIM7_Init(pitch[song_2[i]]);
              HAL_TIM_Base_Start(&htim7);
              HAL_DAC_Start(&hdac1,DAC_CHANNEL_2);
              HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_2, (uint32_t*)sine_wave_array, 128, DAC_ALIGN_12B_R);

              for( int j=0; j<delay1; j++);

              if(stop_1[i]==1){
                  HAL_TIM_Base_Stop(&htim6);
              }
              if(stop_2[i]==1){
				  HAL_TIM_Base_Stop(&htim7);
              }


              for( int j=0; j<delay2; j++);

          }
          else{
              HAL_TIM_Base_Stop(&htim6);
              HAL_TIM_Base_Stop(&htim7);
              start_i=i;
              break;
          }
      }

  /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief DAC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_DAC1_Init(void)
{

  /* USER CODE BEGIN DAC1_Init 0 */

  /* USER CODE END DAC1_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN DAC1_Init 1 */

  /* USER CODE END DAC1_Init 1 */
  /** DAC Initialization
  */
  hdac1.Instance = DAC1;
  if (HAL_DAC_Init(&hdac1) != HAL_OK)
  {
    Error_Handler();
  }
  /** DAC channel OUT1 config
  */
  sConfig.DAC_SampleAndHold = DAC_SAMPLEANDHOLD_DISABLE;
  sConfig.DAC_Trigger = DAC_TRIGGER_T6_TRGO;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  sConfig.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_DISABLE;
  sConfig.DAC_UserTrimming = DAC_TRIMMING_FACTORY;
  if (HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /** DAC channel OUT2 config
  */
  sConfig.DAC_Trigger = DAC_TRIGGER_T7_TRGO;
  sConfig.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_DISABLE;
  if (HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DAC1_Init 2 */

  /* USER CODE END DAC1_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 799;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 199;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 11;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */
  HAL_TIM_MspPostInit(&htim4);

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(int p)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 0;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = p;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief TIM7 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM7_Init(int p)
{

  /* USER CODE BEGIN TIM7_Init 0 */

  /* USER CODE END TIM7_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM7_Init 1 */

  /* USER CODE END TIM7_Init 1 */
  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 0;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = p;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM7_Init 2 */

  /* USER CODE END TIM7_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */
  HAL_UART_Receive_IT(&huart1, (uint8_t *)aRxBuffer, 1);
  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);
  /* DMA1_Channel4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
