#include <body.h>

int main() {

    try
    {   
        
        skelly::Application skellyApp;
        skellyApp.run();
    }
    catch(const std::exception& e)
    {
        std::clog << e.what() << '\n';
        return -1;
    }
    
    return 0;
}