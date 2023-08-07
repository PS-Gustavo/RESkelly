
/****************************************************************************************
 * 
 * Parietal
 * Window Module
 * 
 ****************************************************************************************
 * 
 * Changelog:
 * 
 * - 0.1.0: Initial implementation; Basic OpenGL support, basic creation procedures with
 * fixed dimensions;
 * 
 **************************************************************************************** 
 * 
 * Description:
 * 
 * This is the Window creator module. It allows for the creation of a single window
 * instance. Window calls upo GraphicContext, which is an interface to the API specific
 * RenderContext. Platform specific implementation is carried out in Skelly/API/
 * 
 ***************************************************************************************/

#include <window.h>
#include <opengl.h>

#ifdef PLATFORM_LINUX
#endif

namespace skelly {

    APITarget Window::_s_targetAPI = APITarget::OpenGL;

    Window* Window::create(const WindowProps& props) {
        switch (Window::getTargetAPI()) {
            case APITarget::OpenGL:
                return new OpenGLWindow(props);
            default:
                SKELLY_ASSERT(false, "Window::create: No Rendering API found!");
                return nullptr;
        }

        SKELLY_ASSERT(false, "Window::create: unknown behavior.");
        return nullptr;
    }

}