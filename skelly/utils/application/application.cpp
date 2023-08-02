#include <application.h>

namespace skelly {
    Application* Application::_s_instance;

    Application::Application() {
        _s_instance = this;
        _m_window = nullptr;
        
        Logger::init();
    }

    Application::~Application() {}
    
    void Application::mockTriangle() {
        // triangle drawing example

        _m_vertexArray.reset(VertexArray::create());

        float vertices[6*7] = {
            -0.5f, -0.5f, 0.0f, 0.4f, 0.1f, 0.6f, 1.0f,
            0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            0.0f,  0.8f,  0.0f, 0.4f, 0.1f, 0.6f, 1.0f,
        };

        std::shared_ptr<VertexBuffer> vertexBuffer;
        vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));

        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" },
        };
        vertexBuffer->setLayout(layout);

        _m_vertexArray->addVertexBuffer(vertexBuffer);

        // index buffer creation
        uint32_t indices[3] = {0, 1, 2};
        std::shared_ptr<IndexBuffer> indexBuffer;
        indexBuffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));
        _m_vertexArray->addIndexBuffer(indexBuffer);

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

        _m_shader.reset(Shader::create(vertexSrc, fragmentSrc));
    }

    // Creates the window instance for the application.
    // CAREFUL! You need to create the window context before creating the layers and overlays.
    void Application::createWindow() {
        _m_window = std::unique_ptr<Window>(Window::create());
        _m_window->setEventCallback(BIND_EVENT_FN(Application::onEvent));

        _m_imguiLayer = new ImguiLayer();
        pushOverlay(_m_imguiLayer);

        mockTriangle();
    }

    void Application::pushLayer(Layer* layer) {
        SKELLY_LOG_TRACE("Creating new layer: {0}", layer->getName());
        _m_layerStack.pushLayer(layer);
        layer->onAttach();
    }
    void Application::popLayer(Layer* layer) {
        SKELLY_LOG_TRACE("Destroying layer: {0}", layer->getName());
        _m_layerStack.popLayer(layer);
        layer->onDetach();
    }
    void Application::pushOverlay(Layer* overlay) {
        SKELLY_LOG_TRACE("Creating new overlay: {0}", overlay->getName());
        _m_layerStack.pushOverlay(overlay);
        overlay->onAttach();
    }
    void Application::popOverlay(Layer* overlay) {
        SKELLY_LOG_TRACE("Destroying overlay: {0}", overlay->getName());
        _m_layerStack.popOverlay(overlay);
        overlay->onDetach();
    }

    void Application::onEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::_m_onWindowClose));
        // SKELLY_LOG_TRACE("{0}", e);

        for (auto it = _m_layerStack.end(); it != _m_layerStack.begin();) {
            (*--it)->onEvent(e);
            if (e.isHandled()) break;
        }
    }

    void Application::run() {
        while(_m_running) {            
            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            
            // drawing a triangle
            _m_shader->bind();
            _m_vertexArray->bind();
            glDrawElements(GL_TRIANGLES, _m_vertexArray->getIndexBuffers()[0]->getCount(), GL_UNSIGNED_INT, nullptr);

            for (Layer* layer : _m_layerStack) {
                layer->onUpdate();
            }

            _m_imguiLayer->begin();
            for (Layer* layer : _m_layerStack) {
                layer->onImguiRender();
            }
            _m_imguiLayer->end();

            if(_m_window != nullptr) _m_window->onUpdate();
        }
        
    }

    bool Application::_m_onWindowClose([[maybe_unused]] WindowCloseEvent& e) {
        _m_running = false;
        return _m_running;
    }    
}