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

#include <vector.hpp>

/**
 * Entry point to high-level part of kernel
 */
extern "C" void kmain(struct multiboot_info* mbt)
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

    printf("Heap memory begins at %z (approx. %z KiB)\n", (size_t)(&heap_memory),
           (size_t)(&heap_memory) >> 10);
    puts("");

    init_kmem(mbt->mem_upper * 1024 + 1024 * 1024);
    puts("Memory initialized");

    printf("This is a \x1b*52test\x1b*07!!!\n");

    void* ptr = kmalloc(1100);
    printf("1: ptr = %z\n", ptr);
    kmem_dump_uf(0, 20);

    ptr = krealloc(ptr, 500);
    printf("2: ptr = %z\n", ptr);
    kmem_dump_uf(0, 20);

    ptr = krealloc(ptr, 1500);
    printf("3: ptr = %z\n", ptr);
    kmem_dump_uf(0, 20);

    void* other_ptr = kmalloc(300);
    printf("4: other_ptr = %z\n", other_ptr);
    kmem_dump_uf(0, 20);

    ptr = krealloc(ptr, 2000);
    printf("5: ptr = %z\n", ptr);
    kmem_dump_uf(0, 20);

    kfree(ptr);
    printf("6: ptr freed\n");
    kmem_dump_uf(0, 20);

    kfree(other_ptr);
    printf("7: other_ptr freed\n");
    kmem_dump_uf(0, 20);

    kstd::vector <int> vec(500, 33);
    vec.push_back(42);
    printf("vec.at(499) = %d\n", vec.at(499));
    printf("vec.at(500) = %d\n", vec.at(500));
    vec.at(500) = 145;
    printf("vec.at(500) = %d\n", vec.at(500));


    puts("System initialized, awaiting for user input");
    while (true) {
        idle();
    }
}
