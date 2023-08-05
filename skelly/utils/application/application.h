
/****************************************************************************************
 * 
 * Frontal
 * Application Module
 * 
 ****************************************************************************************
 * 
 * Changelog:
 * 
 * - 0.1.0: Initial implementation; Basic logging, windowing, layer, rendering and events
 * 
 **************************************************************************************** 
 * 
 * Description:
 * 
 * This is the engine focal point for the Body project.
 * This module initializes all Skelly structures as necessary, and provides the necessary
 * tools and modules to create the desired end application.
 * 
 ***************************************************************************************/

#pragma once

#include <logger.h>

#include <window.h>
#include <imguiLayer.h>
#include <layerStack.h>

#include <shader.h>
#include <buffer.h>
#include <vertexArray.h>

#include <windowEvent.h>
#include <mouseEvent.h>
#include <keyEvent.h>

// being scrutinized
// #include <input.h>
// #include <keyBindings.h>
// #include <mouseBindings.h>

#ifndef PCH_ENABLED
    #include <defs.h>
    #include <iostream>
#endif

namespace skelly {

    class ImguiLayer;

    class SKELLY_API Application {
        public:
            // Lifetime handlers
            Application();
            virtual ~Application();

            // Layer handlers
            void pushLayer(Layer* layer);
            void popLayer(Layer* layer);
            void pushOverlay(Layer* overlay);
            void popOverlay(Layer* overlay);

            // Application handlers
            static Application& getApplication() { return *_s_instance; }

            // Window handlers
            Window& getWindow() { return *_m_window; }

            // Event handler
            void onEvent(Event& e);
            
            // Application loop
            virtual void run();

            void mockTriangle();
        private:
            // Event handler for window close action
            bool _m_onWindowClose(WindowCloseEvent& e);

            // Instances
            static Application* _s_instance;
            std::unique_ptr<Window> _m_window;

            // Stacks
            LayerStack _m_layerStack;
            ImguiLayer* _m_imguiLayer;
            
            // Flags
            bool _m_running = true;

            // Mock
            std::shared_ptr<VertexArray> _m_vertexArray;
            std::shared_ptr<Shader> _m_shader;
    };
}