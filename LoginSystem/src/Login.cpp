#include "LoginSystem/Login.hpp"

namespace box3d {
    
    void Login::createTable()
    {
        this->connection->mysql_stmt_execute(
            "CREATE TABLE IF NOT EXISTS users (" 
                "id int(11)  AUTO_INCREMENT PRIMARY KEY NOT NULL,"
                "uidUsers   TINYTEXT NOT NULL,"
                "emailUsers TINYTEXT NOT NULL,"
                "pwdUsers   LONGTEXT NOT NULL"        
            ");"
        );
    }

    void Login::dropTable()
    {
        this->connection->mysql_stmt_execute("DROP TABLE IF EXISTS users");
    }

    Login::Login(const sql::SQLString& mailusername, const sql::SQLString& password)
    {
        this->connection = new mysql::MySQL("localhost", "root", "", "test");

        /*
            connection->mysql_prepare_statement("INSERT INTO users(uidUsers, emailUsers, pwdUsers) VALUES (?, ?, ?)");
            connection->mysql_stmt_bind_param(1, sql::SQLString("Alex"));
            connection->mysql_stmt_bind_param(2, sql::SQLString("alex.it@yahoo.com"));
            connection->mysql_stmt_bind_param(3, sql::SQLString("test1234"));
            connection->mysql_pstmt_execute();
        */

        std::string SQLparse;
        std::string userPassword = std::string(password.c_str());
        sql::SQLString parseSQLUserPassword;

        SQLparse = "SELECT * FROM users WHERE uidUsers='" + std::string(mailusername.c_str()) + "' OR emailUsers='" + std::string(mailusername.c_str()) + "'";;

        //connection->mysql_print_retrieve_data(SQLparse.c_str(), "pwdUsers");
        parseSQLUserPassword = connection->mysql_get_retrieve_data(SQLparse.c_str(), "pwdUsers");

        if (userPassword == std::string(parseSQLUserPassword.c_str()))
            std::cout << "\n[You are loged in !]";
        else
            std::cout << "\n[You have entered an invalid username or password !]";
    }
    
    Login::~Login()
    {
        delete this->connection;
    }

}
