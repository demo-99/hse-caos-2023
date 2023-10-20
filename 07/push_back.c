#include <stdio.h>
#include <stdlib.h>

int REALLOC_COUNT = 0;
int CAPACITY = 0;

int* push_back(int* arr, int* size, int elem) {
    // Reallocate the array with one more element
    if (CAPACITY <= *size) {
        REALLOC_COUNT += 1;
        CAPACITY = *size * 2 + 1;
        int* new_arr = realloc(arr, CAPACITY * sizeof(int));
        if (!new_arr) { // NULL == false
            // Allocation failed, return NULL to indicate an error
            return NULL;
        }

        arr = new_arr;
    }

    // Append the element to the end of the array
    arr[*size] = elem;

    // Update the size variable
    *size = *size + 1;

    // Return the new array
    return arr;
}

int main() {
    int* arr = NULL;
    int size = 0;

    arr = push_back(arr, &size, 1);

    for (int i = 0; i < 10000000; ++i) {
        arr = push_back(arr, &size, 1);
    }

    printf("%d\n", REALLOC_COUNT);

    // for (int i = 0; i < size; i++) {
    //     printf("%d ", arr[i]);
    // }

    // printf("\n");

    return 0;
}