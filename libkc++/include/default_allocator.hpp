#ifndef LIBKCXX_DEFAULT_ALLOCATOR_HPP
#define LIBKCXX_DEFAULT_ALLOCATOR_HPP

#include <kernel/memory.h>

namespace kstd
{

template <typename T>
struct default_allocator
{
    static T* alloc(size_t size)
    {
        T* ptr = static_cast <T*> (kmalloc(size));
        return ptr;
    }

    static void free(T* ptr)
    {
        kfree(static_cast <void*> (ptr));
    }

    static T* realloc(T* ptr, size_t new_size)
    {
        T* newptr = static_cast <T*> (krealloc(static_cast <void*> (ptr), new_size));
        return newptr;
    }
};

}

#endif // end of include guard: LIBKCXX_DEFAULT_ALLOCATOR_HPP
