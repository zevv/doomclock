#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/poll.h>
#include <time.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include <SDL_mixer.h>

#include "serial.h"


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

static Mix_Chunk *mech;
static Mix_Chunk *bell;
static Mix_Chunk *tick;
static Mix_Chunk *tock;

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
		struct pollfd pfd;

		pfd.fd = fd;
		pfd.events = POLLIN;
		int r = poll(&pfd, 1, 0);
		if(r == 0) break;

		r = read(fd, &c, sizeof(c));
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


void fn_output(const char *data1, const char *data2)
{
	printf("output %s %s\n", data1, data2);
	int onoff = strcmp(data2, "on") == 0;
	io_set(atoi(data1), onoff);
}


void fn_play(const char *data1, const char *data2)
{
	if(strcmp(data1, "mech") == 0) {
		Mix_PlayChannel(3, mech, 0);
	}
	if(strcmp(data1, "bell") == 0) {
		Mix_PlayChannel(3, bell, 0);
	}
}


struct work {
	double t;
	void (*fn)(const char *data1, const char *data2);
	const char *data1, *data2;
	int done;
} work_list[] = {
	{    0.0, fn_output, "1", "on",  },
	{   30.0, fn_output, "2", "on",  },
	{   52.0, fn_play,   "mech"      },
	{   60.0, fn_output, "3", "on"   },
	{   60.0, fn_play,   "bell"      },
	{   64.0, fn_play,   "bell"      },
	{   68.0, fn_play,   "bell"      },
	{   72.0, fn_play,   "bell"      },
	{   76.0, fn_play,   "bell"      },
	{   80.0, fn_play,   "bell"      },
	{   84.0, fn_play,   "bell"      },
	{   88.0, fn_play,   "bell"      },
	{   92.0, fn_play,   "bell"      },
	{   96.0, fn_play,   "bell"      },
	{  100.0, fn_play,   "bell"      },
	{  104.0, fn_play,   "bell"      },
	{  104.0, fn_output, "3", "off"  },
	{  114.0, fn_output, "2", "off"  },
	{  120.0, fn_output, "1", "off"  },
};

#define WORK_COUNT (sizeof(work_list) / sizeof(work_list[0]))


void work_reset(void)
{
	int i;
	for(i=0; i<WORK_COUNT; i++) {
		struct work *w = &work_list[i];
		w->done = 0;
	}
}


void work_do(double t)
{
	int i;
	for(i=0; i<WORK_COUNT; i++) {
		struct work *w = &work_list[i];
		if(!w->done && t >= w->t) {
			w->fn(w->data1, w->data2);
			w->done = 1;
		}
	}
}


int main(int argc, char **argv)
{
	system("/usr/sbin/alsactl --file alsa.state restore");

        Mix_OpenAudio(44100, AUDIO_S16, 2, 32);
	SDL_Init(SDL_INIT_AUDIO | SDL_INIT_NOPARACHUTE);
	mech = Mix_LoadWAV("wav/mech.wav");
	bell = Mix_LoadWAV("wav/bell.wav");
	tick = Mix_LoadWAV("wav/tick.wav");
	tock = Mix_LoadWAV("wav/tock.wav");

	Mix_VolumeChunk(tick, 128);
	Mix_VolumeChunk(tock, 128);
	Mix_VolumeChunk(mech, 50);

	t_tick = 0.0;
	t_tock = 1.5;
	t_bell = 3.0;

	int sec_prev = 0;

	int i;
	for(i=0; i<5; i++) {
		io_set(i, 0);
	}

	for(;;) {

		time_t t = time(NULL);
		struct tm *tm = localtime(&t);

		int hour = tm->tm_hour;
		int sec = tm->tm_sec;
		int min = tm->tm_min;

		if(sec != sec_prev) {
			printf("%02d:%02d:%02d\n", tm->tm_hour, tm->tm_min, tm->tm_sec);
			if(tm->tm_sec == 52 && tm->tm_min == 54) {
				work_reset();
				t_work = t_now;
			}
			sec_prev = sec;
		}


		t_now = SDL_GetTicks() / 1000.0;

		io_poll();

		if(t_now > t_ping) {
			io_cmd("ping");
			t_ping += 0.5;
		}

		if(t_now > t_pong + 2.0) {
			fprintf(stderr, "ping timeout\n");
			t_pong = t_now;
		}

		if(t_now >= t_tick) {
			Mix_PlayChannel(0, tick, 0);
			t_tick += 3.0;
		}

		if(t_now >= t_tock) {
			Mix_PlayChannel(1, tock, 0);
			t_tock += 3.0;
		}

		work_do(t_now - t_work);

		SDL_Delay(10);
	}

	SDL_Quit();

	return 0;
}

