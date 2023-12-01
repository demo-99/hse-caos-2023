.section .text
.global compute_function

compute_function:
    pushl %ebp                    # Save base pointer
    movl %esp, %ebp               # Establish stack frame

    # Load 'a' (first argument) from the stack into xmm0
    movss 8(%ebp), %xmm2          # Load single-precision 'a' into xmm0
    mulss %xmm2, %xmm2            # xmm0 *= xmm0 (a * a)

    # Load 'b' (second argument) from the stack into xmm1
    movss 12(%ebp), %xmm3         # Load single-precision 'b' into xmm1

    # Convert 'b' (xmm1) to double-precision before addition
    cvtss2sd %xmm3, %xmm1         # Convert single-precision 'b' to double-precision in xmm1

    # Convert 'a * a' (xmm0) to double-precision as well
    cvtss2sd %xmm2, %xmm0         # Convert single-precision 'a * a' to double-precision in xmm0

    # Perform addition of 'a * a' and 'b'
    addsd %xmm1, %xmm0            # Double-precision 'a * a' + double-precision 'b'

    # The result is now in xmm0, but we need to place this on the stack to return it
    subl $8, %esp                 # Allocate space for the double on the stack
    movsd %xmm0, (%esp)           # Store double-precision result on the stack

    fldl    (%esp)

    # Restore caller's stack frame
    movl %ebp, %esp               # Restore the stack pointer
    popl %ebp                     # Restore the base pointer

    ret                           # Return to caller with address of result in eax
