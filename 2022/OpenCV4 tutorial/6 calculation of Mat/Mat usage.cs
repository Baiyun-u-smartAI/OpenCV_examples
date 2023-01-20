using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.IO;

using OpenCvSharp; //导入OpenCV4
namespace mat_calc
{
    class Program
    {

        static void print<T>(Mat src) where T : new()
        {
            
            T t = new T();
            for (int i = 0; i < src.Rows; i++)
            {
                for (int j = 0; j < src.Cols; j++)
                {
                    if (src.Channels() == 1)
                    {

                        if (typeof(Byte) == t.GetType())
                        {
                            Console.Write(src.At<Byte>(i, j));
                        }
                        else if (typeof(float) == t.GetType())
                        {
                            Console.Write(src.At<float>(i, j));
                        }
                        else if (typeof(double) == t.GetType())
                        {
                            Console.Write(src.At<double>(i, j));
                        }
                        else return;
                    }
                    else if (src.Channels() == 3)
                    {
                        for (int k = 0; k < 3; k++)
                        {
                            if (typeof(Byte) == t.GetType())
                            {
                                Console.Write(src.At<Vec3b>(i, j)[k]);
                            }
                            else if (typeof(float) == t.GetType())
                            {
                                Console.Write(src.At<Vec3f>(i, j)[k]);
                            }
                            else if (typeof(double) == t.GetType())
                            {
                                Console.Write(src.At<Vec3d>(i, j)[k]);
                            }
                            if (k != 2) Console.Write(',');
                        }
                    }
                    Console.Write('\t');
                }
                Console.Write('\n');
            }
        }
        static void Main(string[] args)
        {
            DirectoryInfo rootDir = Directory.GetParent(Environment.CurrentDirectory);
            string root = rootDir.Parent.Parent.FullName;
            System.IO.Directory.SetCurrentDirectory(root);

            // 初始化
            Mat m;
            {
                byte[] data = new byte[] { 1, 2, 3, 4, 5, 6 };
                List<int> size = new List<int>(2) { 1, 2 };
                m = new Mat(size, MatType.CV_8UC3, data);
                print<byte>(m);
            }

            // 单像素点的运算
            {
                m.At<Vec3b>(0, 0)[1]++;
                m.At<Vec3b>(0, 1)[2]--;
                m.At<Vec3b>(0, 1)[1]*=10;
                print<byte>(m);
            }



            // 全局运算，运算得到负数->0，得到超出255->255
            {
                byte[] data = new byte[] { 1, 200, 3, 255, 5, 255 };
                ICollection<int> size = new List<int>(2) { 1, 2 };
                Mat t = new Mat(size, MatType.CV_8UC3, data);
                print<byte>(m + t);// 必须t和m具有完全相同的数据长度和类型
                print<byte>(m + new Scalar(-5, 10, -3));
                print<byte>(m / 2);

            }





            // 类型转换
            m.ConvertTo(m, MatType.CV_32FC3);
            m *= 1.3;
            print<float>(m);

        }
    }
}
