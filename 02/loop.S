    .global main
main:
    call readi32
_loop:
    dec %eax
    call writei32
    test %eax, %eax
    jnz _loop
    call finish