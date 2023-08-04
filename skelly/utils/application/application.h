#pragma once

#include <logger.h>
#include <window.h>
#include <imguiLayer.h>
#include <input.h>

#include <shader.h>
#include <buffer.h>
#include <vertexArray.h>

#ifndef PCH_ENABLED
    #include <defs.h>
    #include <iostream>
    #include <windowEvent.h>
    #include <mouseEvent.h>
    #include <keyEvent.h>
    #include <layerStack.h>
    #include <keyBindings.h>
    #include <mouseBindings.h>
#endif

namespace skelly {

    class ImguiLayer;

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

            // application handlers
            inline static Application& getApplication() { return *_s_instance; }

            // window handlers
            inline Window& getWindow() { return *_m_window; }

            // event handler
            void onEvent(Event& e);
            // main application loop
            virtual void run();

            void mockTriangle();
        private:
            // event handler for window close action
            bool _m_onWindowClose(WindowCloseEvent& e);

            // application window list
            static Application* _s_instance;

            // application layer stack
            LayerStack _m_layerStack;
            ImguiLayer* _m_imguiLayer;
            
            std::unique_ptr<Window> _m_window;
            
            bool _m_running = true;

            // rendering mockup structures
            std::shared_ptr<VertexArray> _m_vertexArray;
            std::shared_ptr<Shader> _m_shader;

    };
}