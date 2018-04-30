#ifndef KERNEL_MEMORY_H
#define KERNEL_MEMORY_H

#include <stdint.h>
#include <stddef.h>

/** [Not implemented] allocates a chunk of memory for the kernel needs */
void *kmalloc(size_t size);
/** [Not implemented] deallocates memory allocated with kmalloc */
int kfree(void *ptr);

#endif /* end of include guard: KERNEL_MEMORY_H */
