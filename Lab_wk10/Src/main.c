/**
  ******************************************************************************
  * @file		main.c
  * @brief		Interpret IR Remote
  *
  * Course:		CPE 2610
  * Section:	131
  * Assignment:	Lab Week 9
  * Name:		Mikhail Filippov
  * Summary:
  ******************************************************************************
*/



#include <stdio.h>
#include "uart_driver.h"
#include "include.h"

#define F_CPU 16000000UL
#define MAX_SIZE	256

// main
int main(void){
	init_usart2(57600,F_CPU);
	char buffer[256];

	// never return
	for(;;){
		fgets(buffer, MAX_SIZE, stdin);
		printf("%s",buffer);
//		delay_ms(2000);
	}
	return 0;
}

