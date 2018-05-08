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
        string path = "../../../../rc/Data/chemins.ini";
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

        void CreateTree(TreeNodeCollection root, TreeNodeCollection currentNode, int level, int n)
        {
            if(n < lines.Length)
            {
                int currentLevel = CountBeginWithChar('#', lines[n]);

                if (currentLevel == 0)
                {
                    if(lines[n] != "")
                    {
                        currentNode.Add(lines[n].Split('=')[0]);
                        currentNode[currentNode.Count - 1].Tag = lines[n].Split('=')[1].Replace(" ", string.Empty) ;
                    }
                        

                    CreateTree(root, currentNode, currentLevel, n + 1);
                }
                else if(currentLevel <= level)
                {
                    currentNode.Add(lines[n]);
                    currentNode[currentNode.Count - 1].Tag = "none";
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
                    pictureBox.Image = new Bitmap("../../../../rc/" + location);
                }
                catch
                {
                    MessageBox.Show("../../../../rc/" + location + " : fichier introuvable", "Erreur : fichier introuvable", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                    
            }
            
        }
    }
}
