#pragma once

#include <glm/vec4.hpp>
#include <vertexArray.h>

#ifndef PCH_ENABLED
    #include <defs.h>
#endif

namespace skelly {

    class RendererAPI {
        public:
            virtual void setClearColor(const glm::vec4& color) = 0;
            virtual void clear() = 0;

            virtual void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

            inline static APITarget getTargetAPI() { return _s_targetAPI; }
        private:
            static APITarget _s_targetAPI;
    };

}