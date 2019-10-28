#include <iostream>
#include <vector>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "OpenCV_example.hpp"
using namespace std;
using namespace cv;

/// 声明全局变量
static int DELAY_CAPTION = 1500;
static int DELAY_BLUR = 100;
static int MAX_KERNEL_LENGTH = 31;

static Mat src; Mat dst;
static char window_name[] = "Smoothing Demo";

/// 声明函数
int display_caption(const char* caption);
int display_dst(int delay);

int run021()
{
	namedWindow(window_name, WINDOW_AUTOSIZE);

	/// 加载图形文件
	src = imread("1.jpg", 1);

	if (display_caption("Original Image") != 0)
	{ return 0; }

	dst = src.clone();
	if (display_dst(DELAY_CAPTION) != 0)
	{ return 0; }


	/// 使用 Homogeneous 模糊法
	if (display_caption("Homogeneous Blur") != 0)
	{ return 0; }

	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
	{
		blur(src, dst, Size(i, i), Point(-1, -1));
		if (display_dst(DELAY_BLUR) != 0)
		{ return 0; }
	}


	/// 使用 Gaussian 模糊法
	if (display_caption("Gaussian Blur") != 0)
	{ return 0; }

	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
	{
		GaussianBlur(src, dst, Size(i, i), 0, 0);
		if (display_dst(DELAY_BLUR) != 0)
		{ return 0; }
	}


	/// 使用 Median 模糊法
	if (display_caption("Median Blur") != 0)
	{ return 0; }

	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
	{
		medianBlur(src, dst, i);
		if (display_dst(DELAY_BLUR) != 0)
		{ return 0; }
	}


	/// 使用 Bilateral 模糊法
	if (display_caption("Bilateral Blur") != 0)
	{ return 0; }

	for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
	{
		bilateralFilter(src, dst, i, i * 2, i / 2);
		if (display_dst(DELAY_BLUR) != 0)
		{ return 0; }
	}

	/// 显示结束并等待按键
	display_caption("End: Press a key!");

	waitKey(0);

	return 0;
}

int display_caption(const char* caption)
{
	dst = Mat::zeros(src.size(), src.type());
	putText(dst, caption,
		Point(src.cols / 4, src.rows / 2),
		FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));

	imshow(window_name, dst);
	int c = waitKey(DELAY_CAPTION);
	if (c >= 0) { return -1; }
	return 0;
}

int display_dst(int delay)
{
	imshow(window_name, dst);
	int c = waitKey(delay);
	if (c >= 0) { return -1; }
	return 0;
}

int (*run_Smoothing)()=run021;