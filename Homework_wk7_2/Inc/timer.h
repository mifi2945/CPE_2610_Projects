/**
  ******************************************************************************
  * @file		timer.h
  * @brief		Timer Header file for TIM constants
  *
  * Course:		CPE 2610
  * Section:	131
  * Name:		Mikhail Filippov
  ******************************************************************************
*/

#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

#define TIM3			0x40000400
#define TIM3_EN			(1<<1)

#define CR1		0
#define CR2		1
#define SMCR	2
#define DIER	3
#define SR		4
#define EGR		5
#define CCMR1	6
#define CCMR2	7
#define CCER	8
#define CNT		9
#define PSC		10
#define ARR		11
//#define RESERVED 12
#define CCR1	13
#define	CCR2	14
#define CCR3	15
#define CCR4	16
//#define RESERVED 17
#define DCR		18
#define DMAR	19
#define OR		20


extern volatile uint32_t *tim3;

#endif /* TIMER_H_ */
