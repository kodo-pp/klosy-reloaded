#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include <kernel/power.h>
#include <kernel/vgatty.h>
#include <kernel/portio.h>
#include <kernel/multiboot.h>
#include <kernel/memory.h>

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
    /* Print available memory size */
    char buf[256];

    /* I know, at the moment printing is VERY ugly, but it will be changed to
     * a couple of generic functions like write or printf, instead of working
     * directly with a tty
     */
    vgatty_setcolor(0x0F);
    vgatty_putstr("Memory information provided? ");
    vgatty_setcolor(0x07);
    if (mbt->flags & 1) {
        vgatty_setcolor(0x02);
        vgatty_putstr("yes\n");
        vgatty_setcolor(0x07);
    } else {
        vgatty_setcolor(0x04);
        vgatty_putstr("no\n");
        vgatty_setcolor(0x07);
        vgatty_putstr("Halting...\n");
        halt();
    }

    to_string(mbt->mem_lower, buf);
    vgatty_setcolor(0x0F);
    vgatty_putstr("Lower memory: ");
    vgatty_setcolor(0x07);
    vgatty_putstr(buf);
    vgatty_putstr(" KiB\n");

    to_string(mbt->mem_upper >> 10, buf);
    vgatty_setcolor(0x0F);
    vgatty_putstr("Upper memory: ");
    vgatty_setcolor(0x07);
    vgatty_putstr(buf);
    vgatty_putstr(" MiB\n");

    to_string((mbt->mem_upper >> 10) + 1, buf);
    vgatty_setcolor(0x0F);
    vgatty_putstr("Memory limit: ");
    vgatty_setcolor(0x07);
    vgatty_putstr(buf);
    vgatty_putstr(" MiB\n\n");

    vgatty_putstr("Heap memory begins at ");
    to_string((size_t)heap_memory, buf);
    vgatty_putstr(buf);
    vgatty_putstr("\n");

    init_kmem(mbt->mem_upper * 1024 + 1024 * 1024);
    vgatty_putstr("Memory initialized\n");
    void *allocated1 = kmalloc(10);
    vgatty_putstr("Memory[1] allocated\n");
    vgatty_putstr("Pointer value is ");
    to_string((size_t)allocated1, buf);
    vgatty_putstr(buf);
    vgatty_putstr("\n");

    void *allocated2 = kmalloc(300);
    vgatty_putstr("Memory[2] allocated\n");
    vgatty_putstr("Pointer value is ");
    to_string((size_t)allocated2, buf);
    vgatty_putstr(buf);
    vgatty_putstr("\n");

    void *allocated3 = kmalloc(10);
    vgatty_putstr("Memory[3] allocated\n");
    vgatty_putstr("Pointer value is ");
    to_string((size_t)allocated3, buf);
    vgatty_putstr(buf);
    vgatty_putstr("\n");

    int val = kfree(allocated2) + 100;
    vgatty_putstr("Memory[2] freed\n");
    vgatty_putstr("Return value + 100 is ");
    to_string((size_t)val, buf);
    vgatty_putstr(buf);
    vgatty_putstr("\n");

    val = kfree(allocated2) + 100;
    vgatty_putstr("Memory[2] freed again\n");
    vgatty_putstr("Return value + 100 is ");
    to_string((size_t)val, buf);
    vgatty_putstr(buf);
    vgatty_putstr("\n");

    val = kfree(NULL) + 100;
    vgatty_putstr("NULL freed\n");
    vgatty_putstr("Return value + 100 is ");
    to_string((size_t)val, buf);
    vgatty_putstr(buf);
    vgatty_putstr("\n");

    for (size_t i = 0; i < 16; ++i) {
        if (is_block_free(i)) {
            vgatty_putstr("F"); /* Free */
        } else {
            vgatty_putstr("U"); /* Used */
        }
    }
    vgatty_putstr(" | ");

    void *allocated4 = kmalloc(200);
    vgatty_putstr("Memory[4] allocated\n");
    vgatty_putstr("Pointer value is ");
    to_string((size_t)allocated4, buf);
    vgatty_putstr(buf);
    vgatty_putstr("\n");

    for (size_t i = 0; i < 16; ++i) {
        if (is_block_free(i)) {
            vgatty_putstr("F"); /* Free */
        } else {
            vgatty_putstr("U"); /* Used */
        }
    }
    vgatty_putstr(" | ");

    void *allocated5 = kmalloc(300);
    vgatty_putstr("Memory[5] allocated\n");
    vgatty_putstr("Pointer value is ");
    to_string((size_t)allocated5, buf);
    vgatty_putstr(buf);
    vgatty_putstr("\n");


    for (size_t i = 0; i < 16; ++i) {
        if (is_block_free(i)) {
            vgatty_putstr("F"); /* Free */
        } else {
            vgatty_putstr("U"); /* Used */
        }
    }
    vgatty_putstr(" | ");

    vgatty_putstr("Halted.\n");
    /* OK, we're done and system can be halted */
    halt();
}
