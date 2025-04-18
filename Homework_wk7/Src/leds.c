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


#include "leds.h"
#include "gpio.h"
#include <stdint.h>

/**
 * @brief Initializes light block on board
 */
void light_LED_init(void) {
	volatile uint32_t *gpiob = (uint32_t*) GPIOB;
	volatile uint32_t *rcc_ahb1enr = (uint32_t*) RCC_AHB1_ENR;

	*rcc_ahb1enr |= (1<<1);
	gpiob[MODER_INDEX] |= (01<<10)|(01<<12)|(01<<14)|(01<<16)|(01<<18)|(01<<20)|
			(01<<24)|(01<<26)|(01<<28)|(01<<30);
}

/**
 * @brief Lights up the lights on light block in binary
 * @param number - the number to be displayed in binary
 */
void light_LED(unsigned int number) {
	volatile uint32_t *gpiob = (uint32_t*) GPIOB;

	gpiob[ODR_INDEX] &= ~(0b11110111111<<5);
	gpiob[ODR_INDEX] |= (((number & (0b1111<<6))<<1)<<5) | ((number & (0b111111))<<5);
}

