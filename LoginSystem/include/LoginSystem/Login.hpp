#ifndef __LOGINSYSTEM_HPP_INCLUDED__
#define __LOGINSYSTEM_HPP_INCLUDED__

#include <iostream>
#include <MySQL/MySQL.hpp>

namespace box3d {

    class Login
    {
    public:
        Login(const sql::SQLString& mailusername, const sql::SQLString& password);
        ~Login();
    private:
        /*
         * Create a new object of type MySQL
         */
        mysql::MySQL* connection;
    private: 
        /**
         * Database management
         */
        void createTable();
        void dropTable();
    };

}

#endif // !__LOGINSYSTEM_HPP_INCLUDED__