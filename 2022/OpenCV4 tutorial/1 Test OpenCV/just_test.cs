using System;
using OpenCvSharp; //导入OpenCV4
namespace CVSharpApp1
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("This is a test for OpenCVSharp");
            // 显示一张100x100全黑的图，窗口标题为"the title"
            Cv2.ImShow("the title", Mat.Zeros(100, 100, MatType.CV_8UC3));
            // 按任意键结束显示
            Cv2.WaitKey();
        }/* end of static void Main */
    }
}
