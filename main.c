#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include <SDL_mixer.h>

#include "serial.h"


struct io {
	FILE *f;
	int seq;
};


int io_cmd(struct io *io, const char *fmt, ...)
{
	char buf[64];
	va_list va;
	va_start(va, fmt);
	vsnprintf(buf, sizeof(buf), fmt, va);
	va_end(va);

	io->seq ++;
	fprintf(io->f, "%d:%s\r\n", io->seq, buf);

	return 0;
}


int io_open(char *fname, struct io *io)
{
	int fd = serial_open(fname, 9600, 0, 0, 0, 0);
	io->f = fdopen(fd, "w+");
	io->seq = 0;
	return 0;
}


void io_set(struct io *io, int nr, int onoff)
{
	io_cmd(io, "output %d %d", nr, onoff);
}


int main(int argc, char **argv)
{
	int t = 0;
	system("/usr/sbin/alsactl --file alsa.state restore");
			
	struct io io;
	io_open("/dev/ttyUSB0", &io);

        Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16, 2, 32);
	SDL_Init(SDL_INIT_AUDIO | SDL_INIT_NOPARACHUTE);
	Mix_Chunk *bell = Mix_LoadWAV("bell.wav");

	for(;;) {

		if(t == 4) {
			Mix_PlayChannel(0, bell, 0);
		}

		sleep(1);
		t++;
	}

	SDL_Quit();
				
	return 0;
}

