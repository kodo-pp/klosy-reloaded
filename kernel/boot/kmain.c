#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include <kernel/power.h>
#include <kernel/vgatty.h>
#include <kernel/portio.h>

extern uint8_t vga_color;

void kmain()
{
    vgatty_putstr("Hello world!\nHello from Klosy Reloaded!");
    halt();
}
