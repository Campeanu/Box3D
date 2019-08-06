#ifndef __LAYERSTACK_HPP_INCLUDED__
#define __LAYERSTACK_HPP_INCLUDED__

#include <vector>

#include "Box3D/Core.hpp"
#include "Layer.hpp"

namespace box3d {

    class LayerStack {
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverLayer(Layer* overlay);

        void PopLayer(Layer* layer);
        void PopOverLayer(Layer* overlay);

        std::vector<Layer*>::iterator begin () { return m_layers.begin(); }
        std::vector<Layer*>::iterator end   () { return m_layers.end();   }

    private:
        std::vector<Layer*> m_layers;
        std::vector<Layer*>::iterator m_layerInsert;

    };

}

#endif // !__LAYERSTACK_HPP_INCLUDED__
