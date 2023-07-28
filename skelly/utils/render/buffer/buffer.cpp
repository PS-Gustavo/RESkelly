#include <buffer.h>
#include <opengl.h>

namespace skelly {

    VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size) {
        switch (Renderer::getAPI()) {
            case RenderAPI::OpenGL:
                return new OpenGLVertexBuffer(vertices, size);
            default:
                SKELLY_ASSERT(false, "No Rendering API found!");
                return nullptr;
        }

        return nullptr;
    }

    IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t size) {
        switch (Renderer::getAPI()) {
            case RenderAPI::OpenGL:
                return new OpenGLIndexBuffer(indices, size);
            default:
                SKELLY_ASSERT(false, "No rendering API found!");
                return nullptr;
        }

        return nullptr;
    }

}