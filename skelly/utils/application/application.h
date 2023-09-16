
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
    #include <logger.h>
    #include <defs.h>
    #include <iostream>
#endif

namespace skelly {

    class ImguiLayer;

    class SKELLY_API Application {
        public:
            // Lifetime handlers
            Application(std::string appName);
            virtual ~Application();

            // Layer handlers
            void pushLayer(Layer* layer);
            void popLayer(Layer* layer);
            void pushOverlay(Layer* overlay);
            void popOverlay(Layer* overlay);

            // Application handlers
            static Application& getApplication() { return *_s_instance; }
            // Rendering handlers
            static std::shared_ptr<VertexArray>& getVertexArray() { return _m_vertexArray; }
            static std::shared_ptr<Shader>& getShader() { return _m_shader; }

            // Window handlers
            Window& getWindow() { return *_m_window; }

            // Event handler
            void onEvent(Event& e);
            
            // Application loop
            virtual void run();
        private:
            // Event handler for window close action
            bool _m_onWindowClose(WindowCloseEvent& e);

            // Instances
            static Application* _s_instance;
            std::unique_ptr<Window> _m_window;
            std::unique_ptr<ImguiLayer> _m_imguiLayer;

            // Stacks
            LayerStack _m_layerStack;
            
            // Flags
            bool _m_running = true;

            // Rendering structures
            static std::shared_ptr<VertexArray> _m_vertexArray;
            static std::shared_ptr<Shader> _m_shader;
    };
}