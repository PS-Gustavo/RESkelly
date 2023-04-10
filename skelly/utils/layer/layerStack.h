#pragma once

#ifndef PCH_ENABLED
    #include <layer.h>
    #include <defs.h>
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
            std::vector<Layer*>::iterator _m_layerIterator;

    };

}
