#include <stddef.h>
#include <stdint.h>
#include <zirv/syscall.h>

extern long _syscall1(long n, long a1);
extern long _syscall2(long n, long a1, long a2);

void exit(int status) {
    _syscall1(SYS_EXIT, status);
    for (;;) ;
}

void abort(void) {
    _syscall1(SYS_EXIT, 1);
    for (;;) ;
}

int atoi(const char *s) {
    int n = 0, sign = 1;
    while (*s == ' ' || *s == '\t' || *s == '\n') s++;
    if (*s == '-') { sign = -1; s++; }
    else if (*s == '+') s++;
    while (*s >= '0' && *s <= '9') n = n * 10 + (*s++ - '0');
    return sign * n;
}

long atol(const char *s) {
    long n = 0;
    int sign = 1;
    while (*s == ' ' || *s == '\t' || *s == '\n') s++;
    if (*s == '-') { sign = -1; s++; }
    else if (*s == '+') s++;
    while (*s >= '0' && *s <= '9') n = n * 10 + (*s++ - '0');
    return sign * n;
}

void *malloc(size_t size) {
    (void)size;
    return NULL;
}

void free(void *ptr) {
    (void)ptr;
}

void *calloc(size_t nmemb, size_t size) {
    return malloc(nmemb * size);
}

void *realloc(void *ptr, size_t size) {
    (void)ptr;
    (void)size;
    return NULL;
}
