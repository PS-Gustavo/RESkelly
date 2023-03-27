#include "skelly.h"

namespace skelly {
    
    Application::Application() {}
    Application::~Application() {}

    void Application::print() {
        printf("Reached Skelly - lvl1!\n");
    }

    void Application::run() {
        
        skelly::Logger::init();

        char i = 64;
        while (i!=90) {
            i++;
            std::cout << i << "\n";
            if (!(i%91)) i = 64;
        }

        SKELLY_LOG_WARN("CHEESIUM");

        WindowResizeEvent e(1280, 720);

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