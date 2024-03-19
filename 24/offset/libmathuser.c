#include <stdio.h>

extern int add(int a, int b);

void use_add() {
    int result = add(5, 3);
    printf("Addition result is %d\n", result);
}
