#ifndef __LAYER_HPP_INCLUDED__
#define __LAYER_HPP_INCLUDED__

#include "Box3D/Core.hpp"
#include "Box3D/Events/Event.hpp"

namespace box3d {

    class Layer {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event& event)  {}

        inline const std::string& GetName() const { return m_debugName; }
    protected:
        std::string m_debugName;
    };

}

#endif // !__LAYER_HPP_INCLUDED__
