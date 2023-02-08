#include <iostream>
#include <dlfcn.h>
#include <dlapi.h>

namespace DLApi {

    DLLink dl_open(std::string lib_path) {
        DLLink dl_object = {nullptr, {}};

        // opening shared object file
        dl_object._dl_ptr = dlopen(lib_path.c_str(), RTLD_LAZY);
        if (!dl_object._dl_ptr) {
            std::cout << "Error retrieving shared object file: " << dlerror() << "\n";
            return {};
        }
        return dl_object;
    }

    bool dl_fetch(DLLink& dl_object, std::string function_id) {
        
        // fetching function sanity from SO handle
        funcPtr dl_function = (funcPtr) dlsym(dl_object._dl_ptr, function_id.c_str());
        if (!dl_function) {
            std::cout << "Error retrieving function address: " << dlerror() << "\n";
            dlclose(dl_object._dl_ptr);
            return false;
        }
        
        dl_object._dl_func_map[function_id] = dl_function;
        return true;
    }

    bool dl_class_fetch(DLLink& dl_object, std::string class_id) {

        // fetching class constructors and destructors - to be implemented
        // TBD - add template support
        Skelly::create_t* create_class = (Skelly::create_t*) dlsym(dl_object._dl_ptr, "create");
        Skelly::destroy_t* destroy_class = (Skelly::destroy_t*) dlsym(dl_object._dl_ptr, "destroy");

        if ((!create_class) || (!destroy_class)) {
            std::cout << "Error retrieving class controls: " << dlerror() << "\n";
            dlclose(dl_object._dl_ptr);
            return false;
        }

        dl_object._dl_class_creators[class_id] = create_class;
        dl_object._dl_class_destructors[class_id] = destroy_class;
        return true; 

    }

    void dl_close(DLLink& dl_object) {
        dlclose(dl_object._dl_ptr);
    }

}

