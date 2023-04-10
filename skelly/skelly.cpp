#include <skelly.h>

namespace skelly {
    
    #define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    Application::Application() {
        Logger::init();
    }

    Application::~Application() {}

    void Application::createWindow() {
        _m_window = std::unique_ptr<Window>(Window::create());
        _m_window->setEventCallback(BIND_EVENT_FN(Application::onEvent));
    }

    void Application::pushLayer(Layer* layer) {
        SKELLY_LOG_TRACE("Creating new layer: {0}", layer->getName());
        _m_layerStack.pushLayer(layer);
    }
    void Application::popLayer(Layer* layer) {
        SKELLY_LOG_TRACE("Creating new layer: {0}", layer->getName());
        _m_layerStack.popLayer(layer);
    }
    void Application::pushOverlay(Layer* overlay) {
        SKELLY_LOG_TRACE("Creating new layer: {0}", overlay->getName());
        _m_layerStack.pushOverlay(overlay);
    }
    void Application::popOverlay(Layer* overlay) {
        SKELLY_LOG_TRACE("Creating new layer: {0}", overlay->getName());
        _m_layerStack.popOverlay(overlay);
    }

    void Application::onEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::_m_onWindowClose));
        SKELLY_LOG_TRACE("{0}", e);

        for (auto it = _m_layerStack.end(); it != _m_layerStack.begin();) {
            (*--it)->onEvent(e);
            if (e.isHandled()) break;
        }
    }

    void Application::run() {
        
        while(_m_running) {
            glClearColor(1, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            
            for (Layer* layer : _m_layerStack) {
                layer->onUpdate();
            }
            _m_window->onUpdate();
        }
        
    }

    bool Application::_m_onWindowClose(WindowCloseEvent& e) {
        _m_running = false;
        return _m_running;
    }    
}