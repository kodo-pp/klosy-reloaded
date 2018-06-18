#ifndef KERNEL_VGATTY_H
#define KERNEL_VGATTY_H

#include <stddef.h>
#include <stdint.h>

/*
 * DEFINITIONS
 *
 * 1. default-colored char/byte - char/byte which has color defined by variable vga_color
 * (see kernel/vgatty/vgatty.c)
 *
 * 2. colored char/byte - char/byte which has color defined by function/macro argument
 */


/* DEFINES */

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

/* Creates a colored uint16_t to output in VGATTY */
#define VGAFCHAR(c, f) ((c) | ((f) << 8))
/* Creates a light-grey-on-black-colored uint16_t to output in VGATTY */
#define VGANFCHAR(c) ((c) | 0x0700)
/* Returns character from colored uint16_t */
#define VGACHR(c) ((c) & 0xFF)
/* Returns color from colored uint16_t */
#define VGAFMT(c) (((c) & 0xFF00) >> 8)

/* Checks whether row is in [0; VGA_HEIGHT) */
#define VGA_ROW_OK(row) (((row) >= 0) && ((row) < VGA_HEIGHT))
/* Checks whether col is in [0; VGA_WIDTH) */
#define VGA_COL_OK(col) (((col) >= 0) && ((col) < VGA_WIDTH))
/* Transforms (row, col) position into one-dimensional index */
#define VGA_POSITION(row, col) ((row) * VGA_WIDTH + (col))
/* Extracts row from one-dimensional index */
#define VGA_ROW(pos) ((pos) / VGA_WIDTH)
/* Extracts col from one-dimensional index */
#define VGA_COL(pos) ((pos) % VGA_WIDTH)

/* FUNCTIONS */

/** Clears the terminal, sets position to (0, 0) */
void vgatty_clear(void);
/** Clears the terminal, sets position to (0, 0) and color to 0x07, enables cursor */
void vgatty_reset(void);

/** Puts raw default-colored byte in the terminal, w/o any checks on '\n' or similar stuff. */
void vgatty_putbyte(char ch);
/** Puts default-colored char in the terminal, checking if it is a special char (e.g. '\n') */
void vgatty_putchar(char ch);
/** Puts default-colored zero-terminated string in the terminal */
void vgatty_putstr(const char *str);
/** Puts default-colored array of raw bytes with arbitary length in the terminal */
void vgatty_putdata(const char *str, size_t len);

/** Puts raw colored byte in the terminal, w/o any checks on '\n' or similar stuff. */
void vgatty_putfbyte(uint16_t ch);
/** Puts colored char in the terminal, checking if it is a special char (e.g. '\n') */
void vgatty_putfchar(uint16_t ch);
/** Puts colored zero-terminated string in the terminal */
void vgatty_putfstr(const uint16_t *str);
/** Puts colored array of raw bytes with arbitary length in the terminal */
void vgatty_putfdata(const uint16_t *str, size_t len);

/** Sets default color */
void vgatty_setcolor(uint8_t color);
/** Sets cursor and output position */
void vgatty_setposition(int row, int col);
/** Enables (cursor=1) or disables (cursor=0) blinking cursor */
void vgatty_setcursor(int cursor);

/** Returns cursor state (1 - enabled, 0 - disabled) */
int  vgatty_getcursor(void);
/** Reports current cursor and output position */
void vgatty_getposition(int *row, int *col);

#endif /* end of include guard: KERNEL_VGATTY_H */
