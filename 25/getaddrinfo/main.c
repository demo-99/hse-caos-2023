#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int main() {
    struct addrinfo hints = {};
    struct addrinfo* res;

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int err = getaddrinfo("google.com", "erwfsddsfdfs", &hints, &res);

    if (err) {
        printf("getaddrinfo err: %s\n", gai_strerror(err));

        return 0;
    }

    struct addrinfo *result_iter = res;

    while(result_iter->ai_next) {
        struct sockaddr_in* ain = (struct sockaddr_in*) result_iter->ai_addr;
        printf("address: %s\n", inet_ntoa(ain->sin_addr));
        result_iter = result_iter->ai_next;
    }

    freeaddrinfo(res);
}