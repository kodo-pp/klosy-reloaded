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

    void *allocated1 = kmalloc(10);
    puts("Memory[1] allocated");
    writes("Pointer value is ");
    to_string((size_t)allocated1, buf);
    writes(buf);
    puts("");

    void *allocated2 = kmalloc(300);
    puts("Memory[2] allocated");
    writes("Pointer value is ");
    to_string((size_t)allocated2, buf);
    writes(buf);
    puts("");

    void *allocated3 = kmalloc(10);
    puts("Memory[3] allocated");
    writes("Pointer value is ");
    to_string((size_t)allocated3, buf);
    writes(buf);
    puts("");

    int val = kfree(allocated2) + 100;
    puts("Memory[2] freed");
    writes("Return value + 100 is ");
    to_string((size_t)val, buf);
    writes(buf);
    puts("");

    val = kfree(allocated2) + 100;
    puts("Memory[2] freed again");
    writes("Return value + 100 is ");
    to_string((size_t)val, buf);
    writes(buf);
    puts("");

    val = kfree(NULL) + 100;
    puts("NULL freed");
    writes("Return value + 100 is ");
    to_string((size_t)val, buf);
    writes(buf);
    puts("");

    for (size_t i = 0; i < 16; ++i) {
        if (is_block_free(i)) {
            writes("F"); /* Free */
        } else {
            writes("U"); /* Used */
        }
    }
    writes(" | ");

    void *allocated4 = kmalloc(200);
    puts("Memory[4] allocated");
    writes("Pointer value is ");
    to_string((size_t)allocated4, buf);
    writes(buf);
    puts("");

    for (size_t i = 0; i < 16; ++i) {
        if (is_block_free(i)) {
            writes("F"); /* Free */
        } else {
            writes("U"); /* Used */
        }
    }
    writes(" | ");

    void *allocated5 = kmalloc(300);
    puts("Memory[5] allocated");
    writes("Pointer value is ");
    to_string((size_t)allocated5, buf);
    writes(buf);
    puts("");


    for (size_t i = 0; i < 16; ++i) {
        if (is_block_free(i)) {
            writes("F"); /* Free */
        } else {
            writes("U"); /* Used */
        }
    }
    writes(" | ");

    puts(ulonglong_to_str_base(buf, 0x7FFFFFFFFFFFFFFFULL, 36));

    puts("Halted.");
    /* OK, we're done and system can be halted */
    halt();
}
