
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

#include <application.h>
#include <render.h>
#include <chrono>
#include "glm/glm.hpp"
#include <cmath>

namespace skelly {
    Application* Application::instance_;
    // DN: Since the App is supposed to be unique, are single static shared pointers for
    // vertexArray and shader enough in the long term?
    std::shared_ptr<VertexArray> Application::vertexArray_;
    std::shared_ptr<Shader> Application::shader_;

    // Lifetime handlers
    // If you modify the constructor behavior, be careful! You need to create the window 
    // context before creating the layers and overlays.
    Application::Application(std::string appName) {
        instance_ = this;
        window_ = nullptr;
        
        Logger::init(appName);
        window_ = std::unique_ptr<Window>(Window::create());
        window_->setEventCallback(BIND_EVENT_FN(Application::onEvent));
        Camera initial_camera;
        cameras_.push_back(initial_camera);

        // debug layer
        // WIP: pop/push layers needs to support ImguiLayer w/o raw pointer translation
        imguiLayer_ = std::unique_ptr<ImguiLayer>(ImguiLayer::create("ImGui Overlay"));
        pushOverlay(imguiLayer_.get());
    }

    Application::~Application() {
        // Remove from stack before destroying uq pointer;
        popOverlay(imguiLayer_.get());
    }
    
    // layer stack handlers
    void Application::pushLayer(Layer* layer) {
        SKELLY_LOG_TRACE("Creating new layer: {0}", layer->getName());
        layerStack_.pushLayer(layer);
        layer->onAttach();
    }
    void Application::popLayer(Layer* layer) {
        SKELLY_LOG_TRACE("Destroying layer: {0}", layer->getName());
        layerStack_.popLayer(layer);
        layer->onDetach();
    }
    void Application::pushOverlay(Layer* overlay) {
        SKELLY_LOG_TRACE("Creating new overlay: {0}", overlay->getName());
        layerStack_.pushOverlay(overlay);
        overlay->onAttach();
    }
    void Application::popOverlay(Layer* overlay) {
        SKELLY_LOG_TRACE("Destroying overlay: {0}", overlay->getName());
        layerStack_.popOverlay(overlay);
        overlay->onDetach();
    }

    // event handlers
    void Application::onEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::onWindowClose_));
 
        for (auto it = layerStack_.end(); it != layerStack_.begin();) {
            (*--it)->onEvent(e);
            if (e.isHandled()) break;
        }
    }

    bool Application::onWindowClose_([[maybe_unused]] WindowCloseEvent& e) {
        is_running_ = false;
        return is_running_;
    }    

    // main application loop
    void Application::run() {
        while(is_running_) {   
            mainLoop();
        }
    }

    // test application loop
    void Application::testRun() {
        int runCount = 0;
        std::cout << "Hardware allows for " << shader_->getMaxVertexAttributes() << " vertex attributes.\n";
        while ((runCount < 200) && (is_running_)) {
            mainLoop();
            runCount++;
        }
    }

    void Application::mainLoop() {
        
        
        
        // standard clear operation
        RenderCommands::setClearColor({0.1f, 0.1f, 0.1f, 1});
        RenderCommands::clear();

        // draw if there are contents in the vertexArray
        if (shader_.use_count()) {
            shader_->bind();
            Renderer::submit(vertexArray_);
        }
        
        // sweep and update layers
        for (Layer* layer : layerStack_) {
            layer->onUpdate();
        }
        if (imguiLayer_ != nullptr) {
            imguiLayer_->begin();
            // WIP: Add support for custom ImGui layers
            // for (Layer* layer : _m_layerStack) {
            //     layer->onImguiRender();
            // }
            imguiLayer_->onImguiRender();
            imguiLayer_->end();
        }

        if (window_ != nullptr) window_->onUpdate();
    }
}
