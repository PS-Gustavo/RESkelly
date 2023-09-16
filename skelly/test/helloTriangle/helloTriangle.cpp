#include <helloTriangle.h>

namespace test {
    // triangle drawing example
    void HelloTriangle::helloTriangle(skelly::Application& app) {
    
        // local scope initialization
        app.getVertexArray().reset(skelly::VertexArray::create());

        float vertices[6*7] = {
            -0.5f, -0.5f, 0.0f, 0.4f, 0.1f, 0.6f, 1.0f,
            0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 0.4f, 1.0f,
            0.0f,  0.8f,  0.0f, 0.4f, 0.1f, 0.6f, 1.0f,
        };

        std::shared_ptr<skelly::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(skelly::VertexBuffer::create(vertices, sizeof(vertices)));

        skelly::BufferLayout layout = {
            { skelly::ShaderDataType::Float3, "a_Position" },
            { skelly::ShaderDataType::Float4, "a_Color" },
        };
        vertexBuffer->setLayout(layout);

        app.getVertexArray()->addVertexBuffer(vertexBuffer);

        // index buffer creation
        uint32_t indices[3] = {0, 1, 2};
        std::shared_ptr<skelly::IndexBuffer> indexBuffer;
        indexBuffer.reset(skelly::IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));
        app.getVertexArray()->addIndexBuffer(indexBuffer);

        std::string vertexSrc = R"(
            #version 450 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            out vec4 v_Color;

            void main() {
                v_Color = a_Color;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        std::string fragmentSrc = R"(
            #version 450 core

            layout(location = 0) out vec4 color;

            in vec4 v_Color;

            void main() {
                color = v_Color;
            }
        )";

        app.getShader().reset(skelly::Shader::create(vertexSrc, fragmentSrc));
    }

}