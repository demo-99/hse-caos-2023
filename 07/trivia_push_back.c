#include <stdio.h>
#include <stdlib.h>

int REALLOC_COUNT = 0;

int* push_back(int* arr, int* size, int elem) {
    // Reallocate the array with one more element
    int new_size = *size + 1;
    int* new_arr = realloc(arr, new_size * sizeof(int));
    if (!new_arr) { // NULL == false
        // Allocation failed, return NULL to indicate an error
        return NULL;
    }

    REALLOC_COUNT += 1;

    // Append the element to the end of the array
    new_arr[new_size - 1] = elem;

    // Update the size variable
    *size = new_size;

    // Return the new array
    return new_arr;
}

int main() {
    int* arr = NULL;
    int size = 0;

    arr = push_back(arr, &size, 1);
    printf("%lx\n", (long)arr);

    for (int i = 0; i < 10000000; ++i) {
        arr = push_back(arr, &size, 1);
    }

    printf("%lx\n", (long)arr);

    // for (int i = 0; i < size; i++) {
    //     printf("%d ", arr[i]);
    // }

    // printf("\n");

    return 0;
}