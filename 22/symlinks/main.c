#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

// S_ISLNK()

void find_symlinks(const char *path) {
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

        if (lstat(fullpath, &statbuf) == -1) {
            perror("lstat");
            continue;
        }

        if (S_ISLNK(statbuf.st_mode)) {
            printf("Found symlink: %s\n", fullpath);
        } else if (S_ISDIR(statbuf.st_mode)) {
            find_symlinks(fullpath);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    find_symlinks(argv[1]);
    return 0;
}
