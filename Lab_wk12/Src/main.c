/**
  ******************************************************************************
  * @file		main.c
  * @brief		Use the accelerometer in tandem with the matrix through SPI
  *
  * Course:		CPE 2610
  * Section:	131
  * Assignment:	Lab Week 12
  * Name:		Mikhail Filippov
  * Summary:	This lab proved to be a cool way to re-factor Lab week 11
  * 			by changing the way we write to SPI (as well as read this time).
  * 			It took a little bit to figure out what does what, as well as
  * 			all of the quirks of the ADXL345 itself, but in the end it was
  * 			fun setting up main itself with how the bubble level would go
  * 			on to work.
  ******************************************************************************
*/



#include <stdio.h>
#include <math.h>
#include "uart_driver.h"
#include "include.h"

#define F_CPU 16000000UL

#define INC		50 // increment 5 times = range of matrix "bubble"
#define G_RANGE	200

static void bubble_level(int x, int y) {
	matrix_clear();
	// int round for more stable "bubble"
	x = (int)floor((-1.0*x + G_RANGE)/INC + 0.5);
	y = (int)floor(((double)y + G_RANGE)/INC + 0.5);

	matrix_set_pixel(x, y);
	matrix_set_pixel(x-1, y);
	matrix_set_pixel(x-1, y-1);
	matrix_set_pixel(x, y-1);
	matrix_update();
}

static void lcd_g(int x, int y, int z) {
	lcd_set_position(0,3);
	lcd_print_string("    ");
	lcd_set_position(0,3);
	lcd_print_num(x);

	lcd_set_position(0,10);
	lcd_print_string("    ");
	lcd_set_position(0,10);
	lcd_print_num(y);

	lcd_set_position(1,3);
	lcd_print_string("    ");
	lcd_set_position(1,3);
	lcd_print_num(z);
}

// main
int main(void){
	init_usart2(57600,F_CPU);
	matrix_init();
	accelerometer_init();

	lcd_init();
	lcd_print_string("X: 0   Y: 0");
	lcd_set_position(1, 0);
	lcd_print_string("Z: 0");

	int x, y, z;
	// never return
	for(;;){
		get_xyz(&x, &y, &z);
		lcd_g(x, y, z);
		bubble_level(x,y);

		// so we don't fry anything... I don't know :)
		delay_ms(250);
	}
	return 0;
}

