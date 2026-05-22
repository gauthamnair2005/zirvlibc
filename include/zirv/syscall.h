#ifndef ZIRV_SYSCALL_H
#define ZIRV_SYSCALL_H

#include <stdint.h>

/* ── Syscall numbers (matching Linux x86-64 ABI) ────────────────────────── */
#define SYS_READ     0
#define SYS_WRITE    1
#define SYS_OPEN     2
#define SYS_CLOSE    3
#define SYS_MMAP     9
#define SYS_MUNMAP   11
#define SYS_BRK      12
#define SYS_UPTIME   13
#define SYS_PIPE     22
#define SYS_GETPID   39
#define SYS_EXECVE   59
#define SYS_EXIT     60
#define SYS_WAIT4    61
#define SYS_GETDENTS   78
#define SYS_GETCWD     79
#define SYS_CHDIR      80
#define SYS_MKDIR      83
#define SYS_RMDIR      84
#define SYS_UNLINK     85
#define SYS_RENAME     86
#define SYS_GETHOSTNAME 89
#define SYS_SETHOSTNAME 90
#define SYS_GETDATETIME 96
#define SYS_SETDATETIME 97
#define SYS_GETTZ       98
#define SYS_SETTZ       99
#define SYS_REBOOT     100
#define SYS_SHUTDOWN   101
#define SYS_DNS_LOOKUP 102
#define SYS_PCI_READ  103
#define SYS_MSLEEP    124

/* ── Open flags ──────────────────────────────────────────────────────────── */
#define O_CREAT  0x40

/* ── Standard I/O FDs ────────────────────────────────────────────────────── */
#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

/* ── Error codes ─────────────────────────────────────────────────────────── */
#define ENOENT   2
#define EBADF    9
#define ECHILD  10
#define ENOMEM  12
#define EACCES  13
#define EFAULT  14
#define EINVAL  22
#define EPIPE   32
#define ERANGE  34
#define ENOSYS  38

#endif /* ZIRV_SYSCALL_H */
