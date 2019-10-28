#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "OpenCV_example.hpp"
#include <iostream>

using namespace cv;
using namespace std;

///����ȫ�ֱ���
static Mat src;
static Mat hsv;
static Mat mask;

static int lo = 20; int up = 20;
static const char* window_image = "Source image";

///��������
void Hist_and_Backproj();
void pickPoint(int event, int x, int y, int, void*);

int run109()
{
	///����ͼ���ļ�
	src = imread("hand_sample1.jpg", 1);

	///ת��HSV
	cvtColor(src, hsv, COLOR_BGR2HSV);

	///��ʾͼ���ļ�
	namedWindow(window_image, WINDOW_AUTOSIZE);
	imshow(window_image, src);

	///��������������ʽ�ٽ紦��(floodfill thresholds)
	createTrackbar("Low thresh", window_image, &lo, 255, 0);
	createTrackbar("High thresh", window_image, &up, 255, 0);

	///�������ص�����
	setMouseCallback(window_image, pickPoint, 0);

	waitKey(0);

	return 0;
}

void pickPoint(int event, int x, int y, int, void*)
{
	///û��������������
	if (event != EVENT_LBUTTONDOWN)
		return;

	Point seed = Point(x, y);

	//ȡ�����벢����
	int newMaskVal = 255;
	Scalar newVal = Scalar(120, 120, 120);

	int connectivity = 8;
	int flags = connectivity + (newMaskVal << 8) +
		FLOODFILL_FIXED_RANGE + FLOODFILL_MASK_ONLY;

	Mat mask2 = Mat::zeros(src.rows + 2, src.cols + 2, CV_8UC1);
	floodFill(src, mask2, seed, newVal, 0,
		Scalar(lo, lo, lo), Scalar(up, up, up), flags);
	mask = mask2(Range(1, mask2.rows - 1),
		Range(1, mask2.cols - 1));

	imshow("Mask", mask);

	Hist_and_Backproj();
}

void Hist_and_Backproj()
{
	MatND hist;
	int h_bins = 30; int s_bins = 32;
	int histSize[] = { h_bins, s_bins };

	float h_range[] = { 0, 179 };
	float s_range[] = { 0, 255 };
	const float* ranges[] = { h_range, s_range };

	int channels[] = { 0, 1 };

	///ȡ��ɫ�׷ֲ�
	calcHist(&hsv, 1, channels, mask, hist, 2,
		histSize, ranges, true, false);

	///������
	normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());

	///��ͶӰ
	MatND backproj;
	calcBackProject(&hsv, 1, channels, hist,
		backproj, ranges, 1, true);

	///��ʾ��ͶӰ���
	imshow("BackProj", backproj);
}
int(*run_calcBackProject_Demo2)()=run109;