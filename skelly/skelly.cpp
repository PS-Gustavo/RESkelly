#include "skelly.h"

namespace skelly {
    
    Application::Application() {}
    Application::~Application() {}

    void Application::print() {
        printf("Reached Skelly - lvl1!\n");
    }

    void Application::run() {
        char i = 64;
        while (true) {
            i++;
            std::cout << i << "\n";
            if (!(i%90)) i = 64;
        }
    }

    extern "C" {
    std::unique_ptr<Application> make_Application() {
        return std::make_unique<Application>();
    }
    }
}