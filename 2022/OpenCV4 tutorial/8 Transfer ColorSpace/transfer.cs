using System;
using System.IO;
using OpenCvSharp; //导入OpenCV4
namespace transfer
{
    class Program
    {

        static void Main(string[] args)
        {
            DirectoryInfo rootDir = Directory.GetParent(Environment.CurrentDirectory);
            string root = rootDir.Parent.Parent.FullName;
            System.IO.Directory.SetCurrentDirectory(root);

            // 读图
            Mat src = Cv2.ImRead("merge_split.jpg", ImreadModes.Color);

            if (!src.Empty())
            {
                Mat hsv = new Mat();
                Cv2.CvtColor(src, hsv, ColorConversionCodes.BGR2HSV);// 将图片转化为HSV通道
                hsv += new Scalar(0, 0, 50);
                Cv2.CvtColor(hsv, hsv, ColorConversionCodes.HSV2BGR);// 将图片转化为BGR通道
                Cv2.ImShow("+V", hsv);

                Mat Lab = new Mat();
                Cv2.CvtColor(src, Lab, ColorConversionCodes.BGR2Lab);// 将图片转化为Lab通道
                Lab -= new Scalar(0, 0, 50);// 修改b通道的值
                Cv2.CvtColor(Lab, Lab, ColorConversionCodes.Lab2BGR);// 将图片转化为BGR通道
                Cv2.ImShow("-b", Lab);



                Cv2.WaitKey();

            }

        }
    }
}