/**
  ******************************************************************************
  * @file		main.c
  * @brief		Knight Rider Lights
  *
  * Course:		CPE 2610
  * Section:	131
  * Assignment:	Lab 2
  * Name:		Mikhail Filippov
  * Summary:
  * This lab was a little difficult, in the sense that we had to do things that
  * involved both hardware and software with minimal instructions. There were
  * some parts that could have definitely been more clear, but I figured it
  * out in the end. Furthermore, I would say measuring our delay_100ms function
  * was the hardest part, since there were no instructions on how to even start
  * that. Otherwise, it was a fun lab once I figured everything out.
  ******************************************************************************
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uart_driver.h"
#include "leds.h"

#define F_CPU 			16000000UL
#define MAX_LINE_SIZE	256

void delay_100ms(void){
	for(int i = 0; i < 130000; ++i){}
}

void knight_rider_10(void) {
	for(int r = 0; r < 10; ++r){
		for(unsigned int i = 1; i <= 512; i = i<<1) {
			light_LED(i);
			delay_100ms();
		}
		for(unsigned int i = 512; i >= 1; i = i>>1) {
			light_LED(i);
			delay_100ms();
		}
		printf("%d cycles complete\n",r+1);
	}
	light_LED(0);
}

void knight_rider_x(int iters) {
	for(int r = 0; r < iters; ++r){
		for(unsigned int i = 1; i <= 512; i = i<<1) {
			light_LED(i);
			delay_100ms();
		}
		for(unsigned int i = 512; i >= 1; i = i>>1) {
			light_LED(i);
			delay_100ms();
		}
		printf("%d cycles complete\n",r+1);
	}
	light_LED(0);
}

void flash_lights(void) {
	for (int i = 0; i < 3; ++i) {
		light_LED(1023);
		delay_100ms();
		light_LED(0);
		delay_100ms();
	}
}

void quiz(void) {
	unsigned int random_num = (rand() % 1023) + 1;
	light_LED(random_num);
	printf("What number is displayed:\n");
	char answer[MAX_LINE_SIZE];
	fgets(answer, MAX_LINE_SIZE, stdin);
	if (atoi(answer) == random_num) {
		knight_rider_x(1);
	} else {
		flash_lights();
	}
}

// main
int main(void){
	init_usart2(57600,F_CPU);
	light_LED_init();

	light_LED(0);
	char input[MAX_LINE_SIZE];

	// never return
	for(;;){
		/*
		for(;;){
			light_LED(1);
			delay_100ms();
			light_LED(0);
			delay_100ms();
		}
		*/

		fgets(input, MAX_LINE_SIZE, stdin);
		int n;
		if (strcmp(input,"kr\n") == 0) {
			knight_rider_10();
		} else if(sscanf(input, "kr %d", &n)==1) {
			knight_rider_x(n);
		} else if(strcmp(input,"quiz\n")==0) {
			quiz();
		} else if(sscanf(input, "%d", &n)==1) {
			if(n >= 0 && n <= 1023) {
				light_LED(n);
			}
		} else if(sscanf(input, "%x", &n)==1) {
			if(n >= 0 && n <= 1023) {
				light_LED(n);
			}
		}
	}

	return 0;
}

