#ifndef KERNEL_TTY_H
#define KERNEL_TTY_H

#include <stdint.h>
#include <stddef.h>

/** Write certain amount of data to the terminal. Stub. */
size_t write(const char *data, size_t length);

/** Reads certain amount of data from the terminal. [NOT IMPLEMENTED] */
size_t read(char *buf, size_t length);

#endif /* end of include guard: KERNEL_TTY_H */
