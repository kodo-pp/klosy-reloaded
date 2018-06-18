#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include <stdio.h>
#include <convert.h>

#include <kernel/power.h>
#include <kernel/vgatty.h>
#include <kernel/portio.h>
#include <kernel/multiboot.h>
#include <kernel/init.h>
#include <kernel/memory.h>
#include <kernel/panic.h>

/**
 * Initialize crucial modules such as memory manager or terminal
 */
extern "C" void kernel_early_init(struct multiboot_info* mbt)
{
    init_modules(mbt);
}

