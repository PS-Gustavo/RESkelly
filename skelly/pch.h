#pragma once

#ifdef PCH_ENABLED
    #include <iostream>
    #include <sstream>
    #include <utility>
    #include <functional>
    #include <memory>
    #include <typeinfo>

    #include <stdexcept>

    #include <iterator>
    #include <string>
    #include <vector>
    #include <map>

    #include <spdlog/spdlog.h>
    #include <spdlog/fmt/ostr.h>
    #include <spdlog/sinks/stdout_color_sinks.h>

    #include <defs.h>
    #include <keycodes.h>

    #include <windowEvent.h>
    #include <mouseEvent.h>
    #include <keyEvent.h>

    #include <layer.h>
    #include <layerStack.h>

#endif