#include "Box3D/Application.hpp"

#include "Box3D/Log.hpp"

#include <GLFW/glfw3.h>

namespace box3d {

    #define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    void Application::getUserData()
    {
        std::cout << "Login ... \n";
        std::cout << "[username/e-mail]: ";
        std::cin >> this->mailusername;
        std::cout << "[password]: ";
        std::cin >> this->password;
    }

    bool Application::checkForLogin()
    {
        return false;
    }

    Application::Application()
    {
        this->m_running = true;

        this->m_window = std::unique_ptr<Window>(Window::create());
        this->m_window->setEventCallback(BIND_EVENT_FN(OnEvent));

        if (this->checkForLogin())
        {
            this->getUserData();
            this->login = new Login(sql::SQLString(this->mailusername.c_str()), sql::SQLString(this->password.c_str()));
        }
    } 
        
    Application::~Application()
    {
        // delete this->login;
    }

    void Application::PushLayer(Layer* layer)
    {
        m_layerStack.PushLayer(layer);
    }

    void Application::PushOverLayer(Layer* layer)
    {
        m_layerStack.PushOverLayer(layer);
    }


    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

        BOX3D_CORE_TRACE("{0}", e);

        for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.GetHandled())
                break;
        }

    }

    void Application::run()
    {
        
        while(this->m_running)
        {
        
            // glClearColor(1, 0, 1, 1);
            // glClear(GL_COLOR_BUFFER_BIT);

            for (Layer* layer : m_layerStack)
                layer->OnUpdate();

            m_window->update();
        
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        this->m_running = false;
        return true;
    }

} // namespace box3d
