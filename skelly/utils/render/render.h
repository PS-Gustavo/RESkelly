
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

#include <rendererAPI.h>
#include <vertexArray.h>

namespace skelly {

    class Renderer {
        public:
            static void beginScene();
            static void endScene();

            static void submit(std::shared_ptr<VertexArray>& vertexArray);

            static APITarget getTargetAPI() { return RendererAPI::getTargetAPI(); }
    };

    class RenderCommands {
        public:

            static void setClearColor(const glm::vec4& color)
                { _s_rendererAPI->setClearColor(color); };
                
            static void clear() { _s_rendererAPI->clear(); }

            static void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) 
                { _s_rendererAPI->drawIndexed(vertexArray); }

            static RendererAPI* initialize();
        private:
            static RendererAPI* _s_rendererAPI;
    };

}