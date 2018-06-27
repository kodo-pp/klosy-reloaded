#include <stdint.h>
#include <stddef.h>

#include <kernel/vgatty.h>
#include <kernel/vesa.hpp>
#include <kernel/vesa_tty.hpp>
#include <kernel/tty.h>
#include <kernel/init.h>
#include <kernel/power.h>

extern size_t vgatty_write(const char*, size_t);
extern size_t vgatty_read(char*, size_t);

static void init_vgatty()
{
    vgatty_reset();
    struct tty vgatty;
    vgatty.write_func = vgatty_write;
    vgatty.read_func = vgatty_read;
    int ttyno = register_tty(&vgatty);
    set_kernel_tty(ttyno);
}

static void init_vesa(struct multiboot_info* mbt)
{
    vesa_init(reinterpret_cast <void*> (mbt->framebuffer_addr),
              mbt->framebuffer_width,
              mbt->framebuffer_height,
              mbt->framebuffer_pitch,
              mbt->framebuffer_bpp);
}

int init_tty(struct multiboot_info* mbt)
{
    if (mbt->framebuffer_type == 2) {
        init_vgatty();
    } else if (mbt->framebuffer_type == 1) {
        init_vesa(mbt);
        vesa_tty_init(mbt);
        /*
        for (int i = 0; i < 1024; ++i) {
            for (int j = 0; j < 1080; ++j) {
                vesa_put_pixel(i, j, i * 256 / 1024, j * 256 / 1080, (i + j) % 256);
            }
        }

        halt();
        */
    }
    return 0;
}
