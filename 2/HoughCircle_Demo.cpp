#include "opencv2/Core/Core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include "OpenCV_example.hpp"
using namespace cv;

namespace
{
	// �����뻬������
	const std::string windowName
		= "Hough Circle Detection Demo";
	const std::string cannyThresholdTrackbarName
		= "Canny threshold";
	const std::string accumulatorThresholdTrackbarName
		= "Accumulator Threshold";

	// ��ʼֵ�����ֵ
	const int cannyThresholdInitialValue = 200;
	const int accumulatorThresholdInitialValue = 50;
	const int maxAccumulatorThreshold = 200;
	const int maxCannyThreshold = 255;

	void HoughDetection(const Mat& src_gray, const Mat& src_display,
			int cannyThreshold, int accumulatorThreshold)
	{
		// circleΪ�������ֵ
		std::vector<Vec3f> circles;

		// ִ�м��
		HoughCircles(src_gray, circles, HOUGH_GRADIENT,
			1, src_gray.rows / 8, cannyThreshold,
			accumulatorThreshold, 0, 0);

		// ������ɫ
		Mat display = src_display.clone();
		for (size_t i = 0; i < circles.size(); i++)
		{
			Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
			int radius = cvRound(circles[i][2]);

			// Բ������
			circle(display, center, 3, Scalar(0, 255, 0), -1, 8, 0);

			// Բ������
			circle(display, center, radius, Scalar(0, 0, 255), 3, 8, 0);
		}

		// ��ʾ���
		imshow(windowName, display);
	}
}


int run911()
{
	Mat src, src_gray;
	src = imread("opencv-logo.png", 1);
	//src = imread("C:\\images\\board.jpg", 1);
	if (!src.data)
	{
		std::cerr << "�ĵ���ȡʧ��\n";
		return -1;
	}

	// ת�ɻҶ�
	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	// �����������Բ��ô����ԲȦ���
	GaussianBlur(src_gray, src_gray, Size(9, 9), 2, 2);

	//���������ı�ǰ�ĳ�ʼֵ
	int cannyThreshold = cannyThresholdInitialValue;
	int accumulatorThreshold = accumulatorThresholdInitialValue;

	//��������
	namedWindow(windowName, WINDOW_AUTOSIZE);

	//��������
	createTrackbar(cannyThresholdTrackbarName, windowName,
		&cannyThreshold, maxCannyThreshold);

	createTrackbar(accumulatorThresholdTrackbarName,
		windowName, &accumulatorThreshold,
		maxAccumulatorThreshold);

	// ��ִ�н����ʾ
	int key = 0;
	while (key != 'q' && key != 'Q')
	{
		//����������Ϊ 0
		cannyThreshold = std::max(cannyThreshold, 1);
		accumulatorThreshold = std::max(accumulatorThreshold, 1);

		//runs the detection, and update the display
		HoughDetection(src_gray, src, cannyThreshold, accumulatorThreshold);

		key = waitKey(10);
	}

	return 0;
}

int(*run_HoughCircle_Demo)()=run911;