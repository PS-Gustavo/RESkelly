#include <body.h>

int main() {

    try
    {
        sl::SkellyLoader sl;

        auto app = sl.makeApplication();

        app->run();
    }
    catch(const std::exception& e)
    {
        std::clog << e.what() << '\n';
        return 1;
    }
    
    return 0;
}