%include "asmdefs.inc.asm"

extern keyboard_handler, puts

section .data
fault_str db `Fault.\0`

section .text
global keyboard_int_handler
keyboard_int_handler:
    pushf

    ; Call C handler
    cld
    call keyboard_handler

    ; send EOI
    mov al, 0x20
    mov dx, 0x20
    out dx, al

    popf
    iret

global fault_handler
fault_handler:
    pushf
    cld

    push fault_str
    call puts
    pop eax

    mov al, 0x20
    mov dx, 0x20
    out dx, al

    popf
    iret

global dummy_int_handler
dummy_int_handler:
    mov al, 0x20
    mov dx, 0x20
    out dx, al

    iret

global load_idt
load_idt:
    mov edx, [esp + 4]
    lidt [edx]
    ret
