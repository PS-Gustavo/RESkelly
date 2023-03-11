#include <skellyloader.h>

namespace skelly_loader {

    skellyloader::skellyloader() :
        dllink("libskelly_dyn.so"),
        make_Application(load<application_t>("make_Application")) {
        if (make_Application == NULL) throw dynlib_error(std::string(dlerror()));
    }
}