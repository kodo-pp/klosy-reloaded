#ifndef LIBKCXX_BUFFR_HPP
#define LIBKCXX_BUFFR_HPP

#include <vector.hpp>
#include <kernel/power.h>
#include <stdio.h>

namespace kstd
{

// TODO: automatically free unnecessary information w/o invalidating iterators
template <typename T>
class buffer
{
public:
    buffer() = default;
    buffer(const buffer <T>&) = default;
    buffer(buffer <T>&&) = default;
    ~buffer() = default;

    void write(const T* data, size_t len)
    {
        //this->data.reserve(data.length() + len);
        for (size_t i = 0; i < len; ++i) {
            this->data.push_back(data[i]);
        }
    }

    void read(T* data, size_t len)
    {
        for (size_t i = 0; i < len; ++i) {
            while (begin >= this->data.length()) {
                idle();
            }
            
            data[i] = this->data.at(begin);
            ++begin;
        }
    }

    // TODO: add readsome method

    void trim()
    {
        for (size_t i = begin; i < data.length(); ++i) {
            data.at(i - begin) = data.at(i);
        }
        data.resize(data.length() - begin);
        begin = 0;
    }

private:
    size_t begin;
    kstd::vector <T> data;
};

}

#endif // end of include guard:  LIBKCXX_BUFFR_HPP
