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
    public partial class InstallControl : UserControl
    {
        public InstallControl()
        {
            InitializeComponent();
        }

        private void Button2_Click(object sender, EventArgs e)
        {
            Process.Start(@"C:\Box3D\box3d_hub\box3d\box3d_installer.exe");
                            C:\Box3D\box3d_hub\box3d\box3d_installer.exe
        }

        private void Button3_Click(object sender, EventArgs e)
        {
            Process.Start(@"C:\Box3D\box3d_hub\box3d\box3d_installer.exe");
        }

        public static String key;

        private void Button4_Click(object sender, EventArgs e)
        {

            // if(textBox1.Text == "ThisKeyShouldBeRandom.")
            // {
            //    Process.Start(@"C:\Box3D\box3d_hub\box3d\box3d_installer.exe");
            // }
            // else
            // {
            //       MessageBox.Show("You entred the wrong key. Please try again.");
            // }

            if (textBox1.Text == "")
            {

                MessageBox.Show("You need to complete this field!");

            } else {

                if (User.Login(Userlogin.getUsername(), Userlogin.getPassword()).Rows.Count > 0)
                {
                    if (textBox1.Text == "")
                    {

                        MessageBox.Show("You need to complete this field!");

                    }
                    else
                    {
                        if (textBox1.Text == User.getKey(Userlogin.getUsername(), Userlogin.getPassword()))
                        {
                            Process.Start(@"C:\Box3D\box3d_hub\box3d\box3d_installer.exe");
                        }
                        else
                        {
                            MessageBox.Show("You don't have a licence key.\nPlease buy one or install the community edition!");
                        }
                    }
                }
                else
                {
                    MessageBox.Show("You need to be loged in!");
                }

            }

        }
    }
}
