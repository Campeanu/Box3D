#ifndef __MYSQL_HPP_INCLUDED__
#define __MYSQL_HPP_INCLUDED__

#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

namespace mysql {

    class MySQL {
    public:

        MySQL(const sql::SQLString& db_host, const sql::SQLString& db_user, const sql::SQLString& db_pass, const sql::SQLString& db_name);
        virtual ~MySQL();
        
    private:

        sql::Driver     *driver;
        sql::Connection *con;
        sql::Statement  *stmt;
        sql::ResultSet  *res;
        sql::PreparedStatement* pstmt;

        const sql::SQLString& db_host;
        const sql::SQLString& db_user;
        const sql::SQLString& db_pass;
        const sql::SQLString& db_name;
        // Private methods
    private:
        void CreateConnection(const sql::SQLString& db_host, const sql::SQLString& db_user, const sql::SQLString& db_pass, const sql::SQLString& db_name);
    };

}


#endif // !__MYSQL_HPP_INCLUDED__
