#include <stdint.h>
#include <stddef.h>
#include <kernel/tty.h>
#include <kernel/memory.h>
#include <kernel/power.h>
#include <kcdefines.h>
#include <memops.h>

struct tty terminals[MAX_TTYS];
static int ttys_count = 0;

int kernel_tty = -1;

void set_kernel_tty(int ttyno)
{
    kernel_assert(0 <= ttyno && ttyno < ttys_count && ttys_count <= MAX_TTYS);
    kernel_tty = ttyno;
}

int get_kernel_tty(void)
{
    kernel_assert(0 <= kernel_tty && kernel_tty < ttys_count && ttys_count <= MAX_TTYS);
    return kernel_tty;
}

int has_kernel_tty(void)
{
    return 0 <= kernel_tty && kernel_tty < ttys_count && ttys_count <= MAX_TTYS;
}

size_t tty_write(int ttyno, const char* data, size_t length)
{
    kernel_assert(0 <= ttyno && ttyno < ttys_count && ttys_count <= MAX_TTYS);
    kernel_assert(terminals[ttyno].write_func != NULL);
    return terminals[ttyno].write_func(data, length);
}

size_t tty_read(int ttyno, char* buf, size_t length)
{
    kernel_assert(0 <= ttyno && ttyno < ttys_count && ttys_count <= MAX_TTYS);
    kernel_assert(terminals[ttyno].read_func != NULL);
    return terminals[ttyno].read_func(buf, length);
}

int register_tty(const struct tty* tty_descriptor)
{
    kernel_assert(ttys_count <= MAX_TTYS);
    if (ttys_count == MAX_TTYS) {
        return -1;
    }

    int tty_idx = ttys_count;
    ++ttys_count;

    kernel_assert(!definitely_not_code((void*)(size_t)(tty_descriptor->write_func)));
    kernel_assert(!definitely_not_code((void*)(size_t)(tty_descriptor->read_func)));

    memcpy(terminals + tty_idx, tty_descriptor, sizeof(*tty_descriptor));
    return tty_idx;
}
