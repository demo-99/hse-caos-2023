.data
    value: .double 42.0   # Define the constant value to compare against

.text
.global find_first_greater_than_42
find_first_greater_than_42:
    pushl %ebp                          # Save old base pointer
    movl %esp, %ebp                     # Establish new base pointer
    movl 8(%ebp), %eax                  # Load the array address into eax
    movl 12(%ebp), %ecx                 # Load the array size into ecx
    movlpd value, %xmm0                 # Load the value 42.0 into xmm0

    # Initialize index to -1, which means "not found"
    movl $-1, %edx                      # Holds the index of the first element greater than 42.0

    # Loop through each element of the array
.loop:
    testl %ecx, %ecx                    # Check if we've looped through the whole array
    jz .done                            # If ecx is zero, then we're done

    movlpd (%eax), %xmm1                # Load the next double in the array into xmm1
    ucomisd %xmm0, %xmm1                # Compare the value in xmm1 with 42.0 in xmm0
    jna .next                           # If xmm1 is not above (greater), skip to the next

    # If the comparison above set the "st" flag, we found our element
    # Calculate the index based on current pointers and exit loop
    subl 8(%ebp), %eax                  # Subtract the base address of the array from the current address
    shrl $3, %eax                       # Divide by 8 (sizeof(double)) to get the index
    movl %eax, %edx                     # Store the index in edx
    jmp .done                           # We found it, no need to search further

.next:
    addl $8, %eax                       # Move to the next double in the array
    decl %ecx                           # Decrement the counter
    jmp .loop                           # Repeat the loop

.done:
    movl %edx, %eax                     # Return the index (or -1 if not found) in eax
    movl %ebp, %esp                     # Clean up stack frame
    popl %ebp                           # Restore old base pointer
    ret
