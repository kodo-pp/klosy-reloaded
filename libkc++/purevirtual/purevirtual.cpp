#include <stdint.h>
#include <stddef.h>
#include <purevirtual.hpp>
#include <kernel/panic.h>
#include <kcdefines.h>

extern "C" NORETURN void __cxa_pure_virtual()
{
    panic("pure virtual function call");
}
