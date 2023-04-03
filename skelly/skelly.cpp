#include "skelly.h"

namespace skelly {
    
    Application::Application() {}
    Application::~Application() {}

    void Application::print() {
        printf("Reached Skelly - lvl1!\n");
    }

    void Application::run() {
        
        skelly::Logger::init();
        SKELLY_LOG_INFO("Logger structures initialized.");

        WindowResizeEvent e(1280, 720);
        SKELLY_LOG_ERROR(e);
        std::cout << e << "\n";

        MouseButtonPressedEvent e2(5);
        std::cout << "This is a test: " << e2 << "\n";
        SKELLY_LOG_WARN(e2);

        std::cout << typeid(e).name() << "\n";
        std::cout << "(" << e.getWidth() << ", " << e.getHeight() << ")\n";
        
        //SKELLY_LOG_TRACE(e);

        //SKELLY_LOG_ERROR(e);
        
    }

    extern "C" {
        std::unique_ptr<Application> makeApplication() {
            return std::make_unique<Application>();
        }
    }
}