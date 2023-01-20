using System;
using System.Collections.Generic;
using System.IO;
using OpenCvSharp; //导入OpenCV4

namespace Sobel
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

                // todo 使用filter2D进行导向滤波
                float[] data = new float[] { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
                List<int> size = new List<int>(2) { 3, 3 };
                kernel = new Mat(size, MatType.CV_32FC1, data);
                src.ConvertTo(tmp, MatType.CV_16SC3);// 因为涉及负数要转换类型
                Cv2.Filter2D(tmp, tmp, tmp.Depth(), kernel);
                tmp = Cv2.Abs(tmp); // 滤波后求绝对值
                tmp.ConvertTo(dst, MatType.CV_8UC3); // 输出前转换为CV_8UC3->dst
                Cv2.ImShow("dx(filter2D)", dst);

                // todo 使用Sobel进行导向滤波
                Cv2.Sobel(src, dst, src.Depth(), 1, 0, 3); // 第4~5个变量分别为int dx, int dy；dx和dy为求导次数，第6为滤波核大小
                Cv2.ImShow("dx(Sobel)", dst);

                Cv2.Sobel(src, dst, src.Depth(), 0, 1, 3); // 第4~5个变量分别为int dx, int dy；dx和dy为求导次数，第6为滤波核大小
                Cv2.ImShow("dy(Sobel)", dst);

                Cv2.WaitKey();
            }

        }
    }
}