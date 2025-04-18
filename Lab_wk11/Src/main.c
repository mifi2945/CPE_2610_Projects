/**
  ******************************************************************************
  * @file		main.c
  * @brief		Use the 8x8 Matrix with SPI
  *
  * Course:		CPE 2610
  * Section:	131
  * Assignment:	Lab Week 11
  * Name:		Mikhail Filippov
  * Summary:	This lab was one I thought would be easy, but unfortunately it
  * 			was not; there were many troubles getting the signals up and
  * 			running, something which was not working with the clock itself.
  * 			I tried using interrupts at first, but opted for a more primitive
  * 			approach of blocking with while loops. In the end, it worked out
  * 			and I had a cool pattern printing.
  ******************************************************************************
*/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "uart_driver.h"
#include "include.h"

#define F_CPU 16000000UL

static int linear_func(int m, int b, int x) {
	return (x*m + b);
}

static void line_gen(void) {
	// first half
	for (int b = 7; b >= 0; --b) {
		for (int x = 0; x < (8-b); ++x) {
			int y = linear_func(1, b, x);
			matrix_set_pixel(y, x);
			matrix_update();
			delay_ms(75);
		}
	}
	//second half
	for (int b = 1; b < 8; ++b) {
		for (int x = 0; x < (8-b); ++x) {
			int y = linear_func(1, b, x);
			matrix_set_pixel(x, y);
			matrix_update();
			delay_ms(75);
		}
	}
}

static void random_clear(void) {
	int index[64];
	for (int i = 0; i < 64; ++i) {
		index[i] = i;
	}

	for (int i = 63; i > 0; i--) {
		int j = rand() % (i+1);
		int temp = index[i];
		index[i] = index[j];
		index[j] = temp;
	}

	for (int i = 0; i < 64; ++i) {
		int x = index[i] / 8;
		int y = index[i] % 8;
		matrix_clear_pixel(x,y);
		matrix_update();
		delay_ms(40);
	}
}

// main
int main(void){
	init_usart2(57600,F_CPU);
	matrix_init();
	srand(time(NULL));

	// never return
	for(;;){
		line_gen();
		delay_ms(500);
		random_clear();
	}
	return 0;
}

