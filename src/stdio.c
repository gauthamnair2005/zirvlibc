#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <zirv/syscall.h>

/* Forward declaration of unistd wrappers */
extern int write(int fd, const void *buf, size_t count);

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
    while (*s) {
        sink_putc(sink, *s++);
    }
}

static void utoa_base(uint64_t n, unsigned int base, char *out) {
    static const char digits[] = "0123456789abcdef";
    char rev[65];
    size_t i = 0;

    if (n == 0) {
        out[0] = '0';
        out[1] = '\0';
        return;
    }

    while (n > 0) {
        rev[i++] = digits[n % base];
        n /= base;
    }

    for (size_t j = 0; j < i; ++j) {
        out[j] = rev[i - 1U - j];
    }
    out[i] = '\0';
}

int vsnprintf(char *str, size_t size, const char *format, va_list ap) {
    sink_t sink = {
        .buf = str,
        .size = size,
        .written = 0,
    };

    for (const char *p = format; *p; ++p) {
        if (*p != '%') {
            sink_putc(&sink, *p);
            continue;
        }

        p++;
        if (*p == '\0') break;

        int pad_len = 0;
        char pad_char = ' ';

        if (*p == '0') {
            pad_char = '0';
            p++;
        }
        while (*p >= '0' && *p <= '9') {
            pad_len = pad_len * 10 + (*p - '0');
            p++;
        }

        switch (*p) {
            case 's': {
                const char *s = va_arg(ap, const char *);
                sink_puts(&sink, s ? s : "(null)");
                break;
            }
            case 'd': {
                int n = va_arg(ap, int);
                uint32_t u;
                if (n < 0) {
                    sink_putc(&sink, '-');
                    u = (n == (-2147483647 - 1)) ? 2147483648u : (uint32_t)(-n);
                } else {
                    u = (uint32_t)n;
                }
                char buf[32];
                utoa_base((uint64_t)u, 10u, buf);
                sink_puts(&sink, buf);
                break;
            }
            case 'u': {
                char buf[32];
                utoa_base((uint64_t)va_arg(ap, uint32_t), 10u, buf);
                sink_puts(&sink, buf);
                break;
            }
            case 'x': {
                char buf[32];
                utoa_base((uint64_t)va_arg(ap, uint32_t), 16u, buf);
                int len = 0;
                while (buf[len]) len++;
                while (len < pad_len) {
                    sink_putc(&sink, pad_char);
                    len++;
                }
                sink_puts(&sink, buf);
                break;
            }
            case 'p': {
                char buf[65];
                sink_puts(&sink, "0x");
                utoa_base((uint64_t)(uintptr_t)va_arg(ap, void *), 16u, buf);
                sink_puts(&sink, buf);
                break;
            }
            case 'c':
                sink_putc(&sink, (char)va_arg(ap, int));
                break;
            case '%':
                sink_putc(&sink, '%');
                break;
            default:
                sink_putc(&sink, '%');
                sink_putc(&sink, *p);
                break;
        }
    }

    if (size > 0) {
        size_t term_pos = (sink.written < size) ? sink.written : (size - 1U);
        sink.buf[term_pos] = '\0';
    }

    return (int)sink.written;
}

int snprintf(char *str, size_t size, const char *format, ...) {
    va_list ap;
    int ret;

    va_start(ap, format);
    ret = vsnprintf(str, size, format, ap);
    va_end(ap);

    return ret;
}

#ifndef KERNEL
int putchar(int c) {
    char ch = (char)c;
    if (write(STDOUT_FILENO, &ch, 1) != 1) {
        return -1;
    }
    return (unsigned char)ch;
}

int puts(const char *s) {
    size_t len = 0;
    while (s[len]) len++;
    if (write(STDOUT_FILENO, s, len) != (int)len) return -1;
    if (putchar('\n') == -1) return -1;
    return 0;
}

int vprintf(const char *format, va_list ap) {
    char buf[1024];
    int ret = vsnprintf(buf, sizeof(buf), format, ap);
    if (ret > 0) {
        write(STDOUT_FILENO, buf, (size_t)ret);
    }
    return ret;
}

int printf(const char *format, ...) {
    va_list ap;
    int ret;

    va_start(ap, format);
    ret = vprintf(format, ap);
    va_end(ap);

    return ret;
}
#endif
