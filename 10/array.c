#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 1024

// Function to generate a random float between min and max.
float random_float(float min, float max) {
    float random_value = (float)rand() / RAND_MAX;
    return min + random_value * (max - min);
}

int main() {
    float array[ARRAY_SIZE];
    srand(time(NULL));

    // Initialize the array with random float values between 0 and 1.
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = random_float(0.0f, 1.0f);
    }

    // Calculate the sum of the array elements as is.
    float original_sum = 0.0f;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        original_sum += array[i];
    }

    // TODO: YOUR CODE HERE

    float max_sum = 0.0f;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        max_sum += array[i];
    }

    printf("Original sum = %.15f\n", original_sum);
    printf("Max sum   = %.15f\n", max_sum);

    return 0;
}
