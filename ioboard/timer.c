#include <avr/io.h>
#include <avr/interrupt.h>

#include "timer.h"
#include "event.h"


/*
 * Setup timer 0 
 */

void timer_init(void)
{
	/* Fast PWM mode, enable interrupt on overflow */

	TCCR0A = (1<<WGM01) | (1<<WGM00);
	TCCR0B = (1<<CS11) | (1<<CS10);
	TIMSK0 |= (1<<TOIE0);

}


/*
 * Timer0 overflow interrupt @ 1Khz
 */

ISR(TIMER0_OVF_vect)
{
	static uint8_t c = 0;

	if(c++ == 10) {
		event_t ev;
		ev.type = EV_TIMER;
		event_push(&ev);
		c = 0;
	}
}


/*
 * End
 */


