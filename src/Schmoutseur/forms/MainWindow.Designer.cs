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
            this.barreOutil.SuspendLayout();
            this.SuspendLayout();
            // 
            // barreOutil
            // 
            this.barreOutil.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.barreOutil.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.buttonRessourceManager});
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
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1182, 628);
            this.Controls.Add(this.barreOutil);
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
    }
}

