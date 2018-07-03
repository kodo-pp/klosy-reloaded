section .text

extern _c_vesa_real_fb
extern _c_vesa_virt_fb
extern _c_vesa_back_fb
extern _c_vesa_fblen

global vesa_flush_range
global vesa_flush_rect
global vesa_flush
global vesa_flush_all


vesa_flush:
    push ebx
    push esi
    push edi
    mov edi, [_c_vesa_real_fb]  ; real_framebuffer
    mov esi, [_c_vesa_virt_fb]  ; virtual_framebuffer
    mov eax, [_c_vesa_back_fb]  ; back_framebuffer
    mov edx, [_c_vesa_fblen]    ; framebuffer length
    mov edi, [edi]
    mov esi, [esi]
    mov eax, [eax]

    ; Main loop, ebx is temporary register
.loop_begin:
    test edx, edx
    jz .loop_end
    js .loop_end
    sub edx, 4

    mov ebx, [esi]
    cmp ebx, [eax]
    je .skip
    mov [edi], ebx
    mov [eax], ebx
.skip:

    add esi, 4
    add edi, 4
    add eax, 4

    jmp .loop_begin
.loop_end:
.fail:
    pop edi
    pop esi
    pop ebx
    ret

