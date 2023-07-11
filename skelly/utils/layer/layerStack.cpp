#include <layerStack.h>

namespace skelly {

    LayerStack::LayerStack() {
        _m_layerIteratorIndex = 0;
    }

    LayerStack::~LayerStack() {
        for (Layer* layer : _m_layers) delete layer;
    }

    void LayerStack::pushLayer(Layer* layer) {
        _m_layers.emplace(_m_layers.begin() + _m_layerIteratorIndex, layer);
        _m_layerIteratorIndex++;
    }

    void LayerStack::popLayer(Layer* layer) {
        auto it = std::find(_m_layers.begin(), _m_layers.end(), layer);
        if (it != _m_layers.end()) {
            _m_layers.erase(it);
            _m_layerIteratorIndex--;
        }
    }

    void LayerStack::pushOverlay(Layer* overlay) {
        _m_layers.emplace_back(overlay);
    }

    void LayerStack::popOverlay(Layer* overlay) {
        auto it = std::find(_m_layers.begin(), _m_layers.end(), overlay);
        if (it != _m_layers.end()) {
            _m_layers.erase(it);
        }
    }

}