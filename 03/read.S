.global main
main:
    call readi32
    jnc main
    call finish
