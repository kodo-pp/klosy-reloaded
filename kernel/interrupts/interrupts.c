#include <stdint.h>
#include <stddef.h>
#include <kernel/interrupts.h>
#include <kernel/power.h>
#include <kernel/portio.h>
#include <kernel/tty.h>
#include <stdio.h>
#include <memops.h>

struct idt_entry IDT[IDT_SIZE];

struct idt_descriptor {
    uint16_t size;
    uint32_t offset;
} PACKED;

struct idt_entry make_idt_entry(uint32_t offset, UNUSED uint8_t dpl) {
    struct idt_entry entry;
    entry.offset_low      = (uint16_t)(offset & 0xFFFF);
    entry.selector        = 0x10; // FUCKING GRUB!!!! I COULDN'T SOLVE THIS PROBLEM FOR
                                  // A COUPLE OF MONTHS. AND WHAT IS IT? JUST FUCKING
                                  // 0x10 INSTEAD OF 0x8!!!
                                  // Ok, GRUB isn't guilty, but why do tutorials say it's 0x8?
    entry.always_zero     = 0;
    entry.type_attr       = 0x8E;
    entry.offset_high     = (uint16_t)((offset >> 16) & 0xFFFF);
    return entry;
}

extern void keyboard_int_handler(void);

void keyboard_handler(void) {
    write("A", 1);
}

void dummy_int_handler(void);

void init_keyboard_idt(void)
{
    IDT[0x21] = make_idt_entry((uint32_t)keyboard_int_handler, 0);
    IDT[0x21] = make_idt_entry((uint32_t)keyboard_int_handler, 0);

    /* Shitty timer */
    IDT[0x08] = make_idt_entry((uint32_t)dummy_int_handler, 0);
}

extern void load_idt(struct idt_descriptor *descr);

void init_interrupts(void)
{
    memset(IDT, 0, sizeof(IDT));
    init_keyboard_idt();

    /* Save masks */
    /*
    uint8_t mask1 = inb(0x21);
    uint8_t mask2 = inb(0xA1);
    */

    uint8_t mask1 = 0xFD;
    uint8_t mask2 = 0xFF;

    /* ICW1 - Initialization */
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    /* ICW2 - Remapping */
    const uint8_t offset1 = 0x20, offset2 = 0x28;
    outb(0x21, offset1);
    outb(0xA1, offset2);

    /* ICW3 */
    outb(0x21, 0x00);
    outb(0xA1, 0x00);

    /* ICW 4 */
    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    /* Restore masks */
    outb(0x21, mask1);
    outb(0xA1, mask2);

    struct idt_descriptor descr;
    descr.size = IDT_SIZE * sizeof(struct idt_entry) - 1;
    descr.offset = (uint32_t)&IDT;
    load_idt(&descr);


    printf("sizeof(struct idt_descriptor) == %d\n", (int)sizeof(struct idt_descriptor));
    printf("keyboard_int_handler = 0x%p\n", keyboard_int_handler);
    printf("keyboard_handler = 0x%p\n", keyboard_handler);
    printf("IDT = 0x%p\n", IDT);
    printf("&descr = 0x%p\n", &descr);
    printf("IDT[0x21].offset = hi:0x%x lo:0x%x\n", (unsigned int)IDT[0x21].offset_high, (unsigned int)IDT[0x21].offset_low);
    printf("IDT[0x21].selector = 0x%x\n", (unsigned int)IDT[0x21].selector);
    printf("IDT[0x21].type_attr = 0x%x\n", (unsigned int)IDT[0x21].type_attr);
    printf("descr.size = %d\n", descr.size);
    printf("descr.offset = 0x%x\n", descr.offset);
    /*halt();*/
    asm volatile("sti\n\t");
    asm volatile("int $0x21\n\t");
    printf("BBB\n");
    halt();
    return;
}
