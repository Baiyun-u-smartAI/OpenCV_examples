using System;
using System.IO;
using OpenCvSharp; //导入OpenCV4

namespace Harris
{

    class Program
    {

        static void Main(string[] args)
        {
            DirectoryInfo rootDir = Directory.GetParent(Environment.CurrentDirectory);
            string root = rootDir.Parent.Parent.FullName;
            System.IO.Directory.SetCurrentDirectory(root);

            Mat inputImage = Cv2.ImRead("CantonTower.png");
            Mat gray = new Mat(), dst = new Mat();
            Mat dst_norm = new Mat(), dst_norm_scaled = new Mat();
            int thresh = 200, blockSize = 2;
            BorderTypes border_t = BorderTypes.Default;


            Cv2.CvtColor(inputImage, gray, ColorConversionCodes.BGR2GRAY);
            Cv2.NamedWindow("Source image");
            Cv2.CreateTrackbar("Threshold: ", "Source image", 255, (int _thresh, IntPtr userdata) =>
            {
                if ((int)border_t == 3 || (int)border_t == 5)
                {
                    Console.Error.WriteLine("border type cannot be BorderTypes.Wrap(3) or BorderTypes.Transparent(5)");
                    return;
                }
                thresh = _thresh;
                Cv2.CornerHarris(gray, dst, blockSize, 3, .04, border_t);
                Cv2.Normalize(dst, dst_norm, 0, 255, NormTypes.MinMax, MatType.CV_32FC1, new Mat());
                Cv2.ConvertScaleAbs(dst_norm, dst_norm_scaled);
                Cv2.CvtColor(dst_norm_scaled, dst_norm_scaled, ColorConversionCodes.GRAY2BGR);
                dst_norm_scaled.ConvertTo(dst_norm_scaled, MatType.CV_8UC3);
                for (int i = 0; i < dst_norm.Rows; i++)
                {
                    for (int j = 0; j < dst_norm.Cols; j++)
                    {
                        if ((int)dst_norm.At<float>(i, j) > thresh)
                        {
                            Cv2.Circle(dst_norm_scaled, new Point(j, i), 5, new Scalar(0, 0, 255), 2, LineTypes.AntiAlias, 0);
                        }
                    }
                } 
                Cv2.NamedWindow("Corners detected");
                Cv2.ImShow("Corners detected", dst_norm_scaled);

            });
            Cv2.SetTrackbarPos("Threshold: ", "Source image", 200);



            Cv2.CreateTrackbar("border: ", "Source image", 6, (int b_t, IntPtr userdata) =>
            {
                border_t = (BorderTypes)b_t;
                if (b_t == 3 || b_t == 5)
                {
                    Console.Error.WriteLine("border type cannot be BORDER_WRAP(3) or BORDER_TRANSPARENT(5)");
                    return;
                }
                if (b_t == 6) border_t = BorderTypes.Isolated;
                
                Cv2.CornerHarris(gray, dst, blockSize, 3, .04, border_t);
                Cv2.Normalize(dst, dst_norm, 0, 255, NormTypes.MinMax, MatType.CV_32FC1, new Mat());
                Cv2.ConvertScaleAbs(dst_norm, dst_norm_scaled);
                Cv2.CvtColor(dst_norm_scaled, dst_norm_scaled, ColorConversionCodes.GRAY2BGR);
                dst_norm_scaled.ConvertTo(dst_norm_scaled, MatType.CV_8UC3);
                for (int i = 0; i < dst_norm.Rows; i++)
                {
                    for (int j = 0; j < dst_norm.Cols; j++)
                    {
                        if ((int)dst_norm.At<float>(i, j) > thresh)
                        {
                            Cv2.Circle(dst_norm_scaled, new Point(j, i), 5, new Scalar(0, 0, 255), 2, LineTypes.AntiAlias, 0);
                        }
                    }
                }
                Cv2.NamedWindow("Corners detected");
                Cv2.ImShow("Corners detected", dst_norm_scaled);



            });
            Cv2.SetTrackbarPos("border: ", "Source image", (int)BorderTypes.Default);


            Cv2.CreateTrackbar("blockSize: ", "Source image", 12, (int block_s, IntPtr userdata) =>
            {
                if ((int)border_t == 3 || (int)border_t == 5)
                {
                    Console.Error.WriteLine("border type cannot be BORDER_WRAP(3) or BORDER_TRANSPARENT(5)");
                    return;
                }
                blockSize = block_s;
                Cv2.CornerHarris(gray, dst, blockSize, 3, .04, border_t);
                Cv2.Normalize(dst, dst_norm, 0, 255, NormTypes.MinMax, MatType.CV_32FC1, new Mat());
                Cv2.ConvertScaleAbs(dst_norm, dst_norm_scaled);
                Cv2.CvtColor(dst_norm_scaled, dst_norm_scaled, ColorConversionCodes.GRAY2BGR);
                dst_norm_scaled.ConvertTo(dst_norm_scaled, MatType.CV_8UC3);
                for (int i = 0; i < dst_norm.Rows; i++)
                {
                    for (int j = 0; j < dst_norm.Cols; j++)
                    {
                        if ((int)dst_norm.At<float>(i, j) > thresh)
                        {
                            Cv2.Circle(dst_norm_scaled, new Point(j, i), 5, new Scalar(0, 0, 255), 2, LineTypes.AntiAlias, 0);
                        }
                    }
                }
                Cv2.NamedWindow("Corners detected");
                Cv2.ImShow("Corners detected", dst_norm_scaled);



            });
            Cv2.SetTrackbarPos("blockSize: ", "Source image", 2);


            Cv2.ImShow("Source image", inputImage);

            Cv2.WaitKey();
        }
    }
}