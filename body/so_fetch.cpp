#include <iostream>
#include <dlfcn.h>
#include <so_fetch.h>

namespace SOOperations {

    SOLink so_fetch (char* function_id) {
        SOLink result = {nullptr, NULL};

        // opening shared object file
        void* handle = dlopen("sanity.so", RTLD_LAZY);
        if (!handle) {
            std::cout << "Error retrieving shared object file: " << dlerror() << "\n";
            return result;
        }

        // fetching function sanity from SO handle
        sanityF sanity = (sanityF) dlsym(handle, function_id);
        if (!sanity) {
            std::cout << "Error retrieving function address: " << dlerror() << "\n";
            dlclose(handle);
            return result;
        }
        
         result = {handle, sanity};

        return result;
    }

    void so_close (void* handle) {
        dlclose(handle);
    }

}

