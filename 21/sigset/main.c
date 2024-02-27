#include <stdio.h>
#include <signal.h>

int main() {
    sigset_t set;

    // Create an empty signal set
    sigemptyset(&set);

    // Add SIGINT and SIGTERM to the set
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGTERM);

    // Check if SIGINT is a member of the set
    if(sigismember(&set, SIGINT)) {
        printf("SIGINT is a member of the set.\n");
    } else {
        printf("SIGINT is not a member of the set.\n");
    }

    // Check if SIGQUIT is a member of the set
    if(sigismember(&set, SIGQUIT)) {
        printf("SIGQUIT is a member of the set.\n");
    } else {
        printf("SIGQUIT is not a member of the set.\n");
    }

    // Remove SIGTERM from the set
    sigdelset(&set, SIGTERM);

    // Verify SIGTERM is removed
    if(!sigismember(&set, SIGTERM)) {
        printf("SIGTERM is successfully removed from the set.\n");
    } else {
        printf("SIGTERM is not removed from the set.\n");
    }

    return 0;
}
