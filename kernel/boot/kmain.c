#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

volatile uint16_t *VGA_CHAR_BUF = 0xB8000;
size_t VGA_WIDTH = 80;
size_t VGA_HEIGTH = 25;

void put_char(size_t position, uint16_t chr)
{
    *(VGA_CHAR_BUF + position) = chr;
}

void put_string(size_t position, uint16_t *str, size_t count)
{
    for (size_t i = 0; i < count; ++i) {
        put_char(position + i, str[i]);
    }
}

uint16_t make_char(char chr)
{
    uint16_t res = chr | (0x07 << 8);
    return res;
}

__attribute__((noreturn))
void halt(); /* Implemented in power/halt.s */

void kmain()
{
    uint16_t fstr[12];
    char str[12] = "Hello world!";
    for (int i = 0; i < 12; ++i) {
        fstr[i] = make_char(str[i]);
    }

    put_string(0, fstr, 12);

    halt();
}
