#include <vertexArray.h>
#include <opengl.h>

namespace skelly {
    
    VertexArray* VertexArray::create() {
        switch (Renderer::getTargetAPI()) {
            case RenderTarget::OpenGL:
                return new OpenGLVertexArray();
            default:
                SKELLY_ASSERT(false, "No Rendering API found!");
                return nullptr;
        }

        SKELLY_ASSERT(false, "VertexBuffer::create unknown behavior.")
        return nullptr;
    }   
}