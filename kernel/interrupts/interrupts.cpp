#include <stdint.h>
#include <stddef.h>
#include <kernel/interrupts.h>
#include <kernel/power.h>
#include <kernel/portio.h>
#include <kernel/tty.h>
#include <stdio.h>
#include <memops.h>
#include <kcdefines.h>

struct idt_entry IDT[IDT_SIZE];

struct idt_descriptor {
    uint16_t size;
    uint32_t offset;
} __attribute__((packed));

extern "C" void load_idt(struct idt_descriptor* descr);

extern "C" void keyboard_int_handler(void);
extern "C" void dummy_int_handler(void);
extern "C" void fault_handler(void);

struct idt_entry make_idt_entry(uint32_t offset, UNUSED uint8_t dpl)
{
    struct idt_entry entry;
    entry.offset_low      = (uint16_t)(offset & 0xFFFF);
    entry.selector        = 0x10; /* FUCKING GRUB!!!! I COULDN'T SOLVE THIS PROBLEM FOR
                                   * A COUPLE OF MONTHS. AND WHAT IS IT? JUST FUCKING
                                   * 0x10 INSTEAD OF 0x8!!!
                                   * Ok, GRUB isn't guilty, but why do tutorials say it's 0x8?
                                   */
    entry.always_zero     = 0;
    entry.type_attr       = 0x8E;
    entry.offset_high     = (uint16_t)((offset >> 16) & 0xFFFF);
    return entry;
}

extern "C" void keyboard_handler(void)
{
    uint8_t scancode = inb(0x60);
    printf("Got scancode: %d\n", (int)scancode);
}

static void init_keyboard_idt(void)
{
    IDT[0x0D] = make_idt_entry((uint32_t)fault_handler, 0); /* GPF handler */
    IDT[0x21] = make_idt_entry((uint32_t)keyboard_int_handler, 0); /* Keyboard handler */
}

void init_interrupts(void)
{
    memset(IDT, 0, sizeof(IDT));
    init_keyboard_idt();

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

    /* ICW4 */
    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    uint8_t mask_master = 0x01;
    uint8_t mask_slave = 0xFF;

    /* Masking */
    outb(0x21, mask_master);
    outb(0xA1, mask_slave);

    /* Load IDT */
    struct idt_descriptor descr;
    descr.size = IDT_SIZE * sizeof(struct idt_entry) - 1;
    descr.offset = (uint32_t)&IDT;
    load_idt(&descr);

    /* Enable interrupts */
    asm volatile("sti\n\t");

    return;
}
