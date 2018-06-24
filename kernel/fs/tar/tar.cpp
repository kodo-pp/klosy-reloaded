#include <kernel/fs/tar.h>
#include <vector.hpp>
#include <string.hpp>
#include <stdio.h>
#include <memops.h>
#include <convert.h>

static size_t ustar_filesize(const struct ustar_file& file)
{
    kstd::string size_str;
    for (size_t i = 0; i < 12; ++i) {
        char c = file.filesize[i];
        if ('0' <= c && c <= '7') {
            size_str.push_back(c);
        }
    }
    // printf("Final size_str: '%s'\n", size_str.c_str());

    size_t size = str_to_size_t_base(size_str.c_str(), 8);
    // printf("file size: %z\n", size);
    return size;
}

void ustar_ls(void* tarball, size_t max_size, kstd::vector < kstd::string >& dest)
{
    // Prepare
    struct ustar_file buf;

    // printf("max_size = %z\n", max_size);

    // Check the USTAR magic
    memcpy(&buf, static_cast <struct ustar_file*> (tarball), sizeof(buf));
    kstd::string magic(buf.ustar_magic, 5);
    kstd::string correct_magic("ustar", 5);
    if (magic != correct_magic) {
        printf("ustar_ls: error: ustar magic mismatch\n");
        printf("Expected: %x %x %x %x %x\n", 'u', 's', 't', 'a', 'r');
        printf("Got:      %x %x %x %x %x\n", magic.at(0), magic.at(1), magic.at(2), magic.at(3), magic.at(4));
        return;
    }

    // While we haven't overrun the tarball size
    for (size_t i = 0; i < max_size / sizeof(buf); /* */) {
        // Read the block
        memcpy(&buf, static_cast <struct ustar_file*> (tarball) + i, sizeof(buf));

        // printf("ustar_ls: i = %z\n", i);

        // Check the USTAR magic, if the check fails - the tarball has ended
        kstd::string magic(buf.ustar_magic, 5);
        kstd::string correct_magic("ustar", 5);
        if (magic != correct_magic) {
            return;
        }
        
        // Add the file name to the list
        dest.push_back(kstd::string(buf.filename_prefix) + kstd::string(buf.filename));

        // Go to the next header block:
        // Determine the file length in blocks
        auto blocks_count = (ustar_filesize(buf) + sizeof(buf) - 1) / sizeof(buf);
        // printf("blocks count: %z\n", blocks_count);
        // The next block is our [0]'th file block
        ++i;

        // And then we skip all file blocks
        i += blocks_count;
    }
}

struct ustar_file* ustar_fileseek(UNUSED void* tarball, UNUSED size_t max_size, UNUSED const kstd::string& filename)
{
    // Prepare
    struct ustar_file buf;

    // printf("max_size = %z\n", max_size);

    // Check the USTAR magic
    memcpy(&buf, static_cast <struct ustar_file*> (tarball), sizeof(buf));
    kstd::string magic(buf.ustar_magic, 5);
    kstd::string correct_magic("ustar", 5);
    if (magic != correct_magic) {
        printf("ustar_ls: error: ustar magic mismatch\n");
        printf("Expected: %x %x %x %x %x\n", 'u', 's', 't', 'a', 'r');
        printf("Got:      %x %x %x %x %x\n", magic.at(0), magic.at(1), magic.at(2), magic.at(3), magic.at(4));
        return nullptr;
    }

    // While we haven't overrun the tarball size
    for (size_t i = 0; i < max_size / sizeof(buf); /* */) {
        // Read the block
        memcpy(&buf, static_cast <struct ustar_file*> (tarball) + i, sizeof(buf));

        // printf("ustar_ls: i = %z\n", i);

        // Check the USTAR magic, if the check fails - the tarball has ended
        kstd::string magic(buf.ustar_magic, 5);
        kstd::string correct_magic("ustar", 5);
        if (magic != correct_magic) {
            return nullptr;
        }
        
        if (kstd::string(buf.filename_prefix) + kstd::string(buf.filename) == filename) {
            return static_cast <struct ustar_file*> (tarball) + i;
        }

        // Go to the next header block:
        // Determine the file length in blocks
        auto blocks_count = (ustar_filesize(buf) + sizeof(buf) - 1) / sizeof(buf);
        // printf("blocks count: %z\n", blocks_count);
        // The next block is our [0]'th file block
        ++i;

        // And then we skip all file blocks
        i += blocks_count;
    }
    return nullptr;
}

size_t ustar_read(UNUSED struct ustar_file* file, UNUSED kstd::string& buf)
{
    kernel_assert(file != nullptr);
    auto filedata = reinterpret_cast <char*> (file + 1);
    size_t filesize = ustar_filesize(*file);
    for (size_t i = 0; i < filesize; ++i) {
        buf.push_back(filedata[i]);
    }
    return filesize;
}

