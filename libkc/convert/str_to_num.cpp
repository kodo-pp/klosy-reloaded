#include <stdint.h>
#include <stddef.h>
#include <convert.h>
#include <string.h>
#include <stdio.h>

#define UNBASE(ch) \
    ( \
        ('0' <= (ch) && (ch) <= '9') \
            ? ((ch) - '0') \
            : ('a' <= (ch) && (ch) <= 'z') \
                ? ((ch) - 'a' + 10) \
                : ('A' <= (ch) && (ch) <= 'Z') \
                    ? ((ch) - 'A' + 10) \
                    : -1 \
    )

/* Uses operator comma */
#define BASE_FILTER(correct, val, base) \
    ((correct = correct && (val >= 0 && val < base)), val)

#define STR_TO_NUMBER(numvar, str, base) \
    do { \
        int correct = 1; \
        numvar = 0; \
        for (size_t i = 0; str[i] != '\0'; ++i) { \
            numvar = numvar * base + BASE_FILTER(correct, UNBASE(str[i]), base); \
        } \
        if (!correct) { \
            numvar = 0; \
        } \
    } while (0) \

unsigned int str_to_uint(const char* s)
{
    return str_to_uint_base(s, 10);
}
unsigned long long str_to_ulonglong(const char* s)
{
    return str_to_ulonglong_base(s, 10);
}

int str_to_int(const char* s)
{
    if (s == nullptr) {
        return 0;
    }

    int sign = 1;
    if (s[0] == '-') {
        sign = -1;
        ++s;
    }

    int num = 0;
    STR_TO_NUMBER(num, s, 10);
    return num * sign;
}

long long str_to_longlong(const char* s)
{
    if (s == nullptr) {
        return 0;
    }

    int sign = 1;
    if (s[0] == '-') {
        sign = -1;
        ++s;
    }

    long long num = 0;
    STR_TO_NUMBER(num, s, 10);
    return num * sign;
}

unsigned int str_to_uint_base(const char* s, int base)
{
    if (s == nullptr) {
        return 0;
    }

    unsigned int num = 0;
    STR_TO_NUMBER(num, s, base);
    return num;
}
unsigned long long str_to_ulonglong_base(const char* s, int base)
{
    if (s == nullptr) {
        return 0;
    }

    unsigned long long num = 0;
    STR_TO_NUMBER(num, s, base);
    return num;
}
