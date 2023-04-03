#pragma once

#include <dlapi.h>
#include <skelly.h>

#ifndef PCH_ENABLED
    #include <memory>
    #include <string>
    #include <stdexcept>
#endif

namespace sl {

    class SkellyLoader : public dlapi::DLLink {
    public:
        using application_t = std::unique_ptr<skelly::Application> (*)();
        const application_t makeApplication;
        SkellyLoader();
    };
}
