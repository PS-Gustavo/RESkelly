#pragma once

#include <buffer.h>
#include <shader.h>
#include <glad/gl.h>
// #include <GLFW/glfw3.h>

namespace skelly {

    class OpenGLVertexBuffer : public VertexBuffer {
        public:
            OpenGLVertexBuffer(float* vertices, uint32_t size);
            virtual ~OpenGLVertexBuffer();

            virtual void bind() const override;
            virtual void unbind() const override;

            virtual const BufferLayout& getLayout() const override { return _m_layout; }
            virtual void setLayout(const BufferLayout& layout) override { _m_layout = layout; }

            virtual void* getElementType(ShaderDataType type) const override;
        private:
            uint32_t _m_rendererId;
            BufferLayout _m_layout;
    };

    class OpenGLIndexBuffer : public IndexBuffer {
        public:
            OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
            virtual ~OpenGLIndexBuffer();

            virtual void bind() const override;
            virtual void unbind() const override;

            virtual inline uint32_t getCount() const { return _m_count; };

        private:
            uint32_t _m_rendererId;
            uint32_t _m_count;
    };

    class OpenGLShader : public Shader {
        public:
            OpenGLShader(std::string& vertexSrc, std::string& fragmentSrc);
            virtual ~OpenGLShader();

            virtual void bind() const override;
            virtual void unbind() const override;

        private:
            uint32_t _m_rendererId;
    };

}