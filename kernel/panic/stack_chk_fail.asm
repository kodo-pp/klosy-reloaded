section .rodata
global __stack_chk_guard
__stack_chk_guard dd 0xef6dd59b

section .text
extern halt
global __stack_chk_fail
__stack_chk_fail:
    call halt
