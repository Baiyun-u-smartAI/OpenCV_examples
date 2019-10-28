#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "OpenCV_example.hpp"
using namespace cv;
using namespace std;

///声明全局变量
static Mat src;
static Mat src_gray;
static int thresh = 100;
static int max_thresh = 255;
static RNG rng(12345);

///声明函数
static void thresh_callback(int, void*);

int run674()
{
	///加载图形文件
	src = imread("HappyFish.jpg", 1);

	///转成灰度
	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	///柔边
	blur(src_gray, src_gray, Size(3, 3));

	///创建窗口
	const char* source_window = "Source";
	namedWindow(source_window, WINDOW_AUTOSIZE);
	imshow(source_window, src);

	///创建滑杆
	createTrackbar(" Canny thresh:", "Source",
		&thresh, max_thresh, thresh_callback);

	thresh_callback(0, 0);

	waitKey(0);
	return(0);
}

void thresh_callback(int, void*)
{
	Mat canny_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	///用canny检测边
	Canny(src_gray, canny_output, thresh, thresh * 2, 3);
	imshow("canny", canny_output);

	///寻找轮廓
	findContours(canny_output, contours, hierarchy,
		RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	imshow("findContour", canny_output);

	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	for (size_t i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255),
			rng.uniform(0, 255), rng.uniform(0, 255));

		///画轮廓
		drawContours(drawing, contours, (int)i,
			color, 2, 8, hierarchy, 0, Point());
	}

	/// 显示结果
	namedWindow("Contours", WINDOW_AUTOSIZE);
	imshow("Contours", drawing);
}
int(*run_findContours_demo)()=run674;