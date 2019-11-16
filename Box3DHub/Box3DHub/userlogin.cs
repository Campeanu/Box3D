using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MySql.Data.MySqlClient;

namespace Box3DHub
{
    public partial class Userlogin : UserControl
    {
        public Userlogin()
        {
            InitializeComponent();
            User.InitializeDB();
        }

        private void Button2_Click(object sender, EventArgs e)
        {
            this.Hide();
        }

        public static String username;
        public static String password;

        public String usernamecurent;

        private void Button1_Click(object sender, EventArgs e)
        {
            /**
                DB db = new DB();
                String username = textBox1.Text;
                String password = textBox2.Text;

                DataTable table = new DataTable();
                MySqlDataAdapter adapter = new MySqlDataAdapter();

                MySqlCommand command = new MySqlCommand("SELECT * FROM `users` WHERE `uidUsers` = @username and `pwdUsers` = @password", db.getConnection());

                command.Parameters.Add("@username", MySqlDbType.VarChar).Value = username;
                command.Parameters.Add("@password", MySqlDbType.VarChar).Value = password;

                adapter.SelectCommand = command;

                adapter.Fill(table);

                if (table.Rows.Count > 0)
                {
                    this.Hide();
                }
                else
                {
                    MessageBox.Show("Acest BoxD ID nu există. Introduceți un alt cont sau obțineți unul nou.");
                }
            */

            username = textBox1.Text;
            password = textBox2.Text;

            if (User.Login(username, password).Rows.Count > 0)
            {
                this.Hide();
                usernamecurent = User.getUserUsername(username, password).ToString();
                useraccount account = new useraccount();
                account.Show();
                // MessageBox.Show("Hello " + (User.getUserUsername(username, password)).ToString() + ". You are loged in!");
            }
            else
            {
                MessageBox.Show("Acest BoxD ID nu există. Introduceți un alt cont sau obțineți unul nou.");
            }

        }
        public static String getUsername()
        {
            return username;
        }
        public static String getPassword()
        {
            return password;
        }

    }
}
