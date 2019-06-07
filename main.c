#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include <SDL_mixer.h>

#include "serial.h"


static char *fname = "/dev/ttyUSB0";

static int debug = 1;
static int t_now = 0;
static int t_ping = 0;
static int t_pong = 0;
static int t_tick = 0;
static int t_tock = 0;
static int t_bell = 0;
static int t_mech = 0;
static int fd = -1;
static int seq = 0;


void printd(const char *fmt, ...)
{
	if(! debug) return;
	va_list va;
	va_start(va, fmt);
	vfprintf(stderr, fmt, va);
	va_end(va);
}


void io_open(void)
{
	if(fd == -1) {
		fd = serial_open(fname, 9600, 0, 0, 0, 0);
	}
}


int io_cmd(const char *fmt, ...)
{
	char buf[64];
	va_list va;
	va_start(va, fmt);
	vsnprintf(buf, sizeof(buf), fmt, va);
	va_end(va);

	char msg[65];
	int l = snprintf(msg, sizeof(msg), "%d:%s\n", seq, buf);

	printd("> %s", msg);

	io_open();
	int r = write(fd, msg, l);
	if(r <= 0) {
		close(fd);
		fd = -1;
	}

	seq ++;

	return 0;
}


void io_set(int nr, int onoff)
{
	io_cmd("output %d %d", nr, onoff);
}


void io_handle(char *line)
{
	printd("< %s\n", line);
	char *seq = strtok(line, ":");
	char *ok = strtok(NULL, ":");
	char *msg = strtok(NULL, ":");

	if(strcmp(msg, "pong") == 0) t_pong = SDL_GetTicks();
}


void io_poll(void)
{
	static char line[256];
	static int p = 0;
		
	io_open();

	for(;;) {
		char c;
		int r = read(fd, &c, sizeof(c));
		if(r == 0) {
			break;
		} else if(r == -1) {
			close(fd);
			fd = -1;
			break;
		} else if(c == 10 || c == 13) {
			if(p > 0) {
				line[p] = '\0';
				io_handle(line);
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


        Mix_OpenAudio(44100, AUDIO_S16, 2, 32);
	SDL_Init(SDL_INIT_AUDIO | SDL_INIT_NOPARACHUTE);
	Mix_Chunk *mech = Mix_LoadWAV("wav/mech.wav");
	Mix_Chunk *bell = Mix_LoadWAV("wav/bell.wav");
	Mix_Chunk *tick = Mix_LoadWAV("wav/tick.wav");
	Mix_Chunk *tock = Mix_LoadWAV("wav/tock.wav");

	Mix_VolumeChunk(tick, 128);
	Mix_VolumeChunk(tock, 128);
	Mix_VolumeChunk(mech, 50);

	t_tick = 0;
	t_tock = 1500;

	int sec_prev = 0;
	int t_mech = 2000;
	int t_bell = t_mech + 8000;

	for(;;) {

		time_t t = time(NULL);
		struct tm *tm = localtime(&t);

		int hour = tm->tm_hour;
		int sec = tm->tm_sec;
		int min = tm->tm_min;

		if(sec != sec_prev) {
			printf("%02d:%02d:%02d\n", tm->tm_hour, tm->tm_min, tm->tm_sec);
			if(tm->tm_sec == 0) {
				t_mech = t_now;
				t_bell = t_now + 8000;
			}
			sec_prev = sec;
		}


		t_now = SDL_GetTicks();

		io_poll();

		if(t_now > t_ping) {
			io_cmd("ping");
			t_ping += 500;
		}

		if(t_now > t_pong + 2000) {
			fprintf(stderr, "ping timeout\n");
			t_pong = t_now;
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

		SDL_Delay(10);
	}

	SDL_Quit();

	return 0;
}

