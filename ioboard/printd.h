#ifndef printd_h
#define printd_h

#include <stdarg.h>

uint8_t printd(const char *fmt, ...);
uint8_t vprintd(const char *fmt, va_list va);
uint8_t vsnprintd(char *s, uint8_t l, const char *fmt,  va_list va);
uint8_t snprintd(char *s, uint8_t l, const char *fmt,  ...);

#endif
