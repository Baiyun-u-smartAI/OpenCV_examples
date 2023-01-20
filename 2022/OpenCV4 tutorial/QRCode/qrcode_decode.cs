using System;
using System.IO;
using OpenCvSharp; //导入OpenCV4

namespace QRCode
{
    
    class Program
    {
        
        static void Main(string[] args)
        {
            DirectoryInfo rootDir = Directory.GetParent(Environment.CurrentDirectory);
            string root = rootDir.Parent.Parent.FullName;
            System.IO.Directory.SetCurrentDirectory(root);

            Mat inputImage = Cv2.ImRead("encode_data.jpg");
            
            if (!inputImage.Empty())
            {
                QRCodeDetector qrDecoder = new QRCodeDetector();

                Mat rectifiedImage = new Mat();

                Point2f[] bbox;

                string data = qrDecoder.DetectAndDecode(inputImage, out bbox, rectifiedImage);
                if (data.Length > 0)
                {
                    Console.WriteLine( "Decoded Data : {0}", data);

                    rectifiedImage.ConvertTo(rectifiedImage, MatType.CV_8UC3);
                    Cv2.NamedWindow("Rectified QRCode", WindowFlags.Normal); // could be resized window
                    Cv2.ImShow("Rectified QRCode", rectifiedImage);

                    Cv2.WaitKey(0);
                }
            }

        }
    }
}