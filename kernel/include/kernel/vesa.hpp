#ifndef KERNEL_VESA_HPP
#define KERNEL_VESA_HPP

#include <stdint.h>
#include <stddef.h>

void vesa_init(void* framebuffer, size_t width, size_t height, size_t pitch, int bpp);

// Slow and naive version
void vesa_put_pixel(int y, int x, uint8_t red, uint8_t green, uint8_t blue);

// Faster, doesn't calculate the position any time. Checks the position user has given
void vesa_put_pixel_faster(void* where, uint32_t color);

// Even faster. No checks, optimized for bpp=32
void vesa_put_pixel_even_faster(void* where, uint32_t color);

// Make a uint32_t color from R, G, B components
uint32_t vesa_make_color(uint8_t red, uint8_t green, uint8_t blue);

// Make a pointer to specified framebuffer location
void* vesa_locate(size_t y, size_t x);

void*  vesa_get_framebuffer();
size_t vesa_get_width();
size_t vesa_get_height();
size_t vesa_get_pitch();
size_t vesa_get_bpp();

uint32_t vesa_hexchar_to_color(char hexchar);

#endif // end of include guard: KERNEL_VESA_HPP
