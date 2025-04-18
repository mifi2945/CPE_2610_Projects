/**
  ******************************************************************************
  * @file		leds.c
  * @brief		Led + GPIO control structure
  *
  * Course:		CPE 2610
  * Section:	131
  * Name:		Mikhail Filippov
  ******************************************************************************
*/


#include <stdint.h>
#include "leds.h"
#include "gpio.h"
#include "interrupt.h"
#include "timer.h"


unsigned int led_number = 0;
unsigned int led_duty = 0;

void tim_init(void) {
	volatile uint32_t *rcc_apb1enr = (uint32_t*) RCC_APB1_ENR;
	*rcc_apb1enr |= TIM3_EN;

	// Use TIM3_CH4 on PB1, Alternate Mode 2
	gpiob[MODER_INDEX] &= ~(0b11<<1*2); //clear
	gpiob[MODER_INDEX] |= (0b10<<1*2); //PB1 alternate function mode
	gpiob[AFRL_INDEX] &= ~(0b1111<<1*4);
	gpiob[AFRL_INDEX] |= (0b0010<<1*4); // AF2


	tim3[CCR4] = 0; //turn off
	tim3[ARR] = (F_CPU / 1000) - 1; // 1KHz period ok for lights
	tim3[CCMR2] |= (0b110<<12); // OC4M, PWM mode 1

	tim3[DIER] |= 0b10001;

	nvic[ISER0] = 1<<29; //TIM3 is IRQ 29

	tim3[CR1] = 1;
}

/**
 * @brief Initializes light block on board
 */
void light_LED_init(void) {
	// Use TIM3_CH4 on PB1, Alternate Mode 2

	volatile uint32_t *gpiob = (uint32_t*) GPIOB;
	volatile uint32_t *rcc_ahb1enr = (uint32_t*) RCC_AHB1_ENR;

	*rcc_ahb1enr |= GPIOBEN;
	gpiob[MODER_INDEX] |= (01<<10)|(01<<12)|(01<<14)|(01<<16)|(01<<18)|(01<<20)|
			(01<<24)|(01<<26)|(01<<28)|(01<<30);

	// init interrupt and timer
	tim_init();
}

void light_leds(unsigned int num) {
	volatile uint32_t *gpiob = (uint32_t*) GPIOB;

	gpiob[ODR_INDEX] &= ~(0b11110111111<<5);
	gpiob[ODR_INDEX] |= (((num & (0b1111<<6))<<1)<<5) | ((num & (0b111111))<<5);
}

/**
 * @brief Lights up the lights on light block in binary
 * @param number - the number to be displayed in binary
 */
void light_LED(unsigned int number) {
	led_number = number;
}

void light_LED_bright(unsigned int duty) {
	led_duty = duty;

	uint32_t period = tim3[ARR] + 1;
	tim3[CCR4] = period*duty/100;
}

void TIM3_IRQHandler(void) {
	if (tim3[SR] & (1<<4)) {
		tim3[SR] = ~(1<<4);
		light_leds(0);
	}

	if (tim3[SR] & 0b1) {
		tim3[SR] = ~0b1;
		if (led_duty != 0) {
			light_leds(led_number);
		}
	}
}
