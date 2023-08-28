
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

#pragma once

#ifndef PCH_ENABLED
    #include <window.h>
    #include <layer.h>
    #include <mouseEvent.h>
    #include <keyEvent.h>
#endif

namespace skelly {

    class SKELLY_API ImguiLayer : public Layer {
        public:
            // constr has to be defined in this scope for its symbol name to be 
            // properly created, other plat-specific functions are pure virtual
            ImguiLayer([[maybe_unused]] const std::string& name) {}

            virtual void onAttach() = 0;
            virtual void onDetach() = 0;
            virtual void onImguiRender() = 0;

            virtual void imguiOverlayPane(bool* p_open) = 0;

            virtual void begin() = 0;
            virtual void end() = 0;

            void setWindow(Window* window) { _m_window = window; }
            Window* getWindow() { return _m_window; }

            static APITarget getTargetAPI() { return _s_targetAPI; }

            // agnostic creator
            static ImguiLayer* create(const std::string& overlayName = "ImGui Overlay");
        private:
            float _m_time = 0.0f;
            Window* _m_window = nullptr;
            static APITarget _s_targetAPI;
    };
}