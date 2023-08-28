
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

#pragma once

#ifndef PCH_ENABLED
    #include <defs.h>
    #include <event.h>
#endif

namespace skelly {

    class SKELLY_API Layer {
        public:
            Layer(const std::string& name = "Layer");
            virtual ~Layer() {}

            virtual void onAttach() {}
            virtual void onDetach() {}
            virtual void onUpdate() {}
            virtual void onEvent([[maybe_unused]] Event& event) {}

            inline const std::string& getName() const { return m_debugName; }
        
        protected:
            std::string m_debugName;
    };
}