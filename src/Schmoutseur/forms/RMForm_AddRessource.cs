using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Schmou_tseur
{
    public partial class RMForm_AddRessource : Form
    {
        TreeNode node;
        ContextMenuStrip contextMenu;
        public RMForm_AddRessource(TreeNode n, ContextMenuStrip cm)
        {
            node = n;
            contextMenu = cm;
            InitializeComponent();
            openFileDialogRessource.InitialDirectory = Globals.workingDirectory;
        }

        private void buttonOpen_Click(object sender, EventArgs e)
        {
            string path;
            if(openFileDialogRessource.ShowDialog() == DialogResult.OK)
            {
                path = openFileDialogRessource.FileName;
                textBoxPath.Text = path;
            }
        }

        private void buttonPreview_Click(object sender, EventArgs e)
        {
            try
            {
                pictureBoxPreview.Image = new Bitmap(textBoxPath.Text);
            }
            catch { }
        }

        private void buttonClose_Click(object sender, EventArgs e)
        {
            Dispose();
        }

        private void buttonOk_Click(object sender, EventArgs e)
        {
            node.Nodes.Add("", textBoxName.Text, RessourceManager.GetExtension(textBoxPath.Text));
            node.Nodes[node.Nodes.Count - 1].Tag = Path.AbsoluteToRelative(textBoxPath.Text);
            node.Nodes[node.Nodes.Count - 1].ContextMenuStrip = contextMenu;

            Dispose();
        }
    }
}
