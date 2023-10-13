#include <inttypes.h>
#include <stdio.h>

void mutate_memory() {
    char str[6];
    str[1] = 123;
    str[2] = 123;
    str[3] = 123;
    str[4] = 123;
    str[5] = 123;
    str[0] = 123;
    printf("%hhd\n", str[5]);
}

union Str
{
    int32_t n;
    char c[4];
};

int main()
{
    char c[] = "hello";

    mutate_memory();

    char str[6];
    str[0] = 'h';
    str[1] = 'e';
    str[2] = 'l';
    str[3] = 'l';
    str[4] = 'o';
    str[5] = '\0';  // str[5] = 0;

    int i = 0x1235678;

    printf("%s\n", str);

    union Str unified_str;
    unified_str.n = 0x00345678; // Due to little endian: c[0] = 0x78, c[1] = 0x56, c[2] = 0x34, c[3] = 0x00

    printf("%s\n", unified_str.c + 1);  //  +sizeof(char)
    printf("%s\n", (char*)(&unified_str.n + 1));  //  +sizeof(int)


    return 0;
}