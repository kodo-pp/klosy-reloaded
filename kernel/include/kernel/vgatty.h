#ifndef KERNEL_VGATTY_H
#define KERNEL_VGATTY_H

#include <stddef.h>
#include <stdint.h>

/* DEFINES */

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define VGAFCHAR(c, f) ((c) | ((f) << 8))
#define VGANFCHAR(c) ((c) | 0x0700)
#define VGACHR(c) ((c) & 0xFF)
#define VGAFMT(c) (((c) & 0xFF00) >> 8)

#define VGA_ROW_OK(row) (((row) >= 0) && ((row) < VGA_HEIGHT))
#define VGA_COL_OK(col) (((col) >= 0) && ((col) < VGA_WIDTH))
#define VGA_POSITION(row, col) ((row) * VGA_WIDTH + (col))
#define VGA_ROW(pos) ((pos) / VGA_WIDTH)
#define VGA_COL(pos) ((pos) % VGA_WIDTH)

/* FUNCTIONS */

void vgatty_putbyte(char ch);
void vgatty_putchar(char ch);
void vgatty_putstr(char *str);
void vgatty_putdata(char *str, size_t len);

void vgatty_putfbyte(uint16_t ch);
void vgatty_putfchar(uint16_t ch);
void vgatty_putfstr(uint16_t *str);
void vgatty_putfdata(uint16_t *str, size_t len);

void vgatty_setcolor(uint8_t color);
void vgatty_setposition(int row, int col);
void vgatty_setcursor(int cursor);

int  vgatty_getcursor(void);
void vgatty_getposition(int *row, int *col);

#endif /* end of include guard: KERNEL_VGATTY_H */
