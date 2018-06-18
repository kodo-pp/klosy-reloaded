#ifndef LIBKCXX_VECTOR_HPP
#define LIBKCXX_VECTOR_HPP

#include <default_allocator.hpp>

namespace kstd
{

template <typename T, typename Alloc = kstd::default_allocator<T> >
class vector
{
public:
    // Default c-tor
    vector()
        : _length(0)
        , _capacity(0)
        , _data(nullptr);

    // Copy c-tor
    vector(const vector <T>& other)
        : _length(other._length)
        , _capacity(other._capacity)
    {
        _data = Alloc::alloc(_capacity * sizeof(T));
        memcpy(_data, other._data, _length * sizeof(T));
    }

    // Move c-tor
    vector(vector <T>&& other)
        : _length(other._length)
        , _capacity(other._capacity)
        , _data(other._data)
    {
        other._length = 0;
        other._capacity = 0;
        other._data = nullptr;
    }
    
    // Fill c-tor
    vector(size_t count, T value = T())
        : _length(count)
        , _capacity(count)
    {
        _data = Alloc::alloc(_capacity * sizeof(T));
        if (_data == nullptr) {
            // TEMP: Replace with throwing an exception when implemented
            printf("std::kvector<%s> at 0x%x: unable to allocate memory for %z elements (%z bytes)\n",
                   kstd::type_traits::type_name<T>,
                   static_cast <size_t> (this),
                   _capacity,
                   _capacity * sizeof(T)
            );
            panic("kstd::vector: memory allocation failed");
        }

        memset(_data, 0, _length * sizeof(T));
    }

    // D-tor
    virtual ~vector()
    {
        Alloc::free(_data);
    }

    // Access (no range checks)
    T& operator [](size_t idx)
    {
        return _data[idx];
    }

    // Access (with range checks)
    T& at(size_t idx)
    {
        // TEMP
        kernel_assert(idx >= 0 && idx < _length);
        return _data[idx];
    }

    // Appending element
    void push_back(T elem)
    {
        if (_length >= _capacity) {
            if (_length < 16) {
                _capacity = 16; // Some sane value
            } else {
                _capacity *= 2;
            }
            kernel_assert(_capacity > _length);
            decltype(_data) tmp = Alloc::realloc(_data, _capacity);
            if (tmp == nullptr) {
                // TEMP
                printf("std::kvector<%s> at 0x%x: unable to [re]allocate memory for %z elements (%z bytes)\n",
                       kstd::type_traits::type_name<T>,
                       static_cast <size_t> (this),
                       _capacity,
                       _capacity * sizeof(T)
                );
                panic("kstd::vector: memory allocation failed");
            }
            _data = tmp;
        }

        kernel_assert(_capacity > _length);
        _data[_length] = elem;
        ++_length;
    }

protected:
    size_t _length;
    size_t _capacity;
    T* _data;
};

}

#endif /* end of include guard: LIBKC_VECTOR_HPP */
