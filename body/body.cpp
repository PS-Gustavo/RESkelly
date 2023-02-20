#include <body.h>

int main() {

    try
    {
        skelly_loader::skellyloader sl;

        auto app = sl.make_Application();

        app->run();
    }
    catch(const std::exception& e)
    {
        std::clog << e.what() << '\n';
        return 1;
    }
    
    return 0;
}