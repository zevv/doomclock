#include <stdint.h>
#include <stdlib.h>
#include <stdint.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "spi.h"
#include "msg.h"
#include "printd.h"

static uint8_t fn_spi(struct msg *m)
{
	spi_tx((void *)"\x00\xff\x0f", 3, 1);
	return 0;
}

/*
 * Enable SPI in master mode, set SCK and MOSI to output. In master mode PB2
 * functions as the slave select, and should be set to output mode to be able
 * to use the SPI in master mode.
 */

void spi_init()
{ 
	PORTB |= (1<<PB3) | (1<<PB4) | (1<<PB5);
	DDRB |= (1<<PB3) | (1<<PB4) | (1<<PB5);

	msg_add_handler("spi", fn_spi, 0);
}


static void mosi(uint8_t v)
{
	if(v) {
		PORTB |= (1<<PB3);
	} else {
		PORTB &= ~(1<<PB3);
	}
}

static void sck(uint8_t v)
{
	if(v) {
		PORTB |= (1<<PB5);
	} else {
		PORTB &= ~(1<<PB5);
	}
}

static void cs(uint8_t v)
{
	if(v) {
		PORTB |= (1<<PB4);
	} else {
		PORTB &= ~(1<<PB4);
	}
}


void spi_tx(uint8_t *buf, size_t len, uint8_t b9)
{
	cs(0);

	while(len--) {
		sck(0);
		mosi(b9);
		sck(1);

		uint8_t v = *buf++;
		for(uint8_t i=0; i<8; i++) {
			sck(0);
			mosi(v & 0x80);
			sck(1);
			v <<= 1;
		}
	}
	
	mosi(1);
	cs(1);
}
	

/*
 * End
 */

