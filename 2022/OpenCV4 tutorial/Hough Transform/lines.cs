using System;
using System.Collections.Generic;
using System.IO;
using OpenCvSharp; //导入OpenCV4

namespace Lines
{

    class Program
    {

        static void Main(string[] args)
        {
            DirectoryInfo rootDir = Directory.GetParent(Environment.CurrentDirectory);
            string root = rootDir.Parent.Parent.FullName;
            System.IO.Directory.SetCurrentDirectory(root);

            Mat inputImage = Cv2.ImRead("circles.jpg", ImreadModes.Grayscale);
            if (!inputImage.Empty())
            {
                Mat dst = new Mat(), cdst = new Mat();
                // Edge detection
                Cv2.Canny(inputImage, dst, 50, 200, 3);
                // Copy edges to the images that will display the results in BGR
                Cv2.CvtColor(dst, cdst, ColorConversionCodes.GRAY2BGR);
                Mat cdstP = cdst.Clone();
                // Standard Hough Line Transform
                IEnumerable<LineSegmentPolar> lines = Cv2.HoughLines(dst, 1, Math.PI / 180, 150, 0, 0);// runs the actual detection
                // Draw the lines
                foreach (var item in lines)
                {
                    float rho = item.Rho, theta = item.Theta;
                    Point pt1 = new Point(), pt2 = new Point();
                    double a = Math.Cos(theta), b = Math.Sin(theta);
                    double x0 = a * rho, y0 = b * rho;
                    pt1.X = (int)Math.Round(x0 + 1000 * (-b), 0);
                    pt1.Y = (int)Math.Round(y0 + 1000 * (a), 0);
                    pt2.X = (int)Math.Round(x0 - 1000 * (-b), 0);
                    pt2.Y = (int)Math.Round(y0 - 1000 * (a), 0);
                    Cv2.Line(cdst, pt1, pt2, new Scalar(0, 0, 255), 3, LineTypes.AntiAlias);
                }
                Cv2.ImShow("Source", inputImage);
                Cv2.ImShow("Detected Lines (in red) - Standard Hough Line Transform", cdst);

                int threshold = 10, minLineLength = 10, maxLineGap = 2;
                Cv2.NamedWindow("Detected Lines (in red) - Probabilistic Line Transform", WindowFlags.AutoSize);
                Cv2.CreateTrackbar("threshold:", "Detected Lines (in red) - Probabilistic Line Transform", 30, (int th, IntPtr userdata) =>
                {
                    threshold = th;
                    // a modification of the Hough transform.
                    IEnumerable<LineSegmentPoint> lines = Cv2.HoughLinesP(dst, 1.0, Math.PI / 180, threshold * 5, (double)minLineLength * 5, (double)maxLineGap * 5);// runs the actual detection
                    Mat dstP = cdstP.Clone();
                    foreach ( var items in lines)
                    {
                        Cv2.Line(dstP, new Point(items.P1.X, items.P1.Y), new Point(items.P2.X, items.P2.Y), new Scalar(0, 0, 255), 3, LineTypes.AntiAlias);

                    }
                    Cv2.ImShow("Detected Lines (in red) - Probabilistic Line Transform", dstP);



                });
                Cv2.SetTrackbarPos("threshold:", "Detected Lines (in red) - Probabilistic Line Transform", threshold);

                Cv2.CreateTrackbar("minLineLength:", "Detected Lines (in red) - Probabilistic Line Transform", 30, (int minL, IntPtr userdata) =>
                {
                    minLineLength = minL;
                    // a modification of the Hough transform.
                    IEnumerable<LineSegmentPoint> lines = Cv2.HoughLinesP(dst, 1.0, Math.PI / 180, threshold * 5, (double)minLineLength * 5, (double)maxLineGap * 5);// runs the actual detection
                    Mat dstP = cdstP.Clone();
                    foreach (var items in lines)
                    {
                        Cv2.Line(dstP, new Point(items.P1.X, items.P1.Y), new Point(items.P2.X, items.P2.Y), new Scalar(0, 0, 255), 3, LineTypes.AntiAlias);

                    }
                    Cv2.ImShow("Detected Lines (in red) - Probabilistic Line Transform", dstP);



                });
                Cv2.SetTrackbarPos("minLineLength:", "Detected Lines (in red) - Probabilistic Line Transform", minLineLength);

                Cv2.CreateTrackbar("maxLineGap:", "Detected Lines (in red) - Probabilistic Line Transform", 30, (int maxL, IntPtr userdata) =>
                {
                    maxLineGap = maxL;
                    // a modification of the Hough transform.
                    IEnumerable<LineSegmentPoint> lines = Cv2.HoughLinesP(dst, 1.0, Math.PI / 180, threshold * 5, (double)minLineLength * 5, (double)maxLineGap * 5);// runs the actual detection
                    Mat dstP = cdstP.Clone();
                    foreach (var items in lines)
                    {
                        Cv2.Line(dstP, new Point(items.P1.X, items.P1.Y), new Point(items.P2.X, items.P2.Y), new Scalar(0, 0, 255), 3, LineTypes.AntiAlias);

                    }
                    Cv2.ImShow("Detected Lines (in red) - Probabilistic Line Transform", dstP);



                });
                Cv2.SetTrackbarPos("maxLineGap:", "Detected Lines (in red) - Probabilistic Line Transform", maxLineGap);

                // Wait and Exit
                Cv2.WaitKey();
            }

        }
    }
}