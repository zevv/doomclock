
#include <avr/io.h>
#include <string.h>
#include <stdlib.h>

#include "gpio.h"
#include "printd.h"
#include "msg.h"

#define INPUT_COUNT 4
#define OUTPUT_COUNT 5


struct input {
	uint8_t mask;
	uint8_t shift;
	uint8_t state;
	uint8_t count;
};

struct output {
	uint8_t mask;
	uint8_t state;
};

	
static uint8_t fn_input(struct msg *m);
static uint8_t fn_inputs(struct msg *m);
static uint8_t fn_output(struct msg *m);
static uint8_t fn_outputs(struct msg *m);


struct input input_list[INPUT_COUNT] = {
	{ .mask = (1<<PC0) },
	{ .mask = (1<<PC1) },
	{ .mask = (1<<PC2) },
	{ .mask = (1<<PC3) },
};

struct output output_list[OUTPUT_COUNT] = {
	{ .mask = (1<<PD2) },
	{ .mask = (1<<PD3) },
	{ .mask = (1<<PD4) },
	{ .mask = (1<<PD5) },
	{ .mask = (1<<PD6) },
};


void gpio_init(void)
{
	DDRD |= 0xfc;
	DDRC &= ~((1<<PC1) | (1<<PC2) | (1<<PC3) | (1<<PC4));
	
	msg_add_handler("input", fn_input, 1);
	msg_add_handler("inputs", fn_inputs, 0);
	msg_add_handler("output", fn_output, 1);
	msg_add_handler("outputs", fn_outputs, 0);
}
	

void gpio_poll(void)
{
	uint8_t v = ~PINC;
	uint8_t i;

	/* Read and debounce inputs */

	for(i=0; i<INPUT_COUNT; i++) {

		struct input *input = &input_list[i];
		input->shift <<= 1;
		if(v & input->mask) input->shift |= 1;

		uint8_t prev_state = input->state;

		if(input->state == 0 && input->shift == 0xff) {
			input->state = 1;
			input->count ++;
		}

		if(input->state == 1 && input->shift == 0x00) {
			input->state = 0;
		}

		if(input->state != prev_state) {
			msg_send_event("input %x %x %x", i+1, input->state, input->count);
		}
	}
}


static uint8_t fn_input(struct msg *m)
{
	uint8_t pin = strtol(m->argv[0], NULL, 16);

	if(pin < 1 || pin > INPUT_COUNT) {
		msg_reply(m, "pin out of range");
		return 1;
	}

	struct input *input = &input_list[pin-1];
	msg_reply(m, "input %x %x %x", pin, input->state, input->count);

	input->count = 0;
	return 0;
}


static uint8_t fn_inputs(struct msg *m)
{
	uint8_t pin;
	uint8_t mask = 0;
	
	for(pin=0; pin<INPUT_COUNT; pin++) {
		struct input *input = &input_list[pin];
		if(input->state) mask |= (1<<pin);
	}

	msg_reply(m, "inputs %x", mask);
	return 0;
}


static uint8_t fn_output(struct msg *m)
{
	uint8_t pin = strtol(m->argv[0], NULL, 16);

	if(pin < 1 || pin > OUTPUT_COUNT) {
		msg_reply(m, "pin out of range");
		return 0;
	}
	
	struct output *output = &output_list[pin-1];
		
	if(m->argc == 2) {
		output->state = !!strtol(m->argv[1], NULL, 16);
		if(output->state) {
			PORTD |= output->mask;
		} else {
			PORTD &= ~output->mask;
		}
	}

	msg_reply(m, "output %x %x", pin, output->state);
	return 0;
}


static uint8_t fn_outputs(struct msg *m)
{
	uint8_t mask;
	uint8_t pin;

	if(m->argc > 0) {
		mask = strtol(m->argv[0], NULL, 16);

		for(pin=0; pin<OUTPUT_COUNT; pin++) {
			struct output *output = &output_list[pin];
			output->state = !!(mask & 1<<pin);

			if(output->state) {
				PORTD |= output->mask;
			} else {
				PORTD &= ~output->mask;
			}
		}
	}
	
	mask = 0;
	for(pin=0; pin<OUTPUT_COUNT; pin++) {
		struct output *output = &output_list[pin];
		if(output->state) mask |= (1<<pin);
	}
	msg_reply(m, "outputs %x", mask);

	return 0;
}


/*
 * End
 */

