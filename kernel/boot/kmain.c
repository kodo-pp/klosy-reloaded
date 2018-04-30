#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include <kernel/power.h>
#include <kernel/vgatty.h>
#include <kernel/portio.h>

extern uint8_t vga_color;

void kmain()
{
    char *str = "01234567890123456789012345678901234567890123456789\n";
    for (int i = 0; i < 24; ++i) {
        vgatty_putstr(str + i);
    }
    halt();
}
