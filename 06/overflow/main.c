#include <stdio.h>
#include <limits.h>

int main()
{
    int i = INT_MAX + 1l;  // b10..0;
    printf("i: %d\n", i);
    printf("INT_MAX: %d\n", INT_MAX);

    unsigned max_uint = (unsigned)-1;
    printf("%u\n", max_uint);
    printf("%u\n", UINT_MAX);

    int n;
    scanf("%d", &n);
    int res = n + INT_MAX;
    printf("%d\n", res);
}
