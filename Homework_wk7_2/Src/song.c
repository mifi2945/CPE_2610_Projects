/**
  ******************************************************************************
  * @file		song.c
  * @brief		Song API
  *
  * Course:		CPE 2610
  * Section:	131
  * Name:		Mikhail Filippov
  ******************************************************************************
*/



#include "song.h"
#include "speaker.h"
#include "delay.h"

#define BPM	80

void play_song(const note *music, int length) {
	for (int i = 0; i < length; ++i) {
		note cur = music[i];
		speaker_tone(cur.freq);
		delay_ms(cur.duration-10);
		speaker_stop();
		delay_ms(10);
	}
}
