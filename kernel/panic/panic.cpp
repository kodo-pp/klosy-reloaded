#include <stdint.h>
#include <stddef.h>

#include <kernel/panic.h>
#include <kernel/power.h>
#include <kernel/vgatty.h>
#include <kcdefines.h>
#include <stdio.h>

NORETURN void panic(const char* message)
{
    writes("Kernel panic: ");
    writes(message);
    halt();
}
