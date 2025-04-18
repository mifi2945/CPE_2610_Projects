/**
  ******************************************************************************
  * @file    main.c
  * @author  Mikhail Filippov
  * @Lab 	 1
  * @brief   Default main function.
  ******************************************************************************
*/



#include <stdio.h>
#include <stdlib.h>
#include "uart_driver.h"

#define F_CPU 16000000UL

void function(void);

const char *global_const = "Hello";
int global_int = 122;


// main
int main(void){
	init_usart2(57600,F_CPU);

	int local_main = 27;

	printf("An int type takes up %d bytes of memory.\n",sizeof(int));
	printf("A float type takes up %d bytes of memory.\n",sizeof(float));
	printf("A double type takes up %d bytes of memory.\n",sizeof(double));
	printf("A long int type takes up %d bytes of memory.\n",sizeof(long int));
	printf("An int* type takes up %d bytes of memory.\n",sizeof(int*));
	printf("A char* type takes up %d bytes of memory.\n",sizeof(char*));

	printf("The memory address of a local variable in main is %p.\n",&local_main);
	printf("The memory address of a global variable in main is %p.\n",&global_int);
	function();

	printf("The memory address of a cont global variable is %p.\n",&global_const);

	printf("The memory address of main is %p.\n",main);
	printf("The memory address of the function is %p.\n",function);
	printf("The memory address of printf is %p.\n",printf);

	int *heap = malloc(sizeof(int));
	printf("The memory address of the start of the heap is %p.\n",heap);
	free(heap);

	// never return
	for(;;){}

	return 0;
}

void function(void) {
	int local_func = 72;

	printf("The memory address of a local variable in a function is %p.\n",&local_func);
	printf("The memory address of a global variable in a function is %p.\n",&global_int);
}

