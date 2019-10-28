#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include "OpenCV_example.hpp"
using namespace cv;

/// 声明全局变量
static Mat src, dst;

int morph_elem = 0;
int morph_size = 0;
int morph_operator = 0;
int const max_operator = 4;
int const max_elem = 2;
int const max_kernel_size = 21;

const char* window_name = "Morphology Transformations Demo";

/** 声明函数 */
void Morphology_Operations(int, void*);

int run901()
{
	/// 加载图形文件
	src = imread("baboon.jpg");
	if (!src.data)
		return -1;

	/// 建立窗口
	namedWindow(window_name, WINDOW_AUTOSIZE);



	/// 建立滑杆以选择 Morphology 运算
	createTrackbar("Operator:\n 0: Opening - 1: Closing  \n 2: Gradient - 3: Top Hat \n 4: Black Hat", window_name, &morph_operator, max_operator, Morphology_Operations);

	/// 建立滑杆以选择 kernel 类型
	createTrackbar("Element:\n 0: Rect - 1: Cross - 2: Ellipse", window_name,
		&morph_elem, max_elem,
		Morphology_Operations);

	/// 建立滑杆以选择 kernel 大小
	createTrackbar("Kernel size:\n 2n +1", window_name,
		&morph_size, max_kernel_size,
		Morphology_Operations);

	imshow(window_name, src);

	/// 主运算开始
	Morphology_Operations(0, 0);

	waitKey(0);
	return 0;
}

void Morphology_Operations(int, void*)
{

	// Since MORPH_X : 2,3,4,5 and 6
	int operation = morph_operator + 2;

	Mat element = getStructuringElement(morph_elem,
		Size(2 * morph_size + 1, 2 * morph_size + 1),
		Point(morph_size, morph_size));

	/// 使用特定的 morphology 运算
	morphologyEx(src, dst, operation, element);
	imshow(window_name, dst);
}

int(*run_Morphology2)()=run901;
