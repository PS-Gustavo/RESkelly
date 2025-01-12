#include "testCamera.h"
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test {
  // triangle drawing example
  void TestCamera::setup(skelly::Application& app) {
  
    app.getVertexArray().reset(skelly::VertexArray::create());

    // cube made of 2 triangles per side
    // XYZ pos + texture coordinates
    float vertices[] = {
      -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
      0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
      0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f,

      -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f,

      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.5f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f,
      -0.5f,  0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,

      0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f, 1.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 0.5f, 1.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.5f, 1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f, 1.0f,

      -0.5f, -0.5f, -0.5f,  0.1f, 0.2f, 0.3f, 1.0f,
      0.5f, -0.5f, -0.5f,  0.6f, 0.5f, 0.4f, 1.0f,
      0.5f, -0.5f,  0.5f,  0.7f, 0.8f, 0.9f, 1.0f,
      0.5f, -0.5f,  0.5f,  0.7f, 0.8f, 0.9f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.6f, 0.5f, 0.4f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.1f, 0.2f, 0.3f, 1.0f,

      -0.5f,  0.5f, -0.5f,  0.3f, 0.6f, 0.9f, 1.0f,
      0.5f,  0.5f, -0.5f,  0.8f, 0.4f, 0.2f, 1.0f,
      0.5f,  0.5f,  0.5f,  0.1f, 0.5f, 0.7f, 1.0f,
      0.5f,  0.5f,  0.5f,  0.1f, 0.4f, 0.8f, 1.0f,
      -0.5f,  0.5f,  0.5f,  0.2f, 0.6f, 1.0f, 1.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.0f,
    };

    std::string vertexSrc = R"(
      #version 330 core
      layout (location = 0) in vec3 a_Position;
      layout(location = 1) in vec4 a_Color;

      out vec4 v_Color;

      uniform mat4 model;
      uniform mat4 view;
      uniform mat4 projection;

      void main()
      {
        v_Color = a_Color;
        gl_Position = projection * view * model * vec4(a_Position, 1.0f);
      }
    )";

    std::string fragmentSrc = R"(
      #version 330 core
      out vec4 FragColor;

      in vec4 v_Color;

      void main() {
        FragColor = v_Color;
      }
    )";

    glm::vec3 cubePositions[] = {
      glm::vec3( 0.0f,  0.0f,  0.0f),
      glm::vec3( 2.0f,  5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f),
      glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),
      glm::vec3(-1.7f,  3.0f, -7.5f),
      glm::vec3( 1.3f, -2.0f, -2.5f),
      glm::vec3( 1.5f,  2.0f, -2.5f),
      glm::vec3( 1.5f,  0.2f, -1.5f),
      glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    app.getShader().reset(skelly::Shader::create(vertexSrc, fragmentSrc));

    std::shared_ptr<skelly::VertexBuffer> vertexBuffer;
    vertexBuffer.reset(skelly::VertexBuffer::create(vertices, sizeof(vertices)));

    skelly::BufferLayout layout = {
      { skelly::ShaderDataType::Float3, "a_Position" },
      { skelly::ShaderDataType::Float4, "a_Color" },
    };
    vertexBuffer->setLayout(layout);

    app.getVertexArray()->addVertexBuffer(vertexBuffer);

    // index buffer creation
    uint32_t indices[6*6*3];
    for (int i = 0; i < 6*6*3; i++) indices[i] = i;
    std::shared_ptr<skelly::IndexBuffer> indexBuffer;
    indexBuffer.reset(skelly::IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));
    app.getVertexArray()->addIndexBuffer(indexBuffer);

    app.getShader()->bind();

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)app.getWindow().getWidth() / (float)app.getWindow().getHeight(), 0.1f, 100.0f);
    app.getShader()->setMat4("projection", projection); 

    // camera/view transformation routine
    auto routine = [&app](){
      glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
      float radius = 10.0f;
      auto ts = app.getWindow().getTime();
      float camX = static_cast<float>(sin(ts) * radius);
      float camZ = static_cast<float>(cos(ts) * radius);
      view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
      app.getShader()->setMat4("view", view);
    };
    app.getActiveCamera()->setRoutine(routine);

    auto rotation_axis = glm::vec3(1.0f, 0.3f, 0.5f);
    for (int i = 0; i < 10; i++) {
      // calculate the model matrix for each object and pass it to shader before drawing
      float angle = 20.0f * i;
      skelly::Object new_cube(cubePositions[i], angle);
      new_cube.populateModelMatrix(rotation_axis);
      app.addObject(new_cube);
    }
  }

}
