#pragma once

// #include <stdio.h>

namespace skelly {

    enum class RenderAPI {
        None = 0,
        OpenGL = 1,
        Direct3D = 2,
        Vulkan = 3,
        Metal = 4
    };

    class Renderer {
        public:
            inline static RenderAPI getAPI() { return _s_rendererAPI; }
            inline void setAPI(RenderAPI api) { _s_rendererAPI = api; }

        private:
            static RenderAPI _s_rendererAPI;
    };

}