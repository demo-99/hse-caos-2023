#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main() {
    const char *filePath = "sample.txt";
    int fd = open(filePath, O_RDONLY);

    if (fd < 0) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        close(fd);
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        // Move to the beginning of the second line
        lseek(fd, 14, SEEK_SET);

        char buffer[100];
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytes_read = read(fd, buffer, 99);
        if (bytes_read > 0) {
            printf("Child read: %s", buffer);
        } else {
            perror("Child failed to read");
        }
        printf("\n\n");
    } else { // Parent process
        wait(NULL); // Wait for the child to perform its read operation

        // Presuming the parent reads first from the beginning
        char buffer[100];
        memset(buffer, 0, sizeof(buffer)); // Clear the buffer
        ssize_t bytes_read = read(fd, buffer, 99); // Read up to 99 bytes
        if(bytes_read > 0) {
            printf("Parent read: %s", buffer);
        } else {
            perror("Parent failed to read");
        }
    }

    close(fd);
    return 0;
}
