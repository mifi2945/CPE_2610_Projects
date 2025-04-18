/**
  ******************************************************************************
  * @file		main.c
  * @brief		Interpret IR Remote
  *
  * Course:		CPE 2610
  * Section:	131
  * Assignment:	Lab Week 9
  * Name:		Mikhail Filippov
  * Summary:	So PA3 is broken... or set up in a way that makes it unusable.
  * 			Unfortunately, I did not know that, so I spent way too long
  * 			trying to debug something that was not "debug-able."
  * 			Once I switched through a couple of pins and finally decided to
  * 			rewrite my song API to use TIM5 so I can use TIM2 for this,
  * 			things were starting to look easier; nevertheless, there was a
  * 			big bug with debouncing the remote (since we can't really do
  * 			that in the ISR to my knowledge). I had to improvise, which led
  * 			me to create the read_ready() method, letting me set when the
  * 			process was ready to read from the remote manually.
  ******************************************************************************
*/



#include <stdio.h>
#include <string.h>
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

static char buffer[80];
static int volume = 5;

static uint16_t start(void) {
	uint16_t button = 0;
	while (button != POWER) {
		read_ready();
		button = ir_get_command();
	}
	return button;
}

static void print_buffer(void) {
	lcd_clear();
	lcd_print_string(buffer);
}

static void handle_vol(void) {
	speaker_volume(volume*10);
	if (get_duration() == 0) {
		speaker_tone(A5);
		delay_ms(100);
		speaker_stop();
	}
}

static void handle_button(uint16_t command) {
	lcd_clear();
	char button[16];
	int delay = 500;
	switch (command) {
	case POWER:
		strcpy(button, "POWER");
		break;
	case MUTE:
		strcpy(button, "MUTE");
		break;
	case VOL_UP:
		strcpy(button, "VOL UP");
		volume = volume == 10 ? 10 : volume + 1;
		delay = 200;
		handle_vol();
		break;
	case VOL_DOWN:
		strcpy(button, "VOL DOWN");
		volume = volume == 0 ? 0 : volume - 1;
		delay = 200;
		handle_vol();
		break;
	case CH_UP:
		strcpy(button, "CH UP");
		strcpy(buffer, "Gravity");
		play_song(gravity, GRAVITY);
		break;
	case CH_DOWN:
		strcpy(button, "CH DOWN");
		strcpy(buffer, "Nocturne");
		play_song(nocturne, NOCTURNE);
		break;
	case NUM_1:
		strcpy(button, "NUM 1");
		break;
	case NUM_2:
		strcpy(button, "NUM 2");
		break;
	case NUM_3:
		strcpy(button, "NUM 3");
		break;
	case NUM_4:
		strcpy(button, "NUM 4");
		break;
	case NUM_5:
		strcpy(button, "NUM 5");
		break;
	case NUM_6:
		strcpy(button, "NUM 6");
		break;
	case NUM_7:
		strcpy(button, "NUM 7");
		break;
	case NUM_8:
		strcpy(button, "NUM 8");
		break;
	case NUM_9:
		strcpy(button, "NUM 9");
		break;
	case NUM_0:
		strcpy(button, "NUM 0");
		break;
	case EXIT:
		strcpy(button, "EXIT");
		strcpy(buffer, "Welcome!");
		stop_song();
		break;
	default:
		strcpy(button, "");
	}
	lcd_print_string(button);
	delay_ms(delay);
	print_buffer();
}

// main
int main(void){
	init_usart2(57600,F_CPU);
	lcd_init();
	keypad_init();
	song_init();
	ir_init();

	speaker_volume(10);
	// never return
	for(;;){
		strcpy(buffer, "Welcome!");
		// press "POWER" to turn "on"
		handle_button(start());

		uint16_t button = 0;
		while (button != POWER) {
			if (button != 0) {
				handle_button(button);
			}
			read_ready();
			button = ir_get_command();
		}
		stop_song();
		lcd_clear();
		lcd_print_string("Goodbye...");
		delay_ms(1000);
		lcd_clear();
	}
	return 0;
}

