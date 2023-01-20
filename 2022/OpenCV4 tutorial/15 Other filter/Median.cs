using System;
using System.IO;
using OpenCvSharp; //导入OpenCV4

namespace Median
{
    
    class Program
    {
        
        static void Main(string[] args)
        {
            DirectoryInfo rootDir = Directory.GetParent(Environment.CurrentDirectory);
            string root = rootDir.Parent.Parent.FullName;
            System.IO.Directory.SetCurrentDirectory(root);

            Mat src = Cv2.ImRead("Robert_Delaunay,_1913,_Premier_Disque.jpg");

            if (!src.Empty())
            {
                Mat dst = new Mat();
                
                Cv2.NamedWindow("MedianBlur"); // 创建窗口

                Cv2.CreateTrackbar("ksize", "MedianBlur", 101, (int ksize, IntPtr userData) =>
                {
                    if (ksize % 2 == 1) //! medianBlur算法要求ksize是奇数
                    {
                        Cv2.MedianBlur(src, dst, ksize);// 执行中值滤波
                        Cv2.ImShow("MedianBlur", dst);
                    }
                    else
                    {
                        Console.Error.WriteLine("ksize must be odd, but current ksize is {0} ",ksize);
                    }
                });// 创建滑杆，ksize最大值预设为101
                Cv2.SetTrackbarPos("ksize", "MedianBlur", 1);

                Cv2.WaitKey();

            }

        }
    }
}