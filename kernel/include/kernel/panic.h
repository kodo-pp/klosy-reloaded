#ifndef KERNEL_PANIC_H
#define KERNEL_PANIC_H

#include <stdint.h>
#include <stddef.h>
#include <kcdefines.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Early failure reporter. Does not requires VGA terminal to be initialized */
NORETURN void early_boot_failure(char *message);

/** Failure reporter. Prints message and halts system */
NORETURN void panic(char *message);

#ifdef __cplusplus
}
#endif

#endif /* end of include guard: KERNEL_PANIC_H */
