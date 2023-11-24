#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 4096
#define NUM_TRIALS 100

int main() {
    int** arr = (int **)malloc(SIZE * sizeof(int*));
    for (int i = 0 ; i < SIZE; ++i) {
        arr[i] = (int*)malloc(SIZE * sizeof(int));
        for (int j = 0; j < SIZE; j++) {
            arr[i][j] = i + j;
        }
    }

    clock_t start, end;
    int sum;

    sum = 0;
    start = clock();
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            sum += arr[i][j];
        }
    }
    end = clock();
    printf("Seconds: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    sum = 0;
    start = clock();
    for (int j = 0; j < SIZE; ++j) {
        for (int i = 0; i < SIZE; ++i) {
            sum += arr[i][j];
        }
    }
    end = clock();
    printf("Seconds: %f\n", (double)(end - start) / CLOCKS_PER_SEC);
}