#pragma once

#include <buffer.h>
#include <vertexArray.h>
#include <shader.h>

#include <window.h>
#include <graphicContext.h>

#include <imguiLayer.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#ifndef PCH_ENABLED
    #include <layer.h>
    #include <logger.h>
#endif

namespace skelly {

    class OpenGLRendererAPI : public RendererAPI {
        public:
            virtual void setClearColor(const glm::vec4& color) override;
            virtual void clear() override;

            virtual void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
    };

    class OpenGLRenderContext : public GraphicContext {
        public:
            OpenGLRenderContext(GLFWwindow* windowHandle);

            virtual void init() override;
            virtual void swapBuffers() override;
        private:
            GLFWwindow* _m_windowHandle;
    };

    class OpenGLWindow : public Window {
        public:
            OpenGLWindow(const WindowProps& props);
            virtual ~OpenGLWindow();

            void onUpdate() override;

            unsigned int getWidth() const override { return _m_data.width; }
            void setWidth(unsigned int width) override { _m_data.width = width; }
            unsigned int getHeight() const override { return _m_data.height; }
            void setHeight(unsigned int height) override { _m_data.height = height; }

            void setEventCallback(const EventCallbackFn& callback) 
                override { _m_data.eventCallback = callback; }
            void setVSync(bool enabled) override;
            bool isVSync() const override;

            virtual void* getNativeWindow() const { return _m_window; }
        private:
            virtual void init(const WindowProps& props);
            virtual void shutdown();

            GLFWwindow* _m_window;
            GraphicContext* _m_context;

            struct WindowData {
                std::string title;
                unsigned int width, height;
                bool vSync;

                EventCallbackFn eventCallback;
            };

            WindowData _m_data;
    };

    class OpenGLImgui : public ImguiLayer {
        public:
            OpenGLImgui(const std::string& overlayName = "ImGui Overlay");

            virtual void onAttach() override;
            virtual void onDetach() override;
            virtual void onImguiRender() override;

            virtual void imguiOverlayPane(bool* p_open) override;

            void begin();
            void end();

            inline void setWindow(Window* window) { _m_window = window; }
            inline Window* getWindow() { return _m_window; }
        private:
            float _m_time = 0.0f;
            Window* _m_window = nullptr;
    };

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