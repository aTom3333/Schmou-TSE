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
            toolStripTextBoxWD.Text = Globals.workingDirectory;
            folderBrowserDialogWD.SelectedPath = Globals.workingDirectory;
        }

        private void buttonRessourceManager_Click(object sender, EventArgs e)
        {
            RessourceManager formRM = new RessourceManager();

            formRM.Show();
        }

        private void toolStripLabel1_Click(object sender, EventArgs e)
        {

        }

        private void toolStripTextBoxWD_TextChanged(object sender, EventArgs e)
        {
            Globals.workingDirectory = ((ToolStripTextBox)sender).Text;
        }

        private void toolStripButtonWD_Click(object sender, EventArgs e)
        {
            string path;
            if (folderBrowserDialogWD.ShowDialog() == DialogResult.OK)
            {
                path = folderBrowserDialogWD.SelectedPath;
                toolStripTextBoxWD.Text = path;
            }
        }
    }
}
