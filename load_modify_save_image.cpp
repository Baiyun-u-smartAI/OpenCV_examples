#include <opencv\cv.h>
#include <opencv\highgui.h>

using namespace cv;

int main(int argc, char* argv)
{
	// ͼ�ļ�
	char* imageName = "C:\\images\\lena.jpg";

	// ��ȡͼ�ļ�
	Mat image = imread(imageName, 1);

	Mat gray_image;
	// ͼ�ļ���BGRת�ɻҶ�
	cvtColor(image, gray_image, CV_BGR2GRAY);

	// ����ת�����ͼ�ļ�
	imwrite("C:\\images\\process\\Gray_lena.jpg", gray_image);

	// ��ʾͼ�ļ����ڴ�С�Ŀ���
	namedWindow(imageName, CV_WINDOW_AUTOSIZE);
	namedWindow("Gray image", CV_WINDOW_AUTOSIZE);

	// ��ʾԭ��ͼ�ļ�
	imshow(imageName, image);

	// ��ʾ�Ҷ�ͼ�ļ�
	imshow("C:\\images\\process\\Gray image", gray_image);

	waitKey(0);

	return 0;
}