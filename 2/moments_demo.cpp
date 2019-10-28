#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "OpenCV_example.hpp"
using namespace cv;
using namespace std;

///����ȫ�ֱ���					
static Mat src;static Mat src_gray;
static int thresh = 100;
static int max_thresh = 255;
static RNG rng(12345);

///��������
static void thresh_callback(int, void*);

int run983()
{
	///����ͼ���ļ�
	src = imread("board.jpg", 1);

	///ת�ɻҶ�
	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	///���
	blur(src_gray, src_gray, Size(3, 3));

	///�½�����
	const char* source_window = "Source";
	namedWindow(source_window, WINDOW_AUTOSIZE);
	imshow(source_window, src);

	///�½�����
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

	///������
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	for (size_t i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255),
			rng.uniform(0, 255), rng.uniform(0, 255));

		drawContours(drawing, contours, (int)i, color
			, 2, 8, hierarchy, 0, Point());

		circle(drawing, mc[i], 4, color, -1, 8, 0);
	}

	///��ʾ���
	namedWindow("Contours", WINDOW_AUTOSIZE);
	imshow("Contours", drawing);

	///��ʱ��(moments) 00 �������������Ƚ�
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