#ifndef KERNEL_FS_TAR_H
#define KERNEL_FS_TAR_H

#include <stdint.h>
#include <stddef.h>
#include <vector.hpp>
#include <kcdefines.h>

struct ustar_file
{
    char filename[100];        // +0
    char filemode[8];          // +100
    char owner[8];             // +108
    char group[8];             // +116
    char filesize[12];         // +124
    char modtime[12];          // +136
    char checksum[8];          // +148
    char typeflag;             // +156
    char linked_filename[100]; // +157
    char ustar_magic[6];       // +257 | must be "ustar\0"
    char ustar_version[2];     // +263 | must be "00", but ignored
    char owner_name[32];       // +265
    char group_name[32];       // +297
    char dev_major[8];         // +329
    char dev_minor[8];         // +337
    char filename_prefix[155]; // +345
    // Used: 500 bytes
    // Padding: 12 bytes
    char padding[12];          // Padding, ignored
} PACKED;

void ustar_ls(void* tarball, kstd::vector < kstd::vector <char> >& dest);
struct ustar_file* ustar_fileseek(void* tarball, const char* filename);
size_t ustar_read(struct ustar_file* file, void* buf, size_t offset, size_t length);

#endif // end of include guard: KERNEL_FS_TAR_H

