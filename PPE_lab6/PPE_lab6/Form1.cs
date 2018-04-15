using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Media;
using System.IO;

namespace PPE_lab6
{
    public partial class Form1 : Form
    {
        bool changeImage = false;
        List<Person> persons = new List<Person>();
        SoundPlayer music = new SoundPlayer(@"bckgMusic.wav");

        public Form1()
        {
            InitializeComponent();
            bckgBtn.FlatStyle = FlatStyle.Flat;
            bckgBtn.FlatAppearance.BorderSize = 2;
            bckgBtn.FlatAppearance.BorderColor = Color.DarkBlue;

        }

        private void bckgBtn_Click(object sender, EventArgs e)
        {
            changeImage = !changeImage;
            if(changeImage)
                this.BackgroundImage = Properties.Resources.blue_circles;
            else
                this.BackgroundImage = Properties.Resources.circles;
        }

        private void addButton_Click(object sender, EventArgs e)
        {
            Information.Items.Add(nameTxt.Text + " - " + surnameTxt.Text);
            persons.Add(new Person(nameTxt.Text, surnameTxt.Text, hobbyTxt.Text, professionTxt.Text));
            nameTxt.ResetText();
            surnameTxt.ResetText();
            hobbyTxt.ResetText();
            professionTxt.ResetText();
        }

        private void deleteBtn_Click(object sender, EventArgs e)
        {
            Information.Items.Remove(Information.SelectedItem);
        }

        private void clearBtn_Click(object sender, EventArgs e)
        {
            Information.Items.Clear();
            persons.Clear();
            allInfo.Text = "";
        }

        private void Information_SelectedIndexChanged(object sender, EventArgs e)
        {
            string info = "";
            if (Information.SelectedItem == null)
                info = "";
            else
            {
                info = Information.SelectedItem.ToString();
                info = info.Replace(" - ", String.Empty);

                foreach (Person p in persons)
                {
                    if (info == p.Name + p.Surname)
                    {
                        if (p.Name == null) p.Name = "";
                        if (p.Surname == null) p.Surname = "";
                        if (p.Hobby == null) p.Hobby = "";
                        if (p.Profession == null) p.Profession = "";

                        allInfo.Text = "Name: " + p.Name + "\n" +
                                       "Surname: " + p.Surname + "\n" +
                                       "Hobby: " + p.Hobby + "\n" +
                                       "Profession: " + p.Profession;
                    }
                }
            }
        }

        private void Information_KeyDown(object sender, KeyEventArgs e)
        {
            if(e.KeyCode == Keys.Delete)
                Information.Items.Remove(Information.SelectedItem);
        }

        private void soundToolStripMenuItem_Click(object sender, EventArgs e)
        {
            music.Play();
        }

        private void viewHelpToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("You have to fill all fields and add the information to the list, so we will be abe to save it))");
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog save = new SaveFileDialog();
            save.DefaultExt = ".txt";

            string info = "";

            if (save.ShowDialog() == DialogResult.OK)
            {
                using (StreamWriter write = new StreamWriter(File.Create(save.FileName)))
                {
                    for (int i = 0; i < persons.Count; i++)
                    {
                        info = persons[i].Name + " - " + persons[i].Surname + " - " +
                                persons[i].Hobby + " - " + persons[i].Profession ;

                        write.WriteLine(info);

                    }
                }
            }
        }

    }
}
