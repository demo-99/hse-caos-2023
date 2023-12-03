.section .data
    value_single: .float 1.5   # Single precision float value
    value_double: .double 2.5  # Double precision float value

.section .text
    .global main

main:
    # Load constants onto the stack
    fld1                # Load constant 1.0 onto the stack
    fldz                # Load constant 0.0 onto the stack
    fldl2t              # Load log2(10) onto the stack

    # Load values onto the stack
    flds value_single   # Load single precision float value
    fldl value_double   # Load double precision float value

    # Arithmetic operations with st(0) register and memory operands
    fadd %st(1), %st(0)    # Add st(1) to st(0)
    fadd value_single    # Add memory to st(0)
    fmul %st(1), %st    # Multiply st(1) by st(0)
    fmul value_double    # Multiply memory by st(0)
    fsubr value_single   # Reverse subtract st(0) from memory
    fdiv %st(1), %st    # Divide st(0) by st(1)
    fdivr value_double   # Reverse divide memory by st(0)

    # Arithmetic operations with FADDS, FADDL (memory operands)
    fadds value_single  # Add single-precision value (memory) to st(0)
    faddl value_double  # Add double-precision value (memory) to st(0)

    # Comparison operations with different arguments
    fucom %st(3)        # Unordered compare st(0) with st(3)
    fucomi %st(2)       # Unordered compare st(0) with st(2) and set EFLAGS

    # Transcendental operations
    fsin                # Calculate the sine of st(0)
    fcos                # Calculate the cosine of st(0)
    fptan               # Calculate the partial tangent of st(0)

    # Stack management
    ffree %st(3)        # Free st(3)
    fincstp             # Increment the stack top pointer
    fdecstp             # Decrement the stack top pointer

    ret
