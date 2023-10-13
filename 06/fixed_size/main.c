#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define PRINT_SIZEOF(type) \
    printf("sizeof(%s) is %ld\n", #type, sizeof(type))

int main()
{
    PRINT_SIZEOF(int8_t);
    PRINT_SIZEOF(int16_t);
    PRINT_SIZEOF(int32_t);
    PRINT_SIZEOF(int64_t);
}
