db_name: 
    box3dloginsystem

users_table:
    CREATE TABLE users ( 
        idUsers    int(11)  AUTO_INCREMENT PRIMARY KEY NOT NULL,
        uidUsers   TINYTEXT NOT NULL,
        emailUsers TINYTEXT NOT NULL,
        pwdUsers   LONGTEXT NOT NULL
    );


/**
    connection->mysql_stmt_execute(
        "CREATE TABLE IF NOT EXISTS users (" 
            "idUsers    int(11)  AUTO_INCREMENT PRIMARY KEY NOT NULL,"
            "uidUsers   TINYTEXT NOT NULL,"
            "emailUsers TINYTEXT NOT NULL,"
            "pwdUsers   LONGTEXT NOT NULL"        
        ");"
    );

    connection->mysql_stmt_execute("DROP TABLE IF EXISTS users");
    connection->mysql_stmt_execute("DROP TABLE IF EXISTS test");
    */
        
/*
connection->mysql_stmt_execute("DROP TABLE IF EXISTS test");
connection->mysql_stmt_execute("CREATE TABLE test(id INT, label INT, test LONGTEXT)");

connection->mysql_prepare_statement("INSERT INTO test(id, label, test) VALUES (?, ?, ?)");
connection->mysql_stmt_bind_param(1, 1);
connection->mysql_stmt_bind_param(2, 121);
connection->mysql_stmt_bind_param(3, sql::SQLString("Vasile are multe mere cumparate de la magazinul dein spatele blocului!"));
connection->mysql_pstmt_execute();
*/

/**
    connection->mysql_stmt_execute("DROP TABLE IF EXISTS test");
    connection->mysql_stmt_execute("CREATE TABLE test(id INT, label INT, test LONGTEXT)");

    connection->mysql_prepare_statement("INSERT INTO test(id, label, test) VALUES (?, ?, ?)");
    connection->mysql_stmt_bind_param(1, 1);
    connection->mysql_stmt_bind_param(2, 121);
    connection->mysql_stmt_bind_param(3, sql::SQLString("Vasile are multe mere cumparate de la magazinul dein spatele blocului!"));
    connection->mysql_pstmt_execute();

    connection->mysql_prepare_statement("INSERT INTO test(id, label, test) VALUES (?, ?, ?)");
    connection->mysql_stmt_bind_param(1, 10);
    connection->mysql_stmt_bind_param(2, 12112);
    connection->mysql_stmt_bind_param(3, sql::SQLString("Test"));
    connection->mysql_pstmt_execute();   
    connection->mysql_print_retrieve_data ("SELECT * FROM test WHERE label=121", "test");
*/