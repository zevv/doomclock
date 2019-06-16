#ifndef sound_h
#define sound_h

enum sample_id {
	SAMPLE_TICK,
	SAMPLE_TOCK,
	SAMPLE_MECH,
	SAMPLE_BELL,
	SAMPLE_SHOUT
};

void sound_init(void);
void sound_play(enum sample_id id);

#endif


