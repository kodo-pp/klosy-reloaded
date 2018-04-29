.include "asmdefs.inc.s"

.section .text
.globl inb
.globl inw
.globl inl
.globl outb
.globl outw
.globl outl
.type inb,  @function
.type inw,  @function
.type inl,  @function
.type outb, @function
.type outw, @function
.type outl, @function

outb:
    cfbegin
    # %dx - port
    # %al - value
    load_arg 0, %edx
    load_arg 1, %eax
    outb %al, %dx
    cfend

outw:
    cfbegin
    # %dx - port
    # %ax - value
    load_arg 0, %edx
    load_arg 1, %eax
    outw %ax, %dx
    cfend

outl:
    cfbegin
    # %dx - port
    # %eax - value
    load_arg 0, %edx
    load_arg 1, %eax
    outl %eax, %dx
    cfend

inb:
    cfbegin
    # %dx - port
    # %al - value
    load_arg 0, %edx
    xor %eax, %eax
    inb %dx, %al
    cfend

inw:
    cfbegin
    # %dx - port
    # %ax - value
    load_arg 0, %edx
    xor %eax, %eax
    inw %dx, %ax
    cfend

inl:
    cfbegin
    # %dx - port
    # %eax - value
    load_arg 0, %edx
    xor %eax, %eax
    inl %dx, %eax
    cfend
