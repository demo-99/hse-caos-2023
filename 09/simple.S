.section .data

printf_format:
    .string "%u\n"

.global main
.section .text
main:
    push %ebp                  # Save the base pointer
    mov %esp, %ebp             # Set the base pointer as the current stack pointer

    pushl %esp
    pushl $printf_format
    call printf

    addl $8, %esp

    pushw %ax
    pushw %ax
    pushw %ax
    pushw %ax

    addl $8, %esp

    pushl %esp
    pushl $printf_format
    call printf

    addl $8, %esp

    mov %ebp, %esp
    pop %ebp

    xorl %eax, %eax
    ret