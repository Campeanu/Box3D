#ifndef __IMGUILAYER_HPP_INCLUDED__
#define __IMGUILAYER_HPP_INCLUDED__

#include "Box3D/Log.hpp"
#include "Box3D/Layer.hpp"

#include "Box3D/Events/ApplicationEvent.hpp"
#include "Box3D/Events/KeyEvent.hpp"
#include "Box3D/Events/MouseEvent.hpp"

#include "Box3D/Core.hpp"

namespace box3d { 

    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();
    private:
        float m_Time = 0.0f;
    };

}

#endif // !__IMGUILAYER_HPP_INCLUDED__
