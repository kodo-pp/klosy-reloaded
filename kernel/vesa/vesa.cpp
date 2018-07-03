#include <kernel/vesa.hpp>
#include <kernel/memory.h>
#include <kernel/power.h>
#include <kcdefines.h>
#include <memops.h>

namespace vesa
{
    static void* virtual_framebuffer;
    static void* back_framebuffer;
    static void* real_framebuffer;
    static size_t width, height, pitch;
    static int bytespp;

    uint32_t colortab[16] {
        0x000000,
        0x000080,
        0x008000,
        0x008080,
        0x800000,
        0x800080,
        0x808000,
        0x808080,
        0x000000,
        0x0000FF,
        0x00FF00,
        0x00FFFF,
        0xFF0000,
        0xFF00FF,
        0xFFFF00,
        0xFFFFFF,
    };
}

extern "C" const auto _c_vesa_real_fb = &vesa::real_framebuffer;
extern "C" const auto _c_vesa_virt_fb = &vesa::virtual_framebuffer;
extern "C" const auto _c_vesa_back_fb = &vesa::back_framebuffer;
size_t _c_vesa_fblen;

void vesa_init(void* framebuffer, size_t width, size_t height, size_t pitch, int bpp)
{
    if (bpp < 32) {
        for (int i = 0; i < 1000; ++i) {
            static_cast <uint16_t*> (framebuffer)[i] = 0xBAD;
        }
        halt();
    }
    vesa::real_framebuffer    = framebuffer;
    vesa::virtual_framebuffer = kmalloc(height * pitch);
    kmalloc(1000);
    vesa::back_framebuffer    = kmalloc(height * pitch);
    vesa::width               = width;
    vesa::height              = height;
    vesa::pitch               = pitch;
    vesa::bytespp             = bpp / 8;
    _c_vesa_fblen             = height * pitch;

    if (vesa::virtual_framebuffer == nullptr || vesa::back_framebuffer == nullptr) {
        for (int i = 0; i < 1000; ++i) {
            static_cast <uint16_t*> (framebuffer)[i] = 0xBAD;
        }
        halt();
    }

    memset(vesa::real_framebuffer, 0, _c_vesa_fblen);
    memset(vesa::virtual_framebuffer, 0, _c_vesa_fblen);
    memset(vesa::back_framebuffer, 0, _c_vesa_fblen);
}

void vesa_put_pixel(int y, int x, uint8_t red, uint8_t green, uint8_t blue)
{
    size_t base_pos = vesa::pitch * y + x * vesa::bytespp;
    uint8_t* location = static_cast <uint8_t*> (vesa::virtual_framebuffer);
    location[base_pos + 0] = blue;
    location[base_pos + 1] = green;
    location[base_pos + 2] = red;
}

void vesa_put_pixel_faster(void* where, uint32_t color)
{
    size_t where_offset       = reinterpret_cast <size_t> (where);
    size_t framebuffer_offset = reinterpret_cast <size_t> (vesa::virtual_framebuffer);

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
    return static_cast <uint8_t*> (vesa::virtual_framebuffer) + (y * vesa::pitch + x * vesa::bytespp);
}

size_t vesa_get_width()  { return vesa::width;       } 
size_t vesa_get_height() { return vesa::height;      }
size_t vesa_get_pitch()  { return vesa::pitch;       }
size_t vesa_get_bpp()    { return vesa::bytespp * 8; }
void* vesa_get_framebuffer() { return vesa::virtual_framebuffer; }

uint32_t vesa_hexchar_to_color(char hexchar)
{
    int idx = -1;
    if ('0' <= hexchar && hexchar <= '9') {
        idx = hexchar - '0';
    } else if ('A' <= hexchar && hexchar <= 'F') {
        idx = hexchar - 'A' + 10;
    } else if ('a' <= hexchar && hexchar <= 'f') {
        idx = hexchar - 'a' + 10;
    }

    if (idx == -1) {
        return 0xBADC07;
    } else {
        return vesa::colortab[idx];
    }
}

void vesa_flush_rect(size_t left, size_t top, size_t width, size_t height)
{
    uint8_t* real = static_cast <uint8_t*> (vesa::real_framebuffer);
    uint8_t* virt = static_cast <uint8_t*> (vesa::virtual_framebuffer);
    uint8_t* back = static_cast <uint8_t*> (vesa::back_framebuffer);
    for (size_t i = 0; i < width; ++i) {
        for (size_t j = 0; j < height; ++j) {
            size_t offset = (top + j) * vesa::pitch + (left + i) * vesa::bytespp;
            for (int k = 0; k < vesa::bytespp; ++k) {
                if (back[offset+k] != virt[offset+k]) {
                    real[offset+k] = virt[offset+k];
                    back[offset+k] = virt[offset+k];
                }
            }
        }
    }
}
