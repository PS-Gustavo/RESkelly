#include <defs.h>
#include <stdio.h>
#include <skellyapi.h>

namespace Skelly {

    class Application : public SkellyApi {
    public:
        Application();
        virtual ~Application();

        // void run();
        void print();
    };

    extern "C" void test();

    // Application interface factory functions

    extern "C" SkellyApi* create();
    extern "C" void destroy(SkellyApi* instance);
}
