#include <layerStack.h>

namespace skelly {

    LayerStack::LayerStack() {
        _m_layerIterator = _m_layers.begin();
    }

    LayerStack::~LayerStack() {
        for (Layer* layer : _m_layers) delete layer;
    }

    void LayerStack::pushLayer(Layer* layer) {
        _m_layerIterator = _m_layers.emplace(_m_layerIterator, layer);
    }

    void LayerStack::popLayer(Layer* layer) {
        auto it = std::find(_m_layers.begin(), _m_layers.end(), layer);
        if (it != _m_layers.end()) {
            _m_layers.erase(it);
            _m_layerIterator--;
        }
    }

    void LayerStack::pushOverlay(Layer* overlay) {
        _m_layers.emplace_back(overlay);
        if (_m_layers.size() == 1) {
            _m_layerIterator = _m_layers.begin();
        }
    }

    void LayerStack::popOverlay(Layer* overlay) {
        auto it = std::find(_m_layers.begin(), _m_layers.end(), overlay);
        if (it != _m_layers.end()) {
            _m_layers.erase(it);
        }
    }

}