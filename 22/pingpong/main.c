#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    int pipe_fd1[2], pipe_fd2[2]; // Two pipes: parent -> child, child -> parent
    pid_t pid;
    char buf[BUFFER_SIZE];
    int count = 5;  // Number of "ping-pong" exchanges

    // Create both pipes
    if (pipe(pipe_fd1) == -1 || pipe(pipe_fd2) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) { // Child process
        close(pipe_fd1[1]);
        close(pipe_fd2[0]);

        while(read(pipe_fd1[0], buf, BUFFER_SIZE) > 0) {
            printf("Child: received '%s'\n", buf);
            snprintf(buf, sizeof(buf), "pong %d", 5 - --count);
            write(pipe_fd2[1], buf, strlen(buf) + 1);
        }

        close(pipe_fd1[0]);
        close(pipe_fd2[1]);
    } else { // Parent process
        close(pipe_fd1[0]);
        close(pipe_fd2[1]);

        while(count--) {
            snprintf(buf, sizeof(buf), "ping %d", 5 - count);
            write(pipe_fd1[1], buf, strlen(buf) + 1);
            if (read(pipe_fd2[0], buf, BUFFER_SIZE) > 0) {
                printf("Parent: received '%s'\n", buf);
            }
        }

        close(pipe_fd1[1]);
        close(pipe_fd2[0]);
    }

    wait(NULL);

    return 0;
}
