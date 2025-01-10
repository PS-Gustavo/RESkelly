#include "testCamera.h"
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace test {
  // triangle drawing example
  void TestCamera::setup(skelly::Application& app) {
  
    app.getVertexArray().reset(skelly::VertexArray::create());

    float vertices[] = {
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
      0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     
      -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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
        v_Color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
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
      glm::vec3 (2.4f, -0.4f, -3.5f),
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
    uint32_t indices[] = {0, 1, 2};
    std::shared_ptr<skelly::IndexBuffer> indexBuffer;
    indexBuffer.reset(skelly::IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));
    app.getVertexArray()->addIndexBuffer(indexBuffer);

    {

      // position attribute
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
      // glEnableVertexAttribArray(0);

      // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
      // -------------------------------------------------------------------------------------------
      app.getShader()->bind();
      // app.getShader()->setInt("texture1", 0);
      // app.getShader()->setInt("texture2", 1);

      glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)app.getWindow().getWidth() / (float)app.getWindow().getHeight(), 0.1f, 100.0f);
      app.getShader()->setMat4("projection", projection); 

      int i = 0;
      while (i < 200) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        // activate shader
        app.getShader()->bind();

        // camera/view transformation
        glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        float radius = 10.0f;
        float camX = static_cast<float>(sin(glfwGetTime()) * radius);
        float camZ = static_cast<float>(cos(glfwGetTime()) * radius);
        view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        app.getShader()->setMat4("view", view);
        
        app.getVertexArray()->bind();
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            app.getShader()->setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        app.getWindow().onUpdate();
        glfwPollEvents();
        
        i++;
      }
    }

    

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)app.getWindow().getWidth()/(float)app.getWindow().getHeight(), 0.1f, 100.0f);

    // std::string vertexSrc = R"(
    //   #version 450 core

    //   layout(location = 0) in vec3 a_Position;
    //   layout(location = 1) in vec4 a_Color;

    //   out vec4 v_Color;

    //   uniform mat4 projection;

    //   void main() {
    //     v_Color = a_Color;
    //     gl_Position = vec4(a_Position, 1.0f);
    //   }
    // )";

    // std::string fragmentSrc = R"(
    //   #version 450 core

    //   layout(location = 0) out vec4 color;

    //   in vec4 v_Color;

    //   void main() {
    //     color = v_Color;
    //   }
    // )";
    projection = glm::mat4(1.0f);
    app.getShader()->setMat4("projection", projection);

    
    //for (unsigned int i = 0; i < 10; i++) {
    //  glm::mat4 model = glm::mat4(1.0f);
    //  model = glm::translate(model, cubePositions[i]);
    //  float angle = 20.0f * i;
    //  model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    //  app.getShader()->setMat4("model", model);
    //  skelly::Renderer::submit(app.getVertexArray());
    //}
  }

}
