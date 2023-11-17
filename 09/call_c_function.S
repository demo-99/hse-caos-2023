.section .text
.global main

main:
    push $42
    push $21

    call 😂

    add $8, %esp

    xorl %eax, %eax
    ret
