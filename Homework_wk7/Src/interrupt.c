/**
  ******************************************************************************
  * @file		interrupt.c
  * @brief		Interrupt API
  *
  * Course:		CPE 2610
  * Section:	131
  * Name:		Mikhail Filippov
  ******************************************************************************
*/



#include <interrupt.h>
#include <stdint.h>
#include "gpio.h"
#include "leds.h"


volatile uint32_t *syscfg = (uint32_t*) SYSCFG;
volatile uint32_t *exti = (uint32_t*) EXTI;

void handler_init(void) {
	volatile uint32_t *rcc_ahb = (uint32_t*) RCC_AHB1_ENR;
	volatile uint32_t *rcc_apb = (uint32_t*) RCC_APB2_ENR;

	*rcc_ahb |= GPIOBEN | GPIOCEN; // gpio enable
	*rcc_apb |= (1<<14); // APB2ENR

	gpiob[MODER_INDEX] &= ~(0b11<<5*2);
	gpiob[MODER_INDEX] |= (0b01<<5*2);
	// gpioc is reset to 0, already input
	gpioc[MODER_INDEX] &= ~(0b11<<13*2);

	syscfg[5] |= (0b0010<<4); // EXTICR4
	exti[FTSR] |= (1<<13);
	exti[IMR] |= (1<<13);

	volatile uint32_t *nvic = (uint32_t*) NVIC;
	nvic[ISER1] = (1<<8);
}

void EXTI15_10_IRQHandler(void) {
	if(exti[PR] & (1<<13)) {
		exti[PR] = (1<<13); //clear
		//toggle light
		gpiob[ODR_INDEX] ^= (1<<5);
	}
}
