#include <vertexArray.h>
#include <opengl.h>

namespace skelly {
    
    VertexArray* VertexArray::create() {
        switch (Renderer::getTargetAPI()) {
            case APITarget::OpenGL:
                return new OpenGLVertexArray();
            default:
                SKELLY_ASSERT(false, "VertexArray::create: No Rendering API found!");
                return nullptr;
        }

        SKELLY_ASSERT(false, "VertexArray::create: unknown behavior.")
        return nullptr;
    }   
}