#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include <kernel/power.h>
#include <kernel/vgatty.h>
#include <kernel/portio.h>

extern uint8_t vga_color;

void kmain()
{
    /*
    char *str = "123456789012345678901234567890\n";
    for (int i = 0; i < 27; ++i) {
        vgatty_setcolor(i);
        vgatty_putstr(str + (size_t)i);
    }
    */
    vgatty_putstr("Hello");
    vgatty_setposition(2, 5);
    vgatty_putstr("World!");
    halt();
}
