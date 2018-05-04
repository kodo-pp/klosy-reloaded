#ifndef LIBKC_STDIO_H
#define LIBKC_STDIO_H

#include <stdint.h>
#include <stddef.h>
#include <kernel/tty.h>

/**
 * printf function. Not fully compatible with standard printf function
 * Formats:
 * %% - A '%' character
 * %d - signed int
 * %u - unsigned int
 * %z - size_t (unsigned int on x86, unsigned long long on x86_64 (but KR does not support x86_64))
 * %D - signed long long
 * %U - unsigned long long
 * %f - float (not implemented)
 * %F - double (not implemented)
 * %P - long double (not implemented)
 * %x - unsigned int, hex output
 * %X - unsigned long long, hex output
 * %p - size_t or void *, hex output
 * %o - unsigned int, octal output
 * %O - unsigned long long, octal output
 * %s - c-style string (char *)
 */
size_t printf(const char *fmt, ...);

/** puts function */
size_t puts(const char *str);

/** puts function which does not append a newline */
size_t writes(const char *str);

#endif /* end of include guard: LIBKC_STDIO_H */
