#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
	argv[1] = "C:\\images\\lena.jpg";

    Mat image;

	// 加载图形文件
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);

	// 检查文件是否读取成功
    if(! image.data )
    {
        cout <<  "无法打开或找不到图形文件" << std::endl ;
        return -1;
    }

	// 建立显示图形文件的窗口
	namedWindow("Display window", CV_WINDOW_NORMAL);

	// CV_WINDOW_FREERATIO 与 CV_WINDOW_KEEPRATIO
	// CV_GUI_NORMAL 与 CV_GUI_EXPANDED

	// 在窗口显示图形文件
    imshow( "Display window", image );

	// 窗口等待按键
    waitKey(0);

    return 0;
}

