#include "skelly.h"

namespace skelly {
    
    #define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    Application::Application() {
        Logger::init();

    }

    Application::~Application() {}

    void Application::createWindow() {
        m_window = std::unique_ptr<Window>(Window::create());
        m_window->setEventCallback(BIND_EVENT_FN(Application::onEvent));
    }

    void Application::onEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::onWindowClose));
        SKELLY_LOG_TRACE("{0}", e);
    }

    void Application::run() {
        
        while(m_running) {
            glClearColor(1, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            m_window->onUpdate();
        }
        
    }

    bool Application::onWindowClose(WindowCloseEvent& e) {
        m_running = false;
        return m_running;
    }    
}