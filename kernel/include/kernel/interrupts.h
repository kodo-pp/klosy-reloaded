#ifndef KERNEL_INTERRUPTS_H
#define KERNEL_INTERRUPTS_H

#include <stdint.h>
#include <stddef.h>
#include <kcdefines.h>

#define IDT_SIZE 256

struct idt_entry {
    /* Low 16 bits of offset */
    uint16_t offset_low;
    /* Code segment selector */
    uint16_t selector;
    /* Zero */
    uint8_t  always_zero;

    /* Attributes */
    uint8_t type_attr;

    /* High 16 bits of offset */
    uint16_t offset_high;
} PACKED;

struct idt_entry make_idt_entry(uint32_t offset, uint8_t dpl);

extern struct idt_entry IDT[IDT_SIZE];

void init_interrupts(void);

#endif /* end of include guard: KERNEL_INTERRUPTS_H */
