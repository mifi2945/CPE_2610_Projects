/**
  ******************************************************************************
  * @file		main.c
  * @brief		Print HEX to LCD
  *
  * Course:		CPE 2610
  * Section:	131
  * Assignment:	Homework Week 5
  * Name:		Mikhail Filippov
  ******************************************************************************
*/



#include <stdio.h>
#include "uart_driver.h"
#include "lcd.h"
#include "timer.h"

#define F_CPU 16000000UL

// main
int main(void){
	init_usart2(57600,F_CPU);
	lcd_init();

	lcd_print_hex(0, 6, 256);

	printf("hello?");
	// never return
	for(;;){
		lcd_print_char('M');
		delay_ms(1000);
		//lcd_clear();
		//delay_ms(1000);
	}

	return 0;
}

