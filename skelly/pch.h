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

    #include <glm/vec3.hpp> // glm::vec3
    #include <glm/vec4.hpp> // glm::vec4
    #include <glm/mat4x4.hpp> // glm::mat4
    #include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
    #include <glm/ext/matrix_clip_space.hpp> // glm::perspective
    #include <glm/ext/scalar_constants.hpp> // glm::pi

    #include <defs.h>
    #include <keycodes.h>

    #include <windowEvent.h>
    #include <mouseEvent.h>
    #include <keyEvent.h>

    #include <layer.h>
    #include <layerStack.h>

#endif