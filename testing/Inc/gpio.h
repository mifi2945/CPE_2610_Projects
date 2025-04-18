/**
  ******************************************************************************
  * @file		gpio.h
  * @brief		GPIO addresses
  *
  * Course:		CPE 2610
  * Section:	131
  * Name:		Mikhail Filippov
  ******************************************************************************
*/



#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>

#define F_CPU 16000000UL

#define GPIOA			0x40020000
#define GPIOB			0x40020400
#define GPIOC			0x40020800
#define GPIOD			0x40020C00

extern volatile uint32_t *gpioa;
extern volatile uint32_t *gpiob;
extern volatile uint32_t *gpioc;
extern volatile uint32_t *gpiod;

#define RCC_AHB1_ENR	0x40023830
#define RCC_AHB2_ENR	0x40023834
#define RCC_APB1_ENR	0x40023840
#define RCC_APB2_ENR	0x40023844


#define GPIOAEN			(1<<0) //this is in the uart_driver.h file
#define GPIOBEN			(1<<1)
#define GPIOCEN			(1<<2)
#define GPIODEN			(1<<3)

#define MODER_INDEX		0
#define OTYPER_INDEX	1
#define SPEED_INDEX		2
#define PUPDR_INDEX		3
#define IDR_INDEX		4
#define ODR_INDEX		5
#define BSRR_INDEX		6
#define LCKR_INDEX		7
#define AFRL_INDEX		8
#define AFRH_INDEX		9

#endif /* GPIO_H_ */
