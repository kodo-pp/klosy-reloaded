#include <stdint.h>
#include <stddef.h>
#include <convert.h>

static const char *base_lookup_table = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

#define NUM_TO_STR(buf, n, idx, base) \
    do { \
        buf[idx] = '0'; \
        while (n != 0) { \
            buf[idx] = base_lookup_table[n % base]; \
            ++idx; \
            n /= base; \
        } \
        buf[idx] = '\0'; \
        for (size_t i = 0; i < (idx - beg) / 2; ++i) { \
            char tmp = buf[beg+i]; \
            buf[beg+i] = buf[idx-i-1]; \
            buf[idx-i-1] = tmp; \
        } \
    } while (0)

char *int_to_str       (char *buf, int n)                { return int_to_str_base       (buf, n, 10); }
char *uint_to_str      (char *buf, unsigned int n)       { return uint_to_str_base      (buf, n, 10); }
char *longlong_to_str  (char *buf, long long n)          { return longlong_to_str_base  (buf, n, 10); }
char *ulonglong_to_str (char *buf, unsigned long long n) { return ulonglong_to_str_base (buf, n, 10); }

char *int_to_str_base(char *buf, int n, int base)
{
    if (base <= 1 || base > 36) {
        return NULL;
    }

    size_t idx = 0;
    size_t beg = 0;
    if (n < 0) {
        buf[idx] = '-';
        ++idx;
        ++beg;
        /* Here is some hack */
        char t = base_lookup_table[(n % base + base) % base];
        buf[idx] = t;
        ++idx;
        n /= base;
        n = ~n + 1;

    }
    NUM_TO_STR(buf, n, idx, base);
    return buf;
}

char *uint_to_str_base(char *buf, unsigned int n, int base)
{
    if (base <= 1 || base > 36) {
        return NULL;
    }

    size_t idx = 0;
    size_t beg = 0;
    NUM_TO_STR(buf, n, idx, base);
    return buf;
}

char *longlong_to_str_base(char *buf, long long n, int base)
{
    if (base <= 1 || base > 36) {
        return NULL;
    }

    size_t idx = 0;
    size_t beg = 0;
    if (n < 0) {
        buf[idx] = '-';
        ++idx;
        ++beg;
        n &= 0x7FFFFFFFFFFFFFFFLL;
    }
    NUM_TO_STR(buf, n, idx, base);
    return buf;
}

char *ulonglong_to_str_base(char *buf, unsigned long long n, int base)
{
    if (base <= 1 || base > 36) {
        return NULL;
    }

    size_t idx = 0;
    size_t beg = 0;
    NUM_TO_STR(buf, n, idx, base);
    return buf;
}
