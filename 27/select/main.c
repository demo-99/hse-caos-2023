#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#define MAXBUF 1024

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
    fd_set readfds;
    char buffer[MAXBUF];
    int max_sd, activity;
    struct timeval tv;

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(sock1, &readfds);
        FD_SET(sock2, &readfds);
        max_sd = (sock1 > sock2) ? sock1 : sock2;

        // Set timeout to NULL for blocking indefinitely
        tv.tv_sec = 5;
        tv.tv_usec = 0;

        activity = select(max_sd + 1, &readfds, NULL, NULL, &tv);

        if ((activity < 0) && (errno != EINTR)) {  // EINTR means that we should retry
            printf("select error");
        }

        if (FD_ISSET(sock1, &readfds)) {
            int bytes_read = read(sock1, buffer, sizeof(buffer));
            if (bytes_read <= 0) {
                close(sock1);
                printf("Socket 1 closed\n");
                break;
            }
            buffer[bytes_read] = '\0';
            printf("Received on socket 1: %s\n", buffer);
        }

        if (FD_ISSET(sock2, &readfds)) {
            int bytes_read = read(sock2, buffer, sizeof(buffer));
            if (bytes_read <= 0) {
                close(sock2);
                printf("Socket 2 closed\n");
                break;
            }
            buffer[bytes_read] = '\0';
            printf("Received on socket 2: %s\n", buffer);
        }
    }

    // Close sockets and end program
    close(sock1);
    close(sock2);
    return 0;
}
