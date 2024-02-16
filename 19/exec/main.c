#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
    pid_t p_fork;
    if ((p_fork = fork()) < 0) {
        exit(1);
    } else if (p_fork == 0) {
        char * args[] = {"hello_world", NULL};
        execve("hello_world", args, NULL);
        exit(1);
    }

    int status;
    if (wait(&status) < 0 || !WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        printf("Child error: %d\n", WEXITSTATUS(status));
        exit(1);
    }
    exit(0);
}
