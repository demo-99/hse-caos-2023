#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

int main() {
    setlocale(LC_CTYPE, "en_US.UTF-8"); // Set the locale to handle UTF-8 input

    FILE *input = fopen("input.txt", "r");
    if (input == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }
    FILE *output = fopen("filtered.txt", "w");
    if (output == NULL) {
        perror("Error opening output file");
        fclose(input);
        return EXIT_FAILURE;
    }

    wint_t ch;
    while ((ch = fgetwc(input)) != WEOF) {
        if (iswspace(ch) || (L'А' <= ch && ch <= L'я')) {
            fputwc(ch, output);
        }
    }

    fclose(input);
    fclose(output);
}