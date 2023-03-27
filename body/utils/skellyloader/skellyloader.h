#pragma once

#include <dlapi.h>
#include <skelly.h>
#include <iostream>
#include <string>
#include <memory>

namespace sl {

    class SkellyLoader : public dlapi::DLLink {
    public:
        using application_t = std::unique_ptr<skelly::Application> (*)();
        const application_t makeApplication;
        SkellyLoader();
    };
}
