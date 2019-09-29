#include "OpenCV_example.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;


//为了多重导入cpp文件，只是将main函数换了个名字
int run137()
{



	Mat image;

	// 载入图形文件
	image = imread("1.jpg", IMREAD_COLOR);

	// 检查读取文件是否成功
	if (!image.data)
	{
		cout << "无法打开或找不到图形文件1.jpg" << std::endl;
		return -1;
	}

	// 建立显示图档窗口
	namedWindow("原图", WINDOW_NORMAL);
	namedWindow("下雪图", WINDOW_NORMAL);

	imshow("原图", image);

	// 雪点数
	int i = 600;

	for (int k = 0; k < i; k++) {
		// rand() is the MFC random number generator
		// try qrand() with Qt
		int i = rand() % image.cols;
		int j = rand() % image.rows;
		if (image.channels() == 1) { // gray-level image
			image.at<uchar>(j, i) = 255;
			if (j < (int)image.cols-1)
				image.at<uchar>(j + 1, i) = 255;
			if (i < (int)image.rows-1)
				image.at<uchar>(j, i + 1) = 255;
			if (i < (int)image.cols-1 && j < (int)image.rows-1)
				image.at<uchar>(j + 1, i + 1) = 255;
		}
		else if (image.channels() == 3) { // color image
			image.at<cv::Vec3b>(j, i)[0] = 255;
			image.at<cv::Vec3b>(j, i)[1] = 255;
			image.at<cv::Vec3b>(j, i)[2] = 255;
			if (i < (int)image.cols - 1)
			{
				image.at<cv::Vec3b>(j, i + 1)[0] = 255;
				image.at<cv::Vec3b>(j, i + 1)[1] = 255;
				image.at<cv::Vec3b>(j, i + 1)[2] = 255;
			}
			if (j < (int)image.rows - 1)
			{
				image.at<cv::Vec3b>(j + 1, i)[0] = 255;
				image.at<cv::Vec3b>(j + 1, i)[1] = 255;
				image.at<cv::Vec3b>(j + 1, i)[2] = 255;
			}
			if (j < (int)image.rows - 1 && i < (int)image.cols - 1)
			{
				image.at<cv::Vec3b>(j + 1, i + 1)[0] = 255;
				image.at<cv::Vec3b>(j + 1, i + 1)[1] = 255;
				image.at<cv::Vec3b>(j + 1, i + 1)[2] = 255;
			}
		}
	}

	// 在窗口内显示图形文件
	imshow("下雪图", image);

	// 窗口等待按键
	waitKey(0);

	return 0;
}

int (*run_snow)() =&run137;