#ifndef ZIRVLIBC_STDIO_H
#define ZIRVLIBC_STDIO_H

#include <stdarg.h>
#include <stddef.h>

int vsnprintf(char *str, size_t size, const char *format, va_list ap);
int snprintf(char *str, size_t size, const char *format, ...);

int vprintf(const char *format, va_list ap);
int printf(const char *format, ...);
int puts(const char *s);
int putchar(int c);

#endif
