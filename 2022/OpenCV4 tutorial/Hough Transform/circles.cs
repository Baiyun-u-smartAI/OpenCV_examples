using System;
using System.Collections.Generic;
using System.IO;
using OpenCvSharp; //导入OpenCV4

namespace Circles
{

    class Program
    {

        static void Main(string[] args)
        {
            DirectoryInfo rootDir = Directory.GetParent(Environment.CurrentDirectory);
            string root = rootDir.Parent.Parent.FullName;
            System.IO.Directory.SetCurrentDirectory(root);

            Mat inputImage = Cv2.ImRead("circles.jpg");
            Mat gray = new Mat();
            int minRadius = 0, maxRadius = 100;
            


            Cv2.CvtColor(inputImage, gray, ColorConversionCodes.BGR2GRAY);
            Cv2.NamedWindow("Circles", WindowFlags.AutoSize);
            Cv2.CreateTrackbar("minRadius: ", "Circles", 100, (int minR, IntPtr userdata) =>
            {
                minRadius = minR;
                IEnumerable<CircleSegment> circles = Cv2.HoughCircles(gray, HoughModes.Gradient,
                 2, gray.Rows / 4, 200, 100, minRadius * 4, maxRadius * 4);
                Mat img = inputImage.Clone();
                foreach (var item in circles)
                {
                    Point center = new Point((int)Math.Round(item.Center.X, 0), (int)Math.Round(item.Center.Y, 0));
                    int radius = (int)Math.Round(item.Radius, 0);
                    Cv2.Circle(img, center, 3, new Scalar(0, 255, 0), -1, LineTypes.AntiAlias, 0);
                    Cv2.Circle(img, center, radius, new Scalar(255, 0, 0), -1, LineTypes.AntiAlias, 0);
                }
                Cv2.ImShow("Circles", img);

            });
            Cv2.SetTrackbarPos("minRadius: ", "Circles", minRadius);
            Cv2.CreateTrackbar("maxRadius: ", "Circles", 100, (int maxR, IntPtr userdata) =>
            {
                maxRadius = maxR;
                IEnumerable<CircleSegment> circles = Cv2.HoughCircles(gray, HoughModes.Gradient,
                 2, gray.Rows / 4, 200, 100, minRadius * 4, maxRadius * 4);
                Mat img = inputImage.Clone();
                foreach (var item in circles)
                {
                    Point center = new Point((int)Math.Round(item.Center.X, 0), (int)Math.Round(item.Center.Y, 0));
                    int radius = (int)Math.Round(item.Radius, 0);
                    Cv2.Circle(img, center, 3, new Scalar(0, 255, 0), -1, LineTypes.AntiAlias, 0);
                    Cv2.Circle(img, center, radius, new Scalar(255, 0, 0), 3, LineTypes.AntiAlias, 0);
                }
                Cv2.ImShow("Circles", img);

            });
            Cv2.SetTrackbarPos("maxRadius: ", "Circles", maxRadius);
            Cv2.WaitKey();
        }
    }
}