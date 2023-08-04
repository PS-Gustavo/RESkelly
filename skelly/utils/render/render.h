#pragma once

// #include <stdio.h>
#include <rendererAPI.h>

namespace skelly {

    class Renderer {
        public:
            // inline static RenderTarget getAPI() { return _s_rendererAPITarget; }
            // inline void setAPI(RenderTarget api) { _s_rendererAPITarget = api; }

            inline static RenderTarget getTargetAPI() { return RendererAPI::getRenderTarget(); }
    };

    // class RendererCommands {
    //     public:

    //     private:
    // };

}