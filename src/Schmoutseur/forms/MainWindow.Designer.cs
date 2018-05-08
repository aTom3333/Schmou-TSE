namespace Schmou_tseur
{
    partial class MainWindow
    {
        /// <summary>
        /// Variable nécessaire au concepteur.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Nettoyage des ressources utilisées.
        /// </summary>
        /// <param name="disposing">true si les ressources managées doivent être supprimées ; sinon, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Code généré par le Concepteur Windows Form

        /// <summary>
        /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
        /// le contenu de cette méthode avec l'éditeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainWindow));
            this.barreOutil = new System.Windows.Forms.ToolStrip();
            this.buttonRessourceManager = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripLabel1 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripTextBoxWD = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripButtonWD = new System.Windows.Forms.ToolStripButton();
            this.folderBrowserDialogWD = new System.Windows.Forms.FolderBrowserDialog();
            this.barreOutil.SuspendLayout();
            this.SuspendLayout();
            // 
            // barreOutil
            // 
            this.barreOutil.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.barreOutil.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.buttonRessourceManager,
            this.toolStripSeparator1,
            this.toolStripLabel1,
            this.toolStripTextBoxWD,
            this.toolStripButtonWD});
            this.barreOutil.Location = new System.Drawing.Point(0, 0);
            this.barreOutil.Name = "barreOutil";
            this.barreOutil.Size = new System.Drawing.Size(1182, 27);
            this.barreOutil.TabIndex = 0;
            this.barreOutil.Text = "toolStrip1";
            // 
            // buttonRessourceManager
            // 
            this.buttonRessourceManager.Image = ((System.Drawing.Image)(resources.GetObject("buttonRessourceManager.Image")));
            this.buttonRessourceManager.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.buttonRessourceManager.Name = "buttonRessourceManager";
            this.buttonRessourceManager.Size = new System.Drawing.Size(162, 24);
            this.buttonRessourceManager.Text = "Ressource Manager";
            this.buttonRessourceManager.Click += new System.EventHandler(this.buttonRessourceManager_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 27);
            // 
            // toolStripLabel1
            // 
            this.toolStripLabel1.Name = "toolStripLabel1";
            this.toolStripLabel1.Size = new System.Drawing.Size(152, 24);
            this.toolStripLabel1.Text = "Repertoire de travail :";
            // 
            // toolStripTextBoxWD
            // 
            this.toolStripTextBoxWD.Name = "toolStripTextBoxWD";
            this.toolStripTextBoxWD.Size = new System.Drawing.Size(300, 27);
            this.toolStripTextBoxWD.TextChanged += new System.EventHandler(this.toolStripTextBoxWD_TextChanged);
            // 
            // toolStripButtonWD
            // 
            this.toolStripButtonWD.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButtonWD.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButtonWD.Image")));
            this.toolStripButtonWD.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButtonWD.Name = "toolStripButtonWD";
            this.toolStripButtonWD.Size = new System.Drawing.Size(24, 24);
            this.toolStripButtonWD.Text = "Dossier de travail";
            this.toolStripButtonWD.Click += new System.EventHandler(this.toolStripButtonWD_Click);
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1182, 628);
            this.Controls.Add(this.barreOutil);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "MainWindow";
            this.Text = "Schmout\'seur";
            this.barreOutil.ResumeLayout(false);
            this.barreOutil.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ToolStrip barreOutil;
        private System.Windows.Forms.ToolStripButton buttonRessourceManager;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripLabel toolStripLabel1;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBoxWD;
        private System.Windows.Forms.ToolStripButton toolStripButtonWD;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialogWD;
    }
}

