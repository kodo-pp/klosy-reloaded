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
        return static_cast <T*> (kmalloc(size));
    }

    static void free(T* ptr)
    {
        kfree(static_cast <void*> (ptr));
    }

    static T* realloc(T* ptr, size_t new_size)
    {
        return static_cast <T*> (krealloc(static_cast <void*> (ptr), new_size));
    }
};

}

#endif // end of include guard: LIBKCXX_DEFAULT_ALLOCATOR_HPP
