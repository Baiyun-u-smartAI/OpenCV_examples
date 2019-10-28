#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include "OpenCV_example.hpp"
using namespace cv;
using namespace std;

///声明全局变量
static Mat src, edges;
static Mat src_gray;
static Mat standard_hough, probabilistic_hough;
static int min_threshold = 50;
static int max_trackbar = 150;

static const char* standard_name = "Standard Hough Lines Demo";
static const char* probabilistic_name = "Probabilistic Hough Lines Demo";

static int s_trackbar = max_trackbar;
static int p_trackbar = max_trackbar;

///声明函数
void help();
void Standard_Hough(int, void*);
void Probabilistic_Hough(int, void*);

int run7732()
{
	src = imread("building.jpg", 1);
	if (src.empty())
		return -1;

	/// 转成灰度
	cvtColor(src, src_gray, COLOR_RGB2GRAY);

	/// 用 Canny 座图边检测
	Canny(src_gray, edges, 50, 200, 3);

	/// 用滑杆座掩码输入
	char thresh_label[50];
	sprintf(thresh_label, "Thres: %d + input", min_threshold);

	namedWindow(standard_name, WINDOW_AUTOSIZE);
	createTrackbar(thresh_label, standard_name,
		&s_trackbar, max_trackbar, Standard_Hough);

	namedWindow(probabilistic_name, WINDOW_AUTOSIZE);
	createTrackbar(thresh_label, probabilistic_name,
		&p_trackbar, max_trackbar, Probabilistic_Hough);

	/// 开始作业
	Standard_Hough(0, 0);
	waitKey(0);

	Probabilistic_Hough(0, 0);

	waitKey(0);
	return 0;
}

void Standard_Hough(int, void*)
{
	vector<Vec2f> s_lines;
	cvtColor(edges, standard_hough, COLOR_GRAY2BGR);

	HoughLines(edges, s_lines, 1, CV_PI / 180,
		min_threshold + s_trackbar, 0, 0);

	/// 1. 用标准的 Hough 转换
	for (size_t i = 0; i < s_lines.size(); i++)
	{
		float r = s_lines[i][0], t = s_lines[i][1];
		double cos_t = cos(t), sin_t = sin(t);
		double x0 = r*cos_t, y0 = r*sin_t;
		double alpha = 1000;

		Point pt1(cvRound(x0 + alpha*(-sin_t)),
			cvRound(y0 + alpha*cos_t));
		Point pt2(cvRound(x0 - alpha*(-sin_t)),
			cvRound(y0 - alpha*cos_t));

		line(standard_hough, pt1, pt2, Scalar(255, 0, 0), 3, LINE_AA);
	}

	/// 显示结果
	imshow(standard_name, standard_hough);
}

void Probabilistic_Hough(int, void*)
{
	vector<Vec4i> p_lines;
	cvtColor(edges, probabilistic_hough, COLOR_GRAY2BGR);

	HoughLinesP(edges, p_lines, 1, CV_PI / 180,
		min_threshold + p_trackbar, 30, 10);

	/// 2. 用机率的 Hough 转换
	for (size_t i = 0; i < p_lines.size(); i++)
	{
		Vec4i l = p_lines[i];
		line(probabilistic_hough, Point(l[0], l[1]),
			Point(l[2], l[3]), Scalar(255, 0, 0), 3, LINE_AA);
	}

	/// 显示结果
	imshow(probabilistic_name, probabilistic_hough);
}

int(*run_HoughLines_Demo)()=run7732;