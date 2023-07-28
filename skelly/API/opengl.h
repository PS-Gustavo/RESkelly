#pragma once

#include <buffer.h>
#include <glad/gl.h>
// #include <GLFW/glfw3.h>

namespace skelly {

    class OpenGLVertexBuffer : public VertexBuffer {
        public:
            OpenGLVertexBuffer(float* vertices, uint32_t size);
            virtual ~OpenGLVertexBuffer();

            virtual void bind() const;
            virtual void unbind() const;

        private:
            uint32_t _m_rendererId;
    };

    class OpenGLIndexBuffer : public IndexBuffer {
        public:
            OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
            virtual ~OpenGLIndexBuffer();

            virtual void bind() const;
            virtual void unbind() const;

            virtual inline uint32_t getCount() const { return _m_count; };

        private:
            uint32_t _m_rendererId;
            uint32_t _m_count;
    };

}