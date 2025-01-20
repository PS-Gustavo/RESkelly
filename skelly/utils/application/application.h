
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

#include "utils/camera/camera.h"
#include "utils/object/object.h"

// being scrutinized
#include "utils/inputPoll/input.h"
#include "utils/inputBindings/keyBindings.h"
#include "utils/inputBindings/mouseBindings.h"

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
            void setEventcb(std::function<void(Event&)> eventCb) {eventCb_ = eventCb;};
            
            Input& getInput() {return *input_;}

            void getFrameTime() {
              delta_frames_[0] = static_cast<float>(getWindow().getTime());
            }
            void updateFrameTime() {delta_frames_[1] = delta_frames_[0];}
            void setDelta() {
              delta_time_ = delta_frames_[0] - delta_frames_[1];
            };
            float getDelta() {return delta_time_;}

            // Object utils
            void addObject(Object object) {
              objects_.push_back(object);
              if (object.hasLabel()) {
                object_labels_.push_back(object.getLabel());
                return;
              }
              std::string label = "object";
              label.append(std::to_string(objects_.size()-1));
              object_labels_.push_back(label);
            };
            void debugListObjects() {
              for (size_t i = 0; i < objects_.size(); i++) {
                std::cout << object_labels_[i] << "\n";
              }
            }
            void renderObjects() {
              for (size_t i = 0; i < objects_.size(); i++) {
                shader_->setMat4("model", objects_[i].getModel());
                Renderer::submit(vertexArray_);
              }
            };
            Camera* getActiveCamera() {return cameras_[activeCamera_];}
            // Application loop
            virtual void run();
            virtual void testRun(int duration);
            virtual void mainLoop();
        private:
            // Event handlers and callbacks
            bool onWindowClose_(WindowCloseEvent& e);
            std::function<void(Event&)> eventCb_;
            std::unique_ptr<Input> input_;

            // Time handler
            float delta_time_;
            float delta_frames_[2] = {0.0f, 0.0f};

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
            std::vector<Object> objects_;
            std::vector<std::string> object_labels_;
            std::vector<Camera*> cameras_;
            int activeCamera_ = 0;
    };
}
