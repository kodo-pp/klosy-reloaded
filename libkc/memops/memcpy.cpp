#include <stdint.h>
#include <stddef.h>
#include <memops.h>

extern "C" void memcpy_fast(void* dest, const void* src, size_t length);

void memcpy(void* dest, const void* src, size_t length)
{
    uint8_t* udest = (uint8_t*)dest;
    uint8_t* usrc = (uint8_t*)src;

    size_t ndest = reinterpret_cast <size_t> (dest);
    size_t nsrc = reinterpret_cast <size_t> (src);

    if (ndest % 4 == 0 && nsrc % 4 == 0 && length % 16 == 0) {
        memcpy_fast(dest, src, length);
        return;
    }

    for (size_t i = 0; i < length; ++i) {
        *(udest + i) = *(usrc + i);
    }
}
