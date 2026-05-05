#include <zirv/syscall.h>
#include <stddef.h>

/* Forward declarations of internal syscall wrappers from syscall.c */
extern long _syscall0(long n);
extern long _syscall1(long n, long a1);
extern long _syscall2(long n, long a1, long a2);
extern long _syscall3(long n, long a1, long a2, long a3);
extern long _syscall4(long n, long a1, long a2, long a3, long a4);
extern long _syscall5(long n, long a1, long a2, long a3, long a4, long a5);
extern long _syscall6(long n, long a1, long a2, long a3, long a4, long a5, long a6);

int read(int fd, void *buf, size_t count) {
    return (int)_syscall3(SYS_READ, fd, (long)buf, (long)count);
}

int write(int fd, const void *buf, size_t count) {
    return (int)_syscall3(SYS_WRITE, fd, (long)buf, (long)count);
}

int open(const char *path, int flags) {
    return (int)_syscall2(SYS_OPEN, (long)path, flags);
}

int close(int fd) {
    return (int)_syscall1(SYS_CLOSE, fd);
}

void _exit(int status) {
    _syscall1(SYS_EXIT, status);
    for (;;) ; /* Should not be reached */
}

int getpid(void) {
    return (int)_syscall0(SYS_GETPID);
}
