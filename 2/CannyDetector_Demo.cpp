#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include "OpenCV_example.hpp"
using namespace cv;

/// ����ȫ�ֱ���
static Mat src, src_gray;
static Mat dst, detected_edges;

static int edgeThresh = 1;
static int lowThreshold;
static int const max_lowThreshold = 100;
static int ratio = 3;
static int kernel_size = 3;
static const char* window_name = "Edge Map";

// ���˻ص����� - Canny ��1:3����������
// ��Ϊ�ò�������Ĳ���������ûȡ����������
static void CannyThreshold(int, void*)
{
	/// ��3x3�ĺ��ļ�������
	blur(src_gray, detected_edges, Size(3, 3));

	/// Canny �����
	Canny(detected_edges, detected_edges, lowThreshold,
		lowThreshold*ratio, kernel_size);

	/// �� Canny �����������, 
	dst = Scalar::all(0);

	/// ��src��detected_edgesΪ���븴�Ƶ�dst
	src.copyTo(dst, detected_edges);

	/// ��ʾ�������
	imshow(window_name, dst);
	//imshow(window_name, detected_edges);
}

int run563()
{
	src = imread("1.jpg");
	if (!src.data)
		return -1;

	imshow("Lexus", src);

	/// ��һ����ԭͼ��С����̬һ��������
	dst.create(src.size(), src.type());

	/// ת�ɻҶ�
	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	/// �½�����
	namedWindow(window_name, WINDOW_AUTOSIZE);

	/// ������������������ֵ������
	createTrackbar("Min Threshold:", window_name, &lowThreshold,
		max_lowThreshold, CannyThreshold);

	/// �������ʾ���
	CannyThreshold(0, 0);

	waitKey(0);

	return 0;
}

int(*run_CannyDetector_Demo)()=run563;