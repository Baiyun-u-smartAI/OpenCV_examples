using System;
using System.IO;
using OpenCvSharp;

namespace split_merge
{
    class Program
    {

        static void Main(string[] args)
        {
            DirectoryInfo rootDir = Directory.GetParent(Environment.CurrentDirectory);
            string root = rootDir.Parent.Parent.FullName;
            System.IO.Directory.SetCurrentDirectory(root);

            VideoCapture cap = new VideoCapture("LIVE Nevskiy avenue St. Petersburg Russia, Gostiny Dvor. Невский пр. Санкт-Петербург, Гостиный двор 2022-11-09 20_18-h1wly909BYw.mp4");
            BackgroundSubtractorMOG fgbg = BackgroundSubtractorMOG.Create();
            Mat frame = new Mat();
            Mat fgMask = new Mat();
            while (true)
            {
                cap.Read(frame);
                if (frame.Empty()) break;
                else Cv2.Resize(frame, frame, new Size(), .6, .6);
                fgbg.Apply(frame, fgMask);
                Cv2.ImShow("mask", fgMask);
                if (Cv2.WaitKey(30) == 27) break;
            }
            cap.Release();

        }
    }
}
