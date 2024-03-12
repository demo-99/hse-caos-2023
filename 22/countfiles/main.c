#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

void count_files_dirs(const char *path, int *file_count, int *dir_count) {
    DIR* dir;
    struct dirent *entry;
    struct stat statbuf;

    dir = opendir(path);
    if (!dir) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        if (stat(fullpath, &statbuf) == -1) {
            perror("stat");
            continue;
        }

        if (S_ISREG(statbuf.st_mode)) {
            ++(*file_count);
            printf("Found regular file: %s\n", fullpath);
        } else if (S_ISDIR(statbuf.st_mode)) {
            ++(*dir_count);
            printf("Found directory: %s\n", fullpath);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    int file_count = 0, dir_count = 0;
    count_files_dirs(argv[1], &file_count, &dir_count);

    printf("Regular files: %d\n", file_count);
    printf("Directories: %d\n", dir_count);

    return 0;
}
