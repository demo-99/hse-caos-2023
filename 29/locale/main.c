#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>
#include <string.h>

int main() {
    // Step 1: Set the locale to the user's default locale
    setlocale(LC_ALL, "");

    // Sample multibyte string
    char *mbstr = "àçéîõ1a";
    wchar_t wc;
    size_t len, mb_len = strlen(mbstr);
    int i = 0;

    while (mb_len > 0) {
        // Step 2: Convert the multibyte character to a wide character
        len = mbtowc(&wc, mbstr + i, mb_len);

        if (len < 0) {
            printf("Conversion error\n");
            return 1;
        }

        // Step 3: Determine if the wide character is alphabetic
        if (iswctype(wc, wctype("alpha"))) {
            wprintf(L"Character %lc is alphabetic\n", wc);
        } else {
            wprintf(L"Character %lc is not alphabetic\n", wc);
        }

        i += len;
        mb_len -= len;
    }

    return 0;
}
