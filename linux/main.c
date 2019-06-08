#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/poll.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <AL/al.h>
#include <AL/alure.h>

#include "serial.h"


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

#define TEST_ERROR(_msg)		\
	error = alGetError();		\
	if (error != AL_NO_ERROR) {	\
		fprintf(stderr, _msg "\n");	\
		exit(1);		\
	}

struct sample {
	const char *fname;
	float pitch;
	float gain;
	ALuint buf;
	ALuint src;
} sample_list[] = {
	{ "wav/tick.wav", .pitch=0.8, .gain=1.0 },
	{ "wav/tock.wav", .pitch=0.8, .gain=1.0 },
	{ "wav/mech.wav", .pitch=0.6, .gain=1.0 },
	{ "wav/bell.wav", .pitch=0.6, .gain=1.0 },
};


struct work {
	double t;
	void (*fn)(const char *data1, const char *data2);
	const char *data1, *data2;
	int done;
} work_list[] = {
	{    0.0, fn_output, "1", "on",  },
	{   30.0, fn_output, "2", "on",  },
	{   48.0, fn_play,   "mech"      },
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
#define SAMPLE_COUNT (sizeof(sample_list) / sizeof(sample_list[0]))


double hirestime(void)
{
	static double t_first = 0;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	double t_now =  tv.tv_sec + tv.tv_usec * 1.0e-6;
	if(t_first == 0) t_first = t_now;
	return t_now - t_first;
}


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


void io_cmd(const char *fmt, ...)
{
	char buf[64];
	va_list va;
	va_start(va, fmt);
	vsnprintf(buf, sizeof(buf), fmt, va);
	va_end(va);

	char msg[65];
	int l = snprintf(msg, sizeof(msg), "%d,%s\n", seq, buf);
	printd("> %s", msg);

	io_open();
	int r = write(fd, msg, l);
	if(r <= 0) {
		close(fd);
		fd = -1;
	}

	seq ++;
}


void io_set(int nr, int onoff)
{
	io_cmd("output %d %d", nr, onoff);
}


void io_dpy_clear(void)
{
	io_cmd("dpy c");
}


void io_dpy_l1(const char *msg)
{
	io_cmd("dpy 1 %s", msg);
}


void io_dpy_l2(int h, int m)
{
	io_cmd("dpy 2 %02d:%02d", h, m);
}


void io_handle(char *line)
{
	printd("< %s\n", line);
	char *seq = strtok(line, ":");
	char *ok = strtok(NULL, ":");
	char *msg = strtok(NULL, ":");

	if(strcmp(msg, "pong") == 0) t_pong = hirestime();
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
		alSourcePlay(sample_list[2].src);
	}
	if(strcmp(data1, "bell") == 0) {
		alSourcePlay(sample_list[3].src);
	}
}



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
	//system("/usr/sbin/alsactl --file alsa.state restore");

	ALCdevice *device = NULL;
	ALCcontext *context = NULL;
	ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
	ALCenum error;

	const char *opt_device = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);

	printd("Opening OpenAL audio device \"%s\"", opt_device);

	device = alcOpenDevice(opt_device);
	if (!device) {
		fprintf(stderr, "unable to open default device\n");
		exit(1);
	}

	context = alcCreateContext(device, NULL);
	if (!alcMakeContextCurrent(context)) {
		fprintf(stderr, "failed to make default context\n");
		exit(1);
	}
	TEST_ERROR("make default context");

	alListener3f(AL_POSITION, 0, 0, 0);
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
		//alSource3f(s->src, AL_POSITION, -.5, 0, 0.5);
		alSourcei(s->src, AL_BUFFER, s->buf);
		TEST_ERROR("source generation");
	}

	t_tick = 0.0;
	t_tock = 1.3;
	t_bell = 3.0;
			
	int sec_prev = 0;

	io_dpy_clear();
	io_dpy_l1("TickTock");

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
			io_dpy_l2(min, sec);
			printf("%02d:%02d:%02d\n", tm->tm_hour, tm->tm_min, tm->tm_sec);
			if(tm->tm_sec == 00 && tm->tm_min == 54) {
				work_reset();
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
			fprintf(stderr, "ping timeout\n");
			t_pong = t_now;
		}

		if(t_now >= t_tick) {
			alSourcePlay(sample_list[0].src);
			t_tick += 3.0;
		}

		if(t_now >= t_tock) {
			alSourcePlay(sample_list[1].src);
			t_tock += 3.0;
		}

		work_do(t_now - t_work);

		usleep(10 * 1000);
	}

	return 0;
}

