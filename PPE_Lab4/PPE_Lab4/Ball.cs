using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace PPE_Lab4
{
    class Ball
    {
        public int X { get; set; }
        public int Y { get; set; }
        public int Width { get; set; }
        public int Height { get; set; }
        public int dx;
        public int dy;
        public Color color;

        public Ball(int x, int y, int width, int height)
        {
            Random rand = new Random();
            X = x;
            Y = y;
            Width = width;
            Height = height;
            dx = rand.Next(1, 10);
            dy = rand.Next(-10, 0);
            color = Color.FromArgb(rand.Next(256), rand.Next(256), rand.Next(256));
        }

        public void changeColor()
        {
            Random rand = new Random();
            color = Color.FromArgb(rand.Next(256), rand.Next(256), rand.Next(256));
        }
    }
}
