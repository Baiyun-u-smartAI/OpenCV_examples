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

int run237()
{
	///加载图形文件
	src = imread("puzzle.jpg", 1);

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
	Mat threshold_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	///用临界值检测边
	threshold(src_gray, threshold_output,
		thresh, 255, THRESH_BINARY);

	///寻找轮廓
	findContours(threshold_output, contours,
		hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	///近似的多边型轮廓
	vector<vector<Point> > contours_poly(contours.size());

	///数组
	vector<Rect> boundRect(contours.size());

	///圆型(圆心,半径)
	vector<Point2f>center(contours.size());
	vector<float>radius(contours.size());

	for (size_t i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
		boundRect[i] = boundingRect(Mat(contours_poly[i]));
		minEnclosingCircle(contours_poly[i], center[i], radius[i]);
	}


	///绘多边型轮廓及许多矩型与圆型
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	for (size_t i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255),
			rng.uniform(0, 255), rng.uniform(0, 255));

		///绘多边型轮廓
		drawContours(drawing, contours_poly, (int)i,
			color, 1, 8, vector<Vec4i>(), 0, Point());

		///数组
		rectangle(drawing, boundRect[i].tl(),
			boundRect[i].br(), color, 2, 8, 0);

		//圆型
		circle(drawing, center[i], (int)radius[i], color, 2, 8, 0);
	}

	///显示结果
	namedWindow("Contours", WINDOW_AUTOSIZE);
	imshow("Contours", drawing);
}
int(*run_generalContours_demo1)()=run237;