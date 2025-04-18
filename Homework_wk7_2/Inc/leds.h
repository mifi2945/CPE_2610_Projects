/**
  ******************************************************************************
  * @file		leds.h
  * @brief		Led + GPIO control header
  *
  * Course:		CPE 2610
  * Section:	131
  * Name:		Mikhail Filippov
  ******************************************************************************
*/

#ifndef LEDS_H_
#define LEDS_H_


void light_LED_init(void);
void light_LED(unsigned int);
void light_LED_bright(unsigned int);

#endif /* LEDS_H_ */
