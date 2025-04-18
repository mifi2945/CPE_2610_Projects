/**
  ******************************************************************************
  * @file		main.c
  * @brief		EXTI interrupt setup for LED toggle
  *
  * Course:		CPE 2610
  * Section:	131
  * Assignment:	Homework Week 7-1
  * Name:		Mikhail Filippov
  ******************************************************************************
*/


#include <stdio.h>
#include "uart_driver.h"
#include "interrupt.h"

#define F_CPU 16000000UL


// main
int main(void){
	init_usart2(57600,F_CPU);
	handler_init();

	// never return
	for(;;){}

	return 0;
}

