#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "OpenCV_example.hpp"
#include <iostream>

using namespace cv;
using namespace std;

///声明全局变量
static Mat src;
static Mat hsv;
static Mat mask;

static int lo = 20; int up = 20;
static const char* window_image = "Source image";

///声明函数
void Hist_and_Backproj();
void pickPoint(int event, int x, int y, int, void*);

int run109()
{
	///加载图形文件
	src = imread("hand_sample1.jpg", 1);

	///转成HSV
	cvtColor(src, hsv, COLOR_BGR2HSV);

	///显示图形文件
	namedWindow(window_image, WINDOW_AUTOSIZE);
	imshow(window_image, src);

	///创建滑杆做填满式临界处理(floodfill thresholds)
	createTrackbar("Low thresh", window_image, &lo, 255, 0);
	createTrackbar("High thresh", window_image, &up, 255, 0);

	///设置鼠标回调函数
	setMouseCallback(window_image, pickPoint, 0);

	waitKey(0);

	return 0;
}

void pickPoint(int event, int x, int y, int, void*)
{
	///没按鼠标左键则跳出
	if (event != EVENT_LBUTTONDOWN)
		return;

	Point seed = Point(x, y);

	//取得掩码并填满
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

	///取得色阶分布
	calcHist(&hsv, 1, channels, mask, hist, 2,
		histSize, ranges, true, false);

	///正常化
	normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());

	///后方投影
	MatND backproj;
	calcBackProject(&hsv, 1, channels, hist,
		backproj, ranges, 1, true);

	///显示后方投影结果
	imshow("BackProj", backproj);
}
int(*run_calcBackProject_Demo2)()=run109;