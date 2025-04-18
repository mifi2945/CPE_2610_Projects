/**
  ******************************************************************************
  * @file		main.c
  * @brief		Problems
  *
  * Course:		CPE 2610
  * Section:	131
  * Assignment:	Homework 2
  * Name:		Mikhail Filippov
  ******************************************************************************
*/



#include <stdio.h>
#include <stdint.h>
#include "uart_driver.h"

#define F_CPU 16000000UL

#define GPIOB			0x40020400
#define GPIOC			0x40020800
#define RCC_ENR			0x40023830

#define MODER_INDEX		0
#define TYPER_INDEX		1
#define SPEED_INDEX		2
#define PUPDR_INDEX		3
#define IDR_INDEX		4
#define ODR_INDEX		5
#define BSRR_INDEX		6
#define LCKR_INDEX		7
#define AFRL_INDEX		8
#define AFRH_INDEX		9

// main
int main(void){
	init_usart2(57600,F_CPU);
	printf("Problem 1:\n");
	printf("~(1<<5): %x\n",(~(1<<5)));
	printf("~1<<5: %x\n",(~1<<5));
	printf("0x12349ABC & 0x77777777: %x\n",(0x12349ABC & 0x77777777));
	printf("0x12349ABC | 0x77777777: %x\n",(0x12349ABC | 0x77777777));
	printf("0x12349ABC ^ 0x77777777: %x\n",(0x12349ABC ^ 0x77777777));

	printf("Problem 2:\n");
	volatile uint32_t *rcc_enr = (uint32_t*) RCC_ENR;
	volatile uint32_t *gpiob = (uint32_t*) GPIOB;
	volatile uint32_t *gpioc = (uint32_t*) GPIOC;

	*rcc_enr |= (0b11<<1); // enable GPIOB and GPIOC
	// port C is already reset to read mode on all pins, so no action needs to be taken
	for(int i = 0; i < 14; i+=4) {
		gpioc[PUPDR_INDEX] |= (0b01<<i); // pull up
	}
	gpioc[PUPDR_INDEX] |= (0b10<<2) | (0b10<<6); // pull down

	printf("GPIOB: %x\n", (unsigned int) gpiob[IDR_INDEX]);
	printf("GPIOC: %x\n", (unsigned int) gpioc[IDR_INDEX]);

	// never return
	for(;;){}

	return 0;
}

