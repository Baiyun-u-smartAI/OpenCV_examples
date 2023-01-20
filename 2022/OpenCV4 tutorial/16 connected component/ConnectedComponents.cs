using System;
using System.IO;
using OpenCvSharp; //导入OpenCV4

namespace ConnectedComponents
{

    class Program
    {

        static void Main(string[] args)
        {
            DirectoryInfo rootDir = Directory.GetParent(Environment.CurrentDirectory);
            string root = rootDir.Parent.Parent.FullName;
            System.IO.Directory.SetCurrentDirectory(root);

            Mat inputImage = Cv2.ImRead("binary-icon-30.bmp", ImreadModes.Grayscale);
            Mat labels = new Mat(), stats = new Mat(), centroids = new Mat();
            // 连通域计算函数，要求输入的图片为二值图，第五个变量默认为8（八连通域）
            Cv2.ConnectedComponentsWithStats(inputImage, labels, stats, centroids);

            Mat dst = new Mat();
            Mat _labels = new Mat(), bg = new Mat();
            labels.ConvertTo(_labels, MatType.CV_8UC1);
            bg = _labels * 255;
            Cv2.CvtColor(bg, bg, ColorConversionCodes.GRAY2BGR);

            Cv2.ApplyColorMap(_labels * 15, dst, ColormapTypes.Hsv);
            Cv2.BitwiseAnd(dst, bg, dst);
            int x, y, w, h;
            for (int i = 1; i < stats.Rows; i++)
            {
                (x, y, w, h) = (stats.At<int>(i, 0), stats.At<int>(i, 1),
                    stats.At<int>(i, 2), stats.At<int>(i, 3));
                Rect rect = new Rect(x, y, w, h);
                Cv2.Rectangle(dst, rect, new Scalar(255, 255, 255), 2);// 线宽2

            }
            Cv2.ImShow("stats connectedComponents", dst);
            Cv2.WaitKey();
        }
    }
}