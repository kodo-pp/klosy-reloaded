#ifndef KERNEL_VESA_TTY_HPP
#define KERNEL_VESA_TTY_HPP

#include <stdint.h>
#include <stddef.h>
#include <kernel/vesa.hpp>
#include <kernel/multiboot.h>

void vesa_tty_init(struct multiboot_info* mbt);

void vesa_tty_clear(void);
void vesa_tty_reset(void);

void vesa_tty_putchar(char ch);

void vesa_tty_setfgcolor(uint32_t color);
void vesa_tty_setposition(size_t row, size_t col);

// UNIMPLEMENTED
void vesa_tty_setcursor(int cursor);
// UNIMPLEMENTED
int  vesa_tty_getcursor(void);

size_t vesa_tty_write(const char* data, size_t length);
// STUB
size_t vesa_tty_read(char* data, size_t length);

#endif // end of include guard: KERNEL_VESA_TTY_HPP

