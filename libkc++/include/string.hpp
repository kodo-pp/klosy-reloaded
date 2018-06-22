#ifndef LIBKCXX_STRING_HPP
#define LIBKCXX_STRING_HPP

#include <default_allocator.hpp>
#include <type_traits.hpp>
#include <kernel/panic.h>
#include <memops.h>

namespace kstd
{

template <typename T, typename Alloc = kstd::default_allocator<T> >
class basic_string
{
public:
    // Default c-tor
    basic_string()
        : _data(1, T(0))
    { }

    // Copy c-tor
    basic_string(const basic_string& other)
        : _data(other._data)
    { }

    // Move c-tor
    basic_string(basic_string <T>&& other)
        : _data(other._data)
    { }
    
    // Fill c-tor
    basic_string(size_t count, T value = T())
        : _data(count, value)
    {
        _data.push_back(T(0));
    }

    // C-style string copy
    basic_string(const T* str)
    {
        while(*str != T(0)) {
            push_back(*str)
            ++str;
        }
    }

    // C-style array copy
    basic_string(const T* arr, size_t count)
    {
        resize(count)
        for (size_t i = 0; i < count; ++i) {
            at(i) = arr[i];
        }
    }

    // D-tor
    virtual ~basic_string() = default;

    // Access (no range checks)
    T& operator [](size_t idx)
    {
        return _data[idx];
    }

    // Access (with range checks)
    T& at(size_t idx)
    {
        return _data.at(idx);
    }

    // Appending element
    void push_back(T elem)
    {
        _data[_data.length() - 1] = elem;
        _data.push_back(T(0));
    }

    // Change actual size of basic_string
    void resize(size_t new_length, T elem = T())
    {
        _data.resize(new_length);
        _data.push_back(T(0));
    }

    // Get length
    size_t length()
    {
        return _data.length() - 1;
    }

    // Provide access to c-style (zero-terminated) string buffer
    T* c_str()
    {
        return _data.data();
    }

    // Concatenate strings together
    basic_string <T, Alloc> operator+(const basic_string& other)
    {
        basic_string <T, Alloc> ret(*this);
        ret.resize(length() + other.length());
        for (size_t i = 0; i < other.length(); ++i) {
            ret.at(length() + i) = other.at(i);
        }
        return ret;
    }

    // Compare two strings
    bool operator==(const basic_string& other)
    {
        if (length() != other.length()) {
            return false;
        }

        for (size_t i = 0; i < length(); ++i) {
            if (at(i) != other.at(i)) {
                return false;
            }
        }
        return true;
    }

protected:
    vector <T, Alloc> _data;
};

using string = basic_string <char>

}

#endif /* end of include guard: LIBKC_STRING_HPP */
