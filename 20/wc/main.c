#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

void count_lines(const char* file_path) {
    int fd = open(file_path, O_RDONLY);
    if (fd == -1) {
        printf("Error opening file");
        return;
    }

    struct stat fileInfo;
    if (fstat(fd, &fileInfo) == -1) {
        printf("fstat failed\n");
        return;
    }
    if (fileInfo.st_size == 0) {
        printf("%s 0\n", file_path);
        return;
    }
    char* data = mmap(NULL, fileInfo.st_size, PROT_READ, MAP_SHARED, fd, 0);

    int count = 0;
    for(size_t i = 0; i < fileInfo.st_size; ++i) {
        if (data[i] == '\n') {
            ++count;
        }
    }
    if(data[fileInfo.st_size - 1] != '\n') {
        ++count;
    }
    printf("%s %d\n", file_path, count);

    munmap(data, fileInfo.st_size);
    close(fd);

    return;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file_path_1> <file_path_2> ... <file_path_N>\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        count_lines(argv[i]);
    }
}
