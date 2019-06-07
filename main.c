#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include <SDL_mixer.h>

#include "serial.h"

struct io {
	int fd;
	int seq;
};


static int debug = 1;
static int t_now = 0;
static int t_ping = 0;
static int t_pong = 0;
static int t_tick = 0;
static int t_tock = 0;
static int t_bell = 0;
static int t_mech = 0;


void printd(const char *fmt, ...)
{
	if(! debug) return;
	va_list va;
	va_start(va, fmt);
	vfprintf(stderr, fmt, va);
	va_end(va);
}


int io_cmd(struct io *io, const char *fmt, ...)
{
	char buf[64];
	va_list va;
	va_start(va, fmt);
	vsnprintf(buf, sizeof(buf), fmt, va);
	va_end(va);

	char msg[65];
	int l = snprintf(msg, sizeof(msg), "%d:%s\n", io->seq, buf);

	printd("> %s", msg);

	write(io->fd, msg, l);

	io->seq ++;

	return 0;
}


int io_open(char *fname, struct io *io)
{
	io->fd = serial_open(fname, 9600, 0, 0, 0, 0);
	io->seq = 0;
	return 0;
}


void io_set(struct io *io, int nr, int onoff)
{
	io_cmd(io, "output %d %d", nr, onoff);
}


void io_handle(struct io *io, char *line)
{
	printd("< %s\n", line);
	char *seq = strtok(line, ":");
	char *ok = strtok(NULL, ":");
	char *msg = strtok(NULL, ":");

	if(strcmp(msg, "pong") == 0) t_pong = SDL_GetTicks();
}


void io_poll(struct io *io)
{
	static char line[256];
	static int p = 0;

	for(;;) {
		char c;
		int r = read(io->fd, &c, sizeof(c));
		if(r <= 0) {
			break;
		} else if(c == 10 || c == 13) {
			if(p > 0) {
				io_handle(io, line);
			}
			line[0] = 0;
			p = 0;
		} else if(p < sizeof(line)-1) {
			line[p++] = c;
		}
	}
}


int main(int argc, char **argv)
{
	//system("/usr/sbin/alsactl --file alsa.state restore");

	struct io io;
	io_open("/dev/ttyUSB0", &io);

        Mix_OpenAudio(44100, AUDIO_S16, 2, 32);
	SDL_Init(SDL_INIT_AUDIO | SDL_INIT_NOPARACHUTE);
	Mix_Chunk *mech = Mix_LoadWAV("wav/mech.wav");
	Mix_Chunk *bell = Mix_LoadWAV("wav/bell.wav");
	Mix_Chunk *tick = Mix_LoadWAV("wav/tick.wav");
	Mix_Chunk *tock = Mix_LoadWAV("wav/tock.wav");

	Mix_VolumeChunk(mech, 70);

	t_tick = 0;
	t_tock = 1500;
	t_mech = 6000;
	t_bell = 8000;

	for(;;) {

		t_now = SDL_GetTicks();

		io_poll(&io);

		if(t_now > t_ping) {
			io_cmd(&io, "ping");
			t_ping += 500;
		}

		if(t_now > t_pong + 2000) {
			fprintf(stderr, "ping timeout\n");
		}

		if(t_now >= t_tick) {
			Mix_PlayChannel(0, tick, 0);
			t_tick += 3000;
		}

		if(t_now >= t_tock) {
			Mix_PlayChannel(1, tock, 0);
			t_tock += 3000;
		}

		if(t_mech && t_now >= t_mech) {
			Mix_PlayChannel(3, mech, 0);
			t_mech = 0;
		}

		if(t_bell && t_now >= t_bell) {
			Mix_PlayChannel(2, bell, 3);
			t_bell = 0;
		}

		SDL_Delay(1);
	}

	SDL_Quit();

	return 0;
}

