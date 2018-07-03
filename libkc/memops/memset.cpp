#include <stdint.h>
#include <stddef.h>
#include <memops.h>

void memset(volatile void* begin, uint8_t fill, size_t length)
{
    volatile uint8_t* ubegin = (volatile uint8_t*)begin;
    for (size_t i = 0; i < length; ++i) {
        *(ubegin + i) = fill;
    }
}
