#include <stdint.h>
#include <stddef.h>
#include <util.h>

int from_hex_char(char ch)
{
    if ('0' <= ch && ch <= '9') {
        return ch - '0';
    } else if ('A' <= ch && ch <= 'F') {
        return ch - 'A' + 10;
    } else if ('a' <= ch && ch <= 'f') {
        return ch - 'a' + 10;
    } else {
        return -1;
    }
}
