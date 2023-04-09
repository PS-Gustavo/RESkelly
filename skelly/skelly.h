#include <logger.h>

#include <window.h>

#include <windowEvent.h>
#include <mouseEvent.h>
#include <keyEvent.h>

#ifndef PCH_ENABLED
    #include <defs.h>
    #include <iostream>
#endif

namespace skelly {

    class SKELLY_API Application {
        public:
            Application();
            virtual ~Application();
            virtual void createWindow();
            virtual void run();
        private:
            std::unique_ptr<Window> m_window;
            // std::map<std::string, std::unique_ptr<Window>> m_windows;
            bool m_running = true;
    };

    extern "C" {
    std::unique_ptr<Application> makeApplication();
    }
}
