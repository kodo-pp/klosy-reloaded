#include <kernel/fs/tar.h>
#include <vector.hpp>
#include <memops.h>

void ustar_ls(void* tarball, size_t max_size, kstd::vector < kstd::string >& dest)
{
    kernel_assert(sizeof (struct ustar_file) == 512);
    struct ustar_file buf;
    dest.resize(0);

    for (size_t i = 0; i < max_size; /* */) {
        memcpy(&buf, static_cast <struct ustar_file*> (tarball) + i, sizeof(buf));
        kstd::string magic(buf->ustar_magic, 6);
        kstd::string correct_magic("ustar\0", 6);
        if (magic != correct_magic) {
            printf("ustar_ls: error: ustar magic mismatch\n");
            return;
        }
    }
}

struct ustar_file* ustar_fileseek(void* tarball, const char* filename);
size_t ustar_read(struct ustar_file* file, void* buf, size_t offset, size_t length);

