#include <stdint.h>
#include <stddef.h>
#include <kernel/tty.h>
#include <kernel/vgatty.h>

size_t write(const char* data, size_t length)
{
    return tty_write(get_kernel_tty(), data, length);
}
