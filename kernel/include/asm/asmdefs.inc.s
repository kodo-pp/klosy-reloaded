.macro load_arg argn=0, dest=%eax method=mov
\method (4*\argn+8)(%ebp), \dest
.endm

.macro cfbegin
push %ebp
mov %esp, %ebp
push %ebx
.endm

.macro cfend
pop %ebx
mov %ebp, %esp
pop %ebp
ret
.endm
