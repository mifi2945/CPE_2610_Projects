/**
  ******************************************************************************
  * @file		main.c
  * @brief
  *
  * Course:		CPE 2610
  * Section:	131
  * Assignment:	Lab Week 5
  * Name:		Mikhail Filippov
  * Summary:	This was definitely a challenging lab because I encountered
  * a problem when setting up my MODE register; the logic from the keypad
  * was interfering with logic from the LCD. This made it incredibly tough to
  * find the bug, which I did eventually. Furthermore, trying to get the timer
  * bars to show up reasonably while having the keypad responsive was tough,
  * but I eventually found an arguably good balance in the end.
  ******************************************************************************
*/



#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "uart_driver.h"
#include "leds.h"
#include "timer.h"
#include "keypad.h"
#include "lcd.h"

#define F_CPU		16000000UL

int countdown;

void start(void) {
	lcd_print_string("Press any key");
	keypad_getkey();
}

void print_timer(int lines) {
	lcd_set_position(1,0);
	char display[17];
	for (int i = 0; i < lines; ++i) {
		display[i] = '|';
	}
	for (int i = lines; i < 16; ++i) {
		display[i] = ' ';
	}
	lcd_print_string(display);
}

void countdown_key_check(char answer[], int *timer) {
	int i = 0;
	char c;
	while (i < 2 && *timer > 0) {
		if((c=keypad_getchar_noblock()) != 0) {
			lcd_print_char(c);
			answer[i++] = c;
		}
		delay_ms(countdown);
		print_timer(--(*timer));
		if (i == 0) {
			lcd_set_position(0,9);
		} else if (i == 1){
			lcd_set_position(0,10);
		} else {
			break;
		}
	}
}

int game(void) {
	lcd_clear();

	unsigned int random_num = (rand() % 0xFF) + 1;
	int timer = 16;
	light_LED(random_num);

	lcd_print_string("Value: 0x");
	print_timer(timer);
	lcd_set_position(0,9);

	char answer[3];
	countdown_key_check(answer, &timer);

	unsigned int compare;
	sscanf(answer, "%X", &compare);

	delay_ms(1000);
	lcd_clear();
	return (random_num == compare) && timer;
}


// main
int main(void){
	init_usart2(57600,F_CPU);
	keypad_init();
	light_LED_init();
	lcd_init();

	start();

	// never return
	for (;;) {
		int score = 0;
		countdown = 500;
		for (int i = 0; i < 10; ++i) {
			if (game()) {
				lcd_print_string("Correct!");
				score++;
			} else {
				lcd_print_string("Wrong...");
			}
			countdown -= 15;
			delay_ms(1000);
		}
		lcd_clear();
		lcd_print_string("Final Score: ");
		lcd_print_num(score);
		lcd_set_position(1,0);
		lcd_print_string("Restart: any key");
		keypad_getkey();
	}


	return 0;
}

