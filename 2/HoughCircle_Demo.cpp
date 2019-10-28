#include "opencv2/Core/Core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include "OpenCV_example.hpp"
using namespace cv;

namespace
{
	// 窗口与滑杆名称
	const std::string windowName
		= "Hough Circle Detection Demo";
	const std::string cannyThresholdTrackbarName
		= "Canny threshold";
	const std::string accumulatorThresholdTrackbarName
		= "Accumulator Threshold";

	// 起始值与最大值
	const int cannyThresholdInitialValue = 200;
	const int accumulatorThresholdInitialValue = 50;
	const int maxAccumulatorThreshold = 200;
	const int maxCannyThreshold = 255;

	void HoughDetection(const Mat& src_gray, const Mat& src_display,
			int cannyThreshold, int accumulatorThreshold)
	{
		// circle为检测结果的值
		std::vector<Vec3f> circles;

		// 执行检测
		HoughCircles(src_gray, circles, HOUGH_GRADIENT,
			1, src_gray.rows / 8, cannyThreshold,
			accumulatorThreshold, 0, 0);

		// 复制颜色
		Mat display = src_display.clone();
		for (size_t i = 0; i < circles.size(); i++)
		{
			Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
			int radius = cvRound(circles[i][2]);

			// 圆的中心
			circle(display, center, 3, Scalar(0, 255, 0), -1, 8, 0);

			// 圆的轮廓
			circle(display, center, radius, Scalar(0, 0, 255), 3, 8, 0);
		}

		// 显示结果
		imshow(windowName, display);
	}
}


int run911()
{
	Mat src, src_gray;
	src = imread("opencv-logo.png", 1);
	//src = imread("C:\\images\\board.jpg", 1);
	if (!src.data)
	{
		std::cerr << "文档读取失败\n";
		return -1;
	}

	// 转成灰度
	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	// 减少噪声所以不用错误的圆圈检测
	GaussianBlur(src_gray, src_gray, Size(9, 9), 2, 2);

	//声明变量改变前的初始值
	int cannyThreshold = cannyThresholdInitialValue;
	int accumulatorThreshold = accumulatorThresholdInitialValue;

	//创建窗口
	namedWindow(windowName, WINDOW_AUTOSIZE);

	//创建滑杆
	createTrackbar(cannyThresholdTrackbarName, windowName,
		&cannyThreshold, maxCannyThreshold);

	createTrackbar(accumulatorThresholdTrackbarName,
		windowName, &accumulatorThreshold,
		maxAccumulatorThreshold);

	// 将执行结果显示
	int key = 0;
	while (key != 'q' && key != 'Q')
	{
		//检察参数不可为 0
		cannyThreshold = std::max(cannyThreshold, 1);
		accumulatorThreshold = std::max(accumulatorThreshold, 1);

		//runs the detection, and update the display
		HoughDetection(src_gray, src, cannyThreshold, accumulatorThreshold);

		key = waitKey(10);
	}

	return 0;
}

int(*run_HoughCircle_Demo)()=run911;