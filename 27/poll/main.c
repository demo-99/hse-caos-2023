#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <unistd.h>
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
    struct pollfd fds[2];
    char buffer[MAXBUF];

    // Configure the pollfd structure
    fds[0].fd = sock1;
    fds[0].events = POLLIN;
    fds[1].fd = sock2;
    fds[1].events = POLLIN;

    while (1) {
        int ret = poll(fds, 2, 5000); // 5 seconds for timeout

        if (ret < 0) {
            perror("poll error");
            break;
        }

        if (ret == 0) {
            printf("Timeout occurred! No data within 5 seconds.\n");
            continue;
        }

        for (int i = 0; i < 2; i++) {
            if (fds[i].revents & POLLIN) {
                int bytes_read = read(fds[i].fd, buffer, MAXBUF);
                if (bytes_read <= 0) {
                    printf("Socket %d closed\n", i + 1);
                    close(fds[i].fd);
                } else {
                    buffer[bytes_read] = '\0';
                    printf("Received on socket %d: %s\n", i + 1, buffer);
                }
            }
        }
    }

    // Close sockets and end program
    close(sock1);
    close(sock2);

    return 0;
}
