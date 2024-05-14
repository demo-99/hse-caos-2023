#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>
#include <string.h>

int main() {
    setlocale(LC_COLLATE, "en_US.UTF-8");
    char str1[] = "apple";
    char str2[] = "äpple";
    int result = strcoll(str1, str2);
    if (result < 0) {
        printf("In en_US.UTF-8 locale, '%s' comes before '%s'\n", str1, str2);
    } else if (result > 0) {
        printf("In en_US.UTF-8 locale, '%s' comes after '%s'\n", str1, str2);
    } else {
        printf("In en_US.UTF-8 locale, '%s' is equal to '%s'\n", str1, str2);
    }
}