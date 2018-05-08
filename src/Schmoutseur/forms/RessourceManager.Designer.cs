namespace Schmou_tseur
{
    partial class RessourceManager
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(RessourceManager));
            this.barreOutil = new System.Windows.Forms.ToolStrip();
            this.buttonNew = new System.Windows.Forms.ToolStripButton();
            this.buttonOpen = new System.Windows.Forms.ToolStripButton();
            this.buttonSave = new System.Windows.Forms.ToolStripButton();
            this.buttonWorkinDir = new System.Windows.Forms.ToolStripButton();
            this.splitContainer = new System.Windows.Forms.SplitContainer();
            this.grpBxTreeView = new System.Windows.Forms.GroupBox();
            this.treeViewRessources = new System.Windows.Forms.TreeView();
            this.fileIcons = new System.Windows.Forms.ImageList(this.components);
            this.grpBxImage = new System.Windows.Forms.GroupBox();
            this.pictureBox = new System.Windows.Forms.PictureBox();
            this.contextMenuStripElement = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.toolStripMenuItemAdd = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItemRemove = new System.Windows.Forms.ToolStripMenuItem();
            this.barreOutil.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer)).BeginInit();
            this.splitContainer.Panel1.SuspendLayout();
            this.splitContainer.Panel2.SuspendLayout();
            this.splitContainer.SuspendLayout();
            this.grpBxTreeView.SuspendLayout();
            this.grpBxImage.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).BeginInit();
            this.contextMenuStripElement.SuspendLayout();
            this.SuspendLayout();
            // 
            // barreOutil
            // 
            this.barreOutil.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.barreOutil.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.buttonNew,
            this.buttonOpen,
            this.buttonSave,
            this.buttonWorkinDir});
            this.barreOutil.Location = new System.Drawing.Point(0, 0);
            this.barreOutil.Name = "barreOutil";
            this.barreOutil.Size = new System.Drawing.Size(782, 27);
            this.barreOutil.TabIndex = 0;
            this.barreOutil.Text = "toolStrip1";
            // 
            // buttonNew
            // 
            this.buttonNew.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.buttonNew.Image = ((System.Drawing.Image)(resources.GetObject("buttonNew.Image")));
            this.buttonNew.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.buttonNew.Name = "buttonNew";
            this.buttonNew.Size = new System.Drawing.Size(24, 24);
            this.buttonNew.Text = "New";
            // 
            // buttonOpen
            // 
            this.buttonOpen.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.buttonOpen.Image = ((System.Drawing.Image)(resources.GetObject("buttonOpen.Image")));
            this.buttonOpen.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.buttonOpen.Name = "buttonOpen";
            this.buttonOpen.Size = new System.Drawing.Size(24, 24);
            this.buttonOpen.Text = "Open";
            // 
            // buttonSave
            // 
            this.buttonSave.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.buttonSave.Image = ((System.Drawing.Image)(resources.GetObject("buttonSave.Image")));
            this.buttonSave.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.buttonSave.Name = "buttonSave";
            this.buttonSave.Size = new System.Drawing.Size(24, 24);
            this.buttonSave.Text = "Save";
            // 
            // buttonWorkinDir
            // 
            this.buttonWorkinDir.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.buttonWorkinDir.Image = ((System.Drawing.Image)(resources.GetObject("buttonWorkinDir.Image")));
            this.buttonWorkinDir.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.buttonWorkinDir.Name = "buttonWorkinDir";
            this.buttonWorkinDir.Size = new System.Drawing.Size(24, 24);
            this.buttonWorkinDir.Text = "Working Directory";
            // 
            // splitContainer
            // 
            this.splitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer.Location = new System.Drawing.Point(0, 27);
            this.splitContainer.Name = "splitContainer";
            // 
            // splitContainer.Panel1
            // 
            this.splitContainer.Panel1.Controls.Add(this.grpBxTreeView);
            // 
            // splitContainer.Panel2
            // 
            this.splitContainer.Panel2.Controls.Add(this.grpBxImage);
            this.splitContainer.Size = new System.Drawing.Size(782, 526);
            this.splitContainer.SplitterDistance = 230;
            this.splitContainer.TabIndex = 1;
            // 
            // grpBxTreeView
            // 
            this.grpBxTreeView.Controls.Add(this.treeViewRessources);
            this.grpBxTreeView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.grpBxTreeView.Location = new System.Drawing.Point(0, 0);
            this.grpBxTreeView.Name = "grpBxTreeView";
            this.grpBxTreeView.Size = new System.Drawing.Size(230, 526);
            this.grpBxTreeView.TabIndex = 0;
            this.grpBxTreeView.TabStop = false;
            this.grpBxTreeView.Text = "Liste des ressources";
            // 
            // treeViewRessources
            // 
            this.treeViewRessources.AllowDrop = true;
            this.treeViewRessources.Dock = System.Windows.Forms.DockStyle.Fill;
            this.treeViewRessources.ImageIndex = 0;
            this.treeViewRessources.ImageList = this.fileIcons;
            this.treeViewRessources.Location = new System.Drawing.Point(3, 18);
            this.treeViewRessources.Name = "treeViewRessources";
            this.treeViewRessources.SelectedImageIndex = 4;
            this.treeViewRessources.Size = new System.Drawing.Size(224, 505);
            this.treeViewRessources.TabIndex = 0;
            this.treeViewRessources.ItemDrag += new System.Windows.Forms.ItemDragEventHandler(this.treeViewRessources_ItemDrag);
            this.treeViewRessources.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.treeViewRessources_AfterSelect);
            this.treeViewRessources.DragDrop += new System.Windows.Forms.DragEventHandler(this.treeViewRessources_DragDrop);
            this.treeViewRessources.DragEnter += new System.Windows.Forms.DragEventHandler(this.treeViewRessources_DragEnter);
            // 
            // fileIcons
            // 
            this.fileIcons.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("fileIcons.ImageStream")));
            this.fileIcons.TransparentColor = System.Drawing.Color.Transparent;
            this.fileIcons.Images.SetKeyName(0, "blank.png");
            this.fileIcons.Images.SetKeyName(1, "file_image [#1687].png");
            this.fileIcons.Images.SetKeyName(2, "file_information [#1714].png");
            this.fileIcons.Images.SetKeyName(3, "file_music_player [#1606].png");
            this.fileIcons.Images.SetKeyName(4, "arrow_right [#336].png");
            // 
            // grpBxImage
            // 
            this.grpBxImage.Controls.Add(this.pictureBox);
            this.grpBxImage.Dock = System.Windows.Forms.DockStyle.Fill;
            this.grpBxImage.Location = new System.Drawing.Point(0, 0);
            this.grpBxImage.Name = "grpBxImage";
            this.grpBxImage.Size = new System.Drawing.Size(548, 526);
            this.grpBxImage.TabIndex = 0;
            this.grpBxImage.TabStop = false;
            this.grpBxImage.Text = "Image";
            // 
            // pictureBox
            // 
            this.pictureBox.BackColor = System.Drawing.SystemColors.MenuText;
            this.pictureBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pictureBox.Location = new System.Drawing.Point(3, 18);
            this.pictureBox.Name = "pictureBox";
            this.pictureBox.Size = new System.Drawing.Size(542, 505);
            this.pictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.pictureBox.TabIndex = 0;
            this.pictureBox.TabStop = false;
            // 
            // contextMenuStripElement
            // 
            this.contextMenuStripElement.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.contextMenuStripElement.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItemAdd,
            this.toolStripMenuItemRemove});
            this.contextMenuStripElement.Name = "contextMenuStripElement";
            this.contextMenuStripElement.Size = new System.Drawing.Size(230, 80);
            this.contextMenuStripElement.Opening += new System.ComponentModel.CancelEventHandler(this.contextMenuStripElement_Opening);
            // 
            // toolStripMenuItemAdd
            // 
            this.toolStripMenuItemAdd.Name = "toolStripMenuItemAdd";
            this.toolStripMenuItemAdd.Size = new System.Drawing.Size(229, 24);
            this.toolStripMenuItemAdd.Text = "Ajouter une ressource";
            this.toolStripMenuItemAdd.Click += new System.EventHandler(this.toolStripMenuItemAdd_Click);
            // 
            // toolStripMenuItemRemove
            // 
            this.toolStripMenuItemRemove.Name = "toolStripMenuItemRemove";
            this.toolStripMenuItemRemove.Size = new System.Drawing.Size(229, 24);
            this.toolStripMenuItemRemove.Text = "Supprimer la ressource";
            this.toolStripMenuItemRemove.Click += new System.EventHandler(this.toolStripMenuItemRemove_Click);
            // 
            // RessourceManager
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(782, 553);
            this.Controls.Add(this.splitContainer);
            this.Controls.Add(this.barreOutil);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "RessourceManager";
            this.Text = "Ressource Manager";
            this.barreOutil.ResumeLayout(false);
            this.barreOutil.PerformLayout();
            this.splitContainer.Panel1.ResumeLayout(false);
            this.splitContainer.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer)).EndInit();
            this.splitContainer.ResumeLayout(false);
            this.grpBxTreeView.ResumeLayout(false);
            this.grpBxImage.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
            this.contextMenuStripElement.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ToolStrip barreOutil;
        private System.Windows.Forms.SplitContainer splitContainer;
        private System.Windows.Forms.GroupBox grpBxTreeView;
        private System.Windows.Forms.TreeView treeViewRessources;
        private System.Windows.Forms.GroupBox grpBxImage;
        private System.Windows.Forms.ToolStripButton buttonOpen;
        private System.Windows.Forms.ToolStripButton buttonNew;
        private System.Windows.Forms.ToolStripButton buttonSave;
        private System.Windows.Forms.ToolStripButton buttonWorkinDir;
        private System.Windows.Forms.PictureBox pictureBox;
        private System.Windows.Forms.ImageList fileIcons;
        private System.Windows.Forms.ContextMenuStrip contextMenuStripElement;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItemAdd;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItemRemove;
    }
}