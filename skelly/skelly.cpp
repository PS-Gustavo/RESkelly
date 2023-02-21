#include "skelly.h"

namespace skelly {
    
    Application::Application() {}
    Application::~Application() {}

    void Application::print() {
        printf("Reached Skelly - lvl1!\n");
    }

    void Application::run() {
        
        skelly::logger::init();

        char i = 64;
        while (i!=90) {
            i++;
            std::cout << i << "\n";
            if (!(i%91)) i = 64;
        }

        SKELLY_LOG_ERROR("Error! i={0} delly", i);
        
    }

    extern "C" {
    std::unique_ptr<Application> make_Application() {
        return std::make_unique<Application>();
    }
    }
}