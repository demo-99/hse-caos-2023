.section .data
dividend: .long 2500
divisor:  .long 50
quotient: .long 0
remainder: .long 0

.section .text
.global main
main:

    movl dividend, %eax # Load the dividend into %eax
    xorl %edx, %edx      # Zero out %edx for the upper 32 bits of dividend

    movl divisor, %ecx   # Load the divisor into %ecx
    divl %ecx            # Divide %eax (with %edx:%eax as dividend) by %ecx

    # At this point:
    # %eax contains the quotient (50).
    # %edx contains the remainder (0).

    movl %eax, quotient  # Save quotient result
    movl %edx, remainder # Save remainder result

    call writei32

    call finish