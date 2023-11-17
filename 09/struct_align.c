#include <stdio.h>

struct A {
    long long c;
    short b;
    char a;
};

int main() {
    struct A a;
    printf("sizeof(struct A): %d\n", sizeof(struct A));

    printf("val a field: %d\n", a.a);

    *(char*)((void*)&a + 10) = 1;

    printf("val a field: %d\n", a.a);
}