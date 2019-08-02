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
        
        connection->mysql_prepare_statement("INSERT INTO users(uidUsers, emailUsers, pwdUsers) VALUES (?, ?, ?)");
        connection->mysql_stmt_bind_param(1, sql::SQLString("Vasile"));
        connection->mysql_stmt_bind_param(2, sql::SQLString("campeanu.it@yahoo.com"));
        connection->mysql_stmt_bind_param(3, sql::SQLString("adasdad"));
        connection->mysql_pstmt_execute();
        
        std::string test;

        test = mailusername.c_str();

        //connection->mysql_print_retrieve_data ("SELECT * FROM users WHERE uidUsers='" + mailusername + "'", "emailUsers");
    }
    
    Login::~Login()
    {
        delete this->connection;
    }

}