#include <stdio.h>
#include <poll.h>
#include <unistd.h>

int main() {
    struct pollfd fds[1];
    int ret;

    // Watch stdin (fd 0) to see when it has input.
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;

    // All set, now wait for five seconds
    ret = poll(fds, 1, 5000);

    if (ret == -1) {
        perror("poll");
        return 1;
    } else if (ret == 0) {
        printf("No data within five seconds.\n");
    } else {
        if (fds[0].revents & POLLIN)
            printf("Data is available now.\n");
    }

    return 0;
}
