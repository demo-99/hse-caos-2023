.section .data
scanf_format:
    .string "%d"

printf_format:
    .string "%d\n"

.section .text
.global main
main:
    push %ebp
    mov %esp, %ebp

    pushl $2
    pushl $1
    pushl $0
    pushl $3
    call printn # Должно быть напечатано "0 1 2"

    mov %ebp, %esp
    pop %ebp

    xorl %eax, %eax
    ret

printn: # void printN(N, ...); sizeof(...) == N
    push %ebp
    mov %esp, %ebp

    movl 8(%ebp), %eax

    xorl %edx, %edx

_loop:
    incl %edx

    movl 8(%ebp, %edx, 4), %ecx

    pushl %eax
    pushl %edx
    pushl %ecx
    pushl $printf_format
    call printf
    addl $8, %esp
    popl %edx
    popl %eax

    cmpl %edx, %eax
    jne _loop

    mov %ebp, %esp
    pop %ebp

    ret
