#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef union {
    int intValue;
    char charValue[4];
} IntCharUnion;

void reverseBytes(IntCharUnion *element) {
    // YOUR CODE HERE
}

int main(int argc, char *argv[]) {
    // Check command-line arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <size_of_array>\n", argv[0]);
        return 1;
    }

    int size;
    IntCharUnion *array;
    // YOUR CODE HERE

    // Seed the random number generator
    srand((unsigned int)time(NULL));

    for (int i = 0; i < size; i++) {
        array[i].intValue = rand();
    }

    printf("Array before reverse:\n");
    for (int i = 0; i < size; i++) {
        printf("0x%X ", array[i].intValue);
    }
    printf("\n");

    for (int i = 0; i < size; i++) {
        reverseBytes(&array[i]);
    }

    printf("Array with bytes reversed:\n");
    for (int i = 0; i < size; i++) {
        printf("0x%X ", array[i].intValue);
    }
    printf("\n");

    free(array);

    return 0;
}
