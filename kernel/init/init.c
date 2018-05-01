#include <stdint.h>
#include <stddef.h>

#include <kernel/init.h>
#include <kernel/memory.h>
#include <kernel/panic.h>

void init_modules(struct multiboot_info *mbt)
{
    if (!(mbt->flags & 1)) {
        early_boot_failure("Memory information not provided by bootloader");
    }
    init_memory(mbt->mem_upper*1024 + 1024*1024);
    init_tty();
}
