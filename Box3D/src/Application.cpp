#include "Box3D/Application.hpp"

namespace box3d {
    
    Application::Application()
    {
        connection = new mysql::MySQL("localhost", "root", "", "test");
    } 
        
    Application::~Application()
    {
        delete connection;
    }
    
    void Application::run()
    {
        while(true);
    }

} // namespace box3d
