
.section .bss
arr:    .space 40

.section .data
n:  .long  10

.section .text
.global main
main:

    movl n, %ecx

_loop:
    call readi32
    movl %ecx, %edx
    decl %edx
    movl %eax, arr(, %edx, 4) # *(arr + %edx * 4) = %eax

    loop _loop # decl ecx + jnz _loop

_print_loop:
    movl arr(, %ecx, 4), %eax
    call writei32

    inc %ecx
    cmpl n, %ecx
    jne _print_loop

    call finish