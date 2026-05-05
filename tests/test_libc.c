#include <assert.h>
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static void test_string_api(void) {
    char a[32];
    char b[32];
    char c[32];

    strcpy(a, "zirv");
    assert(strcmp(a, "zirv") == 0);
    assert(strlen(a) == 4);
    assert(strnlen("kernel", 3) == 3);
    assert(strnlen("kernel", 16) == 6);

    strncpy(b, "abc", sizeof(b));
    assert(strcmp(b, "abc") == 0);
    assert(strncmp("abc", "abd", 2) == 0);
    assert(strncmp("abc", "abd", 3) < 0);

    memset(c, 0, sizeof(c));
    memcpy(c, "memory", 7);
    assert(memcmp(c, "memory", 7) == 0);

    memcpy(c, "123456789", 10);
    memmove(c + 2, c, 5);
    assert(memcmp(c, "121234589", 9) == 0);

    assert(strchr("abc", 'b') != NULL);
    assert(strrchr("abcb", 'b') != NULL);
    assert(strstr("zirvium", "vium") != NULL);
    assert(strstr("zirvium", "none") == NULL);
}

static void test_ctype_api(void) {
    assert(isspace(' '));
    assert(isspace('\n'));
    assert(isdigit('9'));
    assert(!isdigit('a'));
    assert(isalpha('Z'));
    assert(isalpha('m'));
    assert(isalnum('7'));
    assert(isalnum('x'));
    assert(toupper('a') == 'A');
    assert(tolower('B') == 'b');
}

static void test_stdio_api(void) {
    char buf[128];
    int ret;

    ret = snprintf(buf, sizeof(buf), "%s %d %u %x %c %%", "zirv", -42, 42u, 0x2au, '!');
    assert(ret > 0);
    assert(strcmp(buf, "zirv -42 42 2a ! %") == 0);

    int (*zirv_snprintf)(char *, size_t, const char *, ...) = snprintf;
    ret = zirv_snprintf(buf, 6, "abcdefg");
    assert(ret == 7);
    assert(strcmp(buf, "abcde") == 0);

    ret = snprintf(buf, sizeof(buf), "%p", (void *)(uintptr_t)0x1234);
    assert(ret >= 3);
    assert(strstr(buf, "0x") == buf);
}

int main(void) {
    test_string_api();
    test_ctype_api();
    test_stdio_api();
    return 0;
}
