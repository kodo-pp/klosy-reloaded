#include <stdint.h>
#include <stddef.h>

#include <kernel/memory.h>
#include <kernel/init.h>

int init_memory(size_t memory_limit)
{
    init_kmem(memory_limit);
    return 0;
}
