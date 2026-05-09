#ifndef ZIRVLIBC_DIRENT_H
#define ZIRVLIBC_DIRENT_H

#include <stdint.h>

struct dirent {
    uint64_t d_ino;
    char     d_name[256];
};

int getdents(int fd, struct dirent *ents, int count);

#endif
