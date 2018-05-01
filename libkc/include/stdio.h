#ifndef LIBKC_STDIO_H
#define LIBKC_STDIO_H

#include <stdint.h>
#include <stddef.h>
#include <kernel/tty.h>

/** printf function. [NOT IMPLEMENTED] */
size_t printf(const char *fmt, ...);

/** puts function */
size_t puts(const char *str);

/** puts function which does not append a newline */
size_t writes(const char *str);

#endif /* end of include guard: LIBKC_STDIO_H */
