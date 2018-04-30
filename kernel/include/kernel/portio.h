#ifndef KERNEL_PORTIO_H
#define KERNEL_PORTIO_H

#include <stdint.h>

/* Wrappers of assembly instructions in and out with different operand length */

void outb(uint16_t port, uint8_t  val);
void outw(uint16_t port, uint16_t val);
void outl(uint16_t port, uint32_t val);

uint8_t  inb(uint16_t port);
uint16_t inw(uint16_t port);
uint32_t inl(uint16_t port);

#endif /* end of include guard: KERNEL_PORTIO_H */
