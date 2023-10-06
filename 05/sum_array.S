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

    subl $4, %esp # резервируем память на стеке под перемнную, куда будем читать
    pushl %esp # кладем адрес зарезервираванной памяти
    pushl $scanf_format
    call scanf

    movl 8(%esp), %ecx
    movl %ecx, %ebx
    addl $12, %esp

    leal (, %ecx, 4), %eax
    subl %eax, %esp # reserved 4 * n memory on stack

_init:
    decl %ecx

    movl $0, (%esp, %ecx, 4)

    test %ecx, %ecx
    jnz _init

    movl %ebx, %ecx

_loop:
    decl %ecx

    leal (%esp, %ecx, 4), %esi

    pushl %ecx
    pushl %esi # кладем адрес зарезервираванной памяти
    pushl $scanf_format

    call scanf

    addl $8, %esp
    popl %ecx

    test %eax, %eax
    js _eof

    test %ecx, %ecx
    jnz _loop

_eof:

    movl %ebx, %ecx
    xorl %eax, %eax

_sum:
    decl %ecx

    addl (%esp, %ecx, 4), %eax

    test %ecx, %ecx
    jnz _sum

    pushl %eax
    pushl $printf_format
    call printf

    mov %ebp, %esp
    pop %ebp

    xorl %eax, %eax
    ret