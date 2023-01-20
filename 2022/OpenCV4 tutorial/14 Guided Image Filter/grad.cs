using System;
using System.IO;
using OpenCvSharp; //导入OpenCV4

namespace Gradient
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
                Mat tmp = new Mat(), dst = new Mat(), grad_x = new Mat(), grad_y = new Mat();

                // Sobel求dx和dy
                Cv2.Sobel(src, tmp, src.Depth(), 1, 0, 3); // tmp:dx
                Cv2.ImShow("dx", tmp);
                tmp.ConvertTo(grad_x, MatType.CV_32FC3); // 转化为double类型，cv::sqrt要求格式为float/double

                Cv2.Sobel(src, tmp, src.Depth(), 0, 1, 3); // tmp:dy
                Cv2.ImShow("dy", tmp);
                tmp.ConvertTo(grad_y, MatType.CV_32FC3);// 转化为double类型，cv::sqrt要求格式为float/double

                // 计算梯度值
                Mat tmp1 = new Mat(), tmp2 = new Mat();
                Cv2.Multiply(grad_x, grad_x, tmp1);// tmp1：grad_x的平方
                Cv2.Multiply(grad_y, grad_y, tmp2);// tmp2：grad_y的平方
                Cv2.Sqrt(tmp1 + tmp2, tmp);

                tmp.ConvertTo(dst, MatType.CV_8UC3);
                Cv2.ImShow("Grad", dst);

                Cv2.WaitKey();
            }

        }
    }
}