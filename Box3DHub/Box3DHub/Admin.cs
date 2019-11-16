using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
namespace Box3DHub
{
    public partial class Admin : UserControl
    {
        private User currUser;

        public Admin()
        {
            InitializeComponent();
            User.InitializeDB();
        }

        private void LoadAll()
        {
            List<User> users = User.GetUsers();

            listViewUsers.Items.Clear();

            foreach (User u in users)
            {

                ListViewItem item = new ListViewItem(new String[] { u.Id.ToString(), u.Username, u.Email, u.Password, u.UserStatus.ToString(), u.HasKey.ToString(), u.UserKey});
                item.Tag = u;

                listViewUsers.Items.Add(item);

            }
        }

        private void Loadall_Click(object sender, EventArgs e)
        {
            LoadAll();
        }

        private void ListViewUsers_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listViewUsers.SelectedItems.Count > 0)
            {
                ListViewItem item = listViewUsers.SelectedItems[0];
                currUser = (User)item.Tag;

                int id = currUser.Id;

                String u  = currUser.Username;
                String p  = currUser.Password;
                String em = currUser.Email;
                String status = currUser.UserStatus.ToString();
                String haskey = currUser.HasKey.ToString();
                String userkey = currUser.UserKey.ToString();

                admin_textBoxID.Text = id.ToString();
                admin_textBoxUsername.Text = u;
                admin_textBoxEmail.Text = em;
                admin_textBoxPassword.Text = p;
                admin_textBoxStatus.Text = status;
                admin_textBoxHasKey.Text = haskey;
                admin_textBoxUserKey.Text = userkey;
            }
        }

        private void Insert_Click(object sender, EventArgs e)
        {
            String u = admin_textBoxUsername.Text;
            String email = admin_textBoxEmail.Text;
            String p = admin_textBoxPassword.Text;
            int status = int.Parse(admin_textBoxStatus.Text);
            int haskey = int.Parse(admin_textBoxHasKey.Text);
            String userkey = admin_textBoxUserKey.Text; 

            if (String.IsNullOrEmpty(u) || String.IsNullOrEmpty(p))
            {
                MessageBox.Show("It's empty");
                return;
            }

            currUser = User.Insert(u, email, p, status, haskey, userkey);

            LoadAll();

        }

        private void Update_Click(object sender, EventArgs e)
        {
            String u = admin_textBoxUsername.Text;
            String email = admin_textBoxEmail.Text;
            String p = admin_textBoxPassword.Text;
            int status = int.Parse(admin_textBoxStatus.Text);
            int haskey = int.Parse(admin_textBoxHasKey.Text);
            String userkey = admin_textBoxUserKey.Text;

            if (String.IsNullOrEmpty(u) || String.IsNullOrEmpty(p))
            {
                MessageBox.Show("It's empty");
                return;
            }

            currUser.Update(u, email, p, status, haskey, userkey);

            LoadAll();
        }

        private void Delete_Click(object sender, EventArgs e)
        {
            if (currUser == null)
            {
                MessageBox.Show("No user selected!");
                return;
            }

            currUser.Delete();

            LoadAll();
        }
    }
}
