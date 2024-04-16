#include <stdio.h>
#include <sys/epoll.h>
#include <unistd.h>

int main() {
    int epfd, nfds;
    struct epoll_event event, events[1];

    // Create an epoll instance
    epfd = epoll_create1(0);
    if (epfd == -1) {
        perror("epoll_create1");
        return 1;
    }

    // Setup epoll to watch for input on stdin
    event.events = EPOLLIN;
    event.data.fd = STDIN_FILENO;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event) == -1) {
        perror("epoll_ctl: STDIN_FILENO");
        return 1;
    }

    // Wait for events for five seconds
    nfds = epoll_wait(epfd, events, 1, 5000);

    if (nfds == -1) {
        perror("epoll_wait");
        return 1;
    } else if (nfds == 0) {
        printf("No data within five seconds.\n");
    } else {
        printf("Data is available now.\n");
    }

    close(epfd);
    return 0;
}
