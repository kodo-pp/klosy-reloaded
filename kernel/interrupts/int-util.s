.include "asmdefs.inc.s"

.section .data
fault_str:
    .ascii "Fault.\0"

.section .text
.globl keyboard_int_handler
keyboard_int_handler:
    pushf

    # Call C handler
    cld
    call keyboard_handler

    # send EOI
    mov $0x20, %al
    mov $0x20, %dx
    outb %al, %dx

    popf
    iret

.globl fault_handler
fault_handler:
    pushf
    cld

    push $fault_str
    call puts
    pop %eax

    mov $0x20, %al
    mov $0x20, %dx
    outb %al, %dx

    popf
    iret

.globl dummy_int_handler
dummy_int_handler:
    mov $0x20, %al
    mov $0x20, %dx
    outb %al, %dx

    iret


.globl load_idt
load_idt:
    mov 4(%esp), %edx
    lidt (%edx)
    ret
