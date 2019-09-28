#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>

using namespace cv;

int main()
{
	// ����ͼ��
	Mat image1 = imread("C:\\images\\lena.jpg");
	Mat logo = imread("C:\\opencv\\build\\doc\\opencv-logo-white.png");

	Mat image = image1, opencvlogo;

	// ��СԲͼ��Size(80, 64)
	resize(logo, opencvlogo, Size(80, 64));

	namedWindow("Image 1", CV_WINDOW_AUTOSIZE);

	// ����ͼ����Ȥ������(Region Of Interest, ROI)
	Mat imageROI;

	// Rect(x, y, col, row)
	imageROI = image(Rect(420, 420, 80, 64));

	imshow("Image 1", opencvlogo);

	// �����̱�
	addWeighted(imageROI, 1.0, opencvlogo, 0.3, 0., imageROI);

	// ��ʾ���
	namedWindow("with logo");
	imshow("with logo", image);

	/*
	//Mat mask = imread("C:\\images\\OpenCV 2 Computer Vision\\logo.bmp", 0);
	Mat mask = opencvlogo;

	// logo���ڱη�ʽ���Ƹ�imageROI
	logo.copyTo(imageROI, mask);

	namedWindow("with logo 2");
	imshow("with logo 2", image);

	// �����ٴ�����
	logo = imread("C:\\images\\OpenCV 2 Computer Vision\\logo.bmp", 0);
	image1 = imread("C:\\images\\OpenCV 2 Computer Vision\\boldt.jpg");

	// ��ͼ�������ĳɨ���
	std::vector<Mat> channels;
	split(image1, channels);

	imageROI = channels.at(1);

	addWeighted(imageROI(Rect(385, 270, logo.cols, logo.rows)), 1.0,
		logo, 0.5, 0., imageROI(Rect(385, 270, logo.cols, logo.rows)));

	merge(channels, image1);

	namedWindow("with logo 3");
	imshow("with logo 3", image1);
	*/
	waitKey();

	return 0;
}
