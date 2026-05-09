#include <datetime.h>
#include <zirv/syscall.h>

extern long _syscall0(long n);
extern long _syscall1(long n, long a1);

int getdatetime(struct datetime *dt)
{
    return (int)_syscall1(SYS_GETDATETIME, (long)dt);
}

int setdatetime(const struct datetime *dt)
{
    return (int)_syscall1(SYS_SETDATETIME, (long)dt);
}

int gettz(void)
{
    return (int)_syscall0(SYS_GETTZ);
}

int settz(int minutes)
{
    return (int)_syscall1(SYS_SETTZ, minutes);
}
