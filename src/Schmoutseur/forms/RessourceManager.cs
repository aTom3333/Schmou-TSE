using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace Schmou_tseur
{
    public partial class RessourceManager : Form
    {
        string path = Globals.workingDirectory + "\\Data\\chemins.ini";
        string[] lines;


        public RessourceManager()
        {
            InitializeComponent();


            if (File.Exists(path))
            {
                lines = System.IO.File.ReadAllLines(path);
                InitTree();
            }
                
            else
                MessageBox.Show(path + " : chemin invalide", "Erreur : chemin invalide", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        void InitTree()
        {
            treeViewRessources.BeginUpdate();
            CreateTree(treeViewRessources.Nodes, treeViewRessources.Nodes, 999, 0);
            treeViewRessources.EndUpdate();
        }
        
        int CountBeginWithChar(char c, string str)
        {
            int nb = 0;
            
            for(int i = 0; i < str.Length; i++)
            {
                if (str[i] != c)
                    return nb;
                nb++;
            }

            return nb;
        }

        static public int GetExtension(string str)
        {
            string[] split = str.Split('.');
            string extension = split[split.Count() - 1].ToLower();

            switch(extension)
            {
                case "jpg":
                    return 1;
                case "png":
                    return 1;
                case "gif":
                    return 1;
                case "ttf":
                    return 2;
                case "wav":
                    return 3;
                case "mp3":
                    return 3;
            }

            return 0;
        }

        void CreateTree(TreeNodeCollection root, TreeNodeCollection currentNode, int level, int n)
        {
            if(n < lines.Length)
            {
                int currentLevel = CountBeginWithChar('#', lines[n]);

                if (currentLevel == 0)
                {
                    if(lines[n] != "")
                    {
                        currentNode.Add("", lines[n].Split('=')[0], GetExtension(lines[n]));
                        currentNode[currentNode.Count - 1].Tag = lines[n].Split('=')[1].Replace(" ", string.Empty) ;
                        currentNode[currentNode.Count - 1].ContextMenuStrip = contextMenuStripElement;
                    }
                        

                    CreateTree(root, currentNode, currentLevel, n + 1);
                }
                else if(currentLevel <= level)
                {
                    currentNode.Add(lines[n]);
                    currentNode[currentNode.Count - 1].Tag = "none";
                    currentNode[currentNode.Count - 1].ContextMenuStrip = contextMenuStripElement;
                    CreateTree(root, currentNode[currentNode.Count-1].Nodes, currentLevel, n + 1);
                }
                else if(currentLevel > level)
                {
                    if(currentNode.Count != 0)
                    {
                        if (currentNode[0].Parent != null)
                        {
                            if (currentNode[0].Parent.Parent != null)
                                CreateTree(root, currentNode[0].Parent.Parent.Nodes, level + 1, n);
                            else
                                CreateTree(root, root, 999, n);
                        }
                    }
                }
                
            }
        }

        private void treeViewRessources_AfterSelect(object sender, TreeViewEventArgs e)
        {
            string location = (string)e.Node.Tag;
            
            if(location != "none")
            {
                try
                {
                    if(GetExtension(location) != 1)
                        MessageBox.Show(Path.RelativeToAbsolute(location) + " n'est pas une image", "Erreur : fichier non géré", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    else
                        pictureBox.Image = new Bitmap(Path.RelativeToAbsolute(location));
                }
                catch
                {
                    MessageBox.Show(Path.RelativeToAbsolute(location) + " : fichier introuvable", "Erreur : fichier introuvable", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                    
            }
            
        }

        private void treeViewRessources_ItemDrag(object sender, ItemDragEventArgs e)
        {
            DoDragDrop(e.Item, DragDropEffects.Move);
        }

        private void treeViewRessources_DragEnter(object sender, DragEventArgs e)
        {
            e.Effect = DragDropEffects.Move;
        }

        private void treeViewRessources_DragDrop(object sender, DragEventArgs e)
        {
            Point targetPoint = treeViewRessources.PointToClient(new Point(e.X, e.Y));
            TreeNode targetNode = treeViewRessources.GetNodeAt(targetPoint);
            TreeNode draggedNode = (TreeNode)e.Data.GetData(typeof(TreeNode));

            if (!draggedNode.Equals(targetNode) && targetNode != null)
            {
                draggedNode.Remove();
                targetNode.Nodes.Add(draggedNode);
                targetNode.Expand();
            }
        }

        private void contextMenuStripElement_Opening(object sender, CancelEventArgs e)
        {

        }

        private void toolStripMenuItemAdd_Click(object sender, EventArgs e)
        {
            RMForm_AddRessource diagAdd = new RMForm_AddRessource(treeViewRessources.SelectedNode, contextMenuStripElement);

            diagAdd.Show();
        }

        private void toolStripMenuItemRemove_Click(object sender, EventArgs e)
        {
            treeViewRessources.SelectedNode.Remove();
        }
    }
}
