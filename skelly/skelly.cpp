#include "skelly.h"


namespace Skelly {
    
    Application::Application() {}
    Application::~Application() {}

    // void Application::run() {
    //     while (true) {}
    // }

    void Application::print() {
        printf("Reached xxxxxx Skelly!\n");
    }

    void test() {
        printf("This is THE test\n");
    }


    // Application interface factory functions

    SkellyApi* create()
    {
        return new Application;
    }

    void destroy(SkellyApi* instance) {
        delete instance;
    };

}

// int main () {
//     return 0;
// }