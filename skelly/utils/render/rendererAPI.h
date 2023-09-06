
/****************************************************************************************
 * 
 * Zygomatic
 * Render Subsystem
 * 
 ****************************************************************************************
 * 
 * Changelog:
 * 
 * - 0.1.0: Initial implementation; Vertex Array, Buffers and Shader basic functionality
 * 
 **************************************************************************************** 
 * 
 * Description:
 * 
 * This module provides access to higher level abstrations through the Renderer class,
 * such as rendering a scene or drawing from a vertexArray index. It also provides the
 * building blocks for the APIs through RendererCommands. RendererAPI is the abstraction
 * to serve functionality from different rendering APIs.
 * 
 ***************************************************************************************/

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

            static APITarget getTargetAPI() { return _s_targetAPI; }
            static APITarget initialize();
        private:
            #ifdef TARGET_OPENGL
            static const APITarget _s_targetAPI = APITarget::OpenGL;
            #else
            static const APITarget _s_targetAPI = APITarget::None;
            #endif
    };
}