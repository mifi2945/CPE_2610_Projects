/**
  ******************************************************************************
  * @file		leds.h
  * @brief		Knight Rider Lights
  *
  * Course:		CPE 2610
  * Section:	131
  * Assignment:	Lab 2
  * Name:		Mikhail Filippov
  ******************************************************************************
*/

#ifndef LEDS_H_
#define LEDS_H_

#define GPIOA			0x40020000
#define GPIOB			0x40020400
#define GPIOC			0x40020800
#define GPIOD			0x40020C00

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


void light_LED_init(void);
void light_LED(unsigned int);


#endif /* LEDS_H_ */
