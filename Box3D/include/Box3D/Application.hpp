#ifndef __APPLICATION_HPP_INCLUDED__
#define __APPLICATION_HPP_INCLUDED__

#include <iostream>
#include <sstream>

#include <Json/value.hpp>
#include <SystemAbstractions/File.hpp>
#include <SystemAbstractions/StringExtensions.hpp>

#include <LoginSystem/Login.hpp>
#include <MySQL/MySQL.hpp>

#include "Events/Event.hpp"

#include "Window.hpp"

#include <memory>

    namespace box3d {
        
        class Application {
            // Public methods
        public:
            Application();  
            virtual ~Application();

            /**
             * This function contain the main loop of our application
             */
            void run();
            
            // Private methods 
        private:
            void Application::getUserData();
            bool checkForLogin();
            // Private properties
        private:
            bool m_running;
            
            Login* login;

            std::string mailusername;
            std::string password;

            std::unique_ptr<Window> m_window;

        }; // class Application

        // To be defined in CLIENT
        Application* CreateApplication();

    } // namespace box3d

#endif // !__APPLICATION_HPP_INCLUDED__
