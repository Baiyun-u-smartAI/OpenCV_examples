#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "OpenCV_example.hpp"
using namespace cv;
using namespace std;

///声明全局变量					
static Mat src;static Mat src_gray;
static int thresh = 100;
static int max_thresh = 255;
static RNG rng(12345);

///声明函数
static void thresh_callback(int, void*);

int run983()
{
	///加载图形文件
	src = imread("board.jpg", 1);

	///转成灰度
	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	///柔边
	blur(src_gray, src_gray, Size(3, 3));

	///新建窗口
	const char* source_window = "Source";
	namedWindow(source_window, WINDOW_AUTOSIZE);
	imshow(source_window, src);

	///新建拉杆
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

	/// Detect edges using canny
	Canny(src_gray, canny_output, thresh, thresh * 2, 3);
	/// Find contours
	findContours(canny_output, contours, hierarchy,
		RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// Get the moments
	vector<Moments> mu(contours.size());
	for (size_t i = 0; i < contours.size(); i++)
	{
		mu[i] = moments(contours[i], false);
	}

	///  Get the mass centers:
	vector<Point2f> mc(contours.size());
	for (size_t i = 0; i < contours.size(); i++)
	{
		mc[i] = Point2f(static_cast<float>(mu[i].m10 / mu[i].m00),
			static_cast<float>(mu[i].m01 / mu[i].m00));
	}

	///绘轮廓
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	for (size_t i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255),
			rng.uniform(0, 255), rng.uniform(0, 255));

		drawContours(drawing, contours, (int)i, color
			, 2, 8, hierarchy, 0, Point());

		circle(drawing, mc[i], 4, color, -1, 8, 0);
	}

	///显示结果
	namedWindow("Contours", WINDOW_AUTOSIZE);
	imshow("Contours", drawing);

	///用时刻(moments) 00 计算区域并与结果比较
	printf("\t Info: Area and Contour Length \n");
	for (size_t i = 0; i< contours.size(); i++)
	{
		printf(" * Contour[%d] - Area (M_00) = %.2f - Area OpenCV: %.2f - Length: %.2f \n",
			(int)i, mu[i].m00, contourArea(contours[i]),
			arcLength(contours[i], true));

		Scalar color = Scalar(rng.uniform(0, 255),
			rng.uniform(0, 255), rng.uniform(0, 255));

		drawContours(drawing, contours, (int)i, color,
			2, 8, hierarchy, 0, Point());

		circle(drawing, mc[i], 4, color, -1, 8, 0);
	}
}
int(*run_moments_demo)()=run983;