#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include <stdio.h>
#include <convert.h>

#include <kernel/power.h>
#include <kernel/vgatty.h>
#include <kernel/portio.h>
#include <kernel/multiboot.h>
#include <kernel/init.h>
#include <kernel/memory.h>
#include <kernel/panic.h>

#include <vector.hpp>
#include <string.hpp>
#include <kernel/fs/tar.h>
#include <buffer.hpp>

#include <kernel/keyboard.hpp>

extern kstd::buffer <char> keyboard_buffer;

/**
 * Entry point to high-level part of kernel
 */
extern "C" void kmain(struct multiboot_info* mbt)
{
    /*init_modules(mbt);*/

    /* Print available memory size */
    printf("%sMemory information provided?%s ", "\x1b*0F", "\x1b*07");
    if (mbt->flags & 1) {
        printf("%syes%s\n", "\x1b*02", "\x1b*07");
    } else {
        printf("%sno%s\n", "\x1b*04", "\x1b*07");
        puts("Halting...");
        halt();
    }

    printf("%sLower memory:%s %z KiB\n", "\x1b*0F", "\x1b*07", (size_t)mbt->mem_lower);
    printf("%sUpper memory:%s %z MiB\n", "\x1b*0F", "\x1b*07", mbt->mem_upper >> 10);
    printf("%sMemory limit:%s %z MiB\n", "\x1b*0F", "\x1b*07", (mbt->mem_upper >> 10) + 1);
    puts("");

    printf("Modules count: %d\n", static_cast <int> (mbt->mods_count));
    printf("Modules addr : 0x%p\n", static_cast <size_t> (mbt->mods_addr));

    if (mbt->mods_count == 0) {
        printf("No modules are loaded :(\n");
    } else {
        printf("Yay! We can have our initrd!\n");
        auto mod_list = reinterpret_cast <struct multiboot_mod_list*> (mbt->mods_addr);
        printf("Initrd begins at 0x%p\n", mod_list[0].mod_start);
        printf("Initrd ends   at 0x%p\n", mod_list[0].mod_end);

        kstd::vector <kstd::string> files;
        ustar_ls(reinterpret_cast <void*> (mod_list[0].mod_start),
                 mod_list[0].mod_end - mod_list[0].mod_start,
                 files);
        for (size_t i = 0; i < files.length(); ++i) {
            printf("file: '%s'\n", files.at(i).c_str());
        }

        auto file = ustar_fileseek(reinterpret_cast <void*> (mod_list[0].mod_start),
                                   mod_list[0].mod_end - mod_list[0].mod_start,
                                   "some_file");
        printf("file = 0x%p\n", file);
        if (file == nullptr) {
            printf("Sorry, file not found :(\n");
        } else {
            kstd::string buf;
            ustar_read(file, buf);
            printf("File contents: '");
            write(buf.c_str(), buf.length());
            printf("'\n");
        }
    }

    printf("Testing %s24-bit%s %scolor%s\n", "\x1b#ABBA62!", "\x1b#471814!", "\x1b#205000.", "\x1b#222222.");
    printf("\x1b#000000.\x1b#FFFFFF!");

    puts("System initialized, awaiting for user input");
//    while (true) {
//        idle();
//    }
    
    while (true) {
        char ch;
        keyboard_buffer.read(&ch, 1);

        uint8_t scancode = static_cast <uint8_t> (ch);
        uint32_t key = key_translate(scancode);
        if ((key & NO_KEY) == 0) {
            char c = static_cast <char> (key);
            printf("%c", c);
        } else {
            if ((key & RELEASED) == 0) {
                //printf("unknown scancode: %u\n", scancode);
            }
        }
        keyboard_buffer.trim();
    }
}
