#include <stdio.h>
#include <stdint.h>

double sum(double* arr, uint32_t size);

int main()
{
    double arr[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    printf("Sum: %lf\n", sum(arr, sizeof(arr) / sizeof(arr[0])));

    return 0;
}
