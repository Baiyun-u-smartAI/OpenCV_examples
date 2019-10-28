#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "OpenCV_example.hpp"
using namespace cv;
using namespace std;

///声明全局变量
static Mat src; Mat src_gray;
static int thresh = 100;
static int max_thresh = 255;
static RNG rng(12345);

///声明函数
static void thresh_callback(int, void*);

int run129()
{
	///加载图形文件
	src = imread("hand_sample1.jpg", 1);

	///转成灰度
	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	///柔边
	blur(src_gray, src_gray, Size(3, 3));

	///新建窗口
	const char* source_window = "Source";
	namedWindow(source_window, WINDOW_AUTOSIZE);
	imshow(source_window, src);

	///新建滑杆
	createTrackbar(" Threshold:", "Source",
		&thresh, max_thresh, thresh_callback);

	thresh_callback(0, 0);

	waitKey(0);
	return(0);
}

void thresh_callback(int, void*)
{
	Mat src_copy = src.clone();
	Mat threshold_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	///用临界值(Threshold)检测边
	threshold(src_gray, threshold_output,
		thresh, 255, THRESH_BINARY);

	///寻找轮廓(contour)
	findContours(threshold_output, contours, hierarchy,
		RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	///为每个轮廓寻找凸壳(convex hull) 对象
	vector<vector<Point> >hull(contours.size());
	for (size_t i = 0; i < contours.size(); i++)
	{
		convexHull(Mat(contours[i]), hull[i], false);
	}

	///绘轮廓与凸壳
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	for (size_t i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255),
			rng.uniform(0, 255), rng.uniform(0, 255));
		///绘轮廓
		drawContours(drawing, contours, (int)i, color,
			1, 8, vector<Vec4i>(), 0, Point());
		///绘凸壳
		drawContours(drawing, hull, (int)i, color, 1,
			8, vector<Vec4i>(), 0, Point());
	}

	///显示结果
	namedWindow("Hull demo", WINDOW_AUTOSIZE);
	imshow("Hull demo", drawing);
}
int(*run_hull_demo)()=run129;