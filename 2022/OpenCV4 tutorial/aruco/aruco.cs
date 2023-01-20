using System;
using System.Collections.Generic;
using System.IO;
using OpenCvSharp;

namespace Stitching
{
    class Program
    {

        static void Main(string[] args)
        {
            DirectoryInfo rootDir = Directory.GetParent(Environment.CurrentDirectory);
            string root = rootDir.Parent.Parent.FullName;
            System.IO.Directory.SetCurrentDirectory(root);

            //IList<IList<Point>> pts = new List<IList<Point>>(); // 存放多个多边形点的集合
            //pts.Add(new List<Point>()); // 添加第一条曲线
            Mat outImg = Cv2.ImRead(@".\aruco.jpg");
            Point2f[][] corners, rejectedImgPoints;
            int[] ids;
            OpenCvSharp.Aruco.CvAruco.DetectMarkers(outImg, OpenCvSharp.Aruco.CvAruco.GetPredefinedDictionary(OpenCvSharp.Aruco.PredefinedDictionaryName.Dict5X5_100), out corners, out ids, OpenCvSharp.Aruco.DetectorParameters.Create(), out rejectedImgPoints);
            for (int i = 0; i < ids.Length; i++)
            {
                //Console.WriteLine("{0}", ids[i]);
                Point topLeft = new Point(corners[i][0].X, corners[i][0].Y);
                Point topRight = new Point(corners[i][1].X, corners[i][1].Y);
                Point bottomRight = new Point(corners[i][2].X, corners[i][2].Y);
                Point bottomLeft = new Point(corners[i][3].X, corners[i][3].Y);

                Cv2.Line(outImg, topLeft, topRight, new Scalar(0, 255, 0), 5);
                Cv2.Line(outImg, topRight, bottomRight, new Scalar(0, 255, 0), 5);
                Cv2.Line(outImg, bottomRight, bottomLeft, new Scalar(0, 255, 0), 5);
                Cv2.Line(outImg, bottomLeft, topLeft, new Scalar(0, 255, 0), 5);
                Point c = new Point((topLeft.X + bottomRight.X) / 2.0, (topLeft.Y + bottomRight.Y) / 2.0);

                Cv2.Circle(outImg, c, 4, new Scalar(0, 0, 255), -1);
                Cv2.PutText(outImg, ids[i].ToString(),
                new Point(topLeft.X, topLeft.Y - 15),
                   HersheyFonts.HersheySimplex,
                   2, new Scalar(0, 0, 255), 5);
            }
        

            Cv2.ImShow("out", outImg);
            Cv2.WaitKey();

        }
    }
}
