#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile int counter = 0;

void sigint_handler(int sig) {
    printf("handled SIGINT\n");
    printf("N = %d\n",++counter);
    fflush(stdout);

    sleep(4);

    if (counter == 5) {
        exit(0);
    }
}

void sigusr_1_handler(int signal) {
    printf("SIGUSR1 handler\n");
}

// Print pid to stdout and then handle SIGINT up to 5 times print sigint counter.

int main() {
    sigset_t set;
    sigemptyset(&set);

    sigaddset(&set, SIGUSR1);

    struct sigaction sa = {
        .sa_handler = sigint_handler,
        .sa_flags = SA_RESTART,
        .sa_mask = set
    };

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        printf("failed sigaction\n");
        return 1;
    }


    struct sigaction sa_1 = {
        .sa_handler = sigusr_1_handler,
        .sa_flags = SA_RESTART
    };

    if (sigaction(SIGUSR1, &sa_1, NULL) == -1) {
        printf("Sigaction error\n");
        return 1;
    }

    printf("%d\n", getpid());
    fflush(stdout);

    while(1) {
        pause();
    }
}
