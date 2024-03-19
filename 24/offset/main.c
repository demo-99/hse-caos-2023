#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main() {
    void *handle = dlopen("./libmathuser.so", RTLD_LAZY);
    void (*use_add)() = (void (*)())dlsym(handle, "use_add");

    use_add();

    dlclose(handle);
}
