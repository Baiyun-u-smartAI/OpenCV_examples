#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	argv[1] = "C:\\images\\lake.jpg";

	Mat image;

	// ����ͼ���ļ�
	image = imread(argv[1], CV_LOAD_IMAGE_COLOR);

	// ����ȡ�ļ��Ƿ�ɹ�
	if (!image.data)
	{
		cout << "�޷��򿪻��Ҳ���ͼ���ļ�" << std::endl;
		return -1;
	}

	// ������ʾͼ������
	namedWindow("ԭͼ", CV_WINDOW_NORMAL);
	namedWindow("��ѩͼ", CV_WINDOW_NORMAL);

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
			if (i < (int)image.cols)
				image.at<uchar>(j + 1, i) = 255;
			if (j < (int)image.rows)
				image.at<uchar>(j, i + 1) = 255;
			if (i < (int)image.cols && j < (int)image.rows)
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