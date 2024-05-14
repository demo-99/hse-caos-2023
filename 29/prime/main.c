#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

unsigned long largest_prime = 0;

int is_prime(unsigned long num) {
    if (num < 2) return 0;
    for (unsigned long i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int main() {

}
