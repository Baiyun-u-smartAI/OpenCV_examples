#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include "OpenCV_example.hpp"
using namespace cv;

int run139()
{
	Mat src, dst, kernel;

	Point anchor;
	double delta;
	int ddepth;
	int kernel_size;
	const char* window_name = "filter2D Demo";

	int c;

	src = imread("animals.jpg");
	if (!src.data)
		return -1;

	namedWindow(window_name, WINDOW_AUTOSIZE);

	/// filter2D函数的初始参数(arguments)
	/// 核心
	anchor = Point(-1, -1);

	/// 回旋过程加到每个像素的值
	delta = 0;

	/// dst的深度，-1表示与元图相同
	ddepth = -1;

	/// Loop - 每 0.5 秒(500毫秒)用不同的核心大小筛选 (filter) 图像
	int ind = 0;
	for (;;)
	{
		c = waitKey(500);
		/// 按 'ESC' 结束程序
		if ((char)c == 27)
		{
			break;
		}

		/// 以正常化的方块筛选(normalized box filter)来更新核心大小
		kernel_size = 3 + 2 * (ind % 5);
		kernel = Mat::ones(kernel_size, kernel_size, CV_32F)
			/ (float)(kernel_size*kernel_size);

		/// 开始筛选
		filter2D(src, dst, ddepth, kernel, anchor, delta, BORDER_DEFAULT);

		imshow(window_name, dst);

		ind++;
	}

	return 0;
}
int(*run_filter2D_demo)()=run139;