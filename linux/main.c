
#include <stdio.h>
#include <stdarg.h>
#include <syslog.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/poll.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#include "sound.h"
#include "io.h"
#include "dpy.h"


void fn_output(const char *data1, const char *data2);
void fn_play(const char *data1, const char *data2);

static char *fname = "/dev/ttyUSB0";

static int debug = 0;
static double t_ping = 0;
static double t_pong = 0;
static int fd = -1;
static int seq = 0;


struct work {
	double dt;
	void (*fn)(const char *data1, const char *data2);
	const char *data1, *data2;
	bool done;
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


static double hirestime(void)
{
        struct timespec ts;
        double now;
	static double first = 0.0;

        clock_gettime(CLOCK_MONOTONIC, &ts);
        now = ts.tv_sec + (ts.tv_nsec) / 1.0E9;

	if(first == 0.0) first = now;
        return now - first;
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
	syslog(LOG_NOTICE, "output %s %s\n", data1, data2);
	int onoff = strcmp(data2, "on") == 0;
	io_set(atoi(data1), onoff);
}


void fn_play(const char *data1, const char *data2)
{
	syslog(LOG_NOTICE, "play %s\n", data1);
	if(strcmp(data1, "mech") == 0) {
		sound_play(SAMPLE_MECH);
	}
	if(strcmp(data1, "bell") == 0) {
		sound_play(SAMPLE_BELL);
	}
}


void work_init(bool done)
{
	for(int i=0; i<WORK_COUNT; i++) {
		struct work *w = &work_list[i];
		w->done = done;
	}
}


void work_do(double t_now)
{
	double t = 0;
	for(int i=0; i<WORK_COUNT; i++) {
		struct work *w = &work_list[i];
		t += w->dt;
		if(!w->done && t_now >= t) {
			printf("do %f\n", t_now);
			w->fn(w->data1, w->data2);
			w->done = true;
		}
	}
}


static int fd_gpio20;
static int fd_gpio16;

void buttons_init(void)
{
	system("echo 26 > /sys/class/gpio/export");
	system("echo high > /sys/class/gpio/gpio26/direction");
	
	system("echo 19 > /sys/class/gpio/export");
	system("echo high > /sys/class/gpio/gpio19/direction");

	system("echo 20 > /sys/class/gpio/export");
	fd_gpio20 = open("/sys/class/gpio/gpio20/value", O_RDONLY);
	
	system("echo 16 > /sys/class/gpio/export");
	fd_gpio16 = open("/sys/class/gpio/gpio16/value", O_RDONLY);
}


void buttons_poll(void)
{
	static int ticks_down = 0;

	char buf[5] = "";

	lseek(fd_gpio20, 0, SEEK_SET);
	read(fd_gpio20, buf, sizeof(buf));
	int v_up = buf[0] == '1';
	
	lseek(fd_gpio16, 0, SEEK_SET);
	read(fd_gpio16, buf, sizeof(buf));
	int v_dn = buf[0] == '1';

	if(v_up || v_dn) {

		int dt = 1;
		int m = 10;

		if(ticks_down >   0) { m = 100; dt =    1; }
		if(ticks_down > 100) { m =  50; dt =    1; }
		if(ticks_down > 200) { m =  20; dt =    1; }
		if(ticks_down > 300) { m =  50; dt =   60; }
		if(ticks_down > 400) { m =  20; dt =   60; }
		if(ticks_down > 500) { m =   5; dt =   60; }
		if(ticks_down > 700) { m =   2; dt =   60; }
		if(ticks_down > 800) { m =   1; dt =  120; }

		if(v_dn) dt = -dt;
		
		if((ticks_down % m) == 0) {

			struct timespec ts;
			clock_gettime(CLOCK_REALTIME, &ts);
			ts.tv_sec += dt;
			int r = clock_settime(CLOCK_REALTIME, &ts);
		}
		ticks_down ++;
	} else {
		if(ticks_down > 0) {
			printf("rtc write\n");
			system("../ds1302/ds1302 w");
			ticks_down = 0;
		}
	}
}



int main(int argc, char **argv)
{
	static double t_now = 0;
	double t_tick = 0.0;
	double t_tock = 1.3;
	double t_bell = 3.0;
	double t_work = 0.0;
	time_t t_prev = 0;

	sound_init();
	sound_play(SAMPLE_BELL);

	buttons_init();

	dpy_open();
	dpy_init();
	dpy_clear();
	

	int i;
	for(i=0; i<5; i++) {
		io_set(i, 0);
	}

	work_init(true);
	
	syslog(LOG_NOTICE, "start");

	char ip[32] = "";
	FILE *f = popen("ip addr show dev eth0 | grep ' inet' | awk '{print $2}'", "r");
	fscanf(f, "%s", ip);

	for(;;) {

		time_t t = time(NULL);

		if(t != t_prev) {
			struct tm *tm = localtime(&t);

			dpy_clear();
			dpy_printf(FONT_NORMAL, 0, 0, "ip: %s", ip);
			dpy_printf(FONT_MEDIUM, 0, 24, "%02d:%02d:%02d", tm->tm_hour, tm->tm_min, tm->tm_sec);
			dpy_flush();

			if(tm->tm_sec == 00 && tm->tm_min == 54) {
				work_init(false);
				t_work = t_now;
			}
			t_prev = t;
		}

		t_now = hirestime();
		io_poll();
		buttons_poll();

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

