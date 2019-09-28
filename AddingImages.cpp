#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;

int main(void)
{

	double alpha = 0, beta, input;

	Mat src1, src2, dst;

	/// Ask the user enter alpha
	std::cout << " �������Խ���(Linear Blender) " << std::endl;
	std::cout << "-----------------------" << std::endl;
	std::cout << "* ���� 0 �� 1 �� alpha ֵ: ";
	std::cin >> input;

	// ȷ�� alpha ֵ�������ȷ���� 0 �� 1 ֮��
	if (alpha >= 0 && alpha <= 1)
	{
		alpha = input;
	}

	/// ��ȡ������С��������ͬ��ͼ�ļ�
	src1 = imread("C:\\images\\LinuxLogo.jpg");
	src2 = imread("C:\\images\\WindowsLogo.jpg");

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