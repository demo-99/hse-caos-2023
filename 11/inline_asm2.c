#include <stdio.h>
#include <stdint.h>

void swap(int32_t* a, int32_t* b) {
    asm( "movl (%%rax), %%ecx;"
         "movl (%%rbx), %%edx;"
         "movl %%edx, (%%rax);"
         "movl %%ecx, (%%rbx);"
            :
            : "a"(a), "b"(b)
            : "%ecx", "%edx"
            );
}

int main() {
    int32_t a = 10;
    int32_t b = 20;

    printf("Before swap a=%d b=%d", a, b);
    swap(&a, &b);
    printf("\nSwapped a=%d b=%d\n", a, b);
}
