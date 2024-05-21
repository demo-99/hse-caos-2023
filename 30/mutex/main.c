#include <stdio.h>
#include <pthread.h>

// Распечатать все числа от 0 до 10, но каждое число печатаеся в своем thread'е
// При этом нельяз дожидаться тредов по одному

int a;
pthread_mutex_t lock;

void* example(void* arg) {
    pthread_mutex_lock(&lock);
    printf("%d\n", a++);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    int idx = 0;
    pthread_t tid[11];
    for(int i = 0; i<11; i++) {
        pthread_create(&tid[i], NULL, example, &idx);
    }
    for (int i = 0; i < 11; i++) {
        pthread_join(tid[i], NULL);
    }
}