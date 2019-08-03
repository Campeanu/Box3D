#ifndef __LOGINSYSTEM_HPP_INCLUDED__
#define __LOGINSYSTEM_HPP_INCLUDED__

#include <iostream>
#include <MySQL/MySQL.hpp>

#include <Json/value.hpp>
#include <SystemAbstractions/File.hpp>
#include <SystemAbstractions/StringExtensions.hpp>

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
        std::string db_host;
        std::string db_user;
        std::string db_pass;
        std::string db_name;

        /**
         * Configurations
         */
        Json::Value getDBConfigurations();
        void initDBConfigurations();

        void createTable();
        void dropTable();
    };

}

#endif // !__LOGINSYSTEM_HPP_INCLUDED__