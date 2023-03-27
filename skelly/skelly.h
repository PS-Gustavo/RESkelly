
#include <defs.h>
#include <logger.h>

#include <windowEvent.h>
#include <mouseEvent.h>
#include <keyEvent.h>

namespace skelly {

    class SKELLY_API Application {
        public:
            Application();
            virtual ~Application();
            virtual void run();
            virtual void print();
    };

    extern "C" {
    std::unique_ptr<Application> makeApplication();
    }
}
