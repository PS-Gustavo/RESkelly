#include <render.h>
#include <opengl.h>

namespace skelly {

    // Renderer

    void Renderer::beginScene() {

    }

    void Renderer::endScene() {

    }

    void Renderer::submit(std::shared_ptr<VertexArray>& vertexArray) {
        vertexArray->bind();
        RenderCommands::drawIndexed(vertexArray);
    }

    // Renderer Commands

    RendererAPI* RenderCommands::_s_rendererAPI = new OpenGLRendererAPI;


}