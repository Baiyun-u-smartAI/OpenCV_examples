#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "OpenCV_example.hpp"
using namespace cv;
using namespace std;
// 声明全局变量
static Mat image0, image, gray, mask;
static int ffillMode = 1;   // 填补着色模式
static int loDiff = 20, upDiff = 20; // 滑杆起始，调整填色域
static int connectivity = 4;  // connectivity 模式
static int isColor = true;   // 灰度或彩色
static bool useMask = false;  // 使用遮蔽
static int newMaskVal = 255;
// 鼠标回复函数
static void onMouse(int event, int x, int y, int, void*)
{
	if (event != EVENT_LBUTTONDOWN)
		return;
	Point seed = Point(x, y);
	int lo = ffillMode == 0 ? 0 : loDiff;
	int up = ffillMode == 0 ? 0 : upDiff;
	int flags = connectivity + (newMaskVal << 8) +
		(ffillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);
	int b = (unsigned)theRNG() & 255;
	int g = (unsigned)theRNG() & 255;
	int r = (unsigned)theRNG() & 255;
	Rect ccomp;
	Scalar newVal = isColor ? Scalar(b, g, r) : Scalar(r*0.299 + g*0.587 +
		b*0.114);
	Mat dst = isColor ? image : gray;
	int area;
	// 使用遮蔽
	if (useMask)
	{
		threshold(mask, mask, 1, 128, THRESH_BINARY);
		area = floodFill(dst, mask, seed, newVal, &ccomp, Scalar(lo, lo, lo),
			Scalar(up, up, up), flags);
		imshow("mask", mask);
	}
	else
	{
		area = floodFill(dst, seed, newVal, &ccomp, Scalar(lo, lo, lo),
			Scalar(up, up, up), flags);
	}
	imshow("image", dst);
	cout << area << " 像素(pixel)被重画\n";
}
int run562()
{
	char* filename = "fruits.jpg";
	image0 = imread(filename, 1);
	if (image0.empty())
	{
		cout << "读取文档失败\n";
		return 0;
	}
	image0.copyTo(image);
	cvtColor(image0, gray, COLOR_BGR2GRAY);
	mask.create(image0.rows + 2, image0.cols + 2, CV_8UC1);
	namedWindow("image", 0);
	// 建立窗口滑杆回复功能
	createTrackbar("lo_diff", "image", &loDiff, 255, 0);
	createTrackbar("up_diff", "image", &upDiff, 255, 0);
	// 建立鼠标回复功能
	setMouseCallback("image", onMouse, 0);
	for (;;)
	{
		imshow("image", isColor ? image : gray);
		int c = waitKey(0);
		if ((c & 255) == 27)
		{
			cout << "结束 ...\n";
			break;
		}
		switch ((char)c)
		{
		case 'c':
			if (isColor)
			{
				cout << "设成灰度\n";
				cvtColor(image0, gray, COLOR_BGR2GRAY);
				mask = Scalar::all(0);
				isColor = false;
			}
			else
			{
				cout << "设成彩色\n";
				image0.copyTo(image);
				mask = Scalar::all(0);
				isColor = true;
			}
			break;
		case 'm':
			if (useMask)
			{
				destroyWindow("mask");
				useMask = false;
			}
			else
			{
				namedWindow("mask", 0);
				mask = Scalar::all(0);
				imshow("mask", mask);
				useMask = true;
			}
			break;
		case 'r':
			cout << "还原图像\n";
			image0.copyTo(image);
			cvtColor(image, gray, COLOR_BGR2GRAY);
			mask = Scalar::all(0);
			break;
		case 's':
			cout << "设置简易填补着色模式\n";
			ffillMode = 0;
			break;
		case 'f':
			cout << "设置固定范围填补着色模式\n";
			ffillMode = 1;
			break;
		case 'g':
			cout << "设置 Gradient (floating range) 填补着色模式\n";
			ffillMode = 2;
			break;
		case '4':
			cout << "设置 4-connectivity 模式\n";
			connectivity = 4;
			break;
		case '8':
			cout << "设置 8-connectivity 模式\n";
			connectivity = 8;
			break;
		}
	}
	return 0;
}
int(*run_calcBackProject_Demo3)()=run562;