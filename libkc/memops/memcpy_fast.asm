section .text
global memcpy_fast

memcpy_fast:
    push ebp
    push ebx
    
    mov edi, [esp + 12]
    mov esi, [esp + 16]
    mov edx, [esp + 20]

.loop0_begin:
    test edx, edx
    jz memcpy_fast.loop0_end

    sub edx, 16

    mov eax, [esi]
    mov ebx, [esi + 4]
    mov ecx, [esi + 8]
    mov ebp, [esi + 12]

    mov [edi], eax
    mov [edi + 4], ebx
    mov [edi + 8], ecx
    mov [edi + 12], ebp

    add esi, 16
    add edi, 16

    jmp memcpy_fast.loop0_begin

.loop0_end:
    pop ebx
    pop ebp
    ret
