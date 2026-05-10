#ifndef ZIRVLIBC_UNISTD_H
#define ZIRVLIBC_UNISTD_H

#include <stddef.h>
#include <zirv/syscall.h>
#include <dirent.h>
#include <datetime.h>

int read(int fd, void *buf, size_t count);
int write(int fd, const void *buf, size_t count);
int open(const char *path, int flags);
int close(int fd);
void _exit(int status) __attribute__((noreturn));
int getpid(void);
int brk(void *addr);
void *sbrk(intptr_t increment);
int execve(const char *pathname, char *const argv[], char *const envp[]);
int getcwd(char *buf, size_t size);
int chdir(const char *path);
int getdents(int fd, struct dirent *ents, int count);
long mmap(void *addr, size_t length, int prot, int flags, int fd, long offset);
int munmap(void *addr, size_t length);
uint64_t uptime(void);
int reboot(void);
int shutdown(void);
int gethostname(char *buf, size_t size);
int sethostname(const char *name, size_t len);

#define PROT_READ   0x1
#define PROT_WRITE  0x2
#define PROT_EXEC   0x4
#define PROT_NONE   0x0

#define MAP_PRIVATE     0x02
#define MAP_ANONYMOUS   0x20
#define MAP_FAILED      ((void *)-1)

#endif
