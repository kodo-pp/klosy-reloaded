#ifndef LIBKC_STRING_H
#define LIBKC_STRING_H

/*
 * String functions. Some of them are the same as functions in native libc, but
 * there may be some changes
 */

/* === STRING LENGTH === */

/** Returns the length of C-style string */
size_t strlen(const char *str);

/* === STRING MOVING AND COPYING === */

/**
 * Concatenates dest and src C-style strings. dest must have enough space
 * Returns length of the resulting string.
 */
size_t strcat(char *dest, const char *src);
/**
 * Same as above, but the resulting string will be at most lim chars long (not counting
 * zero-terminator)
 */
size_t strncat(size_t lim, char *dest, const char *src);

/**
* Copies a C-style string from src to dest. dest must have enough space.
* Returns the length of copied string.
*/
size_t strcpy(char *dest, const char *src);

/**
* Same as above, but copies no more than lim characters (not counting zero-terminator)
*/
size_t strncpy(size_t lim, char *dest, const char *src);

/* === STRING TRUNCATING === */

/**
 * If str is longer then len chars, truncate it to len chars, not counting zero-terminator)
 * Returns the length of the resulting string
 */
size_t strtrunc(size_t len, char *str);
/**
 * Same as above, O(1) complexity, does not check actual length
 */
size_t strtrunc_fast(size_t len, char *str);

/* === PATTERN FINDING === */

/**
 * Finds the first entry of the specified character and returns its index
 */
size_t strfindc(const char *str, char ch);
/**
 * Finds the first entry of the specified string and returns its index
 * [NOT IMPLEMENTED]
 */
size_t strfinds(const char *str, const char *pattern);

#endif /* end of include guard: LIBKC_STRING_H */
