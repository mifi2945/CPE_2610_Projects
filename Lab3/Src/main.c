/**
  ******************************************************************************
  * @file		main.c
  * @brief		LED Pong
  *
  * Course:		CPE 2610
  * Section:	131
  * Assignment:	Lab 3
  * Name:		Mikhail Filippov
  * Summary:
  * To start this lab off, we had to code our delay functions as functions
  * of SysTick. This proved to be troublesome, since most of my code was
  * correct, but unfortunately the slides from class had some wrong
  * lines. In particular, the "busy wait" while loop had the wrong condition,
  * where the "!" had to be applied after the bitwise &, not before; the missing
  * parentheses definitely threw me for a "loop" :). Otherwise, the testing
  * process of the delay was fairly simple and straightforward as I just
  * plugged the Analog Discovery into one of the pins that connected to the
  * first LED and ran a simple loop:
  * for(;;){
  *		light_LED(1);
  *		delay_ms(100);
  *		light_LED(0);
  *		delay_ms(100);
  *	}
  *	This allowed me to track the period of the signal, which was almost exactly
  *	100 ms.
  *
  * As for the rest of this lab, it was fairly straightforward from there. I had
  * to choose a GPIO pin for the joystick push button, and wire it to ground on
  * the breadboard. One tedious part of this lab was using the variety of
  * if-else logic that could get confusing to look at eventually.
  ******************************************************************************
*/



#include <stdio.h>
#include <stdint.h>
#include "uart_driver.h"
#include "leds.h"
#include "timer.h"
#include "gpio.h"

#define F_CPU		16000000UL
#define AJPLAYER	(1<<3)
#define REPLAYER	(1<<12)

volatile uint32_t *gpioa = (uint32_t*) GPIOA;
volatile uint32_t *gpiob = (uint32_t*) GPIOB;

// variable for setting delay for difficulty
int diff_delay = 100;

/**
 * @brief initializes the joystick and RE buttons
 */
void init_buttons(void) {
	// enable A and B registers
	volatile uint32_t *rcc_enr = (uint32_t*) RCC_ENR;
	*rcc_enr |= GPIOAEN | GPIOBEN;

	// pull up resistors
	gpioa[PUPDR_INDEX] |= (0b01<<24);
	gpiob[PUPDR_INDEX] |= (0b01<<6);

	// set input mode
	gpioa[MODER_INDEX] |= (0b00<<24);
	gpiob[MODER_INDEX] |= (0b00<<6);
}

/**
 * @brief start game logic
 */
unsigned int start(void) {
	while(1) {
		if (!(gpioa[IDR_INDEX] & REPLAYER)) {
			return REPLAYER;
		}
		if (!(gpiob[IDR_INDEX] & AJPLAYER)) {
			return AJPLAYER;
		}
	}
}
/**
 * @brief sweep left, serving RE
 */
int sweep_RE(unsigned int player) {
	for (int i = 1; i <= 1<<9; i = i<<1) {
		light_LED(i);
		if (!(gpiob[IDR_INDEX]&player)) {
			if (i == (1<<9) || i == (1<<8)) {
				return 1;
			} else {
				return 0;
			}
		}
		delay_ms(diff_delay);
	}
	return 0;
}

/**
 * @brief sweep right, serving AJ
 */
int sweep_AJ(unsigned int player) {
	for (int i = 1<<9; i >= 1; i = i>>1) {
		light_LED(i);
		if (!(gpioa[IDR_INDEX]&player)) {
			if (i == (1) || i == (1<<1)) {
				return 1;
			} else {
				return 0;
			}
		}
		delay_ms(diff_delay);
	}
	return 0;
}

void flash_lights(int volleys, int AJpoints, int REpoints) {
	for (int i = 0; i < 3; ++i) {
		light_LED(1023);
		delay_ms(100);
		light_LED(0);
		delay_ms(100);
	}
	printf("Volleys for this round: %d\n",(volleys)/2);
	printf("Overall Score: %d:%d\n\n", AJpoints, REpoints);
}

// main
int main(void){
	init_usart2(57600,F_CPU);
	light_LED_init();
	init_buttons();


	// keep track of score
	int AJpoints = 0;
	int REpoints = 0;

	// never return
	for(;;) {
		// "one" volley is counted when both players hit the ball
		int volleys = 0;
		diff_delay = 100;
		// start ball
		light_LED((1<<4));
		unsigned int player = start();
		for(;;){
			volleys++;
			// increase difficulty by lowering the delay for ball
			// the longer the game goes on
			diff_delay -= 5;
			if (player == REPLAYER) {
				player = AJPLAYER;
				if (sweep_RE(player)) {
					continue;
				} else {
					REpoints++;
					flash_lights(volleys,AJpoints,REpoints);
					break;
				}
			} else {
				player = REPLAYER;
				if (sweep_AJ(player)) {
					continue;
				} else {
					AJpoints++;
					flash_lights(volleys,AJpoints,REpoints);
					break;
				}
			}
		}
	}
	return 0;
}

