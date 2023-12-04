.global sum

sum:
    pushl %ebp               # Save old ebp
    movl %esp, %ebp          # Set up new ebp
    subl $8, %esp            # Allocate 8-byte space on stack for summing
    pxor %xmm0, %xmm0        # Initialize xmm0 to zero - this will store our result

    movl 8(%ebp), %eax       # Load address of the array into eax (arr)
    movl 12(%ebp), %ecx      # Load size into ecx (size)

.loop:
    movupd (%eax), %xmm1     # Load 2 doubles from array into xmm1
    addpd %xmm1, %xmm0       # Add xmm1 to xmm0
    addl $16, %eax           # Increment array pointer by 16 bytes to get the next two doubles
    subl $2, %ecx            # Decrement the count (we process 2 doubles each iteration)
    jnz .loop                # If count is not zero, loop again

    # Horizontally add the accumulated values in xmm0
    # movhlps %xmm0, %xmm1    # Move the high double of xmm0 to the low double of xmm1
    # addsd %xmm1, %xmm0      # Add low double of xmm1 (which is the high double of xmm0) to low double of xmm0
    haddpd %xmm0, %xmm0

    movsd %xmm0, (%esp)      # Store the result on the stack
    fldl (%esp)              # Load result from the stack into the FPU register st(0)

    addl $8, %esp            # Clean up stack
    movl %ebp, %esp          # Restore the stack pointer
    popl %ebp                # Restore base pointer
    ret                      # Return with the sum in st(0) in the x87 register
