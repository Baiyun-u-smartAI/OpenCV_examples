using System;
using System.Collections.Generic;
using System.IO;
using OpenCvSharp; //导入OpenCV4

namespace Laplace
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
                Mat kernel, tmp = new Mat(), dst = new Mat();

                // todo 使用filter2D进行Laplace滤波
                float[] data = new float[] { 0, 1, 0, 1, -4, 1, 0, 1, 0 };
                List<int> size = new List<int>(2) { 3, 3 };
                kernel = new Mat(size, MatType.CV_32FC1, data);
                src.ConvertTo(tmp, MatType.CV_16SC3);// 因为涉及负数要转换类型
                Cv2.Filter2D(tmp, tmp, tmp.Depth(), kernel);
                tmp = Cv2.Abs(tmp); // 滤波后求绝对值
                tmp.ConvertTo(dst, MatType.CV_8UC3); // 输出前转换为CV_8UC3->dst
                Cv2.ImShow("Laplace(filter2D)", dst);

                // todo 使用Laplacian函数
                Cv2.Laplacian(src, dst, src.Depth(), 3); // 第4个变量为滤波核大小
                Cv2.ImShow("Laplacian", dst);


                Cv2.WaitKey();
            }

        }
    }
}