#include <stdint.h>
#include <stddef.h>

#include <kernel/vgatty.h>
#include <kernel/tty.h>
#include <kernel/init.h>

extern size_t vgatty_write(const char*, size_t);
extern size_t vgatty_read(char*, size_t);

int init_tty(void)
{
    vgatty_reset();
    struct tty vgatty;
    vgatty.write_func = vgatty_write;
    vgatty.read_func = vgatty_read;
    int ttyno = register_tty(&vgatty);
    set_kernel_tty(ttyno);
    return 0;
}
