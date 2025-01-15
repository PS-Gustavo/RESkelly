#include <opengl.h>

#include <application.h>

#define IMGUI_IMPL_API
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace skelly {

    int KeyPressedEvent::_m_repeatCount = 0;

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

    // RenderContext

    OpenGLRenderContext::OpenGLRenderContext(GLFWwindow* windowHandle) : windowHandle_(windowHandle) {
        SKELLY_ASSERT(windowHandle, "OpenGLRenderContext: Window handle is null.")
    }

    void OpenGLRenderContext::init() {
        glfwMakeContextCurrent(windowHandle_);
        int status = gladLoadGL(glfwGetProcAddress);
        SKELLY_ASSERT(status, "OpenGLRenderContext::init: Failed to initialize Glad.")
        
        // init log hardware dump
        SKELLY_LOG_INFO("Vendor: {0}", (const char*) glGetString(GL_VENDOR));
        SKELLY_LOG_INFO("Renderer Hardware: {0}", (const char*) glGetString(GL_RENDERER));
        SKELLY_LOG_INFO("Version: {0}", (const char*) glGetString(GL_VERSION));

        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRenderContext::swapBuffers() {        
        glfwSwapBuffers(windowHandle_);
    }

    // Window

    static bool s_GLFWInitialized = false;

    static void GLFWErrorCallback(int error, const char* desc) {
        SKELLY_LOG_ERROR("GLFW Error: ({0}) {1}", error, desc);
    }

    OpenGLWindow::OpenGLWindow(const WindowProps& props) {
        init(props);
    }

    OpenGLWindow::~OpenGLWindow() {
        shutdown();
    };

    double OpenGLWindow::getTime() {
      return glfwGetTime();
    }

    void OpenGLWindow::init(const WindowProps& props) {
        data_.title = props.title;
        data_.width = props.width;
        data_.height = props.height;

        SKELLY_LOG_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);
        if(!s_GLFWInitialized) {
            int success = glfwInit();
            SKELLY_ASSERT(success, "OpenGLWindow::init: Could not initialize GLFW");
            glfwSetErrorCallback(GLFWErrorCallback);
            s_GLFWInitialized = true;
        }

        window_ = glfwCreateWindow((int)props.width, (int)props.height, data_.title.c_str(), nullptr, nullptr);

        context_ = new OpenGLRenderContext(window_);  
        context_->init();

        glfwSetWindowUserPointer(window_, &data_);
        setVSync(true);

        // GLFW callbacks
        glfwSetWindowSizeCallback(window_, [](GLFWwindow* window, int width, int height){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            data.width = width;
            data.height = height;
            
            WindowResizeEvent event(width, height);
            data.eventCallback(event);
        });

        glfwSetWindowCloseCallback(window_, [](GLFWwindow* window){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowCloseEvent event;
            data.eventCallback(event);
        });

        glfwSetKeyCallback(window_, [](GLFWwindow* window, int key,  [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mods){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch(action) {
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(key);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_PRESS: {
                    KeyPressedEvent event(key);
                    event.setRepeatCount(0);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(key);
                    event.increaseRepeatCount();
                    data.eventCallback(event);
                    break;
                }
                default: {
                    break;
                }
            }
        });

        glfwSetCharCallback(window_, [](GLFWwindow* window, unsigned int keycode){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            KeyTypedEvent event(keycode);
            data.eventCallback(event);
        });

        glfwSetMouseButtonCallback(window_, [](GLFWwindow* window, int button, int action, [[maybe_unused]] int mods){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch(action) {
                case GLFW_RELEASE: {
                    MouseButtonReleasedEvent event(button);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(button);
                    data.eventCallback(event);
                    break;
                }
                default: {
                    break;
                }
            }
        });

        glfwSetScrollCallback(window_, [](GLFWwindow* window, double xOffset, double yOffset){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.eventCallback(event);
        });

        glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double xPos, double yPos){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.eventCallback(event);
        });
    }

    void OpenGLWindow::shutdown() {
        glfwDestroyWindow(window_);
    }

    void OpenGLWindow::onUpdate() {
        glfwPollEvents();
        context_->swapBuffers();
    }

    void OpenGLWindow::setVSync(bool enabled) {
        (enabled) ? glfwSwapInterval(1) : glfwSwapInterval(0);
        data_.vSync = enabled;
    }

    bool OpenGLWindow::isVSync() const {
        return data_.vSync;
    }

    // ImGui

    OpenGLImgui::OpenGLImgui(const std::string& overlayName) : ImguiLayer(overlayName) {}

    void OpenGLImgui::onAttach() {
        
        // Decide GL+GLSL versions
        const char* glsl_version = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
        //io.ConfigViewportsNoAutoMerge = true;
        //io.ConfigViewportsNoTaskBarIcon = true;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        GLFWwindow* window = static_cast<GLFWwindow*>(Application::getApplication().getWindow().getNativeWindow());


        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

    }

    void OpenGLImgui::onDetach() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void OpenGLImgui::begin() {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void OpenGLImgui::end() {

        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::getApplication();
        io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void OpenGLImgui::imguiOverlayPane(bool* p_open) {
        static int location = 0;
        ImGuiIO& io = ImGui::GetIO();
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
        if (location >= 0)
        {
            const float PAD = 10.0f;
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
            ImVec2 work_size = viewport->WorkSize;
            ImVec2 window_pos, window_pos_pivot;
            window_pos.x = (location & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
            window_pos.y = (location & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
            window_pos_pivot.x = (location & 1) ? 1.0f : 0.0f;
            window_pos_pivot.y = (location & 2) ? 1.0f : 0.0f;
            ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
            ImGui::SetNextWindowViewport(viewport->ID);
            window_flags |= ImGuiWindowFlags_NoMove;
        }
        else if (location == -2)
        {
            // Center window
            ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
            window_flags |= ImGuiWindowFlags_NoMove;
        }
        ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
        if (ImGui::Begin("Debug Overlay", p_open, window_flags))
        {
            // ImGui::Separator();
            if (ImGui::IsMousePosValid())
                ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
            else
                ImGui::Text("Mouse Position: <invalid>");
            ImGui::Text("%.1f FPS", io.Framerate);
            // if (ImGui::BeginPopupContextWindow())
            // {
            //     if (ImGui::MenuItem("Custom",       NULL, location == -1)) location = -1;
            //     if (ImGui::MenuItem("Center",       NULL, location == -2)) location = -2;
            //     if (ImGui::MenuItem("Top-left",     NULL, location == 0)) location = 0;
            //     if (ImGui::MenuItem("Top-right",    NULL, location == 1)) location = 1;
            //     if (ImGui::MenuItem("Bottom-left",  NULL, location == 2)) location = 2;
            //     if (ImGui::MenuItem("Bottom-right", NULL, location == 3)) location = 3;
            //     if (p_open && ImGui::MenuItem("Close")) *p_open = false;
            //     ImGui::EndPopup();
            // }
        }
        ImGui::End();
    }

    void OpenGLImgui::onImguiRender() {

        #ifdef DEBUG_ENABLED
        static bool show = true;
        // ImGui::ShowDemoWindow(&show);
        imguiOverlayPane(&show);
        #endif
        
    }

    // Input

    bool OpenGLInput::m_isKeyPressedImpl(int keycode) {
        auto window = static_cast<GLFWwindow*>(Application::getApplication().getWindow().getNativeWindow());
        auto state = glfwGetKey(window, keycode);
        return ((state == GLFW_PRESS) || (state == GLFW_REPEAT));
    }

    bool OpenGLInput::m_isMouseButtonPressedImpl(int button) {
        auto window = static_cast<GLFWwindow*>(Application::getApplication().getWindow().getNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return (state == GLFW_PRESS);
    }

    std::pair<float, float> OpenGLInput::m_getMouseCoordImpl() {
        auto window = static_cast<GLFWwindow*>(Application::getApplication().getWindow().getNativeWindow());
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        return std::make_pair((float)xPos, (float)yPos);
    }

    float OpenGLInput::m_getMouseXImpl() {
        auto[x, y] = m_getMouseCoordImpl();
        return x;
    }

    float OpenGLInput::m_getMouseYImpl() {
        auto[x, y] = m_getMouseCoordImpl();
        return y;
    }

    // VertexArray

    OpenGLVertexArray::OpenGLVertexArray() {
        glCreateVertexArrays(1, &rendererId_);
    }

    OpenGLVertexArray::~OpenGLVertexArray() {
        glDeleteVertexArrays(1, &rendererId_);
    }

    void OpenGLVertexArray::bind() const {
        glBindVertexArray(rendererId_);
    }

    void OpenGLVertexArray::unbind() const {
        glBindVertexArray(0);
    }
    
    void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {
        
        SKELLY_ASSERT(vertexBuffer->getLayout().getElements().size(), "OpenGLVertexArray::addVertexBuffer: No layout has been created for the VertexBuffer");

        glBindVertexArray(rendererId_);
        vertexBuffer->bind();
        uint32_t index = 0;
        const auto& layout = vertexBuffer->getLayout();
        for (const auto& element : layout) {
            SKELLY_LOG_INFO("Element: {0}, {1}, {2}, {3}, {4}, {5}",
                index,
                element.getComponentCount(),
                getElementType(element.type),
                element.isNormalized,
                layout.getStride(),
                element.offset);
            glVertexAttribPointer(
                index, 
                element.getComponentCount(),
                getElementType(element.type),
                element.isNormalized ? GL_TRUE : GL_FALSE,
                layout.getStride(),
                (const void*)(intptr_t) element.offset
            );
            glEnableVertexAttribArray(index);
            index++;
        }
        
        vertexBuffers_.push_back(vertexBuffer);
         
    }

    void OpenGLVertexArray::addIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
        glBindVertexArray(rendererId_);
        indexBuffer->bind();
        indexBuffers_.push_back(indexBuffer);
    }

    const std::vector<std::shared_ptr<VertexBuffer>>& OpenGLVertexArray::getVertexBuffers() const {
        return vertexBuffers_;
    }
    const std::vector<std::shared_ptr<IndexBuffer>>& OpenGLVertexArray::getIndexBuffers() const {
        return indexBuffers_;
    }

    // VertexBuffer

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) {
        glCreateBuffers(1, &rendererId_);
        glBindBuffer(GL_ARRAY_BUFFER, rendererId_);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer() {
        glDeleteBuffers(1, &rendererId_);
    }

    void OpenGLVertexBuffer::bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, rendererId_);
    }

    void OpenGLVertexBuffer::unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    // IndexBuffer

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : count_(count) {
        glCreateBuffers(1, &rendererId_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count* sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        glDeleteBuffers(1, &rendererId_);
    }

    void OpenGLIndexBuffer::bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId_);
    }

    void OpenGLIndexBuffer::unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    // Shader

    

    OpenGLShader::OpenGLShader(uint8_t createMode, std::string& vertexSrc, std::string& fragmentSrc) {
        
        switch (createMode) {
            case 0:
                break;
            case 1:
                break;
            default:
                SKELLY_ASSERT(false, "OpenGLShader: Incorrect Shader load mode");
                return;
        }


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
            SKELLY_ASSERT(false, "OpenGLShader: Vertex shader compilation failure");

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
            SKELLY_ASSERT(false, "OpenGLShader: Fragment shader compilation failure");

            return;
        }

        rendererId_ = glCreateProgram();
        GLuint program = rendererId_;

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
            SKELLY_ASSERT(false, "OpenGLShader: Shader linking failure.");

            return;
        }

        glDetachShader(program, vertexShader);
        glDetachShader(program, fragmentShader);

    }

    OpenGLShader::~OpenGLShader() {
        glDeleteProgram(rendererId_);
    }

    int OpenGLShader::getMaxVertexAttributes() const {
        int nrAttributes;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
        return nrAttributes;
    }

    void OpenGLShader::bind() const {
        glUseProgram(rendererId_);
    }

    void OpenGLShader::unbind() const {
        glUseProgram(0);
    }

}
