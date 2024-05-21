#include <stdio.h>
#include <pthread.h>

double arr[3];
#define ITER_COUNT 100000

// создать 3 треда:
//  0 - arr[0] += 100; arr[1] -= 101;
//  1 - arr[1] += 200; arr[2] -= 201;
//  2 - arr[2] += 300; arr[0] -= 301;
// Каждый тред должен отработать 100000
// после завершения всех тредов распечатать результат в main

int a;
// pthread_mutex_t lock;

void* change_0(void* arg) {
    for (int i = 0; i < ITER_COUNT; i++) {
        // pthread_mutex_lock(&lock);
        arr[0] += 100;
        arr[1] -= 101;
        // pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void* change_1(void* arg) {
    for (int i = 0; i < ITER_COUNT; i++) {
        // pthread_mutex_lock(&lock);
        arr[1] += 200;
        arr[2] -= 201;
        // pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void* change_2(void* arg) {
    for (int i = 0; i < ITER_COUNT; i++) {
        // pthread_mutex_lock(&lock);
        arr[2] += 300;
        arr[0] -= 301;
        // pthread_mutex_unlock(&lock);
    }
    return NULL;
}



int main() {
    int idx = 0;
    pthread_t tid[3];
    pthread_create(&tid[0], NULL, change_0, &idx);
    pthread_create(&tid[1], NULL, change_1, &idx);
    pthread_create(&tid[2], NULL, change_2, &idx);

    for (int i = 0; i < 3; i++) {
        pthread_join(tid[i], NULL);
    }

    for (int i = 0; i < 3; i++) {
        printf("%.2f\n", arr[i]);
    }
}