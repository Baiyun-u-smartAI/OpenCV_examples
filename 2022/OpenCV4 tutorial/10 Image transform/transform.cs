using System;
using System.Collections.Generic;
using System.IO;
using OpenCvSharp; //导入OpenCV4
namespace transform
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
                // todo 变换前的在src四个点
                List<Point2f> before = new List<Point2f>{
                    new Point2f(18, 221),
                    new Point2f(270, 0),
                    new Point2f(428, 98),
                    new Point2f(176, 336)
                };

                // todo 需要变换到dst图上的对应四个点位置
                List<Point2f> after = new List<Point2f>();               
                after.AddRange(new[]{ new Point2f(0, 0), 
                                      new Point2f(300, 0), 
                                      new Point2f(300, 200), 
                                      new Point2f(0, 200) 
                });

                // 如何用for循环输出after里面的内容
                foreach (var item in after)
                {
                    Console.WriteLine(item);
                }
                for (int i = 0; i < after.Count; i++)
                {
                    Console.WriteLine(after[i]);
                }


                Mat transMat = Cv2.GetPerspectiveTransform(before, after); // 获取变换矩阵
                Cv2.WarpPerspective(src, dst, transMat, new Size(300, 200)); // 应用变换
                Cv2.ImShow("after warping", dst);


                Cv2.WaitKey();

            }

        }
    }
}