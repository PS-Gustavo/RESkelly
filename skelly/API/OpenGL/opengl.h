#pragma once

#include <buffer.h>
#include <vertexArray.h>
#include <shader.h>

#include <input.h>
#include <window.h>
#include <graphicContext.h>

#include <imguiLayer.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/matrix.hpp"

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
      GLFWwindow* windowHandle_;
  };

  class OpenGLWindow : public Window {
    public:
      OpenGLWindow(const WindowProps& props);
      virtual ~OpenGLWindow();

      void onUpdate() override;

      unsigned int getWidth() const override { return data_.width; }
      void setWidth(unsigned int width) override { data_.width = width; }
      unsigned int getHeight() const override { return data_.height; }
      void setHeight(unsigned int height) override { data_.height = height; }
      double getTime();
      void setEventCallback(const EventCallbackFn& callback) 
        override { data_.eventCallback = callback; }
      void setVSync(bool enabled) override;
      bool isVSync() const override;

      virtual void* getNativeWindow() const { return window_; }
    private:
      virtual void init(const WindowProps& props);
      virtual void shutdown();

      GLFWwindow* window_;
      GraphicContext* context_;

      struct WindowData {
        std::string title;
        unsigned int width, height;
        bool vSync;

        EventCallbackFn eventCallback;
      };

      WindowData data_;
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

      inline void setWindow(Window* window) { window_ = window; }
      inline Window* getWindow() { return window_; }
    private:
      float time_ = 0.0f;
      Window* window_ = nullptr;
  };

  class OpenGLInput : public Input {
    protected:
      bool m_isKeyPressedImpl(int keycode) override;
      bool m_isMouseButtonPressedImpl(int button) override;
      float m_getMouseXImpl() override;
      float m_getMouseYImpl() override;
      std::pair<float, float> m_getMouseCoordImpl() override;
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
      uint32_t rendererId_;
      std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers_;
      std::vector<std::shared_ptr<IndexBuffer>> indexBuffers_;
  };

  class OpenGLVertexBuffer : public VertexBuffer {
    public:
      OpenGLVertexBuffer(float* vertices, uint32_t size);
      virtual ~OpenGLVertexBuffer();

      virtual void bind() const override;
      virtual void unbind() const override;

      virtual const BufferLayout& getLayout() const override { return layout_; }
      virtual void setLayout(const BufferLayout& layout) override { layout_ = layout; }
    private:
      uint32_t rendererId_;
      BufferLayout layout_;
  };

  class OpenGLIndexBuffer : public IndexBuffer {
    public:
      OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
      virtual ~OpenGLIndexBuffer();

      virtual void bind() const override;
      virtual void unbind() const override;

      virtual inline uint32_t getCount() const { return count_; };

    private:
      uint32_t rendererId_;
      uint32_t count_;
  };

  class OpenGLShader : public Shader {
    public:
      OpenGLShader(uint8_t createMode, std::string& vertexSrc, std::string& fragmentSrc);

      virtual ~OpenGLShader();

      // virtual void load(std::string& vertexSrc, std::string& fragmentSrc) const override;

      int getMaxVertexAttributes() const override;

      void setBool(const std::string &name, bool value) const {         
        glUniform1i(glGetUniformLocation(rendererId_, name.c_str()), (int)value); 
      }
      void setInt(const std::string &name, int value) const {
        glUniform1i(glGetUniformLocation(rendererId_, name.c_str()), value); 
      }
      void setFloat(const std::string &name, float value) const {
        glUniform1f(glGetUniformLocation(rendererId_, name.c_str()), value); 
      }
      void setVec2(const std::string &name, const glm::vec2 &value) const {
        glUniform2fv(glGetUniformLocation(rendererId_, name.c_str()), 1, &value[0]); 
      }
      void setVec2(const std::string &name, float x, float y) const {
        glUniform2f(glGetUniformLocation(rendererId_, name.c_str()), x, y); 
      }
      void setVec3(const std::string &name, const glm::vec3 &value) const {
        glUniform3fv(glGetUniformLocation(rendererId_, name.c_str()), 1, &value[0]); 
      }
      void setVec3(const std::string &name, float x, float y, float z) const {
        glUniform3f(glGetUniformLocation(rendererId_, name.c_str()), x, y, z); 
      }
      void setVec4(const std::string &name, const glm::vec4 &value) const {
        glUniform4fv(glGetUniformLocation(rendererId_, name.c_str()), 1, &value[0]); 
      }
      void setVec4(const std::string &name, float x, float y, float z, float w) const {
        glUniform4f(glGetUniformLocation(rendererId_, name.c_str()), x, y, z, w); 
      }
      void setMat2(const std::string &name, const glm::mat2 &mat) const {
        glUniformMatrix2fv(glGetUniformLocation(rendererId_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
      }
      void setMat3(const std::string &name, const glm::mat3 &mat) const {
        glUniformMatrix3fv(glGetUniformLocation(rendererId_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
      }
      void setMat4(const std::string &name, const glm::mat4 &mat) const {
        glUniformMatrix4fv(glGetUniformLocation(rendererId_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
      } 

            void bind() const override;
            void unbind() const override;

        private:
            uint32_t rendererId_;
    };

}
