#include <stdio.h>
#include <pthread.h>

// Распечатать все числа от 0 до 10, но каждое число печатаеся в своем thread'е
// При этом нельяз дожидаться тредов по одному

int a;

void* example(void* arg) {
    int index = *(int*)arg;
    printf("%d\n", index);
    (*(int*)arg)++;
    return NULL;
}

int main() {
    int idx = 0;
    pthread_t tid;
    for(int i = 0; i<11; i++) {
        pthread_create(&tid, NULL, example, &idx);
    }
    sleep(100);
}