#ifndef KERNEL_INIT_H
#define KERNEL_INIT_H

#include <stdint.h>
#include <stddef.h>
#include <kernel/multiboot.h>

/** Initializes all crucial kernel modules (such as memory manager or VGA tty) */
void init_modules(struct multiboot_info *mbt);

/** Init function. Initialize kernel memory manager. Wrapper for init_kmem() */
int init_memory(size_t memory_limit);

/** Init function. Initialize terminal control module and default VGA terminal */
int init_tty(struct multiboot_info* mbt);

#endif /* end of include guard: KERNEL_INIT_H */
