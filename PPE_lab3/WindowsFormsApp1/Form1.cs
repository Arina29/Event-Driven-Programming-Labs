using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        private enum Shape
        {
            Line, Rectangle, Ellipse, Bezier, Eraser
        }

        private enum fillMode
        {
            Filled, Unfilled, Gradient
        }

        private Shape currentShape = Shape.Line;
        private fillMode currentFillMode = fillMode.Unfilled;
        Graphics graph;
        Bitmap bm;
        int x = -1;
        int y = -1;
        int eraserWidth = 5;
        bool moving = false, bezier = false, fillColor = false, delete = false;
        Pen pen;
        Point startPos, currentPos, leftPoint, rightPoint;
        Brush brush;
        List<Point> points = new List<Point>();


        public Form1()
        {
            InitializeComponent();
            InitializeLineWidthComboBox();
            InitializeFigureComboBox();
            graph = panel1.CreateGraphics();
            graph.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            pen = new Pen(Color.Black, 5);
            pen.StartCap = pen.EndCap = System.Drawing.Drawing2D.LineCap.Round;
        }

        private void InitializeLineWidthComboBox()
        {
            txtLineWidth.Items.Add(2);
            txtLineWidth.Items.Add(4);
            txtLineWidth.Items.Add(8);
            txtLineWidth.Items.Add(16);
            txtLineWidth.Items.Add(32);
            txtLineWidth.Items.Add(64);
        }

        private void InitializeFigureComboBox()
        {
            FigureBox.Items.Add("Rectangle");
            FigureBox.Items.Add("Ellipse");
            FigureBox.Items.Add("Line");
            FigureBox.Items.Add("Bezier");
            FigureBox.Items.Add("Eraser");

            FillColorBox.Items.Add("Unfilled");
            FillColorBox.Items.Add("Filled");
            FillColorBox.Items.Add("Gradient");
        }


        private void btnColor_Click(object sender, EventArgs e)
        {
            ColorDialog clrDlg = new ColorDialog();
            if(clrDlg.ShowDialog() == DialogResult.OK)
            {
                pen.Color = clrDlg.Color;
                btnColor.BackColor = pen.Color;
            }
        }

        private Rectangle getRectangle()
        {
            return new Rectangle(Math.Min(startPos.X, currentPos.X),
                                 Math.Min(startPos.Y, currentPos.Y),
                                 Math.Abs(startPos.X - currentPos.X),
                                 Math.Abs(startPos.Y - currentPos.Y));
        }

        private void panel1_MouseMove(object sender, MouseEventArgs e)
        {
            if (moving && x != -1 && y != -1)
            {
                if(currentShape == Shape.Line)
                    graph.DrawLine(pen, new Point(x, y), e.Location);
                if(currentShape == Shape.Eraser)
                { 
                    pen.Color = Color.White;
                    graph.DrawLine(pen, new Point(x, y), e.Location);
                    btnColor.BackColor = pen.Color;
                }
                x = e.X;
                y = e.Y;
            }
            currentPos = e.Location;
        }

        private void panel1_MouseUp(object sender, MouseEventArgs e)
        {
            moving = false;
            x = -1;
            y = -1;
            panel1.Cursor = Cursors.Default;
            if (currentFillMode == fillMode.Filled)
                brush = new SolidBrush(pen.Color);
            else if (currentFillMode == fillMode.Gradient)
                brush = new LinearGradientBrush(new Point(startPos.X, startPos.Y), new Point(currentPos.X+1, currentPos.Y+1), pen.Color, Color.Aquamarine);

            switch (currentShape)
            {
                case Shape.Rectangle:
                    if (currentFillMode == fillMode.Unfilled)
                        graph.DrawRectangle(pen, getRectangle());
                    else if (currentFillMode == fillMode.Filled || currentFillMode == fillMode.Gradient)
                        graph.FillRectangle(brush, getRectangle());
                    break;

                case Shape.Ellipse:
                    if (currentFillMode == fillMode.Unfilled)
                        graph.DrawEllipse(pen, getRectangle());
                    else if (currentFillMode == fillMode.Filled || currentFillMode == fillMode.Gradient)
                        graph.FillEllipse(brush, getRectangle());
                    break;

                case Shape.Bezier:
                    graph.DrawBeziers(pen, points.ToArray());
                    break;
            }
        }

        private void ClearBtn_Click(object sender, EventArgs e)
        {
            panel1.Invalidate();
        }

        private void btnImage_Click(object sender, EventArgs e)
        {
            SaveFileDialog save = new SaveFileDialog();
            save.Filter = "Bitmap Image (.bmp)|*.bmp|Gif Image (.gif)|*.gif|JPEG Image (.jpeg)|*.jpeg|Png Image (.png)|*.png|Tiff Image (.tiff)|*.tiff|Wmf Image (.wmf)|*.wmf";
            if(save.ShowDialog() == DialogResult.OK)
            {
                bm = new Bitmap(panel1.Width, panel1.Height);
                graph = Graphics.FromImage(bm);
                Rectangle rect = panel1.RectangleToScreen(panel1.ClientRectangle);
                graph.CopyFromScreen(rect.Location, Point.Empty, panel1.Size);
                bm.Save(save.FileName);
                bm.Dispose();

                graph = panel1.CreateGraphics();
                graph.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;

            }
        }

        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            moving = true;
            x = e.X;
            y = e.Y;
            panel1.Cursor = Cursors.Cross;
            startPos = e.Location;
            if (bezier)
            {
                if (points.Count == 4)
                    points.Clear();
                points.Add(e.Location);
            }
        }

        private void FillColorBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (FillColorBox.GetItemText(FillColorBox.SelectedItem))
            {
                case "Filled":
                    currentFillMode = fillMode.Filled;
                    break;

                case "Unfilled":
                    currentFillMode = fillMode.Unfilled;
                    break;

                case "Gradient":
                    currentFillMode = fillMode.Gradient;
                    break;
            }

        }
        private void txtLineWidth_SelectedIndexChanged(object sender, EventArgs e)
        {
            int width = 0;
            
            Int32.TryParse(txtLineWidth.GetItemText(txtLineWidth.SelectedItem), out width);
            pen.Width = width;
            eraserWidth = width;
        }

        private void FigureBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch(FigureBox.GetItemText(FigureBox.SelectedItem))
            {
                case "Rectangle":
                    currentShape = Shape.Rectangle;
                    break;
                case "Line":
                    currentShape = Shape.Line;
                    break;
                case "Ellipse":
                    currentShape = Shape.Ellipse;
                    break;
                case "Bezier":
                    currentShape = Shape.Bezier;
                    bezier = true;
                    break;
                case "Eraser":
                    currentShape = Shape.Eraser;
                   
                    break;
            }
        }
        private void panel1_Paint(object sender, PaintEventArgs e)
        {

        }
    }
}
