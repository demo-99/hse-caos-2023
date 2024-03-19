#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fibonacci(int n) {
    if (n <= 1)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

void large_memory_operation(int size) {
    int *array = malloc(size * sizeof(int));
    if (!array) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    // Simulate some memory-bound operations
    for (int i = 0; i < size; i++) {
        array[i] = i * i;
    }
    free(array);
}

int main() {
    printf("Starting CPU-bound Fibonacci calculation...\n");
    int result = fibonacci(35);
    printf("Fibonacci result: %d\n", result);

    printf("Starting memory-bound operation...\n");
    large_memory_operation(10000000);

    return 0;
}
