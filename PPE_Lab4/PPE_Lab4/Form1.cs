using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PPE_Lab4
{
    public partial class Canvas : Form
    {
        List<Ball> balls = new List<Ball>();
        Graphics graphics;
        Point clickedPoint;
        int ballWidth, ballHeight;
        private List<Image> frames = new List<Image>();
        int frame = 0;

        public Canvas()
        {
            InitializeComponent();
            this.MouseWheel += new MouseEventHandler(Form1_MouseWheel);
            this.SetStyle(
                System.Windows.Forms.ControlStyles.UserPaint |
                System.Windows.Forms.ControlStyles.AllPaintingInWmPaint |
                System.Windows.Forms.ControlStyles.OptimizedDoubleBuffer,
                true);
            this.DoubleBuffered = true;
            nyanCatBox.Enabled = false;
            nyanCatBox.Hide();
        }
        private void Form1_MouseWheel(object sender, MouseEventArgs e)
        {
            if (timer1.Interval + (e.Delta/40) > 0)
                timer1.Interval += e.Delta / 40;
        }

        private void Form1_MouseClick(object sender, MouseEventArgs e)
        {
            clickedPoint = e.Location;
            paintBall();
        }

        private void paintBall()
        {
            Random random = new Random();
            ballWidth = ballHeight = random.Next(60, 120);
            balls.Add(new Ball(clickedPoint.X, clickedPoint.Y, ballWidth, ballHeight));
            
        }

        private void MoveBall()
        {
            foreach(Ball b in balls)
            { 
                b.X += b.dx;
                b.Y += b.dy;
                if (b.X < 0 || b.X > this.Width - b.Width)
                {
                    b.dx = -b.dx;
                    b.changeColor();
                }
                if (b.Y < 0 || b.Y  > this.Height - b.Height - 20)
                {
                    b.dy = -b.dy;
                    b.changeColor();
                }
            }

            for(int i = 0; i < balls.Count; i++)
            {
                if (nyanCatBox.Bounds.IntersectsWith(new Rectangle(balls[i].X, balls[i].Y, balls[i].Width, balls[i].Height)))
                    balls.Remove(balls[i]);
            }

            if(nyanCatBox.Enabled == true)
            {
                if (frame > 7)
                    frame = 0;
                nyanCatBox.Image = frames[frame];
                frame += 1;
                nyanCatBox.Location = new Point(nyanCatBox.Location.X + 2, nyanCatBox.Location.Y);
                if (nyanCatBox.Location.X > this.Width)
                    nyanCatBox.Location = new Point(0, nyanCatBox.Location.Y);
            }
            
            Invalidate();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            MoveBall();
        }

        private void Canvas_Paint(object sender, PaintEventArgs e)
        {
            graphics = e.Graphics;
            foreach (Ball b in balls)
            {
                SolidBrush BallBrush = new SolidBrush(b.color);
                graphics.FillEllipse(BallBrush, b.X, b.Y, b.Width, b.Height);
                BallBrush.Dispose();
            }
        }

        private void Canvas_KeyDown(object sender, KeyEventArgs e)
        {
            if(e.KeyCode == Keys.Space)
            {
                nyanCatBox.Show();
                nyanCatBox.Enabled = true;
                frames.Add(Properties.Resources.frame_0);
                frames.Add(Properties.Resources.frame_1);
                frames.Add(Properties.Resources.frame_2);
                frames.Add(Properties.Resources.frame_3);
                frames.Add(Properties.Resources.frame_4);
                frames.Add(Properties.Resources.frame_5);
                frames.Add(Properties.Resources.frame_6);
                frames.Add(Properties.Resources.frame_7);
            }

            if(e.KeyCode == Keys.Up)
            {
                if(nyanCatBox.Location.Y  > 0)          
                 nyanCatBox.Location = new Point(nyanCatBox.Location.X, nyanCatBox.Location.Y - 20);
                else
                    nyanCatBox.Location = new Point(nyanCatBox.Location.X, this.Height - 20);
            }

            if (e.KeyCode == Keys.Down)
            {
                if(nyanCatBox.Location.Y < this.Height)
                    nyanCatBox.Location = new Point(nyanCatBox.Location.X, nyanCatBox.Location.Y + 20);
                else
                    nyanCatBox.Location = new Point(nyanCatBox.Location.X, 20);
            }
        }
    }
}
