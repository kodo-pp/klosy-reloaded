#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <kcdefines.h>

size_t strcat(char* dest, const char* src)
{
    if (dest == nullptr || src == nullptr) {
        return SIZE_T_ERROR;
    }

    size_t len = 0;

    while (*dest != '\0') {
        ++dest;
        ++len;
    }
    while (*src != '\0') {
        *dest = *src;
        ++dest;
        ++src;
        ++len;
    }
    return len;
}

size_t strncat(size_t lim, char* dest, const char* src)
{
    if (dest == nullptr || src == nullptr) {
        return SIZE_T_ERROR;
    }

    size_t len = 0;

    while (*dest != '\0' && len < lim) {
        ++dest;
        ++len;
    }
    while (*src != '\0' && len < lim) {
        *dest = *src;
        ++dest;
        ++src;
        ++len;
    }
    return len;
}
