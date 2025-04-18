/**
  ******************************************************************************
  * @file		main.c
  * @brief		Play a Tune
  *
  * Course:		CPE 2610
  * Section:	131
  * Assignment:	Lab Week 6
  * Name:		Mikhail Filippov
  * Summary:	In this lab, things started fairly smooth. It wasn't too hard to
  * set the timer up (initialize). The harder part was figuring out how to set
  * the ARR and CCRx registers depending on the method of operation for the
  * song. I am glad to say I figured it out in a "eureka" moment, so that wasn't
  * bad. The hard part came in debugging; it was almost impossible to use the
  * debugger until I figured out you can place breakpoints within the ISR. Still,
  * there were many bugs with how the timer would stop playing and not play ever
  * again. After some grueling debugging and trial and error, I resolved it.
  ******************************************************************************
*/



#include <stdio.h>
#include <stdlib.h>
#include "uart_driver.h"
#include "include.h"

#define F_CPU 16000000UL

#define NOCTURNE 	29	//have to define length
#define BPM			80	//MUST put BPM as BPM and BPM only for each song
const note nocturne[NOCTURNE] = {
		{BF4,ENOTE},{G5,HNOTE},{F5,ENOTE},{G5,ENOTE},
		{F5,DQNOTE},{EF5,QNOTE},{BF4,ENOTE},{G5,QNOTE},
		{C5,ENOTE},{C6,QNOTE},{G5,ENOTE},{BF5,DQNOTE},
		{AF5,QNOTE},{G5,ENOTE},{F5,DQNOTE},{G5,QNOTE},
		{D5,ENOTE},{EF5,DQNOTE},{C5,DQNOTE},{BF4,ENOTE},
		{D6,ENOTE},{C6,ENOTE},{BF5,SNOTE},{AF5,SNOTE},
		{G5,SNOTE},{AF5,SNOTE},{C5,SNOTE},{D5,SNOTE},
		{EF5,DQNOTE}
};

#define GRAVITY		30
#define BPM			140
const note gravity[GRAVITY] = {
		{F5,ENOTE},{D5,ENOTE},{A4,ENOTE},{D5,ENOTE},
		{F5,ENOTE},{D5,ENOTE},{A4,ENOTE},{D5,ENOTE},
		{F5,ENOTE},{C5,ENOTE},{A4,ENOTE},{C5,ENOTE},
		{F5,ENOTE},{C5,ENOTE},{A4,ENOTE},{C5,ENOTE},
		{E5,ENOTE},{CS5,ENOTE},{A4,ENOTE},{CS5,ENOTE},
		{E5,ENOTE},{CS5,ENOTE},{A4,ENOTE},{CS5,ENOTE},
		{E5,ENOTE},{CS5,ENOTE},{A4,ENOTE},{CS5,ENOTE},
		{E5,QNOTE},{A5,QNOTE}
};

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

	play_song(gravity, GRAVITY);
	unsigned int random_num = (rand() % 0xFF) + 1;
	int timer = 16;
	led_light(random_num);

	lcd_print_string("Value: 0x");
	print_timer(timer);
	lcd_set_position(0,9);

	char answer[3];
	countdown_key_check(answer, &timer);

	unsigned int compare;
	sscanf(answer, "%X", &compare);

	delay_ms(1000);
	lcd_clear();
	stop_song();
	return (random_num == compare) && timer;
}

// main
int main(void){
	init_usart2(57600,F_CPU);
	keypad_init();
	led_init();
	lcd_init();
	song_init();

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

