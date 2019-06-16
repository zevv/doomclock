#ifndef io_h
#define io_h

void io_open(void);
void io_cmd(const char *fmt, ...);
void io_set(int nr, int onoff);
void io_dpy_clear(void);
void io_dpy_text(int font, int x, int y, const char *msg);
void io_handle(char *line);
void io_poll(void);

#endif

