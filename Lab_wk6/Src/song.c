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
/*
void static nocturne(void) {
	const int NOCTURNE = 29;
	note nocturne[NOCTURNE] = {
			{BF4,ENOTE},{G5,HNOTE},{F5,ENOTE},{G5,ENOTE},
			{F5,DQNOTE},{EF5,QNOTE},{BF4,ENOTE},{G5,QNOTE},
			{C5,ENOTE},{C6,QNOTE},{G5,ENOTE},{BF5,DQNOTE},
			{AF5,QNOTE},{G5,ENOTE},{F5,DQNOTE},{G5,QNOTE},
			{D5,ENOTE},{EF5,DQNOTE},{C5,DQNOTE},{BF4,ENOTE},
			{D6,ENOTE},{C6,ENOTE},{BF5,SNOTE},{AF5,SNOTE},
			{G5,SNOTE},{AF5,SNOTE},{C5,SNOTE},{D5,SNOTE},
			{EF5,SNOTE}
	};
}
*/
