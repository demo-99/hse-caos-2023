#include <stdio.h>
#include <unistd.h>

int main() {
    // Print using buffered stdout
    printf("Buffered (stdout): Start...");
    // setbuf(stdout, NULL);

    // Flush the output buffer to force printing the previous printf statement.
    // If you omit this line, the printing order of the buffered and unbuffered strings might not be as expected.
    // fflush(stdout);

    // Simulate processing time with a delay
    sleep(2);

    // Print using unbuffered stderr
    fprintf(stderr, "Unbuffered (stderr): Processing...\n");

    // Simulate more processing time with a delay
    sleep(2);

    // Print final message using buffered stdout
    printf("Buffered (stdout): Done.\n");

    return 0;
}