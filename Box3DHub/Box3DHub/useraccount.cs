using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Box3DHub
{
    public partial class useraccount : Form
    {
        private int id;
        private String user;
        public useraccount()
        {
            InitializeComponent();
            user = User.getUserUsername(Userlogin.getUsername(), Userlogin.getPassword()).ToString();
            id = User.getUserId(Userlogin.getUsername(), Userlogin.getPassword());
            label1.Text = "ID: " + id.ToString() + " Name: " + user.ToString();

        }

        private void Button1_Click(object sender, EventArgs e)
        {
            this.Hide();
        }

        private void Label1_Click(object sender, EventArgs e)
        {
        }
    }
}
