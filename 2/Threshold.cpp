#include "opencv2/opencv.hpp"
#include "OpenCV_example.hpp"
using namespace cv;
using namespace std;

int run3901()
{
	namedWindow("orignal", WINDOW_AUTOSIZE);
	//namedWindow("threshold", WINDOW_AUTOSIZE);
	// ��ȡͼ��
	Mat src = imread("stuff.jpg", IMREAD_GRAYSCALE);
	imshow("orignal", src);

	waitKey(0);

	Mat dst;

	// �����ٽ�ֵ����
	threshold(src, dst, 0, 255, THRESH_BINARY);
	imshow("��������ֵ��", dst);

	//waitKey(0);

	// Thresholding with maxval set to 128
	threshold(src, dst, 0, 128, THRESH_BINARY);
	imshow("��������ֵ��", dst);

	//waitKey(0);

	// �ٽ�ֵ��Ϊ 127
	threshold(src, dst, 127, 255, THRESH_BINARY);
	imshow("��������ֵ��", dst);

	waitKey(0);

	// ʹ�� THRESH_BINARY_INV �ٽ�ֵ
	threshold(src, dst, 127, 255, THRESH_BINARY_INV);
	imshow("�����������ֵ��", dst);

	waitKey(0);

	// ʹ�� THRESH_TRUNC �ٽ�ֵ
	threshold(src, dst, 127, 255, THRESH_TRUNC);
	imshow("�ض���ֵ��", dst);

	waitKey(0);

	// ʹ�� THRESH_TOZERO �ٽ�ֵ
	threshold(src, dst, 127, 255, THRESH_TOZERO);
	imshow("��ֵΪ�㷨", dst);

	waitKey(0);

	// ʹ�� THRESH_TOZERO_INV �ٽ�ֵ
	threshold(src, dst, 127, 255, THRESH_TOZERO_INV);
	imshow("������ֵΪ�㷨", dst);

	waitKey(0);
}

int (*run_Threshold)()=run3901;