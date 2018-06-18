%include "asmdefs.inc.asm"

section .text
global inb, inw, inl, outb, outw, outl

outb:
    push ebp
    mov ebp, esp

    mov edx, load_arg(0) ; dx is port
    mov eax, load_arg(1) ; al is value
    out dx, al

    mov esp, ebp
    pop ebp
    ret

outw:
    push ebp
    mov ebp, esp

    mov edx, load_arg(0) ; dx is port
    mov eax, load_arg(1) ; al is value
    out dx, ax

    mov esp, ebp
    pop ebp
    ret

outl:
    push ebp
    mov ebp, esp

    mov edx, load_arg(0) ; dx is port
    mov eax, load_arg(1) ; al is value
    out dx, eax

    mov esp, ebp
    pop ebp
    ret

inb:
    push ebp
    mov ebp, esp

    mov edx, load_arg(0)
    xor eax, eax
    in al, dx 

    mov esp, ebp
    pop ebp
    ret

inw:
    push ebp
    mov ebp, esp

    mov edx, load_arg(0)
    xor eax, eax
    in ax, dx 

    mov esp, ebp
    pop ebp
    ret

inl:
    push ebp
    mov ebp, esp

    mov edx, load_arg(0)
    xor eax, eax
    in eax, dx 

    mov esp, ebp
    pop ebp
    ret
