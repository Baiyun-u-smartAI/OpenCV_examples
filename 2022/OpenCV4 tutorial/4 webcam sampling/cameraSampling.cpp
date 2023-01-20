#include <opencv2/opencv.hpp>
#include <windows.h>

using namespace cv;
int main()
{
    // 创建视频捕获对象cap
    VideoCapture cap;
    // 打开默认的摄像头
    cap.open("http://192.168.42.129:8080/video");
    // 创建存放一帧图片的Mat对象
    Mat frame;
    while (1)
    {
        // 读取一帧图片
        cap >> frame;//todo 相当于cap.read(frame);
        
        if (frame.empty())
        {
            std::cout<<GetTickCount()<<":Failed to read current frame"<<std::endl;
            continue;
        }

        imshow("camera 0 ",frame);
        // 大约延时25ms后读取下一帧，按下ESC结束
        if (waitKey(25)==27) break;


    }/* end of camera capture circle */


}/* end of Main */