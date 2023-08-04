#include <opengl.h>

namespace skelly {

    // Renderer API

    void OpenGLRendererAPI::setClearColor(const glm::vec4& color) {
        glClearColor(color.r, color.g, color.b, color.a);

    }
    
    void OpenGLRendererAPI::clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) {
        glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffers()[0]->getCount(), GL_UNSIGNED_INT, nullptr);
    }

    // Utils

    static GLenum getElementType(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float: return GL_FLOAT;
            case ShaderDataType::Float2: return GL_FLOAT;
            case ShaderDataType::Float3: return GL_FLOAT;
            case ShaderDataType::Float4: return GL_FLOAT;
            case ShaderDataType::Mat3: return GL_FLOAT;
            case ShaderDataType::Mat4: return GL_FLOAT;
            case ShaderDataType::Int: return GL_INT;
            case ShaderDataType::Int2: return GL_INT;
            case ShaderDataType::Int3: return GL_INT;
            case ShaderDataType::Int4: return GL_INT;
            case ShaderDataType::Bool: return GL_BOOL;
            default:
                SKELLY_ASSERT(false, "getOpenGLShaderDataType: Unknown Shader Data Type");
                return GL_FALSE;
        }

        SKELLY_ASSERT(false, "getOpenGLShaderDataType: Unknown Error!");
        return GL_FALSE;
    }

    // VertexArray

    OpenGLVertexArray::OpenGLVertexArray() {
        glCreateVertexArrays(1, &_m_rendererId);
    }

    OpenGLVertexArray::~OpenGLVertexArray() {
        glDeleteVertexArrays(1, &_m_rendererId);
    }

    void OpenGLVertexArray::bind() const {
        glBindVertexArray(_m_rendererId);
    }

    void OpenGLVertexArray::unbind() const {
        glBindVertexArray(0);
    }
    
    void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {
        
        SKELLY_ASSERT(vertexBuffer->getLayout().getElements().size(), "No layout has been created for the VertexBuffer");

        glBindVertexArray(_m_rendererId);
        vertexBuffer->bind();
        uint32_t index = 0;
        const auto& layout = vertexBuffer->getLayout();
        for (const auto& element : layout) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                index, 
                element.getComponentCount(),
                getElementType(element.type),
                element.isNormalized ? GL_TRUE : GL_FALSE,
                layout.getStride(),
                (const void*)(intptr_t) element.offset
            );
            index++;
        }
        
        _m_vertexBuffers.push_back(vertexBuffer);
         
    }

    void OpenGLVertexArray::addIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
        glBindVertexArray(_m_rendererId);
        indexBuffer->bind();
        _m_indexBuffers.push_back(indexBuffer);
    }

    const std::vector<std::shared_ptr<VertexBuffer>>& OpenGLVertexArray::getVertexBuffers() const {
        return _m_vertexBuffers;
    }
    const std::vector<std::shared_ptr<IndexBuffer>>& OpenGLVertexArray::getIndexBuffers() const {
        return _m_indexBuffers;
    }

    // VertexBuffer

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) {
        glCreateBuffers(1, &_m_rendererId);
        glBindBuffer(GL_ARRAY_BUFFER, _m_rendererId);
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

    // IndexBuffer

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

    // Shader

    OpenGLShader::OpenGLShader(std::string& vertexSrc, std::string& fragmentSrc) {

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        const GLchar* source = vertexSrc.c_str();
        glShaderSource(vertexShader, 1, &source, 0);

        glCompileShader(vertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(vertexShader);

            SKELLY_LOG_ERROR("{0}", infoLog.data());
            SKELLY_ASSERT(false, "Vertex shader compilation failure");

            return;
        }

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        source = fragmentSrc.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);

        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(fragmentShader);
            glDeleteShader(vertexShader);

            SKELLY_LOG_ERROR("{0}", infoLog.data());
            SKELLY_ASSERT(false, "Fragment shader compilation failure");

            return;
        }

        _m_rendererId = glCreateProgram();
        GLuint program = _m_rendererId;

        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        glLinkProgram(program);

        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(program);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            SKELLY_LOG_ERROR("{0}", infoLog.data());
            SKELLY_ASSERT(false, "Shader linking failure.");

            return;
        }

        glDetachShader(program, vertexShader);
        glDetachShader(program, fragmentShader);

    }

    OpenGLShader::~OpenGLShader() {
        glDeleteProgram(_m_rendererId);
    }

    void OpenGLShader::bind() const {
        glUseProgram(_m_rendererId);
    }

    void OpenGLShader::unbind() const {
        glUseProgram(0);
    }

}