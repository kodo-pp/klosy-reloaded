.include "asmdefs.inc.s"

.section .data
qwerty:
    .ascii "DEBUG: lidt (%%edx) @ %%edx = 0x%x\n\0"

.section .text
.globl keyboard_int_handler
keyboard_int_handler:
    # call halt
    pushf
    mov $0x20, %al
    mov $0x20, %dx
    outb %al, %dx
    cld
    call keyboard_handler
    popf
    iret

.globl dummy_int_handler
dummy_int_handler:
    mov $0x20, %al
    mov $0x20, %dx
    outb %al, %dx
    iret


# .globl load_idt
# .type load_idt, @function
# load_idt:
#     push %ebp
#     mov %esp, %ebp
#
#     # load_arg 1, %eax
#     mov 4(%esp)
#     lidt (%eax)
#
#     mov %ebp, %esp
#     pop %ebp
#     ret
#

.globl load_idt
load_idt:
    mov 4(%esp), %edx
    push %edx
    push $qwerty
    call printf
    pop %eax
    pop %eax
    mov 4(%esp), %edx
    lidt (%edx)
    ret
