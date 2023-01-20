using System;
using System.IO;

using OpenCvSharp; //导入OpenCV4
namespace split_merge
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
                Mat[] bgr = new Mat[3];
                Cv2.Split(src,out bgr);// 分离通道
                (bgr[0],bgr[1]) = (bgr[1], bgr[0]); // 交换 B 和 G 通道
                Mat dst = new Mat();
                Cv2.Merge(bgr, dst);// 合并通道
                Cv2.ImShow("res", dst);
                Cv2.WaitKey();
            }

        }
    }
}
