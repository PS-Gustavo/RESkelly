#include <opengl.h>

namespace skelly {

    //OpenGLVertexBuffer

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) {
        glCreateBuffers(1, &_m_rendererId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _m_rendererId);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer() {
        glDeleteBuffers(1, &_m_rendererId);
    }

    void OpenGLVertexBuffer::bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, _m_rendererId);
    }

    void OpenGLVertexBuffer::unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    //OpenGLIndexBuffer

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : _m_count(count) {
        glCreateBuffers(1, &_m_rendererId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _m_rendererId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count* sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        glDeleteBuffers(1, &_m_rendererId);
    }

    void OpenGLIndexBuffer::bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _m_rendererId);
    }

    void OpenGLIndexBuffer::unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

}