#include <application.h>

namespace skelly {
    Application* Application::_s_instance;

    Application::Application() {
        _s_instance = this;
        _m_window = nullptr;
        
        Logger::init();
    }

    Application::~Application() {}
    
    // Creates the window instance for the application.
    // CAREFUL! You need to create the window context before creating the layers and overlays.
    void Application::createWindow() {
        _m_window = std::unique_ptr<Window>(Window::create());
        _m_window->setEventCallback(BIND_EVENT_FN(Application::onEvent));

        _m_imguiLayer = new ImguiLayer();
        pushOverlay(_m_imguiLayer);
    }

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

    void Application::onEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::_m_onWindowClose));
        // SKELLY_LOG_TRACE("{0}", e);

        for (auto it = _m_layerStack.end(); it != _m_layerStack.begin();) {
            (*--it)->onEvent(e);
            if (e.isHandled()) break;
        }
    }

    void Application::run() {
        while(_m_running) {
            glClearColor(0.6F, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            
            for (Layer* layer : _m_layerStack) {
                layer->onUpdate();
            }

            _m_imguiLayer->begin();
            for (Layer* layer : _m_layerStack) {
                layer->onImguiRender();
            }
            _m_imguiLayer->end();

            if(_m_window != nullptr) _m_window->onUpdate();
        }
        
    }

    bool Application::_m_onWindowClose(WindowCloseEvent& e) {
        _m_running = false;
        return _m_running;
    }    
}