#include <stdint.h>
#include <stddef.h>

#include <kernel/memory.h>
#include <kernel/init.h>

int init_memory(const struct multiboot_info* mbt, size_t memory_limit)
{
    init_kmem(mbt, memory_limit);
    return 0;
}
