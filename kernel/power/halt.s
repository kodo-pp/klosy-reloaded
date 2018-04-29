.section .text
.globl halt
.type halt, @function
halt:
    cli
    hlt
    jmp halt
