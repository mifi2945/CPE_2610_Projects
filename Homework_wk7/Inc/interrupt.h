/**
  ******************************************************************************
  * @file		interrupt.h
  * @brief		Interrupt API Header
  *
  * Course:		CPE 2610
  * Section:	131
  * Name:		Mikhail Filippov
  ******************************************************************************
*/

#ifndef INTERRUPT_H_
#define INTERRUPT_H_


#define EXTI	0x40013C00
#define IMR		0
#define EMR		1
#define RTSR	2
#define FTSR	3
#define SWIER	4
#define PR		5


#define SYSCFG	0x40013800

#define NVIC	0xE000E100
#define ISER0	0
#define ISER1	1
#define ISER2	2


void handler_init(void);



#endif /* INTERRUPT_H_ */
