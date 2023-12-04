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
