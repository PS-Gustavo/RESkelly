#pragma once

#include <graphicContext.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#ifndef PCH_ENABLED
    #include <defs.h>
    #include <logger.h>
#endif

class GLFWwindow;

namespace skelly {
    
    class RenderContext : public GraphicContext {
        public:
            RenderContext(GLFWwindow* windowHandle);

            virtual void init() override;
            virtual void swapBuffers() override;
        private:
            GLFWwindow* _m_windowHandle;
            
    };
}