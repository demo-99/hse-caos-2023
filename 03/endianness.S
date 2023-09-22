.section .data
number: .long 0x12345678

.section .text
.globl main
main:

    # Loading the number into a register
    movl number, %eax

    # Swapping the endianness of the number
    bswap %eax

# Storing the swapped number
.section .bss
swapped_number: .space 4
.section .text

    movl %eax, (swapped_number)

    movb (swapped_number), %al

    call finish