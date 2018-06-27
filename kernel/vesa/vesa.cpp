#include <kernel/vesa.hpp>
#include <kcdefines.h>

namespace vesa
{
    static void* framebuffer;
    static size_t width, height, pitch;
    static int bytespp;
}

void vesa_init(void* framebuffer, size_t width, size_t height, size_t pitch, int bpp)
{
    kernel_assert(bpp >= 24);
    vesa::framebuffer = framebuffer;
    vesa::width       = width;
    vesa::height      = height;
    vesa::pitch       = pitch;
    vesa::bytespp     = bpp / 8;
}

void vesa_put_pixel(int y, int x, uint8_t red, uint8_t green, uint8_t blue)
{
    size_t base_pos = vesa::pitch * y + x * vesa::bytespp;
    uint8_t* location = static_cast <uint8_t*> (vesa::framebuffer);
    location[base_pos + 0] = blue;
    location[base_pos + 1] = green;
    location[base_pos + 2] = red;
}

void vesa_put_pixel_faster(void* where, uint32_t color)
{
    size_t where_offset       = reinterpret_cast <size_t> (where);
    size_t framebuffer_offset = reinterpret_cast <size_t> (vesa::framebuffer);

    if (where_offset < framebuffer_offset
            || where_offset + vesa::bytespp > framebuffer_offset + vesa::pitch * vesa::height) {
        return;
    }

    auto location = static_cast <uint8_t*> (where);
    uint8_t blue = color & 0xFF;
    uint8_t green = (color & 0xFF00) >> 8;
    uint8_t red = (color & 0xFF0000) >> 16;
    location[0] = blue; 
    location[1] = green; 
    location[2] = red; 
}

// Even faster. No checks, optimized for bpp=32
void vesa_put_pixel_even_faster(void* where, uint32_t color)
{
    auto location = static_cast <uint32_t*> (where);
    *location = color;
}

uint32_t vesa_make_color(uint8_t red, uint8_t green, uint8_t blue)
{
    return ((uint32_t)red << 16) | ((uint32_t)green << 8) | (uint32_t)blue;
}

void* vesa_locate(size_t y, size_t x)
{
    return static_cast <uint8_t*> (vesa::framebuffer) + (y * vesa::pitch + x * vesa::bytespp);
}

size_t vesa_get_width()  { return vesa::width;       } 
size_t vesa_get_height() { return vesa::height;      }
size_t vesa_get_pitch()  { return vesa::pitch;       }
size_t vesa_get_bpp()    { return vesa::bytespp * 8; }
void* vesa_get_framebuffer() { return vesa::framebuffer; }
