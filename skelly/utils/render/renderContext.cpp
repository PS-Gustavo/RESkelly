#include <iostream>
#include <renderContext.h>

namespace skelly {
    
    RenderContext::RenderContext(GLFWwindow* windowHandle) : _m_windowHandle(windowHandle) {
        SKELLY_ASSERT(windowHandle, "Window handle is null.")
    }

    void RenderContext::init() {
        glfwMakeContextCurrent(_m_windowHandle);
        int status = gladLoadGL(glfwGetProcAddress);
        SKELLY_ASSERT(status, "Failed to initialize Glad.")
        
        // init log hardware dump
        SKELLY_LOG_INFO("Vendor: {0}", (const char*) glGetString(GL_VENDOR));
        SKELLY_LOG_INFO("Renderer Hardware: {0}", (const char*) glGetString(GL_RENDERER));
        SKELLY_LOG_INFO("Version: {0}", (const char*) glGetString(GL_VERSION));
    }

    void RenderContext::swapBuffers() {        
        glfwSwapBuffers(_m_windowHandle);
    }
}