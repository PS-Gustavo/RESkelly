
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

//#include <camera.h>

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
            static Application& getApplication() { return *instance_; }
            // Rendering handlers
            static std::shared_ptr<VertexArray>& getVertexArray() { return vertexArray_; }
            static std::shared_ptr<Shader>& getShader() { return shader_; }

            // Window handlers
            Window& getWindow() { return *window_; }

            // Event handler
            void onEvent(Event& e);
            
            // Application loop
            virtual void run();
            virtual void testRun();
            virtual void mainLoop();
        private:
            // Event handler for window close action
            bool onWindowClose_(WindowCloseEvent& e);

            // Instances
            static Application* instance_;
            std::unique_ptr<Window> window_;
            std::unique_ptr<ImguiLayer> imguiLayer_;

            // Stacks
            LayerStack layerStack_;
            
            // Flags
            bool is_running_ = true;

            // Rendering structures
            static std::shared_ptr<VertexArray> vertexArray_;
            static std::shared_ptr<Shader> shader_;

            // Object arrays
            //std::vector<Camera> cameras_;
    };
}
