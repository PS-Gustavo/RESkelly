#include <buffer.h>
#include <opengl.h>
#include <render.h>

namespace skelly {

    VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size) {
        switch (Renderer::getTargetAPI()) {
            case APITarget::OpenGL:
                return new OpenGLVertexBuffer(vertices, size);
            default:
                SKELLY_ASSERT(false, "VertexBuffer::create: No Rendering API found!");
                return nullptr;
        }

        SKELLY_ASSERT(false, "VertexBuffer::create: unknown behavior.")
        return nullptr;
    }

    IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t size) {
        switch (Renderer::getTargetAPI()) {
            case APITarget::OpenGL:
                return new OpenGLIndexBuffer(indices, size);
            default:
                SKELLY_ASSERT(false, "IndexBuffer::create: No rendering API found!");
                return nullptr;
        }

        SKELLY_ASSERT(false, "IndexBuffer::create: unknown behavior.")
        return nullptr;
    }

}