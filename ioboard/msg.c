#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <util/crc16.h>

#include "printd.h"
#include "uart.h"
#include "msg.h"

static uint8_t echo = 0;

struct handler {
	const char *cmd;
	uint8_t (*fn)(struct msg *m);
	uint8_t nargs;
};


static uint8_t nhandlers = 0;
static struct handler handler_list[MSG_MAX_HANDLERS] = { { NULL } };


static uint16_t calc_crc16(const void *data, uint8_t len)
{
	uint16_t crc = 0;
	while(len--) crc = _crc16_update(crc, *(uint8_t *)data++);
	return crc;
}


static void msg_send(const char *seq, const char *type, const char *body)
{
	if(!seq) seq = "0";
	uint16_t sum = calc_crc16(body, strlen(body));
	printd("%s:%s:%s:%x\n", seq, type, body, sum);
}


void msg_send_event(const char *fmt, ...)
{
	char body[MSG_MAX_BODY_LEN];
	va_list va;
	va_start(va, fmt);
	vsnprintd(body, sizeof body, fmt, va);
	va_end(va);
	msg_send("!", "ev", body);
}


void msg_reply(struct msg *m, char *fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	vsnprintd(m->reply, sizeof(m->reply), fmt, va);
	va_end(va);
}


static uint8_t split(char *str, char sep, char **part, uint8_t maxparts)
{
	int parts=0;
	char *p1 = str;
	char *p2;
	
	part[parts++] = p1;
	
	while((p2 = strchr(p1, sep)) &&  (parts<maxparts)) {
		*p2=0;
		p1 = p2+1;
		part[parts++]=p1;
	}
	
	return(parts);
}


static uint8_t msg_parse(struct msg *m, char *buf)
{
	char *part[8];
	uint8_t parts;
	char *body = NULL;
	char *seq = NULL;
	char *cksum = NULL;

	parts = split(buf, ':', part, 8);

	if(parts == 1) {
		body = part[0];
	} else if(parts == 2) {
		seq = part[0];
		body = part[1];
	} else if(parts == 3) {
		seq = part[0];
		body = part[1];
		cksum = part[2];
	} else {
		msg_reply(m, "syntax error");
		return 1;
	}

	/* Validate checksum, if given */

	if(cksum) {
		uint16_t sum1 = strtol(cksum, NULL, 16);
		uint16_t sum2 = calc_crc16(body, strlen(body));

		if(sum1 != sum2) {
			msg_reply(m, "checksum fail");
			return 1;
		}
	}

	/* Split body into command and arguments */

	parts = split(body, ' ', part, 8);

	/* Find and call handler for given command */

	uint8_t i;
	char *cmd = part[0];
	m->seq = seq;
	m->argc = parts - 1;
	m->argv = part + 1;

	for(i=0; i<nhandlers; i++) {
		struct handler *handler = &handler_list[i];
		if(strcmp(handler->cmd, cmd) == 0) {
			if(m->argc >= handler->nargs) {
				return handler->fn(m);
			} else {
				msg_reply(m, "wrong nr of arguments");
				return 1;
			}
		}
	}
	
	msg_reply(m, "unknown command");
	return 1;
}


static void msg_handle(char *buf)
{
	struct msg m = { 0 };
	uint8_t rv = msg_parse(&m, buf);
	msg_send(m.seq, rv ? "err" : "ok", m.reply);
}


void msg_handle_char(char c)
{
	static char buf[64];
	static uint8_t p = 0;

	if(c == '\n' || c == '\r') {
		if(echo) uart_tx('\n');
		msg_handle(buf);
		p = 0;
		buf[0] = 0;
	} else if(c == '\b' || c == 127) {
		if(p > 0) {
			p--;
			buf[p] = '\0';
			if(echo) printd("\b \b");
		}
	} else {
		if(p < sizeof(buf)-1) {
			if(echo) uart_tx(c);
			buf[p] = c;
			p ++;
			buf[p] = '\0';
		}
	}
}


void msg_add_handler(const char *cmd, msg_handler fn, uint8_t nargs)
{
	if(nhandlers < MSG_MAX_HANDLERS) {
		struct handler *handler = &handler_list[nhandlers++];
		handler->cmd = cmd;
		handler->fn = fn;
		handler->nargs = nargs;
	}
}


static uint8_t fn_empty(struct msg *m)
{
	return 0;
}


static uint8_t fn_ping(struct msg *m)
{
	msg_reply(m, "pong");
	return 0;
}


static uint8_t fn_echo(struct msg *m)
{
	if(m->argc == 1) {
		if(strcmp(m->argv[0], "on") == 0) echo = 1;
		if(strcmp(m->argv[0], "off") == 0) echo = 0;
	}
	msg_reply(m, "echo %s", echo ? "on" : "off");
	return 0;
}


static uint8_t fn_help(struct msg *m)
{
	char buf[64] = "";
	uint8_t i;
	for(i=0; i<nhandlers; i++) {
		struct handler *handler = &handler_list[i];
		if(handler->cmd[0]) {
			strcat(buf, handler->cmd);
			if(i<nhandlers-1) strcat(buf, ",");
		}
	}
	msg_reply(m, buf);
	return 0;
}


void msg_init(void)
{
	msg_add_handler("", fn_empty, 0);
	msg_add_handler("ping", fn_ping, 0);
	msg_add_handler("echo", fn_echo, 0);
	msg_add_handler("help", fn_help, 0);
}


/*
 * End
 */

