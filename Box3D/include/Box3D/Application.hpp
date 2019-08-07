#ifndef __APPLICATION_HPP_INCLUDED__
#define __APPLICATION_HPP_INCLUDED__

#include <iostream>
#include <sstream>
#include <memory>

#include <Json/value.hpp>
#include <SystemAbstractions/File.hpp>
#include <SystemAbstractions/StringExtensions.hpp>

#include <LoginSystem/Login.hpp>
#include <MySQL/MySQL.hpp>

#include "Events/Event.hpp"
#include "Box3D/Events/ApplicationEvent.hpp"
#include "Window.hpp"
#include "Box3D/LayerStack.hpp"

#include "Box3D/ImGUI/ImGuiLayer.hpp"

    namespace box3d {
        
        class Application
        {
        public:
            Application();
            virtual ~Application() = default;

            void Run();

            void OnEvent(Event& e);

            void PushLayer(Layer* layer);
            void PushOverlay(Layer* layer);

            inline Window& GetWindow() { return *m_Window; }

            inline static Application& Get() { return *s_Instance; }
        private:
            bool OnWindowClose(WindowCloseEvent& e);
        private:
            std::unique_ptr<Window> m_Window;
            ImGuiLayer* m_ImGuiLayer;
            bool m_Running = true;
            LayerStack m_LayerStack;
            float m_LastFrameTime = 0.0f;
        private:
            static Application* s_Instance;
        };

        // To be defined in CLIENT
        Application* CreateApplication();

    } // namespace box3d

#endif // !__APPLICATION_HPP_INCLUDED__
