#pragma once

#include <application.h>

namespace skelly {

    class SKELLY_API Skelly : public Application {
        public:
            Skelly(std::string appName) : Application(appName) {}
            ~Skelly() {}
    };

}