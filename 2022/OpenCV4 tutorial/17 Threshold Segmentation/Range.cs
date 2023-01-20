using System;
using System.IO;
using OpenCvSharp; //导入OpenCV4
using System.Collections.Generic;

namespace Gradient
{

    class Program
    {
        static void simple_test()
        {
            Mat inputImage = Cv2.ImRead("merge_split.jpg"),hsv = new Mat() ,dst = new Mat(), mask = new Mat();
            if (!inputImage.Empty())
            {
                Cv2.CvtColor(inputImage, hsv, ColorConversionCodes.BGR2HSV);
                Cv2.InRange(hsv, new Scalar(28, 100, 100), new Scalar(40, 255, 255), mask);
                Cv2.ImShow("mask", mask);

                Mat[] bgr = new Mat[3], bgr2 = new Mat[3];
                for (int i = 0; i < 3; i++)
                {
                    bgr2[i] = Mat.Zeros(MatType.CV_8UC1, new int[] { inputImage.Cols, inputImage.Rows });
                }
                bgr = Cv2.Split(inputImage);

                for (int i = 0; i < 3; i++)
                {
                    Cv2.BitwiseAnd(bgr[i], mask, bgr2[i]);
                }
                Cv2.Merge(bgr2, dst);
                Cv2.AddWeighted(inputImage, 0.2, dst, 0.8, 0, dst);
                Cv2.ImShow("inRange", dst);
                Cv2.WaitKey();
            }

        }
        static void Main(string[] args)
        {
            DirectoryInfo rootDir = Directory.GetParent(Environment.CurrentDirectory);
            string root = rootDir.Parent.Parent.FullName;
            System.IO.Directory.SetCurrentDirectory(root);

            Mat inputImage = Cv2.ImRead("merge_split.jpg");
            if (!inputImage.Empty())
            {
                Mat hsv = new Mat(), dst = new Mat(), mask = new Mat();
                Cv2.CvtColor(inputImage, hsv, ColorConversionCodes.BGR2HSV);
                Dictionary<string, int> range_data = new Dictionary<string, int>
                {
                    { "hL", 0 },
                    { "sL", 0 },
                    { "vL", 0 },
                    { "hU", 255 },
                    { "sU", 255 },
                    { "vU", 255 }
                };
                Cv2.NamedWindow("inRange", WindowFlags.AutoSize);
                Mat[] bgr = new Mat[3], bgr2 = new Mat[3];
                for (int i = 0; i < 3; i++)
                {
                    bgr2[i] = Mat.Zeros(MatType.CV_8UC1, new int[] { inputImage.Cols, inputImage.Rows });
                }
                bgr = Cv2.Split(inputImage);
                Cv2.CreateTrackbar("hLow", "inRange", 255, (int hL, IntPtr userData) =>
                {
                    Mat dst = hsv.Clone();
                    range_data["hL"] = hL;
                    Cv2.InRange(hsv, new Scalar(range_data["hL"], range_data["sL"], range_data["vL"]), new Scalar(range_data["hU"], range_data["sU"], range_data["vU"]), mask);

                    for (int i = 0; i < 3; i++)
                    {
                        Cv2.BitwiseAnd(bgr[i], mask, bgr2[i]);
                    }
                    Cv2.Merge(bgr2, dst);
                    Cv2.AddWeighted(inputImage, 0.2, dst, 0.8, 0, dst);
                    Cv2.ImShow("inRange", dst);

                }
                );

                Cv2.CreateTrackbar("sLow", "inRange", 255, (int sL, IntPtr userData) =>
                {
                    Mat dst = hsv.Clone();
                    range_data["sL"] = sL;
                    Cv2.InRange(hsv, new Scalar(range_data["hL"], range_data["sL"], range_data["vL"]), new Scalar(range_data["hU"], range_data["sU"], range_data["vU"]), mask);

                    for (int i = 0; i < 3; i++)
                    {
                        Cv2.BitwiseAnd(bgr[i], mask, bgr2[i]);
                    }
                    Cv2.Merge(bgr2, dst);
                    Cv2.AddWeighted(inputImage, 0.2, dst, 0.8, 0, dst);
                    Cv2.ImShow("inRange", dst);

                }
                );
                Cv2.CreateTrackbar("vLow", "inRange", 255, (int vL, IntPtr userData) =>
                {
                    Mat dst = hsv.Clone();
                    range_data["vL"] = vL;
                    Cv2.InRange(hsv, new Scalar(range_data["hL"], range_data["sL"], range_data["vL"]), new Scalar(range_data["hU"], range_data["sU"], range_data["vU"]), mask);

                    for (int i = 0; i < 3; i++)
                    {
                        Cv2.BitwiseAnd(bgr[i], mask, bgr2[i]);
                    }
                    Cv2.Merge(bgr2, dst);
                    Cv2.AddWeighted(inputImage, 0.2, dst, 0.8, 0, dst);
                    Cv2.ImShow("inRange", dst);

                }
                );
                Cv2.CreateTrackbar("hUp", "inRange", 255, (int hU, IntPtr userData) =>
                {
                    Mat dst = hsv.Clone();
                    range_data["hU"] = hU;
                    Cv2.InRange(hsv, new Scalar(range_data["hL"], range_data["sL"], range_data["vL"]), new Scalar(range_data["hU"], range_data["sU"], range_data["vU"]), mask);

                    for (int i = 0; i < 3; i++)
                    {
                        Cv2.BitwiseAnd(bgr[i], mask, bgr2[i]);
                    }
                    Cv2.Merge(bgr2, dst);
                    Cv2.AddWeighted(inputImage, 0.2, dst, 0.8, 0, dst);
                    Cv2.ImShow("inRange", dst);

                }
                );

                Cv2.CreateTrackbar("sUp", "inRange", 255, (int sU, IntPtr userData) =>
                {
                    Mat dst = hsv.Clone();
                    range_data["sU"] = sU;
                    Cv2.InRange(hsv, new Scalar(range_data["hL"], range_data["sL"], range_data["vL"]), new Scalar(range_data["hU"], range_data["sU"], range_data["vU"]), mask);

                    for (int i = 0; i < 3; i++)
                    {
                        Cv2.BitwiseAnd(bgr[i], mask, bgr2[i]);
                    }
                    Cv2.Merge(bgr2, dst);
                    Cv2.AddWeighted(inputImage, 0.2, dst, 0.8, 0, dst);
                    Cv2.ImShow("inRange", dst);

                }
                );
                Cv2.CreateTrackbar("vUp", "inRange", 255, (int vU, IntPtr userData) =>
                {
                    Mat dst = hsv.Clone();
                    range_data["vU"] = vU;
                    Cv2.InRange(hsv, new Scalar(range_data["hL"], range_data["sL"], range_data["vL"]), new Scalar(range_data["hU"], range_data["sU"], range_data["vU"]), mask);

                    for (int i = 0; i < 3; i++)
                    {
                        Cv2.BitwiseAnd(bgr[i], mask, bgr2[i]);
                    }
                    Cv2.Merge(bgr2, dst);
                    Cv2.AddWeighted(inputImage, 0.2, dst, 0.8, 0, dst);
                    Cv2.ImShow("inRange", dst);

                }
                );
                Cv2.SetTrackbarPos("hLow", "inRange", 0);
                Cv2.SetTrackbarPos("sLow", "inRange", 0);
                Cv2.SetTrackbarPos("vLow", "inRange", 0);
                Cv2.SetTrackbarPos("hUp", "inRange", 255);
                Cv2.SetTrackbarPos("sUp", "inRange", 255);
                Cv2.SetTrackbarPos("vUp", "inRange", 255);
                Cv2.WaitKey();

            }
        }
    }
}