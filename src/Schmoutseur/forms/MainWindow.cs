using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Schmou_tseur
{
    public partial class MainWindow : Form
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void buttonRessourceManager_Click(object sender, EventArgs e)
        {
            RessourceManager formRM = new RessourceManager();

            formRM.Show();
        }
    }
}
