#include "OpenCV_example.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int run5332()
{


    Mat image;

	// 加载图形文件
    image = imread("1.jpg", IMREAD_COLOR);

	// 检查文件是否读取成功
    if(! image.data )
    {
        cout <<  "无法打开或找不到图形文件" << std::endl ;
        return -1;
    }

	// 建立显示图形文件的窗口
	namedWindow("Display window", WINDOW_NORMAL);

	// CV_WINDOW_FREERATIO 与 CV_WINDOW_KEEPRATIO
	// CV_GUI_NORMAL 与 CV_GUI_EXPANDED

	// 在窗口显示图形文件
    imshow( "Display window", image );

	// 窗口等待按键
    waitKey(0);

    return 0;
}

int (*run_display_image)() =&run5332;