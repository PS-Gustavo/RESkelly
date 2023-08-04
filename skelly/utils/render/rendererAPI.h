#pragma once

#include <glm/vec4.hpp>
#include <vertexArray.h>

#ifndef PCH_ENABLED
#endif

namespace skelly {

    enum class RenderTarget {
        None = 0,
        OpenGL = 1,
        Direct3D = 2,
        Vulkan = 3,
        Metal = 4
    };

    class RendererAPI {
        public:
            virtual void setClearColor(const glm::vec4& color) = 0;
            virtual void clear() = 0;

            virtual void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

            inline static RenderTarget getRenderTarget() { return _s_renderTarget; }
        private:
            static RenderTarget _s_renderTarget;
    };

}