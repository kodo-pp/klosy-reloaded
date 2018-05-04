#ifndef LIBKC_CONVERT_H
#define LIBKC_CONVERT_H

#include <stdint.h>
#include <stddef.h>

/* TODO: too lazy to write comments. But I guess these are quite obvious */

int str_to_int(const char *s);
unsigned int str_to_uint(const char *s);
long long str_to_longlong(const char *s);
unsigned long long str_to_ulonglong(const char *s);

unsigned int str_to_uint_base(const char *s, int base);
unsigned long long str_to_ulonglong_base(const char *s, int base);

char *int_to_str(char *buf, int n);
char *uint_to_str(char *buf, unsigned int n);
char *longlong_to_str(char *buf, long long n);
char *ulonglong_to_str(char *buf, unsigned long long n);

char *uint_to_str_base(char *buf, unsigned int n, int base);
char *ulonglong_to_str_base(char *buf, unsigned long long n, int base);

/* Alias for size_t */

#ifdef __i386__
    #define str_to_size_t      str_to_uint
    #define size_t_to_str      uint_to_str
    #define str_to_size_t_base str_to_uint_base
    #define size_t_to_str_base uint_to_str_base
#else
    #define str_to_size_t      str_to_ulonglong
    #define size_t_to_str      ulonglong_to_str
    #define str_to_size_t_base str_to_ulonglong_base
    #define size_t_to_str_base ulonglong_to_str_base
#endif /* sizeof(size_t) == sizeof(unsigned int) */

#endif /* end of include guard: LIBKC_CONVERT_H */
