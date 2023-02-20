#pragma once

#include <defs.h>
#include <stdio.h>
#include <memory>
#include <iostream>

namespace skelly {

    class SKELLY_API Application {
        public:
            Application();
            virtual ~Application();
            virtual void run();
            virtual void print();
    };

    extern "C" {
    std::unique_ptr<Application> make_Application();
    }
}
