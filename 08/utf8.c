#include <stdio.h>

int main() {
    // A UTF-8 string containing the ASCII word "Hello" and an emoji (grinning face: U+1F600)
    char utf8_str[] = "Hello \xF0\x9F\x98\x80";

    // If we print the UTF-8 string using printf, the output will depend on your terminal or console's
    // ability to handle and display UTF-8 characters. If it supports and correctly interprets UTF-8,
    // the output will be "Hello 😃". Otherwise, it may not be able to display the emoji correctly.
    printf("UTF-8 string (using printf): %s\n", utf8_str);

    return 0;
}
