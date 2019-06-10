
#ifndef event_h
#define event_h

#include <stdint.h>

enum evtype {
	EV_TIMER,
	EV_UART,
};

struct ev_timer {
	enum evtype type;
};

struct ev_uart {
	enum evtype type;
	uint8_t c;
};

struct ev_input {
	enum evtype type;
	uint8_t pin;
	uint8_t state;
};

typedef union {
	enum evtype type;
	struct ev_timer timer;
	struct ev_uart uart;
	struct ev_input input;
} event_t;

void event_push(event_t *ev);
void event_wait(event_t *ev);
uint8_t event_pop(event_t *ev);

#endif
