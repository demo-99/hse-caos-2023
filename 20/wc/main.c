#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

void count_lines(const char* file_path) {
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
