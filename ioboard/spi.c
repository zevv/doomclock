#include <stdint.h>
#include <stdlib.h>
#include <stdint.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "spi.h"
#include "msg.h"
#include "printd.h"

static uint8_t fn_spi(struct msg *m)
{
	spi_tx((void *)"\x00\xff\x55", 3);
	return 0;
}

/*
 * Enable SPI in master mode, set SCK and MOSI to output. In master mode PB2
 * functions as the slave select, and should be set to output mode to be able
 * to use the SPI in master mode.
 */

void spi_init()
{ 
	DDRB |= (1<<PB2) | (1<<PB3) | (1<<PB4) | (1<<PB5);
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0) | (1<<SPR1) | (1<<CPOL) | (1<<CPHA);

	msg_add_handler("spi", fn_spi, 0);
}


void spi_tx(uint8_t *buf, uint8_t len)
{

	PORTB &= ~(1<<PB4);

	while(len--) {
		SPDR = *buf++;
		while(!(SPSR & (1<<SPIF)));
	}
	PORTB |= (1<<PB4);
}
	

/*
 * End
 */

