#include <stdint.h>
#include <stddef.h>
#include <memops.h>

void memcpy(void *dest, const void *src, size_t length)
{
    uint8_t *udest = (uint8_t *)dest;
    uint8_t *usrc = (uint8_t *)src;
    for (size_t i = 0; i < length; ++i) {
        *(udest + i) = *(usrc + i);
    }
}
