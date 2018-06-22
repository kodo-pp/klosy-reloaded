#include <kernel/memory.h>

void* operator new(size_t size)
{
    return kmalloc(size);
}

void* operator new[](size_t size)
{
    return kmalloc(size);
}

void operator delete(void* ptr)
{
    kfree(ptr);
}

void operator delete[](void* ptr)
{
    kfree(ptr);
}
