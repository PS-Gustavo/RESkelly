
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
    #include <layer.h>
#endif

namespace skelly {

    class SKELLY_API LayerStack {
        public:
            LayerStack();
            ~LayerStack();

            void pushLayer(Layer* layer);
            void popLayer(Layer* layer);

            void pushOverlay(Layer* overlay);
            void popOverlay(Layer* overlay);

            std::vector<Layer*>::iterator begin() { return _m_layers.begin(); }
            std::vector<Layer*>::iterator end() { return _m_layers.end(); }

        private:
            std::vector<Layer*> _m_layers;
            unsigned int _m_layerIteratorIndex;
    };
}
