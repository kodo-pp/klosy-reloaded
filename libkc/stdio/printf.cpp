#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <convert.h>
#include <kcdefines.h>
#include <kernel/memory.h>

size_t printf(const char* fmt, ...)
{
    if (fmt == NULL) {
        return SIZE_T_ERROR;
    }
    char* buf = static_cast <char*> (kmalloc(256 * sizeof(char)));
    if (!buf) {
        return SIZE_T_ERROR;
    }

    va_list args;
    va_start(args, fmt);
    size_t written = 0;

    for (size_t i = 0; fmt[i] != '\0'; ++i) {
        if (fmt[i] == '%') {
            ++i;
            switch(fmt[i]) {
            case '%':
                written += write("%", 1);
                break;
            case 'd':
                written += writes(int_to_str(buf, va_arg(args, int)));
                break;
            case 'u':
                written += writes(uint_to_str(buf, va_arg(args, unsigned int)));
                break;
            case 'z':
                written += writes(size_t_to_str(buf, va_arg(args, size_t)));
                break;
            case 'D':
                written += writes(longlong_to_str(buf, va_arg(args, long long)));
                break;
            case 'U':
                written += writes(ulonglong_to_str(buf, va_arg(args, unsigned long long)));
                break;
            case 'f':
                va_arg(args, double);
                written += writes("<unimplemented:float>");
                break;
            case 'F':
                va_arg(args, double);
                written += writes("<unimplemented:double>");
                break;
            case 'P':
                va_arg(args, long double);
                written += writes("<unimplemented:longdouble>");
                break;
            case 'x':
                written += writes(uint_to_str_base(buf, va_arg(args, unsigned int), 16));
                break;
            case 'X':
                written += writes(ulonglong_to_str_base(buf, va_arg(args, unsigned long long), 16));
                break;
            case 'p':
                written += writes(size_t_to_str_base(buf, va_arg(args, size_t), 16));
                break;
            case 'o':
                written += writes(uint_to_str_base(buf, va_arg(args, unsigned int), 8));
                break;
            case 'O':
                written += writes(ulonglong_to_str_base(buf, va_arg(args, unsigned long long), 8));
                break;
            case 's':
                written += writes(va_arg(args, char*));
                break;
            case 'c': {
                char c = (char)va_arg(args, int);
                written += write(&c, 1);
            }
            break;
            }
        } else {
            write(fmt + i, 1);
        }
    }

    kfree(buf);
    return written;
}
