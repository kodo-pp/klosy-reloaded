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

/*
 * Temporary utility function, should be removed when something like printf is implemented.
 * Converts a size_t to string, w/o any checks, so it's definitely unsafe and should
 * be replaced.
 */
void to_string(size_t n, char *s)
{
    size_t idx = 0;
    while (n) {
        s[idx] = '0' + n % 10;
        n /= 10;
        ++idx;
    }
    for (size_t i = 0; i < idx/2; ++i) {
        char t = s[i];
        s[i] = s[idx-i-1];
        s[idx-i-1] = t;
    }
    s[idx] = 0;
}

/**
 * Entry point to high-level part of kernel (C is considered a high-level prog. language)
 */
void kmain(struct multiboot_info *mbt)
{
    char buf[256];

    init_modules(mbt);

    /* Print available memory size */

    /* I know, at the moment printing is VERY ugly, but it will be changed to
     * a couple of generic functions like write or printf, instead of working
     * directly with a tty
     */
    vgatty_setcolor(0x0F);
    writes("Memory information provided? ");
    vgatty_setcolor(0x07);
    if (mbt->flags & 1) {
        vgatty_setcolor(0x02);
        puts("yes");
        vgatty_setcolor(0x07);
    } else {
        vgatty_setcolor(0x04);
        puts("no");
        vgatty_setcolor(0x07);
        puts("Halting...");
        halt();
    }

    vgatty_setcolor(0x0F);
    writes("Lower memory: ");
    vgatty_setcolor(0x07);
    writes(size_t_to_str(buf, (size_t)mbt->mem_lower));
    puts(" KiB");

    to_string(mbt->mem_upper >> 10, buf);
    vgatty_setcolor(0x0F);
    writes("Upper memory: ");
    vgatty_setcolor(0x07);
    writes(buf);
    puts(" MiB");

    to_string((mbt->mem_upper >> 10) + 1, buf);
    vgatty_setcolor(0x0F);
    writes("Memory limit: ");
    vgatty_setcolor(0x07);
    writes(buf);
    puts(" MiB");
    puts("");

    writes("Heap memory begins at ");
    to_string((size_t)(&heap_memory), buf);
    writes(buf);
    puts("");

    init_kmem(mbt->mem_upper * 1024 + 1024 * 1024);
    puts("Memory initialized");

    printf("This is a \x1b*52test\x1b*07!!!\n");

    puts("System initialized, awaiting for user input");
    while (1) {
        idle();
    }
}
