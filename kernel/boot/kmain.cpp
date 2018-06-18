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

// This is a test
// It should output 'Foo(a=4, b=9)' before the kmain() function starts
class Foo {
public:
    Foo(int a, int b) {
        printf("Foo(a=%d, b=%d)\n", a, b);
    }
};
Foo foo(4, 9);

/**
 * Entry point to high-level part of kernel (C is considered a high-level prog. language)
 */
extern "C" void kmain(struct multiboot_info *mbt)
{
    /*init_modules(mbt);*/

    /* Print available memory size */
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
