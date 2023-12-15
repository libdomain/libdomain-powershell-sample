// main.c
#include <stdio.h>
#include <dlfcn.h>

int main() {
    // Load the shared library
    void *handle = dlopen("./libdomain_wrapper.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }

    // Get the function pointer
    int (*get_root_dse)() = dlsym(handle, "get_root_dse");
    if (!get_root_dse) {
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle);
        return 1;
    }

    // Call the function from the shared library
    get_root_dse();

    // Unload the shared library
    dlclose(handle);

    return 0;
}

