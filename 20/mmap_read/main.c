#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Wrong amount of arguments\n");
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        printf("Couldn't open file\n");
        return 1;
    }

    size_t sz;
    struct stat fileInfo;
    if (fstat(fd, &fileInfo) == -1) {
        printf("fstat failed\n");
        return 1;
    }

    sz = fileInfo.st_size;

    uint64_t* data = mmap(NULL, sz, PROT_READ, MAP_SHARED, fd, 0);
    if (!data) {
        printf("failed mmap\n");
        return 1;
    }

    uint64_t sum = 0;
    uint64_t cnt = sz / sizeof(uint64_t);

    for (size_t i = 0; i < cnt; ++i) {
        sum += data[i];
    }

    printf("Result: %f\n", (double)sum / cnt);

    munmap(data, sz);
    close(fd);
}
