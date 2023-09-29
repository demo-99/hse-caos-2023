.section .data
jumptable:
    .long func1
    .long func2
    .long func3

format_string:
    .string "%d\n"

scan_format:
    .string "%d"

.section .text
.global main

main:
    # Load the index from terminal
    addl $4, %esp
    pushl n
    pushl $scan_format
    call scanf

    movl (%esp, 4, -3), %eax

    # Multiply index by 4 (size of a 32-bit pointer) to get the correct offset in the jump table
    shll $2, %eax

    # Add the jump table base address to the index offset
    addl $jumptable, %eax

    # Load the address of the function into the %eax register
    movl (%eax), %eax

    # Call the function through the address stored in the %eax register
    call *%eax

    addl $8, %esp
    xorl %eax, %eax
    ret

func1:
    pushl $1
    pushl $format_string
    call printf
    addl $8, %esp
    ret

func2:
    pushl $2
    pushl $format_string
    call printf
    addl $8, %esp
    ret

func3:
    pushl $3
    pushl $format_string
    call printf
    addl $8, %esp
    ret
