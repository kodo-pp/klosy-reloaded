#ifndef LIBKC_MEMOPS_H
#define LIBKC_MEMOPS_H

/*
 * Memory operations. Some of them are the same as functions in native libc, but
 * there may be some changes
 */

/** Fills each byte of specified memory range with fill & 0xFF */
void memset(void *begin, int fill, size_t length);

/** Copies length bytes from src to dest. dest must have enough space. dest ans src must not overlap */
void memcpy(void *dest, const void *src, size_t length);

/** Compares memory chunks. Returns -1 if a < b, 0 if a == b, 1 if a > b */
int memcmp(void *a, void *b, size_t length);

/** Copies length bytes from src to dest. dest must have enough space. dest ans src may overlap */
void memmove(void* dest, const void* src, size_t length);

#endif /* end of include guard: LIBKC_MEMOPS_H */
