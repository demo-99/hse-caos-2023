#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>

const char* str = "0123456789ABCDEF";

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Usage: %s <num_rows> <num_cols> <file_path>\n", argv[0]);
        return 1;
    }
    int row = atoi(argv[1]);
    int cols = atoi(argv[2]);
    int data = open(argv[3], O_CREAT | O_RDWR, S_IRUSR | S_IWUSR); // 0600

    size_t sz = row * cols * sizeof(uint64_t);

    if (ftruncate(data, sz) == -1) {
        printf("ftruncate failed\n");
        return 1;
    }

    uint64_t* list = mmap(NULL, sz, PROT_WRITE, MAP_SHARED, data, 0);
    for (int i = 0; i < row; ++i){
        for (int j = 0; j < cols; ++j) {
            list[i * row + j] = i * row + j;
        }
    }

    munmap(list, row *cols);
    close(data);
}
