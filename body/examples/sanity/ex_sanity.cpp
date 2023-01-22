#include <iostream>
#include <dlfcn.h>

int main () {

    // opening shared object file
    void* handle = dlopen("sanity.so", RTLD_LAZY);
    if (!handle) {
        std::cout << "Error retrieving shared object file: " << dlerror() << "\n";
        return 1;
    }

    // fetching function sanity from SO handle
    typedef void (*sanityF)();
    sanityF sanity = (sanityF) dlsym(handle, "_ZN8RESkelly6sanityEv");
    if (!sanity) {
        std::cout << "Error retrieving function address: " << dlerror() << "\n";
        dlclose(handle);
        return 1;
    }

    printf("Application sanity message reached. Proceeding to Skelly dynamic library access check.\n");
    sanity();

    // close SO file
    dlclose(handle);

    return 0;
}