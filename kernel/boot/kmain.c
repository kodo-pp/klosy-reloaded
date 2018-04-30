#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include <kernel/power.h>
#include <kernel/vgatty.h>
#include <kernel/portio.h>
#include <kernel/multiboot.h>

extern uint8_t vga_color;

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

extern size_t heap_memory;

void kmain(struct multiboot_info *mbt)
{
    /*
    char *str = "01234567890123456789012345678901234567890123456789\n";
    for (int i = 0; i < 24; ++i) {
        vgatty_putstr(str + i);
    }
    */

    /* uint32_t axcx = 0, bxdx = 0; */
    /* detect_memory(&axcx, &bxdx); */

    char buf[256];

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
    vgatty_putstr(" MiB\n");


    /*
    to_string(axcx, buf);
    vgatty_putstr("eax = ecx = ");
    vgatty_putstr(buf);
    vgatty_putstr("\n");

    to_string(bxdx, buf);
    vgatty_putstr("ebx = edx = ");
    vgatty_putstr(buf);
    vgatty_putstr("\n");
    */

    halt();
}
