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

#define GPIOA			0x40020000
#define GPIOB			0x40020400
#define GPIOC			0x40020800
#define GPIOD			0x40020C00

#define RCC_ENR			0x40023830
#define GPIOAEN			(1<<0) //this is in the uart_driver.h file
#define GPIOBEN			(1<<1)
#define GPIOCEN			(1<<2)
#define GPIODEN			(1<<3)

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

#endif /* GPIO_H_ */
