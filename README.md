# zirvlibc — Reference MOSIX C Library

Freestanding C library for **MOSIX** operating systems. Provides the standard C
functions and syscall wrappers needed by all MOSIX userspace programs.

This is the **reference implementation** of the MOSIX userspace ABI. Any
MOSIX-compliant kernel can run programs built against zirvlibc.

| | |
|---|---|
| **Website** | [zirvworld](https://github.com/gauthamnair2005/zirvworld) |
| **MOSIX spec** | [standard.html](https://github.com/gauthamnair2005/zirvworld/blob/main/standard.html) |
| **License** | GPLv3 |

---

## Headers

| Header | Contents |
|--------|----------|
| `string.h` | `memcpy`, `memset`, `memmove`, `memcmp`, `strlen`, `strnlen`, `strcmp`, `strncmp`, `strcpy`, `strncpy`, `strcat`, `strchr`, `strrchr`, `strstr` |
| `ctype.h` | `isalpha`, `isdigit`, `isalnum`, `isspace`, `isupper`, `islower`, `toupper`, `tolower` |
| `stdio.h` | `printf`, `snprintf`, `vsnprintf`, `vprintf`, `puts`, `putchar` — supports `%s %d %u %lu %llu %x %p %c %%` with zero-padded width |
| `stdlib.h` | `exit`, `abort`, `atoi`, `atol` (`malloc`/`free` are stubs returning NULL) |
| `unistd.h` | `read`, `write`, `open`, `close`, `_exit`, `getpid`, `brk`, `sbrk`, `execve`, `getcwd`, `chdir`, `mmap`, `munmap`, `uptime`, `reboot`, `shutdown`, `gethostname`, `sethostname` |
| `datetime.h` | `getdatetime`, `setdatetime`, `gettz`, `settz` with `struct datetime` |
| `dirent.h` | `struct dirent` (ino + name[256]), `getdents` |
| `zirv/syscall.h` | Syscall number definitions (0-101), FD constants, error codes |

---

## Syscall Wrappers

All use the `SYSCALL` instruction following the MOSIX x86-64 ABI:

```
RAX = syscall number
RDI = arg1  RSI = arg2  RDX = arg3
R10 = arg4  R8  = arg5  R9  = arg6
Return: RAX = result or negative errno
```

Wrappers provided: `_syscall0` through `_syscall6` via inline assembly.

### Syscall numbers

| # | Name | # | Name | # | Name |
|---|------|---|------|---|------|
| 0 | SYS_READ | 13 | SYS_UPTIME | 89 | SYS_GETHOSTNAME |
| 1 | SYS_WRITE | 22 | SYS_PIPE | 90 | SYS_SETHOSTNAME |
| 2 | SYS_OPEN | 39 | SYS_GETPID | 96 | SYS_GETDATETIME |
| 3 | SYS_CLOSE | 59 | SYS_EXECVE | 97 | SYS_SETDATETIME |
| 9 | SYS_MMAP | 60 | SYS_EXIT | 98 | SYS_GETTZ |
| 11 | SYS_MUNMAP | 61 | SYS_WAIT4 | 99 | SYS_SETTZ |
| 12 | SYS_BRK | 78 | SYS_GETDENTS | 100 | SYS_REBOOT |
|   |        | 79 | SYS_GETCWD | 101 | SYS_SHUTDOWN |
|   |        | 80 | SYS_CHDIR |     |        |

---

## Build

```bash
make          # produces libzirvlibc.a
make test     # builds and runs unit tests
```

The test suite verifies string operations (memcpy, memmove, memset, strcmp,
strstr), character classification, and printf formatting.

---

## MOSIX Compatibility

This library is designed for the **MOSIX** operating system standard. It is
used by:
- [zirvium](https://github.com/gauthamnair2005/zirvium) — The reference MOSIX kernel
- [zirvinit](https://github.com/gauthamnair2005/zirvinit) — PID 1 init system
- [zirvshell](https://github.com/gauthamnair2005/zirvshell) — Interactive shell
- [zirvutils](https://github.com/gauthamnair2005/zirvutils) — System utilities
- [zirvui](https://github.com/gauthamnair2005/zirvui) — Desktop compositor

Any MOSIX-compliant kernel can run programs built against this library.
