#pragma once

#include <dlapi.h>
#include <skelly.h>
#include <memory>

namespace skelly_loader {

    class skellyloader : public dl_api::dllink {
    public:
        using application_t = std::unique_ptr<skelly::Application> (*)();
        const application_t make_Application;

        skellyloader();
    };
}
