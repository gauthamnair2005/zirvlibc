#ifndef ZIRVLIBC_UNISTD_H
#define ZIRVLIBC_UNISTD_H

#include <stddef.h>
#include <stdint.h>
#include <zirv/syscall.h>

/* ── Keyboard event ─────────────────────────────────────────────────────── */
typedef struct {
    uint16_t keycode;
    uint8_t  pressed;   /* 0 = released, 1 = pressed */
    uint8_t  mods;
} key_event_t;
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
void    msleep(uint64_t ms);
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

/* Resolve a target IP to a MAC address (handles routing through gateway).
 * Returns 0 on success, -1 on failure. */
int net_resolve(uint32_t target_ip, uint8_t *mac_out);

/* PCI: read device info by index.  Returns 0 on success, -1 at end. */
#include <stdint.h>
typedef struct {
    uint16_t vendor_id, device_id;
    uint16_t subsys_vendor, subsys_device;
    uint8_t  bus, dev, func;
    uint8_t  class_code, subclass, prog_if, revision;
    uint8_t  irq_line;
    uint8_t  _pad;
    uint64_t bar0_addr, bar0_size;
    uint64_t bar2_addr, bar2_size;
    char     driver_name[32];
} pci_dev_info_t;
int pci_read(uint32_t index, pci_dev_info_t *info);
int pipe(int fds[2]);
int dup2(int oldfd, int newfd);
int read_keys(key_event_t *ev);

int audio_play(const void *buf, unsigned int frames);
int audio_volume(unsigned char vol);

#define PROT_READ   0x1
#define PROT_WRITE  0x2
#define PROT_EXEC   0x4
#define PROT_NONE   0x0

#define MAP_PRIVATE     0x02
#define MAP_ANONYMOUS   0x20
#define MAP_FAILED      ((void *)-1)

/* ── ZirvFS snapshot operations ─────────────────────────────────────────--- */
int zirvfs_snap_create(unsigned int fs_index, const char *message, uint64_t *snap_id);
int zirvfs_snap_list(unsigned int fs_index, zirvfs_snapshot_info_t *snaps, uint32_t *count);
int zirvfs_snap_restore(unsigned int fs_index, uint64_t snap_id);

#endif
