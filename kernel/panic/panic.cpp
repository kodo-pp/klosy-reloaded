#include <stdint.h>
#include <stddef.h>

#include <kernel/panic.h>
#include <kernel/power.h>
#include <kernel/vgatty.h>
#include <kcdefines.h>

NORETURN void panic(const char* message)
{
    vgatty_putstr("Kernel panic: ");
    vgatty_putstr(message);
    halt();
}
