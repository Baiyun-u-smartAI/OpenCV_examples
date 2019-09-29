#include "OpenCV_example.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;


//Ϊ�˶��ص���cpp�ļ���ֻ�ǽ�main�������˸�����
int run137()
{



	Mat image;

	// ����ͼ���ļ�
	image = imread("1.jpg", IMREAD_COLOR);

	// ����ȡ�ļ��Ƿ�ɹ�
	if (!image.data)
	{
		cout << "�޷��򿪻��Ҳ���ͼ���ļ�1.jpg" << std::endl;
		return -1;
	}

	// ������ʾͼ������
	namedWindow("ԭͼ", WINDOW_NORMAL);
	namedWindow("��ѩͼ", WINDOW_NORMAL);

	imshow("ԭͼ", image);

	// ѩ����
	int i = 600;

	for (int k = 0; k < i; k++) {
		// rand() is the MFC random number generator
		// try qrand() with Qt
		int i = rand() % image.cols;
		int j = rand() % image.rows;
		if (image.channels() == 1) { // gray-level image
			image.at<uchar>(j, i) = 255;
			if (j < (int)image.cols-1)
				image.at<uchar>(j + 1, i) = 255;
			if (i < (int)image.rows-1)
				image.at<uchar>(j, i + 1) = 255;
			if (i < (int)image.cols-1 && j < (int)image.rows-1)
				image.at<uchar>(j + 1, i + 1) = 255;
		}
		else if (image.channels() == 3) { // color image
			image.at<cv::Vec3b>(j, i)[0] = 255;
			image.at<cv::Vec3b>(j, i)[1] = 255;
			image.at<cv::Vec3b>(j, i)[2] = 255;
			if (i < (int)image.cols - 1)
			{
				image.at<cv::Vec3b>(j, i + 1)[0] = 255;
				image.at<cv::Vec3b>(j, i + 1)[1] = 255;
				image.at<cv::Vec3b>(j, i + 1)[2] = 255;
			}
			if (j < (int)image.rows - 1)
			{
				image.at<cv::Vec3b>(j + 1, i)[0] = 255;
				image.at<cv::Vec3b>(j + 1, i)[1] = 255;
				image.at<cv::Vec3b>(j + 1, i)[2] = 255;
			}
			if (j < (int)image.rows - 1 && i < (int)image.cols - 1)
			{
				image.at<cv::Vec3b>(j + 1, i + 1)[0] = 255;
				image.at<cv::Vec3b>(j + 1, i + 1)[1] = 255;
				image.at<cv::Vec3b>(j + 1, i + 1)[2] = 255;
			}
		}
	}

	// �ڴ�������ʾͼ���ļ�
	imshow("��ѩͼ", image);

	// ���ڵȴ�����
	waitKey(0);

	return 0;
}

int (*run_snow)() =&run137;