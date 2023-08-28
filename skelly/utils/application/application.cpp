
/****************************************************************************************
 * 
 * Frontal
 * Application Module
 * 
 ****************************************************************************************
 * 
 * Changelog:
 * 
 * - 0.1.0: Initial implementation; Basic logging, windowing, layer, rendering and events
 * 
 **************************************************************************************** 
 * 
 * Description:
 * 
 * This is the engine focal point for the Body project.
 * This module initializes all Skelly structures as necessary, and provides the necessary
 * tools and modules to create the desired end application.
 * 
 ***************************************************************************************/

#include <application.h>
#include <render.h>

namespace skelly {
    Application* Application::_s_instance;

    // Lifetime handlers

    // If you modify the constructor behavior, be careful! You need to create the window 
    // context before creating the layers and overlays.
    Application::Application() {
        _s_instance = this;
        _m_window = nullptr;
        
        Logger::init();
        _m_window = std::unique_ptr<Window>(Window::create());
        _m_window->setEventCallback(BIND_EVENT_FN(Application::onEvent));

        // debug layer
        // WIP: pop/push layers needs to support ImguiLayer w/o raw pointer translation
        _m_imguiLayer = std::unique_ptr<ImguiLayer>(ImguiLayer::create("ImGui Overlay"));
        pushOverlay(_m_imguiLayer.get());
    }

    Application::~Application() {
        // Remove from stack before destroying uq pointer;
        popOverlay(_m_imguiLayer.get());
    }
    
    void Application::mockTriangle() {
        // triangle drawing example

        _m_vertexArray.reset(VertexArray::create());

        float vertices[6*7] = {
            -0.5f, -0.5f, 0.0f, 0.4f, 0.1f, 0.6f, 1.0f,
            0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 0.4f, 1.0f,
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

    // layer stack handlers

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

    // event handlers

    void Application::onEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::_m_onWindowClose));
 
        for (auto it = _m_layerStack.end(); it != _m_layerStack.begin();) {
            (*--it)->onEvent(e);
            if (e.isHandled()) break;
        }
    }

    bool Application::_m_onWindowClose([[maybe_unused]] WindowCloseEvent& e) {
        _m_running = false;
        return _m_running;
    }    

    // main application loop

    void Application::run() {
        while(_m_running) {            

            // standard clear operation
            RenderCommands::setClearColor({0.1f, 0.1f, 0.1f, 1});
            RenderCommands::clear();

            // draw if there are contents in the vertexArray
            if (_m_shader.use_count()) {
                _m_shader->bind();
                Renderer::submit(_m_vertexArray);
            }
            
            // sweep and update layers
            for (Layer* layer : _m_layerStack) {
                layer->onUpdate();
            }
            if (_m_imguiLayer != nullptr) {
                _m_imguiLayer->begin();
                // WIP: Add support for custom ImGui layers
                // for (Layer* layer : _m_layerStack) {
                //     layer->onImguiRender();
                // }
                _m_imguiLayer->onImguiRender();
                _m_imguiLayer->end();
            }

            if (_m_window != nullptr) _m_window->onUpdate();
        }
    }
}