#include <stdint.h>
#include <stddef.h>
#include <convert.h>
#include <string.h>

static const char *base_lookup_table = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

#define NUM_TO_STR(buf, n, idx, base) \
    do { \
        size_t beg = idx; \
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

char *uint_to_str      (char *buf, unsigned int n)       { return uint_to_str_base      (buf, n, 10); }
char *ulonglong_to_str (char *buf, unsigned long long n) { return ulonglong_to_str_base (buf, n, 10); }

char *int_to_str(char *buf, int n)
{
    size_t idx = 0;
    if (n < 0) {
        if (n == (signed int)0x80000000) {
            strcpy(buf, "-2147483648");
            return buf;
        }
        buf[idx] = '-';
        ++idx;
        n = ~n + 1;
    }
    NUM_TO_STR(buf, n, idx, 10);
    return buf;
}

char *uint_to_str_base(char *buf, unsigned int n, int base)
{
    if (base <= 1 || base > 36) {
        return NULL;
    }

    size_t idx = 0;
    NUM_TO_STR(buf, n, idx, base);
    return buf;
}

char *longlong_to_str(char *buf, long long n)
{
    size_t idx = 0;
    if (n < 0) {
        if (n == (signed long long)0x8000000000000000) {
            strcpy(buf, "-9223372036854775808");
            return buf;
        }
        buf[idx] = '-';
        ++idx;
        n = ~n + 1;
    }
    NUM_TO_STR(buf, n, idx, 10);
    return buf;
}

char *ulonglong_to_str_base(char *buf, unsigned long long n, int base)
{
    if (base <= 1 || base > 36) {
        return NULL;
    }

    size_t idx = 0;
    NUM_TO_STR(buf, n, idx, base);
    return buf;
}
