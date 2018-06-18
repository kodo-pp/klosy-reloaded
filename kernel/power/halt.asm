section .text
global halt

halt:
    cli
    hlt
    jmp halt
