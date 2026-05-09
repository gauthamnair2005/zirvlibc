#ifndef ZIRVLIBC_DATETIME_H
#define ZIRVLIBC_DATETIME_H

#include <stdint.h>

struct datetime {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

int getdatetime(struct datetime *dt);
int setdatetime(const struct datetime *dt);
int gettz(void);
int settz(int minutes);

#endif
