#include <stdio.h>
#include "extern1.h"

extern int a, b;

int main() {
    a += b;
    printf("%d %d\n", a, b);

    printf("apply_operator(a, b, add): %d\n", apply_operation(add));
}
