#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile int sigint_count = 0;

void handle_sigint(int sig) {
    sigint_count++;
    printf("SIGINT received, but still waiting. Count = %d\n", sigint_count);
}

void handle_sigalrm(int sig) {
    printf("SIGALRM handler\n");
    fflush(stdout);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <seconds>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int timer_duration = atoi(argv[1]);
    struct sigaction sa_int, sa_alrm;

    // Setup SIGINT handler
    sa_int.sa_handler = handle_sigint;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = SA_RESTART;
    if (sigaction(SIGINT, &sa_int, NULL) == -1) {
        perror("sigaction SIGINT");
        exit(EXIT_FAILURE);
    }

    // Setup SIGALRM handler to enable use of alarm with sigsuspend
    sa_alrm.sa_handler = handle_sigalrm;
    sigemptyset(&sa_alrm.sa_mask);
    sa_alrm.sa_flags = SA_RESTART;
    if (sigaction(SIGALRM, &sa_alrm, NULL) == -1) {
        perror("sigaction SIGALRM");
        exit(EXIT_FAILURE);
    }

    // Block SIGALRM to set up for sigsuspend
    sigset_t alrm_mask, old_mask;
    sigemptyset(&alrm_mask);
    sigaddset(&alrm_mask, SIGINT);
    if (sigprocmask(SIG_BLOCK, &alrm_mask, &old_mask) == -1) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }

    alarm(timer_duration); // Start timer

    printf("Timer started for %d seconds. Press Ctrl+C to send SIGINT.\n", timer_duration);

    // Temporarily replace current signal mask with the old one, allowing SIGALRM to interrupt sigsuspend
    while(1) {
        sigsuspend(&old_mask); // Wait here until a signal is caught

        // Check if the alarm went off
        if (sigismember(&alrm_mask, SIGALRM)) {
            break; // Exit loop if SIGALRM received
        }
    }

    printf("Timer completed. SIGINT was caught %d times.\n", sigint_count);

    return 0;
}
