using System;
using System.IO;
using OpenCvSharp; //导入OpenCV4
namespace resize_example
{
    class Program
    {

        static void Main(string[] args)
        {
            DirectoryInfo rootDir = Directory.GetParent(Environment.CurrentDirectory);
            string root = rootDir.Parent.Parent.FullName;
            System.IO.Directory.SetCurrentDirectory(root);

            
            Mat src = Cv2.ImRead("merge_split.jpg", ImreadModes.Color), dst = new Mat();

            if (!src.Empty())
            {
                /*! resize 常用模式
                            InterpolationFlags.Nearest 近邻插值
                            InterpolationFlags.Linear 线性插值
                            InterpolationFlags.Cubic 三次插值
                            InterpolationFlags.Area
                            InterpolationFlags.Lanczos4 三角插值
                            InterpolationFlags.LinearExact
                  */
                // 第三个参数为new Size()的时候，后面跟的两个浮点数代表图片的宽放缩倍数、高放缩倍数
                Cv2.Resize(src, dst, new Size(), 3.0f, 2.0f, InterpolationFlags.Nearest);
                Cv2.ImShow("Nearest", dst);
                Cv2.Resize(src, dst, new Size(), 3.0f, 2.0f, InterpolationFlags.Linear);
                Cv2.ImShow("Default", dst);
                Cv2.WaitKey();
                // 输出改变尺寸后的图片(Mat变量)
                Cv2.ImWrite("new_size.png", dst);
            }

        }
    }
}