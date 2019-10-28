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

int run674()
{
	///����ͼ���ļ�
	src = imread("HappyFish.jpg", 1);

	///ת�ɻҶ�
	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	///���
	blur(src_gray, src_gray, Size(3, 3));

	///��������
	const char* source_window = "Source";
	namedWindow(source_window, WINDOW_AUTOSIZE);
	imshow(source_window, src);

	///��������
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

	///��canny����
	Canny(src_gray, canny_output, thresh, thresh * 2, 3);
	imshow("canny", canny_output);

	///Ѱ������
	findContours(canny_output, contours, hierarchy,
		RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	imshow("findContour", canny_output);

	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	for (size_t i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255),
			rng.uniform(0, 255), rng.uniform(0, 255));

		///������
		drawContours(drawing, contours, (int)i,
			color, 2, 8, hierarchy, 0, Point());
	}

	/// ��ʾ���
	namedWindow("Contours", WINDOW_AUTOSIZE);
	imshow("Contours", drawing);
}
int(*run_findContours_demo)()=run674;