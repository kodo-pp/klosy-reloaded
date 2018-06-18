#include <stdint.h>
#include <stddef.h>

#include <kernel/panic.h>
#include <kernel/power.h>
#include <kcdefines.h>

#include <kernel/vgatty.h> /* Some constants and defines, not functions */

/*
 * VGA terminal is assumed to be not ready for outputting, so we will write directly
 * to video memory
 */
NORETURN void early_boot_failure(char *message)
{
    char *heading =
        "********************************************************************************"
        "***                              BOOT FAILURE                                ***"
        "********************************************************************************";
    volatile uint16_t * video_ptr = (uint16_t *)0xB8000;
    for (size_t i = 0; i < VGA_HEIGHT * VGA_WIDTH; ++i) {
        *(video_ptr + i) = VGANFCHAR('\0');
    }
    size_t idx = 0;
    while (idx < VGA_HEIGHT * VGA_WIDTH && *heading != '\0') {
        *(video_ptr + idx) = VGANFCHAR(*heading);
        ++heading;
        ++idx;
    }
    while (idx < VGA_HEIGHT * VGA_WIDTH && *message != '\0') {
        *(video_ptr + idx) = VGANFCHAR(*message);
        ++message;
        ++idx;
    }
    halt();
}
