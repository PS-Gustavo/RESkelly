
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

namespace skelly {
    Application* Application::_s_instance;
    // DN: Since the App is supposed to be unique, are single static shared pointers for
    // vertexArray and shader enough in the long term?
    std::shared_ptr<VertexArray> Application::_m_vertexArray;
    std::shared_ptr<Shader> Application::_m_shader;

    // Lifetime handlers
    // If you modify the constructor behavior, be careful! You need to create the window 
    // context before creating the layers and overlays.
    Application::Application(std::string appName) {
        _s_instance = this;
        _m_window = nullptr;
        
        Logger::init(appName);
        _m_window = std::unique_ptr<Window>(Window::create());
        _m_window->setEventCallback(BIND_EVENT_FN(Application::onEvent));

        // debug layer
        // WIP: pop/push layers needs to support ImguiLayer w/o raw pointer translation
        _m_imguiLayer = std::unique_ptr<ImguiLayer>(ImguiLayer::create("ImGui Overlay"));
        pushOverlay(_m_imguiLayer.get());
    }

    Application::~Application() {
        // Remove from stack before destroying uq pointer;
        popOverlay(_m_imguiLayer.get());
    }
    
    // layer stack handlers
    void Application::pushLayer(Layer* layer) {
        SKELLY_LOG_TRACE("Creating new layer: {0}", layer->getName());
        _m_layerStack.pushLayer(layer);
        layer->onAttach();
    }
    void Application::popLayer(Layer* layer) {
        SKELLY_LOG_TRACE("Destroying layer: {0}", layer->getName());
        _m_layerStack.popLayer(layer);
        layer->onDetach();
    }
    void Application::pushOverlay(Layer* overlay) {
        SKELLY_LOG_TRACE("Creating new overlay: {0}", overlay->getName());
        _m_layerStack.pushOverlay(overlay);
        overlay->onAttach();
    }
    void Application::popOverlay(Layer* overlay) {
        SKELLY_LOG_TRACE("Destroying overlay: {0}", overlay->getName());
        _m_layerStack.popOverlay(overlay);
        overlay->onDetach();
    }

    // event handlers
    void Application::onEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::_m_onWindowClose));
 
        for (auto it = _m_layerStack.end(); it != _m_layerStack.begin();) {
            (*--it)->onEvent(e);
            if (e.isHandled()) break;
        }
    }

    bool Application::_m_onWindowClose([[maybe_unused]] WindowCloseEvent& e) {
        _m_running = false;
        return _m_running;
    }    

    // main application loop
    void Application::run() {
        while(_m_running) {            

            // standard clear operation
            RenderCommands::setClearColor({0.1f, 0.1f, 0.1f, 1});
            RenderCommands::clear();

            // draw if there are contents in the vertexArray
            if (_m_shader.use_count()) {
                _m_shader->bind();
                Renderer::submit(_m_vertexArray);
            }
            
            // sweep and update layers
            for (Layer* layer : _m_layerStack) {
                layer->onUpdate();
            }
            if (_m_imguiLayer != nullptr) {
                _m_imguiLayer->begin();
                // WIP: Add support for custom ImGui layers
                // for (Layer* layer : _m_layerStack) {
                //     layer->onImguiRender();
                // }
                _m_imguiLayer->onImguiRender();
                _m_imguiLayer->end();
            }

            if (_m_window != nullptr) _m_window->onUpdate();
        }
    }
}