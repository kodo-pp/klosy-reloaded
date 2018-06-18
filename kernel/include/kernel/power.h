#ifndef KERNEL_POWER_H
#define KERNEL_POWER_H

#include <kcdefines.h>

/**
 * Halts system, does not turn power off.
 */

#ifdef __cplusplus
extern "C" {
#endif

NORETURN void halt(void);
void idle(void);

#ifdef __cplusplus
}
#endif

#endif /* end of include guard: KERNEL_POWER_H */
