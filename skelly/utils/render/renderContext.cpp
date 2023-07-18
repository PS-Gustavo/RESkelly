
#include <renderContext.h>

namespace skelly {
    
    RenderContext::RenderContext(GLFWwindow* windowHandle) : _m_windowHandle(windowHandle) {
        SKELLY_ASSERT(windowHandle, "Window handle is null.")
    }

    void RenderContext::init() {
        glfwMakeContextCurrent(_m_windowHandle);
        int status = gladLoadGL(glfwGetProcAddress);
        SKELLY_ASSERT(status, "Failed to initialize Glad.")
    }

    void RenderContext::swapBuffers() {        
        glfwSwapBuffers(_m_windowHandle);
    }
}