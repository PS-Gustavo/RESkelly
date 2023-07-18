#include <application.h>

namespace skelly {
    Application* Application::_s_instance;

    Application::Application() {
        _s_instance = this;
        _m_window = nullptr;
        
        Logger::init();
    }

    Application::~Application() {}
    
    // Creates the window instance for the application.
    // CAREFUL! You need to create the window context before creating the layers and overlays.
    void Application::createWindow() {
        _m_window = std::unique_ptr<Window>(Window::create());
        _m_window->setEventCallback(BIND_EVENT_FN(Application::onEvent));

        _m_imguiLayer = new ImguiLayer();
        pushOverlay(_m_imguiLayer);


        // triangle drawing example
        // vertex buffer creation
        glGenVertexArrays(1, &_m_vertexArray);
        glBindVertexArray(_m_vertexArray);

        glGenBuffers(1, &_m_vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, _m_vertexBuffer);

        float vertices[3*3] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.8f, 0.0f
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), nullptr);

        // index buffer creation
        glGenBuffers(1, &_m_indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _m_indexBuffer);

        unsigned int indices[3] = {0, 1, 2};
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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
            glBindVertexArray(_m_vertexArray);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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