
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

#include "serial.h"
#include "io.h"

static char *fname = "/dev/ttyUSB0";

static int fd = -1;
static int seq = 0;


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
	int l = snprintf(msg, sizeof(msg), "%d;%s\n", seq, buf);

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


void io_dpy_text(int font, int x, int y, const char *msg)
{
	io_cmd("dpy t %d %d %d %s", font, x, y, msg);
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


