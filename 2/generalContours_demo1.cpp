#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "OpenCV_example.hpp"
using namespace cv;
using namespace std;

///����ȫ�ֱ���
static Mat src;
static Mat src_gray;
static int thresh = 100;
static int max_thresh = 255;
static RNG rng(12345);

///��������
static void thresh_callback(int, void*);

int run237()
{
	///����ͼ���ļ�
	src = imread("puzzle.jpg", 1);

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
	Mat threshold_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	///���ٽ�ֵ����
	threshold(src_gray, threshold_output,
		thresh, 255, THRESH_BINARY);

	///Ѱ������
	findContours(threshold_output, contours,
		hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	///���ƵĶ��������
	vector<vector<Point> > contours_poly(contours.size());

	///����
	vector<Rect> boundRect(contours.size());

	///Բ��(Բ��,�뾶)
	vector<Point2f>center(contours.size());
	vector<float>radius(contours.size());

	for (size_t i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
		boundRect[i] = boundingRect(Mat(contours_poly[i]));
		minEnclosingCircle(contours_poly[i], center[i], radius[i]);
	}


	///��������������������Բ��
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	for (size_t i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255),
			rng.uniform(0, 255), rng.uniform(0, 255));

		///����������
		drawContours(drawing, contours_poly, (int)i,
			color, 1, 8, vector<Vec4i>(), 0, Point());

		///����
		rectangle(drawing, boundRect[i].tl(),
			boundRect[i].br(), color, 2, 8, 0);

		//Բ��
		circle(drawing, center[i], (int)radius[i], color, 2, 8, 0);
	}

	///��ʾ���
	namedWindow("Contours", WINDOW_AUTOSIZE);
	imshow("Contours", drawing);
}
int(*run_generalContours_demo1)()=run237;