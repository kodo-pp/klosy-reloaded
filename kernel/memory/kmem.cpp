#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <kernel/memory.h>
#include <kernel/vgatty.h>
#include <kernel/power.h>

static void* memory_limit;
static void* heap_blocks;
static void* meta_ptr;
static size_t memory_for_blocks;
static size_t blocks_count;
static size_t usable_blocks_count;
static size_t meta_blocks_count;

static void* usable_ptr_by_offset(size_t offset)
{
    return (void*)((size_t)heap_blocks + offset * KMEM_BLOCK_SIZE);
}
static size_t* meta_ptr_by_offset(size_t offset)
{
    return (size_t*)((size_t)meta_ptr + offset * sizeof(size_t));
}

static size_t offset_by_usable_ptr(void* ptr)
{
    return ((size_t)ptr - (size_t)heap_blocks) / KMEM_BLOCK_SIZE;
}
/*
static size_t offset_by_meta_ptr(void *ptr)
{
    return ((size_t)ptr - (size_t)meta_ptr) / sizeof(size_t);
}
*/

static void set_meta(size_t offset, size_t value)
{
    *meta_ptr_by_offset(offset) = value;
}
static size_t get_meta(size_t offset)
{
    return *meta_ptr_by_offset(offset);
}

int is_block_free(size_t offset)
{
    if (offset >= usable_blocks_count) {
        return false; /* TODO: maybe halt system because of internal error */
    }
    return get_meta(offset) == 0;
}

static size_t find_free_blocks(size_t length)
{
    for (size_t i = 0; i < usable_blocks_count; ++i) {
        if (is_block_free(i)) {
            bool range_free = true;
            for (size_t j = i; j < i + length; ++j) {
                if (!is_block_free(j)) {
                    range_free = false;
                    i = j;
                    break;
                }
            }
            if (range_free) {
                return i;
            }
        }
    }
    return SIZE_T_ERROR;
}

void* kmalloc(size_t size)
{
    size_t length = INTCEIL(size, KMEM_BLOCK_SIZE);
    size_t block_index = find_free_blocks(length);
    if (block_index == SIZE_T_ERROR) {
        return NULL;
    }

    set_meta(block_index, length);
    for (size_t i = 1; i < length; ++i) {
        set_meta(block_index + i, KMEM_BLOCK_CONT);
    }

    return usable_ptr_by_offset(block_index);
}

int kfree(void* ptr)
{
    size_t block_index = offset_by_usable_ptr(ptr);
    if (block_index >= usable_blocks_count) {
        return -1; /* Range error */
    }

    if (is_block_free(block_index)) {
        return -2; /* Already free */
    }

    size_t length = get_meta(block_index);
    if (length == KMEM_BLOCK_CONT) {
        return -3; /* Invalid pointer */
    }

    if (block_index + length - 1 >= usable_blocks_count) {
        return -1; /* Range error */
    }

    for (size_t i = 0; i < length; ++i) {
        set_meta(block_index + i, 0);
    }
    return 0;
}

void set_memory_limit(size_t lim)
{
    memory_limit = ALIGN_DOWN(void*, lim, KMEM_BLOCK_SIZE);
}

void* get_memory_limit(void)
{
    return memory_limit;
}

void init_kmem(size_t mem_lim)
{
    heap_blocks = ALIGN(void*, &heap_memory, KMEM_BLOCK_SIZE);
    set_memory_limit(mem_lim);
    if (memory_limit < heap_blocks) {
        vgatty_putstr("Hmm... It seems that the amount of memory usable by kernel is negative.\n");
        vgatty_putstr("WTF? OK, whatever is happening, halting system right now is the best possible option\n");
        halt();
    }
    memory_for_blocks = (size_t)memory_limit - (size_t)heap_blocks;
    blocks_count = memory_for_blocks / KMEM_BLOCK_SIZE;
    usable_blocks_count = blocks_count * KMEM_BLOCK_SIZE / (KMEM_BLOCK_SIZE + sizeof(size_t));
    meta_blocks_count = blocks_count - usable_blocks_count;
    meta_ptr = (void*)((size_t)heap_blocks + usable_blocks_count * KMEM_BLOCK_SIZE);
    for (size_t i = 0; i < meta_blocks_count; ++i) {
        set_meta(i, 0);
    }
}

int definitely_not_code(void* ptr)
{
    if (ptr == 0) {
        return 1;
    } else if ((size_t)ptr >= (size_t)(&heap_memory)) { /* Points to somewhere in the heap */
        return 1;
    } else {
        return 0;
    }
}
