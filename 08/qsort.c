#include <stdio.h>
#include <stdlib.h>

int compare_int(const void* a, const void* b) {
    int int_a = *((int*)a);
    int int_b = *((int*)b);

    if (int_a < int_b) {
        return -10;
    } else if (int_a > int_b) {
        return 1;
    }
    return 0;
}

int main() {
    int arr[] = {10, 3, -1, 50, 58, 111, 9};
    int length = sizeof(arr) / sizeof(int);

    printf("Before sorting: ");
    for (int i = 0; i < length; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    qsort(arr, length, sizeof(int), compare_int);

    printf("After sorting: ");
    for (int i = 0; i < length; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
