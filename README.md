# zirvlibc — Zirvium C Library

Freestanding C library for Zirvium userspace programs. Implements a subset of the C standard library and POSIX syscall wrappers targeting the Linux x86-64 syscall ABI (used by Zirvium's kernel).

## Headers

| Header | Contents |
|--------|----------|
| `string.h` | `memcpy`, `memset`, `memmove`, `memcmp`, `strlen`, `strcmp`, `strncmp`, `strcpy`, `strncpy`, `strcat`, `strchr`, `strrchr`, `strstr` |
| `ctype.h` | `isalpha`, `isdigit`, `isalnum`, `isspace`, `isupper`, `islower`, `toupper`, `tolower` |
| `stdio.h` | `printf`, `snprintf`, `vsnprintf`, `puts`, `kprintf` (kernel), `kputs` (kernel) |
| `stdlib.h` | `exit` |
| `unistd.h` | `read`, `write`, `open`, `close`, `_exit`, `getpid`, `brk`, `sbrk`, `execve`, `getcwd`, `chdir`, `mmap`, `munmap` |
| `zirv/syscall.h` | Syscall number definitions (Linux x86-64 ABI) |

## Syscall wrappers

All use the `SYSCALL` instruction following Linux x86-64 conventions:

- `SYS_READ` (0), `SYS_WRITE` (1), `SYS_OPEN` (2), `SYS_CLOSE` (3)
- `SYS_MMAP` (9), `SYS_MUNMAP` (11), `SYS_BRK` (12)
- `SYS_PIPE` (22)
- `SYS_GETPID` (39)
- `SYS_EXECVE` (59), `SYS_EXIT` (60), `SYS_WAIT4` (61)
- `SYS_GETCWD` (79), `SYS_CHDIR` (80)

## Build

```bash
make
```

Produces `libzirvlibc.a`.
