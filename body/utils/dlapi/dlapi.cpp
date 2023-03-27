#include <dlapi.h>

namespace dlapi {

    DLLink::DLLink(const char* filename) : _m_handle(dlopen(filename, RTLD_NOW | RTLD_LOCAL)) {
        if(_m_handle == nullptr) throw dynlib_error(std::string(dlerror()));
    }

    DLLink::DLLink(DLLink&& o) : _m_handle(std::exchange(o._m_handle, nullptr)) {}

    DLLink& DLLink::operator=(DLLink&& o) {
        if(_m_handle) dlclose(_m_handle);
        _m_handle = std::exchange(o._m_handle, nullptr);
        return *this;
    }

    DLLink::~DLLink() {
        if (_m_handle) dlclose(_m_handle);
    }

}

