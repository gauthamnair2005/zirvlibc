#ifndef ZIRVLIBC_STDLIB_H
#define ZIRVLIBC_STDLIB_H

#include <stddef.h>

void exit(int status) __attribute__((noreturn));
void abort(void) __attribute__((noreturn));
int atoi(const char *s);
long atol(const char *s);
void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#endif
