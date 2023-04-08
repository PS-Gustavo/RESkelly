#include "skelly.h"

namespace skelly {
    
    Application::Application() {
        Logger::init();
        
        m_window = std::unique_ptr<Window>(Window::create());
    }

    Application::~Application() {}

    void Application::run() {
        
        while(m_running) {
            glClearColor(1, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            m_window->onUpdate();
        }
        
    }

    extern "C" {
        std::unique_ptr<Application> makeApplication() {
            return std::make_unique<Application>();
        }
    }
}