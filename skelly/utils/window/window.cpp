#include <window.h>
#include <opengl.h>

#ifdef PLATFORM_LINUX
#endif

namespace skelly {

    Window* Window::create(const WindowProps& props) {
        return new OpenGLWindow(props);
    }

}