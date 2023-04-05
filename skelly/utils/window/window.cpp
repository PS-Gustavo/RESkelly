#include <window.h>

#ifdef PLATFORM_LINUX

namespace skelly {

    static bool s_GLFWInitialized = false;

    Window* Window::create(const WindowProps& props) {
        return new LinuxWindow(props);
    }

    LinuxWindow::LinuxWindow(const WindowProps& props) {
        init(props);
    }

    LinuxWindow::~LinuxWindow() {
        shutdown();
    };

    void LinuxWindow::init(const WindowProps& props) {
        m_data.title = props.title;
        m_data.width = props.width;
        m_data.height = props.height;

        SKELLY_LOG_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);
        if(!s_GLFWInitialized) {
            int success = glfwInit();
            SKELLY_ASSERT(success, "Could not initialize GLFW");

            s_GLFWInitialized = true;
        }

        m_window = glfwCreateWindow((int)props.width, (int)props.height, m_data.title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_window);
        glfwSetWindowUserPointer(m_window, &m_data);
        setVSync(true);

    }

    void LinuxWindow::shutdown() {
        glfwDestroyWindow(m_window);
    }

    void LinuxWindow::onUpdate() {
        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }

    void LinuxWindow::setVSync(bool enabled) {
        enabled ? glfwSwapInterval(1) : glfwSwapInterval(0);

        m_data.vSync = enabled;
    }

    bool LinuxWindow::isVSync() const {
        return m_data.vSync;
    }

}
#endif

