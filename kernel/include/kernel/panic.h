#ifndef KERNEL_PANIC_H
#define KERNEL_PANIC_H

#include <stdint.h>
#include <stddef.h>
#include <kcdefines.h>

/** Early failure reporter. Does not requires VGA terminal to be initialized */
NORETURN void early_boot_failure(char *message);

/** Failure reporter. Prints message and halts system */
NORETURN void panic(char *message);

#endif /* end of include guard: KERNEL_PANIC_H */
