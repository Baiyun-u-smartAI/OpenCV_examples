#include "OpenCV_example.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;

int run3129()
{

	double alpha = 0, beta, input;

	Mat src1, src2, dst;

	/// Ask the user enter alpha
	std::cout << " �������Խ���(Linear Blender) " << std::endl;
	std::cout << "-----------------------" << std::endl;
	std::cout << "* ���� 0 �� 1 �� alpha ֵ: ";
	std::cin >> input;

	// ȷ�� alpha ֵ�������ȷ���� 0 �� 1 ֮��
	if (input >= 0 && input <= 1)
	{
		alpha = input;
	}

	/// ��ȡ������С��������ͬ��ͼ�ļ�
	src1 = imread("LinuxLogo.jpg");
	src2 = imread("WindowsLogo.jpg");

	if (!src1.data)
	{ std::cout << "Error loading src1" << std::endl; return -1; }

	if (!src2.data)
	{ std::cout << "Error loading src2" << std::endl; return -1; }

	namedWindow("Linear Blend", 1);

	beta = (1.0 - alpha);
	addWeighted(src1, alpha, src2, beta, 0.0, dst);

	imshow("Linear Blend", dst);

	waitKey(0);
	return 0;
}

int(*run_AddingImages)()=run3129;
