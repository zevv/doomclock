
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/poll.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#include "sound.h"
#include "io.h"


void fn_output(const char *data1, const char *data2);
void fn_play(const char *data1, const char *data2);

static char *fname = "/dev/ttyUSB0";

static int debug = 0;
static double t_now = 0;
static double t_ping = 0;
static double t_pong = 0;
static int fd = -1;
static int seq = 0;


struct work {
	double dt;
	void (*fn)(const char *data1, const char *data2);
	const char *data1, *data2;
	int done;
} work_list[] = {
	{   0.0, fn_output, "1", "on",  },
	{  30.0, fn_output, "2", "on",  },
	{  18.0, fn_play,   "mech"      },
	{  12.0, fn_output, "3", "on"   },
	{   0.0, fn_play,   "bell"      },
	{   4.0, fn_play,   "bell"      },
	{   4.0, fn_play,   "bell"      },
	{   4.0, fn_play,   "bell"      },
	{   4.0, fn_play,   "bell"      },
	{   4.0, fn_play,   "bell"      },
	{   4.0, fn_play,   "bell"      },
	{   4.0, fn_play,   "bell"      },
	{   4.0, fn_play,   "bell"      },
	{   4.0, fn_play,   "bell"      },
	{   4.0, fn_play,   "bell"      },
	{   4.0, fn_play,   "bell"      },
	{   0.0, fn_output, "3", "off"  },
	{  10.0, fn_output, "2", "off"  },
	{   6.0, fn_output, "1", "off"  },
};


#define WORK_COUNT (sizeof(work_list) / sizeof(work_list[0]))


double hirestime(void)
{
	static double t_first = 0;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	double t_now =  tv.tv_sec + tv.tv_usec * 1.0e-6;
	if(t_first == 0) t_first = t_now;
	return t_now - t_first;
}


void io_handle(char *line)
{
	char *seq = strtok(line, ";");
	char *ok = strtok(NULL, ";");
	char *msg = strtok(NULL, ";");

	if(strcmp(msg, "pong") == 0) {
		t_pong = hirestime();
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
		sound_play(SAMPLE_MECH);
	}
	if(strcmp(data1, "bell") == 0) {
		sound_play(SAMPLE_BELL);
	}
}


void work_init(void)
{
	for(int i=0; i<WORK_COUNT; i++) {
		struct work *w = &work_list[i];
		w->done = 0;
	}
}


void work_do(double t_now)
{
	double t = 0;
	for(int i=0; i<WORK_COUNT; i++) {
		struct work *w = &work_list[i];
		t += w->dt;
		if(!w->done && t_now >= t) {
			w->fn(w->data1, w->data2);
			w->done = 1;
		}
	}
}


int main(int argc, char **argv)
{
	double t_tick = 0.0;
	double t_tock = 1.3;
	double t_bell = 3.0;
	double t_work = 0.0;
	int sec_prev = 0;

	sound_init();

	io_dpy_clear();
	io_dpy_text(1, 0, 0, "RUNNING");

	int i;
	for(i=0; i<5; i++) {
		io_set(i, 0);
	}

	work_init();

	for(;;) {

		time_t t = time(NULL);
		struct tm *tm = localtime(&t);

		int hour = tm->tm_hour;
		int sec = tm->tm_sec;
		int min = tm->tm_min;

		if(sec != sec_prev) {
			char buf[] = "xx:xx:xx";
			buf[0] = (tm->tm_hour / 10) + '0';
			buf[1] = (tm->tm_hour % 10) + '0';
			buf[3] = (tm->tm_min  / 10) + '0';
			buf[4] = (tm->tm_min  % 10) + '0';
			buf[6] = (tm->tm_sec  / 10) + '0';
			buf[7] = (tm->tm_sec  % 10) + '0';

			io_dpy_text(2, 0, 24, buf);
			if(tm->tm_sec == 00 && tm->tm_min == 54) {
				work_init();
				t_work = t_now;
			}
			sec_prev = sec;
		}

		t_now = hirestime();
		io_poll();

		if(t_now > t_ping) {
			io_cmd("ping");
			t_ping += 0.5;
		}

		if(t_now > t_pong + 2.0) {
			//fprintf(stderr, "ping timeout\n");
			t_pong = t_now;
		}

		if(t_now >= t_tick) {
			sound_play(SAMPLE_TICK);
			t_tick += 3.0;
		}

		if(t_now >= t_tock) {
			sound_play(SAMPLE_TOCK);
			t_tock += 3.0;
		}

		work_do(t_now - t_work);

		usleep(10 * 1000);
	}

	return 0;
}

