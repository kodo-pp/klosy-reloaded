#include <stdint.h>
#include <stddef.h>
#include <kernel/panic.h>
#include <kcdefines.h>
#include <stdio.h>

NORETURN void kernel_assert_fail(const char *expr, const char *filename, int lineno) {
    if (has_kernel_tty()) {
        printf("FATAL: Kernel assertion failed\n");
        printf("Assertion: %s\n", expr);
        printf("File %s, line %d\n", filename, lineno);
        panic("kernel assertion failed");
    } else {
        early_boot_failure("Early kernel assertion failed");
    }
}
