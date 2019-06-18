
/*
 * http://api.marmalade.shop/ExampleOpenALReverb.html
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/poll.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <AL/al.h>
#include <AL/efx.h>
#include <AL/alure.h>

#include "sound.h"


void fn_output(const char *data1, const char *data2);
void fn_play(const char *data1, const char *data2);

static char *fname = "/dev/ttyUSB0";

static int debug = 0;
static double t_now = 0;
static double t_ping = 0;
static double t_pong = 0;
static double t_tick = 0;
static double t_tock = 0;
static double t_bell = 0;
static double t_work = 0;
static int fd = -1;
static int seq = 0;

struct sample {
	const char *fname;
	float pitch;
	float gain;
	ALuint buf;
	ALuint src;
} sample_list[] = {
	[SAMPLE_TICK ] = { "wav/tick.wav",  .pitch=0.8, .gain=0.8,},
	[SAMPLE_TOCK ] = { "wav/tock.wav",  .pitch=0.8, .gain=0.8 },
	[SAMPLE_MECH ] = { "wav/mech.wav",  .pitch=0.6, .gain=0.8 },
	[SAMPLE_BELL ] = { "wav/bell.wav",  .pitch=0.6, .gain=0.8 },
	[SAMPLE_SHOUT] = { "wav/shout.wav", .pitch=1.0, .gain=0.8,},
};


#define SAMPLE_COUNT (sizeof(sample_list) / sizeof(sample_list[0]))


void sound_init(void)
{
	int opt_reverb = 1;

	//system("/usr/sbin/alsactl --file alsa.state restore");

	ALCdevice *device = NULL;
	ALCcontext *context = NULL;
	ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
	ALCenum error;

	const char *opt_device = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);

	device = alcOpenDevice(opt_device);
	if (!device) {
		fprintf(stderr, "unable to open default device\n");
		exit(1);
	}

	ALint attribs[4] = {
		ALC_MAX_AUXILIARY_SENDS, 4,
		0
	};

	context = alcCreateContext(device, attribs);
	if (!alcMakeContextCurrent(context)) {
		fprintf(stderr, "failed to make default context\n");
		exit(1);
	}

	LPALGENEFFECTS alGenEffects = alGetProcAddress("alGenEffects");
	LPALGENAUXILIARYEFFECTSLOTS alGenAuxiliaryEffectSlots = alGetProcAddress("alGenAuxiliaryEffectSlots");
	LPALDELETEEFFECTS alDeleteEffects = alGetProcAddress("alDeleteEffects");
	LPALISEFFECT alIsEffect = alGetProcAddress("alIsEffect");
	LPALEFFECTI alEffecti = alGetProcAddress("alEffecti");
	LPALEFFECTF alEffectf = alGetProcAddress("alEffectf");
	LPALAUXILIARYEFFECTSLOTI alAuxiliaryEffectSloti = alGetProcAddress("alAuxiliaryEffectSloti");
	assert(alEffecti);

	ALuint effect;
	alGenEffects(1, &effect);
	alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_EAXREVERB);
	if (alGetError() != AL_NO_ERROR) printf("Reverb Effect not supported\n");

	ALuint slot;
	alGenAuxiliaryEffectSlots(1, &slot);
	alAuxiliaryEffectSloti(slot, AL_EFFECTSLOT_EFFECT, effect);

	alListener3f(AL_POSITION, -10, 0, 0);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	alListenerfv(AL_ORIENTATION, listenerOri);

	for(int i=0; i<SAMPLE_COUNT; i++) {
		struct sample *s = &sample_list[i];
		s->buf = alureCreateBufferFromFile(s->fname);
		if(s->buf == 0) {
			fprintf(stderr, "Error reading sample %s\n", s->fname);
			exit(1);
		}
		alGenSources((ALuint)1, &s->src);
		alSourcef(s->src, AL_GAIN, s->gain);
		alSourcef(s->src, AL_PITCH, s->pitch);
		alSource3f(s->src, AL_POSITION, 0.5, 0, 0.5);
		alSourcei(s->src, AL_BUFFER, s->buf);
		if(opt_reverb) alSource3i(s->src, AL_AUXILIARY_SEND_FILTER, slot, 0, AL_FILTER_NULL);
	}
}


void sound_play(enum sample_id id)
{
	alSourcePlay(sample_list[id].src);
}

