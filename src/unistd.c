#include <zirv/syscall.h>
#include <stddef.h>
#include <dirent.h>

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

int execve(const char *pathname, char *const argv[], char *const envp[]) {
    return (int)_syscall3(SYS_EXECVE, (long)pathname, (long)argv, (long)envp);
}

int getdents(int fd, struct dirent *ents, int count) {
    return (int)_syscall3(SYS_GETDENTS, fd, (long)ents, count);
}

int getcwd(char *buf, size_t size) {
    return (int)_syscall2(SYS_GETCWD, (long)buf, (long)size);
}

int chdir(const char *path) {
    return (int)_syscall1(SYS_CHDIR, (long)path);
}

uint64_t uptime(void) {
    return (uint64_t)_syscall0(SYS_UPTIME);
}

int getpid(void) {
    return (int)_syscall0(SYS_GETPID);
}

int brk(void *addr) {
    return (int)_syscall1(SYS_BRK, (long)addr);
}

void *sbrk(intptr_t increment) {
    uintptr_t cur = (uintptr_t)_syscall1(SYS_BRK, 0);
    if (cur == (uintptr_t)-1) return (void *)-1;
    if (increment == 0) return (void *)cur;
    uintptr_t new = cur + increment;
    uintptr_t result = (uintptr_t)_syscall1(SYS_BRK, new);
    if (result == (uintptr_t)-1) return (void *)-1;
    return (void *)cur;
}

long mmap(void *addr, size_t length, int prot, int flags, int fd, long offset) {
    (void)fd;
    (void)offset;
    return _syscall4(SYS_MMAP, (long)addr, (long)length, prot, flags);
}

int munmap(void *addr, size_t length) {
    return (int)_syscall2(SYS_MUNMAP, (long)addr, (long)length);
}

int reboot(void) {
    return (int)_syscall0(SYS_REBOOT);
}

int shutdown(void) {
    return (int)_syscall0(SYS_SHUTDOWN);
}
