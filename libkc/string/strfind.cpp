#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <kcdefines.h>

size_t strfindc(const char* str, char ch)
{
    if (str == NULL) {
        return SIZE_T_ERROR;
    }

    size_t offset = 0;

    while (*str != '\0') {
        if (*str == ch) {
            return offset;
        }
    }

    return SIZE_T_ERROR;
}
