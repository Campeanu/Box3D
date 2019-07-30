#ifndef __APPLICATION_HPP_INCLUDED__
#define __APPLICATION_HPP_INCLUDED__

#include <iostream>
#include <MySQL/MySQL.hpp>

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
            // Private properties
        private:
            /*
             * Create a new object of type MySQL
             */
            mysql::MySQL* connection;

        }; // class Application

        // To be defined in CLIENT
        Application* CreateApplication();

    } // namespace box3d

#endif // !__APPLICATION_HPP_INCLUDED__
