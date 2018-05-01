#ifndef LIBKC_KCDEFINES
#define LIBKC_KCDEFINES

#define NORETURN __attribute__((noreturn))
#define UNUSED __attribute__((unused))

/* Aling non-negative value of arbitary integer or pointer type */
#define ALIGN(type, val, size) ((type)((size_t)(val) + (size_t)(size) - (size_t)1 - ((size_t)(val) + (size_t)(size) - (size_t)1) % (size_t)(size)))

/* The same as above, but if val % size != 0, then decrease val, not increase it */
#define ALIGN_DOWN(type, val, size) ((type)((size_t)(val) - (size_t)(val) % (size_t)(size)))

/* Integer ceil(a/b) macro */
#define INTCEIL(a, b) (((a) + (b) - 1) / (b))

/* Value used to represent an error */
#define SIZE_T_ERROR ((size_t)(-1))

#endif /* end of include guard: LIBKC_KCDEFINES */
