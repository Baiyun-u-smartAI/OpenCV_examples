#include "OpenCV_example.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

int run310()
{
	// ͼ�ļ�
	char* imageName = "1.jpg";

	// ��ȡͼ�ļ�
	Mat image = imread(imageName, 1);

	Mat gray_image;
	// ͼ�ļ���BGRת�ɻҶ�
	cvtColor(image, gray_image, COLOR_BGR2GRAY);

	// ����ת�����ͼ�ļ�
	imwrite("Gray_1.jpg", gray_image);

	// ��ʾͼ�ļ����ڴ�С�Ŀ���
	namedWindow(imageName, WINDOW_AUTOSIZE);
	namedWindow("Gray image", WINDOW_AUTOSIZE);

	// ��ʾԭ��ͼ�ļ�
	imshow(imageName, image);

	// ��ʾ�Ҷ�ͼ�ļ�
	imshow("Gray image", gray_image);

	waitKey(0);

	return 0;
}

int (*run_load_modify_save_image)() =&run310;