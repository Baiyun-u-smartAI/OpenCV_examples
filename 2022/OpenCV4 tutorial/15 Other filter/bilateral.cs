using System;
using System.IO;
using OpenCvSharp; //导入OpenCV4

namespace bilateral
{
    
    class Program
    {
        struct para4Bi
        {
            public int d;
            public double sigmaColor;
            public double sigmaSpace;
        }
        static void Main(string[] args)
        {
            DirectoryInfo rootDir = Directory.GetParent(Environment.CurrentDirectory);
            string root = rootDir.Parent.Parent.FullName;
            System.IO.Directory.SetCurrentDirectory(root);

            Mat src = Cv2.ImRead("Robert_Delaunay,_1913,_Premier_Disque.jpg");
            
            if (!src.Empty())
            {
                Mat dst = new Mat();


                para4Bi para = new para4Bi() { d = 1, sigmaColor = 2, sigmaSpace = 0.5 };
                Cv2.NamedWindow("bilateral"); // 创建窗口

                Cv2.CreateTrackbar("d", "bilateral", 30, (int d, IntPtr userData) =>
                {
                    para.d = d+20;//! d从20开始到50
                    Cv2.BilateralFilter(src, dst, para.d, para.sigmaColor, para.sigmaSpace); // todo 双边滤波
                    Cv2.ImShow("bilateral", dst);
                });// 创建滑杆，d最大值预设为50
                Cv2.SetTrackbarPos("d", "bilateral", 1);// d 的初始值为1

                Cv2.CreateTrackbar("sigmaColor(2x)", "bilateral", 30, (int s_C2, IntPtr userData) =>
                {
                    para.sigmaColor = (s_C2 + 20) * 2;//! sigmaColor从40开始到100
                    Cv2.BilateralFilter(src, dst, para.d, para.sigmaColor, para.sigmaSpace); // todo 双边滤波
                    Cv2.ImShow("bilateral", dst);
                });// 创建滑杆，sigmaColor最大值预设为100
                Cv2.SetTrackbarPos("sigmaColor(2x)", "bilateral", 1);// s_C2 初始值为1
                
                Cv2.CreateTrackbar("sigmaSpace(1/2)", "bilateral", 30, (int s_S_half, IntPtr userData) =>
                {
                    para.sigmaSpace = (s_S_half + 20) / 2.0;//! sigmaColor从10开始到25
                    Cv2.BilateralFilter(src, dst, para.d, para.sigmaColor, para.sigmaSpace); // todo 双边滤波
                    Cv2.ImShow("bilateral", dst);
                });// 创建滑杆，sigmaSpace最大值预设为25
                Cv2.SetTrackbarPos("sigmaSpace(1/2)", "bilateral", 1);// s_S_half 初始值为1

                Cv2.WaitKey();

            }

        }
    }
}