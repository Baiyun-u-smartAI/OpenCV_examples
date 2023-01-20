using System;
using OpenCvSharp; //导入OpenCV4
namespace ImageQualityAnalysis
{
    class Program
    {
		
		static void Main(string[] args)
        {
            // 创建视频捕获对象cap
            VideoCapture cap = new VideoCapture();
            // 打开默认的摄像头
            cap.Open("http://192.168.42.129:8080/video");
            // 创建存放一帧图片的Mat对象
            Mat frame = new Mat();

            while (true)
            {
                // 读取一帧图片
               cap.Read(frame);

                if (frame.Empty())
                {
                    Console.WriteLine("{0}:Failed to read current frame", DateTime.Now.Ticks / TimeSpan.TicksPerMillisecond);
                    continue;
                }

                Cv2.ImShow("camera 0 ", frame);
                // 大约延时25ms后读取下一帧，按下ESC结束
                if (Cv2.WaitKey(25) == 27) break;


            }/* end of camera capture circle */
        }
    }
}
