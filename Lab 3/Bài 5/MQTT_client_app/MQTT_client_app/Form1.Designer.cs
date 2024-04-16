namespace MQTT_client_app
{
    partial class MQTT_Client_Form
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
            this.Connect_button = new System.Windows.Forms.Button();
            this.dht_val_tb = new System.Windows.Forms.RichTextBox();
            this.dht_detected_tb = new System.Windows.Forms.RichTextBox();
            this.dht_value_lb = new System.Windows.Forms.Label();
            this.dht_detected_lb = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // Connect_button
            // 
            this.Connect_button.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Connect_button.Location = new System.Drawing.Point(725, 12);
            this.Connect_button.Name = "Connect_button";
            this.Connect_button.Size = new System.Drawing.Size(104, 51);
            this.Connect_button.TabIndex = 0;
            this.Connect_button.Text = "Connect";
            this.Connect_button.UseVisualStyleBackColor = true;
            this.Connect_button.Click += new System.EventHandler(this.Connect_Clk);
            // 
            // dht_val_tb
            // 
            this.dht_val_tb.Location = new System.Drawing.Point(12, 32);
            this.dht_val_tb.Name = "dht_val_tb";
            this.dht_val_tb.ReadOnly = true;
            this.dht_val_tb.Size = new System.Drawing.Size(333, 406);
            this.dht_val_tb.TabIndex = 1;
            this.dht_val_tb.Text = "";
            // 
            // dht_detected_tb
            // 
            this.dht_detected_tb.Location = new System.Drawing.Point(362, 32);
            this.dht_detected_tb.Name = "dht_detected_tb";
            this.dht_detected_tb.ReadOnly = true;
            this.dht_detected_tb.Size = new System.Drawing.Size(345, 406);
            this.dht_detected_tb.TabIndex = 2;
            this.dht_detected_tb.Text = "";
            // 
            // dht_value_lb
            // 
            this.dht_value_lb.AutoSize = true;
            this.dht_value_lb.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.dht_value_lb.Location = new System.Drawing.Point(9, 9);
            this.dht_value_lb.Name = "dht_value_lb";
            this.dht_value_lb.Size = new System.Drawing.Size(302, 20);
            this.dht_value_lb.TabIndex = 3;
            this.dht_value_lb.Text = "Messages from cl21/2/nhom2/dht/value";
            this.dht_value_lb.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // dht_detected_lb
            // 
            this.dht_detected_lb.AutoSize = true;
            this.dht_detected_lb.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.dht_detected_lb.Location = new System.Drawing.Point(358, 9);
            this.dht_detected_lb.Name = "dht_detected_lb";
            this.dht_detected_lb.Size = new System.Drawing.Size(307, 20);
            this.dht_detected_lb.TabIndex = 4;
            this.dht_detected_lb.Text = "Messages to cl21/2/nhom2/dht/detected";
            this.dht_detected_lb.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // MQTT_Client_Form
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(841, 450);
            this.Controls.Add(this.dht_detected_lb);
            this.Controls.Add(this.dht_value_lb);
            this.Controls.Add(this.dht_detected_tb);
            this.Controls.Add(this.dht_val_tb);
            this.Controls.Add(this.Connect_button);
            this.Name = "MQTT_Client_Form";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button Connect_button;
        private System.Windows.Forms.RichTextBox dht_val_tb;
        private System.Windows.Forms.RichTextBox dht_detected_tb;
        private System.Windows.Forms.Label dht_value_lb;
        private System.Windows.Forms.Label dht_detected_lb;
    }
}

