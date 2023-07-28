#include <shader.h>
#include <opengl.h>

namespace skelly {

    Shader* Shader::create(std::string& vertexSrc, std::string& fragmentSrc) {
        switch (Renderer::getAPI()) {
            case RenderAPI::OpenGL:
                return new OpenGLShader(vertexSrc, fragmentSrc);
            default:
                SKELLY_ASSERT(false, "No Rendering API found!");
                return nullptr;
        }

        SKELLY_ASSERT(false, "Shader::create unknown behavior.")
        return nullptr;
    }
    
}