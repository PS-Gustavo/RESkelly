#pragma once

#include <buffer.h>
#include <vertexArray.h>
#include <shader.h>
#include <glad/gl.h>
// #include <GLFW/glfw3.h>

namespace skelly {

    class OpenGLVertexArray : public VertexArray {
        public:
            OpenGLVertexArray();
            virtual ~OpenGLVertexArray();

            virtual void bind() const override;
            virtual void unbind() const override;

            virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
            virtual void addIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

            virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const override;
            virtual const std::vector<std::shared_ptr<IndexBuffer>>& getIndexBuffers() const override;
        private:
            uint32_t _m_rendererId;
            std::vector<std::shared_ptr<VertexBuffer>> _m_vertexBuffers;
            std::vector<std::shared_ptr<IndexBuffer>> _m_indexBuffers;
    };

    class OpenGLVertexBuffer : public VertexBuffer {
        public:
            OpenGLVertexBuffer(float* vertices, uint32_t size);
            virtual ~OpenGLVertexBuffer();

            virtual void bind() const override;
            virtual void unbind() const override;

            virtual const BufferLayout& getLayout() const override { return _m_layout; }
            virtual void setLayout(const BufferLayout& layout) override { _m_layout = layout; }
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