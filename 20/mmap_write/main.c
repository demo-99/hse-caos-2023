#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Usage: %s <num_rows> <num_cols> <file_path>\n", argv[0]);
        return 1;
    }

}
