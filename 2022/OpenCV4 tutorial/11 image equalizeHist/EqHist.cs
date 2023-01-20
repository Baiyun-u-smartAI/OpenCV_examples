using System;
using System.IO;
using OpenCvSharp; //导入OpenCV4

namespace EqHist
{
    
    class Program
    {
        

        

        static void Main(string[] args)
        {
            DirectoryInfo rootDir = Directory.GetParent(Environment.CurrentDirectory);
            string root = rootDir.Parent.Parent.FullName;
            System.IO.Directory.SetCurrentDirectory(root);


            Mat src = Cv2.ImRead("dark.jfif", ImreadModes.Color);

            if (!src.Empty())
            {
                Mat gray = new Mat(), dst= new Mat();
                Cv2.CvtColor(src, gray, ColorConversionCodes.BGR2GRAY);// 得到灰度图
                Cv2.ImShow("gray origin", gray);// 显示灰度图
                Cv2.EqualizeHist(gray, dst);// 应用直方图均衡化
                Cv2.ImShow("eq", dst);// 显示
                Cv2.WaitKey();
            }

        }
    }
}