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
    public partial class RessourceManager : Form
    {
        string path = "../../rc/Data/";
        string[] lines;


        public RessourceManager()
        {
            InitializeComponent();
        }

        void InitTree()
        {
            lines = System.IO.File.ReadAllLines(path);
        }
    }
}
