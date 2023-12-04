#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int fin = open("text.txt", O_RDONLY);
    if (fin < 0) {
        printf("Cannot open file");
        return 1;
    }
    int fout = open("file", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fout < 0) {
        printf("Cannot open file");
        return 1;
    }

    off_t file_size; // TODO Write your code

    char buffer;
    while(file_size) {

    }

    close(fin);
    close(fout);
    return 0;
}
c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *source_path = argv[1];
    const char *dest_path = argv[2];

    // Open the source file for reading
    int src_fd = open(source_path, O_RDONLY);
    if (src_fd < 0) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // Open the destination file for writing
    int dest_fd = open(dest_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("Error opening destination file");
        close(src_fd);
        exit(EXIT_FAILURE);
    }

    // Get the size of the source file
    off_t file_size = lseek(src_fd, 0, SEEK_END);
    if (file_size == (off_t)-1) {
        perror("lseek error");
        close(src_fd);
        close(dest_fd);
        exit(EXIT_FAILURE);
    }

    // Reading from the end and writing to the destination file
    char buffer;
    while(file_size--) {
        if (lseek(src_fd, file_size, SEEK_SET) == (off_t)-1) {
            perror("lseek error");
            break;
        }
        if (read(src_fd, &buffer, 1) != 1) {
            perror("read error");
            break;
        }
        if (write(dest_fd, &buffer, 1) != 1) {
            perror("write error");
            break;
        }
    }

    // Close file descriptors
    close(src_fd);
    close(dest_fd);

    return 0;
}
