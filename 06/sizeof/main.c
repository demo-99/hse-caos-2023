#include <stdio.h>

int main()
{
    printf("sizeof(%s) is %ld\n", "long", sizeof(long));

    char c = 123;
    printf("%hhd\n", c);
    printf("%d\n", c);

    int i = 0x12345678;
    printf("%hhx\n", (char)i);
    printf("%x\n", i);
}
