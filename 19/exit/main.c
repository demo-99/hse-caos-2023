#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Text\n");
    // Will print 'Text'
    // exit(0);
    // Will not print 'Text'
    _exit(0);
}
