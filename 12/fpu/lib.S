.text

.global sqrt

sqrt:
    pushl %ebp
    movl %esp, %ebp
    fldl 8(%ebp)
    fsqrt

    popl %ebp
    ret

.global mul

mul:
    pushl %ebp
    movl %esp, %ebp
    fldt 8(%ebp)
    fldt 20(%ebp)
    fmul %st(1), %st(0)
    popl %ebp
    ret

.global compute

compute:
    pushl %ebp
    movl %esp, %ebp

    flds 8(%ebp)
    fmuls 8(%ebp) # st(0) = a * a

    # fldt 12(%ebp)
    fadds 12(%ebp)

    popl %ebp
    ret
