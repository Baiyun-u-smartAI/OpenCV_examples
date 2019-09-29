#include "OpenCV_example.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

int run310()
{
	// 图文件
	char* imageName = "1.jpg";

	// 读取图文件
	Mat image = imread(imageName, 1);

	Mat gray_image;
	// 图文件从BGR转成灰度
	cvtColor(image, gray_image, COLOR_BGR2GRAY);

	// 储存转换后的图文件
	imwrite("Gray_1.jpg", gray_image);

	// 显示图文件窗口大小的控制
	namedWindow(imageName, WINDOW_AUTOSIZE);
	namedWindow("Gray image", WINDOW_AUTOSIZE);

	// 显示原先图文件
	imshow(imageName, image);

	// 显示灰度图文件
	imshow("Gray image", gray_image);

	waitKey(0);

	return 0;
}

int (*run_load_modify_save_image)() =&run310;