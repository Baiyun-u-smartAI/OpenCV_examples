#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "OpenCV_example.hpp"
using namespace cv;
using namespace std;

///����ȫ�ֱ���
static Mat src; Mat src_gray;
static int thresh = 100;
static int max_thresh = 255;
static RNG rng(12345);

///��������
static void thresh_callback(int, void*);

int run129()
{
	///����ͼ���ļ�
	src = imread("hand_sample1.jpg", 1);

	///ת�ɻҶ�
	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	///���
	blur(src_gray, src_gray, Size(3, 3));

	///�½�����
	const char* source_window = "Source";
	namedWindow(source_window, WINDOW_AUTOSIZE);
	imshow(source_window, src);

	///�½�����
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

	///���ٽ�ֵ(Threshold)����
	threshold(src_gray, threshold_output,
		thresh, 255, THRESH_BINARY);

	///Ѱ������(contour)
	findContours(threshold_output, contours, hierarchy,
		RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	///Ϊÿ������Ѱ��͹��(convex hull) ����
	vector<vector<Point> >hull(contours.size());
	for (size_t i = 0; i < contours.size(); i++)
	{
		convexHull(Mat(contours[i]), hull[i], false);
	}

	///��������͹��
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	for (size_t i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255),
			rng.uniform(0, 255), rng.uniform(0, 255));
		///������
		drawContours(drawing, contours, (int)i, color,
			1, 8, vector<Vec4i>(), 0, Point());
		///��͹��
		drawContours(drawing, hull, (int)i, color, 1,
			8, vector<Vec4i>(), 0, Point());
	}

	///��ʾ���
	namedWindow("Hull demo", WINDOW_AUTOSIZE);
	imshow("Hull demo", drawing);
}
int(*run_hull_demo)()=run129;