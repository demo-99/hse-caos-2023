#include <stdio.h>

int a = 10;
int b = 20;

int apply_operation(int(*operation)(int, int)) {
    return operation(a, b);
}

int add() {
    return a + b;
}

int sub() {
    return a - b;
}
