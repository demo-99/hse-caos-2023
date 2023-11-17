#include <stdio.h>

union IntChar {
    int number;
    char character;
};

// 63 00 00 00

int main() {
    union IntChar value;

    printf("Enter an integer: ");
    scanf("%d", &value.number);

    printf("The corresponding character is: %c\n", value.number);

    printf("%d\n", (int)*((char*)&value+0));
    printf("%d\n", (int)*((char*)&value+1));
    printf("%d\n", (int)*((char*)&value+2));
    printf("%d\n", (int)*((char*)&value+3));
}
