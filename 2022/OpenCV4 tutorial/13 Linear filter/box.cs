using System;
using System.Collections.Generic;
using System.IO;
using OpenCvSharp; //导入OpenCV4

namespace Box
{
    
    class Program
    {

        static void Main(string[] args)
        {
            DirectoryInfo rootDir = Directory.GetParent(Environment.CurrentDirectory);
            string root = rootDir.Parent.Parent.FullName;
            System.IO.Directory.SetCurrentDirectory(root);

            Mat src = Cv2.ImRead("merge_split.jpg");

            if (!src.Empty())
            {
                Mat dst = new Mat(), kernel;

                // todo 用filter2D做box filter
                // ! 直接赋值的方法定义线性滤波核kernel
                float[] data = new float[] { 1, 1, 1, 1, 1, 1, 1, 1, 1 };
                List<int> size = new List<int>(2) { 3, 3 };
                kernel = new Mat(size, MatType.CV_32FC1, data);
                kernel /= Cv2.Sum(kernel)[0];// 归一化

                Cv2.Filter2D(src, dst, src.Depth(), kernel);
                Cv2.ImShow("3x3 Box(Filter2D)", dst);


                // ! 用Mat.Ones定义线性滤波核kernel
                kernel = Mat.Ones(20, 20, MatType.CV_32FC1);
                kernel /= Cv2.Sum(kernel)[0];// 归一化

                Cv2.Filter2D(src, dst, src.Depth(), kernel);
                Cv2.ImShow("20x20 Box(Filter2D)", dst);


                // todo 用Cv2.BoxFilter
                Cv2.BoxFilter(src, dst, src.Depth(), new Size(20, 20));
                Cv2.ImShow("20x20 Box(BoxFilter)", dst);


                Cv2.WaitKey();
            }

        }
    }
}