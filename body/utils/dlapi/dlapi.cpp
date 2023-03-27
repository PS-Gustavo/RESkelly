#include <dlapi.h>

namespace dlapi {

    DLLink::DLLink(const char* filename) : m_handle(dlopen(filename, RTLD_NOW | RTLD_LOCAL)) {
        if(m_handle == nullptr) throw dynlib_error(std::string(dlerror()));
    }

    DLLink::DLLink(DLLink&& o) : m_handle(std::exchange(o.m_handle, nullptr)) {}

    DLLink& DLLink::operator=(DLLink&& o) {
        if(m_handle) dlclose(m_handle);
        m_handle = std::exchange(o.m_handle, nullptr);
        return *this;
    }

    DLLink::~DLLink() {
        if (m_handle) dlclose(m_handle);
    }

}

