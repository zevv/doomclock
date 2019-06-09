#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#include "event.h"
#include "printd.h"
#include "timer.h"
#include "uart.h"
#include "msg.h"
#include "gpio.h"
#include "spi.h"
#include "dpy.h"

static uint8_t fn_version(struct msg *m);
static uint8_t fn_reset(struct msg *m);


int main(void)
{
	event_t ev;

	/* Init subsystems */

	msg_init();
	uart_init(UART_BAUD(9600));
	timer_init();
	gpio_init();
	spi_init();
	dpy_init();

	dpy_text(FONT_NORMAL, 0, 0, "     READY      ");
	dpy_flush();

	msg_add_handler("version", fn_version, 0);
	msg_add_handler("reset", fn_reset, 0);

	/* Enable interrupts */

	sei();

	/* Send startup msg */

	msg_send_event("hello");

	/* Handle event queue */

	for(;;) {

		event_wait(&ev);

		if(ev.type == EV_UART) {
			msg_handle_char(ev.uart.c);
		}

		if(ev.type == EV_TIMER) {
			gpio_poll();
		}
	}
}


static uint8_t fn_version(struct msg *m)
{
	msg_reply(m, "%s %s %s", NAME, VERSION, DATE);
	return 0;
}


static uint8_t fn_reset(struct msg *m)
{
	void (*reset)(void) = NULL;
	reset();
	return 0;
}


/*
 * End
 */

