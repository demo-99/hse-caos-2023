#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints = {};
    struct addrinfo* res;

    if (argc != 3) {
        printf("%s usage: host service\n", argv[0]);
        return 1;
    }

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int err = getaddrinfo(argv[1], argv[2], &hints, &res);

    if (err) {
        printf("getaddrinfo err: %s\n", gai_strerror(err));

        return 0;
    }

    struct addrinfo *rp;

    for (rp = res; rp != NULL; rp = rp->ai_next) {
        struct sockaddr_in* ain = (struct sockaddr_in*) rp->ai_addr;
        printf("address: %s\n", inet_ntoa(ain->sin_addr));

        int sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1) {
            continue;
        }

        if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1) {
            char buf[] = "abc\n";
            write(sfd, buf, sizeof(buf));
            close(sfd);
            break;
        }

        close(sfd);
    }

    freeaddrinfo(res);
}
