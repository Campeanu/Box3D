#include <MySQL/MySQL.hpp>

namespace mysql {
    
    void MySQL::CreateConnection(const sql::SQLString& db_host, const sql::SQLString& db_user, const sql::SQLString& db_pass, const sql::SQLString& db_name)
    {
        this->driver = get_driver_instance();
        this->con = driver->connect(db_host, db_user, db_pass);
        con->setSchema(db_name);
    }

    MySQL::MySQL(const sql::SQLString& db_host, const sql::SQLString& db_user, const sql::SQLString& db_pass, const sql::SQLString& db_name)
        : db_host{db_host}, db_user{db_user}, db_pass{db_pass}, db_name{db_name}
    {

        std::cout << std::endl;
        std::cout << "Let's have MySQL count from 10 to 1..." << std::endl;

        try {

            this->CreateConnection(this->db_host, this->db_user, this->db_pass, this->db_name);

            stmt = con->createStatement();
            stmt->execute("DROP TABLE IF EXISTS test");
            stmt->execute("CREATE TABLE test(id INT)");
            delete stmt;

            /* '?' is the supported placeholder syntax */
            pstmt = con->prepareStatement("INSERT INTO test(id) VALUES (?)");
            for (int i = 1; i <= 10; i++) {
                pstmt->setInt(1, i);
                pstmt->executeUpdate();
            }
            delete pstmt;

            /* Select in ascending order */
            pstmt = con->prepareStatement("SELECT id FROM test ORDER BY id ASC");
            res = pstmt->executeQuery();

            /* Fetch in reverse = descending order! */
            res->afterLast();
            while (res->previous())
                std::cout << "\t... MySQL counts: " << res->getInt("id") << std::endl;
            delete res;

            delete pstmt;
            delete con;
        
        } catch(sql::SQLException& e) {

            std::cout << "# ERR: SQLException in " << __FILE__;
            std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
            std::cout << "# ERR: " << e.what();
            std::cout << " (MySQL error code: " << e.getErrorCode();
            std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;

        }

        std::cout << std::endl;

    }

    MySQL::~MySQL()
    {

    }
}
