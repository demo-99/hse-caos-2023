#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

// Signal handler for the timer
void timer_handler(int signum) {
    printf("Timer triggered!\n");
}

int main() {
    time_t input_sec;
    long input_nsec;

    // Read the two integers from stdin
    if (scanf("%ld %ld", &input_sec, &input_nsec) != 2) {
        fprintf(stderr, "Failed to read input\n");
        return 1;
    }

    // Create a struct timespec with the input values
    struct timespec event_time;
    event_time.tv_sec = input_sec;
    event_time.tv_nsec = input_nsec;

    // Setup the timer
    struct sigevent sev;
    struct itimerspec its;
    timer_t timerid;
    struct sigaction sa;

    // Set up signal handler
    sa.sa_flags = SA_SIGINFO;
    sa.sa_handler = timer_handler;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGRTMIN, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    // Set up the sigevent structure
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = &timerid;

    // Create the timer
    if (timer_create(CLOCK_REALTIME, &sev, &timerid) == -1) {
        perror("timer_create");
        return 1;
    }

    // Set the timer to go off at the specified time
    its.it_value = event_time;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 0;

    if (timer_settime(timerid, TIMER_ABSTIME, &its, NULL) == -1) {
        perror("timer_settime");
        return 1;
    }

    // Wait for the timer to trigger
    printf("Waiting for the timer to trigger at %ld seconds and %ld nanoseconds.\n", input_sec, input_nsec);
    pause();

    return 0;
}
