#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 9999

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address = {};
    int opt = 0;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        printf("socke error\n");
        return 0;
    }

    // force port ack
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        printf("setsockopt failed\n");
        return 0;
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr*)(&address), (socklen_t)(addrlen)) < 0) {
        printf("bind error\n");
        return 0;
    }

    if (listen(server_fd, 10) < 0) {
        printf("listen error\n");
        return 0;
    }

    if ((new_socket = accept(server_fd, (struct sockaddr*)(&address), (socklen_t*)(&addrlen))) < 0) {
        printf("accept error\n");
        return 0 ;
    }

    char buf[1024];
    memset(buf, 0, 1024);
    read(new_socket, buf, sizeof(buf));

    printf("Client: %s\n", buf);

    send(new_socket, buf, 1024, 0);
    printf("Message sent:\n");

    close(new_socket);
    close(server_fd);
}