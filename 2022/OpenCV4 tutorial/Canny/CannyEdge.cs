using System;
using System.IO;
using OpenCvSharp; //导入OpenCV4

namespace CannyEdge
{

    class Program
    {

        static void Main(string[] args)
        {
            DirectoryInfo rootDir = Directory.GetParent(Environment.CurrentDirectory);
            string root = rootDir.Parent.Parent.FullName;
            System.IO.Directory.SetCurrentDirectory(root);

            Mat inputImage = Cv2.ImRead("aaa.jpg");
            if (!inputImage.Empty())
            {
                Mat gray = new Mat(), blurImage = new Mat(), cedge = new Mat();
                int edgeThresh = 1, edgeThreshScharr = 1;
                cedge.Create(inputImage.Size(), inputImage.Type());
                Cv2.CvtColor(inputImage, gray, ColorConversionCodes.BGR2GRAY);
                // Create a window
                Cv2.NamedWindow("Edge map : Canny default (Sobel gradient)", WindowFlags.AutoSize);
                // create a toolbar
                Cv2.CreateTrackbar("Canny threshold default", "Edge map : Canny default (Sobel gradient)", 100, (int edgeTh, IntPtr userdata) =>
                {
                    edgeThresh = edgeTh;
                    Mat edge1 = new Mat();
                    Cv2.Blur(gray, blurImage, new Size(3, 3));
                    // Run the edge detector on grayscale
                    Cv2.Canny(blurImage, edge1, edgeThresh, edgeThresh * 3, 3);
                    cedge = cedge.SetTo(new Scalar(0, 0, 0));
                    inputImage.CopyTo(cedge, edge1);
                    Cv2.ImShow("Edge map : Canny default (Sobel gradient)", cedge);


                });
                Cv2.SetTrackbarPos("Canny threshold default", "Edge map : Canny default (Sobel gradient)", edgeThresh);


                Cv2.NamedWindow("Edge map : Canny with custom gradient (Scharr)", WindowFlags.AutoSize);
                Cv2.CreateTrackbar("Canny threshold Scharr", "Edge map : Canny with custom gradient (Scharr)", 400, (int edgeThScharr, IntPtr userdata) =>
                {
                    edgeThreshScharr = edgeThScharr;
                    Mat edge2 = new Mat(), dx = new Mat(), dy = new Mat();
                    Cv2.Blur(gray, blurImage, new Size(3, 3));
                    Cv2.Scharr(blurImage, dx, MatType.CV_16S, 1, 0);
                    Cv2.Scharr(blurImage, dy, MatType.CV_16S, 0, 1);
                    Cv2.Canny(dx, dy, edge2, edgeThreshScharr, edgeThreshScharr * 3);
                    cedge = cedge.SetTo(new Scalar(0, 0, 0));
                    inputImage.CopyTo(cedge, edge2);
                    Cv2.ImShow("Edge map : Canny with custom gradient (Scharr)", cedge);


                });

                Cv2.SetTrackbarPos("Canny threshold Scharr", "Edge map : Canny with custom gradient (Scharr)", edgeThreshScharr);
                // Wait and Exit
                Cv2.WaitKey();
            }

        }
    }
}