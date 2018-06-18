#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <kernel/tty.h>

/* TODO: improve performance */
size_t puts(const char* str)
{
    size_t len = 0;
    len += write(str, strlen(str));
    len += write("\n", 1);
    return len;
}

/* TODO: improve performance */
size_t writes(const char* str)
{
    return write(str, strlen(str));
}
