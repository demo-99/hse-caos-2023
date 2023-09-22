.section .text
.global process
process:
    push %ebp
    mov %esp, %ebp

    subl $1024, %esp
    movl $42, %eax
    call writei32

    mov %ebp, %esp
    pop %ebp

    ret

.global main
main:
    call process
    call finish
