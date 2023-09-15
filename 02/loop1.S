    .global main
main:
    call readi32
    xor %edx, %edx
_loop:
    ror %eax
    jc _skip_even
    rcl %eax
    add %eax, %edx
    jmp _continue
_skip_even:
    rcl %eax
_continue:
    dec %eax
    jnz _loop
    mov %edx, %eax
    call writei32
    call finish