#include <datetime.h>
#include <zirv/syscall.h>

extern long _syscall1(long n, long a1);
extern long _syscall2(long n, long a1, long a2);

int getdatetime(struct datetime *dt)
{
    return (int)_syscall1(SYS_GETDATETIME, (long)dt);
}

int setdatetime(const struct datetime *dt)
{
    return (int)_syscall1(SYS_SETDATETIME, (long)dt);
}
