#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

    pid_t p_fork;

    // Set buffer with some data
    // printf("Cached ");

    if ((p_fork = fork()) < 0) {
        printf("Failed...\n");
        exit(1);
    } else if (p_fork == 0) {
        sleep(1);
        printf("Child\n");
        exit(0);
    }

    wait(NULL);
    printf("Parent\n");

    return 0;
}
