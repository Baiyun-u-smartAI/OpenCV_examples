#include <opencv\cv.h>
#include <opencv\highgui.h>

using namespace cv;

int main(int argc, char* argv)
{
	// 图文件
	char* imageName = "C:\\images\\lena.jpg";

	// 读取图文件
	Mat image = imread(imageName, 1);

	Mat gray_image;
	// 图文件从BGR转成灰度
	cvtColor(image, gray_image, CV_BGR2GRAY);

	// 储存转换后的图文件
	imwrite("C:\\images\\process\\Gray_lena.jpg", gray_image);

	// 显示图文件窗口大小的控制
	namedWindow(imageName, CV_WINDOW_AUTOSIZE);
	namedWindow("Gray image", CV_WINDOW_AUTOSIZE);

	// 显示原先图文件
	imshow(imageName, image);

	// 显示灰度图文件
	imshow("C:\\images\\process\\Gray image", gray_image);

	waitKey(0);

	return 0;
}