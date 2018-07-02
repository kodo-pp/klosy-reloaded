#include <stdint.h>
#include <stddef.h>
#include <memops.h>

extern "C" void memcpy_fast(void* dest, const void* src, size_t length);

void memmove(void* dest, const void* src, size_t length)
{
    uint8_t* udest = static_cast <uint8_t*> (dest);
    const uint8_t* usrc  = static_cast <const uint8_t*> (src);

    size_t   ndest = reinterpret_cast <size_t> (dest);
    size_t   nsrc  = reinterpret_cast <size_t> (src);

    if (ndest > nsrc) {
        // Reversed copying
        // Why just not (i = length - 1; i >= 0; --i)? Because size_t is unsigned
        for (size_t i = length; i > 0; --i) {
            *(udest + i - 1) = *(usrc + i - 1);
        }
    } else if (ndest < nsrc) {
        if (ndest % 4 == 0 && nsrc % 4 == 0 && length % 16 == 0) {
            memcpy_fast(dest, src, length);
            return;
        }
        // Direct copying
        for (size_t i = 0; i < length; ++i) {
            *(udest + i) = *(usrc + i);
        }
    }
}
