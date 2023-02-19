#include "skelly.h"


namespace skelly {
    
    Application::Application() {}
    Application::~Application() {}

    void Application::print() {
        printf("Reached Skelly - lvl1!\n");
    }

    void Application::run() {
        char i = 32;
        while (i < 62) {
            i++;
            std::cout << i << "\n";
        }
    }

    extern "C" {
    std::unique_ptr<Application> make_Application() {
        return std::make_unique<Application>();
    }
    }
}

// int main () {
//     return 0;
// }