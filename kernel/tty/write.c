#include <stdint.h>
#include <stddef.h>
#include <kernel/tty.h>
#include <kernel/vgatty.h>

/* TODO: this is just a stub and should be rewritten */
size_t write(const char *data, size_t length)
{
    if (data == NULL) {
        return 0;
    }
    for (size_t i = 0; i < length; ++i) {
        vgatty_putchar(data[i]);
    }
    return length;
}
