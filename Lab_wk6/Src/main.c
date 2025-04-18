/**
  ******************************************************************************
  * @file		main.c
  * @brief		Play a Tune
  *
  * Course:		CPE 2610
  * Section:	131
  * Assignment:	Lab Week 6
  * Name:		Mikhail Filippov
  * Summary:	This lab was fun AFTER figuring the timer logic out; although, that
  * wasn't necessarily too hard either. A lot of tabs with manuals and datasheets
  * had to be open for this lab, so there was difficulty in finding everything.
  * Otherwise, most of the work was just busy work by trying to set up the
  * notes and song orders, which took a while.
  ******************************************************************************
*/



#include <stdio.h>
#include "uart_driver.h"
#include "delay.h"
#include "speaker.h"
#include "lcd.h"
#include "keypad.h"
#include "leds.h"
#include "song.h"

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
#define BPM			160
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


int volume = 5;


/**
 * @brief print the volume bar to LCD based on volume
 */
void print_volume() {
	lcd_set_position(1,0);
	char display[17];
	for (int i = 0; i < volume; ++i) {
		display[i] = '|';
	}
	for (int i = volume; i < 10; ++i) {
		display[i] = ' ';
	}
	lcd_print_string(display);
	speaker_tone(A5);
	speaker_volume(volume*10);
	delay_ms(100);
	speaker_stop();
}

/**
 * @brief function to start up and return song select
 */
char welcome(void) {
	lcd_print_string("Song:1/2");
	lcd_set_position(0,10);
	lcd_print_string("B-down");
	lcd_set_position(1,12);
	lcd_print_string("A-up");
	print_volume();
	char key = keypad_getchar();
	while(key != '1' && key != '2') {
		if (key == 'A') {
			volume = volume == 10 ? 10 : volume + 1;
		} else if (key == 'B') {
			volume = volume == 0 ? 0 : volume - 1;
		}
		print_volume();
		key = keypad_getchar();
	}
	lcd_clear();
	return key;
}

// main
int main(void){
	init_usart2(57600,F_CPU);
	speaker_init();
	keypad_init();
	lcd_init();

	// never return
	for(;;){
		int song = welcome();
		if (song == '1') {
			play_song(nocturne, NOCTURNE);
		} else if (song == '2'){
			play_song(gravity, GRAVITY);
		}
		delay_ms(400);
	}
	return 0;
}

