#ifndef KERNEL_MEMORY_H
#define KERNEL_MEMORY_H

#include <stdint.h>
#include <stddef.h>

/*
 * Minimal allocatable size
 */
#define KMEM_BLOCK_SIZE 256

/*
 * Block continuation mark
 */
#define KMEM_BLOCK_CONT ((size_t)(-2))

/*
 * Heap memory beginning, symbol comes from linker script.
 */
extern size_t heap_memory;
/*extern size_t memory_limit;*/

/** allocates a chunk of memory for the kernel needs */
void *kmalloc(size_t size);
/** deallocates memory allocated with kmalloc */
int kfree(void *ptr);
/** tells whether the block of memory is allocated or not */
bool is_block_free(size_t offset);

/** Sets the variable memory_limit to specified value */
void set_memory_limit(size_t lim);
/** Returns the value of memory_limit variable */
void *get_memory_limit(void);

/** Performs the initialization of memory management module of kernel */
void init_kmem(size_t mem_lim);

#endif /* end of include guard: KERNEL_MEMORY_H */
