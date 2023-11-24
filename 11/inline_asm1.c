#include <stdio.h>
#include <stdint.h>

int asm_sum(int a, int b) {
    int result;
    uint32_t my_sum;
    printf("my_sum addr: %u\n", my_sum);
    asm(
        ".globl my_sum\n"
        "my_sum:\n"
        "movl %%ebx, %%edx\n"
        "addl %%eax, %%edx\n"
        "movl my_sum, %%ecx"
        : "=d" (result), "=c"(my_sum)
        : "a" (a), "b" (b)
        :
    );

    printf("my_sum addr: %u\n", my_sum);

    return result;
}

int main() {
    int a = 10;
    int b = 20;
    printf("Sum a + b = %d\n", a + b);
    printf("Assembly sum a + b = %d\n", asm_sum(a, b));

    swap(&a, &b);
    printf("\nSwapped a=%d b=%d\n", a, b);
}
