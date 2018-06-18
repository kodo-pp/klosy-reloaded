#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

extern "C" size_t c_puts(const char* str)
{
    return puts(str);
}
