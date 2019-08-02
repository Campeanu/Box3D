db_name: 
    box3dloginsystem

users_table:
    CREATE TABLE users ( 
        idUsers    int(11)  AUTO_INCREMENT PRIMARY KEY NOT NULL,
        uidUsers   TINYTEXT NOT NULL,
        emailUsers TINYTEXT NOT NULL,
        pwdUsers   LONGTEXT NOT NULL
    );