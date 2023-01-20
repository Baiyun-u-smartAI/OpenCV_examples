#include <opencv2/opencv.hpp>
using namespace cv;

int main(int artc, char** argv) {
	Mat frame;

    VideoCapture cap; // 创建捕获对象

    // 读取UDP流
    cap.open("udp://127.0.0.1:34869", CAP_FFMPEG);
    while (true)
    {
        cap >> frame;
        if (frame.empty()) continue; // 防止数据头部的错误导致闪退
        imshow("Beautiful blue 3d ball abstract background",frame);
        if (waitKey(30)==27) break;
    }// 用户已经按下ESC键，结束读取UDP流

    // 读取RTSP流
    cap.open("rtsp://192.168.3.4:8554/live/test", CAP_FFMPEG);
    while (true)
    {
        cap >> frame;
        if (frame.empty()) continue; // 防止数据头部的错误导致闪退
        imshow("Beautiful blue 3d ball abstract background",frame);
        if (waitKey(30)==27) break;
    }// 用户已经按下ESC键，结束读取RTSP流

    // 读取RTMP流
    cap.open("rtmp://192.168.3.4:1935/live/test", CAP_FFMPEG);
    while (true)
    {
        cap >> frame;
        if (frame.empty()) continue; // 防止数据头部的错误导致闪退
        imshow("Beautiful blue 3d ball abstract background",frame);
        if (waitKey(30)==27) break;
    }// 用户已经按下ESC键，结束读取RTMP流

    // 带密码读取流
    cap.open("rtmp://admin:a12345678@192.168.3.4:1935/live/test", CAP_FFMPEG);
    while (true)
    {
        cap >> frame;
        if (frame.empty()) continue; // 防止数据头部的错误导致闪退
        imshow("Beautiful blue 3d ball abstract background",frame);
        if (waitKey(30)==27) break;
    }// 用户已经按下ESC键，结束带密码读取流

    
    // 读取HTTP链接视频
    cap.open("http://files.alex4ai.top/Lines%20Digital%20Abstract%20Background.mp4", CAP_FFMPEG);
    while (true)
    {
        cap >> frame;
        if (frame.empty()) break; // 视频结束后退出
        imshow("Lines Digital Abstract Background",frame);
        if (waitKey(30)==27) break;
    }// 用户已经按下ESC键，结束读取HTTP链接视频
    
	
    // 读取好看视频
    cap.open("https://vd2.bdstatic.com/mda-iidnk37i7rk8k4pi/sc/mda-iidnk37i7rk8k4pi.mp4?v_from_s=hkapp-haokan-hna&auth_key=1659434840-0-0-1cae7af9f44f05fc3f4af78899f5c3ea&bcevod_channel=searchbox_feed&cd=0&pd=1&pt=3&logid=2240700530&vid=13434561325221408696&abtest=103525_2-103890_1&klogid=2240700530", CAP_FFMPEG);
    while (true)
    {
        cap >> frame;
        if (frame.empty()) break; // 视频结束后退出
        imshow("GPU",frame);
        if (waitKey(30)==27) break;
    }// 用户已经按下ESC键，结束读取好看视频
   

    // 读取本地视频
    cap.open("Lines Digital Abstract Background.mp4", CAP_FFMPEG);
    while (true)
    {
        cap >> frame;
        if (frame.empty()) break; // 视频结束后退出
        imshow("Lines Digital Abstract Background",frame);
        if (waitKey(30)==27) break;
    }// 用户已经按下ESC键，结束读取本地视频


    // 读取GIF图片
    std::string GifPath = "13f94b50bd090b8f88811959cdb96cfb.gif";
    cap.open(GifPath, CAP_FFMPEG);
    while (true)
    {
        cap >> frame;
        if (frame.empty())
        {
            cap.release();
            cap.open(GifPath, CAP_FFMPEG);//重新读取播放
        }
        else imshow("abstract",frame);
        if (waitKey(1)==27) break;
    }// 用户已经按下ESC键，结束读取GIF图片

    // 读取网络图片(不支持png，bmp)
    cap.open("https://img.aidotu.com/down/jpg/20200828/ac3e413a0d9425105f0e4097de68c5f4_114134_640_650.jpg", CAP_FFMPEG);
    cap >> frame;
    if (frame.empty())
    {
        cap.release();
    }
    else 
    {
        imshow("smile",frame);
        waitKey(0);
    }


    return 0;
}