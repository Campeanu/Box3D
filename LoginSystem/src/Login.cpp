#include "LoginSystem/Login.hpp"

namespace box3d {
    
    void Login::createTable()
    {
        this->connection->mysql_stmt_execute (
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

    void Login::initDBConfigurations()
    {
        const auto configurations = this->getDBConfigurations();
        
        if(configurations.Has("db_host")) {
            this->db_host = (std::string)configurations["db_host"];
        }

        if (configurations.Has("db_user")) {
            this->db_user = (std::string)configurations["db_user"];
        }

        if (configurations.Has("db_pass")) {
            this->db_pass = (std::string)configurations["db_pass"];
        }

        if (configurations.Has("db_name")) {
            this->db_name = (std::string)configurations["db_name"];
        }

    }

    Json::Value Login::getDBConfigurations()
    {
       Json::Value configuration(Json::Value::Type::Object);

        const auto configFile = std::shared_ptr<FILE>(
            fopen(
                (SystemAbstractions::File::GetExeParentDirectory() + "/Settings/db.json").c_str(), 
                "rb"
            ), 
            [](FILE* f) {
                if(f != NULL) {
                    (void)fclose(f);
                }
            }
        );
    
        if(configFile == NULL) {
            return configuration;
        } 

        if(fseek(configFile.get(), 0, SEEK_END)) {
            fprintf(stderr, "error: unable to open configuration file\n");
            return configuration;
        }

        const auto configSize = ftell(configFile.get());
        if(configSize == EOF) {
            fprintf(stderr, "error: unable to determen end of configuration file\n");
            return configuration;
        }

        if(fseek(configFile.get(), 0, SEEK_SET) != 0) {
            fprintf(stderr, "error: unable to seek to begining of configuration file\n");
            return configuration;    
        }

		const __int64 y = (__int64)configSize + 1;
        std::vector<char> encodedConfig(y);

		const auto readResult = fread(encodedConfig.data(), configSize, 1, configFile.get());
		
		if (readResult != 1) {
            fprintf(stderr, "error: unable read configuration file\n");
            return configuration;  
        }

        configuration = Json::Value::FromEncoding(encodedConfig.data());
        
        return configuration;
    }

    Login::Login(const sql::SQLString& mailusername, const sql::SQLString& password)
    {
        this->initDBConfigurations();
        this->connection = new mysql::MySQL ( 
            sql::SQLString(this->db_host.c_str()),
            sql::SQLString(this->db_user.c_str()),
            sql::SQLString(this->db_pass.c_str()),
            sql::SQLString(this->db_name.c_str())    
        );

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
