#pragma once

#ifdef PCH_ENABLED
    #include <dlfcn.h>

    #include <iostream>
    #include <sstream>
    #include <utility>
    #include <functional>
    #include <memory>
    #include <typeinfo>

    #include <stdexcept>

    #include <string>
    #include <vector>
    #include <map>

    #include <spdlog/spdlog.h>
    #include <spdlog/fmt/ostr.h>
    #include <spdlog/sinks/stdout_color_sinks.h>

    #ifdef ENABLE_ASSERTS
        #define SKELLY_ASSERT(x, ...) { if(!(x)) { SKELLY_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); } }
    #else
        #define SKELLY_ASSERT(x, ...)
    #endif
#endif