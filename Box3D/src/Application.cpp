#include "Box3D/Application.hpp"

#include "Box3D/Events/ApplicationEvent.hpp"
#include "Box3D/Log.hpp"

namespace box3d {

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
        if (this->checkForLogin())
        {
            this->getUserData();
            this->login = new Login(sql::SQLString(this->mailusername.c_str()), sql::SQLString(this->password.c_str()));
        }
    } 
        
    Application::~Application()
    {
        delete this->login;
    }

    void Application::run()
    {
        
        /**
         * Test events
         */
        WindowResizeEvent e(1280, 720);
        BOX3D_TRACE(e);

        while(true);
    }

} // namespace box3d
