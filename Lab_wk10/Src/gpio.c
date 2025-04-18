/**
  ******************************************************************************
  * @file		gpio.c
  * @brief		GPIO addresses
  *
  * Course:		CPE 2610
  * Section:	131
  * Name:		Mikhail Filippov
  ******************************************************************************
*/

#include "gpio.h"

volatile uint32_t *gpioa = (uint32_t*) GPIOA;
volatile uint32_t *gpiob = (uint32_t*) GPIOB;
volatile uint32_t *gpioc = (uint32_t*) GPIOC;
volatile uint32_t *gpiod = (uint32_t*) GPIOD;
