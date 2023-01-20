using System;
using System.IO;
using OpenCvSharp; //导入OpenCV4
namespace get_data_from_image2
{
    class Program
    {
		
		static void Main(string[] args)
        {
            DirectoryInfo rootDir = Directory.GetParent(Environment.CurrentDirectory);
            string root = rootDir.Parent.Parent.FullName;
            System.IO.Directory.SetCurrentDirectory(root);
            
            // 读图
            Mat src = Cv2.ImRead("aaa.jpg", ImreadModes.Grayscale);

            if (!src.Empty())
            {
                // 读取(317,455)的数据,相当于读455行，317列的数据
                Byte p = src.At<Byte>(455, 317);
                /*! 注意，At函数如果越界会报:“Attempted to read or write protected memory. This is often an indication that other memory is corrupt.”)*/
                Console.WriteLine( p );

                
            }

        }
    }
}