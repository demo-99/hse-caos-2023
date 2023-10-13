#include <stdio.h>

int main()
{
    signed char c = 254;
    unsigned char uc = c;

    printf("unsigned char: %hhu, signed char: %hhi\n", uc, c);
}
