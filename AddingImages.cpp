#include "OpenCV_example.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;

int run3129()
{

	double alpha = 0, beta, input;

	Mat src1, src2, dst;

	// 要求用户输入参数α 若α为0，只保留背景图像，若α为1，只保留前景图像
	std::cout << " 简易线性搅合(Linear Blender) " << std::endl;
	std::cout << "-----------------------" << std::endl;
	std::cout << "* 输入 0 到 1 的 alpha 值: ";
	std::cin >> input;

	// 确认 输入的alpha 值(input)数入的正确在于 0 与 1 之间
	if (input >= 0 && input <= 1)
	{
		alpha = input;
	}

	/// 读取两个大小与类型相同的图文件
	src1 = imread("LinuxLogo.jpg");
	src2 = imread("WindowsLogo.jpg");

	if (!src1.data)
	{ std::cout << "Error loading src1" << std::endl; return -1; }

	if (!src2.data)
	{ std::cout << "Error loading src2" << std::endl; return -1; }

	namedWindow("Linear Blend", 1);

	beta = (1.0 - alpha);
	// 图像重叠的算法公式dst = src1*alpha + src2*beta + gamma;
	// 下式中gamma=0
	addWeighted(src1, alpha, src2, beta, 0.0, dst);

	imshow("Linear Blend", dst);

	waitKey(0);
	return 0;
}

int(*run_AddingImages)()=run3129;
