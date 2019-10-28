#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "OpenCV_example.hpp"
using namespace cv;
using namespace std;

/// ����ȫ�ֱ���
static Mat src;
static Mat src_gray;
static int thresh = 100;
static int max_thresh = 255;
static RNG rng(12345);

/// ��������
void thresh_callback(int, void*);

int run425()
{
	/// ����ͼ���ļ�
	src = imread("puzzle.jpg", 1);

	/// ת�ɻҶ�
	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	/// ���
	blur(src_gray, src_gray, Size(3, 3));

	/// �½�����
	const char* source_window = "Source";
	namedWindow(source_window, WINDOW_AUTOSIZE);
	imshow(source_window, src);

	/// �½�����
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

	/// ���ٽ�ֵ����
	threshold(src_gray, threshold_output,
		thresh, 255, THRESH_BINARY);

	/// Ѱ������
	findContours(threshold_output, contours, hierarchy,
		RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// Ϊÿ������Ѱ����ת�ľ�������Բ��
	vector<RotatedRect> minRect(contours.size());
	vector<RotatedRect> minEllipse(contours.size());

	for (size_t i = 0; i < contours.size(); i++)
	{
		minRect[i] = minAreaRect(Mat(contours[i]));
		if (contours[i].size() > 5)
		{
			minEllipse[i] = fitEllipse(Mat(contours[i]));
		}
	}

	/// ������, ��ת�ľ���, ��Բ��
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	for (size_t i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255),
			rng.uniform(0, 255), rng.uniform(0, 255));
		// ����
		drawContours(drawing, contours, (int)i, color,
			1, 8, vector<Vec4i>(), 0, Point());

		// ��Բ��
		ellipse(drawing, minEllipse[i], color, 2, 8);

		// ��ת�ľ���
		Point2f rect_points[4]; minRect[i].points(rect_points);
		for (int j = 0; j < 4; j++)
			line(drawing, rect_points[j],
				rect_points[(j + 1) % 4], color, 1, 8);
	}

	/// ��ʾ���
	namedWindow("Contours", WINDOW_AUTOSIZE);
	imshow("Contours", drawing);
}
int(*run_generalContours_demo2)()=run425;