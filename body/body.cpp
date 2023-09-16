#include <body.h>

int main() {
    try {           
        body::Body app;
        test::HelloTriangle example;
        example.helloTriangle(app.getApplication());
        app.run();
    }
    catch(const std::exception& e) {
        std::clog << e.what() << '\n';
        return -1;
    }
        
    return 0;
}