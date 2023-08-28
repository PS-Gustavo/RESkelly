
/****************************************************************************************
 * 
 * Occipital
 * ImGui Overlay Module
 * 
 ****************************************************************************************
 * 
 * Changelog:
 * 
 * - 0.1.0: Initial implementation; Render GUI interface, basic overlay debug features.
 * 
 **************************************************************************************** 
 * 
 * Description:
 * 
 * ImguiLayer is an expansion of the Layer module, and is built to be GUI agnostic. It 
 * provides basic features to debug applications in a overlay during runtime. The 
 * functions called by the Skelly module are consumed directly from ImGui's backend.
 * 
 ***************************************************************************************/

#include <imguiLayer.h>
#include <opengl.h>

namespace skelly {

    APITarget ImguiLayer::_s_targetAPI = APITarget::OpenGL;

    ImguiLayer* ImguiLayer::create(const std::string& overlayName) {
        switch (ImguiLayer::getTargetAPI()) {
            case APITarget::OpenGL:
                return new OpenGLImgui(overlayName);
            default:
                SKELLY_ASSERT(false, "ImguiLayer::create: No Rendering API Found!");
                return nullptr;
        }

        SKELLY_ASSERT(false, "ImguiLayer::create: unknown behavior.");
    }
}