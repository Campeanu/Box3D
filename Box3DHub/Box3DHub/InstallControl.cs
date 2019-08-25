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
        }
    }
}
