#include <stdio.h>
#include <pthread.h>

// Дается поток чисел и каждое число читается в отдельном треде
// Используя только threads без массивов распечатать в обратном порядке

void* example(void* arg) {
    int x;
    if (scanf("%d", &x) == EOF) {
        return NULL;
    }
    pthread_t now;
    pthread_create(&now, NULL, example, NULL);
    pthread_join(now, NULL);
    printf("%d\n", x);

    return NULL;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, example, NULL);
    pthread_join(tid, NULL);
}
