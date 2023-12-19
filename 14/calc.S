.section .data
A:    .int  15
B:    .int  16
C:    .int  0

# C = A * 3 - B / 16

.section .text
.globl main
main:
    # YOUR CODE HERE

    movl C, %eax
    call writei32

    ret
