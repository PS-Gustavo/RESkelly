#pragma once

#include <defs.h>
#include <stdio.h>

namespace Skelly {

    class SKELLY_API Application {
    public:
        Application();
        virtual ~Application();

        void run();
        void print();
    };

}