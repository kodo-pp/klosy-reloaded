#include <stdint.h>
#include <stddef.h>
#include <kernel/tty.h>
#include <kernel/vgatty.h>

size_t read(char* buf, size_t length)
{
    return tty_read(get_kernel_tty(), buf, length);
}
