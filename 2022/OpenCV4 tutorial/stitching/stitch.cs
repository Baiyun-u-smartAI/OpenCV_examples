using System;
using System.Collections.Generic;
using System.IO;
using OpenCvSharp;

namespace Stitching
{
    class Program
    {

        static void Main(string[] args)
        {
            DirectoryInfo rootDir = Directory.GetParent(Environment.CurrentDirectory);
            string root = rootDir.Parent.Parent.FullName;
            System.IO.Directory.SetCurrentDirectory(root);


            Mat outImg = new Mat();
            IList<Mat> panos = new List<Mat>();
            panos.Add(Cv2.ImRead(@".\1403636579763555584cam0.png"));
            panos.Add(Cv2.ImRead(@".\1403636579763555584cam1.png"));
            Stitcher sticher = Stitcher.Create(Stitcher.Mode.Panorama);
            Stitcher.Status status = sticher.Stitch(panos, outImg);
            if (status != Stitcher.Status.OK)
            {
                Console.WriteLine("Can't stitch images, error code = {0}", ((int)status));
                return;
            }
            Cv2.ImShow("out", outImg);
            Cv2.WaitKey();

        }
    }
}
