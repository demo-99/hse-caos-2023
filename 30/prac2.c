#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

// Два треда:
// 0 - ищет простые числа начиная с 2
// 1 - печатает простое число как только у нас находится новое. После печати count простых чисел завершаем исполение
// count получаем с stdin
int counter = 0;
int count;
int latest_prime = 2;

bool need_increment = false;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

enum { THREADS_COUNT = 10 };
enum { ITERATIONS = 10000 };

bool is_prime(int num) {
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

void* producer(void* ptr) {
    int now = latest_prime;

    while (counter < count) {
        while (!is_prime(now)) {
            now++;
        }
        while (need_increment) {}
        pthread_mutex_lock(&mutex);
        latest_prime = now;
        need_increment = true;
        pthread_cond_signal(&cond);
        now++;
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void* consumer(void* ptr) {
    (void)ptr;
    pthread_mutex_lock(&mutex);
    while (counter < count) {
        while (!need_increment) {
            pthread_cond_wait(&cond, &mutex);
        }
        need_increment = false;
        ++counter;
        printf("New prime: %d\n", latest_prime);
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    scanf("%d", &count);
    pthread_t t1, t2;
    if (pthread_create(&t1, NULL, producer, NULL) != 0) {
        exit(1);
    }
    if (pthread_create(&t2, NULL, consumer, NULL) != 0) {
        exit(1);
    }
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}