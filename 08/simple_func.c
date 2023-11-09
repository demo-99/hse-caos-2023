#include <stdio.h>

int apply_operation(int a, int b, int(*operation)(int, int)) {
    return operation(a, b);
}

int add(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

int main() {
    int a = 10;
    int b = 20;

    int(*ptr_func)(int, int);

    ptr_func = &add;

    printf("%d\n", apply_operation(a, b, ptr_func));

    ptr_func = &sub

    printf("%d\n", apply_operation(a, b, ptr_func));
}
