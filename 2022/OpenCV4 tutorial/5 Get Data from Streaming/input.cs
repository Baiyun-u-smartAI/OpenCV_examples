using System;
using System.IO;
using OpenCvSharp; //导入OpenCV4

namespace Input_Stream
{
    
    class Program
    {
        static void Main(string[] args)
        {
            DirectoryInfo rootDir = Directory.GetParent(Environment.CurrentDirectory);
            string root = rootDir.Parent.Parent.FullName;
            System.IO.Directory.SetCurrentDirectory(root);

            Mat frame = new Mat();
            VideoCapture cap = new VideoCapture();// 创建捕获对象


            // 读取UDP流
            cap.Open("udp://127.0.0.1:34869", VideoCaptureAPIs.FFMPEG);
            while (true)
            {
                cap.Read(frame);
                if (frame.Empty()) continue; // 防止数据头部的错误导致闪退
                Cv2.ImShow("UDP流演示", frame);
                if (Cv2.WaitKey(30) == 27) break;
            }


            // 读取RTSP流
            cap.Open("rtsp://192.168.3.4:8554/live/test", VideoCaptureAPIs.FFMPEG);
            
            while (true)
            {
                cap.Read(frame);
                if (frame.Empty()) continue; // 防止数据头部的错误导致闪退
                Cv2.ImShow("RTSP流演示", frame);
                if (Cv2.WaitKey(30) == 27) break;
            }

            // 读取RTMP流
            cap.Open("rtmp://192.168.3.4:1935/live/test", VideoCaptureAPIs.FFMPEG);

            while (true)
            {
                cap.Read(frame);
                if (frame.Empty()) continue; // 防止数据头部的错误导致闪退
                Cv2.ImShow("RTMP流演示", frame);
                if (Cv2.WaitKey(30) == 27) break;
            }

            // 带密码读取流
            cap.Open("rtmp://admin:a12345678@192.168.3.4:1935/live/test", VideoCaptureAPIs.FFMPEG);

            while (true)
            {
                cap.Read(frame);
                if (frame.Empty()) continue; // 防止数据头部的错误导致闪退
                Cv2.ImShow("RTMP+密码 流演示", frame);
                if (Cv2.WaitKey(30) == 27) break;
            }


            // 读取HTTP视频
            cap.Open("http://files.alex4ai.top/Lines%20Digital%20Abstract%20Background.mp4", VideoCaptureAPIs.FFMPEG);

            while (true)
            {
                cap.Read(frame);
                if (frame.Empty()) break; // 视频结束后退出
                Cv2.ImShow("HTTP流演示", frame);
                if (Cv2.WaitKey(30) == 27) break;
            }

            // 读取好看视频
            cap.Open("https://vd2.bdstatic.com/mda-iidnk37i7rk8k4pi/sc/mda-iidnk37i7rk8k4pi.mp4?v_from_s=hkapp-haokan-hna&auth_key=1659434840-0-0-1cae7af9f44f05fc3f4af78899f5c3ea&bcevod_channel=searchbox_feed&cd=0&pd=1&pt=3&logid=2240700530&vid=13434561325221408696&abtest=103525_2-103890_1&klogid=2240700530", VideoCaptureAPIs.FFMPEG);
            while (true)
            {
                cap.Read(frame);
                if (frame.Empty()) break; // 视频结束后退出
                Cv2.ImShow("GPU", frame);
                if (Cv2.WaitKey(30) == 27) break;
            }


            // 读取本地视频
            cap.Open("Lines Digital Abstract Background.mp4", VideoCaptureAPIs.FFMPEG);
            while (true)
            {
                cap.Read(frame);
                if (frame.Empty()) break; // 视频结束后退出
                Cv2.ImShow("本地视频展示", frame);
                if (Cv2.WaitKey(30) == 27) break;
            }

            // 读取GIF图片
            cap.Open("rtmp://admin:a12345678@192.168.3.4:1935/live/test", VideoCaptureAPIs.FFMPEG);
            string GifPath = "13f94b50bd090b8f88811959cdb96cfb.gif";
            cap.Open(GifPath, VideoCaptureAPIs.FFMPEG);
            while (true)
            {
                cap.Read(frame);
                if (frame.Empty())
                {
                    cap.Release();
                    cap.Open(GifPath, VideoCaptureAPIs.FFMPEG);//重新读取播放
                }
                else Cv2.ImShow("GIF演示", frame);
                if (Cv2.WaitKey(1) == 27) break;
            }

            // 读取本地视频
            cap.Open("https://img.aidotu.com/down/jpg/20200828/ac3e413a0d9425105f0e4097de68c5f4_114134_640_650.jpg", VideoCaptureAPIs.FFMPEG);
            
            cap.Read(frame);
            if (!frame.Empty())
            {
                Cv2.ImShow("网络图片展示", frame);
                Cv2.WaitKey();
            } 
                
        }
    }
}