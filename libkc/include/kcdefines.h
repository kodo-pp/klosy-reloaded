#ifndef LIBKC_KCDEFINES_H
#define LIBKC_KCDEFINES_H

#define NORETURN __attribute__((noreturn))
#define UNUSED __attribute__((unused))
#define PACKED __attribute__((packed))

/* Aling non-negative value of arbitary integer or pointer type */
#define ALIGN(type, val, size) ((type)((size_t)(val) + (size_t)(size) - (size_t)1 - ((size_t)(val) + (size_t)(size) - (size_t)1) % (size_t)(size)))

/* The same as above, but if val % size != 0, then decrease val, not increase it */
#define ALIGN_DOWN(type, val, size) ((type)((size_t)(val) - (size_t)(val) % (size_t)(size)))

/* Integer ceil(a/b) macro */
#define INTCEIL(a, b) (((a) + (b) - 1) / (b))

/* Value used to represent an error */
#define SIZE_T_ERROR ((size_t)(-1))

/* Kernel-space assert */
#define kernel_assert(expr) \
    do { \
        if (!(expr)) { \
            kernel_assert_fail(#expr, __FILE__, __LINE__); \
        } \
    } while (0)
extern NORETURN void kernel_assert_fail(const char *expr, const char *filename, int lineno);

#endif /* end of include guard: LIBKC_KCDEFINES_H */
