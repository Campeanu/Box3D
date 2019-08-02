#include "Box3D/Application.hpp"

namespace box3d {

    void Application::getUserData()
    {
        std::cout << "Login ... \n";
        std::cout << "[username/e-mail]: ";
        std::cin >> this->mailusername;
        std::cout << "[password]: ";
        std::cin >> this->password;
    }


    Application::Application()
    {
        this->getUserData();
        this->login = new Login(sql::SQLString(this->mailusername.c_str()), sql::SQLString(this->password.c_str()));
    } 
        
    Application::~Application()
    {
        delete this->login;
    }

    void Application::run()
    {
        while(true);
    }

} // namespace box3d
