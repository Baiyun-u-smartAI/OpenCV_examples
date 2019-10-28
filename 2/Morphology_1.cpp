#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "OpenCV_example.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// 声明全局变量
static Mat src, erosion_dst, dilation_dst;

static char text[] = "Element: 0:Rect 1:Cross 2:Ellipse";

static int erosion_elem = 0;
static int erosion_size = 0;
static int dilation_elem = 0;
static int dilation_size = 0;
static int const max_elem = 2;
static int const max_kernel_size = 21;

/** 声明函数 */
void Erosion(int, void*);
void Dilation(int, void*);

int run3281()
{
	/// 加载图形文件
	src = imread("opencv-logo.png");
	if (!src.data)
		return -1;

	/// 建立窗口
	namedWindow("原图", WINDOW_AUTOSIZE);
	namedWindow("浸蚀", WINDOW_AUTOSIZE);
	namedWindow("膨胀", WINDOW_AUTOSIZE);

	moveWindow("膨胀", src.cols, 0);

	/// 建立浸蚀(Erosion)滑杆
	createTrackbar("Element:", "浸蚀",
		&erosion_elem, max_elem, Erosion);

	createTrackbar("Kernel:", "浸蚀",
		&erosion_size, max_kernel_size,	Erosion);

	/// 建立膨胀(Dilation)滑杆
	createTrackbar("Element:", "膨胀",
		&dilation_elem, max_elem, Dilation);

	createTrackbar("Kernel:", "膨胀",
		&dilation_size, max_kernel_size, Dilation);

	imshow("原图", src);

	/// 主运算开始
	Erosion(0, 0);

	Dilation(0, 0);

	waitKey(0);
	return 0;
}

void Erosion(int, void*)
{
	int erosion_type = 0;
	if (erosion_elem == 0) {
		erosion_type = MORPH_RECT;
	} else if (erosion_elem == 1) {
		erosion_type = MORPH_CROSS;
	} else if (erosion_elem == 2) {
		erosion_type = MORPH_ELLIPSE;
	}

	Mat element = getStructuringElement(erosion_type,
		Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		Point(erosion_size, erosion_size));

	/// 使用浸蚀(erosion)运算
	erode(src, erosion_dst, element);

	// 取得文字中心点
	Point textOrg(10, 25);
	putText(erosion_dst, text, textOrg, FONT_HERSHEY_SIMPLEX, 1, 3);

	imshow("浸蚀", erosion_dst);
}

void Dilation(int, void*)
{
	int dilation_type = 0;
	if (dilation_elem == 0) {
		dilation_type = MORPH_RECT;
	} else if (dilation_elem == 1) {
		dilation_type = MORPH_CROSS;
	} else if (dilation_elem == 2) {
		dilation_type = MORPH_ELLIPSE;
	}

	Mat element = getStructuringElement(dilation_type,
		Size(2 * dilation_size + 1, 2 * dilation_size + 1),
		Point(dilation_size, dilation_size));

	/// 使用膨胀(dilation)运算
	dilate(src, dilation_dst, element);

	// 取得文字中心点
	Point textOrg(10, 25);
	putText(dilation_dst, text, textOrg, FONT_HERSHEY_SIMPLEX, 1, 3);

	imshow("膨胀", dilation_dst);
}

int (*run_Morphology1)()=run3281;