#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "printd.h"
#include "uart.h"

struct sc {
	char *s;
	uint8_t l;
};


static uint8_t _vprintd(void (*fn)(char c, void *fndata), void *fndata, const char *fmt, va_list va)
{
	const char *p = fmt;
	char buf[6];
	uint8_t l = 0;

	while(*p) {
		if(*p == '%') {
			p++;
			if(*p == 'd' || *p == 'x') {
				int val = va_arg(va, int);
				itoa(val, buf, *p == 'd' ? 10 : 16);
				char *q = buf;
				while(*q) {
					fn(*q++, fndata);
					l++;
				}
			} 
			if(*p == 's') {
				char *q = va_arg(va, char *);
				while(*q) {
					fn(*q++, fndata);
					l++;
				}
			}
		} else {
			fn(*p, fndata);
			l++;
		}
		p++;
	}

	return l;
}


static void fn_uart(char c, void *data)
{
	uart_tx(c);
}


static void fn_str(char c, void *data)
{
	struct sc *sc = data;
	if(sc->l > 1) {
		*(sc->s) = c;
		sc->s++;
		sc->l--;
	}
}

uint8_t vprintd(const char *fmt, va_list va)
{
	return _vprintd(fn_uart, NULL, fmt, va);
}


uint8_t printd(const char *fmt, ...)
{
	uint8_t l;
	va_list va;
	va_start(va, fmt);
	l = vprintd(fmt, va);
	va_end(va);
	return l;
}


uint8_t vsnprintd(char *s, uint8_t l, const char *fmt,  va_list va)
{
	uint8_t r;
	struct sc sc;
	sc.s = s;
	sc.l = l;
	r = _vprintd(fn_str, &sc, fmt, va);
	*(sc.s) = '\0';
	return r;
}


uint8_t snprintd(char *s, uint8_t l, const char *fmt,  ...)
{
	uint8_t r;
	va_list va;
	va_start(va, fmt);
	r = vsnprintd(s, l, fmt, va);
	va_end(va);
	return r;
}


/* 
 * End
 */
