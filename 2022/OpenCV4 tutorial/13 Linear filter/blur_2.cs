using System;
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
                Mat dst = new Mat();
                // todo 用blur函数模糊，注意Size宽和高必须是奇数
                Cv2.Blur(src, dst, new Size(21, 21));
                Cv2.ImShow("21x21 blur", dst);

                // todo 用GaussianBlur函数模糊，注意Size宽和高必须是奇数
                Cv2.GaussianBlur(src, dst, new Size(21, 21), 3);
                Cv2.ImShow("21x21 GaussianBlur(sigma=3)", dst);
                Cv2.GaussianBlur(src, dst, new Size(21, 21), 8);
                Cv2.ImShow("21x21 GaussianBlur(sigma=8)", dst);

                Cv2.WaitKey();

            }

        }
    }
}