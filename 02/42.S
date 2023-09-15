    .global  main
main:
        mov     $42, %eax
        call    writei32
        call    finish
