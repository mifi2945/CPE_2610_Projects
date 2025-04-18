/**
  ******************************************************************************
  * @file    main.c
  * @author  Auto-generated by STM32CubeIDE
  * @version V1.0
  * @brief   Default main function.
  ******************************************************************************
*/



#include <stdio.h>
#include "uart_driver.h"

#define F_CPU 16000000UL
#define ID_REG 0xe0042000

// main
int main(void){
	init_usart2(57600,F_CPU);

	uint32_t *id = (uint32_t*)ID_REG;
	printf("The full register contents are: 0x%x\n",(unsigned int)*id);
	printf("The device ID is: 0x%x",(unsigned int)(*id & 0xFFF));

	// never return
	for(;;){}

	return 0;
}

