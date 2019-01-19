using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Collections;
using System.IO;


namespace Arithmetic_GUI
{
    public partial class Form1 : Form
    {
        private string quenum = "1000";
        private string mode = "1";
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            string para = quenum + " " + mode;
            System.Diagnostics.Process.Start("Generator_wm.exe", para).WaitForExit();
            Form2 f2 = new Form2();
            this.Hide();
            f2.Show();   //调用做题窗口
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
           quenum = textBox1.Text;
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            mode = textBox2.Text;
        }
    }
}
