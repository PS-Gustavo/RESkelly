#include <logger.h>

#include <window.h>

#ifndef PCH_ENABLED
    #include <defs.h>
    #include <iostream>
    #include <windowEvent.h>
    #include <mouseEvent.h>
    #include <keyEvent.h>
#endif

namespace skelly {

    class SKELLY_API Application {
        public:
            Application();
            virtual ~Application();
            virtual void createWindow();
            virtual void run();

            void onEvent(Event& e);
        private:
            bool onWindowClose(WindowCloseEvent& e);

            std::unique_ptr<Window> m_window;
            // std::map<std::string, std::unique_ptr<Window>> m_windows;
            bool m_running = true;
    };
}
