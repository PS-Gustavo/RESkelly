#pragma once

namespace skelly {

    #define SKELLY_MOUSE_BUTTON_1         0
    #define SKELLY_MOUSE_BUTTON_2         1
    #define SKELLY_MOUSE_BUTTON_3         2
    #define SKELLY_MOUSE_BUTTON_4         3
    #define SKELLY_MOUSE_BUTTON_5         4
    #define SKELLY_MOUSE_BUTTON_6         5
    #define SKELLY_MOUSE_BUTTON_7         6
    #define SKELLY_MOUSE_BUTTON_8         7
    #define SKELLY_MOUSE_BUTTON_LAST      SKELLY_MOUSE_BUTTON_8
    #define SKELLY_MOUSE_BUTTON_LEFT      SKELLY_MOUSE_BUTTON_1
    #define SKELLY_MOUSE_BUTTON_RIGHT     SKELLY_MOUSE_BUTTON_2
    #define SKELLY_MOUSE_BUTTON_MIDDLE    SKELLY_MOUSE_BUTTON_3

    struct mouseConverterMaps {
        std::vector<int> glfwMap;
        std::vector<int> win32Map;

        int inline getGlfwMappedMouseButton(int skellyMouseButton) { return glfwMap[skellyMouseButton]; }
        int inline getWin32MappedMouseButton(int skellyMouseButton) { return win32Map[skellyMouseButton]; }
    };

}