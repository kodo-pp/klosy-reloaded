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
 * Entry point to high-level part of kernel (C is considered a high-level prog. language)
 */
void kmain(struct multiboot_info *mbt)
{
    init_modules(mbt);

    /* Print available memory size */

    /* I know, at the moment printing is VERY ugly, but it will be changed to
     * a couple of generic functions like write or printf, instead of working
     * directly with a tty
     *
     * TIME TO REFACTOR!!1!
     */
    printf("%sMemory information provided?%s ", "\x1b*0F", "\x1b*07");
    if (mbt->flags & 1) {
        printf("%syes%s\n", "\x1b*02", "\x1b*07");
    } else {
        printf("%sno%s\n", "\x1b*04", "\x1b*07");
        puts("Halting...");
        halt();
    }

    printf("%sLower memory:%s %z KiB\n", "\x1b*0F", "\x1b*07", (size_t)mbt->mem_lower);
    printf("%sUpper memory:%s %z MiB\n", "\x1b*0F", "\x1b*07", mbt->mem_upper >> 10);
    printf("%sMemory limit:%s %z MiB\n", "\x1b*0F", "\x1b*07", (mbt->mem_upper >> 10) + 1);
    puts("");

    printf("Heap memory begins at %z (approx. %z KiB)\n", (size_t)(&heap_memory), (size_t)(&heap_memory) >> 10);
    puts("");

    init_kmem(mbt->mem_upper * 1024 + 1024 * 1024);
    puts("Memory initialized");

    printf("This is a \x1b*52test\x1b*07!!!\n");

    puts("System initialized, awaiting for user input");
    while (1) {
        idle();
    }
}
