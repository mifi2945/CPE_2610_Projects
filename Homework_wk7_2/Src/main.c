/**
  ******************************************************************************
  * @file		main.c
  * @brief		Edit LEDs to imlement brightness
  *
  * Course:		CPE 2610
  * Section:	131
  * Assignment:	Homework 7-2
  * Name:		Mikhail Filippov
  * Summary:
  ******************************************************************************
*/



#include <stdio.h>
#include "uart_driver.h"
#include "leds.h"
#include "keypad.h"

#define F_CPU 16000000UL

// main
int main(void){
	init_usart2(57600,F_CPU);
	light_LED_init();
	keypad_init();
	light_LED(1023);

	// never return
	for(;;){
		if (keypad_getchar_noblock() == '1') {
			light_LED_bright(100);
		} else if (keypad_getchar_noblock() == '2') {
			light_LED_bright(50);
		} else if (keypad_getchar_noblock() == '3') {
			light_LED_bright(5);
		} else if (keypad_getchar_noblock() == '4') {
			light_LED_bright(0);
		}
	}
	return 0;
}

