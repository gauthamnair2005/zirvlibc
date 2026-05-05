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
#define SYS_PIPE     22
#define SYS_GETPID   39
#define SYS_EXIT     60

/* ── Standard I/O FDs ────────────────────────────────────────────────────── */
#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

/* ── Error codes ─────────────────────────────────────────────────────────── */
#define EBADF   9
#define ENOMEM  12
#define EFAULT  14
#define EINVAL  22
#define EPIPE   32
#define ENOSYS  38

#endif /* ZIRV_SYSCALL_H */
