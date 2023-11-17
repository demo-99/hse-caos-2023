.section .data
scanf_format:
    .string "%d %d"

.section .text
.global main
main:
    push %ebp
    mov %esp, %ebp

    subl $8, %esp

    movl %esp, %eax
    pushl %eax
    addl $4, %eax
    pushl %eax
    pushl $scanf_format
    call scanf

    addl $12, %esp
    call 😂

    mov %ebp, %esp
    pop %ebp

    xorl %eax, %eax
    ret
