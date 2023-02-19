#include <dlapi.h>

namespace dl_api {

    dllink::dllink(const char* filename) : handle(dlopen(filename, RTLD_NOW | RTLD_LOCAL)) {
        if(handle == nullptr) throw dynlib_error(std::string(dlerror()));
    }

    dllink::dllink(dllink&& o) : handle(std::exchange(o.handle, nullptr)) {}

    dllink& dllink::operator=(dllink&& o) {
        if(handle) dlclose(handle);
        handle = std::exchange(o.handle, nullptr);
        return *this;
    }

    dllink::~dllink() {
        if (handle) dlclose(handle);
    }

}

