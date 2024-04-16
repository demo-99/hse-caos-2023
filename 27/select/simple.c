#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>

int main() {
    fd_set readfds;
    struct timeval tv;
    int ret;

    // Clear the set ahead of time
    FD_ZERO(&readfds);

    // Add our descriptor to the set
    FD_SET(STDIN_FILENO, &readfds);

    // Wait up to five seconds.
    tv.tv_sec = 5;
    tv.tv_usec = 0;

    // Wait for input on stdin
    ret = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);

    if (ret == -1) {
        perror("select");
        return 1;
    } else if (ret) {
        printf("Data is available now.\n");
    } else {
        printf("No data within five seconds.\n");
    }

    return 0;
}
