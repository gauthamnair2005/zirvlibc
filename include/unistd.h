#ifndef ZIRVLIBC_UNISTD_H
#define ZIRVLIBC_UNISTD_H

#include <stddef.h>
#include <stdint.h>
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
int mkdir(const char *path);
int rmdir(const char *path);
int unlink(const char *path);
int rename(const char *oldpath, const char *newpath);

/* DNS: resolve a domain name to an IPv4 address.
 * Returns the IP in host byte order on success, 0 on failure. */
uint32_t dns_lookup(const char *domain);

#define PROT_READ   0x1
#define PROT_WRITE  0x2
#define PROT_EXEC   0x4
#define PROT_NONE   0x0

#define MAP_PRIVATE     0x02
#define MAP_ANONYMOUS   0x20
#define MAP_FAILED      ((void *)-1)

#endif
