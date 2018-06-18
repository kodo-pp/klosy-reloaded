#include <stdint.h>
#include <stddef.h>
#include <memops.h>

int memcmp(void* a, void* b, size_t length)
{
    uint8_t* ua = (uint8_t*)a;
    uint8_t* ub = (uint8_t*)b;
    for (size_t i = 0; i < length; ++i) {
        if (*(ua + i) < *(ub + i)) {
            return -1;
        } else if (*(ua + i) > *(ub + i)) {
            return 1;
        }
    }
    return 0;
}
