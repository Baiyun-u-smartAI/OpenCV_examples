using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using OpenCvSharp; //导入OpenCV4

namespace JPEG_Compressing
{
    
    class Program
    {
        //定义用于滑杆的结构体
        struct Userdata
        {
            public IntPtr data;
            public int r;
            public int c;
        };
        /**
         * @brief Jpegcompress是JPEG编码函数
         * 
         * @param src 输入的Mat变量
         * @param dest 编码后的Mat变量
         * @param quality JPEG编码中质量 可选0~100（越高损失数据越少），默认95
         */
        static void Jpegcompress(Mat src, ref Mat dest, int quality)
        {
            byte[] buff = new byte[src.Rows * src.Cols * src.Channels()]; // 缓存图像数据区域
            int[] para = new int[] { (int)ImwriteFlags.JpegQuality, quality };// para存放JPEG编码参数  

            //将图像压缩编码到缓冲流区域
            Cv2.ImEncode(".jpg", src, out buff, para);
            
            //将压缩后的缓冲流内容解码为Mat，进行后续的处理
            dest = Cv2.ImDecode(buff, ImreadModes.Unchanged);
            
        }


        static void Main(string[] args)
        {
            DirectoryInfo rootDir = Directory.GetParent(Environment.CurrentDirectory);
            string root = rootDir.Parent.Parent.FullName;
            System.IO.Directory.SetCurrentDirectory(root);

            Mat src = Cv2.ImRead("aaa.jpg", ImreadModes.Color);
                      
            if (!src.Empty())
            {
               
                               
                Mat dst = new Mat();// 输出处理结果的变量
                //创建窗口
                Cv2.NamedWindow("after compression");

                //创建滑杆
                Cv2.CreateTrackbar("压缩质量","after compression", 100, (int quality, IntPtr userData) =>
                {                    
                    Jpegcompress(src, ref dst, quality);
                    Cv2.ImShow("after compression", dst);
                });
                Cv2.SetTrackbarPos("压缩质量", "after compression", 0);
                Cv2.WaitKey();
            }

        }
    }
}