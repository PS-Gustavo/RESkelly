#include <skellyloader.h>

namespace sl {

    SkellyLoader::SkellyLoader() :
        DLLink("libskelly_dyn.so"),
        makeApplication(load<application_t>("makeApplication")) {
        if (makeApplication == NULL) throw dynlib_error(std::string(dlerror()));
    }
}