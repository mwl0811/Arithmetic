using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Arithmetic_GUI
{
    public partial class Form2 : Form
    {
        private int count = 0;
        TimeSpan ts = new TimeSpan(0, 0, 20);
        public Form2()
        {
            InitializeComponent();
            timer1.Interval = 1000;
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            FillGrid();
        }

        void FillGrid()
        {
            ts = new TimeSpan(0, 0, 20);
            this.timer1.Enabled = true;
            StreamReader str1 = new StreamReader(@"question.txt");
            string quebefore;
            for (int i = 0; i < count; i++) 
            {
                quebefore = str1.ReadLine();
            }
            string que = str1.ReadLine();
            if(que==null)
            {
                this.timer1.Enabled = false;
                System.Diagnostics.Process.Start("Count_num.exe");
                MessageBox.Show("no question left! Please quit!", "警告", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            label5.Text = que;
            if (que != null)
            {
                count++;
            }
            label6.Text = count.ToString();
            textBox3.Text = "Input your answer here";
            label7.Text = ts.Seconds.ToString();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string que = label5.Text;
            string ans = textBox3.Text;
            string para = que + " " + ans;
            System.Diagnostics.Process.Start("Solve.exe", para).WaitForExit();
            FillGrid();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            System.Environment.Exit(0);
        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            Form3 f3 = new Form3();
            f3.Show();   //调用做题窗口
        }

        private void label7_Click(object sender, EventArgs e)
        {

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            label7.Text = ts.Seconds.ToString();
            ts = ts.Subtract(new TimeSpan(0, 0, 1));   //隔一秒
            if(ts.TotalSeconds<0.0)
            {
                timer1.Enabled = false;
                string que = label5.Text;
                string ans = textBox3.Text;
                string para = que + " " + ans;
                System.Diagnostics.Process.Start("Solve.exe", para).WaitForExit();
                MessageBox.Show("You have used out of the time!", "超时警告", MessageBoxButtons.OK, MessageBoxIcon.Error);
                FillGrid();
            }
        }
    }
}
