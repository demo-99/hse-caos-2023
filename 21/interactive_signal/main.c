#include <stdio.h>
#include <signal.h>
#include <unistd.h>


/*
    Пользователь определяет с помощью сигналов SIGUSR1 SIGUSR2 режим обработки stdin.
    SIGUSR1 - считываем число с stdin и печатаем его отрицательное значение. (дефолтное поведение)
    SIGUSR2 - считываем число с stdin и печатаем его квадрат.
    Исполняемся до тех пор пока scanf(%d) == 1
*/

volatile int mode = 1;

void sigusr_1_handler(int signal) {
    mode = 1;
}

void sigusr_2_handler(int signal) {
    mode = 2;
}



int main() {
    struct sigaction sa_1 = {
        .sa_handler = sigusr_1_handler,
        .sa_flags = SA_RESTART
    };

    struct sigaction sa_2 = {
        .sa_handler = sigusr_2_handler,
        .sa_flags = SA_RESTART
    };

    if (sigaction(SIGUSR1, &sa_1, NULL) == -1) {
        printf("Sigaction error\n");
        return 1;
    }

    if (sigaction(SIGUSR2, &sa_2, NULL) == -1) {
        printf("Sigaction error\n");
        return 1;
    }

    int number = 0;
    while (scanf("%d", &number) == 1) {
        if (mode == 1) {
            printf("%d\n", -number);
            fflush(stdout);
        } else {
            printf("%d\n", number * number);
            fflush(stdout);
        }
    }

    return 0;
}
