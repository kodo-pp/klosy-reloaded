#ifndef KERNEL_MEMORY_H
#define KERNEL_MEMORY_H

#include <stdint.h>
#include <stddef.h>

void *kmalloc(size_t size);
int kfree(void *ptr);

#endif /* end of include guard: KERNEL_MEMORY_H */
