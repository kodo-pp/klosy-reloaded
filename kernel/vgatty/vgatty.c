#include <stddef.h>
#include <stdint.h>

#include <kernel/vgatty.h>
#include <kernel/portio.h>
#include <kcdefines.h>

/* CONSTANTS */

/* Constant pointer to non-constant volatile data */
static volatile uint16_t * const VGA_CHAR_BUF = (uint16_t * const)0xB8000;

/* STATE VARIABLES */

static int vga_position = 0;
static int vga_color = 0x07;
static int vgatty_cursor = -1;

/* CLEAR AND RESET FUNCTIONS */

void vgatty_clear(void)
{
    for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; ++i) {
        *(VGA_CHAR_BUF + i) = VGANFCHAR('\0');
    }
    vgatty_setposition(0, 0);
}

void vgatty_reset(void)
{
    vgatty_clear();
    vgatty_setcursor(1);
    vgatty_setcolor(0x07);
}

/* UTILITY FUNCTIONS: PARTIAL CLEANING */
static void vgatty_clear_range(size_t begin, size_t end)
{
    if (end > VGA_WIDTH * VGA_HEIGHT) {
        end = VGA_WIDTH * VGA_HEIGHT;
    }
    /* Always false */
    /*
    if (begin < 0) {
        begin = 0;
    }
    */
    if (begin >= end) {
        return;
    }

    for (size_t i = begin; i < end; ++i) {
        VGA_CHAR_BUF[i] = VGANFCHAR('\0');
    }
}

static void vgatty_clear_line(size_t line)
{
    if (!VGA_ROW_OK((int)line)) {
        return;
    }
    vgatty_clear_range(line * VGA_WIDTH, (line + 1) * VGA_WIDTH);
}

/* CURSOR MANIPULATION FUNCTIONS */

void vgatty_move_cursor(uint16_t pos)
{
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos & 0xFF00) >> 8));
}

static void vgatty_enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3E0) & 0xE0) | cursor_end);
}

static void vgatty_disable_cursor()
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

/* UTILITY FUNCTION: SCROLLING */

static void vgatty_scroll(void)
{
    for (size_t i = 0; i < VGA_WIDTH * (VGA_HEIGHT - 1); ++i) {
        VGA_CHAR_BUF[i] = VGA_CHAR_BUF[i + VGA_WIDTH];
    }
    vgatty_clear_line(VGA_HEIGHT - 1);
    vgatty_setposition(VGA_HEIGHT - 1, 0);
}

/* WRITING UNFORMATTED DATA TO VGATTY */

void vgatty_putbyte(char ch) { vgatty_putfbyte(VGAFCHAR(ch, vga_color)); }
void vgatty_putchar(char ch) { vgatty_putfchar(VGAFCHAR(ch, vga_color)); }
void vgatty_putstr(char *str)
{
    if (str == NULL) {
        return;
    }
    while (*str != '\0') {
        vgatty_putfchar(VGAFCHAR(*str, vga_color));
        ++str;
    }
}
void vgatty_putdata(char *str, size_t len)
{
    if (str == NULL) {
        return;
    }
    for (size_t i = 0; i < len; ++i) {
        vgatty_putfbyte(VGAFCHAR(str[i], vga_color));
    }
}

/* WRITING FORMATTED DATA TO VGATTY */

void vgatty_putfbyte(uint16_t ch)
{
    VGA_CHAR_BUF[vga_position] = ch;
    /* vga_position = (vga_position + 1) % (VGA_WIDTH * VGA_HEIGHT); */
    ++vga_position;
    if (vga_position >= VGA_WIDTH * VGA_HEIGHT) {
        vgatty_scroll();
    }
    vgatty_move_cursor(vga_position);
}
void vgatty_putfchar(uint16_t ch)
{
    if (VGACHR(ch) == '\n') {
        size_t delta = VGA_WIDTH - vga_position % VGA_WIDTH;
        vga_position += delta;
        if (vga_position >= VGA_WIDTH * VGA_HEIGHT) {
            vgatty_scroll();
        }
        vgatty_move_cursor(vga_position);
    } else {
        vgatty_putfbyte(ch);
    }
}
void vgatty_putfstr(uint16_t *str)
{
    if (str == NULL) {
        return;
    }
    while (*str != '\0') {
        vgatty_putfchar(*str);
    }
}
void vgatty_putfdata(uint16_t *str, size_t len)
{
    if (str == NULL) {
        return;
    }
    for (size_t i = 0; i < len; ++i) {
        vgatty_putfbyte(str[i]);
        ++str;
    }
}

/* MANAGING VGATTY CONFIGURATION (COLOR, ETC) */

void vgatty_setcolor(uint8_t color) { vga_color = color; }
void vgatty_setposition(int row, int col)
{
    if (VGA_ROW_OK(row) && VGA_COL_OK(col)) {
        vga_position = VGA_POSITION(row, col);
    }
    vgatty_move_cursor(vga_position);
}
void vgatty_setcursor(int cursor) {
    if (cursor == 0) {
        vgatty_disable_cursor();
    } else {
        vgatty_enable_cursor(14, 15); /* Bottom of the character cell */
    }
    vgatty_cursor = cursor;
}

int vgatty_getcursor(void) {
    return vgatty_cursor == 0 ? 0 : 1;
}
void vgatty_getposition(int *row, int *col)
{
    if (row != NULL) {
        *row = VGA_ROW(vga_position);
    }
    if (col != NULL) {
        *col = VGA_COL(vga_position);
    }
}

size_t vgatty_write(const char *data, size_t length) {
    if (data == NULL) {
        return 0;
    }
    for (size_t i = 0; i < length; ++i) {
        vgatty_putchar(data[i]);
    }
    return length;
}

/* STUB */
size_t vgatty_read(UNUSED const char *data, UNUSED size_t length) {
    return 0;
}
