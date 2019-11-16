#include <MySQL/MySQL.hpp>

namespace mysql {

    void MySQL::CreateConnection(const sql::SQLString& db_host, const sql::SQLString& db_user, const sql::SQLString& db_pass, const sql::SQLString& db_name)
    {
        try {

            this->driver = get_driver_instance();
            this->conn = driver->connect(db_host, db_user, db_pass);
            this->conn->setSchema(db_name);

        } catch(sql::SQLException& e) {

            std::cout << "# ERR: SQLException in " << __FILE__;
            std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
            std::cout << "# ERR: " << e.what();
            std::cout << " (MySQL error code: " << e.getErrorCode();
            std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;

        }
    }

    MySQL::MySQL(const sql::SQLString& db_host, const sql::SQLString& db_user, const sql::SQLString& db_pass, const sql::SQLString& db_name)
        : db_host{db_host}, db_user{db_user}, db_pass{db_pass}, db_name{db_name}
    {

        this->CreateConnection(this->db_host, this->db_user, this->db_pass, this->db_name);
        this->stmt = conn->createStatement();
    }

    MySQL::~MySQL()
    {
        delete this->conn;
        delete this->stmt;
        delete this->pstmt;
        delete this->res;
    }

    void MySQL::mysql_stmt_execute(const sql::SQLString& sql)
    {
        this->stmt->execute(sql);
    }

    void MySQL::mysql_prepare_statement(const sql::SQLString& sql)
    {
        this->pstmt = this->conn->prepareStatement(sql);
    }

    void MySQL::mysql_stmt_bind_param(int placeholder, int value)
    {
        this->pstmt->setInt(placeholder, value);
    }

    void MySQL::mysql_stmt_bind_param(int placeholder, const sql::SQLString& value)
    {
        this->pstmt->setString(placeholder, value);
    }

    void MySQL::mysql_pstmt_execute()
    {
        this->pstmt->execute();
    }

    void MySQL::mysql_print_retrieve_data(const sql::SQLString& sql, const sql::SQLString& colname)
    {
        this->res = this->stmt->executeQuery(sql);
        while (res->next()) {
            std::cout << res->getString(colname).c_str() << std::endl;
        }
    }

    sql::SQLString MySQL::mysql_get_retrieve_data(const sql::SQLString& sql, const sql::SQLString& colname)
    {
        this->res = this->stmt->executeQuery(sql);
        sql::SQLString data;

        while (res->next()) {
            data = res->getString(colname).c_str();
            // std::cout << res->getString(colname).c_str() << std::endl;
        }

        return data;
    }

}
