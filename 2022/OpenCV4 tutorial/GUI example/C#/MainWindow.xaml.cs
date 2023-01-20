using System;
using System.Windows;
using OpenCvSharp;
using OpenCvSharp.WpfExtensions;


namespace opencv_wpf
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : System.Windows.Window
    {
        private Mat src;
        public MainWindow()
        {
            InitializeComponent();
            this.src = Cv2.ImRead("aec655d5c73d4167942ad8bc409733d0.png");
            ImageCV.Source = this.src.ToWriteableBitmap();


        }

        private void BrightnessBar_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            //Console.WriteLine(e.NewValue);
            int val = (int)e.NewValue;
            Mat dst = this.src + new Scalar(val, val, val);
            ImageCV.Source = dst.ToWriteableBitmap();
        }
    }
}
