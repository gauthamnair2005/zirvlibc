#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
    char *buf;
    size_t size;
    size_t written;
} sink_t;

static void sink_putc(sink_t *sink, char c) {
    if (sink->written + 1 < sink->size) {
        sink->buf[sink->written] = c;
    }
    sink->written++;
}

static void sink_puts(sink_t *sink, const char *s) {
    if (!s) s = "(null)";
    while (*s) sink_putc(sink, *s++);
}

static void utoa_base(uint64_t n, unsigned int base, char *out) {
    static const char digits[] = "0123456789abcdef";
    char rev[65];
    size_t i = 0;
    if (n == 0) { out[0] = '0'; out[1] = '\0'; return; }
    while (n > 0) { rev[i++] = digits[n % base]; n /= base; }
    for (size_t j = 0; j < i; ++j) out[j] = rev[i - 1U - j];
    out[i] = '\0';
}

int vsnprintf(char *str, size_t size, const char *format, va_list ap) {
    sink_t sink = { .buf = str, .size = size, .written = 0 };
    for (const char *p = format; *p; ++p) {
        if (*p != '%') { sink_putc(&sink, *p); continue; }
        p++;
        if (*p == '\0') break;

        if (*p == '0') {
            while (*p >= '0' && *p <= '9') p++;
            if (*p == '\0') break;
        }

        int long_count = 0;
        while (*p == 'l') { long_count++; p++; }
        if (*p == '\0') break;

        switch (*p) {
            case 's': sink_puts(&sink, va_arg(ap, const char *)); break;
            case 'd': {
                long n;
                if (long_count >= 1) n = va_arg(ap, long);
                else n = va_arg(ap, int);
                char buf[32];
                uint64_t abs = n < 0 ? -(uint64_t)n : (uint64_t)n;
                utoa_base(abs, 10, buf);
                if (n < 0) sink_putc(&sink, '-');
                sink_puts(&sink, buf);
                break;
            }
            case 'u': {
                uint64_t n;
                if (long_count >= 1) n = va_arg(ap, unsigned long);
                else n = va_arg(ap, unsigned int);
                char buf[32]; utoa_base(n, 10, buf);
                sink_puts(&sink, buf);
                break;
            }
            case 'x': {
                uint64_t n;
                if (long_count >= 1) n = va_arg(ap, unsigned long);
                else n = va_arg(ap, unsigned int);
                char buf[32]; utoa_base(n, 16, buf);
                sink_puts(&sink, buf);
                break;
            }
            case 'p': {
                char buf[32]; sink_puts(&sink, "0x");
                utoa_base((uint64_t)(uintptr_t)va_arg(ap, void *), 16, buf);
                sink_puts(&sink, buf);
                break;
            }
            case 'c': sink_putc(&sink, (char)va_arg(ap, int)); break;
            case '%': sink_putc(&sink, '%'); break;
            default: sink_putc(&sink, '%'); sink_putc(&sink, *p); break;
        }
    }
    if (size > 0) {
        size_t term = (sink.written < size) ? sink.written : (size - 1);
        sink.buf[term] = '\0';
    }
    return (int)sink.written;
}

#ifndef KERNEL
#include <zirv/syscall.h>
#include <stdarg.h>
extern int write(int fd, const void *buf, size_t count);

int snprintf(char *str, size_t size, const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    int n = vsnprintf(str, size, format, ap);
    va_end(ap);
    return n;
}

int vprintf(const char *format, va_list ap) {
    char buf[1024];
    int n = vsnprintf(buf, sizeof(buf), format, ap);
    if (n > 0) write(1, buf, n);
    return n;
}

int printf(const char *fmt, ...) {
    va_list ap; char buf[1024]; va_start(ap, fmt);
    int n = vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    if (n > 0) write(1, buf, n);
    return n;
}

int putchar(int c) {
    char ch = (char)c;
    write(1, &ch, 1);
    return (unsigned char)c;
}

int puts(const char *s) {
    if (!s) return -1;
    while(*s) {
        char c = *s++;
        write(1, &c, 1);
    }
    char n = '\n';
    write(1, &n, 1);
    return 0;
}
#endif
