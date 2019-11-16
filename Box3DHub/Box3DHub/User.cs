using System;
using System.Collections.Generic;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading.Tasks;

using MySql.Data.MySqlClient;

namespace Box3DHub
{
    public class User
    {
        private const String SERVER   = "localhost";
        private const String DATABASE = "box3d";
        private const String UID      = "root";
        private const String PASSWORD = "";

        private static MySqlConnection dbConn;

        public int Id { get; private set; }

        public String Username { get; private set; }

        public String Email    { get; private set; }

        public String Password { get; private set; }
        public int UserStatus { get; private set; }
        public int HasKey { get; private set; }
        public String UserKey { get; private set; }

        private User(int id, String u, String e, String p, int status, int haskey, String userkey)
        {
            Id       = id;
            Username = u;
            Email    = e;
            Password = p;
            UserStatus  = status;
            HasKey      = haskey;
            UserKey     = userkey;

        }

        public static void InitializeDB()
        {
            MySqlConnectionStringBuilder builder = new MySqlConnectionStringBuilder();
            builder.Server   = SERVER;
            builder.UserID   = UID;
            builder.Password = PASSWORD;
            builder.Database = DATABASE;

            String connString = builder.ToString();

            builder = null;

            Console.WriteLine(connString);

            dbConn = new MySqlConnection(connString);

            Application.ApplicationExit += (sender, args) =>
            {
                if (dbConn != null)
                {
                    dbConn.Dispose();
                    dbConn = null;
                }
            };
        }

        public static List<User> GetUsers()
        {
            List<User> users = new List<User>();

            String query = "SELECT * FROM users";

            MySqlCommand cmd = new MySqlCommand(query, dbConn);

            dbConn.Open();

            MySqlDataReader reader = cmd.ExecuteReader();

            while (reader.Read())
            {
                int    id       = (int)reader["idUsers"];
                String username = reader["uidUsers"].ToString();
                String email    = reader["emailUsers"].ToString();
                String password = reader["pwdUsers"].ToString();
                int status = (int)reader["userStatus"];
                int haskey = (int)reader["haskey"];
                String userkey = reader["userKey"].ToString();

                User u = new User(id, username, email, password, status, haskey, userkey);

                users.Add(u);
            }

            reader.Close();

            dbConn.Close();

            return users;
        }

        public static int getUserId(String username, String password)
        {
            String query = string.Format("SELECT * FROM users WHERE uidUsers='{0}' and pwdUsers='{1}'", username, password);
            MySqlCommand cmd = new MySqlCommand(query, dbConn);

            dbConn.Open();

            MySqlDataReader toreader = cmd.ExecuteReader();

            int getid;
            toreader.Read();
            getid = (int)toreader["idUsers"];

            // String getusername = reader["uidUsers"].ToString();
            // String getemail    = reader["emailUsers"].ToString();
            // String getpassword = reader["pwdUsers"].ToString();

            toreader.Close();

            dbConn.Close();

            return getid;
        }

        public static String getUserUsername(String username, String password)
        {
            String query = string.Format("SELECT * FROM users WHERE uidUsers='{0}' and pwdUsers='{1}'", username, password);
            MySqlCommand cmd = new MySqlCommand(query, dbConn);

            dbConn.Open();

            MySqlDataReader toreader = cmd.ExecuteReader();

            String getusername;
            toreader.Read();
            getusername = (String)toreader["uidUsers"];

            // String getusername = reader["uidUsers"].ToString();
            // String getemail    = reader["emailUsers"].ToString();
            // String getpassword = reader["pwdUsers"].ToString();

            toreader.Close();

            dbConn.Close();

            return getusername;
        }

        public static String getKey(String username, String password)
        {
            String query = string.Format("SELECT * FROM users WHERE uidUsers='{0}' and pwdUsers='{1}'", username, password);
            MySqlCommand cmd = new MySqlCommand(query, dbConn);

            dbConn.Open();

            MySqlDataReader toreader = cmd.ExecuteReader();

            String getKey;
            toreader.Read();
            getKey = (String)toreader["userkey"];

            // String getusername = reader["uidUsers"].ToString();
            // String getemail    = reader["emailUsers"].ToString();
            // String getpassword = reader["pwdUsers"].ToString();

            toreader.Close();

            dbConn.Close();

            return getKey;
        }

        public static DataTable Login(String username, String password)
        {
            DataTable table = new DataTable();
            MySqlDataAdapter adapter = new MySqlDataAdapter();

            MySqlCommand command = new MySqlCommand("SELECT * FROM `users` WHERE `uidUsers` = @username and `pwdUsers` = @password", dbConn);

            command.Parameters.Add("@username", MySqlDbType.VarChar).Value = username;
            command.Parameters.Add("@password", MySqlDbType.VarChar).Value = password;

            adapter.SelectCommand = command;

            adapter.Fill(table);

            return table;
        }

        public static User Insert(String u, String e, String p, int status, int haskey, String userkey)
        {
            String query = string.Format("INSERT INTO users(uidUsers, emailUsers, pwdUsers, userStatus, haskey, userkey) VALUES ('{0}', '{1}', '{2}', '{3}', '{4}', '{5}')", u, e, p, status, haskey, userkey);

            MySqlCommand cmd = new MySqlCommand(query, dbConn);

            dbConn.Open();

            cmd.ExecuteNonQuery();
            int id = (int)cmd.LastInsertedId;

            User user = new User(id, u, e, p, status, haskey, userkey);

            dbConn.Close();

            return user;

        }

        public void Update(string u, string e, string p, int status, int haskey, String userkey)
        {
            String query = string.Format("UPDATE users SET uidUsers='{0}', emailUsers='{1}', pwdUsers='{2}', userStatus='{3}', haskey='{4}', userkey='{5}' WHERE idUsers={6}", u, e, p, status, haskey, userkey, Id);

            MySqlCommand cmd = new MySqlCommand(query, dbConn);

            dbConn.Open();

            cmd.ExecuteNonQuery();

            dbConn.Close();
        }

        public void Delete()
        {
            String query = string.Format("DELETE FROM users WHERE idUsers={0}", Id);

            MySqlCommand cmd = new MySqlCommand(query, dbConn);

            dbConn.Open();

            cmd.ExecuteNonQuery();

            dbConn.Close();
        }
    }

}
