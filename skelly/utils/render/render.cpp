
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

#include <render.h>
#include <opengl.h>

namespace skelly {

    // Renderer

    void Renderer::beginScene() {
        // orchestrate the matrices, environment, cameras, objects and shader info
    }

    void Renderer::endScene() {
    }

    void Renderer::submit(std::shared_ptr<VertexArray>& vertexArray) {
        vertexArray->bind();
        RenderCommands::drawIndexed(vertexArray);
    }

    // Renderer Commands
    
    // Initializes interface according to Render GUI available
    RendererAPI* RenderCommands::initialize() {
        switch (Renderer::getTargetAPI()) {
            case APITarget::OpenGL:
                return new OpenGLRendererAPI();
            default:
                SKELLY_ASSERT(false, "RendererCommands::initialize: No Rendering API found!");
                return nullptr;
        }

        SKELLY_ASSERT(false, "RendererCommands::initialize: unknown behavior.")
        return nullptr;
    }
    RendererAPI* RenderCommands::_s_rendererAPI = RenderCommands::initialize();
}