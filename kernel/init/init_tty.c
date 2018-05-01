#include <stdint.h>
#include <stddef.h>

#include <kernel/vgatty.h>
#include <kernel/init.h>

int init_tty(void)
{
    vgatty_reset();
    return 0;
}
