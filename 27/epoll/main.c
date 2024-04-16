#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAXBUF 1024
#define MAX_EVENTS 2

int create_connected_socket(int port) {
    int sockfd;
    struct sockaddr_in addr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Connection failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    return sockfd;
}

int main() {
    int sock1 = create_connected_socket(9998);
    int sock2 = create_connected_socket(9999);
    int epfd, nfds;
    struct epoll_event ev, events[MAX_EVENTS];

    // Create epoll instance
    if ((epfd = epoll_create1(0)) == -1) {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    // Add sock1 to epoll instance
    ev.events = EPOLLIN;
    ev.data.fd = sock1;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, sock1, &ev) == -1) {
        perror("epoll_ctl: sock1");
        exit(EXIT_FAILURE);
    }

    // Add sock2 to epoll instance
    ev.events = EPOLLIN;
    ev.data.fd = sock2;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, sock2, &ev) == -1) {
        perror("epoll_ctl: sock2");
        exit(EXIT_FAILURE);
    }

    // Buffer for incoming data
    char buffer[MAXBUF];

    // Event loop
    while (1) {
        nfds = epoll_wait(epfd, events, MAX_EVENTS, 5000); // Timeout of 5000 milliseconds

        if (nfds == -1) {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }

        for (int n = 0; n < nfds; ++n) {
            int bytes_read = read(events[n].data.fd, buffer, MAXBUF);
            if (bytes_read <= 0) {
                printf("Socket %d closed\n", events[n].data.fd);
                close(events[n].data.fd);
                exit(EXIT_FAILURE);
            } else {
                buffer[bytes_read] = '\0';
                printf("Received on socket %d: %s\n", events[n].data.fd, buffer);
            }
        }

        if (nfds == 0)
            printf("Timeout occurred! No data within 5 seconds.\n");
    }

    close(epfd);
    close(sock1);
    close(sock2);
    return 0;
}
