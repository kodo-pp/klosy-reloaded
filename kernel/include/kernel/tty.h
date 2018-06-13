#ifndef KERNEL_TTY_H
#define KERNEL_TTY_H

#include <stdint.h>
#include <stddef.h>

/** Write certain amount of data to the terminal. Stub. */
size_t write(const char *data, size_t length);

/** Reads certain amount of data from the terminal. [NOT IMPLEMENTED] */
size_t read(char *buf, size_t length);

typedef size_t(*tty_write_t)(const char *, size_t);
typedef size_t(*tty_read_t)(char *, size_t);

struct tty {
    tty_write_t write_func;
    tty_read_t read_func;
};

size_t tty_write(int ttyno, const char *data, size_t length);
size_t tty_read(int ttyno, char *buf, size_t length);
int register_tty(const struct tty *tty_descriptor);

#define MAX_TTYS 256

void set_kernel_tty(int ttyno);
int get_kernel_tty(void);
int has_kernel_tty(void);

#endif /* end of include guard: KERNEL_TTY_H */
