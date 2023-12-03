#include <stdio.h>

int find_first_greater_than_42(double* arr, unsigned int size);

int main() {
    double array[] = { 35, 40, 45, 50, 55 };
    unsigned int size = sizeof(array) / sizeof(array[0]);

    int index = find_first_greater_than_42(array, size);
    if (index != -1) {
        printf("First element greater than 42.0: array[%d] = %f\n", index, array[index]);
    } else {
        printf("No elements greater than 42.0 found.\n");
    }

    return 0;
}
