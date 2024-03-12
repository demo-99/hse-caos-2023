#include <stdio.h>

unsigned long long int factorial(int n) {
    if (n == 0)
        return 1;
    else
        return n * factorial(n - 1);
}

int main() {
    int number;
    unsigned long long int result;

    printf("Enter a non-negative integer: ");
    scanf("%d", &number);

    if (number < 0) {
        printf("Factorial of a negative number doesn't exist.\n");
    } else {
        result = factorial(number);
        printf("Factorial of %d = %llu\n", number, result);
    }

    return 0;
}
