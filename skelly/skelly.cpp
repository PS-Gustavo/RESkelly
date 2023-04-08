#include "skelly.h"

namespace skelly {
    
    Application::Application() {
        Logger::init();
        
        m_window = std::unique_ptr<Window>(Window::create());
    }

    Application::~Application() {}

    void Application::print() {
        printf("Reached Skelly - lvl1!\n");
    }

    void Application::run() {
        
        while(m_running) {
            m_window->onUpdate();
        }
        
    }

    extern "C" {
        std::unique_ptr<Application> makeApplication() {
            return std::make_unique<Application>();
        }
    }
}