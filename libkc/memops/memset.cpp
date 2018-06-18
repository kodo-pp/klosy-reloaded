#include <stdint.h>
#include <stddef.h>
#include <memops.h>

void memset(void *begin, int fill, size_t length)
{
    uint8_t *ubegin = (uint8_t *)begin;
    for (size_t i = 0; i < length; ++i) {
        *(ubegin + i) = (uint8_t)(fill & 0xFF);
    }
}
