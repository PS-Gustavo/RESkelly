#include <window.h>

#ifdef PLATFORM_LINUX
#endif

namespace skelly {

    static bool s_GLFWInitialized = false;

    static void GLFWErrorCallback(int error, const char* desc) {
        SKELLY_LOG_ERROR("GLFW Error: ({0}) {1}", error, desc);
    }

    Window* Window::create(const WindowProps& props) {
        return new PlatWindow(props);
    }

    PlatWindow::PlatWindow(const WindowProps& props) {
        init(props);
    }

    PlatWindow::~PlatWindow() {
        shutdown();
    };

    void PlatWindow::init(const WindowProps& props) {
        m_data.title = props.title;
        m_data.width = props.width;
        m_data.height = props.height;

        SKELLY_LOG_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);
        if(!s_GLFWInitialized) {
            int success = glfwInit();
            SKELLY_ASSERT(success, "Could not initialize GLFW");
            glfwSetErrorCallback(GLFWErrorCallback);
            s_GLFWInitialized = true;
        }

        _m_window = glfwCreateWindow((int)props.width, (int)props.height, m_data.title.c_str(), nullptr, nullptr);

        #ifdef USING_OPENGL
        _m_context = new RenderContext(_m_window);  
        #endif
        _m_context->init();

        glfwSetWindowUserPointer(_m_window, &m_data);
        setVSync(true);

        // GLFW callbacks
        glfwSetWindowSizeCallback(_m_window, [](GLFWwindow* window, int width, int height){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            data.width = width;
            data.height = height;
            
            WindowResizeEvent event(width, height);
            data.eventCallback(event);
        });

        glfwSetWindowCloseCallback(_m_window, [](GLFWwindow* window){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowCloseEvent event;
            data.eventCallback(event);
        });

        glfwSetKeyCallback(_m_window, [](GLFWwindow* window, int key, int action, [[maybe_unused]] int scancode, [[maybe_unused]] int mods){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            // WIP: Change action mapping from glfw specific to Skelly specific (framework agnostic)
            switch(action) {
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(key);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_PRESS: {
                    KeyPressedEvent event(key, 0);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(key, 1);
                    data.eventCallback(event);
                    break;
                }
                default: {
                    break;
                }
            }
        });

        glfwSetCharCallback(_m_window, [](GLFWwindow* window, unsigned int keycode){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            KeyTypedEvent event(keycode);
            data.eventCallback(event);
        });

        glfwSetMouseButtonCallback(_m_window, [](GLFWwindow* window, int button, int action, [[maybe_unused]] int mods){
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

        glfwSetScrollCallback(_m_window, [](GLFWwindow* window, double xOffset, double yOffset){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.eventCallback(event);
        });

        glfwSetCursorPosCallback(_m_window, [](GLFWwindow* window, double xPos, double yPos){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.eventCallback(event);
        });

    }

    void PlatWindow::shutdown() {
        glfwDestroyWindow(_m_window);
    }

    void PlatWindow::onUpdate() {
        glfwPollEvents();
        _m_context->swapBuffers();
    }

    void PlatWindow::setVSync(bool enabled) {
        (enabled) ? glfwSwapInterval(1) : glfwSwapInterval(0);
        m_data.vSync = enabled;
    }

    bool PlatWindow::isVSync() const {
        return m_data.vSync;
    }

}