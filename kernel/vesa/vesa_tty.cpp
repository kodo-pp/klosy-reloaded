#include <kernel/vesa_tty.hpp>
#include <kernel/multiboot.h>
#include <kernel/vesa.hpp>
#include <kernel/tty.h>
#include <kernel/fs/tar.h>
#include <stddef.h>
#include <stdint.h>
#include <memops.h>

#include <kcdefines.h>
#include <util.h>

namespace vesa_tty
{
    static size_t col = 0;
    static size_t row = 0;
    static const int font_width = 8;
    static const int font_height = 8;
    static int fg_color = 0xa0a0a0;
    static int bg_color = 0x000000;
    static void* font;
}

/* INITIALIZATION FUNCTIONS */

void vesa_tty_init(struct multiboot_info* mbt)
{
    if (mbt->mods_count == 0) {
        panic("initrd not found");
    }
    auto mods = reinterpret_cast <const struct multiboot_mod_list*> (mbt->mods_addr);
    kernel_assert(mods != nullptr);

    auto tarball = reinterpret_cast <void*>  (mods[0].mod_start);
    size_t len   = static_cast <size_t> (mods[0].mod_end - mods[0].mod_start);

    struct ustar_file* fontfile = ustar_fileseek(tarball, len, "default_font.bin");
    if (fontfile == nullptr) {
        panic("unable to find font file");
    }

    kstd::string font;
    ustar_read(fontfile, font);
    kernel_assert(font.length() == 8 * 256);

    vesa_tty::font = kmalloc(8 * 256);
    if (vesa_tty::font == nullptr) {
        vesa_tty::font = font.c_str(); // Won't cause UB
        panic("font is nullptr");
    }

    memcpy(vesa_tty::font, font.c_str(), 8 * 256);

    struct tty t;
    t.write_func = vesa_tty_write;
    t.read_func = vesa_tty_read;
    int ttyno = register_tty(&t);
    set_kernel_tty(ttyno);
}

/* CLEAR AND RESET FUNCTIONS */

void vesa_tty_clear()
{
    size_t size = vesa_get_pitch() * vesa_get_height();
    memset(vesa_get_framebuffer(), 0x00, size);
    vesa_tty::col = 0;
    vesa_tty::row = 0;
}

void vesa_tty_reset()
{
    vesa_tty_clear();
    vesa_tty_setfgcolor(0xa0a0a0);
}

static size_t vesa_tty_height() { return vesa_get_height() / vesa_tty::font_height; }
static size_t vesa_tty_width() { return vesa_get_width() / vesa_tty::font_width; }

static void vesa_tty_scroll()
{
    size_t size = vesa_get_pitch() * (vesa_get_height() - 1);
    void* framebuffer = vesa_get_framebuffer();
    void* second_line = static_cast <uint8_t*> (framebuffer) + vesa_get_pitch() * vesa_tty::font_height; 
    memmove_fast(framebuffer, second_line, size);

    vesa_tty_setposition(vesa_get_height() - 1, 0);
}

template <typename Int>
static inline bool getbit(Int n, int bit)
{
    return (n & (1ULL << bit)) > 0;
}

void vesa_tty_putchar(char ch)
{
    if (ch == '\n') {
        vesa_tty::col = 0;
        ++vesa_tty::row;
        if (vesa_tty::row >= vesa_tty_height()) {
            --vesa_tty::row;
            vesa_tty_scroll();
        }
        return;
    }
    uint64_t glyph = static_cast <uint64_t*> (vesa_tty::font)[static_cast <uint8_t> (ch)];

    auto pitch = vesa_get_pitch();
    auto bpp = vesa_get_bpp();
    uint8_t* framebuffer = static_cast <uint8_t*> (vesa_get_framebuffer());
    UNUSED uint8_t* where = framebuffer
                     + pitch * vesa_tty::font_height * vesa_tty::row
                     + bpp   * vesa_tty::font_width  * vesa_tty::col;
    int bit = 63;
    kernel_assert(vesa_tty::font_height == 8);
    kernel_assert(vesa_tty::font_width == 8);

    /* Faster but untested */
    /*
    for (int i = 0; i < vesa_tty::font_height; ++i) {
        auto prev_where = where;
        for (int j = 0; j < vesa_tty::font_width; ++j) {
            vesa_put_pixel_faster(where, getbit(glyph, bit) ? vesa_tty::fgcolor : vesa_tty::bgcolor);
            where += bpp / 8;
            --bit;
        }
        where = prev_where + pitch;
    }
    */

    /* Slower but more reliable */
    for (int i = 0; i < vesa_tty::font_height; ++i) {
        for (int j = 0; j < vesa_tty::font_width; ++j) {
            uint8_t red   = ((getbit(glyph, bit) ? vesa_tty::fg_color : vesa_tty::bg_color) & 0xFF0000) >> 16;
            uint8_t green = ((getbit(glyph, bit) ? vesa_tty::fg_color : vesa_tty::bg_color) & 0x00FF00) >>  8;
            uint8_t blue  = ((getbit(glyph, bit) ? vesa_tty::fg_color : vesa_tty::bg_color) & 0x0000FF) >>  0;
            vesa_put_pixel(i + vesa_tty::font_height * vesa_tty::row, j + vesa_tty::font_width * vesa_tty::col, red, green, blue);
            --bit;
        }
    }
    ++vesa_tty::col;

    //auto width = vesa_get_width() / vesa_tty::font_width;
    //auto height = vesa_get_height() / vesa_tty::font_height;
    
    auto width = vesa_tty_width();
    auto height = vesa_tty_height();

    if (vesa_tty::col >= width) {
        vesa_tty::col = 0;
        ++vesa_tty::row;
        if (vesa_tty::row >= height) {
            --vesa_tty::row;
            vesa_tty_scroll();
        }
    }
}

void vesa_tty_setfgcolor(uint32_t color)
{
    vesa_tty::fg_color = color;
}

void vesa_tty_setposition(size_t row, size_t col)
{
    vesa_tty::row = row;
    vesa_tty::col = col;
}

size_t vesa_tty_write(const char* data, size_t length)
{
    if (data == nullptr) {
        return 0;
    }
    for (size_t i = 0; i < length; ++i) {
        vesa_tty_putchar(data[i]);
    }
    return length;
}

/* STUB */
size_t vesa_tty_read(UNUSED char* data, UNUSED size_t length)
{
    return 0;
}

