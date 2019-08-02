#ifndef __MYSQL_HPP_INCLUDED__
#define __MYSQL_HPP_INCLUDED__

#include <stdlib.h>
#include <iostream>
#include <string>

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

        void mysql_stmt_execute(const sql::SQLString& sql);
        void mysql_prepare_statement(const sql::SQLString& sql);

        void mysql_stmt_bind_param(int placeholder, int value);
        void mysql_stmt_bind_param(int placeholder, const sql::SQLString& value);
        
        void mysql_pstmt_execute();

        void mysql_print_retrieve_data(const sql::SQLString& sql, const sql::SQLString& colname);
        sql::SQLString mysql_get_retrieve_data(const sql::SQLString& sql, const sql::SQLString& colname);
    
    private:

        sql::Driver     *driver;
        sql::Connection *conn;

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
