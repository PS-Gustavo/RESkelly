
/****************************************************************************************
 * 
 * Ethmoid
 * Layer Module
 * 
 ****************************************************************************************
 * 
 * Changelog:
 * 
 * - 0.1.0: Initial implementation; Support to layer stack and ImGui overlay
 * 
 **************************************************************************************** 
 * 
 * Description:
 * 
 * This is the module that controls layers and overlays for organized rendering flow.
 * Layer provides the abstraction, which is defined by ImguiLayer for Imgui integration.
 * LayerStack instantiates layers and ImGui Overlays for controlled access.
 * 
 ***************************************************************************************/

#include <layer.h>

namespace skelly {

    Layer::Layer(const std::string& debugName) : m_debugName(debugName) {}

}