#include <stddef.h>
#include <stdint.h>
#include <zirv/syscall.h>

extern long _syscall1(long n, long a1);
extern long _syscall2(long n, long a1, long a2);
void *sbrk(intptr_t increment);

void exit(int status) {
    _syscall1(SYS_EXIT, status);
    for (;;) ;
}

void abort(void) {
    _syscall1(SYS_EXIT, 1);
    for (;;) ;
}

int atoi(const char *s) {
    int n = 0, sign = 1;
    while (*s == ' ' || *s == '\t' || *s == '\n') s++;
    if (*s == '-') { sign = -1; s++; }
    else if (*s == '+') s++;
    while (*s >= '0' && *s <= '9') n = n * 10 + (*s++ - '0');
    return sign * n;
}

long atol(const char *s) {
    long n = 0;
    int sign = 1;
    while (*s == ' ' || *s == '\t' || *s == '\n') s++;
    if (*s == '-') { sign = -1; s++; }
    else if (*s == '+') s++;
    while (*s >= '0' && *s <= '9') n = n * 10 + (*s++ - '0');
    return sign * n;
}

/* ── Heap allocator (free-list on brk) ──────────────────────────────── */
typedef struct block {
    size_t       size;
    struct block *next;
} block_t;

#define BLOCK_HDR  sizeof(block_t)   /* 16 bytes on x64 */
#define MIN_BLOCK  32
#define ALIGN      16

static block_t *g_free;              /* free-list head (NULL = need init) */
static int      g_heap_inited;

/* Round n up to the nearest multiple of ALIGN */
static inline size_t align_up(size_t n) {
    return (n + ALIGN - 1) & ~(size_t)(ALIGN - 1);
}

void *malloc(size_t size) {
    if (!size) size = 1;
    size = align_up(size);
    if (size < MIN_BLOCK - BLOCK_HDR) size = MIN_BLOCK - BLOCK_HDR;

    /* First-time init: request one page from the kernel */
    if (!g_heap_inited) {
        g_free = (block_t *)sbrk(4096);
        if (g_free == (void *)-1) return NULL;
        g_free->size = 4096 - BLOCK_HDR;
        g_free->next = NULL;
        g_heap_inited = 1;
    }

    block_t **pp = &g_free;
    while (*pp) {
        block_t *b = *pp;
        if (b->size >= size) {
            /* Split if remainder is large enough for a free block */
            size_t remain = b->size - size;
            if (remain >= MIN_BLOCK) {
                block_t *newb = (block_t *)((uint8_t *)(b + 1) + size);
                newb->size = remain - BLOCK_HDR;
                newb->next = b->next;
                b->size = size;
                b->next = NULL;
                *pp = newb;
            } else {
                *pp = b->next;
            }
            return (void *)(b + 1);
        }
        pp = &b->next;
    }

    /* No suitable free block — extend the heap */
    size_t req = align_up(size + BLOCK_HDR);
    if (req < 4096) req = 4096;
    block_t *b = (block_t *)sbrk((intptr_t)req);
    if (b == (void *)-1) return NULL;
    b->size = req - BLOCK_HDR;
    b->next = g_free;
    g_free  = b;

    /* Try again (will succeed since we just added a block) */
    pp = &g_free;
    b = *pp;
    size_t remain = b->size - size;
    if (remain >= MIN_BLOCK) {
        block_t *newb = (block_t *)((uint8_t *)(b + 1) + size);
        newb->size = remain - BLOCK_HDR;
        newb->next = b->next;
        b->size = size;
        b->next = NULL;
        *pp = newb;
    } else {
        *pp = b->next;
    }
    return (void *)(b + 1);
}

void free(void *ptr) {
    if (!ptr) return;

    block_t *b = (block_t *)((uint8_t *)ptr - BLOCK_HDR);
    size_t   sz = b->size;

    /* Simple coalesce with adjacent blocks:
     * The block right after us (if any) that is free. */
    block_t *after = (block_t *)((uint8_t *)(b + 1) + sz);
    block_t **pp = &g_free;
    block_t *prev = NULL;
    while (*pp) {
        if (*pp == after) {
            /* Coalesce with next free block */
            sz += BLOCK_HDR + (*pp)->size;
            *pp = (*pp)->next;
            break;
        }
        if (*pp < b) prev = *pp;
        pp = &(*pp)->next;
    }

    b->size = sz;
    /* Insert back into free list in address order for easy coalescing */
    if (prev) {
        b->next = prev->next;
        prev->next = b;
    } else {
        b->next = g_free;
        g_free  = b;
    }
}

void *calloc(size_t nmemb, size_t size) {
    size_t total = nmemb * size;
    void *p = malloc(total);
    if (p) {
        uint8_t *b = (uint8_t *)p;
        for (size_t i = 0; i < total; i++) b[i] = 0;
    }
    return p;
}

void *realloc(void *ptr, size_t size) {
    if (!ptr) return malloc(size);
    if (!size) { free(ptr); return NULL; }
    block_t *b = (block_t *)((uint8_t *)ptr - BLOCK_HDR);
    size_t old = b->size;
    if (old >= size) return ptr;
    void *newp = malloc(size);
    if (!newp) return NULL;
    for (size_t i = 0; i < old; i++)
        ((uint8_t *)newp)[i] = ((uint8_t *)ptr)[i];
    free(ptr);
    return newp;
}
