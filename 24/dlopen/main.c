#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main() {
    // Load the shared library
    void *handle = dlopen("./libexample.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return EXIT_FAILURE;
    }

    // Clear any existing error
    dlerror();

    // Retrieve the address of the hello function
    void (*hello)() = (void (*)())dlsym(handle, "hello");
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        fprintf(stderr, "Error: %s\n", dlsym_error);
        dlclose(handle);
        return EXIT_FAILURE;
    }

    // Call the function
    hello();

    // Close the library
    dlclose(handle);

    return EXIT_SUCCESS;
}
