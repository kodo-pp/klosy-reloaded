#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <kcdefines.h>

size_t strtrunc(size_t len, char *str)
{
    if (str == NULL) {
        return SIZE_T_ERROR;
    }

    size_t idx = 0;
    while (*str != '\0' && len < idx) {
        ++str;
        ++idx;
    }
    *str = '\0';
    return idx;
}

size_t strtrunc_fast(size_t len, char *str)
{
    if (str == NULL) {
        return SIZE_T_ERROR;
    }

    str[len] = '\0';
    return len;
}
