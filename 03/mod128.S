.section .data
input_msg:      .asciz "Enter a number: "
greater_msg:    .int -1
less_msg:       .int 1
correct_msg:    .int 0

.section .bss
n:              .space 4
guess:          .space 4

.section .text
.global main

main:
    # Reading N
    call    readi32
    movl    %eax, n

    # Calculate z = N mod 128
    andl    $0x7F, n # kek

retry:
    # Reading guess
    call    readi32
    movl    %eax, guess

    # Comparing guess and N
    movl    n, %ecx
    movl    guess, %edx
    cmpl    %edx, %ecx

    # Printing output
    jl      less
    jg      greater

correct:
    call    writei32_correct
    jmp     _exit

greater:
    call    writei32_greater
    jmp     retry

less:
    call    writei32_less
    jmp     retry

writei32_correct:
    movl    correct_msg, %eax
    call    writei32
    ret

writei32_greater:
    movl    greater_msg, %eax
    call    writei32
    ret

writei32_less:
    movl    less_msg, %eax
    call    writei32
    ret

_exit:
    # Exit
    movl    $1, %eax
    xorl    %ebx, %ebx
    int     $0x80
