using System;
using System.IO;
using OpenCvSharp; //导入OpenCV4

namespace morph
{

    class Program
    {

        static void Main(string[] args)
        {
            DirectoryInfo rootDir = Directory.GetParent(Environment.CurrentDirectory);
            string root = rootDir.Parent.Parent.FullName;
            System.IO.Directory.SetCurrentDirectory(root);

            Mat inputImage = Cv2.ImRead("binary-icon-30.bmp", ImreadModes.Grayscale);
            Mat dst = new Mat();
            int morph_elem = 0, morph_size = 0, morph_operator = 0;
            
            Cv2.NamedWindow("Morphology Transformations Demo"); // Create window
            Cv2.CreateTrackbar("Operator", "Morphology Transformations Demo", 7, (int Operator, IntPtr userdata) =>
            {
                morph_operator = Operator;
                Mat element = Cv2.GetStructuringElement((MorphShapes)morph_elem , new Size(2 * morph_size + 1, 2 * morph_size + 1), new Point(morph_size, morph_size));

                Cv2.MorphologyEx(inputImage, dst, (MorphTypes)morph_operator, element);
                Cv2.ImShow("Morphology Transformations Demo", dst);

            });
            Cv2.SetTrackbarPos("Operator", "Morphology Transformations Demo", 0);

            Cv2.CreateTrackbar("Element", "Morphology Transformations Demo", 2, (int elem_T, IntPtr userdata) =>
            {
                morph_elem = elem_T;
                Mat element = Cv2.GetStructuringElement((MorphShapes)morph_elem, new Size(2 * morph_size + 1, 2 * morph_size + 1), new Point(morph_size, morph_size));

                Cv2.MorphologyEx(inputImage, dst, (MorphTypes)morph_operator, element);
                Cv2.ImShow("Morphology Transformations Demo", dst);

            });
            Cv2.SetTrackbarPos("Element", "Morphology Transformations Demo", 0);

            Cv2.CreateTrackbar("Kernel size:(2n+1)", "Morphology Transformations Demo", 21, (int morph_s, IntPtr userdata) =>
            {
                morph_size = morph_s;
                Mat element = Cv2.GetStructuringElement((MorphShapes)morph_elem, new Size(2 * morph_size + 1, 2 * morph_size + 1), new Point(morph_size, morph_size));

                Cv2.MorphologyEx(inputImage, dst, (MorphTypes)morph_operator, element);
                Cv2.ImShow("Morphology Transformations Demo", dst);

            });
            Cv2.SetTrackbarPos("Kernel size:(2n+1)", "Morphology Transformations Demo", 0);

            Cv2.WaitKey();
        }
    }
}