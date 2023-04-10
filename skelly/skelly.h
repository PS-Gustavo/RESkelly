#include <logger.h>
#include <window.h>

#ifndef PCH_ENABLED
    #include <defs.h>
    #include <iostream>
    #include <windowEvent.h>
    #include <mouseEvent.h>
    #include <keyEvent.h>
    #include <layerStack.h>
#endif

namespace skelly {

    class SKELLY_API Application {
        public:
            Application();
            virtual ~Application();

            virtual void createWindow();

            // layer handlers
            void pushLayer(Layer* layer);
            void popLayer(Layer* layer);
            void pushOverlay(Layer* overlay);
            void popOverlay(Layer* overlay);

            // event handler
            void onEvent(Event& e);
            // main application loop
            virtual void run();
        private:
            // event handler for window close action
            bool _m_onWindowClose(WindowCloseEvent& e);

            // application layer stack
            LayerStack _m_layerStack;

            std::unique_ptr<Window> _m_window;
            // std::map<std::string, std::unique_ptr<Window>> m_windows;
            bool _m_running = true;
    };
}
