#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    const size_t SIZE = 100 * 1024 * 1024; // 100 MiB
    char *data = (char*)malloc(SIZE);
    if (!data) {
        perror("malloc failed");
        return 1;
    }
    // Optional: Initialize the memory to force the OS to actually allocate it
    memset(data, 0, SIZE);
    printf("Memory allocated, press enter to fork...\n");
    getchar();

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        free(data);
        return 1;
    }

    if (pid == 0) {
        sleep(1);
        // Child: Optionally modify the data
        // memset(data, 43, SIZE); // Uncomment to see the effects of CoW
        printf("Child process, press enter to exit...\n");
        pid_t main_pid = getpid();
        pid_t ppid = getppid();

        printf("PID: %d\nPPID: %d\n", main_pid, ppid);
    } else {
        // Parent
        printf("Parent process, press enter to exit...\n");
        pid_t main_pid = getpid();
        pid_t ppid = getppid();

        printf("PID: %d\nPPID: %d\n", main_pid, ppid);
    }

    sleep(100);

    free(data);
    return 0;
}
