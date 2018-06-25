#ifndef KERNEL_VESA_TTY_HPP
#define KERNEL_VESA_TTY_HPP

#include <stdint.h>
#include <stddef.h>
#include <kernel/vesa.hpp>

void vesa_tty_init();

void vesa_tty_clear(void);
void vesa_tty_reset(void);

void vesa_tty_putchar(char ch);

void vesa_tty_setcolor(uint8_t red, uint8_t green, uint8_t blue);
void vesa_tty_setposition(int row, int col);

// UNIMPLEMENTED
void vesa_tty_setcursor(int cursor);
// UNIMPLEMENTED
int  vesa_tty_getcursor(void);

#endif /* end of include guard: KERNEL_VGATTY_H */

#endif // end of include guard: KERNEL_VESA_TTY_HPP

