#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <kcdefines.h>

size_t strcpy(char *dest, const char *src)
{
    if (dest == NULL || src == NULL) {
        return SIZE_T_ERROR;
    }

    size_t len = 0;
    while (*src != '\0') {
        *dest = *src;
        ++dest;
        ++src;
        ++len;
    }
    return len;
}

size_t strncpy(size_t lim, char *dest, const char *src)
{
    if (dest == NULL || src == NULL) {
        return SIZE_T_ERROR;
    }

    size_t len = 0;
    while (*src != '\0' && len < lim) {
        *dest = *src;
        ++dest;
        ++src;
        ++len;
    }
    return len;
}
